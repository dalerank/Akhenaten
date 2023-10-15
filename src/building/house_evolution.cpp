#include "house_evolution.h"

#include "building/house.h"
#include "building/model.h"
#include "city/houses.h"
#include "city/resource.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "game/resource.h"
#include "game/time.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "grid/routing/routing_terrain.h"
#include "grid/tiles.h"

enum e_house_progress { 
    E_HOUSE_EVOLVE = 1,
    E_HOUSE_NONE = 0, 
    E_HOUSE_DECAY = -1
};

static e_house_progress check_evolve_desirability(building* house) {
    int level = house->subtype.house_level;
    const model_house* model = model_get_house(level);
    int evolve_des = model->evolve_desirability;
    if (level >= HOUSE_PALATIAL_ESTATE) {
        evolve_des = 1000;
    }

    int current_des = house->desirability;
    e_house_progress status;
    if (current_des <= model->devolve_desirability) {
        status = E_HOUSE_DECAY;
    } else if (current_des >= evolve_des)
        status = E_HOUSE_EVOLVE;
    else {
        status = E_HOUSE_NONE;
    }
    house->data.house.evolve_text_id = status; // BUG? -1 in an unsigned char?
    return status;
}

static e_house_progress has_required_goods_and_services(building* house, int for_upgrade, house_demands* demands) {
    int level = house->subtype.house_level;
    if (for_upgrade)
        ++level;

    const model_house* model = model_get_house(level);
    // water
    int water = model->water;
    if (!house->has_water_access) {
        if (water >= 2) {
            ++demands->missing.fountain;
            return E_HOUSE_NONE;
        }
        if (water == 1 && !house->has_well_access) {
            ++demands->missing.well;
            return E_HOUSE_NONE;
        }
    }
    // entertainment
    int entertainment = model->entertainment;
    if (house->data.house.entertainment < entertainment) {
        if (house->data.house.entertainment)
            ++demands->missing.more_entertainment;
        else {
            ++demands->missing.entertainment;
        }
        return E_HOUSE_NONE;
    }
    // education
    int education = model->education;
    if (house->data.house.education < education) {
        if (house->data.house.education)
            ++demands->missing.more_education;
        else {
            ++demands->missing.education;
        }
        return E_HOUSE_NONE;
    }
    if (education == 2) {
        ++demands->requiring.school;
        ++demands->requiring.library;
    } else if (education == 1)
        ++demands->requiring.school;

    // religion
    int religion = model->religion;
    if (house->data.house.num_gods < religion) {
        if (religion == 1) {
            ++demands->missing.religion;
            return E_HOUSE_NONE;
        } else if (religion == 2) {
            ++demands->missing.second_religion;
            return E_HOUSE_NONE;
        } else if (religion == 3) {
            ++demands->missing.third_religion;
            return E_HOUSE_NONE;
        }
    } else if (religion > 0)
        ++demands->requiring.religion;

    // dentist
    int dentist = model->dentist;
    if (house->data.house.dentist < dentist) {
        ++demands->missing.dentist;
        return E_HOUSE_NONE;
    }
    if (dentist == 1) {
        ++demands->requiring.dentist;
    }

    // physician
    int magistrate = model->physician;
    if (house->data.house.magistrate < magistrate) {
        ++demands->missing.magistrate;
        return E_HOUSE_NONE;
    }
    if (magistrate == 1) {
        ++demands->requiring.magistrate;
    }

    // health
    int health_need = model->health;
    if (house->data.house.health < health_need) {
        if (health_need < 2)
            ++demands->missing.dentist;
        else {
            ++demands->missing.physician;
        }
        return E_HOUSE_NONE;
    }
    if (health_need >= 1) {
        ++demands->requiring.physician;
    }

    // food types
    int foodtypes_required = model->food_types;
    int foodtypes_available = 0;
    for (int i = INVENTORY_MIN_FOOD; i < INVENTORY_MAX_FOOD; i++) {
        if (house->data.house.inventory[i])
            foodtypes_available++;
    }
    if (foodtypes_available < foodtypes_required) {
        ++demands->missing.food;
        return E_HOUSE_NONE;
    }
    // goods
    if (house->data.house.inventory[INVENTORY_GOOD1] < model->pottery)
        return E_HOUSE_NONE;

    if (house->data.house.inventory[INVENTORY_GOOD3] < model->linen_oil)
        return E_HOUSE_NONE;

    if (house->data.house.inventory[INVENTORY_GOOD2] < model->jewelry_furniture)
        return E_HOUSE_NONE;

    int wine = model->beer_wine;
    if (wine && house->data.house.inventory[INVENTORY_GOOD4] <= 0)
        return E_HOUSE_NONE;

    if (wine > 1 && !city_resource_multiple_wine_available()) {
        ++demands->missing.second_wine;
        return E_HOUSE_NONE;
    }
    return E_HOUSE_EVOLVE;
}

static e_house_progress check_requirements(building* house, house_demands* demands) {
    e_house_progress status = check_evolve_desirability(house);
    if (!has_required_goods_and_services(house, 0, demands)) { // check if it will devolve to previous step
        status = E_HOUSE_DECAY;
    } else if (status == E_HOUSE_EVOLVE) { // check if it can evolve to the next step
        status = has_required_goods_and_services(house, 1, demands);
    }

    return status;
}

static bool has_devolve_delay(building* house, int status) {
    if (status == E_HOUSE_DECAY && house->data.house.devolve_delay < 2) {
        house->data.house.devolve_delay++;
        return true;
    } else {
        house->data.house.devolve_delay = 0;
        return false;
    }
}

static bool evolve_crudy_hut(building* house, house_demands* demands) {
    if (house->house_population > 0) {
        building_house_merge(house);
        int status = check_requirements(house, demands);
        if (status == E_HOUSE_EVOLVE) {
            building_house_change_to(house, BUILDING_HOUSE_STURDY_HUT);
        }
    }

    return false;
}

static bool evolve_sturdy_hut(building* house, house_demands* demands) {
    if (house->house_population > 0) {
        building_house_merge(house);
        e_house_progress status = check_requirements(house, demands);
        if (!has_devolve_delay(house, status)) {
            if (status == E_HOUSE_EVOLVE)
                building_house_change_to(house, BUILDING_HOUSE_MEAGER_SHANTY);
            else if (status == E_HOUSE_DECAY)
                building_house_change_to(house, BUILDING_HOUSE_CRUDE_HUT);
        }
    }

    return false;
}

static bool evolve_meager_shanty(building* house, house_demands* demands) {
    building_house_merge(house);
    e_house_progress status = check_requirements(house, demands);
    if (!has_devolve_delay(house, status)) {
        if (status == E_HOUSE_EVOLVE)
            building_house_change_to(house, BUILDING_HOUSE_COMMON_SHANTY);
        else if (status == E_HOUSE_DECAY)
            building_house_change_to(house, BUILDING_HOUSE_STURDY_HUT);
    }
    return 0;
}

static bool evolve_common_shanty(building* house, house_demands* demands) {
    building_house_merge(house);
    e_house_progress status = check_requirements(house, demands);
    if (!has_devolve_delay(house, status)) {
        if (status == E_HOUSE_EVOLVE)
            building_house_change_to(house, BUILDING_HOUSE_ROUGH_COTTAGE);
        else if (status == E_HOUSE_DECAY)
            building_house_change_to(house, BUILDING_HOUSE_MEAGER_SHANTY);
    }
    return 0;
}

static bool evolve_small_hovel(building* house, house_demands* demands) {
    building_house_merge(house);
    e_house_progress status = check_requirements(house, demands);
    if (!has_devolve_delay(house, status)) {
        if (status == E_HOUSE_EVOLVE)
            building_house_change_to(house, BUILDING_HOUSE_ORDINARY_COTTAGE);
        else if (status == E_HOUSE_DECAY)
            building_house_change_to(house, BUILDING_HOUSE_COMMON_SHANTY);
    }
    return 0;
}

static bool evolve_large_hovel(building* house, house_demands* demands) {
    building_house_merge(house);
    e_house_progress status = check_requirements(house, demands);
    if (!has_devolve_delay(house, status)) {
        if (status == E_HOUSE_EVOLVE)
            building_house_change_to(house, BUILDING_HOUSE_MODEST_HOMESTEAD);
        else if (status == E_HOUSE_DECAY)
            building_house_change_to(house, BUILDING_HOUSE_ROUGH_COTTAGE);
    }
    return 0;
}

static bool evolve_small_casa(building* house, house_demands* demands) {
    building_house_merge(house);
    e_house_progress status = check_requirements(house, demands);
    if (!has_devolve_delay(house, status)) {
        if (status == E_HOUSE_EVOLVE)
            building_house_change_to(house, BUILDING_HOUSE_SPACIOUS_HOMESTEAD);
        else if (status == E_HOUSE_DECAY)
            building_house_change_to(house, BUILDING_HOUSE_ORDINARY_COTTAGE);
    }
    return 0;
}
static bool evolve_large_casa(building* house, house_demands* demands) {
    building_house_merge(house);
    e_house_progress status = check_requirements(house, demands);
    if (!has_devolve_delay(house, status)) {
        if (status == E_HOUSE_EVOLVE)
            building_house_change_to(house, BUILDING_HOUSE_MODEST_APARTMENT);
        else if (status == E_HOUSE_DECAY)
            building_house_change_to(house, BUILDING_HOUSE_MODEST_HOMESTEAD);
    }
    return 0;
}
static bool evolve_small_insula(building* house, house_demands* demands) {
    building_house_merge(house);
    e_house_progress status = check_requirements(house, demands);
    if (!has_devolve_delay(house, status)) {
        if (status == E_HOUSE_EVOLVE)
            building_house_change_to(house, BUILDING_HOUSE_SPACIOUS_APARTMENT);
        else if (status == E_HOUSE_DECAY)
            building_house_change_to(house, BUILDING_HOUSE_SPACIOUS_HOMESTEAD);
    }
    return 0;
}
static bool evolve_medium_insula(building* house, house_demands* demands) {
    building_house_merge(house);
    e_house_progress status = check_requirements(house, demands);
    if (!has_devolve_delay(house, status)) {
        if (status == E_HOUSE_EVOLVE) {
            if (building_house_can_expand(house, 4)) {
                house->house_is_merged = 0;
                building_house_expand_to_large_insula(house);
                map_tiles_update_all_gardens();
                return 1;
            }
        } else if (status == E_HOUSE_DECAY) {
            building_house_change_to(house, BUILDING_HOUSE_MODEST_APARTMENT);
        }
    }
    return 0;
}
static bool evolve_large_insula(building* house, house_demands* demands) {
    e_house_progress status = check_requirements(house, demands);
    if (!has_devolve_delay(house, status)) {
        if (status == E_HOUSE_EVOLVE)
            building_house_change_to(house, BUILDING_HOUSE_GRAND_INSULA);
        else if (status == E_HOUSE_DECAY)
            building_house_devolve_from_large_insula(house);
    }
    return 0;
}
static bool evolve_grand_insula(building* house, house_demands* demands) {
    e_house_progress status = check_requirements(house, demands);
    if (!has_devolve_delay(house, status)) {
        if (status == E_HOUSE_EVOLVE)
            building_house_change_to(house, BUILDING_HOUSE_SMALL_VILLA);
        else if (status == E_HOUSE_DECAY)
            building_house_change_to(house, BUILDING_HOUSE_LARGE_INSULA);
    }
    return 0;
}
static bool evolve_small_villa(building* house, house_demands* demands) {
    e_house_progress status = check_requirements(house, demands);
    if (!has_devolve_delay(house, status)) {
        if (status == E_HOUSE_EVOLVE)
            building_house_change_to(house, BUILDING_HOUSE_MEDIUM_VILLA);
        else if (status == E_HOUSE_DECAY)
            building_house_change_to(house, BUILDING_HOUSE_GRAND_INSULA);
    }
    return 0;
}
static bool evolve_medium_villa(building* house, house_demands* demands) {
    e_house_progress status = check_requirements(house, demands);
    if (!has_devolve_delay(house, status)) {
        if (status == E_HOUSE_EVOLVE) {
            if (building_house_can_expand(house, 9)) {
                building_house_expand_to_large_villa(house);
                map_tiles_update_all_gardens();
                return true;
            }
        } else if (status == E_HOUSE_DECAY)
            building_house_change_to(house, BUILDING_HOUSE_SMALL_VILLA);
    }
    return false;
}
static bool evolve_large_villa(building* house, house_demands* demands) {
    e_house_progress status = check_requirements(house, demands);
    if (!has_devolve_delay(house, status)) {
        if (status == E_HOUSE_EVOLVE)
            building_house_change_to(house, BUILDING_HOUSE_GRAND_VILLA);
        else if (status == E_HOUSE_DECAY)
            building_house_devolve_from_large_villa(house);
    }
    return 0;
}
static bool evolve_grand_villa(building* house, house_demands* demands) {
    e_house_progress status = check_requirements(house, demands);
    if (!has_devolve_delay(house, status)) {
        if (status == E_HOUSE_EVOLVE)
            building_house_change_to(house, BUILDING_HOUSE_SMALL_PALACE);
        else if (status == E_HOUSE_DECAY)
            building_house_change_to(house, BUILDING_HOUSE_LARGE_VILLA);
    }
    return 0;
}
static bool evolve_small_palace(building* house, house_demands* demands) {
    e_house_progress status = check_requirements(house, demands);
    if (!has_devolve_delay(house, status)) {
        if (status == E_HOUSE_EVOLVE)
            building_house_change_to(house, BUILDING_HOUSE_MEDIUM_PALACE);
        else if (status == E_HOUSE_DECAY)
            building_house_change_to(house, BUILDING_HOUSE_GRAND_VILLA);
    }
    return 0;
}
static bool evolve_medium_palace(building* house, house_demands* demands) {
    e_house_progress status = check_requirements(house, demands);
    if (!has_devolve_delay(house, status)) {
        if (status == E_HOUSE_EVOLVE) {
            if (building_house_can_expand(house, 16)) {
                building_house_expand_to_large_palace(house);
                map_tiles_update_all_gardens();
                return 1;
            }
        } else if (status == E_HOUSE_DECAY)
            building_house_change_to(house, BUILDING_HOUSE_SMALL_PALACE);
    }
    return 0;
}
static bool evolve_large_palace(building* house, house_demands* demands) {
    e_house_progress status = check_requirements(house, demands);
    if (!has_devolve_delay(house, status)) {
        if (status == E_HOUSE_EVOLVE)
            building_house_change_to(house, BUILDING_HOUSE_LUXURY_PALACE);
        else if (status == E_HOUSE_DECAY)
            building_house_devolve_from_large_palace(house);
    }
    return 0;
}
static bool evolve_luxury_palace(building* house, house_demands* demands) {
    e_house_progress status = check_evolve_desirability(house);
    if (!has_required_goods_and_services(house, 0, demands)) {
        status = E_HOUSE_DECAY;
    }

    if (!has_devolve_delay(house, status) && status == E_HOUSE_DECAY)
        building_house_change_to(house, BUILDING_HOUSE_LARGE_PALACE);

    return 0;
}

static void consume_resource(building& b, int inventory, int amount) {
    if (amount > 0) {
        if (amount > b.data.house.inventory[inventory])
            b.data.house.inventory[inventory] = 0;
        else {
            b.data.house.inventory[inventory] -= amount;
        }
    }
}

static void consume_resources(building &b) {
    const model_house* model = model_get_house(b.subtype.house_level);
    consume_resource(b, INVENTORY_GOOD1, model->pottery);
    consume_resource(b, INVENTORY_GOOD2, model->jewelry_furniture);
    consume_resource(b, INVENTORY_GOOD3, model->linen_oil);
    consume_resource(b, INVENTORY_GOOD4, model->beer_wine);
}

static bool (*evolve_callback[])(building*, house_demands*) = {
    evolve_crudy_hut,
    evolve_sturdy_hut,
    evolve_meager_shanty,
    evolve_common_shanty,
    evolve_small_hovel,
    evolve_large_hovel,
    evolve_small_casa,
    evolve_large_casa,
    evolve_small_insula,
    evolve_medium_insula,
    evolve_large_insula,
    evolve_grand_insula,
    evolve_small_villa,
    evolve_medium_villa,
    evolve_large_villa,
    evolve_grand_villa,
    evolve_small_palace,
    evolve_medium_palace,
    evolve_large_palace,
    evolve_luxury_palace
};

void building_house_process_evolve_and_consume_goods(void) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Process'n'Consume Goods");
    city_houses_reset_demands();
    house_demands* demands = city_houses_demands();
    bool has_expanded = false;
    buildings_house_do([&] (building &h) {
        building_house_check_for_corruption(&h);
        has_expanded |= evolve_callback[h.type - BUILDING_HOUSE_VACANT_LOT](&h, demands);

        if (game_time_day() == 0 || game_time_day() == 7) {
            consume_resources(h);
        }
    });

    if (has_expanded) {
        map_routing_update_land();
    }
}

void building_house_determine_evolve_text(building* house, int worst_desirability_building) {
    int level = house->subtype.house_level;

    // this house will devolve soon because...

    const model_house* model = model_get_house(level);
    // desirability
    if (house->desirability <= model->devolve_desirability) {
        house->data.house.evolve_text_id = 0;
        return;
    }
    // water
    int water = model->water;
    if (water == 1 && !house->has_water_access && !house->has_well_access) {
        house->data.house.evolve_text_id = 1;
        return;
    }
    if (water == 2 && (!house->has_water_access || !house->data.house.water_supply)) {
        house->data.house.evolve_text_id = 2;
        return;
    }
    // entertainment
    int entertainment = model->entertainment;
    if (house->data.house.entertainment < entertainment) {
        if (!house->data.house.entertainment)
            house->data.house.evolve_text_id = 3;
        else if (entertainment < 10)
            house->data.house.evolve_text_id = 4;
        else if (entertainment < 25)
            house->data.house.evolve_text_id = 5;
        else if (entertainment < 50)
            house->data.house.evolve_text_id = 6;
        else if (entertainment < 80)
            house->data.house.evolve_text_id = 7;
        else {
            house->data.house.evolve_text_id = 8;
        }
        return;
    }
    // food types
    int foodtypes_required = model->food;
    int foodtypes_available = 0;
    for (int i = INVENTORY_MIN_FOOD; i < INVENTORY_MAX_FOOD; i++) {
        if (house->data.house.inventory[i])
            foodtypes_available++;
    }
    if (foodtypes_available < foodtypes_required) {
        if (foodtypes_required == 1) {
            house->data.house.evolve_text_id = 9;
            return;
        } else if (foodtypes_required == 2) {
            house->data.house.evolve_text_id = 10;
            return;
        } else if (foodtypes_required == 3) {
            house->data.house.evolve_text_id = 11;
            return;
        }
    }
    // education
    int education = model->education;
    if (house->data.house.education < education) {
        if (education == 1) {
            house->data.house.evolve_text_id = 14;
            return;
        } else if (education == 2) {
            if (house->data.house.school) {
                house->data.house.evolve_text_id = 15;
                return;
            } else if (house->data.house.library) {
                house->data.house.evolve_text_id = 16;
                return;
            }
        } else if (education == 3) {
            house->data.house.evolve_text_id = 17;
            return;
        }
    }
    // magistrate
    if (house->data.house.magistrate < model->physician) {
        house->data.house.evolve_text_id = 18;
        return;
    }
    // pottery
    if (house->data.house.inventory[INVENTORY_GOOD1] < model->pottery) {
        house->data.house.evolve_text_id = 19;
        return;
    }
    // religion
    int religion = model->religion;
    if (house->data.house.num_gods < religion) {
        if (religion == 1) {
            house->data.house.evolve_text_id = 20;
            return;
        } else if (religion == 2) {
            house->data.house.evolve_text_id = 21;
            return;
        } else if (religion == 3) {
            house->data.house.evolve_text_id = 22;
            return;
        }
    }

    // mortuary
    if (house->data.house.dentist < model->dentist) {
        house->data.house.evolve_text_id = 23;
        return;
    }

    // health
    int health_need = model->health;
    if (house->data.house.health < health_need) {
        if (health_need == 1) {
            house->data.house.evolve_text_id = 24;
        } else if (house->data.house.mortuary) {
            house->data.house.evolve_text_id = 25;
        } else {
            house->data.house.evolve_text_id = 26;
        }
        return;
    }
    // oil
    if (house->data.house.inventory[INVENTORY_GOOD3] < model->linen_oil) {
        house->data.house.evolve_text_id = 27;
        return;
    }
    // furniture
    if (house->data.house.inventory[INVENTORY_GOOD2] < model->jewelry_furniture) {
        house->data.house.evolve_text_id = 28;
        return;
    }
    // wine
    int wine = model->beer_wine;
    if (house->data.house.inventory[INVENTORY_GOOD4] < wine) {
        house->data.house.evolve_text_id = 29;
        return;
    }
    if (wine > 1 && !city_resource_multiple_wine_available()) {
        house->data.house.evolve_text_id = 65;
        return;
    }
    if (level >= 19) { // max level!
        house->data.house.evolve_text_id = 60;
        return;
    }

    // this house will evolve if ...

    // desirability
    if (house->desirability < model->evolve_desirability) {
        if (worst_desirability_building)
            house->data.house.evolve_text_id = 62;
        else {
            house->data.house.evolve_text_id = 30;
        }
        return;
    }
    model = model_get_house(++level);
    // water
    water = model->water;
    if (water == 1 && !house->has_water_access && !house->has_well_access) {
        house->data.house.evolve_text_id = 31;
        return;
    }
    if (water == 2 && !house->has_water_access) {
        house->data.house.evolve_text_id = 32;
        return;
    }
    // entertainment
    entertainment = model->entertainment;
    if (house->data.house.entertainment < entertainment) {
        if (!house->data.house.entertainment)
            house->data.house.evolve_text_id = 33;
        else if (entertainment < 10)
            house->data.house.evolve_text_id = 34;
        else if (entertainment < 25)
            house->data.house.evolve_text_id = 35;
        else if (entertainment < 50)
            house->data.house.evolve_text_id = 36;
        else if (entertainment < 80)
            house->data.house.evolve_text_id = 37;
        else {
            house->data.house.evolve_text_id = 38;
        }
        return;
    }
    // food types
    foodtypes_required = model->food_types;
    if (foodtypes_available < foodtypes_required) {
        if (foodtypes_required == 1) {
            house->data.house.evolve_text_id = 39;
            return;
        } else if (foodtypes_required == 2) {
            house->data.house.evolve_text_id = 40;
            return;
        } else if (foodtypes_required == 3) {
            house->data.house.evolve_text_id = 41;
            return;
        }
    }
    // education
    education = model->education;
    if (house->data.house.education < education) {
        if (education == 1) {
            house->data.house.evolve_text_id = 44;
            return;
        } else if (education == 2) {
            if (house->data.house.school) {
                house->data.house.evolve_text_id = 45;
                return;
            } else if (house->data.house.library) {
                house->data.house.evolve_text_id = 46;
                return;
            }
        } else if (education == 3) {
            house->data.house.evolve_text_id = 47;
            return;
        }
    }
    // magistrate
    if (house->data.house.magistrate < model->physician) {
        house->data.house.evolve_text_id = 48;
        return;
    }
    // pottery
    if (house->data.house.inventory[INVENTORY_GOOD1] < model->pottery) {
        house->data.house.evolve_text_id = 49;
        return;
    }
    // religion
    religion = model->religion;
    if (house->data.house.num_gods < religion) {
        if (religion == 1) {
            house->data.house.evolve_text_id = 50;
            return;
        } else if (religion == 2) {
            house->data.house.evolve_text_id = 51;
            return;
        } else if (religion == 3) {
            house->data.house.evolve_text_id = 52;
            return;
        }
    }

    // dentist
    if (house->data.house.dentist < model->dentist) {
        house->data.house.evolve_text_id = 53;
        return;
    }

    // health
    int model_health_need = model->health;
    if (house->data.house.health < model_health_need) {
        if (model_health_need == 1)
            house->data.house.evolve_text_id = 54;
        else if (house->data.house.dentist)
            house->data.house.evolve_text_id = 55;
        else {
            house->data.house.evolve_text_id = 56;
        }
        return;
    }
    // oil
    if (house->data.house.inventory[INVENTORY_GOOD3] < model->linen_oil) {
        house->data.house.evolve_text_id = 57;
        return;
    }
    // furniture
    if (house->data.house.inventory[INVENTORY_GOOD2] < model->jewelry_furniture) {
        house->data.house.evolve_text_id = 58;
        return;
    }
    // wine
    wine = model->beer_wine;
    if (house->data.house.inventory[INVENTORY_GOOD4] < wine) {
        house->data.house.evolve_text_id = 59;
        return;
    }
    if (wine > 1 && !city_resource_multiple_wine_available()) {
        house->data.house.evolve_text_id = 66;
        return;
    }
    // house is evolving
    house->data.house.evolve_text_id = 61;
    if (house->data.house.no_space_to_expand == 1) {
        // house would like to evolve but can't
        house->data.house.evolve_text_id = 64;
    }
}

int building_house_determine_worst_desirability_building(building* house) {
    int lowest_desirability = 0;
    int lowest_building_id = 0;
    int x_min, y_min, x_max, y_max;
    map_grid_get_area(house->tile, 1, 6, &x_min, &y_min, &x_max, &y_max);

    for (int y = y_min; y <= y_max; y++) {
        for (int x = x_min; x <= x_max; x++) {
            int building_id = map_building_at(MAP_OFFSET(x, y));
            if (building_id <= 0)
                continue;

            building* b = building_get(building_id);
            if (b->state != BUILDING_STATE_VALID || building_id == house->id)
                continue;

            if (!b->house_size || b->type < house->type) {
                int des = model_get_building(b->type)->desirability_value;
                if (des < 0) {
                    // simplified desirability calculation
                    int step_size = model_get_building(b->type)->desirability_step_size;
                    int range = model_get_building(b->type)->desirability_range;
                    int dist = calc_maximum_distance(vec2i(x, y), house->tile);
                    if (dist <= range) {
                        while (--dist > 1) {
                            des += step_size;
                        }
                        if (des < lowest_desirability) {
                            lowest_desirability = des;
                            lowest_building_id = building_id;
                        }
                    }
                }
            }
        }
    }
    return lowest_building_id;
}

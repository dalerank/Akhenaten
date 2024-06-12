#include "house_evolution.h"

#include "building/building_house.h"
#include "building/model.h"
#include "city/houses.h"
#include "city/city.h"
#include "city/resource.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "game/resource.h"
#include "game/time.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "grid/routing/routing_terrain.h"
#include "grid/tiles.h"

static bool evolve_crudy_hut(building* b, house_demands* demands) {
    building_house *house = b->dcast_house();
    if (house->house_population() > 0) {
        house->merge();
        int status = house->check_requirements(demands);
        if (status == e_house_evolve) {
            house->change_to(BUILDING_HOUSE_STURDY_HUT);
        }
    }

    return false;
}

static bool evolve_sturdy_hut(building* b, house_demands* demands) {
    building_house *house = b->dcast_house();
    if (house->house_population() > 0) {
        house->merge();
        e_house_progress status = house->check_requirements(demands);
        if (!house->has_devolve_delay(status)) {
            if (status == e_house_evolve)
                house->change_to(BUILDING_HOUSE_MEAGER_SHANTY);
            else if (status == e_house_decay)
                house->change_to(BUILDING_HOUSE_CRUDE_HUT);
        }
    }

    return false;
}

static bool evolve_meager_shanty(building* b, house_demands* demands) {
    building_house *house = b->dcast_house();
    house->merge();
    e_house_progress status = house->check_requirements(demands);
    if (!house->has_devolve_delay(status)) {
        if (status == e_house_evolve)
            house->change_to(BUILDING_HOUSE_COMMON_SHANTY);
        else if (status == e_house_decay)
            house->change_to(BUILDING_HOUSE_STURDY_HUT);
    }
    return 0;
}

static bool evolve_common_shanty(building* b, house_demands* demands) {
    building_house *house = b->dcast_house();
    house->merge();
    e_house_progress status = house->check_requirements(demands);
    if (!house->has_devolve_delay(status)) {
        if (status == e_house_evolve)
            house->change_to(BUILDING_HOUSE_ROUGH_COTTAGE);
        else if (status == e_house_decay)
            house->change_to(BUILDING_HOUSE_MEAGER_SHANTY);
    }
    return 0;
}

static bool evolve_small_hovel(building* b, house_demands* demands) {
    building_house *house = b->dcast_house();
    house->merge();
    e_house_progress status = house->check_requirements(demands);
    if (!house->has_devolve_delay(status)) {
        if (status == e_house_evolve)
            house->change_to(BUILDING_HOUSE_ORDINARY_COTTAGE);
        else if (status == e_house_decay)
            house->change_to(BUILDING_HOUSE_COMMON_SHANTY);
    }
    return 0;
}

static bool evolve_large_hovel(building* b, house_demands* demands) {
    building_house *house = b->dcast_house();
    house->merge();
    e_house_progress status = house->check_requirements(demands);
    if (!house->has_devolve_delay(status)) {
        if (status == e_house_evolve)
            house->change_to(BUILDING_HOUSE_MODEST_HOMESTEAD);
        else if (status == e_house_decay)
            house->change_to(BUILDING_HOUSE_ROUGH_COTTAGE);
    }
    return 0;
}

static bool evolve_small_casa(building* b, house_demands* demands) {
    building_house *house = b->dcast_house();
    house->merge();
    e_house_progress status = house->check_requirements(demands);
    if (!house->has_devolve_delay(status)) {
        if (status == e_house_evolve)
            house->change_to(BUILDING_HOUSE_SPACIOUS_HOMESTEAD);
        else if (status == e_house_decay)
            house->change_to(BUILDING_HOUSE_ORDINARY_COTTAGE);
    }
    return 0;
}
static bool evolve_large_casa(building* b, house_demands* demands) {
    building_house *house = b->dcast_house();
    house->merge();
    e_house_progress status = house->check_requirements(demands);
    if (!house->has_devolve_delay(status)) {
        if (status == e_house_evolve)
            house->change_to(BUILDING_HOUSE_MODEST_APARTMENT);
        else if (status == e_house_decay)
            house->change_to(BUILDING_HOUSE_MODEST_HOMESTEAD);
    }
    return 0;
}

static bool evolve_small_insula(building* b, house_demands* demands) {
    building_house *house = b->dcast_house();
    house->merge();
    e_house_progress status = house->check_requirements(demands);
    if (!house->has_devolve_delay(status)) {
        if (status == e_house_evolve)
            house->change_to(BUILDING_HOUSE_SPACIOUS_APARTMENT);
        else if (status == e_house_decay)
            house->change_to(BUILDING_HOUSE_SPACIOUS_HOMESTEAD);
    }
    return 0;
}

static bool evolve_medium_insula(building* b, house_demands* demands) {
    building_house *house = b->dcast_house();
    house->merge();
    e_house_progress status = house->check_requirements(demands);
    if (!house->has_devolve_delay(status)) {
        if (status == e_house_evolve) {
            if (house->building_house_can_expand(4)) {
                house->base.house_is_merged = 0;
                building_house_expand_to_large_insula(b);
                map_tiles_update_all_gardens();
                return 1;
            }
        } else if (status == e_house_decay) {
            house->change_to(BUILDING_HOUSE_MODEST_APARTMENT);
        }
    }
    return 0;
}

static bool evolve_large_insula(building* b, house_demands* demands) {
    building_house *house = b->dcast_house();
    e_house_progress status = house->check_requirements(demands);
    if (!house->has_devolve_delay(status)) {
        if (status == e_house_evolve) {
            house->change_to(BUILDING_HOUSE_SPACIOUS_RESIDENCE);
        } else if (status == e_house_decay) {
            building_house_devolve_from_large_insula(b);
        }
    }
    return 0;
}

static bool evolve_grand_insula(building* b, house_demands* demands) {
    building_house *house = b->dcast_house();
    e_house_progress status = house->check_requirements(demands);
    if (!house->has_devolve_delay(status)) {
        if (status == e_house_evolve)
            house->change_to(BUILDING_HOUSE_ELEGANT_RESIDENCE);
        else if (status == e_house_decay)
            house->change_to(BUILDING_HOUSE_COMMON_RESIDENCE);
    }
    return 0;
}

static bool evolve_small_villa(building* b, house_demands* demands) {
    building_house *house = b->dcast_house();
    e_house_progress status = house->check_requirements(demands);
    if (!house->has_devolve_delay(status)) {
        if (status == e_house_evolve)
            house->change_to(BUILDING_HOUSE_FANCY_RESIDENCE);
        else if (status == e_house_decay)
            house->change_to(BUILDING_HOUSE_SPACIOUS_RESIDENCE);
    }
    return 0;
}

static bool evolve_medium_villa(building* b, house_demands* demands) {
    building_house *house = b->dcast_house();
    e_house_progress status = house->check_requirements(demands);
    if (!house->has_devolve_delay(status)) {
        if (status == e_house_evolve) {
            if (house->building_house_can_expand(9)) {
                building_house_expand_to_large_villa(b);
                map_tiles_update_all_gardens();
                return true;
            }
        } else if (status == e_house_decay) {
            house->change_to(BUILDING_HOUSE_ELEGANT_RESIDENCE);
        }
    }
    return false;
}

static bool evolve_large_villa(building* b, house_demands* demands) {
    building_house *house = b->dcast_house();
    e_house_progress status = house->check_requirements(demands);
    if (!house->has_devolve_delay(status)) {
        if (status == e_house_evolve) {
            house->change_to(BUILDING_HOUSE_GRAND_VILLA);
        } else if (status == e_house_decay) {
            building_house_devolve_from_large_villa(b);
        }
    }
    return 0;
}

static bool evolve_grand_villa(building* b, house_demands* demands) {
    building_house *house = b->dcast_house();
    e_house_progress status = house->check_requirements(demands);
    if (!house->has_devolve_delay(status)) {
        if (status == e_house_evolve)
            house->change_to(BUILDING_HOUSE_SMALL_PALACE);
        else if (status == e_house_decay)
            house->change_to(BUILDING_HOUSE_COMMON_MANOR);
    }
    return 0;
}

static bool evolve_small_palace(building* b, house_demands* demands) {
    building_house *house = b->dcast_house();
    e_house_progress status = house->check_requirements(demands);
    if (!house->has_devolve_delay(status)) {
        if (status == e_house_evolve)
            house->change_to(BUILDING_HOUSE_MEDIUM_PALACE);
        else if (status == e_house_decay)
            house->change_to(BUILDING_HOUSE_GRAND_VILLA);
    }
    return 0;
}
static bool evolve_medium_palace(building* b, house_demands* demands) {
    building_house *house = b->dcast_house();
    e_house_progress status = house->check_requirements(demands);
    if (!house->has_devolve_delay(status)) {
        if (status == e_house_evolve) {
            if (house->building_house_can_expand(16)) {
                building_house_expand_to_large_palace(b);
                map_tiles_update_all_gardens();
                return 1;
            }
        } else if (status == e_house_decay) {
            house->change_to(BUILDING_HOUSE_SMALL_PALACE);
        }
    }
    return 0;
}
static bool evolve_large_palace(building* b, house_demands* demands) {
    building_house *house = b->dcast_house();
    e_house_progress status = house->check_requirements(demands);
    if (!house->has_devolve_delay(status)) {
        if (status == e_house_evolve)
            house->change_to(BUILDING_HOUSE_LUXURY_PALACE);
        else if (status == e_house_decay)
            building_house_devolve_from_large_palace(b);
    }
    return 0;
}
static bool evolve_luxury_palace(building* b, house_demands* demands) {
    building_house *house = b->dcast_house();
    e_house_progress status = house->check_evolve_desirability();
    if (!house->has_required_goods_and_services(0, demands)) {
        status = e_house_decay;
    }

    if (!house->has_devolve_delay(status) && status == e_house_decay)
        house->change_to(BUILDING_HOUSE_LARGE_PALACE);

    return 0;
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
    g_city.houses_reset_demands();
    house_demands &demands = g_city.houses;
    bool has_expanded = false;
    buildings_house_do([&] (building &h) {
        building_house_check_for_corruption(&h);
        has_expanded |= evolve_callback[h.type - BUILDING_HOUSE_VACANT_LOT](&h, &demands);

        building_house *house = h.dcast_house();
        if (game_time_day() == 0 || game_time_day() == 7) {
            house->consume_resources();
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
    grid_area area = map_grid_get_area(house->tile, 1, 6);

    for (int y = area.tmin.y(), endy = area.tmax.y(); y <= endy; y++) {
        for (int x = area.tmin.x(), endx = area.tmax.x(); x <= endx; x++) {
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

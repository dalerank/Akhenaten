#include "building/building_house.h"
#include "building/model.h"
#include "city/houses.h"
#include "city/city.h"
#include "city/city_resource.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "game/resource.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "grid/routing/routing_terrain.h"
#include "grid/tiles.h"

void building_house::determine_evolve_text() {
    int level = house_level();
    auto& housed = runtime_data();

    // this house will devolve soon because...

    const model_house& model = model_get_house(level);
    // desirability
    if (base.desirability <= model.devolve_desirability) {
        housed.evolve_text_id = 0;
        return;
    }
    // water
    int water = model.water;
    if (water == 1 && !base.has_water_access && !base.has_well_access) {
        housed.evolve_text_id = 1;
        return;
    }
    if (water == 2 && (!base.has_water_access || !housed.water_supply)) {
        housed.evolve_text_id = 2;
        return;
    }
    // entertainment
    int entertainment = model.entertainment;
    if (housed.entertainment < entertainment) {
        if (!housed.entertainment)
            housed.evolve_text_id = 3;
        else if (entertainment < 10)
            housed.evolve_text_id = 4;
        else if (entertainment < 25)
            housed.evolve_text_id = 5;
        else if (entertainment < 50)
            housed.evolve_text_id = 6;
        else if (entertainment < 80)
            housed.evolve_text_id = 7;
        else {
            housed.evolve_text_id = 8;
        }
        return;
    }
    // food types
    int foodtypes_required = model.food;
    int foodtypes_available = 0;
    for (int i = INVENTORY_MIN_FOOD; i < INVENTORY_MAX_FOOD; i++) {
        if (housed.foods[i])
            foodtypes_available++;
    }
    if (foodtypes_available < foodtypes_required) {
        if (foodtypes_required == 1) {
            housed.evolve_text_id = 9;
            return;
        } else if (foodtypes_required == 2) {
            housed.evolve_text_id = 10;
            return;
        } else if (foodtypes_required == 3) {
            housed.evolve_text_id = 11;
            return;
        }
    }
    // education
    int education = model.education;
    if (housed.education < education) {
        if (education == 1) {
            housed.evolve_text_id = 14;
            return;
        } else if (education == 2) {
            if (housed.school) {
                housed.evolve_text_id = 15;
                return;
            } else if (housed.library) {
                housed.evolve_text_id = 16;
                return;
            }
        } else if (education == 3) {
            housed.evolve_text_id = 17;
            return;
        }
    }
    // magistrate
    if (housed.magistrate < model.physician) {
        housed.evolve_text_id = 18;
        return;
    }

    // pottery
    if (housed.inventory[INVENTORY_GOOD1] < model.pottery) {
        housed.evolve_text_id = 19;
        return;
    }
    // religion
    int religion = model.religion;
    if (housed.num_gods < religion) {
        if (religion == 1) {
            housed.evolve_text_id = 20;
            return;
        } else if (religion == 2) {
            housed.evolve_text_id = 21;
            return;
        } else if (religion == 3) {
            housed.evolve_text_id = 22;
            return;
        }
    }

    // mortuary
    if (housed.dentist < model.dentist) {
        housed.evolve_text_id = 23;
        return;
    }

    // health
    int health_need = model.health;
    if (housed.health < health_need) {
        if (health_need == 1) {
            housed.evolve_text_id = 24;
        } else if (housed.mortuary) {
            housed.evolve_text_id = 25;
        } else {
            housed.evolve_text_id = 26;
        }
        return;
    }
    // linen
    if (housed.inventory[INVENTORY_GOOD3] < model.linen) {
        housed.evolve_text_id = 27;
        return;
    }
    // jewelry
    if (housed.inventory[INVENTORY_GOOD2] < model.jewelry) {
        housed.evolve_text_id = 28;
        return;
    }
    // beer
    int beer = model.beer;
    if (housed.inventory[INVENTORY_GOOD4] < beer) {
        housed.evolve_text_id = 29;
        return;
    }
    if (beer > 1 && !city_resource_multiple_wine_available()) {
        housed.evolve_text_id = 65;
        return;
    }
    if (level >= 19) { // max level!
        housed.evolve_text_id = 60;
        return;
    }

    // this house will evolve if ...

    // desirability
    if (base.desirability < model.evolve_desirability) {
        if (housed.worst_desirability_building_id) {
            housed.evolve_text_id = 62;
        } else {
            housed.evolve_text_id = 30;
        }
        return;
    }

    const auto& next_model = model_get_house(++level);
    // water
    water = next_model.water;
    if (water == 1 && !base.has_water_access && !base.has_well_access) {
        housed.evolve_text_id = 31;
        return;
    }
    if (water == 2 && !base.has_water_access) {
        housed.evolve_text_id = 32;
        return;
    }
    // entertainment
    entertainment = next_model.entertainment;
    if (housed.entertainment < entertainment) {
        if (!housed.entertainment)
            housed.evolve_text_id = 33;
        else if (entertainment < 10)
            housed.evolve_text_id = 34;
        else if (entertainment < 25)
            housed.evolve_text_id = 35;
        else if (entertainment < 50)
            housed.evolve_text_id = 36;
        else if (entertainment < 80)
            housed.evolve_text_id = 37;
        else {
            housed.evolve_text_id = 38;
        }
        return;
    }
    // food types
    foodtypes_required = next_model.food_types;
    if (foodtypes_available < foodtypes_required) {
        if (foodtypes_required == 1) {
            housed.evolve_text_id = 39;
            return;
        } else if (foodtypes_required == 2) {
            housed.evolve_text_id = 40;
            return;
        } else if (foodtypes_required == 3) {
            housed.evolve_text_id = 41;
            return;
        }
    }
    // education
    education = next_model.education;
    if (housed.education < education) {
        if (education == 1) {
            housed.evolve_text_id = 44;
            return;
        } else if (education == 2) {
            if (housed.school) {
                housed.evolve_text_id = 45;
                return;
            } else if (housed.library) {
                housed.evolve_text_id = 46;
                return;
            }
        } else if (education == 3) {
            housed.evolve_text_id = 47;
            return;
        }
    }
    // magistrate
    if (housed.magistrate < next_model.physician) {
        housed.evolve_text_id = 48;
        return;
    }
    // pottery
    if (housed.inventory[INVENTORY_GOOD1] < next_model.pottery) {
        housed.evolve_text_id = 49;
        return;
    }
    // religion
    religion = next_model.religion;
    if (housed.num_gods < religion) {
        if (religion == 1) {
            housed.evolve_text_id = 50;
            return;
        } else if (religion == 2) {
            housed.evolve_text_id = 51;
            return;
        } else if (religion == 3) {
            housed.evolve_text_id = 52;
            return;
        }
    }

    // dentist
    if (housed.dentist < next_model.dentist) {
        housed.evolve_text_id = 53;
        return;
    }

    // health
    int model_health_need = next_model.health;
    if (housed.health < model_health_need) {
        if (model_health_need == 1)
            housed.evolve_text_id = 54;
        else if (housed.dentist)
            housed.evolve_text_id = 55;
        else {
            housed.evolve_text_id = 56;
        }
        return;
    }
    // linen
    if (housed.inventory[INVENTORY_GOOD3] < next_model.linen) {
        housed.evolve_text_id = 57;
        return;
    }
    // jewelry
    if (housed.inventory[INVENTORY_GOOD2] < next_model.jewelry) {
        housed.evolve_text_id = 58;
        return;
    }
    // wine
    beer = next_model.beer;
    if (housed.inventory[INVENTORY_GOOD4] < beer) {
        housed.evolve_text_id = 59;
        return;
    }
    if (beer > 1 && !city_resource_multiple_wine_available()) {
        housed.evolve_text_id = 66;
        return;
    }
    // house is evolving
    housed.evolve_text_id = 61;
    if (housed.no_space_to_expand == 1) {
        // house would like to evolve but can't
        housed.evolve_text_id = 64;
    }
}

void building_house::determine_worst_desirability_building() {
    auto &housed = runtime_data();
    housed.worst_desirability_building_id = 0;

    grid_area area = map_grid_get_area(tile(), 1, 6);

    if (!house_level()) {
        return;
    }

    int lowest_desirability = 0;
    int lowest_building_id = 0;

    for (int y = area.tmin.y(), endy = area.tmax.y(); y <= endy; y++) {
        for (int x = area.tmin.x(), endx = area.tmax.x(); x <= endx; x++) {
            int building_id = map_building_at(tile2i(x, y));
            if (building_id <= 0)
                continue;

            auto b = building_get(building_id);
            if (!b->is_valid() || building_id == id()) {
                continue;
            }

            int des = model_get_building(b->type)->desirability_value;
            if (des >= 0) {
                continue;
            }

            // simplified desirability calculation
            int step_size = model_get_building(b->type)->desirability_step_size;
            int range = model_get_building(b->type)->desirability_range;
            int dist = calc_maximum_distance(vec2i(x, y), tile());
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

    housed.worst_desirability_building_id = lowest_building_id;
}

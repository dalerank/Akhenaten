#include "building/building_house.h"

#include "building/building_house_model.h"
#include "city/city.h"
#include "city/city_resource.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "game/resource.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "grid/routing/routing_terrain.h"
#include "grid/tiles.h"

#include <numeric>

void building_house::determine_evolve_text() {
    int level = house_level();
    auto& housed = runtime_data();

    // this house will devolve soon because...

    const model_house& model = get_model(level);
    housed.evolve_text = "";
    // desirability
    if (base.current_desirability <= model.devolve_desirability) {
        housed.evolve_text = "#house_low_desirabilty";
        return;
    }

    // water
    int water = model.water;
    if (water == 1 && !base.has_water_access && !base.has_well_access) {
        housed.evolve_text = "#lacks_access_primitive_water";
        return;
    }

    if (water == 2 && (!base.has_water_access || !housed.water_supply)) {
        housed.evolve_text = "#not_visited_by_water_carrier";
        return;
    }

    // entertainment
    int entertainment = model.entertainment;
    if (housed.entertainment < entertainment) {
        if (!housed.entertainment) housed.evolve_text = "#no_entertainment_to_be_found";
        else if (entertainment < 10) housed.evolve_text = "#any_entertainment_in_location";
        else if (entertainment < 25) housed.evolve_text = "#too_little_entertainment_in_location";
        else if (entertainment < 50) housed.evolve_text = "#some_entertainment_found_location";
        else if (entertainment < 80) housed.evolve_text = "#good_entertainment_found_location";
        else                       { housed.evolve_text = "#excellent_entertainment_found_location"; }
        return;
    }
    // food types
    int foodtypes_required = model.food_types;
    const int foodtypes_available = std::accumulate(std::begin(housed.foods), std::end(housed.foods), 0, 
                                                    [] (short r, short it) { return r + ((it > 0) ? 1 : 0); });
    constexpr pcstr foodtype_text[] = { "empty", "#one_food_type_need", "#two_food_types_need", "#three_food_types_need" };
    if (foodtypes_available < foodtypes_required) {
        housed.evolve_text = foodtype_text[foodtypes_required];
        return;
    }

    // bazaar access is only required for houses that need food or goods
    // (houses with food_types > 0 or any goods requirement)
    bool needs_bazaar = (model.food_types + model.pottery + model.linen + model.jewelry + model.beer > 0);
    if (needs_bazaar && !housed.bazaar_access) {
        housed.evolve_text = "#no_bazaar_access";
        return;
    }

    // education
    int education = model.education;
    if (housed.education < education) {
        if (education == 1) {
            housed.evolve_text = "#lost_basic_educational_facilities";
            return;
        } else if (education == 2) {
            if (housed.school) {
                housed.evolve_text = "#lost_access_to_scribal_school";
                return;
            } else if (housed.library) {
                housed.evolve_text = "#lost_access_to_library";
                return;
            }
        } else if (education == 3) {
            housed.evolve_text = "#lost_access_to_higher_education";
            return;
        }
    }

    // magistrate
    if (housed.magistrate < model.physician) {
        housed.evolve_text = "#no_access_to_magistrates";
        return;
    }

    // pottery
    if (housed.inventory[INVENTORY_GOOD1] < model.pottery) {
        housed.evolve_text = "#run_out_of_pottery";
        return;
    }

    // religion
    int religion = model.religion;
    if (housed.num_gods < religion) {
        if (religion == 1) {
            housed.evolve_text = "#lost_all_access_to_local_religious";
            return;
        } else if (religion == 2) {
            housed.evolve_text = "#access_to_one_local_religious";
            return;
        } else if (religion == 3) {
            housed.evolve_text = "#access_to_two_local_religious";
            return;
        }
    }

    // dentist
    if (housed.dentist < model.dentist) {
        housed.evolve_text = "#lost_dentist_access";
        return;
    }

    // health
    int health_need = model.health;
    if (housed.health < health_need) {
        if (health_need == 1) {
            housed.evolve_text = "#no_access_to_physician";
        } else if (housed.mortuary) {
            housed.evolve_text = "#no_access_to_mortuary";
        } else {
            housed.evolve_text = "#hard_access_to_physician";
        }
        return;
    }

    // linen
    if (housed.inventory[INVENTORY_GOOD3] < model.linen) {
        housed.evolve_text = "#run_out_of_linen";
        return;
    }

    // beer
    if (housed.inventory[INVENTORY_GOOD4] < model.beer) {
        housed.evolve_text = "#run_out_of_beer";
        return;
    }

    // jewelry
    if (housed.inventory[INVENTORY_GOOD2] < model.jewelry) {
        housed.evolve_text = "#run_out_of_jewelry";;
        return;
    }

    //if (beer > 1 && !city_resource_multiple_wine_available()) {
    //    housed.evolve_text_id = 65;
    //    return;
    //}

    if (level >= 19) { // max level!
        housed.evolve_text = "#dwellers_palace_are_pinnacle";
        return;
    }

    // this house will evolve if ...

    // desirability
    if (base.current_desirability < model.evolve_desirability) {
        if (housed.worst_desirability_building_id) {
            housed.evolve_text = "";
        } else {
            housed.evolve_text = "#cannot_evolve_cause_low_desirability";
        }
        return;
    }

    const auto& next_model = get_model(++level);
    // water
    water = next_model.water;
    if (water == 1 && !base.has_water_access && !base.has_well_access) {
        housed.evolve_text = "#cannot_evolve_most_primitive_water_source";
        return;
    }

    if (water == 2 && !base.has_water_access) {
        housed.evolve_text = "#cannot_evolve_access_to_water_carrier";
        return;
    }

    // entertainment
    entertainment = next_model.entertainment;
    if (housed.entertainment < entertainment) {
        if (!housed.entertainment)
            housed.evolve_text = "#cannot_evolve_no_entertainment";
        else if (entertainment < 10)
            housed.evolve_text = "#cannot_evolve_hardly_any_entertainment";
        else if (entertainment < 25)
            housed.evolve_text = "#cannot_evolve_too_little_entertainment";
        else if (entertainment < 50)
            housed.evolve_text = "#cannot_evolve_some_entertainment";
        else if (entertainment < 80)
            housed.evolve_text = "#cannot_evolve_good_entertainment";
        else {
            housed.evolve_text = "#cannot_evolve_excellent_entertainment";
        }
        return;
    }

    // food types
    foodtypes_required = next_model.food_types;
    if (foodtypes_available < foodtypes_required) {
        if (foodtypes_required == 1) {
            housed.evolve_text = "#cannot_evolve_needs_supply_food";
            return;
        } else if (foodtypes_required == 2) {
            housed.evolve_text = "#cannot_evolve_needs_second_type_food";
            return;
        } else if (foodtypes_required == 3) {
            housed.evolve_text = "#cannot_evolve_needs_third_type_food";
            return;
        }
    }

    if (next_model.fancy_bazaar && (housed.fancy_bazaar_access <= 0)) {
        housed.evolve_text = "#cannot_evolve_needs_access_bazaar";
        return;
    }

    // education
    education = next_model.education;
    if (housed.education < education) {
        if (education == 1) {
            housed.evolve_text = "#cannot_evolve_needs_basic_education";
            return;
        } else if (education == 2) {
            if (housed.school) {
                housed.evolve_text = "#cannot_evolve_needs_school_education";
                return;
            } else if (housed.library) {
                housed.evolve_text = "#cannot_evolve_needs_library_education";
                return;
            }
        } 
        
        //if (education == 3) {
        //    housed.evolve_text_id = 47;
        //    return;
        //}
    }

    // magistrate
    if (housed.magistrate < next_model.physician) {
        housed.evolve_text = "#cannot_evolve_needs_magistrate";
        return;
    }

    // pottery
    if (housed.inventory[INVENTORY_GOOD1] < next_model.pottery) {
        housed.evolve_text = "#cannot_evolve_needs_pottery";
        return;
    }

    // religion
    religion = next_model.religion;
    if (housed.num_gods < religion) {
        if (religion == 1) {
            housed.evolve_text = "#cannot_evolve_needs_religious";
            return;
        } else if (religion == 2) {
            housed.evolve_text = "#cannot_evolve_needs_religious_two_gods";
            return;
        } else if (religion == 3) {
            housed.evolve_text = "#cannot_evolve_needs_religious_three_gods";
            return;
        }
    }

    // dentist
    if (housed.dentist < next_model.dentist) {
        housed.evolve_text = "#cannot_evolve_needs_dentist";
        return;
    }

    // health
    int model_health_need = next_model.health;
    if (housed.health < model_health_need) {
        if (model_health_need == 1) {
            housed.evolve_text = "#cannot_evolve_needs_physician";
        } else if (housed.dentist) {
            housed.evolve_text = "#cannot_evolve_needs_mortuary_has_physician";
        } else {
            housed.evolve_text = "#cannot_evolve_needs_physician_mortuary_has";
        }
        return;
    }

    // linen
    if (housed.inventory[INVENTORY_GOOD3] < next_model.linen) {
        housed.evolve_text = "#cannot_evolve_needs_linen";
        return;
    }

    // jewelry
    if (housed.inventory[INVENTORY_GOOD2] < next_model.jewelry) {
        housed.evolve_text = "#cannot_evolve_needs_jewlery";
        return;
    }

    // beer
    if (housed.inventory[INVENTORY_GOOD4] < next_model.beer) {
        housed.evolve_text = "#cannot_evolve_needs_beer";
        return;
    }

    //if (beer > 1 && !city_resource_multiple_wine_available()) {
    //    housed.evolve_text_id = 66;
    //    return;
    //}
    // house is evolving

    housed.evolve_text = "#house_upgrade_inprogress";
    if (housed.no_space_to_expand == 1) {
        // house would like to evolve but can't
        housed.evolve_text = "#house_upgrade_nospace";
    }
}

void building_house::determine_worst_desirability_building() {
    auto &housed = runtime_data();
    housed.worst_desirability_building_id = 0;

    grid_area area = map_grid_get_area(tile(), 1, 6);

    const e_house_level my_level = house_level();
    if (!my_level) {
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

            int8_t des = b->des_influence.value;
            if (des >= 0) {
                continue;
            }

            auto other_house = b->dcast_house();
            if (other_house && other_house->house_level() >= my_level) {
                continue;
            }

            // simplified desirability calculation
            int step_size = b->des_influence.step_size;
            int range = b->des_influence.range;
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

#include "industry.h"

#include "building/building_type.h"
#include "city/resource.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "game/resource.h"
#include "graphics/image.h"
#include "grid/building_tiles.h"
#include "grid/road_access.h"
#include "scenario/property.h"
#include "window/city.h"
#include "graphics/image_groups.h"
#include "grid/terrain.h"
#include "config/config.h"
#include "city/data_private.h"
#include "city/floods.h"
#include "game/time.h"
#include "grid/floodplain.h"
#include "grid/grid.h"

#include <cmath>

#define MAX_PROGRESS_RAW 200
#define MAX_PROGRESS_WORKSHOP 400
#define MAX_PROGRESS_FARM_PH 2000
#define INFINITE 10000

static int max_progress(building &b) {
    if (building_is_farm(b.type)) {
        return MAX_PROGRESS_FARM_PH;
    }

    return building_is_workshop(b.type) ? MAX_PROGRESS_WORKSHOP : MAX_PROGRESS_RAW;
}

static void update_farm_image(building &b) {
    bool is_flooded = false;
    if (building_is_floodplain_farm(b)) {
        for (int _y = b.tile.y(); _y < b.tile.y() + b.size; _y++) {
            for (int _x = b.tile.x(); _x < b.tile.x() + b.size; _x++) {
                if (map_terrain_is(MAP_OFFSET(_x, _y), TERRAIN_WATER))
                    is_flooded = true;
            }
        }
    }

    if (!is_flooded) {
        map_building_tiles_add_farm(b.id, b.tile.x(), b.tile.y(), image_id_from_group(GROUP_BUILDING_FARMLAND) + 5 * (b.output_resource_first_id - 1), b.data.industry.progress);
    }
}

building* building_determine_worker_needed() {
    for (building *it = building_begin(), *end = building_end(); it != end; ++it) {
        if (it->state != BUILDING_STATE_VALID) {
            continue;
        }

        if (floodplains_is(FLOOD_STATE_FARMABLE) && building_is_floodplain_farm(*it)) {
            if (!it->data.industry.worker_id && it->data.industry.labor_days_left <= 47 && !it->num_workers) {
                return it;
            }
        } else if (building_is_monument(it->type)) {
            // todo
        }
    }

    return nullptr;
}

static const float produce_uptick_per_day = 103.5f * 20.0f / 128.0f / 100.0f; // don't ask

float get_farm_produce_uptick_per_day(building &b) {
    return produce_uptick_per_day;
}

float get_produce_uptick_per_day(building &b) {
    switch (b.type) {
    case BUILDING_GOLD_MINE:
        if (config_get(CONFIG_GP_CH_GOLDMINE_TWICE_PRODUCTION)) {
            return b.num_workers / 5.f;
        } else {
            return b.num_workers / 10.f;
        }
        break;

    case BUILDING_STONE_QUARRY:
        return b.num_workers / 2.f;
        break;

    default:
        break;
    }

    return b.num_workers;
}

// void building_bless_farms(void) {
//     for (int i = 1; i < MAX_BUILDINGS; i++) {
//         building *b = building_get(i);
//         if (b->state == BUILDING_STATE_VALID && b->output_resource_id && building_is_farm(b->type)) {
//             b->data.industry.progress = MAX_PROGRESS_RAW;
//             b->data.industry.curse_days_left = 0;
//             b->data.industry.blessing_days_left = 16;
//             update_farm_image(b);
//         }
//     }
// }
int farm_expected_produce(building* b) {
    int progress = b->data.industry.ready_production > 0
                        ? b->data.industry.ready_production
                        : b->data.industry.progress;
    if (!config_get(CONFIG_GP_FIX_FARM_PRODUCE_QUANTITY))
        progress = (progress / 20) * 20;
    // In OG Pharaoh, the progress value gets counted as if it was rounded
    // down to the lowest 20 points. No idea why! But here's as an option.

    int modifier = 1;
    if (city_data.religion.osiris_double_farm_yield && building_is_floodplain_farm(*b)) {
        modifier = 2;
    }

    return int((progress / 2.5f) * modifier);
}

void building_industry_update_production(void) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Industry Update");
    buildings_valid_do([] (building &b) {
        if (!b.output_resource_first_id) {
            return;
        }

        if (building_is_farm(b.type)) {
            return;
        }

        b.data.industry.has_raw_materials = false;
        if (b.num_workers <= 0) {
            return;
        }

        if (building_is_workshop(b.type) && !b.workshop_has_resources()) {
            return;
        }

        if (b.data.industry.curse_days_left) {
            b.data.industry.curse_days_left--;
        } else {
            if (b.data.industry.blessing_days_left) {
                b.data.industry.blessing_days_left--;
            }

            b.data.industry.progress += get_produce_uptick_per_day(b);

            if (b.data.industry.blessing_days_left && building_is_farm(b.type)) {
                const float normal_progress = get_produce_uptick_per_day(b);
                b.data.industry.progress += normal_progress;
            }

            int max = max_progress(b);
            if (b.data.industry.progress > max) {
                b.data.industry.progress = max;
            }
        }
    });
}

void building_industry_update_farms(void) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Farms Update");

    buildings_valid_do([] (building &b) {
        if (!b.output_resource_first_id) {
            return;
        }

        if (!building_is_farm(b.type)) {
            return;
        }

        if (b.data.industry.curse_days_left) { // TODO
            b.data.industry.curse_days_left--;
        }

        if (b.data.industry.blessing_days_left) {
            b.data.industry.blessing_days_left--;
        }
        //        if (b->data.industry.blessing_days_left && building_is_farm(b->type))
        //            b->data.industry.progress += b->num_workers;

        bool is_floodplain = building_is_floodplain_farm(b);
        int fert = map_get_fertility_for_farm(b.tile.grid_offset());
        int progress_step = (float)fert * get_farm_produce_uptick_per_day(b); // 0.16f

        if (is_floodplain) { // floodplain farms
            // advance production
            if (b.data.industry.labor_days_left > 0) {
                b.data.industry.progress += progress_step;
            }
            // update labor state
            if (b.data.industry.labor_state == LABOR_STATE_JUST_ENTERED) {
                b.data.industry.labor_state = LABOR_STATE_PRESENT;
            }

            if (b.data.industry.labor_days_left == 0) {
                b.data.industry.labor_state = LABOR_STATE_NONE;
            }

            if (b.data.industry.labor_days_left > 0) {
                b.data.industry.labor_days_left--;
            }
        } else { // meadow farms
            // advance production
            if (b.num_workers > 0) {
                b.data.industry.progress += progress_step * ((float)b.num_workers / 10.0f);
            }
        }

        // clamp progress
        int max = max_progress(b);
        b.data.industry.progress = std::clamp<int>(b.data.industry.progress, 0, max);

        update_farm_image(b);
    });
    city_data.religion.osiris_double_farm_yield = false;
}

void building_industry_update_wheat_production() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Wheat Production Update");
    if (scenario_property_climate() == CLIMATE_NORTHERN)
        return;

    buildings_valid_do([] (building &b) {
        if (!b.output_resource_first_id) {
            return;
        }

        if (b.houses_covered <= 0 || b.num_workers <= 0) {
            return;
        }

        if (b.type == BUILDING_BARLEY_FARM && !b.data.industry.curse_days_left) {
            b.data.industry.progress += b.num_workers;
            if (b.data.industry.blessing_days_left)
                b.data.industry.progress += b.num_workers;

            if (b.data.industry.progress > MAX_PROGRESS_RAW)
                b.data.industry.progress = MAX_PROGRESS_RAW;

            update_farm_image(b);
        }
    });
}

bool building_industry_has_produced_resource(building &b) {
    return b.data.industry.progress >= max_progress(b);
}

void building_industry_start_new_production(building* b) {
    b->data.industry.progress = 0;
    if (building_is_workshop(b->type)) {
        if (b->workshop_has_resources()) {
            b->workshop_start_production();
        }
    }

    if (building_is_farm(b->type)) {
        update_farm_image(*b);
    }
}

static bool farm_harvesting_month_for_produce(int resource_id, int month) {
    switch (resource_id) {
    // annual meadow farms
    case RESOURCE_CHICKPEAS:
    case RESOURCE_LETTUCE:
        return (month == MONTH_APRIL);
        break;
    case RESOURCE_FIGS:
        return (month == MONTH_SEPTEMPTER);
        break;
    case RESOURCE_FLAX:
        return (month == MONTH_DECEMBER);
        break;

    // biannual meadow farms
    case RESOURCE_GRAIN:
        return (month == MONTH_JANUARY || month == MONTH_MAY);
        break;
    case RESOURCE_BARLEY:
        return (month == MONTH_FEBRUARY || month == MONTH_AUGUST);
        break;
    case RESOURCE_POMEGRANATES:
        return (month == MONTH_JUNE || month == MONTH_NOVEMBER);
        break;
    }
    return false;
}

bool building_farm_time_to_deliver(bool floodplains, int resource_id) {
    if (floodplains) {
        auto current_cycle = floods_current_cycle();
        auto start_cycle = floods_start_cycle();
        auto harvest_cycle = start_cycle - 28.0f;
        return floodplains_is(FLOOD_STATE_IMMINENT) && current_cycle >= harvest_cycle;
    } else {
        if (game_time_day() < 2 && farm_harvesting_month_for_produce(resource_id, game_time_month()))
            return true;

        return false;
    }
}

void building_curse_farms(int big_curse) {
    // TODO
    //    for (int i = 1; i < MAX_BUILDINGS; i++) {
    //        building *b = building_get(i);
    //        if (b->state == BUILDING_STATE_VALID && b->output_resource_id && building_is_farm(b->type)) {
    //            b->data.industry.progress = 0;
    //            b->data.industry.blessing_days_left = 0;
    //            b->data.industry.curse_days_left = big_curse ? 48 : 4;
    //            update_farm_image(b);
    //        }
    //    }
}

void building_farm_deplete_soil(building* b) {
    // DIFFERENT from original Pharaoh... and a bit easier to do?
    if (config_get(CONFIG_GP_CH_SOIL_DEPLETION)) {
        int malus = (float)b->data.industry.progress / (float)MAX_PROGRESS_FARM_PH * (float)-100;
        for (int _y = b->tile.y(); _y < b->tile.y() + b->size; _y++) {
            for (int _x = b->tile.x(); _x < b->tile.x() + b->size; _x++) {
                map_soil_set_depletion(MAP_OFFSET(_x, _y), malus);
            }
        }
    } else {
        for (int _y = b->tile.y(); _y < b->tile.y() + b->size; _y++) {
            for (int _x = b->tile.x(); _x < b->tile.x() + b->size; _x++) {
                int new_fert = map_get_fertility(MAP_OFFSET(_x, _y), FERT_WITH_MALUS) * 0.2f;
                int malus = new_fert - map_get_fertility(MAP_OFFSET(_x, _y), FERT_NO_MALUS);
                map_soil_set_depletion(MAP_OFFSET(_x, _y), malus);
            }
        }
    }
    update_farm_image(*b);
}

void building_workshop_add_raw_material(building* b, int amount, e_resource res) {
    if (b->id > 0
        && building_is_workshop(b->type)
        && resource_required_by_workshop(b, res)) {
        if (b->data.industry.first_material_id == res) {
            b->stored_full_amount += amount; // BUG: any raw material accepted
        } else if (b->data.industry.second_material_id == res) {
            b->data.industry.stored_amount_second += amount;
        } else {
            assert(false);
        }
    } else {
        assert(false);
    }
}
int building_get_workshop_for_raw_material_with_room(tile2i tile, e_resource resource, int distance_from_entry, int road_network_id, tile2i &dst) {
    if (city_resource_is_stockpiled(resource)) {
        return 0;
    }

    int min_dist = INFINITE;
    building* min_building = 0;
    buildings_valid_do([&] (building &b) {
        if (!building_is_workshop(b.type)) {
            return;
        }

        if (!b.has_road_access || b.distance_from_entry <= 0) {
            return;
        }

        if (resource_required_by_workshop(&b, resource) && b.road_network_id == road_network_id && b.stored_amount(resource) < 200) {
            int dist = calc_distance_with_penalty(b.tile, tile, distance_from_entry, b.distance_from_entry);
            if (b.stored_amount(resource) > 0) {
                dist += 20;
            }

            if (dist < min_dist) {
                min_dist = dist;
                min_building = &b;
            }
        }
    });

    if (min_building) {
        map_point_store_result(min_building->road_access, dst);
        return min_building->id;
    }

    return 0;
}
int building_get_workshop_for_raw_material(tile2i tile, e_resource resource, int distance_from_entry, int road_network_id, tile2i &dst) {
    if (city_resource_is_stockpiled(resource)) {
        return 0;
    }

    int min_dist = INFINITE;
    building* min_building = nullptr;
    buildings_valid_do([&] (building &b) {
        if (!building_is_workshop(b.type)) {
            return;
        }

        if (!b.has_road_access || b.distance_from_entry <= 0) {
            return;
        }

        if (resource_required_by_workshop(&b, resource) && b.road_network_id == road_network_id) {
            int dist = 10 * (b.stored_amount(resource) / 100) + calc_distance_with_penalty(b.tile, tile, distance_from_entry, b.distance_from_entry);
            if (dist < min_dist) {
                min_dist = dist;
                min_building = &b;
            }
        }
    });

    if (min_building) {
        map_point_store_result(min_building->road_access, dst);
        return min_building->id;
    }

    return 0;
}
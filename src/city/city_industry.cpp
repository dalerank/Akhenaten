#include "city_industry.h"

#include "building/building_type.h"
#include "building/building_farm.h"
#include "building/building_industry.h"
#include "building/monuments.h"
#include "city/city_resource.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "game/resource.h"
#include "graphics/image.h"
#include "grid/building_tiles.h"
#include "grid/road_access.h"
#include "scenario/scenario.h"
#include "window/window_city.h"
#include "graphics/image_groups.h"
#include "grid/terrain.h"
#include "game/game_config.h"
#include "city/city.h"
#include "city/city_floods.h"
#include "grid/floodplain.h"
#include "grid/grid.h"

#include <cmath>

#define INFINITE 10000

delivery_destination building_get_asker_for_resource(tile2i tile, e_building_type btype, e_resource resource, int road_network_id, int distance_from_entry) {
    if (g_city.resource.is_stockpiled(resource)) {
        return {0};
    }

    int min_dist = INFINITE;
    building* min_building = 0;
    buildings_valid_do([&] (building &b) {
        if (b.type != btype) {
            return;
        }

        if (!map_has_road_access(b.tile, b.size)) {
            return;
        }

        if (b.distance_from_entry <= 0 || b.road_network_id != road_network_id) {
            return;
        }

        if (b.stored_amount(resource) >= b.need_resource_amount(resource) * 100) {
            return;
        }

        int dist = calc_distance_with_penalty(b.tile, tile, distance_from_entry, b.distance_from_entry);
        dist += 8 * b.stored_amount(resource) / 100;
        if (dist < min_dist) {
            min_dist = dist;
            min_building = &b;
        }
    });

    if (min_building && min_dist < INFINITE) {
        tile2i dst;
        map_point_store_result(min_building->road_access, dst);
        return {min_building->id, dst};
    }

    return {0};
}

static const float produce_uptick_per_day = 103.5f * 20.0f / 128.0f / 100.0f; // don't ask

float get_farm_produce_uptick_per_day(building &b) {
    return produce_uptick_per_day;
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

void city_industry_t::update_production() {
    OZZY_PROFILER_FUNCTION();
    buildings_valid_do([] (building &b) {
        if (!b.output.resource) {
            return;
        }

        if (b.is_farm()) {
            return;
        }

        if (b.is_workshop() && !b.workshop_has_resources()) {
            return;
        }

        auto industry = b.dcast_industry();
        if (!industry) {
            return;
        }

        industry->update_preproduction();
        industry->update_production();
    });
}

void building_industry_update_farms(void) {
    OZZY_PROFILER_FUNCTION();

    buildings_valid_farms_do([] (building &b) {
        building_farm *farm = b.dcast_farm();
        verify_no_crash(b.output.resource != RESOURCE_NONE);

        if (!farm) {
            return;
        }

        if (b.curse_days_left) { // TODO
            b.curse_days_left--;
        }

        if (b.blessing_days_left) {
            b.blessing_days_left--;
        }

        bool is_floodplain = b.is_floodplain_farm();
        int fert = map_get_fertility_for_farm(b.tile.grid_offset());
        int progress_step = (float)fert * get_farm_produce_uptick_per_day(b); // 0.16f
        const bool osiris_blessing = g_city.religion.osiris_double_farm_yield_days > 0;
        
        auto& farmd = farm->runtime_data();
        if (osiris_blessing) {
            farmd.produce_multiplier++;
        }

        if (is_floodplain) { // floodplain farms
            // advance production
            auto &d = b.dcast_farm()->runtime_data();
            if (d.labor_days_left > 0) {
                d.progress += progress_step;
            }
            // update labor state
            if (d.labor_state == LABOR_STATE_JUST_ENTERED) {
                d.labor_state = LABOR_STATE_PRESENT;
            }

            if (d.labor_days_left == 0) {
                d.labor_state = LABOR_STATE_NONE;
            }

            if (d.labor_days_left > 0) {
                d.labor_days_left--;
            }
        } else { // meadow farms
            // advance production
            auto &d = b.dcast_farm()->runtime_data();
            if (b.num_workers > 0) {
                d.progress += progress_step * ((float)b.num_workers / 10.0f);
            }
        }

        // clamp progress
        int max = farmd.progress_max;
        farmd.progress = std::clamp<int>(farmd.progress, 0, max);

        farm->update_tiles_image();
    });
}

void building_industry_update_wheat_production() {
    OZZY_PROFILER_FUNCTION();
    if (scenario_property_climate() == CLIMATE_NORTHERN)
        return;

    buildings_valid_do([] (building &b) {
        verify_no_crash(b.type == BUILDING_GRAIN_FARM);
        if (!b.output.resource) {
            return;
        }

        if (b.houses_covered <= 0 || b.num_workers <= 0) {
            return;
        }

        auto &farm = b.dcast_farm()->runtime_data();
        if (b.curse_days_left) {
            return;
        }

        farm.progress += b.num_workers;
        if (b.blessing_days_left) {
            farm.progress += b.num_workers;
        }

        farm.progress = std::min<short>(farm.progress, 200);
        b.dcast_farm()->update_tiles_image();
    }, BUILDING_GRAIN_FARM);
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

void building_workshop_add_raw_material(building* b, int amount, e_resource res) {
    if (b->id > 0 && b->is_workshop() && b->need_resource(res)) {
        if (b->input.resource == res || b->input.resource_second == res) {
            b->store_resource(b->input.resource, amount);
        } else {
            verify_no_crash(false);
        }
    } else {
        //assert(false);
    }
}

int building_get_workshop_for_raw_material_with_room(tile2i tile, e_resource resource, int distance_from_entry, int road_network_id, tile2i &dst) {
    if (g_city.resource.is_stockpiled(resource)) {
        return 0;
    }

    int min_dist = INFINITE;
    building* min_building = 0;
    buildings_valid_do([&] (building &b) {
        if (!b.is_workshop()) {
            return;
        }

        if (!b.has_road_access || b.distance_from_entry <= 0) {
            return;
        }

        if (b.need_resource(resource) && (b.road_network_id == road_network_id) && b.stored_amount(resource) < 200) {
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
    if (g_city.resource.is_stockpiled(resource)) {
        return 0;
    }

    int min_dist = INFINITE;
    building* min_building = nullptr;
    buildings_valid_do([&] (building &b) {
        if (!b.is_workshop()) {
            return;
        }

        if (!b.has_road_access || b.distance_from_entry <= 0) {
            return;
        }

        if (b.need_resource(resource) && (b.road_network_id == road_network_id)) {
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
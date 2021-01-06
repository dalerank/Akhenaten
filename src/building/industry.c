#include "window/city.h"
#include "industry.h"

#include "city/resource.h"
#include "core/calc.h"
#include "core/image.h"
#include "game/resource.h"
#include "map/building_tiles.h"
#include "map/road_access.h"
#include "scenario/property.h"

#define MAX_PROGRESS_RAW 200
#define MAX_PROGRESS_WORKSHOP 400
#define MAX_PROGRESS_FARM_PH 2000
#define INFINITE 10000

#include "map/terrain.h"
#include "city/view.h"

#include <math.h>

static const int X_VIEW_OFFSETS[9] = {
        0, 30, 60,
        -30, 0, 30,
        -60, -30, 0
};

static const int Y_VIEW_OFFSETS[9] = {
        30, 45, 60,
        45, 60, 75,
        60, 75, 90
};

int get_farm_image(int grid_offset) {
    if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) {
        int base = image_id_from_group(GROUP_BUILDING_FARMLAND);
        int fert_average = map_get_fertility_average(grid_offset);
        int fertility_index = 0;
        if (fert_average < 13)
            fertility_index = 0;
        else if (fert_average < 25)
            fertility_index = 1;
        else if (fert_average < 38)
            fertility_index = 2;
        else if (fert_average < 50)
            fertility_index = 3;
        else if (fert_average < 63)
            fertility_index = 4;
        else if (fert_average < 75)
            fertility_index = 5;
        else if (fert_average < 87)
            fertility_index = 6;
        else
            fertility_index = 7;
        return base + fertility_index;
    } else
        return image_id_from_group(GROUP_BUILDING_FARM_HOUSE);
}
int get_crops_image(int type, int growth) {
    int base = 0;
    if (GAME_ENV == ENGINE_ENV_C3) {
        base = image_id_from_group(GROUP_BUILDING_FARMLAND);
        return (type - BUILDING_BARLEY_FARM) * 5 + growth;
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        base = image_id_from_group(GROUP_BUILDING_FARM_CROPS_PH);
        switch (type) {
            case BUILDING_BARLEY_FARM:
                return base + 6 * 0 + growth;
            case BUILDING_FLAX_FARM:
                return base + 6 * 6 + growth;
            case BUILDING_GRAIN_FARM:
                return base + 6 * 2 + growth;
            case BUILDING_LETTUCE_FARM:
                return base + 6 * 3 + growth;
            case BUILDING_POMEGRANATES_FARM:
                return base + 6 * 4 + growth;
            case BUILDING_CHICKPEAS_FARM:
                return base + 6 * 5 + growth;
            case BUILDING_FIGS_FARM:
                return base + 6 * 1 + growth;
//            case BUILDING_HENNA_FARM:
//                return base + 6 * 0 + growth;
        }
    }
    return image_id_from_group(GROUP_BUILDING_FARM_CROPS_PH) + (type - BUILDING_BARLEY_FARM) * 6; // temp
}
void draw_ph_crops(int type, int progress, int grid_offset, int x, int y, color_t color_mask) {
    int image_crops = get_crops_image(type, 0);
    if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) {
        for (int i = 0; i < 9; i++) {
            int growth_offset = fmin(5, fmax(0, (progress - i*200)/100));
            image_draw_sprite(image_crops + growth_offset, x + X_VIEW_OFFSETS[i] + 60,
                                  y + Y_VIEW_OFFSETS[i] - 90, color_mask);
        }
    } else {
        for (int i = 4; i < 9; i++) {
            int growth_offset = fmin(5, fmax(0, (progress - i*200)/100));
            image_draw_sprite(image_crops + growth_offset, x + X_VIEW_OFFSETS[i] + 60,
                                  y + Y_VIEW_OFFSETS[i] - 90, color_mask);
        }
    }

}

static int max_progress(const building *b) {
    if (GAME_ENV == ENGINE_ENV_PHARAOH && building_is_farm(b->type))
        return MAX_PROGRESS_FARM_PH;
    return b->subtype.workshop_type ? MAX_PROGRESS_WORKSHOP : MAX_PROGRESS_RAW;
}
static void update_farm_image(const building *b) {
//    if (GAME_ENV == ENGINE_ENV_C3)
        map_building_tiles_add_farm(b->id, b->x, b->y,
                                    image_id_from_group(GROUP_BUILDING_FARMLAND) + 5 * (b->output_resource_id - 1),
                                    b->data.industry.progress);
//    else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
//
//    };
}

int building_determine_worker_needed() {
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        building *b = building_get(i);
        if (b->state != BUILDING_STATE_VALID)
            continue;
        if (building_is_farm(b->type) && !b->data.industry.worker_id && b->data.industry.labor_days_left <= 47)
            return i;
        else if (b->type == BUILDING_PYRAMID) {
            // todo
        }
    }
    return 0; // temp
}

void building_industry_update_production(void) {
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        building *b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || !b->output_resource_id)
            continue;
        b->data.industry.has_raw_materials = 0;
        if (b->labor_category != 255 && (b->houses_covered <= 0 || b->num_workers <= 0))
            continue;
        if (b->subtype.workshop_type && !b->loads_stored)
            continue;
        if (b->data.industry.curse_days_left)
            b->data.industry.curse_days_left--;
        else {
            if (b->data.industry.blessing_days_left)
                b->data.industry.blessing_days_left--;

            if (b->type == BUILDING_MARBLE_QUARRY)
                b->data.industry.progress += b->num_workers / 2;
            else if (building_is_farm(b->type) && GAME_ENV == ENGINE_ENV_PHARAOH && b->data.industry.labor_state >= 1) {
                int fert = map_get_fertility_average(b->grid_offset);
                b->data.industry.progress += fert * 0.16;
            } else
                b->data.industry.progress += b->num_workers;
            if (b->data.industry.blessing_days_left && building_is_farm(b->type))
                b->data.industry.progress += b->num_workers;

            int max = max_progress(b);
            if (b->data.industry.progress > max)
                b->data.industry.progress = max;

            if (building_is_farm(b->type))
                update_farm_image(b);
        }
    }
}
void building_industry_update_wheat_production(void) {
    if (scenario_property_climate() == CLIMATE_NORTHERN)
        return;
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        building *b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || !b->output_resource_id)
            continue;
        if (b->houses_covered <= 0 || b->num_workers <= 0)
            continue;
        if (b->type == BUILDING_WHEAT_FARM && !b->data.industry.curse_days_left) {
            b->data.industry.progress += b->num_workers;
            if (b->data.industry.blessing_days_left)
                b->data.industry.progress += b->num_workers;

            if (b->data.industry.progress > MAX_PROGRESS_RAW)
                b->data.industry.progress = MAX_PROGRESS_RAW;

            update_farm_image(b);
        }
    }
}

#include "city/data_private.h"

bool is_flood_imminent() {
    if (city_data.floods.month == 0)
        return true;
    return false;
}
int building_industry_has_produced_resource(building *b) {
//    if (building_is_farm(b->type) && GAME_ENV == ENGINE_ENV_PHARAOH) {
//        if (is_flood_imminent())
//            return 1;
//        return 0;
//    }
    return b->data.industry.progress >= max_progress(b);
}
void building_industry_start_new_production(building *b) {
    b->data.industry.progress = 0;
    if (b->subtype.workshop_type) {
        if (b->loads_stored) {
            if (b->loads_stored > 1)
                b->data.industry.has_raw_materials = 1;
            b->loads_stored--;
        }
    }
    if (building_is_farm(b->type))
        update_farm_image(b);
}

void building_bless_farms(void) {
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        building *b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->output_resource_id && building_is_farm(b->type)) {
            b->data.industry.progress = MAX_PROGRESS_RAW;
            b->data.industry.curse_days_left = 0;
            b->data.industry.blessing_days_left = 16;
            update_farm_image(b);
        }
    }
}
void building_curse_farms(int big_curse) {
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        building *b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->output_resource_id && building_is_farm(b->type)) {
            b->data.industry.progress = 0;
            b->data.industry.blessing_days_left = 0;
            b->data.industry.curse_days_left = big_curse ? 48 : 4;
            update_farm_image(b);
        }
    }
}

void building_workshop_add_raw_material(building *b) {
    if (b->id > 0 && building_is_workshop(b->type))
        b->loads_stored++; // BUG: any raw material accepted
}
int building_get_workshop_for_raw_material_with_room(int x, int y, int resource, int distance_from_entry, int road_network_id, map_point *dst) {
    if (city_resource_is_stockpiled(resource))
        return 0;

    int output_type = resource_to_workshop_type(resource);
    if (output_type == WORKSHOP_NONE)
        return 0;

    int min_dist = INFINITE;
    building *min_building = 0;
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        building *b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || !building_is_workshop(b->type))
            continue;

        if (!b->has_road_access || b->distance_from_entry <= 0)
            continue;

        if (b->subtype.workshop_type == output_type && b->road_network_id == road_network_id && b->loads_stored < 2) {
            int dist = calc_distance_with_penalty(b->x, b->y, x, y, distance_from_entry, b->distance_from_entry);
            if (b->loads_stored > 0)
                dist += 20;

            if (dist < min_dist) {
                min_dist = dist;
                min_building = b;
            }
        }
    }
    if (min_building) {
        map_point_store_result(min_building->road_access_x, min_building->road_access_y, dst);
        return min_building->id;
    }
    return 0;
}
int building_get_workshop_for_raw_material(int x, int y, int resource, int distance_from_entry, int road_network_id, map_point *dst) {
    if (city_resource_is_stockpiled(resource))
        return 0;

    int output_type = resource_to_workshop_type(resource);
    if (output_type == WORKSHOP_NONE)
        return 0;

    int min_dist = INFINITE;
    building *min_building = 0;
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        building *b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || !building_is_workshop(b->type))
            continue;

        if (!b->has_road_access || b->distance_from_entry <= 0)
            continue;

        if (b->subtype.workshop_type == output_type && b->road_network_id == road_network_id) {
            int dist = 10 * b->loads_stored +
                       calc_distance_with_penalty(b->x, b->y, x, y, distance_from_entry, b->distance_from_entry);
            if (dist < min_dist) {
                min_dist = dist;
                min_building = b;
            }
        }
    }
    if (min_building) {
        map_point_store_result(min_building->road_access_x, min_building->road_access_y, dst);
        return min_building->id;
    }
    return 0;
}

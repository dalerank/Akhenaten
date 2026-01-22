#include "natives.h"

#include "building/building.h"
#include "city/buildings.h"
#include "city/city.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/grid.h"
#include "grid/image.h"
#include "grid/property.h"
#include "grid/random.h"
#include "grid/terrain.h"
#include "scenario/scenario.h"
#include "scenario/map.h"

static void mark_native_land(int x, int y, int size, int radius) {
    grid_area area = map_grid_get_area(tile2i(x, y), size, radius);
    map_grid_area_foreach(area.tmin, area.tmax, [] (tile2i tile) {
        map_property_mark_native_land(tile.grid_offset());
    });
}

static bool has_building_on_native_land(int x, int y, int size, int radius) {
    grid_area area = map_grid_get_area(tile2i(x, y), size, radius);
    for (int yy = area.tmin.y(), endy = area.tmax.y(); yy <= endy; yy++) {
        for (int xx = area.tmin.x(), endx = area.tmax.x(); xx <= endx; xx++) {
            int building_id = map_building_at(MAP_OFFSET(xx, yy));
            if (building_id > 0) {
                int type = building_get(building_id)->type;
                if (type != BUILDING_UNUSED_SHIP_BRIDGE_83 && type != BUILDING_UNUSED_NATIVE_HUT_88 && type != BUILDING_UNUSED_NATIVE_MEETING_89
                    && type != BUILDING_UNUSED_NATIVE_CROPS_93 && type != BUILDING_ROADBLOCK) {
                    return true;
                }
            }
        }
    }
    return false;
}

static void determine_meeting_center(void) {
    // gather list of meeting centers
    svector<building_id, 128> ids;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->is_valid() && b->type == BUILDING_UNUSED_NATIVE_MEETING_89) {
            ids.push_back(i);
        }
    }

    size_t total_meetings = ids.size();
    if (total_meetings <= 0)
        return;

    // determine closest meeting center for hut
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_UNUSED_NATIVE_HUT_88) {
            int min_dist = 1000;
            int min_meeting_id = 0;
            for (int n = 0; n < total_meetings; n++) {
                building* meeting = building_get(ids[n]);
                int dist = calc_maximum_distance(b->tile, meeting->tile);
                if (dist < min_dist) {
                    min_dist = dist;
                    min_meeting_id = ids[n];
                }
            }
            b->native_meeting_center_id = min_meeting_id;
        }
    }
}

void map_natives_init() {
    int meeting_center_set = 0;
    int image_hut = scenario_building_image_native_hut();
    int image_meeting = scenario_building_image_native_meeting();
    int image_crops = scenario_building_image_native_crops();
    int native_image = image_id_from_group(GROUP_BUILDING_NATIVE);
    int grid_offset = scenario_map_data()->start_offset;
    for (int y = 0; y < scenario_map_data()->height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < scenario_map_data()->width; x++, grid_offset++) {
            if (!map_terrain_is(grid_offset, TERRAIN_BUILDING) || map_building_at(grid_offset))
                continue;

            int random_bit = map_random_get(grid_offset) & 1;
            e_building_type type;
            int image_id = map_image_at(grid_offset);
            if (image_id == image_hut) {
                type = BUILDING_UNUSED_NATIVE_HUT_88;
                map_image_set(grid_offset, native_image);
            } else if (image_id == image_hut + 1) {
                type = BUILDING_UNUSED_NATIVE_HUT_88;
                map_image_set(grid_offset, native_image + 1);
            } else if (image_id == image_meeting) {
                type = BUILDING_UNUSED_NATIVE_MEETING_89;
                map_image_set(grid_offset, native_image + 2);
                map_image_set(grid_offset + GRID_OFFSET(1, 0), native_image + 2);
                map_image_set(grid_offset + GRID_OFFSET(0, 1), native_image + 2);
                map_image_set(grid_offset + GRID_OFFSET(1, 1), native_image + 2);
            } else if (image_id == image_crops) {
                type = BUILDING_UNUSED_NATIVE_CROPS_93;
                int img_id = building_static_params::get(BUILDING_BARLEY_FARM).first_img(animkeys().farmland);
                map_image_set(grid_offset, img_id + random_bit);
            } else { // unknown building
                map_building_tiles_remove(0, tile2i(x, y));
                continue;
            }
            building* b = building_create(type, tile2i(x, y), 0);
            map_building_set(grid_offset, b->id);
            b->state = BUILDING_STATE_VALID;
            switch (type) {
            case BUILDING_UNUSED_NATIVE_CROPS_93:
                //b->data.industry.progress = random_bit; // TODO
                break;
            case BUILDING_UNUSED_NATIVE_MEETING_89:
                b->sentiment.native_anger = 100;
                map_building_set(grid_offset + GRID_OFFSET(1, 0), b->id);
                map_building_set(grid_offset + GRID_OFFSET(0, 1), b->id);
                map_building_set(grid_offset + GRID_OFFSET(1, 1), b->id);
                mark_native_land(b->tile.x(), b->tile.y(), 2, 6);
                if (!meeting_center_set)
                    city_buildings_set_main_native_meeting_center(b->tile.x(), b->tile.y());

                break;
            case BUILDING_UNUSED_NATIVE_HUT_88:
                b->sentiment.native_anger = 100;
                b->figure_spawn_delay = random_bit;
                mark_native_land(b->tile.x(), b->tile.y(), 1, 3);
                break;
            }
        }
    }

    determine_meeting_center();
}

void map_natives_init_editor(void) {
    int image_hut = scenario_building_image_native_hut();
    int image_meeting = scenario_building_image_native_meeting();
    int image_crops = scenario_building_image_native_crops();
    int native_image = image_id_from_group(GROUP_EDITOR_BUILDING_NATIVE);
    int grid_offset = scenario_map_data()->start_offset;
    for (int y = 0; y < scenario_map_data()->height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < scenario_map_data()->width; x++, grid_offset++) {
            if (!map_terrain_is(grid_offset, TERRAIN_BUILDING) || map_building_at(grid_offset))
                continue;

            e_building_type type;
            int image_id = map_image_at(grid_offset);
            if (image_id == image_hut) {
                type = BUILDING_UNUSED_NATIVE_HUT_88;
                map_image_set(grid_offset, native_image);
            } else if (image_id == image_hut + 1) {
                type = BUILDING_UNUSED_NATIVE_HUT_88;
                map_image_set(grid_offset, native_image + 1);
            } else if (image_id == image_meeting) {
                type = BUILDING_UNUSED_NATIVE_MEETING_89;
                map_image_set(grid_offset, native_image + 2);
                map_image_set(grid_offset + GRID_OFFSET(1, 0), native_image + 2);
                map_image_set(grid_offset + GRID_OFFSET(0, 1), native_image + 2);
                map_image_set(grid_offset + GRID_OFFSET(1, 1), native_image + 2);
            } else if (image_id == image_crops) {
                type = BUILDING_UNUSED_NATIVE_CROPS_93;
                map_image_set(grid_offset, image_id_from_group(GROUP_EDITOR_BUILDING_CROPS));
            } else { // unknown building
                map_building_tiles_remove(0, tile2i(x, y));
                continue;
            }
            building* b = building_create(type, tile2i(x, y), 0);
            b->state = BUILDING_STATE_VALID;
            map_building_set(grid_offset, b->id);
            if (type == BUILDING_UNUSED_NATIVE_MEETING_89) {
                map_building_set(grid_offset + GRID_OFFSET(1, 0), b->id);
                map_building_set(grid_offset + GRID_OFFSET(0, 1), b->id);
                map_building_set(grid_offset + GRID_OFFSET(1, 1), b->id);
            }
        }
    }
}

void map_natives_check_land(void) {
    OZZY_PROFILER_FUNCTION();
    map_property_clear_all_native_land();
    g_city.military.decrease_native_attack_duration();

    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID)
            continue;

        int size, radius;
        if (b->type == BUILDING_UNUSED_NATIVE_HUT_88) {
            size = 1;
            radius = 3;
        } else if (b->type == BUILDING_UNUSED_NATIVE_MEETING_89) {
            size = 2;
            radius = 6;
        } else {
            continue;
        }
        if (b->sentiment.native_anger >= 100) {
            mark_native_land(b->tile.x(), b->tile.y(), size, radius);
            if (has_building_on_native_land(b->tile.x(), b->tile.y(), size, radius))
                g_city.military.start_native_attack();

        } else {
            b->sentiment.native_anger++;
        }
    }
}

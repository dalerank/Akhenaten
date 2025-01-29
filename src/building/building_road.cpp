#include "building/building_road.h"

#include "game/undo.h"
#include "city/finance.h"
#include "city/labor.h"
#include "grid/routing/routing.h"
#include "grid/routing/routing_terrain.h"
#include "building/construction/routed.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "grid/floodplain.h"
#include "grid/image.h"
#include "grid/property.h"
#include "grid/road_canal.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/window.h"
#include "js/js_game.h"
#include "widget/city/building_ghost.h"
#include "construction/build_planner.h"

buildings::model_t<building_road> road_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_road);
void config_load_building_road() {
    road_m.load();
}

void building_road::on_place_checks() {
    /*nothing*/
}

int building_road::place(bool measure_only, tile2i start, tile2i end) {
    game_undo_restore_map(0);
    int items_placed = 0;
    if (map_routing_calculate_distances_for_building(ROUTED_BUILDING_ROAD, start)
        && place_routed_building(start, end, ROUTED_BUILDING_ROAD, &items_placed)) {
        if (!measure_only) {
            map_routing_update_land();
        }
    }
    return items_placed;
}

void building_road::ghost_preview(tile2i tile, vec2i pixel, painter &ctx) {
    int grid_offset = tile.grid_offset();
    bool blocked = false;
    int image_id = 0;

    if (map_terrain_is(grid_offset, TERRAIN_CANAL)) {
        image_id = image_id_from_group(GROUP_BUILDING_AQUEDUCT);
        if (map_can_place_road_under_canal(grid_offset)) {
            image_id += map_get_canal_with_road_image(grid_offset);
        } else {
            blocked = true;
        }
    } else if (map_terrain_is(grid_offset, TERRAIN_NOT_CLEAR - TERRAIN_FLOODPLAIN)) {
        blocked = true;
    } else {
        image_id = image_id_from_group(GROUP_TERRAIN_DIRT_ROAD);
        if (!map_terrain_has_adjacent_y_with_type(grid_offset, TERRAIN_ROAD) && map_terrain_has_adjacent_x_with_type(grid_offset, TERRAIN_ROAD)) {
            image_id++;
        }

        if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) {
            if (map_terrain_is(grid_offset, TERRAIN_WATER)) // inundated floodplains
                blocked = true;
        } else if (map_terrain_has_adjecent_with_type(grid_offset, TERRAIN_FLOODPLAIN)) {
            if (map_terrain_count_directly_adjacent_with_type(grid_offset, TERRAIN_FLOODPLAIN) != 1)
                blocked = true;
            else {
                if (map_terrain_has_adjacent_x_with_type(grid_offset, TERRAIN_FLOODPLAIN)) {
                    if (map_terrain_has_adjacent_y_with_type(grid_offset, TERRAIN_ROAD))
                        blocked = true;
                    else
                        image_id++;
                }

                if (map_terrain_has_adjacent_y_with_type(grid_offset, TERRAIN_FLOODPLAIN)
                    && map_terrain_has_adjacent_x_with_type(grid_offset, TERRAIN_ROAD)) {
                    blocked = true;
                }
            }
        }
    }

    if (city_finance_out_of_money()) {
        blocked = true;
    }

    if (blocked) {
        build_planner::draw_flat_tile(ctx, pixel, COLOR_MASK_RED);
    } else {
        build_planner::draw_building_ghost(ctx, image_id, pixel);
    }
}

void building_road::set_image(tile2i tile) {
    int grid_offset = tile.grid_offset();
    if (!map_terrain_is(grid_offset, TERRAIN_ROAD)
        || map_terrain_is(grid_offset, TERRAIN_WATER)
        || map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
        return;
    }

    if (map_terrain_is(grid_offset, TERRAIN_CANAL)) {
        map_tiles_set_canal_image(grid_offset);
        return;
    }

    if (map_property_is_plaza_or_earthquake(grid_offset)) {
        return;
    }

    int base_img = road_m.anim["base"].first_img();
    if (map_tiles_is_paved_road(grid_offset)) {
        const terrain_image* img = map_image_context_get_paved_road(grid_offset);
        map_image_set(grid_offset, base_img + img->group_offset + img->item_offset);
    } else {
        if (!map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) {
            map_image_set_road_floodplain(grid_offset);
        } else {
            const terrain_image* img = map_image_context_get_dirt_road(grid_offset);
            map_image_set(grid_offset, base_img + img->group_offset + img->item_offset + 49 + 344);
        }
    }
    map_property_set_multi_tile_size(grid_offset, 1);
    map_property_mark_draw_tile(grid_offset);
}

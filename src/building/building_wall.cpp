#include "building_wall.h"

#include "game/undo.h"
#include "grid/terrain.h"
#include "grid/property.h"
#include "grid/tiles.h"
#include "grid/image.h"
#include "grid/building.h"
#include "graphics/view/view.h"
#include "construction/routed.h"
#include "graphics/image.h"
#include "grid/routing/routing_terrain.h"
#include "game/game_events.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_mud_wall);

void ANK_PERMANENT_CALLBACK(event_building_update_walls, ev) {
    building_mud_wall::update_area_walls( ev.tile, ev.size );
}

bool building_mud_wall::place_wall(bool measure_only, tile2i start, tile2i end) {
    game_undo_restore_map(0);

    int forbidden_terrain_mask = TERRAIN_TREE | TERRAIN_ROCK | TERRAIN_WATER | TERRAIN_BUILDING | TERRAIN_SHRUB
        | TERRAIN_ROAD | TERRAIN_GARDEN | TERRAIN_ELEVATION | TERRAIN_RUBBLE | TERRAIN_CANAL
        | TERRAIN_ACCESS_RAMP;

    if (map_terrain_is(start, forbidden_terrain_mask))
        return false;

    if (map_terrain_is(end, forbidden_terrain_mask))
        return false;

    auto result = place_routed_building(start, end, ROUTED_BUILDING_WALL);
    if (result.ok && !measure_only) {
        map_routing_update_land();
        map_routing_update_walls();
    }

    return result.ok;
}

void building_mud_wall::update_all_walls() {
    map_tiles_foreach_map_tile(building_mud_wall::set_image);
}

void building_mud_wall::update_area_walls(tile2i tile, int size) {
    tile2i start = tile.shifted(-1, -1);
    tile2i end = tile.shifted(size, size);
    map_tiles_foreach_region_tile_ex(start, end, building_mud_wall::set_image);
}

int building_mud_wall::get_gatehouse_position(int grid_offset, int direction, int building_id) {
    int result = 0;
    if (direction == DIR_0_TOP_RIGHT) {
        if (map_terrain_is(grid_offset + GRID_OFFSET(1, -1), TERRAIN_GATEHOUSE)
            && map_building_at(grid_offset + GRID_OFFSET(1, -1)) == building_id) {
            result = 1;
            if (!map_terrain_is(grid_offset + GRID_OFFSET(1, 0), TERRAIN_WALL))
                result = 0;

            if (map_terrain_is(grid_offset + GRID_OFFSET(-1, 0), TERRAIN_WALL)
                && map_terrain_is(grid_offset + GRID_OFFSET(-1, 1), TERRAIN_WALL)) {
                result = 2;
            }
            if (!map_terrain_is(grid_offset + GRID_OFFSET(0, 1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

            if (!map_terrain_is(grid_offset + GRID_OFFSET(1, 1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

        } else if (map_terrain_is(grid_offset + GRID_OFFSET(-1, -1), TERRAIN_GATEHOUSE)
            && map_building_at(grid_offset + GRID_OFFSET(-1, -1)) == building_id) {
            result = 3;
            if (!map_terrain_is(grid_offset + GRID_OFFSET(-1, 0), TERRAIN_WALL))
                result = 0;

            if (map_terrain_is(grid_offset + GRID_OFFSET(1, 0), TERRAIN_WALL)
                && map_terrain_is(grid_offset + GRID_OFFSET(1, 1), TERRAIN_WALL)) {
                result = 4;
            }
            if (!map_terrain_is(grid_offset + GRID_OFFSET(0, 1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

            if (!map_terrain_is(grid_offset + GRID_OFFSET(-1, 1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;
        }
    } else if (direction == DIR_6_TOP_LEFT) {
        if (map_terrain_is(grid_offset + GRID_OFFSET(-1, 1), TERRAIN_GATEHOUSE)
            && map_building_at(grid_offset + GRID_OFFSET(-1, 1)) == building_id) {
            result = 1;
            if (!map_terrain_is(grid_offset + GRID_OFFSET(0, 1), TERRAIN_WALL))
                result = 0;

            if (map_terrain_is(grid_offset + GRID_OFFSET(0, -1), TERRAIN_WALL)
                && map_terrain_is(grid_offset + GRID_OFFSET(1, -1), TERRAIN_WALL)) {
                result = 2;
            }
            if (!map_terrain_is(grid_offset + GRID_OFFSET(1, 0), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

            if (!map_terrain_is(grid_offset + GRID_OFFSET(1, 1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

        } else if (map_terrain_is(grid_offset + GRID_OFFSET(-1, -1), TERRAIN_GATEHOUSE)
            && map_building_at(grid_offset + GRID_OFFSET(-1, -1)) == building_id) {
            result = 3;
            if (!map_terrain_is(grid_offset + GRID_OFFSET(0, -1), TERRAIN_WALL))
                result = 0;

            if (map_terrain_is(grid_offset + GRID_OFFSET(0, 1), TERRAIN_WALL)
                && map_terrain_is(grid_offset + GRID_OFFSET(1, 1), TERRAIN_WALL)) {
                result = 4;
            }
            if (!map_terrain_is(grid_offset + GRID_OFFSET(1, 0), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

            if (!map_terrain_is(grid_offset + GRID_OFFSET(1, -1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;
        }
    } else if (direction == DIR_4_BOTTOM_LEFT) {
        if (map_terrain_is(grid_offset + GRID_OFFSET(1, 1), TERRAIN_GATEHOUSE)
            && map_building_at(grid_offset + GRID_OFFSET(1, 1)) == building_id) {
            result = 1;
            if (!map_terrain_is(grid_offset + GRID_OFFSET(1, 0), TERRAIN_WALL))
                result = 0;

            if (map_terrain_is(grid_offset + GRID_OFFSET(-1, 0), TERRAIN_WALL)
                && map_terrain_is(grid_offset + GRID_OFFSET(-1, -1), TERRAIN_WALL)) {
                result = 2;
            }
            if (!map_terrain_is(grid_offset + GRID_OFFSET(0, -1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

            if (!map_terrain_is(grid_offset + GRID_OFFSET(1, -1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

        } else if (map_terrain_is(grid_offset + GRID_OFFSET(-1, 1), TERRAIN_GATEHOUSE)
            && map_building_at(grid_offset + GRID_OFFSET(-1, 1)) == building_id) {
            result = 3;
            if (!map_terrain_is(grid_offset + GRID_OFFSET(-1, 0), TERRAIN_WALL))
                result = 0;

            if (map_terrain_is(grid_offset + GRID_OFFSET(1, 0), TERRAIN_WALL)
                && map_terrain_is(grid_offset + GRID_OFFSET(1, -1), TERRAIN_WALL)) {
                result = 4;
            }
            if (!map_terrain_is(grid_offset + GRID_OFFSET(0, -1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

            if (!map_terrain_is(grid_offset + GRID_OFFSET(-1, -1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;
        }
    } else if (direction == DIR_2_BOTTOM_RIGHT) {
        if (map_terrain_is(grid_offset + GRID_OFFSET(1, 1), TERRAIN_GATEHOUSE)
            && map_building_at(grid_offset + GRID_OFFSET(1, 1)) == building_id) {
            result = 1;
            if (!map_terrain_is(grid_offset + GRID_OFFSET(0, 1), TERRAIN_WALL))
                result = 0;

            if (map_terrain_is(grid_offset + GRID_OFFSET(0, -1), TERRAIN_WALL)
                && map_terrain_is(grid_offset + GRID_OFFSET(-1, -1), TERRAIN_WALL)) {
                result = 2;
            }
            if (!map_terrain_is(grid_offset + GRID_OFFSET(-1, 0), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

            if (!map_terrain_is(grid_offset + GRID_OFFSET(-1, 1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

        } else if (map_terrain_is(grid_offset + GRID_OFFSET(1, -1), TERRAIN_GATEHOUSE)
            && map_building_at(grid_offset + GRID_OFFSET(1, -1)) == building_id) {
            result = 3;
            if (!map_terrain_is(grid_offset + GRID_OFFSET(0, -1), TERRAIN_WALL))
                result = 0;

            if (map_terrain_is(grid_offset + GRID_OFFSET(0, 1), TERRAIN_WALL)
                && map_terrain_is(grid_offset + GRID_OFFSET(-1, 1), TERRAIN_WALL)) {
                result = 4;
            }
            if (!map_terrain_is(grid_offset + GRID_OFFSET(-1, 0), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

            if (!map_terrain_is(grid_offset + GRID_OFFSET(-1, -1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;
        }
    }
    return result;
}

int building_mud_wall::get_gatehouse_building_id(int grid_offset) {
    if (map_terrain_is(grid_offset, TERRAIN_GATEHOUSE)) {
        return map_building_at(grid_offset);
    }

    return 0;
}

void building_mud_wall::set_wall_gatehouse_image_manually(int grid_offset) {
    int gatehouse_up = get_gatehouse_building_id(grid_offset + GRID_OFFSET(0, -1));
    int gatehouse_left = get_gatehouse_building_id(grid_offset + GRID_OFFSET(-1, 0));
    int gatehouse_down = get_gatehouse_building_id(grid_offset + GRID_OFFSET(0, 1));
    int gatehouse_right = get_gatehouse_building_id(grid_offset + GRID_OFFSET(1, 0));
    int image_offset = 0;
    int map_orientation = city_view_orientation();
    if (map_orientation == DIR_0_TOP_RIGHT) {
        if (gatehouse_up && !gatehouse_left) {
            int pos = get_gatehouse_position(grid_offset, DIR_0_TOP_RIGHT, gatehouse_up);
            if (pos > 0) {
                if (pos <= 2)
                    image_offset = 29;
                else if (pos == 3)
                    image_offset = 31;
                else {
                    image_offset = 33;
                }
            }
        } else if (gatehouse_left && !gatehouse_up) {
            int pos = get_gatehouse_position(grid_offset, DIR_6_TOP_LEFT, gatehouse_left);
            if (pos > 0) {
                if (pos <= 2)
                    image_offset = 30;
                else if (pos == 3)
                    image_offset = 32;
                else {
                    image_offset = 33;
                }
            }
        }
    } else if (map_orientation == DIR_2_BOTTOM_RIGHT) {
        if (gatehouse_up && !gatehouse_right) {
            int pos = get_gatehouse_position(grid_offset, DIR_0_TOP_RIGHT, gatehouse_up);
            if (pos > 0) {
                if (pos == 1)
                    image_offset = 32;
                else if (pos == 2)
                    image_offset = 33;
                else {
                    image_offset = 30;
                }
            }
        } else if (gatehouse_right && !gatehouse_up) {
            int pos = get_gatehouse_position(grid_offset, DIR_2_BOTTOM_RIGHT, gatehouse_right);
            if (pos > 0) {
                if (pos <= 2)
                    image_offset = 29;
                else if (pos == 3)
                    image_offset = 31;
                else {
                    image_offset = 33;
                }
            }
        }
    } else if (map_orientation == DIR_4_BOTTOM_LEFT) {
        if (gatehouse_down && !gatehouse_right) {
            int pos = get_gatehouse_position(grid_offset, DIR_4_BOTTOM_LEFT, gatehouse_down);
            if (pos > 0) {
                if (pos == 1)
                    image_offset = 31;
                else if (pos == 2)
                    image_offset = 33;
                else {
                    image_offset = 29;
                }
            }
        } else if (gatehouse_right && !gatehouse_down) {
            int pos = get_gatehouse_position(grid_offset, DIR_2_BOTTOM_RIGHT, gatehouse_right);
            if (pos > 0) {
                if (pos == 1)
                    image_offset = 32;
                else if (pos == 2)
                    image_offset = 33;
                else {
                    image_offset = 30;
                }
            }
        }
    } else if (map_orientation == DIR_6_TOP_LEFT) {
        if (gatehouse_down && !gatehouse_left) {
            int pos = get_gatehouse_position(grid_offset, DIR_4_BOTTOM_LEFT, gatehouse_down);
            if (pos > 0) {
                if (pos <= 2)
                    image_offset = 30;
                else if (pos == 3)
                    image_offset = 32;
                else {
                    image_offset = 33;
                }
            }
        } else if (gatehouse_left && !gatehouse_down) {
            int pos = get_gatehouse_position(grid_offset, DIR_6_TOP_LEFT, gatehouse_left);
            if (pos > 0) {
                if (pos == 1)
                    image_offset = 31;
                else if (pos == 2)
                    image_offset = 33;
                else {
                    image_offset = 29;
                }
            }
        }
    }

    if (image_offset) {
        const int id = building_static_params::get(TYPE).base_img();
        map_image_set(grid_offset, id + image_offset);
    }
}

terrain_image building_mud_wall::get_terrain_image(tile2i tile) {
    std::array<int, MAP_IMAGE_MAX_TILES> tiles;
    
    map_image_context_fill_matches(tile, TERRAIN_WALL | TERRAIN_GATEHOUSE, { 0, 1 }, tiles);

    terrain_image timg = map_image_context_get_terrain_image(CONTEXT_WALL, tiles);
    return timg;
}

void building_mud_wall::set_image(tile2i tile) {
    const bool is_wall = map_terrain_is(tile, TERRAIN_WALL);
    const bool is_building = map_terrain_is(tile, TERRAIN_BUILDING);
    if (!is_wall || is_building) {
        return;
    }

    terrain_image img = get_terrain_image(tile);
    const int id = building_static_params::get(TYPE).base_img();
    const int img_id = id + img.group_offset + img.item_offset;
    map_image_set(tile, img_id);
    map_property_set_multi_tile_size(tile.grid_offset(), 1);
    map_property_mark_draw_tile(tile);

    if (map_terrain_count_directly_adjacent_with_type(tile.grid_offset(), TERRAIN_GATEHOUSE) > 0) {
        img = map_image_context_get_wall_gatehouse(tile);
        if (img.is_valid) {
            map_image_set(tile, img_id);
        } else {
            set_wall_gatehouse_image_manually(tile.grid_offset());
        }
    }
}

bool building_mud_wall::set_wall(tile2i tile) {
    int grid_offset = tile.grid_offset();
    bool tile_set = false;
    
    if (!map_terrain_is(grid_offset, TERRAIN_WALL)) {
        tile_set = true;
    }

    map_terrain_add(grid_offset, TERRAIN_WALL);
    map_property_clear_constructing(grid_offset);

    map_tiles_foreach_region_tile_ex(tile.shifted(-1, -1), tile.shifted(1, 1), set_image);

    return tile_set;
}

int building_mud_wall::preview::construction_update(build_planner &p, tile2i start, tile2i end) const {
    int items_placed = place_wall(true, start, end);
    return items_placed;
}

int building_mud_wall::preview::construction_place(build_planner &planer, tile2i start, tile2i end, int orientation, int variant) const {
    int items_placed = place_wall(false, start, end);
    return items_placed;
}

bool building_mud_wall::preview::can_construction_start(build_planner &p, tile2i start) const {
    return map_routing_calculate_distances_for_building(ROUTED_BUILDING_WALL, start);
}

void building_mud_wall::on_place_checks() {
    // nothing
}

#include "road_canal.h"

#include "city/city_buildings.h"
#include "core/direction.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/view/view.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "grid/image.h"
#include "grid/routing/routing.h"
#include "grid/routing/routing_terrain.h"
#include "grid/terrain.h"

bool map_can_place_road_under_canal(int grid_offset) {
    int image_id = map_image_at(grid_offset) - image_id_from_group(GROUP_BUILDING_AQUEDUCT);
    if (image_id != 0 && image_id != 1 && image_id != 48 && image_id != 49)
        return false;

    //    int check_y = image_id == 0 || image_id == 48;
    //    if (city_view_orientation() == DIR_6_TOP_LEFT || city_view_orientation() == DIR_2_BOTTOM_RIGHT)
    //        check_y = !check_y;
    //
    //    if (check_y) {
    //        if (map_routing_distance(grid_offset + map_grid_delta(0, -1)) > 0 ||
    //            map_routing_distance(grid_offset + map_grid_delta(0, 1)) > 0) {
    //            return false;
    //        }
    //    } else {
    //        if (map_routing_distance(grid_offset + map_grid_delta(-1, 0)) > 0 ||
    //            map_routing_distance(grid_offset + map_grid_delta(1, 0)) > 0) {
    //            return false;
    //        }
    //    }
    return true;
}

bool map_can_place_canal_on_road(int grid_offset) {
    int base_img = building_impl::params(BUILDING_ROAD).anim["base"].first_img();
    int image_id = map_image_at(grid_offset) - base_img;
    if (image_id != 0 && image_id != 1 && image_id != 49 && image_id != 50)
        return false;

    //    int check_y = image_id == 0 || image_id == 49;
    //    if (city_view_orientation() == DIR_6_TOP_LEFT || city_view_orientation() == DIR_2_BOTTOM_RIGHT)
    //        check_y = !check_y;
    //
    //    if (check_y) {
    //        if (map_routing_distance(grid_offset + map_grid_delta(0, -1)) > 0 ||
    //            map_routing_distance(grid_offset + map_grid_delta(0, 1)) > 0) {
    //            return false;
    //        }
    //    } else {
    //        if (map_routing_distance(grid_offset + map_grid_delta(-1, 0)) > 0 ||
    //            map_routing_distance(grid_offset + map_grid_delta(1, 0)) > 0) {
    //            return false;
    //        }
    //    }
    return true;
}

int map_get_canal_with_road_image(int grid_offset) {
    int image_id = map_image_at(grid_offset) - image_id_from_group(GROUP_BUILDING_AQUEDUCT);
    switch (image_id) {
    case 2:
        return 8;
    case 17:
        return 23;
    case 3:
        return 9;
    case 18:
        return 24;
    case 0:
    case 1:
    case 8:
    case 9:
    case 15:
    case 16:
    case 23:
    case 24:
        // unchanged
        return image_id;
    default:
        // shouldn't happen
        return 8;
    }
}

static int is_road_tile_for_canal(int grid_offset, int gate_orientation) {
    int is_road = map_terrain_is(grid_offset, TERRAIN_ROAD) ? 1 : 0;
    if (map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
        building* b = building_at(grid_offset);
        if (b->type == BUILDING_MUD_GATEHOUSE) {
            if (b->subtype.orientation == gate_orientation)
                is_road = 1;

        } else if (b->type == BUILDING_GRANARY) {
            if (map_routing_citizen_is_road(grid_offset))
                is_road = 1;
        }
    }
    return is_road;
}

int map_is_straight_road_for_canal(int grid_offset) {
    int road_tiles_x = is_road_tile_for_canal(grid_offset + GRID_OFFSET(1, 0), 2)
                       + is_road_tile_for_canal(grid_offset + GRID_OFFSET(-1, 0), 2);
    int road_tiles_y = is_road_tile_for_canal(grid_offset + GRID_OFFSET(0, -1), 1)
                       + is_road_tile_for_canal(grid_offset + GRID_OFFSET(0, 1), 1);

    if (road_tiles_x == 2 && road_tiles_y == 0)
        return 1;
    else if (road_tiles_y == 2 && road_tiles_x == 0)
        return 1;
    else {
        return 0;
    }
}

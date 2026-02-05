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
#include "building/building_irrigation_ditch.h"
#include "grid/terrain.h"

bool map_can_place_road_under_canal(tile2i tile) {
    int water_start_image = building_irrigation_ditch::images().begin;
    int image_id = map_image_at(tile) - water_start_image;
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

bool map_can_place_canal_on_road(tile2i tile) {
    const auto &params = building_static_params::get(BUILDING_ROAD);
    int base_img = params.base_img();
    int image_id = map_image_at(tile) - base_img;
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
    int water_start_image = building_irrigation_ditch::images().begin;
    int image_id = map_image_at(grid_offset) - water_start_image;
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
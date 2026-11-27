#include "road_canal.h"

#include "building/building.h"
#include "building/building_irrigation_ditch.h"
#include "building/building_type.h"
#include "city/city_buildings.h"
#include "grid/building.h"
#include "grid/canals.h"
#include "grid/grid.h"
#include "grid/image.h"
#include "grid/routing/routing_terrain.h"
#include "grid/terrain.h"

static void canal_image_split_layers(int rel_image_id, int &layer_base, int &connection) {
    layer_base = 0;
    connection = rel_image_id;
    if (connection >= building_irrigation_ditch::image_set::IMAGE_FULL_OFFSET) {
        layer_base += building_irrigation_ditch::image_set::IMAGE_FULL_OFFSET;
        connection -= building_irrigation_ditch::image_set::IMAGE_FULL_OFFSET;
    }
    if ((connection >= 15 && connection <= 16) || (connection >= 42 && connection <= 43)) {
        return;
    }
    if (connection >= IMAGE_CANAL_FLOODPLAIN_OFFSET) {
        layer_base += IMAGE_CANAL_FLOODPLAIN_OFFSET;
        connection -= IMAGE_CANAL_FLOODPLAIN_OFFSET;
    }
}

static bool canal_road_neighbor(tile2i tile, int gate_orientation) {
    if (map_terrain_is(tile, TERRAIN_ROAD)) {
        return true;
    }
    if (!map_terrain_is(tile, TERRAIN_BUILDING)) {
        return false;
    }
    building* b = city_buildings().at(tile);
    if (b->type == BUILDING_MUD_GATEHOUSE && b->orientation == gate_orientation) {
        return true;
    }
    if (b->type == BUILDING_GRANARY && map_routing_citizen_is_road(tile)) {
        return true;
    }
    return false;
}

static bool canal_network_neighbor(tile2i tile, int direction) {
    if (map_terrain_is(tile, TERRAIN_CANAL)) {
        return true;
    }
    if (map_terrain_is(tile, TERRAIN_BUILDING)) {
        building* b = city_buildings().at(tile);
        if (b->type == BUILDING_WATER_LIFT) {
            const int lift_direction_binary = b->orientation % 2;
            const int canal_direction_binary = (direction / 2) % 2;
            return lift_direction_binary == canal_direction_binary;
        }
    }
    return map_terrain_is(tile, TERRAIN_WATER);
}

static bool canal_is_straight_segment(tile2i tile) {
    const bool cx = canal_network_neighbor(tile.shifted(1, 0), 2)
        || canal_network_neighbor(tile.shifted(-1, 0), 6);
    const bool cy = canal_network_neighbor(tile.shifted(0, 1), 4)
        || canal_network_neighbor(tile.shifted(0, -1), 0);
    return (cx && !cy) || (cy && !cx);
}

bool map_can_place_road_under_canal(tile2i tile) {
    return canal_is_straight_segment(tile);
}

bool map_can_place_canal_on_road(tile2i tile) {
    if (map_terrain_is(tile, TERRAIN_DIKE)) {
        return false;
    }

    const bool road_x = canal_road_neighbor(tile.shifted(1, 0), 2)
        || canal_road_neighbor(tile.shifted(-1, 0), 2);
    const bool road_y = canal_road_neighbor(tile.shifted(0, -1), 1)
        || canal_road_neighbor(tile.shifted(0, 1), 1);
    return (road_x && !road_y) || (road_y && !road_x);
}

int map_get_canal_with_road_image(int grid_offset) {
    int water_start_image = building_irrigation_ditch::images().begin;
    int layer_base = 0;
    int connection = 0;
    canal_image_split_layers(map_image_at(grid_offset) - water_start_image, layer_base, connection);

    int mapped = 8;
    switch (connection) {
    case 2:
        mapped = 8;
        break;
    case 17:
        mapped = 23;
        break;
    case 3:
        mapped = 9;
        break;
    case 18:
        mapped = 24;
        break;
    case 0:
    case 1:
    case 8:
    case 9:
    case 15:
    case 16:
    case 23:
    case 24:
        mapped = connection;
        break;
    default:
        mapped = 8;
        break;
    }
    return layer_base + mapped;
}

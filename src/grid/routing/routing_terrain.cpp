#include "routing_terrain.h"

#include "building/building.h"
#include "building/monuments.h"
#include "core/direction.h"
#include "core/profiler.h"
#include "core/svector.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/view/view.h"
#include "grid/building.h"
#include "grid/image.h"
#include "grid/property.h"
#include "grid/random.h"
#include "grid/sprite.h"
#include "grid/terrain.h"
#include "grid/water.h"
#include "routing_grids.h"
#include "routing.h"
#include "scenario/map.h"
#include "figure/route.h"
#include "city/city_buildings.h"
#include "js/js_game.h"
#include <array>
#include <cstdlib>

struct building_penalty {
    e_building_type type = BUILDING_NONE;
    int penalty = - 1;
};

template<>
struct stable_array_max_elements<building_penalty> {
    enum { max_elements = BUILDING_MAX };
};

template<>
struct std::hash<building_penalty> {
    [[nodiscard]] size_t operator()(const building_penalty &bp) const noexcept {
        return bp.type;
    }
};
ANK_CONFIG_STRUCT(building_penalty, type, penalty)

stable_array<building_penalty> routing_amphibia_buildings;
stable_array<building_penalty> routing_citizen_buildings;
stable_array<building_penalty> routing_noncitizen_buildings;

void ANK_REGISTER_CONFIG_ITERATOR(config_load_routing_config) {
    routing_amphibia_buildings.fill({ BUILDING_NONE, -1 });
    routing_citizen_buildings.fill({ BUILDING_NONE, -1 });
    routing_noncitizen_buildings.fill({ BUILDING_NONE, 0 }); // why it  0

    g_config_arch.r("routing_amphibia", routing_amphibia_buildings);
    g_config_arch.r("routing_citizen", routing_citizen_buildings);
    g_config_arch.r("routing_noncitizen", routing_noncitizen_buildings);
}

static int get_land_type_citizen_building(int grid_offset) {
    auto base = building_at(grid_offset);
    auto b = base->dcast();
    int land_result;
    if (b->get_route_citizen_land_type(grid_offset, land_result)) {
        return land_result;
    }

    //case BUILDING_RESERVED_TRIUMPHAL_ARCH_56:
    //    if (b->orientation == 3) {
    //        switch (map_property_multi_tile_xy(grid_offset)) {
    //        case EDGE_X0Y1:
    //        case EDGE_X1Y1:
    //        case EDGE_X2Y1:
    //            return CITIZEN_0_ROAD;
    //        }
    //    } else {
    //        switch (map_property_multi_tile_xy(grid_offset)) {
    //        case EDGE_X1Y0:
    //        case EDGE_X1Y1:
    //        case EDGE_X1Y2:
    //            return CITIZEN_0_ROAD;
    //        }
    //    }
    //    break;

    return routing_citizen_buildings[base->type].penalty;
}
static int get_land_type_citizen_canal(int grid_offset) {
    return CITIZEN_N3_CANAL;
    //    int image_id = map_image_at(grid_offset) - image_id_from_group(GROUP_BUILDING_AQUEDUCT);
    //    if (image_id <= 3)
    //        return CITIZEN_N3_AQUEDUCT;
    //    else if (image_id <= 7)
    //        return CITIZEN_N1_BLOCKED;
    //    else if (image_id <= 9)
    //        return CITIZEN_N3_AQUEDUCT;
    //    else if (image_id <= 14)
    //        return CITIZEN_N1_BLOCKED;
    //    else if (image_id <= 18)
    //        return CITIZEN_N3_AQUEDUCT;
    //    else if (image_id <= 22)
    //        return CITIZEN_N1_BLOCKED;
    //    else if (image_id <= 24)
    //        return CITIZEN_N3_AQUEDUCT;
    //    else {
    //        return CITIZEN_N1_BLOCKED;
    //    }
}

int map_routing_land_penalty_amphibia(int grid_offset) {
    building* b = building_at(grid_offset);
    return routing_amphibia_buildings[b->type].penalty;
}

static int get_land_type_noncitizen(int grid_offset) {
    building *b = building_at(grid_offset);
    return routing_amphibia_buildings[b->type].penalty;
}

static bool is_water_tile(int grid_offset) {
    // Check if tile is water (either regular water or flooded floodplain)
    // Must have TERRAIN_WATER flag - if it's floodplain without water, it's dry land
    return map_terrain_is(grid_offset, TERRAIN_WATER);
}

static int is_surrounded_by_water(int grid_offset) {
    // All four cardinal neighbors must be water tiles
    // This prevents boats from navigating on floodplain edges where land is adjacent
    return is_water_tile(grid_offset + GRID_OFFSET(0, -1))
           && is_water_tile(grid_offset + GRID_OFFSET(-1, 0))
           && is_water_tile(grid_offset + GRID_OFFSET(1, 0))
           && is_water_tile(grid_offset + GRID_OFFSET(0, 1));
}

static bool has_land_corner(int grid_offset) {
    // Check if any diagonal neighbor is land (not water)
    // This prevents boats from navigating through land corners
    return !is_water_tile(grid_offset + GRID_OFFSET(1, -1))
           || !is_water_tile(grid_offset + GRID_OFFSET(1, 1))
           || !is_water_tile(grid_offset + GRID_OFFSET(-1, 1))
           || !is_water_tile(grid_offset + GRID_OFFSET(-1, -1));
}

static int is_wall_tile(int grid_offset) {
    return map_terrain_is(grid_offset, TERRAIN_WALL_OR_GATEHOUSE) ? 1 : 0;
}

static int count_adjacent_wall_tiles(int grid_offset) {
    int adjacent = 0;
    switch (city_view_orientation()) {
    case DIR_0_TOP_RIGHT:
        adjacent += is_wall_tile(grid_offset + GRID_OFFSET(0, 1));
        adjacent += is_wall_tile(grid_offset + GRID_OFFSET(1, 1));
        adjacent += is_wall_tile(grid_offset + GRID_OFFSET(1, 0));
        break;
    case DIR_2_BOTTOM_RIGHT:
        adjacent += is_wall_tile(grid_offset + GRID_OFFSET(0, 1));
        adjacent += is_wall_tile(grid_offset + GRID_OFFSET(-1, 1));
        adjacent += is_wall_tile(grid_offset + GRID_OFFSET(-1, 0));
        break;
    case DIR_4_BOTTOM_LEFT:
        adjacent += is_wall_tile(grid_offset + GRID_OFFSET(0, -1));
        adjacent += is_wall_tile(grid_offset + GRID_OFFSET(-1, -1));
        adjacent += is_wall_tile(grid_offset + GRID_OFFSET(-1, 0));
        break;
    case DIR_6_TOP_LEFT:
        adjacent += is_wall_tile(grid_offset + GRID_OFFSET(0, -1));
        adjacent += is_wall_tile(grid_offset + GRID_OFFSET(1, -1));
        adjacent += is_wall_tile(grid_offset + GRID_OFFSET(1, 0));
        break;
    }
    return adjacent;
}

static bool fix_incorrect_buildings(int grid_offset) {
    // shouldn't happen...?
    if (!map_building_at(grid_offset)) {
        // set caches automatically to fix this?
        //        map_grid_set(&terrain_land_citizen, grid_offset, CITIZEN_4_CLEAR_TERRAIN);
        //        map_grid_set(&terrain_land_noncitizen, grid_offset, NONCITIZEN_0_PASSABLE);

        map_terrain_remove(grid_offset, TERRAIN_BUILDING);
        map_image_set(grid_offset, (map_random_get(grid_offset) & 7) + image_id_from_group(GROUP_TERRAIN_EMPTY_LAND));
        map_property_mark_draw_tile(grid_offset);
        map_property_set_multi_tile_size(grid_offset, 1);
        return true;
    }
    return false;
}

int map_routing_tile_check(int routing_type, int grid_offset) {
    int terrain = map_terrain_get(grid_offset);
    int x = MAP_X(grid_offset);
    int y = MAP_Y(grid_offset);
    switch (routing_type) {
    case ROUTING_TYPE_CITIZEN: {
            // Exclude river shoreline tiles from citizen pathfinding, unless there's a road
            if ((terrain & TERRAIN_SHORE) && !(terrain & TERRAIN_ROAD)) {
                return CITIZEN_N1_BLOCKED;
            }

            if (!!(terrain & TERRAIN_ROAD) && !(terrain & TERRAIN_WATER)) {
                return CITIZEN_0_ROAD;
            }

            if (!!(terrain & TERRAIN_FERRY_ROUTE) && !!(terrain & TERRAIN_WATER)) {
                return CITIZEN_0_ROAD;
            }

            // Block pure water tiles (lakes, rivers) - citizens cannot build roads through water
            if (!!(terrain & TERRAIN_WATER) && !(terrain & TERRAIN_FERRY_ROUTE)) {
                return CITIZEN_N1_BLOCKED;
            }

            if (terrain & (TERRAIN_RUBBLE | TERRAIN_ACCESS_RAMP | TERRAIN_GARDEN | TERRAIN_MARSHLAND | TERRAIN_FLOODPLAIN | TERRAIN_TREE)) {// TODO?
                return CITIZEN_2_PASSABLE_TERRAIN;
            }

            if (terrain & (TERRAIN_BUILDING | TERRAIN_GATEHOUSE)) {
                if (fix_incorrect_buildings(grid_offset)) {
                    return CITIZEN_4_CLEAR_TERRAIN;
                } else {
                    return get_land_type_citizen_building(grid_offset);
                }
            }

            if (terrain & TERRAIN_CANAL) {
                return get_land_type_citizen_canal(grid_offset);
            }

            if (terrain & TERRAIN_NOT_CLEAR) {
                return CITIZEN_N1_BLOCKED;
            }

            return CITIZEN_4_CLEAR_TERRAIN;
        }

    case ROUTING_TYPE_NONCITIZEN: {
            if (terrain & TERRAIN_GATEHOUSE) {
                return NONCITIZEN_4_GATEHOUSE;
            }

            if (terrain & TERRAIN_ROAD) {
                return NONCITIZEN_0_PASSABLE;
            }

            if (terrain & (TERRAIN_GARDEN | TERRAIN_ACCESS_RAMP | TERRAIN_RUBBLE | TERRAIN_MARSHLAND)) {
                return NONCITIZEN_2_CLEARABLE;
            }

            if (terrain & TERRAIN_BUILDING) {
                return get_land_type_noncitizen(grid_offset);
            }

            if (terrain & TERRAIN_CANAL) {
                return NONCITIZEN_2_CLEARABLE;
            }

            if (terrain & TERRAIN_WALL) {
                return NONCITIZEN_3_WALL;
            }

            if (terrain & TERRAIN_NOT_CLEAR) {
                return NONCITIZEN_N1_BLOCKED;
            }

            return NONCITIZEN_0_PASSABLE;
        }

    case ROUTING_TYPE_AMPHIBIA: {
            if (terrain & TERRAIN_GATEHOUSE) {
                return AMPHIBIA_1_BUILDING;
            }

            if (terrain & (TERRAIN_GARDEN | TERRAIN_ACCESS_RAMP | TERRAIN_RUBBLE | TERRAIN_CANAL | TERRAIN_MARSHLAND)) {
                return AMPHIBIA_0_PASSABLE;
            }

            if (terrain & TERRAIN_ROAD) {
                return AMPHIBIA_0_PASSABLE;
            }

            if (terrain & (TERRAIN_WALL | TERRAIN_ROCK | TERRAIN_TREE)) {
                return AMPHIBIA_N1_BLOCKED;
            }

            if (terrain & TERRAIN_BUILDING) {
                return map_routing_land_penalty_amphibia(grid_offset);
            }

            if (terrain & TERRAIN_WATER && is_surrounded_by_water(grid_offset)) {
                if (x > 0 && x < scenario_map_data()->width - 1 && y > 0 && y < scenario_map_data()->height - 1) {
                    switch (map_sprite_animation_at(grid_offset)) {
                    case 5:
                    case 6: // low bridge middle section
                        return AMPHIBIA_N3_LOW_BRIDGE;
                    case 13: // ship bridge pillar
                        return AMPHIBIA_N1_BLOCKED;
                    default:
                        return AMPHIBIA_0_PASSABLE;
                    }
                } else
                    return AMPHIBIA_N2_MAP_EDGE;
            }

            return AMPHIBIA_0_PASSABLE;
        }

    case ROUTING_TYPE_WATER: {
            if ((terrain & TERRAIN_WATER) && !(terrain & TERRAIN_FLOODPLAIN) && is_surrounded_by_water(grid_offset) && !has_land_corner(grid_offset)) {
                if (x > 0 && x < scenario_map_data()->width - 1 && y > 0 && y < scenario_map_data()->height - 1) {
                    switch (map_sprite_animation_at(grid_offset)) {
                    case 5:
                    case 6: // low bridge middle section
                        return WATER_N3_LOW_BRIDGE;

                    case 13: // ship bridge pillar
                        return WATER_N1_BLOCKED;

                    default:
                        return WATER_0_PASSABLE;
                    }
                }

                return WATER_N2_MAP_EDGE;
            }

            return WATER_N1_BLOCKED;
        }

    case ROUTING_TYPE_WALLS: {
            if (terrain & TERRAIN_WALL) {
                if (count_adjacent_wall_tiles(grid_offset) == 3)
                    return WALL_0_PASSABLE;

                return WALL_N1_BLOCKED;
            }

            if (map_terrain_is(grid_offset, TERRAIN_GATEHOUSE)) {
                return WALL_0_PASSABLE;
            }

            return WALL_N1_BLOCKED;
        }
    }

    // fallback case
    return NO_VALID_ROUTING_CHECK_RESULT;
}

void map_routing_update_land_citizen(void) {
    OZZY_PROFILER_FUNCTION();
    map_grid_fill(routing_land_citizen, -1);
    int grid_offset = scenario_map_data()->start_offset;
    for (int y = 0; y < scenario_map_data()->height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < scenario_map_data()->width; x++, grid_offset++) {
            map_grid_set(routing_land_citizen, grid_offset, map_routing_tile_check(ROUTING_TYPE_CITIZEN, grid_offset));
            //            int terrain = map_terrain_get(grid_offset);
            //            if (terrain & TERRAIN_ROAD && !(terrain & TERRAIN_WATER)) {
            //                map_grid_set(&terrain_land_citizen, grid_offset, CITIZEN_0_ROAD);
            //            } else if (terrain & (TERRAIN_RUBBLE | TERRAIN_ACCESS_RAMP | TERRAIN_GARDEN | TERRAIN_REEDS |
            //            TERRAIN_FLOODPLAIN)) { // TODO?
            //                map_grid_set(&terrain_land_citizen, grid_offset, CITIZEN_2_PASSABLE_TERRAIN);
            //            } else if (terrain & (TERRAIN_BUILDING | TERRAIN_GATEHOUSE)) {
            //                if (!map_building_at(grid_offset)) {
            //                    // shouldn't happen
            //                    map_grid_set(&terrain_land_noncitizen, grid_offset, CITIZEN_4_CLEAR_TERRAIN); // BUG:
            //                    should be citizen grid? map_terrain_remove(grid_offset, TERRAIN_BUILDING);
            //                    map_image_set(grid_offset, (map_random_get(grid_offset) & 7) +
            //                                               image_id_from_group(GROUP_TERRAIN_EMPTY_LAND));
            //                    map_property_mark_draw_tile(grid_offset);
            //                    map_property_set_multi_tile_size(grid_offset, 1);
            //                    continue;
            //                }
            //                map_grid_set(&terrain_land_citizen, grid_offset,
            //                get_land_type_citizen_building(grid_offset));
            //            } else if (terrain & TERRAIN_AQUEDUCT) {
            //                map_grid_set(&terrain_land_citizen, grid_offset,
            //                get_land_type_citizen_aqueduct(grid_offset));
            //            } else if (terrain & TERRAIN_NOT_CLEAR) {
            //                map_grid_set(&terrain_land_citizen, grid_offset, CITIZEN_N1_BLOCKED);
            //            } else {
            //                map_grid_set(&terrain_land_citizen, grid_offset, CITIZEN_4_CLEAR_TERRAIN);
            //            }
        }
    }
}

static void map_routing_update_amphibia() {
    OZZY_PROFILER_FUNCTION();
    map_grid_fill(routing_land_amphibia, -1);
    int grid_offset = scenario_map_data()->start_offset;

    const int mheight = scenario_map_data()->height;
    const int mwidth = scenario_map_data()->width;
    const int mborder_size = scenario_map_data()->border_size;

    for (int y = 0; y < mheight; y++, grid_offset += mborder_size) {
        for (int x = 0; x < mwidth; x++, grid_offset++) {
            map_grid_set(routing_land_amphibia, grid_offset, map_routing_tile_check(ROUTING_TYPE_AMPHIBIA, grid_offset));
        }
    }
}

static void map_routing_update_land_noncitizen() {
    OZZY_PROFILER_FUNCTION();
    map_grid_fill(routing_land_noncitizen, -1);
    int grid_offset = scenario_map_data()->start_offset;

    const int mheight = scenario_map_data()->height;
    const int mwidth = scenario_map_data()->width;
    const int mborder_size = scenario_map_data()->border_size;
    for (int y = 0; y < mheight; y++, grid_offset += mborder_size) {
        for (int x = 0; x < mwidth; x++, grid_offset++) {
            map_grid_set(routing_land_noncitizen, grid_offset, map_routing_tile_check(ROUTING_TYPE_NONCITIZEN, grid_offset));
            //            int terrain = map_terrain_get(grid_offset);
            //            if (terrain & TERRAIN_GATEHOUSE) {
            //                map_grid_set(&terrain_land_noncitizen, grid_offset, NONCITIZEN_4_GATEHOUSE);
            //            } else if (terrain & TERRAIN_ROAD) {
            //                map_grid_set(&terrain_land_noncitizen, grid_offset, NONCITIZEN_0_PASSABLE);
            //            } else if (terrain & (TERRAIN_GARDEN | TERRAIN_ACCESS_RAMP | TERRAIN_RUBBLE)) {
            //                map_grid_set(&terrain_land_noncitizen, grid_offset, NONCITIZEN_2_CLEARABLE);
            //            } else if (terrain & TERRAIN_BUILDING) {
            //                map_grid_set(&terrain_land_noncitizen, grid_offset,
            //                get_land_type_noncitizen(grid_offset));
            //            } else if (terrain & TERRAIN_AQUEDUCT) {
            //                map_grid_set(&terrain_land_noncitizen, grid_offset, NONCITIZEN_2_CLEARABLE);
            //            } else if (terrain & TERRAIN_WALL) {
            //                map_grid_set(&terrain_land_noncitizen, grid_offset, NONCITIZEN_3_WALL);
            //            } else if (terrain & TERRAIN_NOT_CLEAR) {
            //                map_grid_set(&terrain_land_noncitizen, grid_offset, NONCITIZEN_N1_BLOCKED);
            //            } else {
            //                map_grid_set(&terrain_land_noncitizen, grid_offset, NONCITIZEN_0_PASSABLE);
            //            }
        }
    }
}

void map_routing_update_land() {
    OZZY_PROFILER_FUNCTION();
    map_routing_update_land_citizen();
    map_routing_update_land_noncitizen();
    map_routing_update_amphibia();
}

void map_routing_update_ferry_routes() {
    foreach_river_tile([] (int offset) {
        if (map_terrain_is(offset, TERRAIN_WATER)
            && map_terrain_is(offset, TERRAIN_FERRY_ROUTE)
            && !map_terrain_is(offset, TERRAIN_BUILDING)) {
            map_terrain_remove(offset, TERRAIN_FERRY_ROUTE);
        }
    });

    svector<building *, 64> ferries;
    buildings_get(ferries, BUILDING_FERRY);

    using path_points = std::pair<tile2i, tile2i>;
    auto mark_path = [] (path_points &ppoints) {
        std::array<uint8_t, 500> path_data;
        map_routing_calculate_distances_water_boat(ppoints.first);
        int path_length = map_routing_get_path_on_water(path_data.data(), ppoints.second, false);

        map_terrain_add(ppoints.first.grid_offset(), TERRAIN_FERRY_ROUTE);
        map_terrain_add(ppoints.second.grid_offset(), TERRAIN_FERRY_ROUTE);
        if (path_length > 0) {
            auto path = make_span(path_data.data(), path_length);

            int grid_offset = ppoints.first.grid_offset();
            for (const auto &dir : path) {
                map_terrain_add(grid_offset, TERRAIN_FERRY_ROUTE);
                map_routing_adjust_tile_in_direction(dir, ppoints.first, grid_offset);
            }
        }
    };

    for (auto f1 = ferries.begin(); f1 != ferries.end(); ++f1) {
        for (auto f2 = f1 + 1; f2 != ferries.end(); ++f2) {
            // Check if ferries are close enough (difference in x or y not more than 2 tiles)
            tile2i tile1 = (*f1)->tile;
            tile2i tile2 = (*f2)->tile;
            int dx = std::abs(tile1.x() - tile2.x());
            int dy = std::abs(tile1.y() - tile2.y());

            // Only connect ferries that are close (difference in x or y <= 2)
            if (dx > 4 && dy > 4) {
                continue;
            }

            water_access_tiles fpoints_begin = map_water_get_access_points(**f1, (*f1)->dcast()->get_orientation(), 1);
            water_access_tiles fpoints_end = map_water_get_access_points(**f2, (*f2)->dcast()->get_orientation(), 1);

            path_points possible_paths[] = {
                {fpoints_begin.point_a, fpoints_end.point_a},
                {fpoints_begin.point_a, fpoints_end.point_b},
                {fpoints_begin.point_b, fpoints_end.point_a},
                {fpoints_begin.point_b, fpoints_end.point_b},
            };

            for (auto &path : possible_paths) {
                mark_path(path);
            }
        }
    }
}

void map_routing_update_water(void) {
    map_grid_fill(routing_tiles_water, -1);
    int grid_offset = scenario_map_data()->start_offset;
    for (int y = 0; y < scenario_map_data()->height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < scenario_map_data()->width; x++, grid_offset++) {
            map_grid_set(routing_tiles_water, grid_offset, map_routing_tile_check(ROUTING_TYPE_WATER, grid_offset));
            //            if (map_terrain_is(grid_offset, TERRAIN_WATER) && is_surrounded_by_water(grid_offset)) {
            //                if (x > 0 && x < scenario_map_data()->width - 1 &&
            //                    y > 0 && y < scenario_map_data()->height - 1) {
            //                    switch (map_sprite_animation_at(grid_offset)) {
            //                        case 5:
            //                        case 6: // low bridge middle section
            //                            map_grid_set(&terrain_water, grid_offset, WATER_N3_LOW_BRIDGE);
            //                            break;
            //                        case 13: // ship bridge pillar
            //                            map_grid_set(&terrain_water, grid_offset, WATER_N1_BLOCKED);
            //                            break;
            //                        default:
            //                            map_grid_set(&terrain_water, grid_offset, WATER_0_PASSABLE);
            //                            break;
            //                    }
            //                } else {
            //                    map_grid_set(&terrain_water, grid_offset, WATER_N2_MAP_EDGE);
            //                }
            //            } else {
            //                map_grid_set(&terrain_water, grid_offset, WATER_N1_BLOCKED);
            //            }
        }
    }
}
void map_routing_update_walls(void) {
    map_grid_fill(routing_tiles_walls, -1);
    int grid_offset = scenario_map_data()->start_offset;
    for (int y = 0; y < scenario_map_data()->height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < scenario_map_data()->width; x++, grid_offset++) {
            map_grid_set(routing_tiles_walls, grid_offset, map_routing_tile_check(ROUTING_TYPE_WALLS, grid_offset));
            //            if (map_terrain_is(grid_offset, TERRAIN_WALL)) {
            //                if (count_adjacent_wall_tiles(grid_offset) == 3) {
            //                    map_grid_set(&terrain_walls, grid_offset, WALL_0_PASSABLE);
            //                } else {
            //                    map_grid_set(&terrain_walls, grid_offset, WALL_N1_BLOCKED);
            //                }
            //            } else if (map_terrain_is(grid_offset, TERRAIN_GATEHOUSE)) {
            //                map_grid_set(&terrain_walls, grid_offset, WALL_0_PASSABLE);
            //            } else {
            //                map_grid_set(&terrain_walls, grid_offset, WALL_N1_BLOCKED);
            //            }
        }
    }
}

void map_routing_update_all() {
    map_routing_update_land();
    map_routing_update_water();
    map_routing_update_walls();
    map_routing_update_amphibia();
}

/////////////

bool map_routing_passable_by_usage(int terrain_usage, int grid_offset) {
    switch (terrain_usage) {
    case TERRAIN_USAGE_ANY:
        return true;
    case TERRAIN_USAGE_ROADS:
        return map_grid_get(routing_land_citizen, grid_offset) == CITIZEN_0_ROAD;
    case TERRAIN_USAGE_ENEMY:
        return map_grid_get(routing_land_noncitizen, grid_offset) >= NONCITIZEN_0_PASSABLE;
    case TERRAIN_USAGE_PREFER_ROADS:
        return map_grid_get(routing_land_citizen, grid_offset) >= CITIZEN_0_ROAD;
    case TERRAIN_USAGE_WALLS:
        return map_grid_get(routing_tiles_walls, grid_offset) == WALL_0_PASSABLE;
    case TERRAIN_USAGE_ANIMAL:
        return map_grid_get(routing_land_noncitizen, grid_offset) >= NONCITIZEN_0_PASSABLE;
    case TERRAIN_USAGE_AMPHIBIA:
        return map_grid_get(routing_land_amphibia, grid_offset) >= AMPHIBIA_0_PASSABLE;
    }
    assert(false && "uknown terrain usage option");
    return false;
}

bool map_routing_amphibia_is_passable_building(int grid_offset) {
    return false;
}

int map_routing_is_wall_passable(int grid_offset) {
    return map_grid_get(routing_tiles_walls, grid_offset) == WALL_0_PASSABLE;
}

static bool wall_tile_in_radius(int x, int y, int radius, int* x_wall, int* y_wall) {
    int size = 1;
    grid_area area = map_grid_get_area(tile2i(x, y), size, radius);

    for (int yy = area.tmin.y(), endy = area.tmax.y(); yy <= endy; yy++) {
        for (int xx = area.tmin.x(), endx = area.tmax.x(); xx <= endx; xx++) {
            if (map_routing_is_wall_passable(MAP_OFFSET(xx, yy))) {
                *x_wall = xx;
                *y_wall = yy;
                return true;
            }
        }
    }
    return false;
}

int map_routing_wall_tile_in_radius(int x, int y, int radius, int* x_wall, int* y_wall) {
    for (int i = 1; i <= radius; i++) {
        if (wall_tile_in_radius(x, y, i, x_wall, y_wall))
            return 1;
    }
    return 0;
}

int map_routing_citizen_is_passable(int grid_offset) {
    return map_grid_get(routing_land_citizen, grid_offset) == CITIZEN_0_ROAD
           || map_grid_get(routing_land_citizen, grid_offset) == CITIZEN_2_PASSABLE_TERRAIN;
}
int map_routing_citizen_is_road(int grid_offset) {
    return map_grid_get(routing_land_citizen, grid_offset) == CITIZEN_0_ROAD;
}
int map_routing_citizen_is_passable_terrain(int grid_offset) {
    return map_grid_get(routing_land_citizen, grid_offset) == CITIZEN_2_PASSABLE_TERRAIN;
}
int map_routing_noncitizen_is_passable(int grid_offset) {
    return map_grid_get(routing_land_noncitizen, grid_offset) >= NONCITIZEN_0_PASSABLE;
}
int map_routing_is_destroyable(int grid_offset) {
    return map_grid_get(routing_land_noncitizen, grid_offset) > NONCITIZEN_0_PASSABLE
           && map_grid_get(routing_land_noncitizen, grid_offset) != NONCITIZEN_5_FORT;
}
int map_routing_get_destroyable(int grid_offset) {
    switch (map_grid_get(routing_land_noncitizen, grid_offset)) {
    case NONCITIZEN_1_BUILDING:
        return DESTROYABLE_BUILDING;
    case NONCITIZEN_2_CLEARABLE:
        return DESTROYABLE_CANALS_GARDEN;
    case NONCITIZEN_3_WALL:
        return DESTROYABLE_WALL;
    case NONCITIZEN_4_GATEHOUSE:
        return DESTROYABLE_GATEHOUSE;
    default:
        return DESTROYABLE_NONE;
    }
}

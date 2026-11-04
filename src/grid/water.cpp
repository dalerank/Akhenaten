#include "water.h"

#include "building/building.h"
#include "graphics/view/view.h"
#include "grid/building.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/image.h"
#include "grid/point.h"
#include "grid/property.h"
#include "grid/ring.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "grid/routing/routing.h"
#include "scenario/map.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <cfloat>

tile_cache river_tiles_cache;
tile_cache g_river_shore;
tile_cache &river_tiles() { return river_tiles_cache; }

bool map_water_is_point_inside(tile2i tile) {
    int map_height = scenario_map_data()->height;
    int map_width = scenario_map_data()->width;
    return tile.x() < map_width && tile.y() < map_height;
}

void map_water_cache_river_tiles() {
    river_tiles_cache.clear();

    int grid_offset = scenario_map_data()->start_offset;
    int map_height = scenario_map_data()->height;
    int border_size = scenario_map_data()->border_size;
    int map_width = scenario_map_data()->width;
    for (int y = 0; y < map_height; y++, grid_offset += border_size) {
        for (int x = 0; x < map_width; x++, grid_offset++) {
            if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN + TERRAIN_WATER)) {
                river_tiles_cache.push_back(grid_offset);
            }
        }
    }
}

void map_water_update_docking_points(building &b, int orientation, int offset) {
    tile2i river_entry = scenario_map_river_entry();
    if (!river_entry.valid()) {
        b.has_water_access = false;
        b.has_open_water_access = false;
        return;
    }

    map_routing_calculate_distances_water_boat(river_entry);

    bool found = map_terrain_is_adjacent_to_open_water(b.tile, b.size);
    if (found) {
        b.has_water_access = 1;
    }
    b.has_open_water_access = found;

    water_access_tiles ppoints;
    if (found) {
        ppoints = map_water_get_access_points(b, b.dcast()->get_orientation(), offset);
    }
    b.dcast()->set_water_access_tiles(ppoints);
}

water_access_tiles map_water_get_access_points(const building &b, int orientation, int offset) {
    const auto &params = building_static_params::get(b.type);
    if (!params.needs.water_access) {
        return {{-1, -1},{-1, -1}};
    }

    water_access_tiles result;
    const int bsize = params.building_size;
    tile2i origin = b.tile;
    switch (orientation) {
    case 0:
        result.point_a = origin.shifted(1, -offset);
        result.point_b = origin.shifted(0, -offset);
        break;
    case 1:
        result.point_a = origin.shifted(bsize + (offset - 1), 0);
        result.point_b = origin.shifted(bsize + (offset - 1), 1);
        break;
    case 2:
        result.point_a = origin.shifted(0, bsize + (offset - 1));
        result.point_b = origin.shifted(1, bsize + (offset - 1));
        break;
    case 3:
        result.point_a = origin.shifted(-offset, 0);
        result.point_b = origin.shifted(-offset, 1);
        break;
    }

    return result;
}

void map_water_add_building(int building_id, tile2i tile, int size, int image_id, int ext_terrain_flags) {
    if (!map_grid_is_inside(tile, size)) {
        return;
    }

    tile2i leftmost;
    switch (g_camera.orientation) {
    case DIR_0_TOP_RIGHT:
        leftmost.set(0, size - 1);
        break;
    case DIR_2_BOTTOM_RIGHT:
        leftmost.set(0, 0);
        break;
    case DIR_4_BOTTOM_LEFT:
        leftmost.set(size - 1, 0);
        break;
    case DIR_6_TOP_LEFT:
        leftmost.set(size - 1, size - 1);
        break;
    default:
        return;
    }
    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            int grid_offset = MAP_OFFSET(tile.x() + dx, tile.y() + dy);
            map_terrain_add(grid_offset, TERRAIN_BUILDING|ext_terrain_flags);
            if (!map_terrain_is(grid_offset, TERRAIN_WATER)) {
                map_terrain_remove(grid_offset, TERRAIN_CLEARABLE);
                map_terrain_add(grid_offset, TERRAIN_BUILDING);
            }
            map_building_set(grid_offset, building_id);
            map_property_clear_constructing(grid_offset);
            map_property_set_multi_tile_size(grid_offset, size);
            map_image_set(grid_offset, image_id);
            map_property_set_multi_tile_xy(grid_offset, dx, dy, dx == leftmost.x() && dy == leftmost.y());
        }
    }
}

static int blocked_land_terrain(void) {
    return TERRAIN_TREE | TERRAIN_ROCK | TERRAIN_WATER | TERRAIN_BUILDING | TERRAIN_SHRUB | TERRAIN_GARDEN
           | TERRAIN_ROAD | TERRAIN_ELEVATION | TERRAIN_RUBBLE;
}

void map_water_rebuild_shores() {
    foreach_river_tile([&] (int tile_offset) {
        tile2i tile(tile_offset);
        grid_area area = map_grid_get_area(tile, 1, 1);

        bool ground_aside = false;
        int ground_tiles_num = 0;
        int water_tiles_num = 0;
        map_grid_area_foreach(area, [&] (tile2i t) {
            if (map_terrain_is(t, TERRAIN_WATER|TERRAIN_FLOODPLAIN)) {
                water_tiles_num++;
            } else {
                ground_aside = true;
                ground_tiles_num++;
            }
        });

        if (ground_aside) {
            map_terrain_add(tile_offset, TERRAIN_SHORE);
        }
    });
}

shore_orientation map_shore_determine_orientation(tile2i tile, int size, bool adjust_xy, bool adjacent, int shore_terrain) {
    int x = tile.x();
    int y = tile.y();

    if (adjust_xy) {
        switch (g_camera.orientation) {
        case DIR_0_TOP_RIGHT:
            break;

        case DIR_2_BOTTOM_RIGHT:
            x -= size - 1;
            break;

        case DIR_6_TOP_LEFT:
            y -= size - 1;
            break;

        case DIR_4_BOTTOM_LEFT:
            x -= size - 1;
            y -= size - 1;
            break;
        }
    }

    if (!map_grid_is_inside(tile2i(x, y), size)) {
        return { false, 0 };
    }

    // actually... check also the bordering blocks on each side.
    size += 2;
    x--;
    y--;

    // fill in tile cache first
    struct water_tiles_t {
        int _size;
        std::array<int, 32> _data = { 0 };
        water_tiles_t(int size) : _size(size) {}
        int &at(int row, int column) { return _data[row * _size + column]; }
    } water_tiles(size);
    assert((size *size) < 36);

    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            water_tiles.at(row, column) = map_terrain_is(MAP_OFFSET(x + column, y + row), shore_terrain);
        }
    }

    // check -- north
    bool matches = true;
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            if ((water_tiles.at(row, column) && row > (!adjacent) && (column > 0 && column < size - 1 && row < size - 1))
                || (!water_tiles.at(row, column) && row <= (!adjacent) && (column >= adjacent && column <= size - (1 + adjacent))))
                matches = false;
        }
    }

    if (matches) {
        return {true, 0};
    }

    // check -- east
    matches = true;
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            if ((water_tiles.at(row, column) == true && column < size - (1 + !adjacent) && (row > 0 && row < size - 1 && column > 0))
                || (water_tiles.at(row, column) == false && column >= size - (1 + !adjacent) && (row >= adjacent && row <= size - (1 + adjacent))))
                matches = false;
        }
    }

    if (matches) {
        return {true, 1};
    }

    // check -- south
    matches = true;
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            if ((water_tiles.at(row, column) == true && row < size - (1 + !adjacent) && (column > 0 && column < size - 1 && row > 0))
                || (water_tiles.at(row, column) == false && row >= size - (1 + !adjacent) && (column >= adjacent && column <= size - (1 + adjacent))))
                matches = false;
        }
    }

    if (matches) {
        return {true, 2};
    }

    // check -- west
    matches = true;
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            if ((water_tiles.at(row, column) == true && column > (!adjacent) && (row > 0 && row < size - 1 && column < size - 1))
                || (water_tiles.at(row, column) == false && column <= (!adjacent) && (row >= adjacent && row <= size - (1 + adjacent))))
                matches = false;
        }
    }

    if (matches) {
        return {true, 3};
    }

    // no match.
    return {false, 0};
}

bool map_water_find_alternative_fishing_boat_tile(figure &boat, tile2i &tile) {
    if (map_figure_id_get(boat.tile) == boat.id) {
        return false;
    }

    for (int radius = 1; radius <= 5; radius++) {
        grid_area area = map_grid_get_area(boat.tile, 1, radius);
        for (int yy = area.tmin_y, endy = area.tmax_y; yy <= endy; yy++) {
            for (int xx = area.tmin_x, endx = area.tmax_x; xx <= endx; xx++) {
                int grid_offset = MAP_OFFSET(xx, yy);
                if (!map_has_figure_at(grid_offset) && map_terrain_is(grid_offset, TERRAIN_WATER)) {
                    map_point_store_result(tile2i(xx, yy), tile);
                    return true;
                }
            }
        }
    }
    return false;
}

water_dest map_water_find_shipwreck_tile(figure &wreck) {
    if (map_terrain_is(wreck.tile, TERRAIN_WATER) && map_figure_id_get(wreck.tile) == wreck.id) {
        return {false};
    }

    tile2i tile;
    for (int radius = 1; radius <= 5; radius++) {
        grid_area area = map_grid_get_area(wreck.tile, 1, radius);

        for (int yy = area.tmin_y, endy = area.tmax_y; yy <= endy; yy++) {
            for (int xx = area.tmin_x, endx = area.tmax_x; xx <= endx; xx++) {
                int grid_offset = MAP_OFFSET(xx, yy);
                if (!map_has_figure_at(grid_offset) || map_figure_id_get(grid_offset) == wreck.id) {
                    if (map_terrain_is(grid_offset, TERRAIN_WATER)
                        && map_terrain_is(MAP_OFFSET(xx, yy - 2), TERRAIN_WATER)
                        && map_terrain_is(MAP_OFFSET(xx, yy + 2), TERRAIN_WATER)
                        && map_terrain_is(MAP_OFFSET(xx - 2, yy), TERRAIN_WATER)
                        && map_terrain_is(MAP_OFFSET(xx + 2, yy), TERRAIN_WATER)) {
                        map_point_store_result(tile2i(xx, yy), tile);
                        return {true, 0, tile};
                    }
                }
            }
        }
    }
    return {false};
}

static int num_surrounding_water_tiles(int grid_offset) {
    int amount = 0;
    for (int i = 0; i < DIR_8_NONE; i++) {
        if (map_terrain_is(grid_offset + map_grid_direction_delta(i), TERRAIN_WATER))
            amount++;
    }
    return amount;
}

bool map_water_can_spawn_boat(tile2i tile, int size, tile2i &boat_tile) {
    int base_offset = tile.grid_offset();
    offsets_array offsets;
    map_grid_adjacent_offsets(size, offsets);
    for (const int& tile_delta: offsets) {
        int grid_offset = base_offset + tile_delta;
        if (map_terrain_is(grid_offset, TERRAIN_WATER|TERRAIN_DEEPWATER)) {
            if (!map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
                if (num_surrounding_water_tiles(grid_offset) >= 2) {
                    map_point_store_result(tile2i(grid_offset), boat_tile);
                    return true;
                }
            }
        }
    }
    return false;
}

// Chebyshev (king-move) distance from `tile` to the nearest non-water tile.
// Returns the ring distance r in [1, max_d], or max_d + 1 if no land within
// range. Off-map tiles count as land — keeps the shallow collar along the
// map border the same way it borders inland shores.
static int distance_to_land(tile2i tile, int max_d) {
    for (int r = 1; r <= max_d; ++r) {
        for (int dy = -r; dy <= r; ++dy) {
            for (int dx = -r; dx <= r; ++dx) {
                if (std::max(std::abs(dx), std::abs(dy)) != r) {
                    continue; // only walk the ring at exact distance r
                }
                tile2i n(tile.x() + dx, tile.y() + dy);
                if (!map_grid_is_inside(n, 1)) {
                    return r; // off-map = shore
                }
                if (!map_terrain_is(n.grid_offset(), TERRAIN_WATER | TERRAIN_DEEPWATER)) {
                    return r;
                }
            }
        }
    }
    return max_d + 1;
}

// Promote/demote the deepwater bit on one tile. Pharaoh's deepwater image
// table has no land-edge art, so deepwater tiles must sit at least 2
// Chebyshev-tiles away from any land (1-tile shallow collar). This routine
// enforces that on both directions: paint-water in the interior promotes
// to deep, and any previously-deep tile now adjacent to new land gets
// demoted to shallow.
static void recompute_depth_tile(int grid_offset) {
    if (!map_terrain_is(grid_offset, TERRAIN_WATER | TERRAIN_DEEPWATER)) {
        return;
    }
    // Cap the probe at 1: we only need to know whether land is within 1
    // ring. distance_to_land returns 2 when no land within 1, which is the
    // deepwater condition.
    int d = distance_to_land(tile2i(grid_offset), 1);
    if (d >= 2) {
        if (!map_terrain_is(grid_offset, TERRAIN_DEEPWATER)) {
            map_terrain_add(grid_offset, TERRAIN_DEEPWATER);
        }
    } else {
        if (map_terrain_is(grid_offset, TERRAIN_DEEPWATER)) {
            map_terrain_remove(grid_offset, TERRAIN_DEEPWATER);
        }
    }
}

void map_water_recompute_depth_region(tile2i tmin, tile2i tmax) {
    // Widen by 1 — that's the collar width; a tile in the outer ring may
    // have flipped depth class because the brush changed something within
    // its 1-tile distance window. map_tiles_foreach_region_tile clamps
    // out-of-map coordinates safely via map_grid_bound_area.
    tile2i rmin(tmin.x() - 1, tmin.y() - 1);
    tile2i rmax(tmax.x() + 1, tmax.y() + 1);
    map_tiles_foreach_region_tile(rmin, rmax, recompute_depth_tile);
}

namespace {

bool landing_tile_ok(tile2i t) {
    if (!t.valid()) {
        return false;
    }
    const int offset = t.grid_offset();
    if (map_terrain_is(offset, TERRAIN_ROAD) || map_terrain_is(offset, TERRAIN_SUBMERGED_ROAD)) {
        return true;
    }
    if (map_terrain_is(offset, TERRAIN_WATER | TERRAIN_DEEPWATER)) {
        return false;
    }
    for (int d = 0; d < 8; d++) {
        const int n = offset + map_grid_direction_delta(d);
        if (map_grid_is_valid_offset(n) && map_terrain_is(n, TERRAIN_WATER | TERRAIN_DEEPWATER)) {
            return false;
        }
    }
    return true;
}

bool free_land_tile(tile2i t) {
    if (!t.valid()) {
        return false;
    }
    if (map_terrain_is(t, TERRAIN_WATER | TERRAIN_DEEPWATER | TERRAIN_BUILDING | TERRAIN_WALL | TERRAIN_ROCK
            | TERRAIN_ELEVATION)) {
        return false;
    }
    if (map_building_at(t) > 0) {
        return false;
    }
    return true;
}

} // namespace

int map_water_landing_point(tile2i landing, tile2i ship, tile2i &out) {
    // OG map_water_landing_point(x0,y0 landing → x1,y1 ship).
    if (!landing.valid()) {
        out = tile2i::invalid;
        return 0;
    }
    if (landing == ship || !ship.valid()) {
        out = landing;
        return 0;
    }

    const int x0 = landing.x();
    const int y0 = landing.y();
    const int x1 = ship.x();
    const int y1 = ship.y();
    const int dx = x1 - x0;
    const int dy = y1 - y0;

    int best = 0;
    int best_x = x0;
    int best_y = y0;
    int sx = 0;
    int sy = 0;
    double slope;
    double inverse;
    if (dx == 0) {
        slope = FLT_MAX;
        inverse = 0.0;
    } else if (dy == 0) {
        slope = 0.0;
        inverse = FLT_MAX;
    } else {
        slope = (double)dy / (double)dx;
        inverse = 1.0 / slope;
    }
    if (dx < 0) {
        sx = -1;
    } else if (dx > 0) {
        sx = 1;
    }
    if (dy < 0) {
        sy = -1;
    } else if (dy > 0) {
        sy = 1;
    }

    const int rows = std::abs(dy);
    const int columns = std::abs(dx);
    int y = y0;
    for (int i = rows; i > 0; i--) {
        if (inverse == (double)FLT_MAX) {
            continue;
        }
        y += sy;
        const int ry = y - y0;
        const int x = (int)std::lround(((double)ry * inverse) + (double)x0);
        tile2i cand(x, y);
        if (landing_tile_ok(cand)) {
            const int d = (x - x0) * (x - x0) + ry * ry;
            if (d >= best) {
                best = d;
                best_x = x;
                best_y = y;
            }
        }
    }
    int x = x0;
    for (int i = columns; i > 0; i--) {
        if (slope == (double)FLT_MAX) {
            continue;
        }
        x += sx;
        const int rx = x - x0;
        const int ty = (int)std::lround(((double)rx * slope) + (double)y0);
        tile2i cand(x, ty);
        if (landing_tile_ok(cand)) {
            const int d = rx * rx + (ty - y0) * (ty - y0);
            if (d >= best) {
                best = d;
                best_x = x;
                best_y = ty;
            }
        }
    }

    out = tile2i(best_x, best_y);
    if (x0 != best_x || y0 != best_y) {
        return best;
    }

    // Nothing inland along the line: nudge to first dry neighbour (OG order).
    static const vec2i nudge[8] = {
        {0, -1}, {1, -1}, {0, 1}, {-1, -1}, {1, 0}, {1, 1}, {-1, 0}, {-1, 1}
    };
    for (const vec2i &n : nudge) {
        tile2i cand = landing.shifted(n);
        if (cand.valid() && !map_terrain_is(cand, TERRAIN_WATER | TERRAIN_DEEPWATER)) {
            out = cand;
            break;
        }
    }
    return best;
}

bool map_find_nearest_free_land_tile(tile2i &tile) {
    if (free_land_tile(tile)) {
        return true;
    }

    const int map_w = scenario_map_data()->width;
    const int map_h = scenario_map_data()->height;
    constexpr int k_max_radius = 5;
    for (int radius = 1; radius <= k_max_radius; radius++) {
        const int x_lo = tile.x() - radius;
        const int x_hi = tile.x() + radius;
        const int y_lo = tile.y() - radius;
        const int y_hi = tile.y() + radius;
        for (int xx = x_lo; xx <= x_hi; xx++) {
            tile2i top(xx, y_lo);
            if (top.x() >= 0 && top.x() < map_w && top.y() >= 0 && top.y() < map_h && free_land_tile(top)) {
                tile = top;
                return true;
            }
            tile2i bot(xx, y_hi);
            if (bot.x() >= 0 && bot.x() < map_w && bot.y() >= 0 && bot.y() < map_h && free_land_tile(bot)) {
                tile = bot;
                return true;
            }
        }
        for (int yy = y_lo + 1; yy <= y_hi - 1; yy++) {
            tile2i left(x_lo, yy);
            if (left.x() >= 0 && left.x() < map_w && left.y() >= 0 && left.y() < map_h && free_land_tile(left)) {
                tile = left;
                return true;
            }
            tile2i right(x_hi, yy);
            if (right.x() >= 0 && right.x() < map_w && right.y() >= 0 && right.y() < map_h && free_land_tile(right)) {
                tile = right;
                return true;
            }
        }
    }
    return false;
}

namespace {

bool open_reached_water(tile2i t) {
    if (!t.valid() || !map_terrain_is(t, TERRAIN_WATER | TERRAIN_DEEPWATER)) {
        return false;
    }
    if (map_routing_distance(t) <= 0) {
        return false;
    }
    // OG open_reached_water: tile + 4 orthogonal neighbours are water.
    static const vec2i orth[4] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    for (const vec2i &d : orth) {
        tile2i n = t.shifted(d);
        if (!n.valid() || !map_terrain_is(n, TERRAIN_WATER | TERRAIN_DEEPWATER)) {
            return false;
        }
    }
    return true;
}

} // namespace

int map_water_farthest_on_line(tile2i from, tile2i to, tile2i &out) {
    if (!from.valid()) {
        out = tile2i::invalid;
        return 0;
    }
    if (!to.valid() || from == to) {
        out = from;
        return 0;
    }

    map_routing_calculate_distances_water_boat(from);

    const int x = from.x();
    const int y = from.y();
    const int dx = to.x() - x;
    const int dy = to.y() - y;
    int step_x = 0;
    int step_y = 0;
    int best = 0;
    int best_x = x;
    int best_y = y;
    double slope;
    double inverse;
    if (dx == 0) {
        slope = FLT_MAX;
        inverse = 0.0;
    } else if (dy == 0) {
        slope = 0.0;
        inverse = FLT_MAX;
    } else {
        slope = (double)dy / (double)dx;
        inverse = 1.0 / slope;
    }
    if (dx < 0) {
        step_x = -1;
    } else if (dx > 0) {
        step_x = 1;
    }
    if (dy < 0) {
        step_y = -1;
    } else if (dy > 0) {
        step_y = 1;
    }

    const int rows = std::abs(dy);
    const int columns = std::abs(dx);
    int yy = y;
    for (int i = rows; i > 0; i--) {
        if (inverse == (double)FLT_MAX) {
            continue;
        }
        yy += step_y;
        const int xx = (int)std::lround(((double)(yy - y) * inverse) + (double)x);
        tile2i cand(xx, yy);
        if (open_reached_water(cand)) {
            const int d = (yy - y) * (yy - y) + (xx - x) * (xx - x);
            if (d >= best) {
                best = d;
                best_x = xx;
                best_y = yy;
            }
        }
    }
    int xx = x;
    for (int i = columns; i > 0; i--) {
        if (slope == (double)FLT_MAX) {
            continue;
        }
        xx += step_x;
        const int yv = (int)std::lround(((double)(xx - x) * slope) + (double)y);
        tile2i cand(xx, yv);
        if (open_reached_water(cand)) {
            const int d = (yv - y) * (yv - y) + (xx - x) * (xx - x);
            if (d >= best) {
                best = d;
                best_x = xx;
                best_y = yv;
            }
        }
    }

    out = tile2i(best_x, best_y);
    return best;
}

bool map_water_tile_next_to(tile2i building_tile, int size, tile2i &out) {
    out = tile2i::invalid;
    if (!building_tile.valid() || size < 1) {
        return false;
    }

    constexpr int k_min_water_around = 8;
    tile2i fallback = tile2i::invalid;
    const int start = map_ring_start(size, 1);
    const int end = map_ring_end(size, 1);
    for (int i = start; i < end; i++) {
        const ring_tile *rt = map_ring_tile(i);
        if (!rt) {
            continue;
        }
        const int tx = building_tile.x() + rt->x;
        const int ty = building_tile.y() + rt->y;
        if (!map_ring_is_inside_map(tx, ty)) {
            continue;
        }
        tile2i cand(tx, ty);
        if (!map_terrain_is(cand, TERRAIN_WATER | TERRAIN_DEEPWATER)) {
            continue;
        }
        if (map_terrain_is(cand, TERRAIN_BUILDING)) {
            continue;
        }
        if (!fallback.valid()) {
            fallback = cand;
        }
        const int around =
            map_terrain_count_directly_adjacent_with_type(cand.grid_offset(), TERRAIN_WATER | TERRAIN_DEEPWATER)
            + map_terrain_count_diagonally_adjacent_with_type(cand.grid_offset(), TERRAIN_WATER | TERRAIN_DEEPWATER);
        if (around >= k_min_water_around) {
            out = cand;
            return true;
        }
    }
    if (fallback.valid()) {
        out = fallback;
        return true;
    }
    return false;
}
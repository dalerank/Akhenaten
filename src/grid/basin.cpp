#include "basin.h"

#include "building/building.h"
#include "building/building_dike.h"
#include "core/profiler.h"
#include "core/random.h"
#include "game/game_config.h"
#include "grid/building.h"
#include "grid/canals.h"
#include "grid/grid.h"
#include "grid/irrigation_value.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "scenario/map.h"

#include <algorithm>
#include <vector>

namespace {

constexpr int BASIN_MIN_AREA = 4;
constexpr int BASIN_MAX_AREA = 200;
constexpr uint16_t BASIN_MARK_VISITED = 0xFFFF;

grid_xx g_basin_id_grid(FS_UINT16);

struct basin_runtime_t {
    uint16_t id = 0;
    int area = 0;
};

std::vector<basin_runtime_t> g_basins;
bool g_basin_dirty = true;

// Cardinal neighbors via relative xy (same pattern as map_canal_fill_from_offset).
// Raw ±1 / ±GRID_LENGTH wraps at abs column 0/227 and can leak into the border strip.
const vec2i ADJACENT_DIRS[4] = {vec2i(0, -1), vec2i(1, 0), vec2i(0, 1), vec2i(-1, 0)};

bool is_basin_fillable(tile2i tile) {
    if (!map_grid_is_inside(tile, 1)) {
        return false;
    }
    if (!map_terrain_is(tile, TERRAIN_FLOODPLAIN)) {
        return false;
    }
    // Dike crest (incl. road|dike sluice) is a wall for the fill.
    if (map_terrain_is(tile, TERRAIN_DIKE)) {
        return false;
    }
    return true;
}

int floodfill_component(int seed_offset, std::vector<int> &out_tiles) {
    out_tiles.clear();
    tile2i seed(seed_offset);
    if (!is_basin_fillable(seed) || map_grid_get(g_basin_id_grid, seed_offset) != 0) {
        return 0;
    }

    std::vector<int> queue;
    queue.reserve(256);
    queue.push_back(seed_offset);
    map_grid_set(g_basin_id_grid, seed_offset, BASIN_MARK_VISITED);
    out_tiles.push_back(seed_offset);

    size_t head = 0;
    while (head < queue.size()) {
        const int offset = queue[head++];
        tile2i tile(offset);
        for (const vec2i &dir : ADJACENT_DIRS) {
            tile2i next = tile.shifted(dir.x, dir.y);
            if (!is_basin_fillable(next)) {
                continue;
            }
            const int next_offset = next.grid_offset();
            if (map_grid_get(g_basin_id_grid, next_offset) != 0) {
                continue;
            }
            map_grid_set(g_basin_id_grid, next_offset, BASIN_MARK_VISITED);
            queue.push_back(next_offset);
            out_tiles.push_back(next_offset);
            // Oversize components stay marked visited until the cleanup pass.
        }
    }

    return (int)out_tiles.size();
}

// True when a short walk through DIKE crests reaches open floodplain outside
// the component — i.e. dikes are load-bearing for the seal.
// Natural rock/water pockets stay unsealed. A long meadow DIKE spur to distant
// floodplain does not count (MAX_DIKE_CREST_RUN) — only thin embankment walls.
bool dikes_seal_component(const std::vector<int> &tiles) {
    if (tiles.empty()) {
        return false;
    }

    constexpr int MAX_DIKE_CREST_RUN = 6; // allow heavy embankments; longer = spur
    constexpr uint8_t RUN_UNSET = 0xFF;

    // Reused across candidates within a rebuild; clear only the touched cells.
    static std::vector<uint8_t> best_run;
    static std::vector<uint8_t> in_component;
    static std::vector<int> touched;
    if ((int)best_run.size() != GRID_SIZE_TOTAL) {
        best_run.assign(GRID_SIZE_TOTAL, RUN_UNSET);
        in_component.assign(GRID_SIZE_TOTAL, 0);
    }
    touched.clear();
    touched.reserve(std::min((size_t)BASIN_MAX_AREA * 4, (size_t)1024));

    for (int offset : tiles) {
        in_component[(size_t)offset] = 1;
        touched.push_back(offset);
    }

    struct node_t {
        int offset;
        uint8_t dike_run; // consecutive DIKE tiles on the path from the component
    };
    std::vector<node_t> queue;
    queue.reserve(std::min((size_t)BASIN_MAX_AREA * 4, (size_t)1024));
    queue.push_back({tiles[0], 0});
    best_run[(size_t)tiles[0]] = 0;

    size_t head = 0;
    bool sealed_by_dikes = false;
    while (head < queue.size()) {
        const node_t cur = queue[head++];
        // Stale entry: a better (lower) dike_run reached this tile later in the queue.
        if (cur.dike_run > best_run[(size_t)cur.offset]) {
            continue;
        }

        tile2i tile(cur.offset);
        const bool on_dike = map_terrain_is(tile, TERRAIN_DIKE);

        if (!on_dike && !in_component[(size_t)cur.offset]) {
            // Exterior FP. Accept short crest crossings; keep searching if this path
            // was a long spur / ultra-thick face (thin face elsewhere may still seal).
            if (cur.dike_run > 0 && cur.dike_run <= MAX_DIKE_CREST_RUN) {
                sealed_by_dikes = true;
                break;
            }
            continue; // do not expand into the open floodplain sea
        }

        for (const vec2i &dir : ADJACENT_DIRS) {
            tile2i next = tile.shifted(dir.x, dir.y);
            if (!map_grid_is_inside(next, 1)) {
                continue;
            }
            // Crest may sit on meadow edge (DIKE without FLOODPLAIN) — still walkable
            // for the load-bearing test. Plain meadow/rock stays a hard stop.
            const bool next_dike = map_terrain_is(next, TERRAIN_DIKE);
            if (!next_dike && !map_terrain_is(next, TERRAIN_FLOODPLAIN)) {
                continue;
            }
            const int next_offset = next.grid_offset();
            if (next_offset < 0 || next_offset >= GRID_SIZE_TOTAL) {
                continue;
            }

            uint8_t next_run = 0;
            if (next_dike) {
                next_run = (uint8_t)std::min(cur.dike_run + 1, 255);
                if (next_run > MAX_DIKE_CREST_RUN) {
                    continue; // spur / ultra-thick
                }
            } else if (on_dike) {
                // Stepping off a crest onto FP: inherit run so exterior check can use it.
                next_run = cur.dike_run;
            }

            // Dijkstra on dike_run: first-visit by hop count is wrong — re-open on better run.
            if (best_run[(size_t)next_offset] <= next_run) {
                continue;
            }
            if (best_run[(size_t)next_offset] == RUN_UNSET) {
                touched.push_back(next_offset);
            }
            best_run[(size_t)next_offset] = next_run;
            queue.push_back({next_offset, next_run});
        }
    }

    for (int offset : touched) {
        best_run[(size_t)offset] = RUN_UNSET;
        in_component[(size_t)offset] = 0;
    }
    return sealed_by_dikes;
}

} // namespace

uint16_t map_basin_id_at(int grid_offset) {
    if (!map_grid_is_valid_offset(grid_offset)) {
        return 0;
    }
    const uint16_t id = (uint16_t)map_grid_get(g_basin_id_grid, grid_offset);
    return (id == BASIN_MARK_VISITED) ? 0 : id;
}

bool map_basin_is_sealed_at(int grid_offset) {
    // Only sealed components receive a non-zero basin_id.
    return map_basin_id_at(grid_offset) != 0;
}

int map_basin_count() {
    return (int)g_basins.size();
}

int map_basin_area(uint16_t basin_id) {
    if (basin_id == 0) {
        return 0;
    }
    for (const auto &b : g_basins) {
        if (b.id == basin_id) {
            return b.area;
        }
    }
    return 0;
}

int map_basin_farm_count(uint16_t basin_id) {
    if (basin_id == 0 || !game_features::gameplay_enhanced_flood_basins.to_bool()) {
        return 0;
    }

    // Live count so farm place/destroy without a dike rebuild stays accurate in UI.
    int count = 0;
    int grid_offset = scenario_map_data()->start_offset;
    for (int y = 0; y < scenario_map_data()->height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < scenario_map_data()->width; x++, grid_offset++) {
            if (map_basin_id_at(grid_offset) != basin_id) {
                continue;
            }
            const int bid = map_building_at(grid_offset);
            if (!bid) {
                continue;
            }
            building *b = building_get(bid);
            if (b && b->dcast_farm() && b->tile.grid_offset() == grid_offset) {
                count++;
            }
        }
    }
    return count;
}

uint16_t map_basin_adjacent_id(tile2i tile) {
    if (!map_grid_is_inside(tile, 1)) {
        return 0;
    }

    // 8-neigh: corner crest tiles only touch the interior diagonally.
    static const vec2i dirs8[8] = {
        vec2i(0, -1), vec2i(1, -1), vec2i(1, 0), vec2i(1, 1),
        vec2i(0, 1), vec2i(-1, 1), vec2i(-1, 0), vec2i(-1, -1),
    };

    auto basin_touching = [&](tile2i t) -> uint16_t {
        for (const vec2i &dir : dirs8) {
            tile2i next = t.shifted(dir.x, dir.y);
            if (!map_grid_is_inside(next, 1)) {
                continue;
            }
            const uint16_t id = map_basin_id_at(next);
            if (id != 0) {
                return id;
            }
        }
        return 0;
    };

    if (const uint16_t id = basin_touching(tile)) {
        return id;
    }

    // Thick crest / spur: walk contiguous DIKE a short distance until a sealed interior
    // is adjacent (outer tile of a double wall otherwise looks falsely Breached).
    if (!map_terrain_is(tile, TERRAIN_DIKE)) {
        return 0;
    }

    constexpr int MAX_DIKE_WALK = 48;
    int queue[MAX_DIKE_WALK];
    int qsize = 0;
    const int start = tile.grid_offset();
    queue[qsize++] = start;

    auto already_queued = [&](int offset) {
        for (int i = 0; i < qsize; i++) {
            if (queue[i] == offset) {
                return true;
            }
        }
        return false;
    };

    int head = 0;
    while (head < qsize) {
        tile2i cur(queue[head++]);
        for (const vec2i &dir : dirs8) {
            tile2i next = cur.shifted(dir.x, dir.y);
            if (!map_grid_is_inside(next, 1)) {
                continue;
            }
            if (const uint16_t id = map_basin_id_at(next)) {
                return id;
            }
            if (!map_terrain_is(next, TERRAIN_DIKE)) {
                continue;
            }
            const int next_offset = next.grid_offset();
            if (qsize >= MAX_DIKE_WALK || already_queued(next_offset)) {
                continue;
            }
            queue[qsize++] = next_offset;
        }
    }
    return 0;
}

void map_basin_mark_dirty() {
    g_basin_dirty = true;
}

void map_basin_rebuild() {
    OZZY_PROFILER_FUNCTION();
    g_basins.clear();
    map_grid_clear(g_basin_id_grid);
    g_basin_dirty = false;

    if (!game_features::gameplay_enhanced_flood_basins.to_bool()) {
        // OG keeps the saved IRRIGATION_RANGE; a clipped stamp left by a flag toggle goes at the next water update.
        g_irrigation_value.update();
        return;
    }

    uint16_t next_id = 1;
    std::vector<int> component;
    component.reserve(BASIN_MAX_AREA + 8);

    int grid_offset = scenario_map_data()->start_offset;
    for (int y = 0; y < scenario_map_data()->height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < scenario_map_data()->width; x++, grid_offset++) {
            if (!is_basin_fillable(tile2i(grid_offset))) {
                continue;
            }
            if (map_grid_get(g_basin_id_grid, grid_offset) != 0) {
                continue;
            }

            const int area = floodfill_component(grid_offset, component);
            if (area >= BASIN_MIN_AREA && area <= BASIN_MAX_AREA && next_id < BASIN_MARK_VISITED
                && dikes_seal_component(component)) {
                for (int tile_offset : component) {
                    map_grid_set(g_basin_id_grid, tile_offset, next_id);
                }
                basin_runtime_t info;
                info.id = next_id;
                info.area = area;
                g_basins.push_back(info);
                next_id++;
            }
            // else: component left as BASIN_MARK_VISITED — treat as none via accessor
        }
    }

    // Convert leftover visit marks to 0 (open floodplain / too-small / natural-only pockets).
    grid_offset = scenario_map_data()->start_offset;
    for (int y = 0; y < scenario_map_data()->height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < scenario_map_data()->width; x++, grid_offset++) {
            if (map_grid_get(g_basin_id_grid, grid_offset) == BASIN_MARK_VISITED) {
                map_grid_set(g_basin_id_grid, grid_offset, 0);
            }
        }
    }

    // Place/clear/undo change basin_id but leave TERRAIN_IRRIGATION_RANGE until the
    // next canal day — restamp now so radius-2 cannot keep leaking across a new crest.
    map_irrigation_restamp_from_wet_canals();
    g_irrigation_value.update();
}

void map_basin_rebuild_dirty() {
    if (!g_basin_dirty) {
        return;
    }
    map_basin_rebuild();
}

int map_basin_breach_perimeter(int max_tiles, int *first_breach_offset) {
    if (first_breach_offset) {
        *first_breach_offset = -1;
    }
    if (max_tiles <= 0 || !game_features::gameplay_enhanced_flood_basins.to_bool()) {
        return 0;
    }
    if (g_basins.empty()) {
        return 0;
    }

    std::vector<int> candidates;
    candidates.reserve(64);

    int grid_offset = scenario_map_data()->start_offset;
    for (int y = 0; y < scenario_map_data()->height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < scenario_map_data()->width; x++, grid_offset++) {
            if (!map_terrain_is(grid_offset, TERRAIN_DIKE)) {
                continue;
            }
            if (map_basin_adjacent_id(tile2i(grid_offset)) == 0) {
                continue;
            }
            candidates.push_back(grid_offset);
        }
    }

    if (candidates.empty()) {
        return 0;
    }

    // Deterministic shuffle from map random so tests / replay stay stable enough.
    for (int i = (int)candidates.size() - 1; i > 0; i--) {
        const int j = anti_scum_random_15bit() % (i + 1);
        std::swap(candidates[(size_t)i], candidates[(size_t)j]);
    }

    const int remove_count = std::min(max_tiles, (int)candidates.size());
    int min_x = 9999, min_y = 9999, max_x = -1, max_y = -1;
    for (int i = 0; i < remove_count; i++) {
        const int offset = candidates[(size_t)i];
        if (i == 0 && first_breach_offset) {
            *first_breach_offset = offset;
        }
        // Strip crest only — keep ROAD / SUBMERGED_ROAD so a sluice becomes a
        // plain road gap (floodfill breach) without orphaning the road bit.
        map_terrain_remove(offset, TERRAIN_DIKE);
        map_refresh_river_image_at(offset, true);
        tile2i t(offset);
        min_x = std::min(min_x, t.x());
        min_y = std::min(min_y, t.y());
        max_x = std::max(max_x, t.x());
        max_y = std::max(max_y, t.y());
    }

    const int span = std::max(max_x - min_x, max_y - min_y) + 3;
    building_dike::update_area_dikes(tile2i(min_x, min_y).shifted(-1, -1), span);
    map_basin_mark_dirty();
    map_basin_rebuild_dirty();
    return remove_count;
}

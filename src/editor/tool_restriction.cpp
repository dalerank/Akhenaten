#include "tool_restriction.h"

#include "city/warning.h"
#include "grid/elevation.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/terrain.h"

// #define OFFSET(x,y) (x + GRID_SIZE_PH * y)

static const int TILE_GRID_OFFSETS_PH[] = {0, GRID_LENGTH, 1, GRID_LENGTH + 1};

static const int ACCESS_RAMP_TILE_OFFSETS_BY_ORIENTATION_PH[4][6] = {
  {GRID_OFFSET(0, 1), GRID_OFFSET(1, 1), GRID_OFFSET(0, 2), GRID_OFFSET(1, 2), GRID_OFFSET(0, 0), GRID_OFFSET(1, 0)},
  {GRID_OFFSET(0, 0), GRID_OFFSET(0, 1), GRID_OFFSET(-1, 0), GRID_OFFSET(-1, 1), GRID_OFFSET(1, 0), GRID_OFFSET(1, 1)},
  {GRID_OFFSET(0, 0), GRID_OFFSET(1, 0), GRID_OFFSET(0, -1), GRID_OFFSET(1, -1), GRID_OFFSET(0, 1), GRID_OFFSET(1, 1)},
  {GRID_OFFSET(1, 0), GRID_OFFSET(1, 1), GRID_OFFSET(2, 0), GRID_OFFSET(2, 1), GRID_OFFSET(0, 0), GRID_OFFSET(0, 1)},
};

static int is_clear_terrain(tile2i tile, xstring& warning) {
    int result = !map_terrain_is(tile.grid_offset(), TERRAIN_NOT_CLEAR ^ TERRAIN_ROAD);
    if (!result)
        warning = "#editor_cannot_place";

    return result;
}

static int is_edge(map_point tile, xstring& warning) {
    int result = tile.x() == 0 || tile.y() == 0 || tile.x() == scenario_map_data()->width - 1
                 || tile.y() == scenario_map_data()->height - 1;
    if (!result)
        warning = "#editor_need_map_edge";

    return result;
}

static int is_water(map_point tile, xstring& warning) {
    int result = map_terrain_is(tile.grid_offset(), TERRAIN_WATER);
    if (!result)
        warning = "#editor_need_open_water";

    return result;
}

static int is_deep_water(map_point tile, xstring& warning) {
    int result = map_terrain_is(tile.grid_offset(), TERRAIN_WATER)
                 && map_terrain_count_directly_adjacent_with_type(tile.grid_offset(), TERRAIN_WATER) == 4;
    if (!result)
        warning = "#editor_need_open_water";

    return result;
}

int editor_tool_can_place_flag(int type, map_point tile, xstring& warning) {
    switch (type) {
    case TOOL_ENTRY_POINT:
    case TOOL_EXIT_POINT:
    case TOOL_INVASION_POINT:
        return is_clear_terrain(tile, warning) && is_edge(tile, warning);

    case TOOL_EARTHQUAKE_POINT:
    case TOOL_HERD_POINT:
        return is_clear_terrain(tile, warning);

    case TOOL_FISHING_POINT:
        return is_water(tile, warning);

    case TOOL_RIVER_ENTRY_POINT:
    case TOOL_RIVER_EXIT_POINT:
        return is_edge(tile, warning) && is_deep_water(tile, warning);

    default:
        return 0;
    }
}

int editor_tool_can_place_access_ramp(map_point tile, int* orientation_index) {
    if (!map_grid_is_inside(tile, 2))
        return 0;

    for (int orientation = 0; orientation < 4; orientation++) {
        int right_tiles = 0;
        int wrong_tiles = 0;
        int top_elevation = 0;
        for (int index = 0; index < 6; index++) {
            int tile_offset = tile.grid_offset(); // + ACCESS_RAMP_TILE_OFFSETS_BY_ORIENTATION[orientation][index];
            tile_offset += ACCESS_RAMP_TILE_OFFSETS_BY_ORIENTATION_PH[orientation][index];

            int elevation = map_elevation_at(tile_offset);
            if (index < 2) {
                if (map_terrain_is(tile_offset, TERRAIN_ELEVATION))
                    right_tiles++;
                else {
                    wrong_tiles++;
                }
                top_elevation = elevation;
            } else if (index < 4) {
                if (map_terrain_is(tile_offset, TERRAIN_ELEVATION)) {
                    if (elevation == top_elevation)
                        wrong_tiles++;
                    else {
                        right_tiles++;
                    }
                } else if (elevation >= top_elevation)
                    right_tiles++;
                else {
                    wrong_tiles++;
                }
            } else {
                if (map_terrain_is(tile_offset, TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP))
                    wrong_tiles++;
                else if (elevation >= top_elevation)
                    wrong_tiles++;
                else {
                    right_tiles++;
                }
            }
        }
        if (right_tiles == 6) {
            if (orientation_index)
                *orientation_index = orientation;

            return 1;
        }
    }
    return 0;
}

int editor_tool_can_place_building(map_point tile, int num_tiles, int* blocked_tiles) {
    bool blocked = false;
    for (int i = 0; i < num_tiles; i++) {
        int tile_offset = tile.grid_offset(); // + TILE_GRID_OFFSETS[i];
        tile_offset += TILE_GRID_OFFSETS_PH[i];

        int forbidden_terrain = map_terrain_get(tile_offset) & TERRAIN_NOT_CLEAR;
        if (forbidden_terrain || map_has_figure_at(tile_offset)) {
            blocked = true;
            if (blocked_tiles)
                blocked_tiles[i] = 1;
        } else {
            if (blocked_tiles)
                blocked_tiles[i] = 0;
        }
    }
    return !blocked;
}

#include "tool.h"

#include "building/construction/routed.h"
#include "building/building_road.h"
#include "city/city_warnings.h"
#include "city/city.h"
#include "game/game_events.h"
#include "city/city_buildings.h"
#include "core/random.h"
#include "editor/tool_restriction.h"
#include "game/undo.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "grid/building_tiles.h"
#include "grid/elevation.h"
#include "grid/grid.h"
#include "grid/trees.h"
#include "grid/image_context.h"
#include "grid/property.h"
#include "grid/routing/routing.h"
#include "grid/routing/routing_terrain.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "scenario/editor_events.h"
#include "scenario/editor_map.h"
#include "widget/widget_minimap.h"
#include "building/construction/build_planner.h"

#define TERRAIN_PAINT_MASK ~(TERRAIN_TREE | TERRAIN_ROCK | TERRAIN_WATER | TERRAIN_BUILDING | TERRAIN_SHRUB | TERRAIN_GARDEN | TERRAIN_ROAD | TERRAIN_MEADOW)

static struct {
    int active = 0;
    int type = TOOL_GRASS;
    int id = 0;
    int brush_size = 3;
    int build_in_progress = 0;
    int start_elevation = 0;
    tile2i start_tile = {0, 0};
} data;

int editor_tool_type(void) {
    return data.type;
}

int editor_tool_is_active(void) {
    return data.active;
}

void editor_tool_deactivate(void) {
    if (editor_tool_is_updatable() && data.build_in_progress) {
        game_undo_restore_map(1);
        data.build_in_progress = 0;
    } else {
        data.active = 0;
    }
}

void editor_tool_set_type(int type) {
    editor_tool_set_with_id(type, 0);
}

void editor_tool_set_with_id(int type, int id) {
    data.active = 1;
    data.type = type;
    data.id = id;
}

int editor_tool_brush_size(void) {
    return data.brush_size;
}

void editor_tool_set_brush_size(int size) {
    data.brush_size = size;
}

void editor_tool_foreach_brush_tile(void (*callback)(const void* user_data, int dx, int dy), const void* user_data) {
    if (data.type == TOOL_RAISE_LAND || data.type == TOOL_LOWER_LAND) {
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                callback(user_data, dx, dy);
            }
        }
    } else {
        for (int dy = -data.brush_size + 1; dy < data.brush_size; dy++) {
            for (int dx = -data.brush_size + 1; dx < data.brush_size; dx++) {
                int steps = (dx < 0 ? -dx : dx) + (dy < 0 ? -dy : dy);
                if (steps < data.brush_size)
                    callback(user_data, dx, dy);
            }
        }
    }
}

int editor_tool_is_updatable(void) {
    return data.type == TOOL_ROAD;
}

int editor_tool_is_in_use(void) {
    return data.build_in_progress;
}

void editor_tool_start_use(tile2i tile) {
    if (!data.active)
        return;
    data.build_in_progress = 1;
    data.start_elevation = map_elevation_at(tile.grid_offset());
    data.start_tile = tile;
    if (data.type == TOOL_ROAD) {
        game_undo_start_build(BUILDING_ROAD);
        map_routing_update_land();
    }
}

int editor_tool_is_brush(void) {
    switch (data.type) {
    case TOOL_GRASS:
    case TOOL_TREES:
    case TOOL_WATER:
    case TOOL_SHRUB:
    case TOOL_ROCKS:
    case TOOL_MEADOW:
    case TOOL_RAISE_LAND:
    case TOOL_LOWER_LAND:
        return 1;
    default:
        return 0;
    }
}

static int raise_land_tile(int x, int y, int grid_offset, int terrain) {
    int elevation = map_elevation_at(grid_offset);
    if (elevation < 5 && elevation == data.start_elevation) {
        if (!(terrain & (TERRAIN_ACCESS_RAMP | TERRAIN_ELEVATION))) {
            map_property_set_multi_tile_size(grid_offset, 1);
            map_elevation_set(grid_offset, elevation + 1);
            terrain &= ~(TERRAIN_WATER | TERRAIN_BUILDING | TERRAIN_GARDEN | TERRAIN_ROAD);
        }
    }
    return terrain;
}

static int lower_land_tile(int x, int y, int grid_offset, int terrain) {
    if (terrain & TERRAIN_ACCESS_RAMP) {
        terrain |= TERRAIN_ELEVATION;
        terrain &= ~(TERRAIN_ACCESS_RAMP);
        map_property_set_multi_tile_size(grid_offset, 1);
        map_property_set_multi_tile_xy(grid_offset, 0, 0, 1);
    }
    int elevation = map_elevation_at(grid_offset);
    if (elevation <= 0)
        terrain &= ~(TERRAIN_ELEVATION);
    else if (elevation == data.start_elevation) {
        terrain &= ~(TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP);
        map_elevation_set(grid_offset, elevation - 1);
    }
    return terrain;
}

static void add_terrain(const void* tile_data, int dx, int dy) {
    tile2i tile = *(tile2i*)tile_data;
    int x = tile.x() + dx;
    int y = tile.y() + dy;
    if (!map_grid_is_inside(tile2i(x, y), 1))
        return;
    int grid_offset = tile.grid_offset() + GRID_OFFSET(dx, dy);
    int terrain = map_terrain_get(grid_offset);
    if (terrain & TERRAIN_BUILDING) {
        map_building_tiles_remove(0, tile2i(x, y));
        terrain = map_terrain_get(grid_offset);
    }
    switch (data.type) {
    case TOOL_GRASS:
        terrain &= TERRAIN_PAINT_MASK;
        break;
    case TOOL_TREES:
        if (!(terrain & TERRAIN_TREE)) {
            terrain &= TERRAIN_PAINT_MASK;
            terrain |= TERRAIN_TREE;
        }
        break;
    case TOOL_ROCKS:
        if (!(terrain & TERRAIN_ROCK)) {
            terrain &= TERRAIN_PAINT_MASK;
            terrain |= TERRAIN_ROCK;
        }
        break;
    case TOOL_WATER:
        if (!map_elevation_at(grid_offset) && !(terrain & TERRAIN_WATER)) {
            terrain &= TERRAIN_PAINT_MASK;
            terrain |= TERRAIN_WATER;
        }
        break;
    case TOOL_SHRUB:
        if (!(terrain & TERRAIN_SHRUB)) {
            terrain &= TERRAIN_PAINT_MASK;
            terrain |= TERRAIN_SHRUB;
        }
        break;
    case TOOL_MEADOW:
        if (!(terrain & TERRAIN_MEADOW)) {
            terrain &= TERRAIN_PAINT_MASK;
            terrain |= TERRAIN_MEADOW;
        }
        break;
    case TOOL_RAISE_LAND:
        terrain = raise_land_tile(x, y, grid_offset, terrain);
        break;
    case TOOL_LOWER_LAND:
        terrain = lower_land_tile(x, y, grid_offset, terrain);
        break;
    default:
        break;
    }
    map_terrain_set(grid_offset, terrain);
}

void editor_tool_update_use(tile2i tile) {
    if (!data.build_in_progress)
        return;

    if (data.type == TOOL_ROAD) {
        const auto &params = building_impl::params(BUILDING_ROAD);
        params.planer_construction_update(g_city_planner, data.start_tile, tile);
        return;
    }

    if (!editor_tool_is_brush())
        return;

    editor_tool_foreach_brush_tile(add_terrain, &tile);

    int x_min = tile.x() - data.brush_size;
    int x_max = tile.x() + data.brush_size;
    int y_min = tile.y() - data.brush_size;
    int y_max = tile.y() + data.brush_size;
    switch (data.type) {
    case TOOL_GRASS:
        map_image_context_reset_water();
        map_tiles_river_refresh_region(x_min, y_min, x_max, y_max);
        map_tiles_update_all_rocks();
        map_tiles_update_region_empty_land(false, tile2i(x_min, y_min), tile2i(x_max, y_max));
        map_tiles_update_region_meadow(x_min, y_min, x_max, y_max);
        break;
    case TOOL_TREES:
        map_image_context_reset_water();
        map_tiles_river_refresh_region(x_min, y_min, x_max, y_max);
        map_tiles_update_all_rocks();
        map_tree_update_region_tiles(x_min, y_min, x_max, y_max);
        break;
    case TOOL_WATER:
    case TOOL_ROCKS:
        map_image_context_reset_water();
        map_tiles_update_all_rocks();
        map_tiles_river_refresh_region(x_min, y_min, x_max, y_max);
        break;
    case TOOL_SHRUB:
        map_image_context_reset_water();
        map_tiles_river_refresh_region(x_min, y_min, x_max, y_max);
        map_tiles_update_all_rocks();
        map_tiles_update_region_shrub(x_min, y_min, x_max, y_max);
        break;
    case TOOL_MEADOW:
        map_image_context_reset_water();
        map_tiles_river_refresh_region(x_min, y_min, x_max, y_max);
        map_tiles_update_all_rocks();
        map_tiles_update_region_meadow(x_min, y_min, x_max, y_max);
        break;
    case TOOL_RAISE_LAND:
    case TOOL_LOWER_LAND:
        map_image_context_reset_water();
        map_image_context_reset_elevation();
        map_tiles_update_all_elevation();
        map_tiles_river_refresh_region(x_min, y_min, x_max, y_max);
        map_tree_update_region_tiles(x_min, y_min, x_max, y_max);
        map_tiles_update_region_shrub(x_min, y_min, x_max, y_max);
        map_tiles_update_all_rocks();
        map_tiles_update_region_empty_land(false, tile2i(x_min, y_min), tile2i(x_max, y_max));
        map_tiles_update_region_meadow(x_min, y_min, x_max, y_max);
        break;
    default:
        break;
    }

    scenario_editor_updated_terrain();
    widget_minimap_invalidate();
}

static void place_earthquake_flag(tile2i tile) {
    xstring warning;
    if (editor_tool_can_place_flag(data.type, tile, warning)) {
        if (scenario_editor_earthquake_severity())
            scenario_editor_set_earthquake_point(tile.x(), tile.y());
        else {
            events::emit(event_city_warning{ "#warning_editor_no_earthquake_scheduled" });
        }
    } else {
        events::emit(event_city_warning{ "#place_earthquake_flag" });
    }
}

static void place_flag(tile2i tile, void (*update)(int x, int y)) {
    xstring warning;
    if (editor_tool_can_place_flag(data.type, tile, warning))
        update(tile.x(), tile.y());
    else {
        events::emit(event_city_warning{ "#place_flag" });
    }
}

static void place_flag_with_id(tile2i tile, void (*update)(int id, int x, int y)) {
    xstring warning;
    if (editor_tool_can_place_flag(data.type, tile, warning))
        update(data.id, tile.x(), tile.y());
    else
        events::emit(event_city_warning{ "#place_flag_with_id" });
}

static void place_building(map_point tile) {
    int image_id;
    int size;
    e_building_type type;
    switch (data.type) {
    case TOOL_NATIVE_HUT:
        type = BUILDING_UNUSED_NATIVE_HUT_88;
        image_id = image_id_from_group(GROUP_EDITOR_BUILDING_NATIVE) + (random_byte() & 1);
        size = 1;
        break;
    case TOOL_NATIVE_CENTER:
        type = BUILDING_UNUSED_NATIVE_MEETING_89;
        image_id = image_id_from_group(GROUP_EDITOR_BUILDING_NATIVE) + 2;
        size = 2;
        break;
    case TOOL_NATIVE_FIELD:
        type = BUILDING_UNUSED_NATIVE_CROPS_93;
        image_id = image_id_from_group(GROUP_EDITOR_BUILDING_CROPS);
        size = 1;
        break;
    default:
        return;
    }

    if (editor_tool_can_place_building(tile, size * size, 0)) {
        building* b = building_create(type, tile, 0);
        map_building_tiles_add(b->id, tile, size, image_id, TERRAIN_BUILDING);
        scenario_editor_updated_terrain();
    } else {
        events::emit(event_city_warning{ "#warning_editor_cannot_place" });
    }
}

static void update_terrain_after_elevation_changes(void) {
    map_elevation_remove_cliffs();

    map_image_context_reset_water();
    map_image_context_reset_elevation();
    map_tiles_update_all_elevation();
    map_tiles_update_all_rocks();
    map_tiles_update_all_empty_land();
    map_tiles_update_all_meadow();

    scenario_editor_updated_terrain();
}

static void place_access_ramp(map_point tile) {
    int orientation = 0;
    if (editor_tool_can_place_access_ramp(tile, &orientation)) {
        int terrain_mask = ~(TERRAIN_ROCK | TERRAIN_WATER | TERRAIN_BUILDING | TERRAIN_GARDEN | TERRAIN_CANAL);
        for (int dy = 0; dy < 2; dy++) {
            for (int dx = 0; dx < 2; dx++) {
                int grid_offset = tile.grid_offset() + GRID_OFFSET(dx, dy);
                map_terrain_set(grid_offset, map_terrain_get(grid_offset) & terrain_mask);
            }
        }
        map_building_tiles_add(0, tile, 2, image_id_from_group(GROUP_TERRAIN_ACCESS_RAMP) + orientation, TERRAIN_ACCESS_RAMP);

        update_terrain_after_elevation_changes();
        scenario_editor_updated_terrain();
    } else {
        events::emit(event_city_warning{ "#warning_editor_cannot_place" });
    }
}

static void place_road(map_point start_tile, map_point end_tile) {
    const auto &params = building_impl::params(BUILDING_ROAD);
    int items_placed = params.planer_construction_place(g_city_planner, start_tile, end_tile, 0, 0);
    if (items_placed) {
        scenario_editor_updated_terrain();
    }
}

void editor_tool_end_use(map_point tile) {
    if (!data.build_in_progress)
        return;
    data.build_in_progress = 0;
    switch (data.type) {
    case TOOL_EARTHQUAKE_POINT:
        place_earthquake_flag(tile);
        break;
    case TOOL_ENTRY_POINT:
        place_flag(tile, scenario_editor_set_entry_point);
        break;
    case TOOL_EXIT_POINT:
        place_flag(tile, scenario_editor_set_exit_point);
        break;
    case TOOL_RIVER_ENTRY_POINT:
        place_flag(tile, scenario_editor_set_river_entry_point);
        break;
    case TOOL_RIVER_EXIT_POINT:
        place_flag(tile, scenario_editor_set_river_exit_point);
        break;
    case TOOL_INVASION_POINT:
        place_flag_with_id(tile, scenario_editor_set_land_invasion_point);
        break;
    case TOOL_FISHING_POINT:
        place_flag_with_id(tile, scenario_editor_set_fishing_point);
        break;
    case TOOL_HERD_POINT:
        place_flag_with_id(tile, scenario_editor_set_predator_herd_point);
        break;
    case TOOL_NATIVE_CENTER:
    case TOOL_NATIVE_FIELD:
    case TOOL_NATIVE_HUT:
        place_building(tile);
        break;
    case TOOL_RAISE_LAND:
    case TOOL_LOWER_LAND:
        update_terrain_after_elevation_changes();
        break;
    case TOOL_ACCESS_RAMP:
        place_access_ramp(tile);
        break;
    case TOOL_ROAD:
        place_road(data.start_tile, tile);
        break;
    default:
        break;
    }
}

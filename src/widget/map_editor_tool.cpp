#include "map_editor_tool.h"
#include <graphics/view/zoom.h>

#include "editor/tool.h"
#include "building/building.h"
#include "editor/tool_restriction.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "grid/terrain.h"
#include "input/scroll.h"
#include "scenario/scenario.h"
#include "game/game.h"

#define MAX_TILES 4

static const int X_VIEW_OFFSETS[MAX_TILES] = {0, -30, 30, 0};
static const int Y_VIEW_OFFSETS[MAX_TILES] = {0, 15, 15, 30};

static void draw_flat_tile_editor(vec2i pos, color color_mask) {
    painter ctx = game.painter();
    if (color_mask == COLOR_MASK_GREEN && scenario_property_climate() != CLIMATE_DESERT)
        ImageDraw::img_generic(ctx, image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED), pos, ALPHA_MASK_SEMI_TRANSPARENT & color_mask);
    else {
        ImageDraw::img_generic(ctx, image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED), pos, color_mask);
    }
}

static void draw_partially_blocked_editor(int x, int y, int num_tiles, int* blocked_tiles) {
    for (int i = 0; i < num_tiles; i++) {
        int x_offset = x + X_VIEW_OFFSETS[i];
        int y_offset = y + Y_VIEW_OFFSETS[i];
        if (blocked_tiles[i])
            draw_flat_tile_editor(vec2i{x_offset, y_offset}, COLOR_MASK_RED);
        else {
            draw_flat_tile_editor(vec2i{x_offset, y_offset}, COLOR_MASK_GREEN);
        }
    }
}

static void draw_building_image(int image_id, int x, int y) {
    painter ctx = game.painter();
    ImageDraw::isometric(ctx, image_id, vec2i{x, y}, COLOR_MASK_GREEN);
    //    ImageDraw::isometric_top(image_id, x, y, COLOR_MASK_GREEN, city_view_get_scale_float());
}

static void draw_building(tile2i tile, int screen_x, int screen_y, e_building_type type) {
    const auto &props = building_impl::params(type);
    painter ctx = game.painter();

    int num_tiles = props.building_size * props.building_size;
    int blocked_tiles[MAX_TILES];
    int blocked = !editor_tool_can_place_building(tile, num_tiles, blocked_tiles);

    if (blocked) {
        draw_partially_blocked_editor(screen_x, screen_y, num_tiles, blocked_tiles);
    } else if (editor_tool_is_in_use()) {
        int image_id = image_id_from_group(GROUP_TERRAIN_OVERLAY_FLAT);
        for (int i = 0; i < num_tiles; i++) {
            int x_offset = screen_x + X_VIEW_OFFSETS[i];
            int y_offset = screen_y + Y_VIEW_OFFSETS[i];
            ImageDraw::isometric(ctx, image_id, vec2i{x_offset, y_offset});
        }
    } else {
        int image_id;
        if (type == BUILDING_UNUSED_NATIVE_CROPS_93) {
            image_id = image_id_from_group(GROUP_EDITOR_BUILDING_CROPS);
        } else {
            image_id =  props.base_img();
        }
        draw_building_image(image_id, screen_x, screen_y);
    }
}

static void draw_road(painter &ctx, tile2i tile, int x, int y) {
    bool blocked = false;
    int image_id = 0;
    if (map_terrain_is(tile, TERRAIN_NOT_CLEAR))
        blocked = true;
    else {
        const auto &params = building_impl::params(BUILDING_ROAD);
        image_id = params.base_img();
        if (!map_terrain_has_adjacent_y_with_type(tile.grid_offset(), TERRAIN_ROAD)
            && map_terrain_has_adjacent_x_with_type(tile.grid_offset(), TERRAIN_ROAD)) {
            image_id++;
        }
    }

    if (blocked) {
        draw_flat_tile_editor(vec2i{ x, y }, COLOR_MASK_RED);
    } else {
        draw_building_image(image_id, x, y);
    }
}

static void draw_brush_tile(const void* data, int dx, int dy) {
    screen_tile* view = (screen_tile*)data;
    vec2i view_t = map_tile_to_view({ dx, dy });
    draw_flat_tile_editor(vec2i{view->x + view_t.x, view->y + view_t.y}, COLOR_MASK_GREEN);
}

static void draw_brush(painter &ctx, tile2i tile, int x, int y) {
    screen_tile vt = {x, y};
    editor_tool_foreach_brush_tile(draw_brush_tile, &vt);
}

static void draw_access_ramp(tile2i tile, int x, int y) {
    int orientation;
    if (editor_tool_can_place_access_ramp(tile, &orientation)) {
        int image_id = image_id_from_group(GROUP_TERRAIN_ACCESS_RAMP) + orientation;
        draw_building_image(image_id, x, y);
    } else {
        int blocked[4] = {1, 1, 1, 1};
        draw_partially_blocked_editor(x, y, 4, blocked);
    }
}

static void draw_map_flag(int x, int y, int is_ok) {
    draw_flat_tile_editor(vec2i{x, y}, is_ok ? COLOR_MASK_GREEN : COLOR_MASK_RED);
}

void map_editor_tool_draw(painter &ctx, tile2i tile) {
    if (!tile.grid_offset() || scroll_in_progress() || !editor_tool_is_active())
        return;

    int type = editor_tool_type();
    screen_tile screen = camera_get_selected_screen_tile();
    int x = screen.x;
    int y = screen.y;
    xstring warning;
    switch (type) {
    case TOOL_NATIVE_CENTER:
        draw_building(tile, x, y, BUILDING_UNUSED_NATIVE_MEETING_89);
        break;
    case TOOL_NATIVE_HUT:
        draw_building(tile, x, y, BUILDING_UNUSED_NATIVE_HUT_88);
        break;
    case TOOL_NATIVE_FIELD:
        draw_building(tile, x, y, BUILDING_UNUSED_NATIVE_CROPS_93);
        break;

    case TOOL_EARTHQUAKE_POINT:
    case TOOL_ENTRY_POINT:
    case TOOL_EXIT_POINT:
    case TOOL_RIVER_ENTRY_POINT:
    case TOOL_RIVER_EXIT_POINT:
    case TOOL_INVASION_POINT:
    case TOOL_FISHING_POINT:
    case TOOL_HERD_POINT:
        draw_map_flag(x, y, editor_tool_can_place_flag(type, tile, warning));
        break;

    case TOOL_ACCESS_RAMP:
        draw_access_ramp(tile, x, y);
        break;

    case TOOL_GRASS:
    case TOOL_MEADOW:
    case TOOL_ROCKS:
    case TOOL_SHRUB:
    case TOOL_TREES:
    case TOOL_WATER:
    case TOOL_RAISE_LAND:
    case TOOL_LOWER_LAND:
        draw_brush(ctx, tile, x, y);
        break;

    case TOOL_ROAD:
        draw_road(ctx, tile, x, y);
        break;
    }
}

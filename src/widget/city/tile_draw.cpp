#include "tile_draw.h"

#include "dev/debug.h"
#include "core/svector.h"
#include "building/construction/build_planner.h"
#include "graphics/view/view.h"
#include "building/monuments.h"
#include "game/state.h"
#include "graphics/graphics.h"
#include "grid/building.h"
#include "grid/figure.h"
#include "grid/image.h"
#include "grid/property.h"
#include "grid/random.h"
#include "grid/terrain.h"
#include "config/config.h"
#include "ornaments.h"
#include "sound/sound_city.h"
#include "game/game.h"
#include "graphics/view/lookup.h"
#include "city/city_buildings.h"

#include "overlays/city_overlay.h"
#include "overlays/city_overlay_risks.h"

static const int ADJACENT_OFFSETS_PH[2][4][7]
  = {{{GRID_OFFSET(-1, 0), GRID_OFFSET(-1, -1), GRID_OFFSET(-1, -2), GRID_OFFSET(0, -2), GRID_OFFSET(1, -2)},
      {GRID_OFFSET(0, -1), GRID_OFFSET(1, -1), GRID_OFFSET(2, -1), GRID_OFFSET(2, 0), GRID_OFFSET(2, 1)},
      {GRID_OFFSET(1, 0), GRID_OFFSET(1, 1), GRID_OFFSET(1, 2), GRID_OFFSET(0, 2), GRID_OFFSET(-1, 2)},
      {GRID_OFFSET(0, 1), GRID_OFFSET(-1, 1), GRID_OFFSET(-2, 1), GRID_OFFSET(-2, 0), GRID_OFFSET(-2, -1)}},
     {{GRID_OFFSET(-1, 0),
       GRID_OFFSET(-1, -1),
       GRID_OFFSET(-1, -2),
       GRID_OFFSET(-1, -3),
       GRID_OFFSET(0, -3),
       GRID_OFFSET(1, -3),
       GRID_OFFSET(2, -3)},
      {GRID_OFFSET(0, -1),
       GRID_OFFSET(1, -1),
       GRID_OFFSET(2, -1),
       GRID_OFFSET(3, -1),
       GRID_OFFSET(3, 0),
       GRID_OFFSET(3, 1),
       GRID_OFFSET(3, 2)},
      {GRID_OFFSET(1, 0),
       GRID_OFFSET(1, 1),
       GRID_OFFSET(1, 2),
       GRID_OFFSET(1, 3),
       GRID_OFFSET(0, 3),
       GRID_OFFSET(-1, 3),
       GRID_OFFSET(-2, 3)},
      {GRID_OFFSET(0, 1),
       GRID_OFFSET(-1, 1),
       GRID_OFFSET(-2, 1),
       GRID_OFFSET(-3, 1),
       GRID_OFFSET(-3, 0),
       GRID_OFFSET(-3, -1),
       GRID_OFFSET(-3, -2)}}};


grid_xx g_render_grid = {0, FS_UINT32};

void map_render_clear() {
    map_grid_clear(g_render_grid);
}

bool map_render_is(int grid_offset, int render_mask) {
    return map_grid_is_valid_offset(grid_offset) && !!(map_grid_get(g_render_grid, grid_offset) & render_mask);
}

bool map_render_is(tile2i tile, int render_mask) {
    return map_render_is(tile.grid_offset(), render_mask);
}

void map_render_set(tile2i tile, int flag) {
    map_grid_set(g_render_grid, tile.grid_offset(), flag);
}

void map_render_set(int grid_offset, int flag) {
    map_grid_set(g_render_grid, grid_offset, flag);
}

enum e_figure_draw_mode { e_figure_draw_common = 0, e_figure_draw_overlay = 1 };

void local_render_context_t::init() {
    advance_water_animation = 0;

    time_millis now = time_get_millis();
    if (now - last_water_animation_time > 60) {
        last_water_animation_time = now;
        advance_water_animation = 1;
    }

    image_id_water_first = image_id_from_group(GROUP_TERRAIN_WATER);
    image_id_water_last = 5 + image_id_water_first;
    image_id_deepwater_first = image_id_from_group(GROUP_TERRAIN_DEEPWATER);
    image_id_deepwater_last = 89 + image_id_deepwater_first;
}

bool drawing_building_as_deleted(building* b) {
    if (!config_get(CONFIG_UI_VISUAL_FEEDBACK_ON_DELETE)) {
        return false;
    }

    b = b->main();
    if (b->id && (b->is_deleted || map_property_is_deleted(b->tile))) {
        return true;
    }

    return false;
}

static bool is_multi_tile_terrain(int grid_offset) {
    return (!map_building_at(grid_offset) && map_property_multi_tile_size(grid_offset) > 1);
}

static bool has_adjacent_deletion(int grid_offset) {
    int size = map_property_multi_tile_size(grid_offset);
    int total_adjacent_offsets = size * 2 + 1;
    const int* adjacent_offset; // = ADJACENT_OFFSETS[size - 2][city_view_orientation() / 2];

    adjacent_offset = ADJACENT_OFFSETS_PH[size - 2][city_view_orientation() / 2];
    for (int i = 0; i < total_adjacent_offsets; ++i) {
        if (map_property_is_deleted(grid_offset + adjacent_offset[i])
            || drawing_building_as_deleted(building_at(grid_offset + adjacent_offset[i]))) {
            return true;
        }
    }
    return false;
}

static void clip_between_rectangles(int* xOut, int* yOut, int* wOut, int* hOut, int xA, int yA, int wA, int hA, int xB, int yB, int wB, int hB) {
    *xOut = (xA > xB) ? xA : xB;
    *yOut = (yA > yB) ? yA : yB;
    int x_end_A = (xA + wA);
    int x_end_B = (xB + wB);
    int x_end_Out = (x_end_A < x_end_B) ? x_end_A : x_end_B;
    int y_end_A = (yA + hA);
    int y_end_B = (yB + hB);
    int y_end_Out = (y_end_A < y_end_B) ? y_end_A : y_end_B;
    *wOut = x_end_Out - *xOut;
    *hOut = y_end_Out - *yOut;
    if (*wOut < 0)
        *wOut = 0;
    if (*hOut < 0)
        *hOut = 0;
}

void draw_isometric_mark_sound(int building_id, int grid_offset, color &color_mask, int direction) {
    if (building_id) {
        building* b = building_get(building_id);
        if (config_get(CONFIG_UI_VISUAL_FEEDBACK_ON_DELETE) && drawing_building_as_deleted(b)) {
            color_mask = COLOR_MASK_RED;
        }

        sound_city_mark_building_view(b, direction);
    } else {
        int terrain = map_terrain_get(grid_offset);
        sound_city_mark_terrain_view(terrain, grid_offset, direction);
    }
}

void draw_isometric_nonterrain_height(vec2i pixel, tile2i tile, painter &ctx) {
    int grid_offset = tile.grid_offset();
    // black tile outside of map
    if (grid_offset < 0) {
        ImageDraw::isometric_from_drawtile(ctx, image_id_from_group(GROUP_TERRAIN_BLACK), pixel, COLOR_BLACK);
        return;
    }

    g_city_planner.construction_record_view_position(pixel, tile);
    int building_id = map_building_at(grid_offset);

    color color_mask = COLOR_MASK_NONE;
    building *b = building_get(building_id);
    bool deletion_tool = (g_city_planner.build_type == BUILDING_CLEAR_LAND && g_city_planner.end == tile);
    if (deletion_tool || map_property_is_deleted(tile) || drawing_building_as_deleted(b)) {
        color_mask = COLOR_MASK_RED;
    }

    if (!map_property_is_draw_tile(grid_offset)) {
        bool force_draw_tile = false;
        if (building_id > 0) {
            force_draw_tile = b->dcast()->force_draw_height_tile(ctx, tile, pixel, color_mask);
            b->dcast()->force_draw_top_tile(ctx, tile, pixel, color_mask);
        }

        if (!force_draw_tile) {
            return;
        }
    }

    bool tall_flat_tile = map_render_is(grid_offset, RENDER_TALL_TILE);
    bool should_draw = building_id > 0 || tall_flat_tile;
    if (!should_draw) {
        return;
    }

    if (tall_flat_tile && building_id > 0) {
        map_grid_area_foreach(tile, tile.shifted(b->size, b->size), [] (tile2i tile) {
            const bool is_building = map_terrain_is(tile, TERRAIN_BUILDING);
            if (is_building) {
                return;
            }
            int image_id = map_image_at(tile);
            const image_t* img = image_get(image_id);
            int top_height = img->isometric_top_height();
            map_render_set(tile, top_height > 0);
        });
    }

    int image_id = map_image_at(grid_offset);
    if (tall_flat_tile) {
        ImageDraw::isometric_from_drawtile_top(ctx, image_id, pixel, color_mask);

        int image_alt_value = map_image_alt_at(grid_offset);
        int image_alt_id = (image_alt_value & 0x00ffffff);
        uint8_t image_alt_alpha = ((image_alt_value & 0xff000000) >> 24);
        if (image_alt_id > 0 && image_alt_alpha > 0) {
            ImageDraw::isometric_from_drawtile_top(ctx, image_alt_id, pixel, (0x00ffffff | (image_alt_alpha << 24)), ImgFlag_Alpha);
        }
        return;
    }

    vec2i view_pos, view_size;
    city_view_get_viewport(*ctx.view, view_pos, view_size);
    int direction = SOUND_DIRECTION_CENTER;
    if (pixel.x < view_pos.x + 100) {
        direction = SOUND_DIRECTION_LEFT;
    } else if (pixel.x > view_pos.x + view_size.x - 100) {
        direction = SOUND_DIRECTION_RIGHT;
    }

    if (config_get(CONFIG_UI_VISUAL_FEEDBACK_ON_DELETE) && drawing_building_as_deleted(b)) {
        color_mask = COLOR_MASK_RED;
    }

    sound_city_mark_building_view(b, direction);
    if (map_property_is_constructing(grid_offset)) {
        image_id = image_id_from_group(GROUP_TERRAIN_OVERLAY_FLAT);
    }

    //ImageDraw::isometric_from_drawtile(ctx, image_id, pixel, color_mask);
}

void draw_isometrics_overlay_flat(vec2i pixel, tile2i tile, painter &ctx) {
    g_city_planner.construction_record_view_position(pixel, tile);
    constexpr uint32_t mode_highlighted[] = {0, COLOR_BLUE, COLOR_RED, COLOR_GREEN, COLOR_YELLOW};
    if (!tile.valid()) {
        // Outside map: draw black tile
        ImageDraw::isometric_from_drawtile(ctx, image_id_from_group(GROUP_TERRAIN_BLACK), pixel, 0);
        return;
    }

    auto overlay = get_city_overlay();
    if (overlay->draw_custom_footprint(pixel, tile, ctx)) {
        /*nothing*/

    } else if (map_property_is_draw_tile(tile)) {
        int terrain = map_terrain_get(tile);
        if (terrain & (TERRAIN_CANAL | TERRAIN_WALL)) {
        //    // display groundwater
        //    int image_id = image_id_from_group(GROUP_TERRAIN_EMPTY_LAND) + (map_random_get(grid_offset) & 7);
        //    ImageDraw::isometric_from_drawtile(ctx, image_id, pixel, mode_highlighted[map_is_highlighted(grid_offset)]);
        //
        } else if (map_is_highlighted(tile)) {
            e_highligth_mode mode = map_is_highlighted(tile);
            ImageDraw::isometric_from_drawtile(ctx, map_image_at(tile), pixel, mode_highlighted[mode]);
        
        } else if (terrain & TERRAIN_BUILDING) {
            overlay->draw_building_footprint(ctx, pixel, tile, 0);
        
        } else {
            const image_t *img = ImageDraw::isometric_from_drawtile(ctx, map_image_at(tile), pixel, 0);
            int top_height = img->isometric_top_height();
            map_render_set(tile, top_height > 0 ? RENDER_TALL_TILE : 0);
        }
    }

    //get_city_overlay()->draw_custom_top(pixel, point, ctx);
}

void draw_isometrics_overlay_height(vec2i pixel, tile2i point, painter &ctx) {
    int grid_offset = point.grid_offset();
    //Planner.construction_record_view_position(pixel, point);
    constexpr uint32_t mode_highlighted[] = {0, COLOR_BLUE, COLOR_RED};

    auto overlay = get_city_overlay();
    if (grid_offset < 0) {
        // Outside map: draw black tile
        //ImageDraw::isometric_from_drawtile(ctx, image_id_from_group(GROUP_TERRAIN_BLACK), pixel, 0);

    } else if (overlay->draw_custom_footprint(pixel, point, ctx)) {
        //get_city_overlay()->draw_custom_footprint(pixel, point, ctx);

    } else if (map_property_is_draw_tile(grid_offset)) {
        bool tall_flat_tile = map_render_is(grid_offset, RENDER_TALL_TILE);
        if (tall_flat_tile) {
            ImageDraw::isometric_from_drawtile_top(ctx, map_image_at(grid_offset), pixel, 0);
        }

        //int terrain = map_terrain_get(grid_offset);
        //if (terrain & (TERRAIN_CANAL | TERRAIN_WALL)) {
        //    // display groundwater
        //    int image_id = image_id_from_group(GROUP_TERRAIN_EMPTY_LAND) + (map_random_get(grid_offset) & 7);
        //    ImageDraw::isometric_from_drawtile_top(ctx, image_id, pixel, mode_highlighted[map_is_highlighted(grid_offset)]);
        //
        //} else if ((terrain & TERRAIN_ROAD) && !(terrain & TERRAIN_BUILDING)) {
        //    ImageDraw::isometric_from_drawtile_top(ctx, map_image_at(grid_offset), pixel, mode_highlighted[map_is_highlighted(grid_offset)]);
        //
        //} else if (terrain & TERRAIN_BUILDING) {
        //    //city_with_overlay_draw_building_footprint(ctx, pixel.x, pixel.y, grid_offset, 0);
        //
        //} else {
        //    ImageDraw::isometric_from_drawtile_top(ctx, map_image_at(grid_offset), pixel, 0);
        //}
    }

    get_city_overlay()->draw_custom_top(pixel, point, ctx);
}

void draw_ornaments_overlay(vec2i pixel, tile2i point, painter &ctx) {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;
    int b_id = map_building_at(grid_offset);

    if (b_id) {
        const building* b = building_at(grid_offset);
        if (get_city_overlay()->show_building(b)) {
            draw_ornaments_and_animations_height(pixel, point, ctx);
        }
    } else {
        draw_ornaments_and_animations_height(pixel, point, ctx);
    }
}

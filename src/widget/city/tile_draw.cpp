#include "tile_draw.h"

#include "dev/debug.h"
#include "core/svector.h"
#include "building/construction/build_planner.h"
#include "graphics/view/view.h"
#include "figures_cached_draw.h"
#include "game/state.h"
#include "graphics/boilerplate.h"
#include "grid/building.h"
#include "grid/figure.h"
#include "grid/image.h"
#include "grid/property.h"
#include "grid/random.h"
#include "grid/terrain.h"
#include "config/config.h"
#include "ornaments.h"
#include "sound/city.h"
#include "game/game.h"

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

enum e_figure_draw_mode { e_figure_draw_common = 0, e_figure_draw_overlay = 1 };

struct draw_context_t {
    time_millis last_water_animation_time;
    int advance_water_animation;

    int image_id_water_first;
    int image_id_water_last;

    int image_id_deepwater_first;
    int image_id_deepwater_last;

    int selected_figure_id;
    int highlighted_formation;
    vec2i* selected_figure_coord;
};

draw_context_t& get_draw_context() {
    static draw_context_t data;
    return data;
}

void init_draw_context(int selected_figure_id, vec2i* figure_coord, int highlighted_formation) {
    auto& draw_context = get_draw_context();

    draw_context.advance_water_animation = 0;
    if (!selected_figure_id) {
        time_millis now = time_get_millis();
        if (now - draw_context.last_water_animation_time > 60) {
            draw_context.last_water_animation_time = now;
            draw_context.advance_water_animation = 1;
        }
    }
    draw_context.image_id_water_first = image_id_from_group(GROUP_TERRAIN_WATER);
    draw_context.image_id_water_last = 5 + draw_context.image_id_water_first;
    draw_context.image_id_deepwater_first = image_id_from_group(GROUP_TERRAIN_DEEPWATER);
    draw_context.image_id_deepwater_last = 89 + draw_context.image_id_deepwater_first;
    draw_context.selected_figure_id = selected_figure_id;
    draw_context.selected_figure_coord = figure_coord;
    draw_context.highlighted_formation = highlighted_formation;
}

static bool drawing_building_as_deleted(building* b) {
    if (!config_get(CONFIG_UI_VISUAL_FEEDBACK_ON_DELETE))
        return false;

    b = b->main();
    if (b->id && (b->is_deleted || map_property_is_deleted(b->tile.grid_offset())))
        return true;
    return false;
}
static bool is_multi_tile_terrain(int grid_offset) {
    return (!map_building_at(grid_offset) && map_property_multi_tile_size(grid_offset) > 1);
}
static bool has_adjacent_deletion(int grid_offset) {
    int size = map_property_multi_tile_size(grid_offset);
    int total_adjacent_offsets = size * 2 + 1;
    const int* adjacent_offset; // = ADJACENT_OFFSETS[size - 2][city_view_orientation() / 2];
    switch (GAME_ENV) {
    case ENGINE_ENV_PHARAOH: // TODO: get rid of this garbage
        adjacent_offset = ADJACENT_OFFSETS_PH[size - 2][city_view_orientation() / 2];
        break;
    }
    for (int i = 0; i < total_adjacent_offsets; ++i) {
        if (map_property_is_deleted(grid_offset + adjacent_offset[i])
            || drawing_building_as_deleted(building_at(grid_offset + adjacent_offset[i]))) {
            return true;
        }
    }
    return false;
}

/////////

static bool is_drawable_farmhouse(int grid_offset, int map_orientation) {
    if (!map_property_is_draw_tile(grid_offset))
        return false;

    int xy = map_property_multi_tile_xy(grid_offset);
    if (map_orientation == DIR_0_TOP_RIGHT && xy == EDGE_X0Y1)
        return true;

    if (map_orientation == DIR_2_BOTTOM_RIGHT && xy == EDGE_X0Y0)
        return true;

    if (map_orientation == DIR_4_BOTTOM_LEFT && xy == EDGE_X1Y0)
        return true;

    if (map_orientation == DIR_2_BOTTOM_RIGHT && xy == EDGE_X1Y1)
        return true;

    return false;
}
static bool is_drawable_farm_corner(int grid_offset) {
    if (!map_property_is_draw_tile(grid_offset))
        return false;

    int map_orientation = city_view_orientation();
    int xy = map_property_multi_tile_xy(grid_offset);
    if (map_orientation == DIR_0_TOP_RIGHT && xy == EDGE_X0Y2)
        return true;
    else if (map_orientation == DIR_2_BOTTOM_RIGHT && xy == EDGE_X0Y0)
        return true;
    else if (map_orientation == DIR_4_BOTTOM_LEFT && xy == EDGE_X2Y0)
        return true;
    else if (map_orientation == DIR_6_TOP_LEFT && xy == EDGE_X2Y2)
        return true;

    return false;
}

void draw_flattened_footprint_anysize(int x, int y, int size_x, int size_y, int image_offset, color color_mask) {
    painter ctx = game.painter();
    int image_base = image_id_from_group(GROUP_TERRAIN_OVERLAY_FLAT) + image_offset;

    for (int xx = 0; xx < size_x; xx++) {
        for (int yy = 0; yy < size_y; yy++) {
            int t_x = x + (30 * xx) + (30 * yy);
            int t_y = y + (15 * xx) - (15 * yy);

            // tile shape -- image offset
            // (0 = top corner, 1 = left edge, 2 = right edge, 3 = any other case)
            int shape_offset = 3;
            if (xx == 0) {
                shape_offset = 1;
                if (yy == size_y - 1)
                    shape_offset = 0;
            } else if (yy == size_y - 1)
                shape_offset = 2;

            ImageDraw::isometric_from_drawtile(ctx, image_base + shape_offset, t_x, t_y, color_mask);
        }
    }
}
void draw_flattened_footprint_building(const building* b, int x, int y, int image_offset, color color_mask) {
    return (draw_flattened_footprint_anysize(x, y, b->size, b->size, image_offset, color_mask));
}

/////////

#define TILE_BLEEDING_Y_BIAS 8
static bool USE_BLEEDING_CACHE = true;
static void clip_between_rectangles(int* xOut,
                                    int* yOut,
                                    int* wOut,
                                    int* hOut,
                                    int xA,
                                    int yA,
                                    int wA,
                                    int hA,
                                    int xB,
                                    int yB,
                                    int wB,
                                    int hB) {
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

static void draw_cached_figures(vec2i pixel, tile2i point, e_figure_draw_mode mode, painter &ctx) {
    auto& draw_context = get_draw_context();

    if (!USE_BLEEDING_CACHE) {
        return;
    }

    if (!map_property_is_draw_tile(point.grid_offset())) {
        return;
    }

    tile_figure_draw_cache *cache = get_figure_cache_for_tile(*(ctx.figure_cache), point);
    if (cache == nullptr || cache->num_figures == 0) {
        return;
    }

    // city zoom & viewport params
    float scale = zoom_get_scale();
    vec2i viewport_pos, viewport_size;
    city_view_get_viewport(viewport_pos, viewport_size);

    // record tile's rendering coords
    int clip_x, clip_y, clip_width, clip_height;
    int size = 1;
    clip_between_rectangles(&clip_x, &clip_y, &clip_width, &clip_height, pixel.x, pixel.y - (size - 1) * HALF_TILE_HEIGHT_PIXELS - 30,
                            size * TILE_WIDTH_PIXELS, size * TILE_HEIGHT_PIXELS + 30,
                            viewport_pos.x / scale, viewport_pos.y / scale,
                            viewport_size.x / scale, viewport_size.y / scale);

    // set rendering clip around the current tile
    if (clip_width == 0 || clip_height == 0) {
        return;
    }

    graphics_set_clip_rectangle(scale * clip_x, scale * clip_y, scale * clip_width, scale * clip_height);
    int image_id = map_image_at(point.grid_offset());
    const image_t* img = image_get(image_id);
    vec2i tile_z_cross = pixel;
    tile_z_cross += {HALF_TILE_WIDTH_PIXELS, img->isometric_3d_height() - TILE_BLEEDING_Y_BIAS};

    if (g_debug_show_opts[e_debug_show_tile_cache]) {
        graphics_fill_rect(0, 0, 10000, 10000, 0x22000000); // for debugging
    }

    struct tile_figure_t {
        figure *f;
        vec2i pixel;
        vec2i cc_offset;
    };

    svector<tile_figure_t, 32> tile_figures;
    for (int i = 0; i < cache->num_figures; ++i) {
        int figure_id = cache->figures[i].id;
        figure* f = figure_get(figure_id);
        tile_figures.push_back({f, cache->figures[i].pixel, f->tile_pixel_coords()});
    }

    std::sort(tile_figures.begin(), tile_figures.end(), [] (const auto &lhs, const auto &rhs) {
        return (lhs.pixel.y + lhs.cc_offset.y) < (rhs.pixel.y + rhs.cc_offset.y);
    });

    for (const auto &c: tile_figures) {
        figure* f = c.f;

        vec2i cc_offsets = c.cc_offset;
        vec2i tile_center = {HALF_TILE_WIDTH_PIXELS, HALF_TILE_HEIGHT_PIXELS};
        vec2i pivot = c.pixel + cc_offsets + tile_center;
        if (tile_z_cross.y > pivot.y) {
            continue;
        }

        vec2i ghost_pixel = c.pixel;
        switch (mode) {
        case e_figure_draw_common: // non-overlay
            if (!f->is_ghost) {
                if (!draw_context.selected_figure_id) {
                    int highlight = f->formation_id > 0 && f->formation_id == draw_context.highlighted_formation;
                    f->city_draw_figure(ctx, ghost_pixel, highlight);
                } else if (f->id == draw_context.selected_figure_id) {
                    f->city_draw_figure(ctx, ghost_pixel, 0, draw_context.selected_figure_coord);
                }
            }
            break;

        case e_figure_draw_overlay: // overlay
            if (!f->is_ghost && get_city_overlay()->show_figure(f)) {
                f->city_draw_figure(ctx, ghost_pixel, 0);
            }
            break;
        }
    }
    // reset rendering clip
    set_city_clip_rectangle();
}

void draw_debug_figurecaches(vec2i pixel, map_point point, painter &ctx) {
    return;

    if (!USE_BLEEDING_CACHE) {
        return;
    }

    if (!map_property_is_draw_tile(point.grid_offset())) {
        return;
    }

    auto cache = get_figure_cache_for_tile(*ctx.figure_cache, point);
    if (cache == nullptr || cache->num_figures == 0) {
        return;
    }

    const image_t* img = image_get(map_image_at(point.grid_offset()));
    int size = img->isometric_size();
    int height = img->isometric_3d_height();
    if (size > 1) {
        debug_draw_tile_top_bb(pixel.x, pixel.y, height, COLOR_BLUE, size);
        debug_draw_tile_box(pixel.x, pixel.y, COLOR_NULL, COLOR_BLUE, size, size);
    }

    debug_draw_tile_top_bb(pixel.x, pixel.y, height, COLOR_RED);
    debug_draw_tile_box(pixel.x, pixel.y, COLOR_NULL, COLOR_RED);

    vec2i tile_z_cross = pixel;
    tile_z_cross += {HALF_TILE_WIDTH_PIXELS, img->isometric_3d_height() - TILE_BLEEDING_Y_BIAS};
    debug_draw_line_with_contour((pixel.x + 16) * zoom_get_scale(), (pixel.x + TILE_WIDTH_PIXELS - 16) * zoom_get_scale(),
                                 tile_z_cross.y * zoom_get_scale(), tile_z_cross.y * zoom_get_scale(), COLOR_FONT_YELLOW);

    for (int i = 0; i < cache->num_figures; ++i) {
        auto f = figure_get(cache->figures[i].id);
        auto cc_offsets = f->tile_pixel_coords();
        vec2i tile_center = {HALF_TILE_WIDTH_PIXELS, HALF_TILE_HEIGHT_PIXELS};
        auto pivot = cache->figures[i].pixel + cc_offsets + tile_center;
        debug_draw_crosshair(pivot.x * zoom_get_scale(), pivot.y * zoom_get_scale());

        debug_draw_line_with_contour(tile_z_cross.x * zoom_get_scale(), pivot.x * zoom_get_scale(),
                                     tile_z_cross.y * zoom_get_scale(), pivot.y * zoom_get_scale(),
                                     tile_z_cross.y > pivot.y ? COLOR_RED : COLOR_GREEN);
    }
}

void draw_isometrics(vec2i pixel, tile2i point, painter &ctx) {
    auto& draw_context = get_draw_context();

    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;
    // black tile outside of map
    if (grid_offset < 0) {
        return ImageDraw::isometric_from_drawtile(ctx, image_id_from_group(GROUP_TERRAIN_BLACK), x, y, COLOR_BLACK);
    }

    Planner.construction_record_view_position(pixel, point);
    if (map_property_is_draw_tile(grid_offset)) {
        // Valid grid_offset_figure and leftmost tile -> draw
        int building_id = map_building_at(grid_offset);
        color color_mask = COLOR_MASK_NONE;
        bool deletion_tool = (Planner.build_type == BUILDING_CLEAR_LAND && Planner.end == point);
        if (deletion_tool || map_property_is_deleted(point.grid_offset())) {
            color_mask = COLOR_MASK_RED;
        }

        vec2i view_pos, view_size;
        city_view_get_viewport(view_pos, view_size);
        int direction = SOUND_DIRECTION_CENTER;
        if (x < view_pos.x + 100) {
           direction = SOUND_DIRECTION_LEFT;
        } else if (x > view_pos.x + view_size.x - 100) {
           direction = SOUND_DIRECTION_RIGHT;
        }

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

        int image_id = map_image_at(grid_offset);
        if (draw_context.advance_water_animation) {
            if (image_id >= draw_context.image_id_water_first && image_id <= draw_context.image_id_water_last) {
                image_id++; // wrong, but eh
                if (image_id > draw_context.image_id_water_last) {
                    image_id = draw_context.image_id_water_first;
                }
            }

            if (image_id >= draw_context.image_id_deepwater_first && image_id <= draw_context.image_id_deepwater_last) {
                image_id += 15;

                if (image_id > draw_context.image_id_deepwater_last) {
                    image_id -= 90;
                }
            }
            map_image_set(grid_offset, image_id);
        }

        if (map_property_is_constructing(grid_offset)) {
            image_id = image_id_from_group(GROUP_TERRAIN_OVERLAY_FLAT);
        }

        //        const image_t *img = image_get(image_id);
        //
        //        int tile_size = (img->width + 2) / (FOOTPRINT_WIDTH + 2);
        //        int footprint_height = img->height - (FOOTPRINT_HEIGHT * (tile_size));
        //
        //        int y_start = y + FOOTPRINT_HALF_HEIGHT;
        //        graphics_draw_line(x * zoom_get_scale(), x * zoom_get_scale(), y_start * zoom_get_scale(), (y_start -
        //        footprint_height) * zoom_get_scale(), COLOR_RED);

        ImageDraw::isometric_from_drawtile(ctx, image_id, x, y, color_mask);
    }
}

void draw_ornaments(vec2i pixel, tile2i point, painter &ctx) {
    // defined separately in ornaments.cpp
    // cuz it's too much stuff.
    draw_ornaments_and_animations(pixel, point, ctx);
}

void draw_figures(vec2i pixel, tile2i point, painter &ctx) {
    auto& draw_context = get_draw_context();

    // first, draw from the cache
    draw_cached_figures(pixel, point, e_figure_draw_common, ctx);

    // secondly, draw figures found on this tile as normal
    int grid_offset = point.grid_offset();
    int figure_id = map_figure_id_get(grid_offset);
    while (figure_id) {
        figure* f = figure_get(figure_id);
        if (!f->is_ghost) {
            if (!draw_context.selected_figure_id) {
                int highlight = f->formation_id > 0 && f->formation_id == draw_context.highlighted_formation;
                f->city_draw_figure(ctx, pixel, highlight);
            } else if (figure_id == draw_context.selected_figure_id)
                f->city_draw_figure(ctx, pixel, 0, draw_context.selected_figure_coord);
        }
        if (figure_id != f->next_figure)
            figure_id = f->next_figure;
        else
            figure_id = 0;
    }
}

void draw_isometrics_overlay(vec2i pixel, tile2i point, painter &ctx) {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;
    Planner.construction_record_view_position(pixel, point);
    constexpr uint32_t mode_highlighted[] = {0, COLOR_BLUE, COLOR_RED};
    if (grid_offset < 0) {
        // Outside map: draw black tile
        ImageDraw::isometric_from_drawtile(ctx, image_id_from_group(GROUP_TERRAIN_BLACK), x, y, 0);

    } else if (get_city_overlay()->draw_custom_footprint) {
        get_city_overlay()->draw_custom_footprint(pixel, point, ctx);

    } else if (map_property_is_draw_tile(grid_offset)) {
        int terrain = map_terrain_get(grid_offset);
        if (terrain & (TERRAIN_CANAL | TERRAIN_WALL)) {
            // display groundwater
            int image_id = image_id_from_group(GROUP_TERRAIN_EMPTY_LAND) + (map_random_get(grid_offset) & 7);
            ImageDraw::isometric_from_drawtile(ctx, image_id, x, y, mode_highlighted[map_is_highlighted(grid_offset)]);

        } else if ((terrain & TERRAIN_ROAD) && !(terrain & TERRAIN_BUILDING)) {
            ImageDraw::isometric_from_drawtile(ctx, map_image_at(grid_offset), x, y, mode_highlighted[map_is_highlighted(grid_offset)]);

        } else if (terrain & TERRAIN_BUILDING) {
            city_with_overlay_draw_building_footprint(ctx, x, y, grid_offset, 0);

        } else {
            ImageDraw::isometric_from_drawtile(ctx, map_image_at(grid_offset), x, y, 0);
        }
    }

    get_city_overlay()->draw_custom_top(pixel, point, ctx);
}

void draw_ornaments_overlay(vec2i pixel, map_point point, painter &ctx) {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;
    int b_id = map_building_at(grid_offset);
    if (b_id) {
        const building* b = building_at(grid_offset);
        if (get_city_overlay()->show_building(b)) {
            draw_ornaments(pixel, point, ctx);
        }
    } else {
        draw_ornaments(pixel, point, ctx);
    }
}

void draw_figures_overlay(vec2i pixel, tile2i point, painter &ctx) {
    // first, draw the cached figures
    draw_cached_figures(pixel, point, e_figure_draw_overlay, ctx);

    // secondly, draw the figures normally found on this tile
    int grid_offset = point.grid_offset();
    int figure_id = map_figure_id_get(grid_offset);
    while (figure_id) {
        figure* f = figure_get(figure_id);
        if (!f->is_ghost && get_city_overlay()->show_figure(f))
            f->city_draw_figure(ctx, pixel, 0);

        if (figure_id != f->next_figure)
            figure_id = f->next_figure;
        else
            figure_id = 0;
    }
}

static void draw_overlay_column(int x, int y, int height, int column_style, painter &ctx) {
    int image_id = image_id_from_group(GROUP_OVERLAY_COLUMN);
    switch (column_style) {
    case COLUMN_TYPE_RISK:
        if (height <= 5)
            image_id += COLUMN_COLOR_PLAIN;
        else if (height < 7)
            image_id += COLUMN_COLOR_YELLOW;
        else if (height < 9)
            image_id += COLUMN_COLOR_ORANGE;
        else
            image_id += COLUMN_COLOR_RED;
        break;

    case COLUMN_TYPE_POSITIVE:
        image_id += COLUMN_COLOR_BLUE;
        break;

    case COLUMN_TYPE_WATER_ACCESS:
        image_id += COLUMN_COLOR_BLUE;
        break;
    }

    if (height > 10)
        height = 10;

    int capital_height = image_get(image_id)->height;
    // base
    ImageDraw::img_generic(ctx, image_id + 2, x + 9, y - 8);
    if (height) {
        // column
        for (int i = 1; i < height; i++) {
            ImageDraw::img_generic(ctx, image_id + 1, x + 17, y - 8 - 10 * i + 13);
        }
        // capital
        ImageDraw::img_generic(ctx, image_id, x + 5, y - 8 - capital_height - 10 * (height - 1) + 13);
    }
}

void city_with_overlay_draw_building_footprint(painter &ctx, int x, int y, int grid_offset, int image_offset) {
    int building_id = map_building_at(grid_offset);
    if (!building_id) {
        return;
    }

    building* b = building_get(building_id);
    if (get_city_overlay()->show_building(b)) {
        if (building_is_farm(b->type)) {
            if (is_drawable_farmhouse(grid_offset, city_view_orientation())) {
                ImageDraw::isometric_from_drawtile(ctx, map_image_at(grid_offset), x, y, 0);
            } else if (map_property_is_draw_tile(grid_offset)) {
                ImageDraw::isometric_from_drawtile(ctx, map_image_at(grid_offset), x, y, 0);
            }
        } else {
            ImageDraw::isometric_from_drawtile(ctx, map_image_at(grid_offset), x, y, 0);
        }
    } else {
        if (b->type == BUILDING_FESTIVAL_SQUARE) {
            return;
        }
        int draw = 1;
        if (b->size == 3 && building_is_farm(b->type)) {
            draw = is_drawable_farm_corner(grid_offset);
        }

        if (draw) {
            draw_flattened_footprint_building(b, x, y, image_offset, 0);
        }
    }
}

void city_with_overlay_draw_building_top(vec2i pixel, tile2i point, painter &ctx) {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;
    building* b = building_at(grid_offset);
    if (get_city_overlay()->type == OVERLAY_PROBLEMS) {
        overlay_problems_prepare_building(b);
    }

    if (get_city_overlay()->show_building(b)) {
        //        draw_top(pixel, point);
        draw_isometrics(pixel, point, ctx);
    } else {
        int column_height = get_city_overlay()->get_column_height(b);
        if (column_height != NO_COLUMN) {
            int draw = 1;
            if (building_is_farm(b->type)) {
                draw = is_drawable_farm_corner(grid_offset);
            }

            if (draw) {
                draw_overlay_column(x, y, column_height, get_city_overlay()->column_type, ctx);
            }
        }
    }
}

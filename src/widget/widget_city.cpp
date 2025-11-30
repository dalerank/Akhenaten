#include "widget/widget_city.h"

#include "graphics/clouds.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/view/lookup.h"
#include "graphics/view/view.h"
#include "grid/property.h"
#include "grid/grid.h"
#include "widget/city/building_ghost.h"
#include "overlays/city_overlay.h"
#include "building/construction/build_planner.h"
#include "city/city_finance.h"
#include "city/city_warnings.h"
#include "core/calc.h"
#include "core/string.h"
#include "figure/formation_batalion.h"
#include "game/cheats.h"
#include "game/settings.h"
#include "game/state.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "grid/figure.h"
#include "grid/image.h"
#include "grid/terrain.h"
#include "input/scroll.h"
#include "game/game_config.h"
#include "io/gamefiles/lang.h"
#include "platform/renderer.h"
#include "scenario/scenario.h"
#include "sound/sound_city.h"
#include "sound/effect.h"
#include "sound/sound.h"
#include "widget/city/ornaments.h"
#include "widget/city/tile_draw.h"
#include "widget/widget_minimap.h"
#include "window/window_building_info.h"
#include "window/window_city.h"
#include "window/window_city_military.h"
#include "game/game.h"
#include "overlays/city_overlay.h"
#include "building/building.h"
#include "dev/debug.h"

screen_city_t g_screen_city;

void set_city_clip_rectangle(painter &ctx) {
    vec2i view_pos, view_size;
    city_view_get_viewport(*ctx.view, view_pos, view_size);
    graphics_set_clip_rectangle(view_pos, view_size);
}

void screen_city_t::update_zoom_level(painter &ctx) {
    vec2i offset = camera_get_position();

    if (g_zoom.update_value(&offset)) {
        city_view_refresh_viewport();
        camera_go_to_pixel(ctx, offset, true);
        sound_city_decay_views();
    }
}

void screen_city_t::scroll_map(const mouse* m) {
    vec2i delta;
    if (scroll_get_delta(m, &delta, SCROLL_TYPE_CITY)) {
        camera_scroll(delta.x, delta.y);
        sound_city_decay_views();
    }
}

tile2i screen_city_t::update_city_view_coords(vec2i pixel) {
    if (!pixel_is_inside_viewport(pixel)) {
        return tile2i(0);
    }

    vec2i screen = pixel_to_screentile(pixel);
    if (screen.x != -1 && screen.y != -1) {
        city_view_set_selected_view_tile(&screen);
        return screen_to_tile(screen);
    }

    return tile2i::invalid;
}

int screen_city_t::input_coords_in_city(int x, int y) {
    vec2i view_pos, view_size;
    city_view_get_viewport(g_city_view, view_pos, view_size);

    x -= view_pos.x;
    y -= view_pos.y;

    return (x >= 0 && x < view_size.x && y >= 0 && y < view_size.y);
}

static void draw_TEST(vec2i pixel, tile2i point, painter &ctx) {
    int grid_offset = point.grid_offset();

    // NO grid_offset outside of the valid map area can be accessed -- the ones passed through here will ALWAYS be set
    // to -1. so it's impossible to draw outside the map with these!
    if (grid_offset == -1)
        return;
    //    int tx = MAP_X(grid_offset);
    //    int ty = MAP_Y(grid_offset);
    //    if (tx==40 && ty==44)
    //        return ImageDraw::isometric_footprint_from_drawtile(image_id_from_group(GROUP_TERRAIN_GARDEN), x, y,
    //        COLOR_CHANNEL_RED);
    const auto &params = building_static_params::get(BUILDING_GARDENS);
    const auto &anim = params.base_img();
    if (map_grid_inside_map_area(grid_offset, 1)) {
        auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
        command.image_id = anim;
        command.pixel = pixel;
        command.mask = COLOR_CHANNEL_GREEN;
        return;
    }
}

void draw_tile_boxes(vec2i pixel, tile2i point) {
    if (map_property_is_draw_tile(point.grid_offset())) {
        int tile_size = map_property_multi_tile_size(point.grid_offset());
        debug_draw_tile_box(pixel.x, pixel.y, tile_size, tile_size);
    }
};

void update_tile_coords(vec2i pixel, tile2i tile, painter &ctx) {
    record_mappoint_pixelcoord(tile, pixel);
}

void screen_city_t::update_clouds(painter &ctx) {
    if (game.paused || (!window_is(WINDOW_CITY) && !window_is(WINDOW_CITY_MILITARY))) {
        g_clouds.pause();
    }

    auto mm_view = g_city_view.get_scrollable_pixel_limits();
    const vec2i offset = {
        g_city_view.camera.position.x - mm_view.min.x,
        g_city_view.camera.position.y - mm_view.min.y,
    };

    const vec2i limit = {
        GRID_LENGTH * TILE_WIDTH_PIXELS,
        GRID_LENGTH * TILE_HEIGHT_PIXELS,
    };

    g_clouds.draw(ctx, mm_view.min, offset, limit);
}

void screen_city_t::clear_current_tile() {
    current_tile = tile2i::invalid;
    selected_tile = tile2i::invalid;
}

void screen_city_t::draw_figures_on_flat_tiles(vec2i pixel, tile2i tile, painter &ctx) {
    auto figures = map_figures_in_row(tile);

    for (const auto &f : figures) {
        const figure_static_params &params = figure_static_params::get(f.f->type);
        if (!params.render_on_flat_tiles) {
            continue;
        }

        const bool should_draw_main = !f.f->is_main_drawn;
        if (!should_draw_main) {
            continue;
        }

        if (f.f->main_cached_pos.x < (pixel.x - TILE_WIDTH_PIXELS) || f.f->main_cached_pos.x >(pixel.x + TILE_WIDTH_PIXELS)) {
            continue;
        }

        if (!selected_figure_id) {
            int highlight = (f.f->formation_id > 0) && (f.f->formation_id == highlighted_formation);
            f.f->city_draw_figure(ctx, highlight);
        } else if (f.f->id == selected_figure_id) {
            f.f->city_draw_figure(ctx, 0);
        }
    }
}

void screen_city_t::draw_figures(vec2i pixel, tile2i tile, painter &ctx, bool force) {
    auto figures = map_figures_in_row(tile);

    for (const auto &f : figures) {
        const figure_static_params &params = figure_static_params::get(f.f->type);
        if (params.render_on_flat_tiles) {
            continue; // Skip figures that render on flat tiles
        }

        const bool should_draw_main = !f.f->is_main_drawn;
        const bool should_draw_cart = (f.draw_cart && !f.f->is_cart_drawn);
        if (!should_draw_main && !should_draw_cart && !force) {
            continue;
        }

        if (should_draw_main) { // draw main
            if (f.f->main_cached_pos.x < (pixel.x - TILE_WIDTH_PIXELS) || f.f->main_cached_pos.x >(pixel.x + TILE_WIDTH_PIXELS)) {
                continue;
            }

            if (!selected_figure_id) {
                int highlight = (f.f->formation_id > 0) && (f.f->formation_id == highlighted_formation);
                f.f->city_draw_figure(ctx, highlight);
            } else if (f.f->id == selected_figure_id) {
                f.f->city_draw_figure(ctx, 0);
            }
        } 
        
        if (should_draw_cart) { // draw cart
            if (f.f->cart_cached_pos.x < (pixel.x - TILE_WIDTH_PIXELS) || f.f->cart_cached_pos.x >(pixel.x + TILE_WIDTH_PIXELS)) {
                continue;
            }

            f.f->draw_figure_cart(ctx, f.f->cart_cached_pos, 0);
        }
    }
}

void screen_city_t::draw_figures_overlay(vec2i pixel, tile2i tile, painter &ctx) {
    int grid_offset = tile.grid_offset();
    auto figures = map_figures_in_row(tile);

    for (const auto &f : figures) {
        const figure_static_params &params = figure_static_params::get(f.f->type);
        if (params.render_on_flat_tiles) {
            continue; // Skip figures that render on flat tiles
        }

        if (!g_city.overlay()->show_figure(f.f)) {
            continue;
        }

        if (f.f->is_main_drawn) {
            continue;
        }

        if (f.f->main_cached_pos.x < (pixel.x - TILE_WIDTH_PIXELS) || f.f->main_cached_pos.x >(pixel.x + TILE_WIDTH_PIXELS)) {
            continue;
        }

        if (!selected_figure_id) {
            int highlight = f.f->formation_id > 0 && f.f->formation_id == highlighted_formation;
            f.f->city_draw_figure(ctx, highlight);
        } else if (f.f->id == selected_figure_id) {
            f.f->city_draw_figure(ctx, 0);
        }
    }
}

void screen_city_t::draw_isometric_mark_sound(int building_id, int grid_offset, color &color_mask, int direction) {
    if (building_id) {
        building *b = building_get(building_id);
        if (!!game_features::gameui_visual_feedback_on_delete && drawing_building_as_deleted(b)) {
            color_mask = COLOR_MASK_RED;
        }

        sound_city_mark_building_view(b, direction);
    } else {
        int terrain = map_terrain_get(grid_offset);
        sound_city_mark_terrain_view(terrain, grid_offset, direction);
    }
}

void screen_city_t::draw_without_overlay(painter &ctx, int selected_figure_id) {
    highlighted_formation = 0;
    if (!!game_features::gameui_highlight_legions) {
        highlighted_formation = formation_batalion_at(current_tile);
        if (highlighted_formation > 0 && formation_get(highlighted_formation)->in_distant_battle) {
            highlighted_formation = 0;
        }
    }

    this->selected_figure_id = selected_figure_id;

    render_ctx.init();

    g_city_planner.ghost_mark_deleting(current_tile);

    map_render_clear();
    ImageDraw::clear_render_commands();

    clear_mappoint_pixelcoord();
    city_view_foreach_valid_map_tile(ctx, update_tile_coords);

    map_figure_sort_by_y();
    city_view_foreach_valid_map_tile(ctx, 
        [this] (vec2i pixel, tile2i tile, painter &ctx) { draw_isometric_flat(pixel, tile, ctx); },
        [this] (vec2i pixel, tile2i tile, painter &ctx) { draw_figures_on_flat_tiles(pixel, tile, ctx); },
        draw_ornaments_flat
    );

    city_view_foreach_valid_map_tile(ctx, 
        [this] (vec2i pixel, tile2i tile, painter &ctx) { draw_isometric_terrain_height(pixel, tile, ctx); }
    );

    ImageDraw::apply_render_commands(ctx);

    // Experimental: draw debug layer after flat map rendering
    draw_debug_animal_spawn_areas(ctx);
    ImageDraw::apply_render_commands(ctx);

       
    city_view_foreach_valid_map_tile(ctx,
        [this] (vec2i pixel, tile2i tile, painter& ctx) { draw_isometric_nonterrain_height(pixel, tile, ctx); },
        [this] (vec2i pixel, tile2i tile, painter &ctx) { draw_ornaments_and_animations_height(pixel, tile, ctx); },
        [this] (vec2i pixel, tile2i tile, painter &ctx) { draw_figures(pixel, tile, ctx, false); }
    );

    ImageDraw::apply_render_commands(ctx);

    if (!selected_figure_id) {
        g_city_planner.update(current_tile);
        g_city_planner.draw(ctx);
    }

    // finally, draw these on top of everything else
    city_view_foreach_valid_map_tile(ctx, draw_debug_tile);
    debug_draw_figures();

    ImageDraw::apply_render_commands(ctx);

    update_clouds(ctx);
}

void screen_city_t::debug_draw_figures() {
    for (auto &f : map_figures()) {
        f->draw_debug();
    }
}

void screen_city_t::draw_isometric_flat(vec2i pixel, tile2i tile, painter &ctx) {
    // black tile outside of map
    const bool is_tree = map_terrain_is(tile, TERRAIN_TREE);
    const bool is_water = map_terrain_is(tile, TERRAIN_WATER);
    const bool outside_map = is_tree && is_water;
    if (!tile.valid() || outside_map) {
        auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
        command.image_id = image_id_from_group(GROUP_TERRAIN_UGLY_GRASS);
        command.pixel = pixel;
        command.mask = COLOR_MASK_NONE;
        return;
    }

    g_city_planner.construction_record_view_position(pixel, tile);
    int building_id = map_building_at(tile);

    color color_mask = COLOR_MASK_NONE;
    bool deletion_tool = (g_city_planner.build_type == BUILDING_CLEAR_LAND && g_city_planner.end == tile);
    if (deletion_tool || map_property_is_deleted(tile)) {
        color_mask = COLOR_MASK_RED;
    }

    bool force_tile_draw = false;
    if (!map_property_is_draw_tile(tile)) {
        bool force_tile_draw = false;
        if (building_id > 0) {
            building_impl *b = building_get(building_id)->dcast();
            force_tile_draw = b->force_draw_flat_tile(ctx, tile, pixel, color_mask);
        }

        if (!force_tile_draw) {
            return;
        }
    }

    vec2i view_pos, view_size;
    city_view_get_viewport(*ctx.view, view_pos, view_size);
    int direction = SOUND_DIRECTION_CENTER;
    if (pixel.x < view_pos.x + 100) {
        direction = SOUND_DIRECTION_LEFT;
    } else if (pixel.x > view_pos.x + view_size.x - 100) {
        direction = SOUND_DIRECTION_RIGHT;
    }

    draw_isometric_mark_sound(building_id, tile.grid_offset(), color_mask, direction);

    int image_id = map_image_at(tile);
    if (render_ctx.advance_water_animation) {
        if (image_id >= render_ctx.image_id_water_first && image_id <= render_ctx.image_id_water_last) {
            image_id++; // wrong, but eh
            if (image_id > render_ctx.image_id_water_last) {
                image_id = render_ctx.image_id_water_first;
            }
        }

        if (image_id >= render_ctx.image_id_deepwater_first && image_id <= render_ctx.image_id_deepwater_last) {
            image_id += 15;

            if (image_id > render_ctx.image_id_deepwater_last) {
                image_id -= 90;
            }
        }
        map_image_set(tile, image_id);
    }

    if (map_property_is_constructing(tile)) {
        image_id = image_id_from_group(GROUP_TERRAIN_OVERLAY_FLAT);
    }

    const bool is_green_tile = map_terrain_is(tile, TERRAIN_PLANER_FUTURE);
    if (is_green_tile && (color_mask == COLOR_MASK_NONE)) {
        color_mask = COLOR_MASK_GREEN;
    }

    const image_t* img = image_get(image_id);
    if (!img) {
        return;
    }

    auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
    command.image_id = image_id;
    command.pixel = pixel;
    command.mask = color_mask;

    int image_alt_value = map_image_alt_at(tile);
    int image_alt_id = (image_alt_value & 0x00ffffff);
    uint8_t image_alt_alpha = ((image_alt_value & 0xff000000) >> 24);
    if (image_alt_id > 0 && image_alt_alpha > 0) {
        auto& command = ImageDraw::create_subcommand(render_command_t::ert_drawtile);
        command.image_id = image_alt_id;
        command.pixel = pixel;
        command.mask = (0x00ffffff | (image_alt_alpha << 24));
        command.flags = ImgFlag_Alpha;
    }

    int top_height = img->isometric_top_height();
    map_render_set(tile, (top_height > 0) ? RENDER_TALL_TILE : 0);
}

void screen_city_t::draw_isometric_nonterrain_height(vec2i pixel, tile2i tile, color mask, painter &ctx) {
    color save = force_mask;
    force_mask = mask;
    draw_isometric_nonterrain_height(pixel, tile, ctx);
    force_mask = save;
}

void screen_city_t::draw_isometric_nonterrain_height(vec2i pixel, tile2i tile, painter &ctx) {
    int grid_offset = tile.grid_offset();
    // black tile outside of map
    if (grid_offset < 0) {
        auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
        command.image_id = image_id_from_group(GROUP_TERRAIN_BLACK);
        command.pixel = pixel;
        command.mask = COLOR_BLACK;
        return;
    }

    g_city_planner.construction_record_view_position(pixel, tile);
    int building_id = map_building_at(grid_offset);

    color color_mask = force_mask;
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
    bool tall_flat_tile_drawn = map_render_is(grid_offset, RENDER_TALL_TILE_DRAWN);
    bool should_draw = building_id > 0 || (tall_flat_tile && !tall_flat_tile_drawn);
    if (!should_draw) {
        return;
    }

    int image_id = map_image_at(grid_offset);
    if (tall_flat_tile) {
        {
            auto& command = ImageDraw::create_command(render_command_t::ert_drawtile_top);
            command.image_id = image_id;
            const image_t* img = image_get(image_id);
            int offset_y = 15 * (img->width / 58);
            command.pixel = pixel - vec2i{ 0, offset_y };
            command.mask = color_mask;
            command.tag = (building_id == 261);
            command.use_sort_pixel = true;
            command.sort_pixel = pixel;
        }

        int image_alt_value = map_image_alt_at(grid_offset);
        int image_alt_id = (image_alt_value & 0x00ffffff);
        uint8_t image_alt_alpha = ((image_alt_value & 0xff000000) >> 24);
        if (image_alt_id > 0 && image_alt_alpha > 0) {
            auto& command = ImageDraw::create_subcommand(render_command_t::ert_drawtile_top);
            const image_t *img = image_get(image_alt_id);
            int offset_y = 15 * (img->width / 58);
            command.image_id = image_alt_id;
            command.pixel = pixel;
            command.mask = (0x00ffffff | (image_alt_alpha << 24));
            command.flags = ImgFlag_Alpha;
        }
        return;
    }
}

void screen_city_t::draw_isometric_terrain_height(vec2i pixel, tile2i tile, painter &ctx) {
    // black tile outside of map
    if (!tile.valid()) {
        auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
        command.image_id = image_id_from_group(GROUP_TERRAIN_BLACK);
        command.pixel = pixel;
        command.mask = COLOR_BLACK;
        return;
    }

    g_city_planner.construction_record_view_position(pixel, tile);
    if (!map_property_is_draw_tile(tile)) {
        return;
    }

    bool tall_flat_tile = map_render_is(tile.grid_offset(), RENDER_TALL_TILE);
    if (!tall_flat_tile) {
        return;
    }

    const bool non_terrain = map_terrain_is(tile, TERRAIN_TREE | TERRAIN_ROCK | TERRAIN_BUILDING | TERRAIN_ELEVATION | TERRAIN_WALL | TERRAIN_GATEHOUSE);
    if (non_terrain) {
        return;
    }

    map_render_set(tile, 0);
    color color_mask = COLOR_MASK_NONE;
    bool deletion_tool = (g_city_planner.build_type == BUILDING_CLEAR_LAND && g_city_planner.end == tile);
    if (deletion_tool || map_property_is_deleted(tile)) {
        color_mask = COLOR_MASK_RED;
    }

    map_render_add(tile.grid_offset(), RENDER_TALL_TILE_DRAWN);
    {
        int image_id = map_image_at(tile);
        auto& command = ImageDraw::create_command(render_command_t::ert_drawtile_top);
        const image_t *img = image_get(image_id);
        int offset_y = 15 * (img->width / 58) - 1;
            command.image_id = image_id;
            command.pixel = pixel - vec2i(0, offset_y );
            command.mask = color_mask;
            command.use_sort_pixel = true;
            command.sort_pixel = pixel;
        //command.virtual_xorder = TILE_WIDTH_PIXELS;
    } 

    {
        int image_alt_value = map_image_alt_at(tile);
        int image_alt_id = (image_alt_value & 0x00ffffff);
        uint8_t image_alt_alpha = ((image_alt_value & 0xff000000) >> 24);
        if (image_alt_id > 0 && image_alt_alpha > 0) {
            auto &command = ImageDraw::create_subcommand(render_command_t::ert_drawtile_top);
            command.image_id = image_alt_id;
            const image_t *img = image_get(image_alt_id);
            int offset_y = 15 * (img->width / 58) - 1;
            command.pixel = pixel - vec2i(0, offset_y);
            command.mask = (0x00ffffff | (image_alt_alpha << 24));
            command.flags = ImgFlag_Alpha;
        }
    }
}

void screen_city_t::draw_ornaments_and_animations_height(vec2i point, tile2i tile, painter &ctx) {
    int grid_offset = tile.grid_offset();
    // tile must contain image draw data
    if (!map_property_is_draw_tile(grid_offset)) {
        return;
    }


    building *b = building_at(grid_offset);
    if (b->type == 0 || b->state == BUILDING_STATE_UNUSED) {
        return;
    }

    // draw in red if necessary
    int color_mask = force_mask;
    if (drawing_building_as_deleted(b) || map_property_is_deleted(grid_offset)) {
        color_mask = COLOR_MASK_RED;
    }

    b->dcast()->draw_ornaments_and_animations_height(ctx, point, tile, color_mask);
}

void screen_city_t::draw_ornaments_overlay(vec2i pixel, tile2i point, painter &ctx) {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;
    int b_id = map_building_at(grid_offset);

    if (b_id) {
        const building *b = building_at(grid_offset);
        if (g_city.overlay()->show_building(b)) {
            color save = force_mask;
            force_mask = g_city.overlay()->color_mask_building_def(b);
            draw_ornaments_and_animations_height(pixel, point, ctx);
            force_mask = save;
        }
    } else {
        draw_ornaments_and_animations_height(pixel, point, ctx);
    }
}


void screen_city_t::draw_with_overlay(painter &ctx) {
    const auto overlay = g_city.overlay();
    if (!overlay) {
        return;
    }

    map_render_clear();
    ImageDraw::clear_render_commands();

    g_city_planner.ghost_mark_deleting(current_tile);
    city_view_foreach_valid_map_tile(ctx, update_tile_coords);

    map_figure_sort_by_y();
    city_view_foreach_valid_map_tile(ctx, draw_isometrics_overlay_flat);

    ImageDraw::apply_render_commands(ctx);

    city_view_foreach_valid_map_tile(ctx,
        draw_isometrics_overlay_height,
        [this] (vec2i pixel, tile2i tile, painter &ctx) { draw_ornaments_overlay(pixel, tile, ctx); },
        [this] (vec2i pixel, tile2i tile, painter &ctx) { draw_figures_overlay(pixel, tile, ctx); }
    );

    ImageDraw::apply_render_commands(ctx);

    g_city_planner.update(current_tile);
    g_city_planner.draw(ctx);

    ImageDraw::apply_render_commands(ctx);

    // finally, draw these on top of everything else
    city_view_foreach_valid_map_tile(ctx, draw_debug_tile);
    debug_draw_figures();

    ImageDraw::apply_render_commands(ctx);

    update_clouds(ctx);
}

void screen_city_t::draw(painter &ctx) {
    update_zoom_level(ctx);
    set_render_scale(ctx, g_zoom.get_scale());
    set_city_clip_rectangle(ctx);

    if (g_city.overlay()) {
        draw_with_overlay(ctx);
    } else {
        draw_without_overlay(ctx, 0);
    }

    graphics_reset_clip_rectangle();
    set_render_scale(ctx, 1.0f);
}

void screen_city_t::draw_for_figure(painter &ctx, int figure_id) {
    set_city_clip_rectangle(ctx);

    draw_without_overlay(ctx, figure_id);

    graphics_reset_clip_rectangle();
}

// INPUT HANDLING

static void build_move(tile2i tile) {
    if (!g_city_planner.in_progress)
        return;
    g_city_planner.construction_update(tile);
}

static void build_end(void) {
    if (g_city_planner.in_progress) {
        if (g_city_planner.build_type != BUILDING_NONE)
            g_sound.play_effect(SOUND_EFFECT_BUILD);

        g_city_planner.construction_finalize();
    }
}

static bool has_confirmed_construction(tile2i ghost, tile2i point, int range_size) {
    //    map_point point = map_point(tile_offset);
    switch (city_view_orientation()) {
    case DIR_0_TOP_RIGHT:
        point.shift(-range_size + 1, -range_size + 1);
    case DIR_2_BOTTOM_RIGHT:
        point.shift(0, -range_size + 1);
    case DIR_6_TOP_LEFT:
        point.shift(-range_size + 1, 0);
    }
    //    tile_offset = point.grid_offset();

    //    int x = map_grid_offset_to_x(tile_offset);
    //    int y = map_grid_offset_to_y(tile_offset);
    if (ghost.grid_offset() <= 0 || !map_grid_is_inside(point, range_size))
        return false;

    for (int dy = 0; dy < range_size; dy++) {
        for (int dx = 0; dx < range_size; dx++) {
            if (ghost == point.shifted(dx, dy)) // tile_offset + GRID_OFFSET(dx, dy)
                return true;
        }
    }
    return false;
}

bool screen_city_t::allow_building_info(tile2i tile) {
    int allow = true;
    if (!window_is(WINDOW_CITY)) {
        allow = false;
    }

    window_city_show();

    if (!tile.valid()) {
        allow = false;
    }

    return allow;
}

bool screen_city_t::handle_legion_click(tile2i tile) {
    if (!tile.valid()) {
        return false;
    }

    int formation_id = formation_batalion_at(tile);
    if (formation_id > 0 && !formation_get(formation_id)->in_distant_battle) {
        window_city_military_show(formation_id);
        return true;
    }

    return false;
}

bool screen_city_t::handle_cancel_construction_button(const touch_t * t) {
    if (!g_city_planner.build_type)
        return false;

    vec2i view_pos, view_size;
    city_view_get_viewport(g_city_view, view_pos, view_size);
    int box_size = 5 * 16;
    view_size.x -= box_size;

    if (t->current_point.x < view_size.x || t->current_point.x >= view_size.x + box_size || t->current_point.y < 24
        || t->current_point.y >= 40 + box_size) {
        return false;
    }

    g_city_planner.construction_cancel();
    return true;
}

void screen_city_t::handle_touch_scroll(const touch_t * t, bool fore_capture_input) {
    struct holder_capture_input {
        holder_capture_input(screen_city_t& s, const touch_t *t, bool h) : screen(s), touch(t), hold(h) {
            if (hold && t->has_started) {
                screen.capture_input = true;
            }
        }

        ~holder_capture_input() {
            if (hold && touch->has_ended) {
                screen.capture_input = false;
            }
        }

        screen_city_t &screen;
        const touch_t *touch = nullptr;
        bool hold = false;
    };

    holder_capture_input capture_holder(*this, t, fore_capture_input);

    if (g_city_planner.build_type) {
        if (t->has_started) {
            vec2i view_pos, view_size;
            city_view_get_viewport(g_city_view, view_pos, view_size);
            scroll_set_custom_margins(view_pos.x, view_pos.y, view_size.x, view_size.y);
        }
        if (t->has_ended) {
            scroll_restore_margins();
        }

        return;
    }
    scroll_restore_margins();

    if (!capture_input) {
        return;
    }

    int was_click = touch_was_click(get_latest_touch());
    if (t->has_started || was_click) {
        scroll_drag_start(1);
        return;
    }

    if (!touch_not_click(t)) {
        return;
    }

    if (t->has_ended) {
        scroll_drag_end();
    }
}

static void handle_touch_zoom(const touch_t * first, const touch_t * last) {
    if (touch_not_click(first))
        g_zoom.handle_touch(first, last, g_zoom.get_percentage());

    if (first->has_ended || last->has_ended)
        g_zoom.end_touch();
}

void screen_city_t::handle_first_touch(tile2i tile) {
    const touch_t * first = get_earliest_touch();
    e_building_type type = g_city_planner.build_type;

    if (touch_was_click(first)) {
        if (handle_cancel_construction_button(first) || handle_legion_click(tile)) {
            return;
        }

        if (type == BUILDING_NONE && allow_building_info(tile)) {
            scroll_drag_end();
            capture_input = false;
            events::emit(event_show_tile_info{ tile, false, SOURCE_LOCATION });
            return;
        }
    }

    handle_touch_scroll(first, false);

    if (!input_coords_in_city(first->current_point.x, first->current_point.y) || type == BUILDING_NONE)
        return;

    if (g_city_planner.has_flag_set(e_building_flag::Draggable)) {
        if (!g_city_planner.in_progress) {
            if (first->has_started) {
                g_city_planner.construction_start(tile);
                new_start_grid_offset = 0;
            }
        } else {
            if (first->has_started) {
                if (selected_tile.grid_offset() != tile.grid_offset()) {
                    new_start_grid_offset = tile.grid_offset();
                }
            }
            if (touch_not_click(first) && new_start_grid_offset) {
                new_start_grid_offset = 0;
                selected_tile.set(0);
                g_city_planner.construction_cancel();
                g_city_planner.construction_start(tile);
            }
            build_move(tile);
            if (selected_tile.grid_offset() != tile.grid_offset())
                selected_tile.set(0);

            if (first->has_ended) {
                if (selected_tile == tile) {
                    build_end();
                    clear_current_tile();
                    new_start_grid_offset = 0;
                } else {
                    selected_tile = tile;
                }
            }
        }
        return;
    }

    int size = building_static_params::get(type).building_size;
    if (type == BUILDING_STORAGE_YARD) {
        size = 3;
    }

    if (touch_was_click(first) && first->has_ended && capture_input
        && has_confirmed_construction(selected_tile, tile, size)) {
        g_city_planner.construction_start(selected_tile);
        build_move(selected_tile);
        build_end();
        clear_current_tile();
    } else if (first->has_ended) {
        selected_tile = tile;
    }
}

static void handle_last_touch(void) {
    const touch_t * last = get_latest_touch();
    if (!last->in_use)
        return;
    if (touch_was_click(last)) {
        g_city_planner.construction_cancel();
        return;
    }

    if (touch_not_click(last)) {
        handle_touch_zoom(get_earliest_touch(), last);
    }
}

void screen_city_t::handle_touch() {
    const touch_t * first = get_earliest_touch();
    if (!first->in_use) {
        scroll_restore_margins();
        return;
    }

    if (!g_city_planner.in_progress || input_coords_in_city(first->current_point.x, first->current_point.y)) {
        current_tile = update_city_view_coords(first->current_point);
    }

    if (first->has_started && input_coords_in_city(first->current_point.x, first->current_point.y)) {
        capture_input = true;
        scroll_restore_margins();
    }

    handle_last_touch();
    handle_first_touch(current_tile);

    if (first->has_ended) {
        capture_input = false;
    }

    g_city_planner.draw_as_constructing = false;
}

void screen_city_t::military_map_click(int legion_formation_id, tile2i tile) {
    if (!tile.valid()) {
        window_city_show();
        return;
    }

    formation *m = formation_get(legion_formation_id);
    if (m->in_distant_battle || m->cursed_by_seth) {
        return;
    }

    int other_formation_id = formation_batalion_at_building(tile.grid_offset());
    if (other_formation_id && other_formation_id == legion_formation_id) {
        formation_batalion_return_home(m);
    } else {
        formation_batalion_move_to(m, tile);
        g_sound.speech_play_file("Wavs/cohort5.wav", 255);
    }

    window_city_show();
}

void screen_city_t::handle_input_military(const mouse *m, const hotkeys *h, int legion_formation_id) {
    current_tile = update_city_view_coords(*m);

    if (!city_view_is_sidebar_collapsed() && widget_minimap_handle_mouse(m)) {
        return;
    }

    if (m->is_touch) {
        const touch_t *t = get_earliest_touch();
        if (!t->in_use) {
            return;
        }

        handle_touch_scroll(t, true);
    }

    scroll_map(m);

    if (m->right.went_up || h->escape_pressed) {
        capture_input = false;
        g_warning_manager.clear_all();
        window_city_show();
        return;
    }

    current_tile = update_city_view_coords(*m);

    const bool m_left_down = (!m->is_touch && m->left.went_down);
    const auto *early_touch = get_earliest_touch();
    const bool m_has_touch = (m->is_touch && m->left.went_up && touch_was_click(early_touch));

    if (m_left_down || m_has_touch) {
        const tile2i tile = current_tile;
        military_map_click(legion_formation_id, tile);
    }
}

void screen_city_t::handle_mouse(const mouse* m) {
    current_tile = update_city_view_coords(*m);

    const float old_zoom_target = g_zoom.ftarget();
    painter ctx = game.painter();
    g_zoom.handle_mouse(m);
    if (!ctx.view->can_update(g_zoom.ftarget())) {
        g_zoom.set_scale(old_zoom_target);
    }

    g_city_planner.draw_as_constructing = false;
    if (m->left.went_down) {
        if (handle_legion_click(current_tile)) {
            return;
        }
        
        g_city_planner.construction_start(current_tile);

        build_move(current_tile);
    } else if (m->left.is_down || g_city_planner.in_progress) {
        build_move(current_tile);
    }

    if (m->left.went_up) {
        build_end();
    }

    if (m->middle.went_down && input_coords_in_city(m->x, m->y) && !g_city_planner.build_type) {
        scroll_drag_start(0);
    }

    bool action_in_warnings = false;
    if (g_warning_manager.has_warnings()) {
        action_in_warnings = g_warning_manager.handle_mouse(m);
    }

    if (m->right.went_up && !action_in_warnings) {
        if (g_city_planner.construction_active()) {
            g_city_planner.construction_cancel();
        } else {
            if (allow_building_info(current_tile)) {
                events::emit(event_show_tile_info{ current_tile, false, SOURCE_LOCATION });
            }
        }
    }

    if (m->middle.went_up) {
        scroll_drag_end();
    }
}
void screen_city_t::handle_escape(const hotkeys *h) {
    if (!h->escape_pressed) {
        return;
    }

    if (g_city_planner.build_type) {
        g_city_planner.construction_cancel();
        return;
    }

    hotkey_handle_escape();
}

void screen_city_t::handle_input(const mouse* m, const hotkeys* h) {
    scroll_map(m);

    if (m->is_touch) {
        handle_touch();
    } else {
        handle_mouse(m);
    }

    handle_escape(h);
}

xstring screen_city_t::get_overlay_tooltip(tooltip_context *c, tile2i tile) {
    const auto overlay = g_city.overlay();
    if (!overlay) {
        return {};
    }

    int overlay_type = overlay->get_type();
    int building_id = map_building_at(tile);
    if (!building_id) {
        return {};
    }

    int overlay_requires_house = (overlay_type != OVERLAY_WATER) && (overlay_type != OVERLAY_FIRE)
        && (overlay_type != OVERLAY_DAMAGE) && (overlay_type != OVERLAY_NATIVE)
        && (overlay_type != OVERLAY_DESIRABILITY);

    auto b = building_get(building_id);
    auto house = b->dcast_house();
    if (overlay_requires_house && !house) {
        return {};
    }

    xstring tooltip = ((city_overlay*)overlay)->get_tooltip_for_building(c, b);
    if (!tooltip) {
        tooltip = overlay->get_tooltip(c, tile);
    }

    return tooltip;
}

void screen_city_t::draw_tooltip(tooltip_context* c) {
    if (g_settings.tooltips == e_tooltip_show_none) {
        return;
    }

    if (!window_is(WINDOW_CITY)) {
        return;
    }

    if (!current_tile.valid()) {
        return;
    }

    if (g_city.overlay()) {
        c->high_priority = 1;
        c->text = get_overlay_tooltip(c, current_tile);
    }

    int building_id = map_building_at(current_tile);
    building_impl *b = building_get(building_id)->dcast();
    b->draw_tooltip(c);
    // cheat tooltips
    //if (game.current_overlay == OVERLAY_NONE && game_cheat_tooltip_enabled()) {
    //    c->type = TOOLTIP_TILES;
    //    c->high_priority = 1;
    //    return;
    //}
    //
    //// overlay tooltips
    
}

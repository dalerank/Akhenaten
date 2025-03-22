#include "dev/debug.h"

#include "graphics/clouds.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/view/lookup.h"
#include "graphics/view/view.h"
#include "grid/property.h"
#include "widget/city/building_ghost.h"
#include "overlays/city_overlay.h"
#include "building/construction/build_planner.h"
#include "city/finance.h"
#include "city/city_warnings.h"
#include "core/calc.h"
#include "core/string.h"
#include "figure/formation_legion.h"
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
#include "config/config.h"
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
        return screentile_to_mappoint(screen);
    }

    return tile2i(0);
}

int screen_city_t::input_coords_in_city(int x, int y) {
    vec2i view_pos, view_size;
    view_data_t viewport = city_view_viewport();
    city_view_get_viewport(viewport, view_pos, view_size);

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
    const auto &params = building_impl::params(BUILDING_GARDENS);
    const auto &anim = params.anim["base"].first_img();
    if (map_grid_inside_map_area(grid_offset, 1)) {
        ImageDraw::isometric_from_drawtile(ctx, anim, pixel, COLOR_CHANNEL_GREEN);
        return;
    }
    //    if (!map_grid_is_inside(tx, ty, 1))
    //        return ImageDraw::isometric_footprint_from_drawtile(image_id_from_group(GROUP_TERRAIN_GARDEN), x, y,
    //        COLOR_CHANNEL_RED);
    //    else
    //        return ImageDraw::isometric_footprint_from_drawtile(image_id_from_group(GROUP_TERRAIN_GARDEN), x, y,
    //        COLOR_CHANNEL_GREEN);
}

static void draw_tile_boxes(vec2i pixel, tile2i point) {
    if (map_property_is_draw_tile(point.grid_offset())) {
        int tile_size = map_property_multi_tile_size(point.grid_offset());
        debug_draw_tile_box(pixel.x, pixel.y, tile_size, tile_size);
    }
};

static void update_tile_coords(vec2i pixel, tile2i tile, painter &ctx) {
    record_mappoint_pixelcoord(tile, pixel);
}

void screen_city_t::update_clouds(painter &ctx) {
    if (game.paused || (!window_is(WINDOW_CITY) && !window_is(WINDOW_CITY_MILITARY))) {
        clouds_pause();
    }

    auto& viewdata = city_view_data_unsafe();
    vec2i min_pos, max_pos;
    city_view_get_camera_scrollable_pixel_limits(viewdata, min_pos, max_pos);
    const vec2i offset = {
        viewdata.camera.position.x - min_pos.x,
        viewdata.camera.position.y - min_pos.y,
    };

    const vec2i limit = {
        GRID_LENGTH * TILE_WIDTH_PIXELS,
        GRID_LENGTH * TILE_HEIGHT_PIXELS,
    };

    clouds_draw(ctx, min_pos, offset, limit);
}

void screen_city_t::clear_current_tile() {
    current_tile = tile2i::invalid;
    selected_tile = tile2i::invalid;
}

void screen_city_t::draw_figures(vec2i pixel, tile2i tile, painter &ctx, bool force) {
    auto figures = map_figures_in_row(tile);

    for (auto *f : figures) {
        if (f->is_drawn && !force) {
            continue;
        }

        if (f->cached_pos.x < (pixel.x - TILE_WIDTH_PIXELS) || f->cached_pos.x >(pixel.x + TILE_WIDTH_PIXELS)) {
            continue;
        }

        if (!selected_figure_id) {
            int highlight = f->formation_id > 0 && f->formation_id == highlighted_formation;
            f->city_draw_figure(ctx, highlight);
        } else if (f->id == selected_figure_id) {
            f->city_draw_figure(ctx, 0, selected_figure_coord);
        }
    }
}

void screen_city_t::draw_figures_overlay(vec2i pixel, tile2i tile, painter &ctx) {
    int grid_offset = tile.grid_offset();
    auto figures = map_figures_in_row(tile);

    for (auto *f : figures) {
        if (!get_city_overlay()->show_figure(f)) {
            continue;
        }

        if (f->is_drawn) {
            continue;
        }

        if (f->cached_pos.x < (pixel.x - TILE_WIDTH_PIXELS) || f->cached_pos.x >(pixel.x + TILE_WIDTH_PIXELS)) {
            continue;
        }

        if (!selected_figure_id) {
            int highlight = f->formation_id > 0 && f->formation_id == highlighted_formation;
            f->city_draw_figure(ctx, highlight);
        } else if (f->id == selected_figure_id) {
            f->city_draw_figure(ctx, 0, selected_figure_coord);
        }
    }
}

void screen_city_t::draw_without_overlay(painter &ctx, int selected_figure_id, vec2i* figure_coord) {
    highlighted_formation = 0;
    if (config_get(CONFIG_UI_HIGHLIGHT_LEGIONS)) {
        highlighted_formation = formation_legion_at(current_tile);
        if (highlighted_formation > 0 && formation_get(highlighted_formation)->in_distant_battle) {
            highlighted_formation = 0;
        }
    }

    this->selected_figure_id = selected_figure_id;
    this->selected_figure_coord = figure_coord;

    render_ctx.init();

    g_city_planner.ghost_mark_deleting(current_tile);

    map_render_clear();

    clear_mappoint_pixelcoord();
    city_view_foreach_valid_map_tile(ctx, update_tile_coords);

    auto s_draw_figures = [this] (vec2i pixel, tile2i tile, painter &ctx) {
        draw_figures(pixel, tile, ctx, false);
    };

    map_figure_sort_by_y();
    city_view_foreach_valid_map_tile(ctx, 
        [this] (vec2i pixel, tile2i tile, painter &ctx) { draw_isometric_flat(pixel, tile, ctx); },
        draw_ornaments_flat
    );
    city_view_foreach_valid_map_tile(ctx, 
        [this] (vec2i pixel, tile2i tile, painter &ctx) { draw_isometric_terrain_height(pixel, tile, ctx); }
    );
    city_view_foreach_valid_map_tile(ctx, draw_isometric_nonterrain_height, draw_ornaments_and_animations_height, s_draw_figures);

    if (!selected_figure_id) {
        g_city_planner.update(current_tile);
        g_city_planner.draw(ctx);
    }

    update_clouds(ctx);

    // finally, draw these on top of everything else
    city_view_foreach_valid_map_tile(ctx, draw_debug_tile);
    city_view_foreach_valid_map_tile(ctx, draw_debug_figures);
}

void screen_city_t::draw_isometric_flat(vec2i pixel, tile2i tile, painter &ctx) {
    // black tile outside of map
    if (!tile.valid()) {
        ImageDraw::isometric_from_drawtile(ctx, image_id_from_group(GROUP_TERRAIN_BLACK), pixel, COLOR_BLACK);
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

    const image_t *img = ImageDraw::isometric_from_drawtile(ctx, image_id, pixel, color_mask);
    if (!img) {
        return;
    }

    int image_alt_value = map_image_alt_at(tile);
    int image_alt_id = (image_alt_value & 0x00ffffff);
    uint8_t image_alt_alpha = ((image_alt_value & 0xff000000) >> 24);
    if (image_alt_id > 0 && image_alt_alpha > 0) {
        ImageDraw::isometric_from_drawtile(ctx, image_alt_id, pixel, (0x00ffffff | (image_alt_alpha << 24)), ImgFlag_Alpha);
    }

    int top_height = img->isometric_top_height();
    map_render_set(tile, (top_height > 0) ? RENDER_TALL_TILE : 0);
}

void screen_city_t::draw_isometric_terrain_height(vec2i pixel, tile2i tile, painter &ctx) {
    // black tile outside of map
    if (!tile.valid()) {
        ImageDraw::isometric_from_drawtile(ctx, image_id_from_group(GROUP_TERRAIN_BLACK), pixel, COLOR_BLACK);
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

    int image_id = map_image_at(tile);
    ImageDraw::isometric_from_drawtile_top(ctx, image_id, pixel, color_mask);

    int image_alt_value = map_image_alt_at(tile);
    int image_alt_id = (image_alt_value & 0x00ffffff);
    uint8_t image_alt_alpha = ((image_alt_value & 0xff000000) >> 24);
    if (image_alt_id > 0 && image_alt_alpha > 0) {
        ImageDraw::isometric_from_drawtile_top(ctx, image_alt_id, pixel, (0x00ffffff | (image_alt_alpha << 24)), ImgFlag_Alpha);
    }
}

void screen_city_t::draw_with_overlay(painter &ctx) {
    if (!select_city_overlay()) {
        return;
    }

    map_render_clear();

    g_city_planner.ghost_mark_deleting(current_tile);
    city_view_foreach_valid_map_tile(ctx, update_tile_coords);

    map_figure_sort_by_y();
    city_view_foreach_valid_map_tile(ctx, draw_isometrics_overlay_flat);
    city_view_foreach_valid_map_tile(ctx,
        draw_isometrics_overlay_height,
        draw_ornaments_overlay,
        [this] (vec2i pixel, tile2i tile, painter &ctx) { draw_figures_overlay(pixel, tile, ctx); }
    );
    g_city_planner.update(current_tile);
    g_city_planner.draw(ctx);
}

void screen_city_t::draw(painter &ctx) {
    update_zoom_level(ctx);
    set_render_scale(ctx, g_zoom.get_scale());
    set_city_clip_rectangle(ctx);

    if (game.current_overlay) {
        draw_with_overlay(ctx);
    } else {
        draw_without_overlay(ctx, 0, nullptr);
    }

    graphics_reset_clip_rectangle();
    set_render_scale(ctx, 1.0f);
}

void screen_city_t::draw_for_figure(painter &ctx, int figure_id, vec2i* coord) {
    set_city_clip_rectangle(ctx);

    draw_without_overlay(ctx, figure_id, coord);

    graphics_reset_clip_rectangle();
}

// INPUT HANDLING

static void build_start(tile2i tile) {
    if (tile.grid_offset() > 0) // Allow building on paused
        g_city_planner.construction_start(tile);
}

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

static bool handle_right_click_allow_building_info(tile2i tile) {
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

    int formation_id = formation_legion_at(tile);
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
    view_data_t viewport = city_view_viewport();
    city_view_get_viewport(viewport, view_pos, view_size);
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
            view_data_t viewport = city_view_viewport();
            city_view_get_viewport(viewport, view_pos, view_size);
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
        if (handle_cancel_construction_button(first) || handle_legion_click(tile))
            return;
        if (type == BUILDING_NONE && handle_right_click_allow_building_info(tile)) {
            scroll_drag_end();
            capture_input = false;
            window_info_show(tile);
            return;
        }
    }

    handle_touch_scroll(first, false);

    if (!input_coords_in_city(first->current_point.x, first->current_point.y) || type == BUILDING_NONE)
        return;

    if (g_city_planner.has_flag_set(e_building_flag::Draggable)) {
        if (!g_city_planner.in_progress) {
            if (first->has_started) {
                build_start(tile);
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
                build_start(tile);
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

    int size = building_impl::params(type).building_size;
    if (type == BUILDING_STORAGE_YARD) {
        size = 3;
    }

    if (touch_was_click(first) && first->has_ended && capture_input
        && has_confirmed_construction(selected_tile, tile, size)) {
        build_start(selected_tile);
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

    int other_formation_id = formation_legion_at_building(tile.grid_offset());
    if (other_formation_id && other_formation_id == legion_formation_id) {
        formation_legion_return_home(m);
    } else {
        formation_legion_move_to(m, tile);
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
        g_screen_city.capture_input = false;
        g_warning_manager.clear_all();
        window_city_show();
        return;
    }

    current_tile = update_city_view_coords(*m);

    const bool m_left_down = (!m->is_touch && m->left.went_down);
    const auto *early_touch = get_earliest_touch();
    const bool m_has_touch = (m->is_touch && m->left.went_up && touch_was_click(early_touch));

    if (m_left_down || m_has_touch) {
        const tile2i tile = g_screen_city.current_tile;
        military_map_click(legion_formation_id, tile);
    }
}

void screen_city_t::handle_mouse(const mouse* m) {
    current_tile = update_city_view_coords(*m);

    g_zoom.handle_mouse(m);
    g_city_planner.draw_as_constructing = false;
    if (m->left.went_down) {
        if (handle_legion_click(current_tile)) {
            return;
        }
        
        if (!g_city_planner.in_progress) {
            build_start(current_tile);
        }

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
            if (handle_right_click_allow_building_info(current_tile)) {
                window_info_show(current_tile);
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
    const auto overlay = get_city_overlay();
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

    xstring tooltip = overlay->get_tooltip_for_building(c, b);
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

    if (game.current_overlay != OVERLAY_NONE) {
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

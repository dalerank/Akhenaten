#include "dev/debug.h"

#include "graphics/boilerplate.h"
#include "graphics/view/lookup.h"
#include "graphics/view/view.h"
#include "grid/property.h"
#include "widget/city/building_ghost.h"
#include "overlays/city_overlay.h"
#include "building/construction/build_planner.h"
#include "building/properties.h"
#include "city/finance.h"
#include "city/warning.h"
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
#include "input/scroll.h"
#include "config/config.h"
#include "io/gamefiles/lang.h"
#include "platform/renderer.h"
#include "scenario/property.h"
#include "sound/city.h"
#include "sound/effect.h"
#include "sound/speech.h"
#include "widget/city/figures_cached_draw.h"
#include "widget/city/ornaments.h"
#include "widget/city/tile_draw.h"
#include "widget/minimap.h"
#include "window/window_building_info.h"
#include "window/city.h"
#include "game/game.h"
#include "building/building.h"

struct widget_city_data_t {
    map_point current_tile;
    map_point selected_tile;
    int new_start_grid_offset;
    bool capture_input;
};

widget_city_data_t g_wdiget_city_data;

void set_city_clip_rectangle(painter &ctx) {
    vec2i view_pos, view_size;
    city_view_get_viewport(*ctx.view, view_pos, view_size);
    graphics_set_clip_rectangle(view_pos.x, view_pos.y, view_size.x, view_size.y);

    // TODO?
    //    city_view_foreach_map_tile(draw_outside_map);
    //    int x;
    //    int y;
    //    city_view_get_camera_scrollable_viewspace_clip(&x, &y);
    //    graphics_set_clip_rectangle(x - 30, y, scenario_map_data()->width * 30 - 60, scenario_map_data()->height * 15
    //    - 30);
}

static void update_zoom_level(painter &ctx) {
    vec2i offset = camera_get_position();
    if (zoom_update_value(&offset)) {
        city_view_refresh_viewport();
        camera_go_to_pixel(ctx, offset, true);
        sound_city_decay_views();
    }
}

static void scroll_map(const mouse* m) {
    vec2i delta;
    if (scroll_get_delta(m, &delta, SCROLL_TYPE_CITY)) {
        camera_scroll(delta.x, delta.y);
        sound_city_decay_views();
    }
}
static map_point update_city_view_coords(vec2i pixel) {
    if (!pixel_is_inside_viewport(pixel)) {
        return map_point(0);
    } else {
        screen_tile screen = pixel_to_screentile(pixel);
        if (screen.x != -1 && screen.y != -1) {
            city_view_set_selected_view_tile(&screen);
            return screentile_to_mappoint(screen);
        } else {
            return map_point(0);
        }
    }
}
static int input_coords_in_city(int x, int y) {
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
    if (map_grid_inside_map_area(grid_offset, 1)) {
        return ImageDraw::isometric_from_drawtile(ctx, image_id_from_group(GROUP_TERRAIN_GARDEN), pixel, COLOR_CHANNEL_GREEN);
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

void widget_city_draw_without_overlay(painter &ctx, int selected_figure_id, vec2i* figure_coord, tile2i tile) {
    int highlighted_formation = 0;
    if (config_get(CONFIG_UI_HIGHLIGHT_LEGIONS)) {
        highlighted_formation = formation_legion_at_grid_offset(tile.grid_offset());
        if (highlighted_formation > 0 && formation_get(highlighted_formation)->in_distant_battle) {
            highlighted_formation = 0;
        }
    }

    init_draw_context(selected_figure_id, figure_coord, highlighted_formation);

    city_building_ghost_mark_deleting(tile);

    reset_tiledraw_caches(*ctx.figure_cache);

    city_view_foreach_valid_map_tile(ctx, cache_figures);
    city_view_foreach_valid_map_tile(ctx, draw_isometric_flat);
    city_view_foreach_valid_map_tile(ctx, draw_isometric_height, draw_ornaments_and_animations, draw_figures);

    if (!selected_figure_id) {
        Planner.update(tile);
        Planner.draw(ctx);
    }

    // finally, draw these on top of everything else
    city_view_foreach_valid_map_tile(ctx, draw_debug_tile, draw_debug_figurecaches);
    city_view_foreach_valid_map_tile(ctx, draw_debug_figures);
}

void widget_city_draw_with_overlay(painter &ctx, tile2i tile) {
    if (!select_city_overlay())
        return;

    city_building_ghost_mark_deleting(tile);
    reset_tiledraw_caches(*ctx.figure_cache);
    city_view_foreach_valid_map_tile(ctx, cache_figures);
    city_view_foreach_valid_map_tile(ctx, draw_isometrics_overlay, draw_ornaments_overlay, draw_figures_overlay);
    Planner.update(tile);
    Planner.draw(ctx);
}

void widget_city_draw(painter &ctx) {
    auto& data = g_wdiget_city_data;
    update_zoom_level(ctx);
    set_render_scale(ctx, zoom_get_scale());
    set_city_clip_rectangle(ctx);
    if (game_state_overlay()) {
        widget_city_draw_with_overlay(ctx, data.current_tile);
    } else {
        widget_city_draw_without_overlay(ctx, 0, nullptr, data.current_tile);
    }
    graphics_reset_clip_rectangle();
    set_render_scale(ctx, 1.0f);
}

void widget_city_draw_for_figure(painter &ctx, int figure_id, vec2i* coord) {
    auto& data = g_wdiget_city_data;
    set_city_clip_rectangle(ctx);

    widget_city_draw_without_overlay(ctx, figure_id, coord, data.current_tile);

    graphics_reset_clip_rectangle();
}

bool widget_city_draw_construction_cost_and_size() {
    if (!Planner.in_progress)
        return false;

    if (scroll_in_progress())
        return false;

    int size_x, size_y;
    int cost = Planner.total_cost;
    int has_size = Planner.get_total_drag_size(&size_x, &size_y);
    if (!cost && !has_size) {
        return false;
    }

    painter ctx = game.painter();
    set_city_clip_rectangle(ctx);
    screen_tile screen = camera_get_selected_screen_tile();
    int x = screen.x;
    int y = screen.y;
    int inverted_scale = calc_percentage(100, zoom_get_percentage());
    x = calc_adjust_with_percentage(x, inverted_scale);
    y = calc_adjust_with_percentage(y, inverted_scale);

    if (cost) {
        color color;
        if (cost <= city_finance_treasury()) // Color blind friendly
            color = scenario_property_climate() == CLIMATE_DESERT ? COLOR_FONT_ORANGE : COLOR_FONT_ORANGE_LIGHT;
        else
            color = COLOR_FONT_RED;
        text_draw_number_colored(cost, '@', " ", x + 58 + 1, y + 1, FONT_SMALL_PLAIN, COLOR_BLACK);
        text_draw_number_colored(cost, '@', " ", x + 58, y, FONT_SMALL_PLAIN, color);
    }
    if (has_size) {
        int width = -text_get_width(string_from_ascii("  "), FONT_SMALL_PLAIN);
        width += text_draw_number_colored(size_x, '@', "x", x - 15 + 1, y + 25 + 1, FONT_SMALL_PLAIN, COLOR_BLACK);
        text_draw_number_colored(size_x, '@', "x", x - 15, y + 25, FONT_SMALL_PLAIN, COLOR_FONT_YELLOW);
        text_draw_number_colored(size_y, '@', " ", x - 15 + width + 1, y + 25 + 1, FONT_SMALL_PLAIN, COLOR_BLACK);
        text_draw_number_colored(size_y, '@', " ", x - 15 + width, y + 25, FONT_SMALL_PLAIN, COLOR_FONT_YELLOW);
    }
    graphics_reset_clip_rectangle();
    return true;
}

// INPUT HANDLING

static void build_start(map_point tile) {
    if (tile.grid_offset() > 0) // Allow building on paused
        Planner.construction_start(tile);
}
static void build_move(map_point tile) {
    if (!Planner.in_progress)
        return;
    Planner.construction_update(tile);
}
static void build_end(void) {
    if (Planner.in_progress) {
        if (Planner.build_type != BUILDING_NONE)
            sound_effect_play(SOUND_EFFECT_BUILD);

        Planner.construction_finalize();
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
    if (!window_is(WINDOW_CITY))
        allow = false;

    window_city_show();

    if (!tile.grid_offset())
        allow = false;

    if (allow && city_has_warnings()) {
        city_warning_clear_all();
        allow = false;
    }
    return allow;
}
static bool handle_legion_click(map_point tile) {
    if (tile.grid_offset() > 0) {
        int formation_id = formation_legion_at_grid_offset(tile.grid_offset());
        if (formation_id > 0 && !formation_get(formation_id)->in_distant_battle) {
            window_city_military_show(formation_id);
            return true;
        }
    }
    return false;
}
static bool handle_cancel_construction_button(const touch* t) {
    if (!Planner.build_type)
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
    Planner.construction_cancel();
    return true;
}
void widget_city_clear_current_tile(void) {
    auto& data = g_wdiget_city_data;
    data.selected_tile.set(0);
    data.current_tile.set(0);
    //    data.selected_tile.x = -1;
    //    data.selected_tile.y = -1;
    //    data.selected_tile.grid_offset() = 0;
    //    data.current_tile.grid_offset() = 0;
}

static void handle_touch_scroll(const touch* t) {
    auto& data = g_wdiget_city_data;
    if (Planner.build_type) {
        if (t->has_started) {
            vec2i view_pos, view_size;
            view_data_t viewport = city_view_viewport();
            city_view_get_viewport(viewport, view_pos, view_size);
            scroll_set_custom_margins(view_pos.x, view_pos.y, view_size.x, view_size.y);
        }
        if (t->has_ended)
            scroll_restore_margins();

        return;
    }
    scroll_restore_margins();

    if (!data.capture_input)
        return;
    int was_click = touch_was_click(get_latest_touch());
    if (t->has_started || was_click) {
        scroll_drag_start(1);
        return;
    }
    if (!touch_not_click(t))
        return;
    if (t->has_ended)
        scroll_drag_end();
}
static void handle_touch_zoom(const touch* first, const touch* last) {
    if (touch_not_click(first))
        zoom_update_touch(first, last, zoom_get_percentage());

    if (first->has_ended || last->has_ended)
        zoom_end_touch();
}

static void handle_first_touch(map_point tile) {
    auto& data = g_wdiget_city_data;
    const touch* first = get_earliest_touch();
    e_building_type type = Planner.build_type;

    if (touch_was_click(first)) {
        if (handle_cancel_construction_button(first) || handle_legion_click(tile))
            return;
        if (type == BUILDING_NONE && handle_right_click_allow_building_info(tile)) {
            scroll_drag_end();
            data.capture_input = false;
            window_building_info_show(tile);
            return;
        }
    }

    handle_touch_scroll(first);

    if (!input_coords_in_city(first->current_point.x, first->current_point.y) || type == BUILDING_NONE)
        return;

    if (Planner.has_flag_set(PlannerFlags::Draggable)) {
        if (!Planner.in_progress) {
            if (first->has_started) {
                build_start(tile);
                data.new_start_grid_offset = 0;
            }
        } else {
            if (first->has_started) {
                if (data.selected_tile.grid_offset() != tile.grid_offset())
                    data.new_start_grid_offset = tile.grid_offset();
            }
            if (touch_not_click(first) && data.new_start_grid_offset) {
                data.new_start_grid_offset = 0;
                data.selected_tile.set(0);
                Planner.construction_cancel();
                build_start(tile);
            }
            build_move(tile);
            if (data.selected_tile.grid_offset() != tile.grid_offset())
                data.selected_tile.set(0);

            if (first->has_ended) {
                if (data.selected_tile.grid_offset() == tile.grid_offset()) {
                    build_end();
                    widget_city_clear_current_tile();
                    data.new_start_grid_offset = 0;
                } else {
                    data.selected_tile = tile;
                }
            }
        }
        return;
    }

    int size = building_properties_for_type(type)->size;
    if (type == BUILDING_STORAGE_YARD)
        size = 3;

    if (touch_was_click(first) && first->has_ended && data.capture_input
        && has_confirmed_construction(data.selected_tile, tile, size)) {
        build_start(data.selected_tile);
        build_move(data.selected_tile);
        build_end();
        widget_city_clear_current_tile();
    } else if (first->has_ended)
        data.selected_tile = tile;
}
static void handle_last_touch(void) {
    const touch* last = get_latest_touch();
    if (!last->in_use)
        return;
    if (touch_was_click(last)) {
        Planner.construction_cancel();
        return;
    }
    if (touch_not_click(last))
        handle_touch_zoom(get_earliest_touch(), last);
}
static void handle_touch(void) {
    auto& data = g_wdiget_city_data;
    const touch* first = get_earliest_touch();
    if (!first->in_use) {
        scroll_restore_margins();
        return;
    }

    if (!Planner.in_progress || input_coords_in_city(first->current_point.x, first->current_point.y))
        data.current_tile = update_city_view_coords(first->current_point);

    if (first->has_started && input_coords_in_city(first->current_point.x, first->current_point.y)) {
        data.capture_input = true;
        scroll_restore_margins();
    }

    handle_last_touch();
    handle_first_touch(data.current_tile);

    if (first->has_ended)
        data.capture_input = false;

    Planner.draw_as_constructing = false;
}
int widget_city_has_input(void) {
    auto& data = g_wdiget_city_data;
    return data.capture_input;
}
static void handle_mouse(const mouse* m) {
    auto& data = g_wdiget_city_data;
    data.current_tile = update_city_view_coords({m->x, m->y});
    zoom_map(m);
    Planner.draw_as_constructing = false;
    if (m->left.went_down) {
        if (handle_legion_click(data.current_tile))
            return;
        if (!Planner.in_progress)
            build_start(data.current_tile);

        build_move(data.current_tile);
    } else if (m->left.is_down || Planner.in_progress)
        build_move(data.current_tile);

    if (m->left.went_up)
        build_end();

    if (m->middle.went_down && input_coords_in_city(m->x, m->y) && !Planner.build_type)
        scroll_drag_start(0);

    if (m->right.went_up) {
        if (!Planner.build_type) {
            if (handle_right_click_allow_building_info(data.current_tile)) {
                window_building_info_show(data.current_tile);
            }
        } else {
            Planner.construction_cancel();
        }
    }

    if (m->middle.went_up)
        scroll_drag_end();
}
static void military_map_click(int legion_formation_id, map_point tile) {
    if (!tile.grid_offset()) {
        window_city_show();
        return;
    }
    formation* m = formation_get(legion_formation_id);
    if (m->in_distant_battle || m->cursed_by_mars)
        return;
    int other_formation_id = formation_legion_at_building(tile.grid_offset());
    if (other_formation_id && other_formation_id == legion_formation_id)
        formation_legion_return_home(m);
    else {
        formation_legion_move_to(m, tile.x(), tile.y());
        sound_speech_play_file("wavs/cohort5.wav");
    }
    window_city_show();
}
void widget_city_handle_input(const mouse* m, const hotkeys* h) {
    scroll_map(m);

    if (m->is_touch)
        handle_touch();
    else
        handle_mouse(m);

    if (h->escape_pressed) {
        if (Planner.build_type) {
            Planner.construction_cancel();
        } else {
            hotkey_handle_escape();
        }
    }
}
void widget_city_handle_input_military(const mouse* m, const hotkeys* h, int legion_formation_id) {
    auto& data = g_wdiget_city_data;
    data.current_tile = update_city_view_coords({m->x, m->y});
    if (!city_view_is_sidebar_collapsed() && widget_minimap_handle_mouse(m))
        return;
    if (m->is_touch) {
        const touch* t = get_earliest_touch();
        if (!t->in_use)
            return;
        if (t->has_started)
            data.capture_input = true;

        handle_touch_scroll(t);
        if (t->has_ended)
            data.capture_input = false;
    }
    scroll_map(m);
    if (m->right.went_up || h->escape_pressed) {
        data.capture_input = false;
        city_warning_clear_all();
        window_city_show();
    } else {
        data.current_tile = update_city_view_coords({m->x, m->y});
        if ((!m->is_touch && m->left.went_down)
            || (m->is_touch && m->left.went_up && touch_was_click(get_earliest_touch())))
            military_map_click(legion_formation_id, data.current_tile);
    }
}

void widget_city_get_tooltip(tooltip_context* c) {
    auto& data = g_wdiget_city_data;
    if (setting_tooltips() == TOOLTIPS_NONE) {
        return;
    }

    if (!window_is(WINDOW_CITY)) {
        return;
    }

    int grid_offset = data.current_tile.grid_offset();
    if (grid_offset == 0) {
        return;
    }

    int building_id = map_building_at(grid_offset);
    int overlay = game_state_overlay();
    // cheat tooltips
    if (overlay == OVERLAY_NONE && game_cheat_tooltip_enabled()) {
        c->type = TOOLTIP_TILES;
        c->high_priority = 1;
        return;
    }

    // regular tooltips
    if (overlay == OVERLAY_NONE && building_id && building_get(building_id)->is_palace()) {
        c->type = TOOLTIP_SENATE;
        c->high_priority = 1;
        return;
    }

    // overlay tooltips
    if (overlay != OVERLAY_NONE) {
        c->text_group = e_text_tooltip;
        c->text_id = widget_city_overlay_get_tooltip_text(c, grid_offset);
        if (c->text_id) {
            c->type = TOOLTIP_OVERLAY;
            c->high_priority = 1;
        }
    }
}

#include "map_editor.h"
#include <graphics/view/lookup.h>

#include "editor/tool.h"
#include "widget/widget_city.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/menu.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/image.h"
#include "grid/point.h"
#include "grid/property.h"
#include "input/scroll.h"
#include "game/game_config.h"
#include "sound/sound_city.h"
#include "sound/sound.h"
#include "widget/city/tile_draw.h"
#include "city/city_figures.h"
#include "widget/map_editor_tool.h"
#include "game/game.h"

struct map_editor_data_t {
    tile2i current_tile;
    int selected_grid_offset;
    int new_start_grid_offset;
    int capture_input;
};

map_editor_data_t g_map_editor_data;
local_render_context_t draw_context;

static void draw_flags(vec2i pixel, tile2i point) {
    painter ctx = game.painter();
    int figure_id = map_figure_id_get(point);
    while (figure_id) {
        figure* f = figure_get(figure_id);
        f->draw(ctx, 0);

        if (figure_id != f->next_figure) {
            figure_id = f->next_figure;
        } else {
            figure_id = 0;
        }
    }
}

// static void set_city_clip_rectangle(void) {
//     int x, y, width, height;
//     city_view_get_viewport(&x, &y, &width, &height);
//     graphics_set_clip_rectangle(x, y, width, height);
// }

static void update_zoom_level() {
    vec2i offset = camera_get_position();
    if (g_zoom.update_value(&offset)) {
        city_view_refresh_viewport();
        painter ctx = game.painter();
        camera_go_to_pixel(ctx, offset, true);
        sound_city_decay_views();
    }
}

void widget_map_editor_draw() {
    painter ctx = game.painter();
    auto &data = g_map_editor_data;
    update_zoom_level();
    set_city_clip_rectangle(ctx);

    draw_context.init();
    //    city_view_foreach_map_tile(draw_buildings);
    city_view_foreach_valid_map_tile(ctx, 
        [] (vec2i pixel, tile2i tile, painter &ctx) { g_screen_city.draw_isometric_flat(pixel, tile, ctx); }
    );

    city_view_foreach_valid_map_tile(ctx, 
        [] (vec2i pixel, tile2i tile, painter &ctx) { g_screen_city.draw_isometric_terrain_height(pixel, tile, ctx); }
    );
    //    city_view_foreach_valid_map_tile(draw_flags, draw_top, 0);
    map_editor_tool_draw(ctx, data.current_tile);
}

static void update_city_view_coords(int x, int y, tile2i* tile) {
    screen_tile screen = pixel_to_screentile({x, y});
    if (screen.x != -1 && screen.y != -1) {
        *tile = screen_to_tile(screen);
        city_view_set_selected_view_tile(&screen);
    } else {
        *tile = tile2i::invalid;
    }
}

static void scroll_map(const mouse* m) {
    vec2i delta;
    if (scroll_get_delta(m, &delta, SCROLL_TYPE_CITY)) {
        camera_scroll(delta.x, delta.y);
        sound_city_decay_views();
    }
}

static int input_coords_in_map(int x, int y) {
    vec2i view_pos, view_size;
    city_view_get_viewport(g_city_view, view_pos, view_size);

    x -= view_pos.x;
    y -= view_pos.y;

    return (x >= 0 && x < view_size.x && y >= 0 && y < view_size.y);
}

static void handle_touch_scroll(const touch_t * t) {
    auto &data = g_map_editor_data;
    if (editor_tool_is_active()) {
        if (t->has_started) {
            vec2i view_pos, view_size;
            city_view_get_viewport(g_city_view, view_pos, view_size);
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

static void handle_touch_zoom(const touch_t * first, const touch_t * last) {
    if (touch_not_click(first))
        g_zoom.handle_touch(first, last, g_zoom.get_percentage());

    if (first->has_ended || last->has_ended)
        g_zoom.end_touch();
}

static void handle_last_touch(void) {
    const touch_t * last = get_latest_touch();
    if (!last->in_use)
        return;
    if (touch_was_click(last)) {
        editor_tool_deactivate();
        return;
    }
    if (touch_not_click(last))
        handle_touch_zoom(get_earliest_touch(), last);
}

static bool handle_cancel_construction_button(const touch_t * t) {
    if (!editor_tool_is_active())
        return false;

    vec2i view_pos, view_size;
    city_view_get_viewport(g_city_view, view_pos, view_size);

    int box_size = 5 * 16;
    view_size.x -= box_size;

    if (t->current_point.x < view_size.x || t->current_point.x >= view_size.x + box_size || t->current_point.y < 24
        || t->current_point.y >= 40 + box_size) {
        return false;
    }
    editor_tool_deactivate();
    return true;
}

static void handle_first_touch(tile2i tile) {
    auto &data = g_map_editor_data;
    const touch_t * first = get_earliest_touch();

    if (touch_was_click(first)) {
        if (handle_cancel_construction_button(first))
            return;
    }

    handle_touch_scroll(first);

    if (!input_coords_in_map(first->current_point.x, first->current_point.y))
        return;

    if (editor_tool_is_updatable()) {
        if (!editor_tool_is_in_use()) {
            if (first->has_started) {
                editor_tool_start_use(tile);
                data.new_start_grid_offset = 0;
            }
        } else {
            if (first->has_started) {
                if (data.selected_grid_offset != tile.grid_offset())
                    data.new_start_grid_offset = tile.grid_offset();
            }
            if (touch_not_click(first) && data.new_start_grid_offset) {
                data.new_start_grid_offset = 0;
                data.selected_grid_offset = 0;
                editor_tool_deactivate();
                editor_tool_start_use(tile);
            }
            editor_tool_update_use(tile);
            if (data.selected_grid_offset != tile.grid_offset())
                data.selected_grid_offset = 0;

            if (first->has_ended) {
                if (data.selected_grid_offset == tile.grid_offset()) {
                    editor_tool_end_use(tile);
                    widget_map_editor_clear_current_tile();
                    data.new_start_grid_offset = 0;
                } else {
                    data.selected_grid_offset = tile.grid_offset();
                }
            }
        }
        return;
    }

    if (editor_tool_is_brush()) {
        if (first->has_started)
            editor_tool_start_use(tile);

        editor_tool_update_use(tile);
        if (first->has_ended)
            editor_tool_end_use(tile);

        return;
    }

    if (touch_was_click(first) && first->has_ended && data.capture_input
        && data.selected_grid_offset == tile.grid_offset()) {
        editor_tool_start_use(tile);
        editor_tool_update_use(tile);
        editor_tool_end_use(tile);
        widget_map_editor_clear_current_tile();
    } else if (first->has_ended)
        data.selected_grid_offset = tile.grid_offset();
}

static void handle_touch(void) {
    auto &data = g_map_editor_data;
    const touch_t * first = get_earliest_touch();
    if (!first->in_use) {
        scroll_restore_margins();
        return;
    }

    if (!editor_tool_is_in_use() || input_coords_in_map(first->current_point.x, first->current_point.y))
        update_city_view_coords(first->current_point.x, first->current_point.y, &data.current_tile);

    if (first->has_started && input_coords_in_map(first->current_point.x, first->current_point.y)) {
        data.capture_input = true;
        scroll_restore_margins();
    }

    handle_last_touch();
    handle_first_touch(data.current_tile);

    if (first->has_ended)
        data.capture_input = false;
}

void widget_map_editor_handle_input(const mouse* m, const hotkeys* h) {
    auto &data = g_map_editor_data;
    scroll_map(m);

    if (m->is_touch) {
        g_zoom.handle_mouse(m);
        handle_touch();
    } else {
        if (m->right.went_down && input_coords_in_map(m->x, m->y) && !editor_tool_is_active())
            scroll_drag_start(0);

        if (m->right.went_up) {
            if (!editor_tool_is_active()) {
                int has_scrolled = scroll_drag_end();
                if (!has_scrolled)
                    editor_tool_deactivate();

            } else {
                editor_tool_deactivate();
            }
        }
    }

    if (h->escape_pressed) {
        if (editor_tool_is_active())
            editor_tool_deactivate();
        else {
            hotkey_handle_escape();
        }
        return;
    }

    update_city_view_coords(m->x, m->y, &data.current_tile);

    if (!data.current_tile.grid_offset())
        return;

    if (m->left.went_down) {
        if (!editor_tool_is_in_use())
            editor_tool_start_use(data.current_tile);

        editor_tool_update_use(data.current_tile);
    } else if (m->left.is_down || editor_tool_is_in_use())
        editor_tool_update_use(data.current_tile);

    if (m->left.went_up) {
        editor_tool_end_use(data.current_tile);
        g_sound.play_effect(SOUND_EFFECT_BUILD);
    }
}

void widget_map_editor_clear_current_tile(void) {
    auto &data = g_map_editor_data;
    data.selected_grid_offset = 0;
    data.current_tile.set(0);
}

#include "map_editor.h"
#include <graphics/view/lookup.h>

#include "editor/tool.h"
#include "graphics/boilerplate.h"
#include "graphics/elements/menu.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/image.h"
#include "grid/point.h"
#include "grid/property.h"
#include "input/scroll.h"
#include "io/config/config.h"
#include "sound/city.h"
#include "sound/effect.h"
#include "widget/city/tile_draw.h"
#include "widget/map_editor_tool.h"

static struct {
    map_point current_tile;
    int selected_grid_offset;
    int new_start_grid_offset;
    int capture_input;
} data;

static struct {
    time_millis last_water_animation_time;
    int advance_water_animation;

    int image_id_water_first;
    int image_id_water_last;

    int image_id_deepwater_first;
    int image_id_deepwater_last;
} draw_context;

static void init_draw_context(void) {
    draw_context.advance_water_animation = 0;
    time_millis now = time_get_millis();
    if (now - draw_context.last_water_animation_time > 60) {
        draw_context.last_water_animation_time = now;
        draw_context.advance_water_animation = 1;
    }
    draw_context.image_id_water_first = image_id_from_group(GROUP_TERRAIN_WATER);
    draw_context.image_id_water_last = 5 + draw_context.image_id_water_first;
    draw_context.image_id_deepwater_first = image_id_from_group(GROUP_TERRAIN_DEEPWATER);
    draw_context.image_id_deepwater_last = 89 + draw_context.image_id_deepwater_first;
}

static void draw_flags(pixel_coordinate pixel, map_point point) {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;
    int figure_id = map_figure_at(grid_offset);
    while (figure_id) {
        figure* f = figure_get(figure_id);
        if (!f->is_ghost)
            f->city_draw_figure(pixel, 0);

        if (figure_id != f->next_figure)
            figure_id = f->next_figure;
        else
            figure_id = 0;
    }
}

// static void set_city_clip_rectangle(void) {
//     int x, y, width, height;
//     city_view_get_viewport(&x, &y, &width, &height);
//     graphics_set_clip_rectangle(x, y, width, height);
// }

static void update_zoom_level(void) {
    pixel_coordinate offset = camera_get_position();
    if (zoom_update_value(&offset)) {
        city_view_refresh_viewport();
        camera_go_to_pixel(offset, true);
        sound_city_decay_views();
    }
}

void widget_map_editor_draw(void) {
    update_zoom_level();
    set_city_clip_rectangle();

    init_draw_context();
    //    city_view_foreach_map_tile(draw_buildings);
    city_view_foreach_valid_map_tile(draw_isometrics);
    //    city_view_foreach_valid_map_tile(draw_flags, draw_top, 0);
    map_editor_tool_draw(data.current_tile);
}

static void update_city_view_coords(int x, int y, map_point* tile) {
    screen_tile screen = pixel_to_screentile({x, y});
    if (screen.x != -1 && screen.y != -1) {
        tile->set(screentile_to_mappoint(screen).grid_offset());
        city_view_set_selected_view_tile(&screen);
    } else
        tile->set(0);
}

static void scroll_map(const mouse* m) {
    pixel_coordinate delta;
    if (scroll_get_delta(m, &delta, SCROLL_TYPE_CITY)) {
        camera_scroll(delta.x, delta.y);
        sound_city_decay_views();
    }
}

static int input_coords_in_map(int x, int y) {
    int x_offset, y_offset, width, height;
    city_view_get_viewport(&x_offset, &y_offset, &width, &height);

    x -= x_offset;
    y -= y_offset;

    return (x >= 0 && x < width && y >= 0 && y < height);
}

static void handle_touch_scroll(const touch* t) {
    if (editor_tool_is_active()) {
        if (t->has_started) {
            int x_offset, y_offset, width, height;
            city_view_get_viewport(&x_offset, &y_offset, &width, &height);
            scroll_set_custom_margins(x_offset, y_offset, width, height);
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

static void handle_last_touch(void) {
    const touch* last = get_latest_touch();
    if (!last->in_use)
        return;
    if (touch_was_click(last)) {
        editor_tool_deactivate();
        return;
    }
    if (touch_not_click(last))
        handle_touch_zoom(get_earliest_touch(), last);
}

static bool handle_cancel_construction_button(const touch* t) {
    if (!editor_tool_is_active())
        return false;

    int x, y, width, height;
    city_view_get_viewport(&x, &y, &width, &height);
    int box_size = 5 * 16;
    width -= box_size;

    if (t->current_point.x < width || t->current_point.x >= width + box_size || t->current_point.y < 24
        || t->current_point.y >= 40 + box_size) {
        return false;
    }
    editor_tool_deactivate();
    return true;
}

static void handle_first_touch(map_point tile) {
    const touch* first = get_earliest_touch();

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
    const touch* first = get_earliest_touch();
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
    scroll_map(m);

    if (m->is_touch) {
        zoom_map(m);
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
        sound_effect_play(SOUND_EFFECT_BUILD);
    }
}

void widget_map_editor_clear_current_tile(void) {
    data.selected_grid_offset = 0;
    data.current_tile.set(0);
}

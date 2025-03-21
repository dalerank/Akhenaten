#include "window_city_military.h"

#include "window_city.h"
#include "city/city_warnings.h"
#include "widget/widget_city.h"
#include "widget/widget_minimap.h"
#include "widget/widget_top_menu_game.h"
#include "widget/sidebar/common.h"
#include "widget/widget_sidebar.h"
#include "graphics/window.h"
#include "grid/point.h"
#include "figure/formation.h"
#include "figure/formation_legion.h"
#include "sound/sound.h"

static int selected_legion_formation_id;

void military_map_click(int legion_formation_id, tile2i tile) {
    if (!tile.grid_offset()) {
        window_city_show();
        return;
    }
    formation* m = formation_get(legion_formation_id);
    if (m->in_distant_battle || m->cursed_by_seth)
        return;
    int other_formation_id = formation_legion_at_building(tile.grid_offset());
    if (other_formation_id && other_formation_id == legion_formation_id) {
        formation_legion_return_home(m);
    } else {
        formation_legion_move_to(m, tile);
        g_sound.speech_play_file("Wavs/cohort5.wav", 255);
    }
    window_city_show();
}

void widget_city_handle_input_military(const mouse* m, const hotkeys* h, int legion_formation_id) {
    tile2i current_tile = widget_city_update_city_view_coords({m->x, m->y});
    widget_city_set_current_tile(current_tile);

    if (!city_view_is_sidebar_collapsed() && widget_minimap_handle_mouse(m)) {
        return;
    }

    if (m->is_touch) {
        const touch_t* t = get_earliest_touch();
        if (!t->in_use) {
            return;
        }

        g_screen_city.handle_touch_scroll(t, true);
    }

    widget_city_scroll_map(m);

    if (m->right.went_up || h->escape_pressed) {
        g_screen_city.capture_input = false;
        g_warning_manager.clear_all();
        window_city_show();
        return;
    } 

    current_tile = widget_city_update_city_view_coords({m->x, m->y});
    widget_city_set_current_tile(current_tile);
    const bool m_left_down = (!m->is_touch && m->left.went_down);
    const auto *early_touch = get_earliest_touch();
    const bool m_has_touch = (m->is_touch && m->left.went_up && touch_was_click(early_touch));

    if (m_left_down || m_has_touch) {
        const tile2i tile = widget_city_get_current_tile();
        military_map_click(legion_formation_id, tile);
    }
}

void handle_input_military(const mouse* m, const hotkeys* h) {
    window_city_handle_hotkeys(h);
    widget_city_handle_input_military(m, h, selected_legion_formation_id);
}

void draw_foreground_military(int) {
    widget_top_menu_draw();
    window_city_draw();
    widget_sidebar_city_draw_foreground_military();
    window_city_draw_paused_and_time_left();
}

void window_city_military_show(int legion_formation_id) {
    selected_legion_formation_id = legion_formation_id;
    static window_type window = {
        WINDOW_CITY_MILITARY,
        window_city_draw_background,
        draw_foreground_military,
        handle_input_military,
        window_city_get_tooltip
    };

    window_show(&window);
}
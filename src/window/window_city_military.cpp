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
        [] (auto m, auto h) {
          window_city_handle_hotkeys(h);
          g_screen_city.handle_input_military(m, h, selected_legion_formation_id);
        },
        [] (auto c) { g_screen_city.draw_tooltip(c); }
    };

    window_show(&window);
}
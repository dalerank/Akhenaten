#include "window_city_warship.h"

#include "window_city.h"
#include "city/city_warnings.h"
#include "widget/widget_city.h"
#include "widget/widget_minimap.h"
#include "widget/widget_top_menu_game.h"
#include "widget/sidebar/common.h"
#include "widget/widget_sidebar.h"
#include "graphics/window.h"
#include "grid/point.h"

static int selected_warship_figure_id;

static void draw_foreground_warship(int) {
    widget_top_menu_draw();
    window_city_draw();
    widget_sidebar_city_draw_foreground();
    window_city_draw_paused_and_time_left();
}

void window_city_warship_show(int warship_figure_id) {
    selected_warship_figure_id = warship_figure_id;

    static window_type window = {
        "window_city_warship",
        window_city_draw_background,
        draw_foreground_warship,
        [] (auto m, auto h) {
          window_city_handle_hotkeys(h);
          g_screen_city.handle_input_warship(m, h, selected_warship_figure_id);
        },
        [] (auto c) { g_screen_city.draw_tooltip(c); }
    };

    window_show(&window);
}

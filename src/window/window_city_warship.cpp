#include "window_city_warship.h"

#include "window_city.h"
#include "city/city_warnings.h"
#include "widget/widget_city.h"
#include "widget/widget_minimap.h"
#include "widget/sidebar/common.h"
#include "widget/widget_sidebar.h"
#include "widget/widget_figure_follow.h"
#include "graphics/window.h"
#include "js/js_game.h"
#include "grid/point.h"

static int selected_warship_figure_id;

static void draw_foreground_warship(int) {
    js_call_event_handlers("top_menu_draw", {});
    window_city_draw();
    widget_sidebar_city_draw_foreground();
    g_window_city.draw_paused_panel();
    window_city_draw_time_left_panel();
    g_figure_follow.draw_panel();
}

void window_city_warship_show(int warship_figure_id) {
    selected_warship_figure_id = warship_figure_id;

    static window_type window = {
        "window_city_warship",
        [](int flags) { g_window_city.draw_background(flags); },
        draw_foreground_warship,
        [] (auto m, auto h) {
          window_city_handle_hotkeys(h);
          if (g_figure_follow.handle_escape(h) || g_figure_follow.handle_mouse(m)) {
              return;
          }
          g_screen_city.handle_input_warship(m, h, selected_warship_figure_id);
        },
        [] (auto c) { g_screen_city.draw_tooltip(c); }
    };

    window_show(&window);
}

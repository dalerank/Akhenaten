#include "window_city_transport.h"

#include "window_city.h"
#include "widget/widget_city.h"
#include "widget/widget_minimap.h"
#include "widget/sidebar/common.h"
#include "widget/widget_sidebar.h"
#include "graphics/window.h"
#include "js/js_game.h"
#include "grid/point.h"

static int selected_transport_figure_id;
static e_transport_pick_mode selected_transport_pick_mode;

const e_transport_pick_mode_tokens_t ANK_CONFIG_ENUM(e_transport_pick_mode_tokens);

static void draw_foreground_transport(int) {
    js_call_event_handlers("top_menu_draw", {});
    window_city_draw();
    widget_sidebar_city_draw_foreground();
    g_window_city.draw_paused_panel();
    window_city_draw_time_left_panel();
}

void window_city_transport_show(int transport_figure_id, e_transport_pick_mode mode) {
    selected_transport_figure_id = transport_figure_id;
    selected_transport_pick_mode = mode;

    static window_type window = {
        "window_city_transport",
        [](int flags) { g_window_city.draw_background(flags); },
        draw_foreground_transport,
        [] (auto m, auto h) {
          window_city_handle_hotkeys(h);
          g_screen_city.handle_input_transport(m, h, selected_transport_figure_id, selected_transport_pick_mode);
        },
        [] (auto c) { g_screen_city.draw_tooltip(c); }
    };

    window_show(&window);
}

e_transport_pick_mode window_city_transport_pick_mode() {
    return selected_transport_pick_mode;
}

int window_city_transport_figure_id() {
    return selected_transport_figure_id;
}

void __window_city_transport_show(int transport_figure_id, int mode) {
    window_city_transport_show(transport_figure_id, (e_transport_pick_mode)mode);
}
ANK_FUNCTION_2(__window_city_transport_show)

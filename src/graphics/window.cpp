#include "window.h"

#include "core/profiler.h"
#include "graphics/graphics.h"
#include "input/cursor.h"
#include "input/scroll.h"
#include "graphics/elements/ui.h"
#include "graphics/render_device.h"
#include "core/tokenum.h"
#include "graphics/elements/ui_js.h"
#include "game/game_events.h"
#include "game/simulation.h"

windows_manager_t g_window_manager;

xstring windows_manager_t::window_city = "window_city";
xstring windows_manager_t::window_main_menu = "window_main_menu";

struct event_window_back { vec2i pos; };
ANK_REGISTER_STRUCT_WRITER(event_window_back, pos)

static void noop(int) {
}

static void noop_input(const mouse* m, const hotkeys* h) {
}

static void reset_input() {
    mouse::ref().reset_button_state();
    g_touch.reset(true);
    g_scroll.stop();
}

static void set_current_window(window_type* window) {
    g_window_manager.current_window = window;
    g_simulation.time_runs = window->sim_time_runs;
}

static void increase_queue_index() {
    auto& data = g_window_manager;
    data.queue_index++;
    if (data.queue_index >= data.window_queue.size())
        data.queue_index = 0;
}

static void decrease_queue_index(void) {
    auto& data = g_window_manager;
    data.queue_index--;
    if (data.queue_index < 0) {
        data.queue_index = data.window_queue.size() - 1;
    }

    auto w = data.window_queue[data.queue_index];
    ui::event(event_window_back{ vec2i{0, 0} }, w.id.c_str(), "on_restore");
}

bool windows_manager_t::window_is(xstring id) {
    return current_window && current_window->id == id;
}

xstring window_get_id() {
    auto& data = g_window_manager;
    return data.current_window->id;
}

xstring window_get_id_at_depth(int depth) {
    auto& data = g_window_manager;
    const int n = (int)data.window_queue.size();
    if (depth < 0 || depth >= n) {
        return {};
    }
    return data.window_queue[((data.queue_index - depth) % n + n) % n].id;
}

void window_show(const window_type* window) {
    auto& data = g_window_manager;
    // push window into queue of screens to render
    reset_input();
    ui::stop_active_input();
    ui::clear_active_elements();
    increase_queue_index();
    data.window_queue[data.queue_index] = *window;
    set_current_window(&data.window_queue[data.queue_index]);
    if (!data.current_window->draw_background)
        data.current_window->draw_background = noop;

    if (!data.current_window->draw_foreground)
        data.current_window->draw_foreground = noop;

    if (!data.current_window->handle_input) {
        data.current_window->handle_input = noop_input;
    }
}

void window_go_back() {
    auto& data = g_window_manager;
    // cant exit from city with rmb
    if (data.current_window->id == windows_manager_t::window_city
        || data.current_window->id == windows_manager_t::window_main_menu) {
        return;
    }

    reset_input();
    ui::stop_active_input();
    decrease_queue_index();

    set_current_window(&data.window_queue[data.queue_index]);
}

void windows_manager_t::update_input_after() {
    auto& data = g_window_manager;
    g_touch.reset(false);
    mouse::ref().reset_scroll();
    if (data.current_window) {
        input_cursor_update(data.current_window->id);
    }
    g_hotkeys.reset();
}

void windows_manager_t::handle_input(const mouse *m, const hotkeys *h) {
    if (current_window) {
        current_window->handle_input(m, h);
    }
}

void windows_manager_t::handle_tooltip(const mouse *m) {
    if (current_window) {
        tooltip_handle(m, current_window->draw_tooltip);
    }
}

void window_draw(int force) {
    auto& data = g_window_manager;
    // draw the current (top) window in the queue
    ui::begin_frame();

    if (!g_touch.to_mouse()) {
        mouse::ref().determine_button_state(); // touch overrides mouse
    }

    window_type* w = data.current_window;
    if (!w) {
        return;
    }

    {
        OZZY_PROFILER_SECTION(_, "Render/Frame/Refresh");
        g_render.clear_screen();
    }

    {
        OZZY_PROFILER_SECTION(_, "Render/Frame/Window/Background");
        w->draw_background(UiFlags_None);
    }

    {
        OZZY_PROFILER_SECTION(_, "Render/Frame/Foreground");
        w->draw_foreground(UiFlags_None);
    }

    {
        OZZY_PROFILER_SECTION(_, "Render/Frame/Tooltip");
        data.handle_tooltip(&mouse::get());
    }

    ui::flush_commands();
}

void window_draw_underlying_window(int flags) {
    auto& data = g_window_manager;
    if (data.underlying_windows_redrawing < data.window_queue.size()) {
        ++data.underlying_windows_redrawing;
        decrease_queue_index();

        window_type* window_behind = &data.window_queue[data.queue_index];
        if (window_behind->draw_background)
            window_behind->draw_background(flags);

        if (window_behind->draw_foreground)
            window_behind->draw_foreground(flags);

        ui::flush_commands();
        increase_queue_index();
        ui::clear_active_elements();
        --data.underlying_windows_redrawing;
    }
}

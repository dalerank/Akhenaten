#include "window.h"

#include "core/profiler.h"
#include "graphics/graphics.h"
#include "input/cursor.h"
#include "input/scroll.h"
#include "graphics/elements/ui.h"
#include "platform/renderer.h"
#include "js/js_game.h"

windows_manager_t g_window_manager;

static void noop(int) {
}
static void noop_input(const mouse* m, const hotkeys* h) {
}

static void reset_input() {
    mouse::ref().reset_button_state();
    reset_touches(1);
    scroll_stop();
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
}

bool window_is(e_window_id id) {
    auto& data = g_window_manager;
    return data.current_window->id == id;
}

e_window_id window_get_id() {
    auto& data = g_window_manager;
    return data.current_window->id;
}

void window_show(const window_type* window) {
    auto& data = g_window_manager;
    // push window into queue of screens to render
    reset_input();
    ui::begin_frame();
    increase_queue_index();
    data.window_queue[data.queue_index] = *window;
    data.current_window = &data.window_queue[data.queue_index];
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
    reset_input();
    decrease_queue_index();
    data.current_window = &data.window_queue[data.queue_index];
}
ANK_FUNCTION(window_go_back);

void windows_manager_t::update_input_after() {
    auto& data = g_window_manager;
    reset_touches(0);
    mouse::ref().reset_scroll();
    input_cursor_update(data.current_window->id);
    hotkey_reset_state();
}

void windows_manager_t::handle_input(const mouse *m, const hotkeys *h) {
    current_window->handle_input(m, h);
}

void windows_manager_t::handle_tooltip(const mouse *m) {
    tooltip_handle(m, current_window->draw_tooltip);
}

void window_draw(int force) {
    auto& data = g_window_manager;
    // draw the current (top) window in the queue
    ui::begin_frame();

    if (!touch_to_mouse()) {
        mouse::ref().determine_button_state(); // touch overrides mouse
    }

    window_type* w = data.current_window;

    {
        OZZY_PROFILER_SECTION("Render/Frame/Refresh");
        g_render.clear_screen();
        tooltip_invalidate();
    }
        
    {
        OZZY_PROFILER_SECTION("Render/Frame/Window/Background");
        w->draw_background(UiFlags_None);
    }

    {
        OZZY_PROFILER_SECTION("Render/Frame/Foreground");
        w->draw_foreground(UiFlags_None);
    }
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

        increase_queue_index();
        ui::clear_active_elements();
        --data.underlying_windows_redrawing;
    }
}

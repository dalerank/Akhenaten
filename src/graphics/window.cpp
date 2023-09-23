#include "window.h"

#include "core/profiler.h"
#include "graphics/boilerplate.h"
#include "graphics/graphics.h"
#include "graphics/elements/warning.h"
#include "input/cursor.h"
#include "input/scroll.h"

#define MAX_QUEUE 6

struct window_data_t {
    window_type window_queue[MAX_QUEUE];
    int queue_index;
    window_type* current_window;
    bool refresh_immediate;
    bool refresh_on_draw;
    bool refresh_background;
    int underlying_windows_redrawing;
};

window_data_t g_window;

static void noop(void) {
}
static void noop_input(const mouse* m, const hotkeys* h) {
}
static void reset_input(void) {
    mouse_reset_button_state();
    reset_touches(1);
    scroll_stop();
}
static void increase_queue_index(void) {
    auto& data = g_window;
    data.queue_index++;
    if (data.queue_index >= MAX_QUEUE)
        data.queue_index = 0;
}
static void decrease_queue_index(void) {
    auto& data = g_window;
    data.queue_index--;
    if (data.queue_index < 0)
        data.queue_index = MAX_QUEUE - 1;
}

void window_invalidate() {
    auto& data = g_window;
    data.refresh_immediate = true;
    data.refresh_on_draw = true;
}

void window_request_refresh_background() {
    auto& data = g_window;
    data.refresh_background = true;
}

int window_is_invalid(void) {
    auto& data = g_window;
    return data.refresh_immediate;
}

void window_request_refresh(void) {
    auto& data = g_window;
    data.refresh_on_draw = true;
}

int window_is(e_window_id id) {
    auto& data = g_window;
    return data.current_window->id == id;
}

e_window_id window_get_id(void) {
    auto& data = g_window;
    return data.current_window->id;
}

void window_show(const window_type* window) {
    auto& data = g_window;
    // push window into queue of screens to render
    reset_input();
    increase_queue_index();
    data.window_queue[data.queue_index] = *window;
    data.current_window = &data.window_queue[data.queue_index];
    if (!data.current_window->draw_background)
        data.current_window->draw_background = noop;
    if (!data.current_window->draw_foreground)
        data.current_window->draw_foreground = noop;
    if (!data.current_window->handle_input)
        data.current_window->handle_input = noop_input;
    window_invalidate();
}
void window_go_back(void) {
    auto& data = g_window;
    reset_input();
    decrease_queue_index();
    data.current_window = &data.window_queue[data.queue_index];
    window_invalidate();
}
static void update_input_before(void) {
    if (!touch_to_mouse()) {
        mouse_determine_button_state(); // touch overrides mouse
    }

    hotkey_handle_global_keys();
}
void window_update_input_after() {
    auto& data = g_window;
    reset_touches(0);
    mouse_reset_scroll();
    input_cursor_update(data.current_window->id);
    hotkey_reset_state();
}
void window_draw(int force) {
    auto& data = g_window;
    // draw the current (top) window in the queue
    update_input_before();
    window_type* w = data.current_window;
    if (force || data.refresh_on_draw) {
        OZZY_PROFILER_SECTION("Render/Frame/Refresh");
        graphics_clear_screen();
        tooltip_invalidate();
        {
            OZZY_PROFILER_SECTION("Render/Frame/Window/Background");
            w->draw_background();
        }
        data.refresh_on_draw = false;
        data.refresh_immediate = false;
        data.refresh_background = false;
    }

    if (data.refresh_background) {
        if (w->draw_refresh) {
            w->draw_refresh();
        }

        data.refresh_background = false;
    }

    {
        OZZY_PROFILER_SECTION("Render/Frame/Foreground");
        w->draw_foreground();
    }
}

window_type *window_current() {
    return g_window.current_window;
}

void window_draw_underlying_window(void) {
    auto& data = g_window;
    if (data.underlying_windows_redrawing < MAX_QUEUE) {
        ++data.underlying_windows_redrawing;
        decrease_queue_index();
        window_type* window_behind = &data.window_queue[data.queue_index];
        if (window_behind->draw_background)
            window_behind->draw_background();

        if (window_behind->draw_foreground)
            window_behind->draw_foreground();

        increase_queue_index();
        --data.underlying_windows_redrawing;
    }
}

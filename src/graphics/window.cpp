#include "window.h"

#include "core/profiler.h"
#include "graphics/graphics.h"
#include "graphics/elements/warning.h"
#include "input/cursor.h"
#include "input/scroll.h"
#include "graphics/elements/ui.h"

#define MAX_QUEUE 6

struct window_data_t {
    window_type window_queue[MAX_QUEUE];
    int queue_index;
    window_type* current_window;
    int underlying_windows_redrawing;
};

window_data_t g_window;

static void noop(void) {
}
static void noop_input(const mouse* m, const hotkeys* h) {
}

static void reset_input() {
    mouse_reset_button_state();
    reset_touches(1);
    scroll_stop();
}

static void increase_queue_index() {
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

bool window_is(e_window_id id) {
    auto& data = g_window;
    return data.current_window->id == id;
}

e_window_id window_get_id() {
    auto& data = g_window;
    return data.current_window->id;
}

void window_show(const window_type* window) {
    auto& data = g_window;
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
    auto& data = g_window;
    reset_input();
    decrease_queue_index();
    data.current_window = &data.window_queue[data.queue_index];
}

static void update_input_before() {
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
    ui::begin_frame();
    update_input_before();
    window_type* w = data.current_window;

    {
        OZZY_PROFILER_SECTION("Render/Frame/Refresh");
        graphics_clear_screen();
        tooltip_invalidate();
    }
        
    {
        OZZY_PROFILER_SECTION("Render/Frame/Window/Background");
        w->draw_background();
    }

    {
        OZZY_PROFILER_SECTION("Render/Frame/Foreground");
        w->draw_foreground();
    }
}

window_type *window_current() {
    return g_window.current_window;
}

void window_draw_underlying_window() {
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

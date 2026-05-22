#include "victory_video.h"

#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/screen.h"
#include "graphics/video.h"
#include "platform/renderer.h"
#include "graphics/window.h"
#include "core/bstring.h"
#include "core/profiler.h"
#include "js/js.h"
#include "js/js_game.h"

#include <functional>

static struct {
    int width;
    int height;
    std::function<void()> callback;
} data;

static int init(const char* filename, int width, int height, std::function<void()> callback) {
    if (video_start(filename)) {
        data.width = width;
        data.height = height;
        data.callback = std::move(callback);
        video_init();
        return 1;
    }
    return 0;
}

static void draw_background(int) {
    g_render.clear_screen();
}

static void draw_foreground(int) {
    video_draw((screen_width() - data.width) / 2, (screen_height() - data.height) / 2);
}

static void handle_input(const mouse* m, const hotkeys* h) {
    if (m->left.went_up || m->right.went_up || video_is_finished()) {
        video_stop();
        if (data.callback) {
            data.callback();
        }
    }
}

void window_victory_video_show(const char* filename, int width, int height, std::function<void()> callback) {
    if (init(filename, width, height, callback)) {
        window_type window = {
            "window_victory_video",
            draw_background,
            draw_foreground,
            handle_input
        };
        window_show(&window);
    } else if (callback) {
        callback();
    }
}

void __game_victory_video_show(pcstr filename, int width, int height, pcstr on_done) {
    bstring256 file = filename ? filename : "";
    bstring64 cb = (on_done && *on_done) ? on_done : "";
    window_victory_video_show(file.c_str(), width, height, [cb]() {
        if (!cb.empty()) {
            js_vm_exec_function(cb.c_str());
        }
    });
}
ANK_FUNCTION_4(__game_victory_video_show)

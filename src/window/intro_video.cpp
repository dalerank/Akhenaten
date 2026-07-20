#include "intro_video.h"

#include "core/log.h"
#include "graphics/graphics.h"
#include "graphics/screen.h"
#include "graphics/video.h"
#include "graphics/window.h"
#include "js/js_game.h"
#include "platform/renderer.h"
#include "sound/sound.h"
#include "window/autoconfig_window.h"

static struct {
    int width;
    int height;
    int video_started;
} data;

// Original/Steam use BINKS/; some GOG layouts ship the same files under Video/.
static const char* PH_INTRO_CANDIDATES[] = {
    "BINKS/high/Intro_big.bik",
    "Video/High/Intro_big.bik",
    "BINKS/low/intro.bik",
    "Video/Low/intro.bik",
};

static int start_intro_video(void) {
    const int candidates = (int)(sizeof(PH_INTRO_CANDIDATES) / sizeof(PH_INTRO_CANDIDATES[0]));
    for (int i = 0; i < candidates; i++) {
        const char* path = PH_INTRO_CANDIDATES[i];
        if (video_start(path)) {
            video_size(&data.width, &data.height);
            video_init();
            data.video_started = 1;
            logs::info("Intro video: playing %s", path);
            return 1;
        }
        logs::info("Intro video: could not open %s", path);
    }
    return 0;
}

static int init(void) {
    data.width = 0;
    data.height = 0;
    data.video_started = 0;
    return 1;
}

static void show_logo(void) {
    g_sound.play_intro();
    autoconfig_window::show("window_logo");
}

static int ensure_video_started(void) {
    if (data.video_started) {
        return 1;
    }

    if (start_intro_video()) {
        return 1;
    }

    show_logo();
    return 0;
}

static void draw_background(int) {
    g_render.clear_screen();
}

static void draw_foreground(int) {
    if (ensure_video_started()) {
        video_draw_fullscreen();
    }
}

static void handle_input(const mouse* m, const hotkeys* h) {
    if (!data.video_started && !ensure_video_started()) {
        return;
    }

    if (m->left.went_up || m->right.went_up || video_is_finished() || h->enter_pressed) {
        g_sound.music_stop();
        video_stop();
        data.video_started = 0;
        show_logo();
    }
}

void window_intro_video_show(void) {
    if (init()) {
        window_type window = {
            "window_intro_video",
            draw_background,
            draw_foreground,
            handle_input
        };
        window_show(&window);
    }
}

void __window_intro_video_show() {
    window_intro_video_show();
}
ANK_FUNCTION(__window_intro_video_show)

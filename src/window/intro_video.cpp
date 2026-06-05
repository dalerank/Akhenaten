#include "intro_video.h"

#include "graphics/graphics.h"
#include "graphics/screen.h"
#include "graphics/video.h"
#include "graphics/window.h"
#include "platform/renderer.h"
#include "sound/sound.h"
#include "window/autoconfig_window.h"

static struct {
    int width;
    int height;
    int current_video;
    int video_started;
} data;

static const char* PH_INTRO_VIDEOS[] = {"BINKS/high/Intro_big.bik"};

static int start_next_video(void) {
    const int videos_num = (int)(sizeof(PH_INTRO_VIDEOS) / sizeof(PH_INTRO_VIDEOS[0]));
    while (data.current_video < videos_num) {
        if (video_start(PH_INTRO_VIDEOS[data.current_video++])) {
            video_size(&data.width, &data.height);
            video_init();
            data.video_started = 1;
            return 1;
        }
    }
    return 0;
}

static int init(void) {
    data.width = 0;
    data.height = 0;
    data.current_video = 0;
    data.video_started = 0;
    return 1;
}

static int ensure_video_started(void) {
    if (data.video_started) {
        return 1;
    }

    if (start_next_video()) {
        return 1;
    }

    g_sound.play_intro();
    autoconfig_window::show("window_logo");
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
        if (!start_next_video()) {
            g_sound.play_intro();
            autoconfig_window::show("window_logo");
        }
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

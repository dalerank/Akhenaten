#pragma once

#include "graphics/painter.h"
#include "overlays/city_overlay_fwd.h"
#include "core/threading.h"
#include "core/time.h"

bool game_pre_init();

bool game_init();

bool game_init_editor();

int game_reload_language();

void game_run();

void game_frame_draw();
void game_frame_end();
void game_sound_frame();
void game_handle_input_frame();
void game_draw_frame_warning();
void game_handle_input_after();
void game_exit_editor();

void game_exit();

struct fps_data_t {
    int frame_count;
    int last_fps;
    uint32_t last_update_time;
};

struct animation_timer {
    time_millis last_update;
    bool should_update;
};

struct game_t {
    enum {
        MAX_ANIM_TIMERS = 51
    };
    bool paused = false;
    bool save_debug_texture = false;
    bool animation = false;
    bool console = false;
    fps_data_t fps = {0, 0, 0};
    e_overlay current_overlay = OVERLAY_NONE;
    e_overlay previous_overlay = OVERLAY_NONE;

    animation_timer animation_timers[MAX_ANIM_TIMERS];

    void animation_timers_init();
    void animation_timers_update();
    bool animation_should_advance(uint32_t speed);

    threading::thread_pool mtrpc;
    threading::thread_pool mt;

    ::painter painter();
};

extern game_t game;

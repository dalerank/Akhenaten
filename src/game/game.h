#pragma once

#include "graphics/painter.h"

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

struct game_t {
    bool paused = false;
    bool save_debug_texture = false;
    bool animation = false;
    bool console = false;
    fps_data_t fps = {0, 0, 0};

    ::painter painter();
};

extern game_t game;

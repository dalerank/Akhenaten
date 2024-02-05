#pragma once

#include "graphics/painter.h"

bool game_pre_init();

bool game_init();

bool game_init_editor();

int game_reload_language();

void game_run();

void game_draw_frame();
void game_sound_frame();
void game_handle_input_frame();
void game_draw_frame_warning();
void game_handle_input_after();
void game_exit_editor();

void game_exit();

struct game_t {
    bool paused = false;
    bool save_debug_texture = false;
    bool console = false;

    ::painter painter();
};

extern game_t game;

#pragma once

#include "core/string.h"

void game_debug_cli_draw();
void game_debug_cli_message(pcstr msg);
void game_imgui_overlay_init();
void game_imgui_overlay_destroy();
void game_imgui_overlay_begin_frame();
void game_imgui_overlay_draw();

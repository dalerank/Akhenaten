#pragma once

#include "core/string.h"

#include <functional>
#include <iosfwd>

void game_debug_cli_draw();
void game_debug_properties_draw();
void game_debug_cli_message(pcstr msg);
void game_imgui_overlay_init();
void game_imgui_overlay_destroy();
void game_imgui_overlay_begin_frame();
void game_imgui_overlay_draw();
bool game_imgui_overlay_handle_event(void *event);
void game_toggle_debug_console();
void bind_debug_command(pcstr cmd, std::function<void(std::istream &, std::ostream &)> f);
void bind_debug_console_var_int(pcstr var, int &ref);
void bind_debug_console_var_int8(pcstr var, int8_t &ref);
void bind_debug_console_var_int16(pcstr var, int16_t &ref);
void bind_debug_console_var_bool(pcstr var, bool &ref);

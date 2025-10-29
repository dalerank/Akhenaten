#pragma once

#include "core/string.h"
#include "core/core.h"
#include "core/custom_span.hpp"

#include "figure/figure.h"
#include "dev/debug.h"

#include <functional>
#include <iosfwd>

#if !defined(GAME_PLATFORM_ANDROID)

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
void bind_debug_console_var_uint8(pcstr var, uint8_t &ref);
void bind_debug_console_var_float(pcstr var, float &ref);
void bind_debug_console_var_bool(pcstr var, bool &ref);

void game_debug_show_property(pcstr field, const int &v, bool disabled = false);
void game_debug_show_property(pcstr field, const uint8_t &v, custom_span<pcstr> modes, bool disabled = false);
void game_debug_show_property(pcstr field, const float &v, bool disabled = false);
void game_debug_show_property(pcstr field, const double &v, bool disabled = false);
void game_debug_show_property(pcstr field, const e_move_type &v, bool disabled = false);
void game_debug_show_property(pcstr field, const int8_t &v, bool disabled = false);
void game_debug_show_property(pcstr field, const short &v, bool disabled = false);
void game_debug_show_property(pcstr field, const uint8_t &v, bool disabled = false);
void game_debug_show_property(pcstr field, const uint16_t &v, bool disabled = false);
void game_debug_show_property(pcstr field, const bool &v, bool disabled = false);
void game_debug_show_property(pcstr field, const pcstr v);
void game_debug_show_property(pcstr field, const bstring64 &v, bool disabled = false);
void game_debug_show_property(pcstr field, const bstring256 &v, bool disabled = false);
void game_debug_show_property(pcstr field, const xstring &v, bool disabled = false);
void game_debug_show_property(pcstr field, const vec2i &v, bool disabled = false);
void game_debug_show_property(pcstr field, const tile2i &v, bool disabled = false);
void game_debug_show_property(pcstr field, const std::function<void()> &f, bool disabled = false);
void game_debug_show_property(pcstr field, const game_date_t &f, bool disabled = false);

#else 

inline void game_debug_cli_draw() {}
inline void game_debug_properties_draw() {}
inline void game_imgui_overlay_draw() {}
inline void game_debug_show_property(...) {}
inline void game_imgui_overlay_begin_frame() {}
inline void game_imgui_overlay_init() {}
inline bool game_imgui_overlay_handle_event(...) { return false; }
inline void bind_debug_command(...) {}
inline void bind_debug_console_var_int(...) {}
inline void bind_debug_console_var_int8(...) {}
inline void bind_debug_console_var_uint8(...) {}
inline void bind_debug_console_var_int16(...) {}
inline void bind_debug_console_var_float(...) {}
inline void bind_debug_console_var_bool(...) {}
inline void game_imgui_overlay_destroy() {}

#endif //GAME_PLATFORM_ANDROID



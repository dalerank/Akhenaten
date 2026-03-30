#pragma once

#include <cstdint>
#include "platform/platform.h"

#ifndef GAME_PLATFORM_ANDROID

void game_perfmon_overlay_init();
void game_perfmon_draw();
void game_perfmon_frame_mark_end();
void game_perfmon_set_phase_ms(double game_update_ms, double draw_ms);

#else

inline void game_perfmon_overlay_init() {}
inline void game_perfmon_frame_mark_end() {}
inline void game_perfmon_set_phase_ms(double, double) {}
inline void game_perfmon_draw() {}

#endif

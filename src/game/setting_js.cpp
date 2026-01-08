#include "settings.h"

#include "js/js_game.h"
#include "platform/renderer.h"
#include "game/system.h"

int __game_difficulty() { return game_difficulty(); }
ANK_FUNCTION(__game_difficulty)

void __game_decrease_difficulty() { g_settings.difficulty.decrease(); }
ANK_FUNCTION(__game_decrease_difficulty)

void __game_increase_difficulty() { g_settings.difficulty.increase(); }
ANK_FUNCTION(__game_increase_difficulty)

bool __game_is_fullscreen_only() { return g_render.is_fullscreen_only(); }
ANK_FUNCTION(__game_is_fullscreen_only)

bool __game_monthly_autosave() { return g_settings.monthly_autosave; }
ANK_FUNCTION(__game_monthly_autosave)

void __game_set_monthly_autosave(bool v) { g_settings.monthly_autosave = v; }
ANK_FUNCTION_1(__game_set_monthly_autosave)

int __game_tooltips_mode() { return g_settings.tooltips_mode; }
ANK_FUNCTION(__game_tooltips_mode)

void __game_set_tooltips_mode(int v) { g_settings.tooltips_mode = (e_tooltip_mode)v; }
ANK_FUNCTION_1(__game_set_tooltips_mode)

bool __game_warnings() { return g_settings.warnings; }
ANK_FUNCTION(__game_warnings)

void __game_set_warnings(bool v) { g_settings.warnings = v; }
ANK_FUNCTION_1(__game_set_warnings)
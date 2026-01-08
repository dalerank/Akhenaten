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
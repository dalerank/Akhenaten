#include "settings.h"

#include "js/js_game.h"

int __game_difficulty() { return game_difficulty(); }
ANK_FUNCTION(__game_difficulty)

void __game_decrease_difficulty() { g_settings.difficulty.decrease(); }
ANK_FUNCTION(__game_decrease_difficulty)

void __game_increase_difficulty() { g_settings.difficulty.increase(); }
ANK_FUNCTION(__game_increase_difficulty)

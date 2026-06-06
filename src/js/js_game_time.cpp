#include "game/game.h"
#include "js/js_game.h"

int __game_absolute_day() { return game.simtime.absolute_day(true); } ANK_FUNCTION(__game_absolute_day)
int __game_simtime_absolute_day(bool since_start) { return game.simtime.absolute_day(since_start); } ANK_FUNCTION_1(__game_simtime_absolute_day)
int __game_simtime_absolute_tick(bool since_start) { return game.simtime.absolute_tick(since_start); } ANK_FUNCTION_1(__game_simtime_absolute_tick)

ANK_GLOBAL_OBJECT(game.simtime, __game_simtime,
    tick,
    day,
    month,
    year);



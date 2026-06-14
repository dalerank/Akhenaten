log_info("akhenaten: game_speed config started")

// Minimum milliseconds between simulation ticks, indexed by game_speed_index.
// game_speed_index = (100 - gameopt_game_speed%) / 10
//   100% -> 0 ms (as fast as frames allow)
//    80% -> 35 ms (default)
//    10% -> 500 ms
//   <=0% -> index >= 10, simulation paused (C++ returns before tick_timer_ms is read)
var GAME_SPEED_TICK_TIMER_FUDGE_MS = 2
var GAME_SPEED_MILLIS_PER_TICK = [0, 20, 35, 55, 80, 110, 160, 240, 350, 500, 700]

[es=event_update_game_tick_timer]
function event_update_game_tick_timer_handler(ev) {
    var speed = Math.round(game_features.gameopt_game_speed)
    var index = 0
    if (speed > 100) {
        index = 0
    } else {
        index = Math.floor((100 - speed) / 10)
        index = Math.clamp(index, 0, GAME_SPEED_MILLIS_PER_TICK.length - 1)
    }
    game.tick_timer_ms = GAME_SPEED_MILLIS_PER_TICK[index] + GAME_SPEED_TICK_TIMER_FUDGE_MS
}
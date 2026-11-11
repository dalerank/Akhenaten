// Fireman at a fire vs OG (walkers.c:919, 961, 983): on arrival wait_ticks = fire_fight_ticks (50) and
// extinguish_ticks = 0; he leaves only when --wait_ticks <= 0 and a whole fight_fire animation (36 frames)
// has played. A ruin that is out or out of reach sets wait_ticks = 1, so he still stays 36 ticks + the leaving one.
// Markers:
//   [test-marker] fireman_fight_near_ok
//   [test-marker] fireman_fight_far_ok

var FIRE_FIGHT_TICKS = 50
var FIGHT_FIRE_FRAMES = 36

function test310_fail(msg) {
    __log_info_native('[test:310] FAIL: ' + msg)
}

function run_test() {
    __log_info_native('[test:310] fireman fight frames OG')
    test_reload_city_session('data/default.map')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = __test_burning_ruin_create(cx, cy + 10)
    if (!bid) {
        test310_fail('ruin create failed')
        __test_signal_ready()
        return
    }

    var near = __test_fireman_ticks_at_fire(bid, 1)
    if (near == FIRE_FIGHT_TICKS) {
        __log_marker('fireman_fight_near_ok')
    } else {
        test310_fail('next to the ruin: ' + near + ' ticks, want ' + FIRE_FIGHT_TICKS)
    }

    var far = __test_fireman_ticks_at_fire(bid, 3)
    if (far == FIGHT_FIRE_FRAMES + 1) {
        __log_marker('fireman_fight_far_ok')
    } else {
        test310_fail('out of reach: ' + far + ' ticks, want ' + (FIGHT_FIRE_FRAMES + 1))
    }

    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('fireman_fight_near_ok') && __test_find_inlog('fireman_fight_far_ok')
}

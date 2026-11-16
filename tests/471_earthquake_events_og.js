// EVENT_TYPE_EARTHQUAKE vs OG disaster_events.c:157-229 and event_manager.c scenario_earthquake_process:
// due in the event's month, all four fronts start on the earthquake point, one random front moves
// every `delay` ticks, the quake is over after amount * 25 steps (at least 25), several quake events
// run one after another. Each fault tile also redraws meadow, wall and canal tiles (Augustus 3bdd1189d).
// Markers:
//   [test-marker] earthquake_og_start_ok
//   [test-marker] earthquake_og_steps_ok
//   [test-marker] earthquake_og_second_ok

var EARTHQUAKE_RUNNING = 1
var EARTHQUAKE_OVER = 2

function test471_fail(msg) {
    __log_info_native('[test:471] FAIL: ' + msg)
}

function test471_find_free_tile() {
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    for (var r = 0; r < 40; r++) {
        for (var dx = -r; dx <= r; dx++) {
            for (var dy = -r; dy <= r; dy++) {
                if (__test_earthquake_tile_free(cx + dx, cy + dy)) {
                    return { x: cx + dx, y: cy + dy }
                }
            }
        }
    }
    return null
}

function test471_quake(tag, amount, delay) {
    var ev = city.create_chain_event({ tag_id: tag, type: EVENT_TYPE_EARTHQUAKE, amount: amount, trigger: EVENT_TRIGGER_ONCE })
    ev.set_param('delay', delay)
    return __test_event_id_by_tag(tag)
}

function run_test() {
    __log_info_native('[test:471] OG earthquake events')
    test_reload_city_session('data/default.map')
    var p = test471_find_free_tile()
    if (!p) {
        test471_fail('no free tile')
        __test_signal_ready()
        return
    }
    __test_set_earthquake_point(p.x, p.y)
    var point = p.x * 1000 + p.y

    // A meadow tile away from the fault with a stale image: the quake must redraw it (Augustus 3bdd1189d).
    var meadow = null
    for (var mx = p.x + 6; mx < p.x + 30 && !meadow; mx++) {
        if (__test_earthquake_tile_free(mx, p.y)) {
            meadow = { x: mx, y: p.y }
        }
    }
    if (meadow) {
        __test_map_set_meadow(meadow.x, meadow.y, 77777)
    }

    var first = test471_quake(47101, 1, 2)
    var second = test471_quake(47102, 2, 0)

    __test_earthquake_tick(1)
    if (__test_event_state(first) != EARTHQUAKE_RUNNING || __test_event_state(second) != 0) {
        test471_fail('start: first=' + __test_event_state(first) + ' second=' + __test_event_state(second))
        __test_signal_ready()
        return
    }
    for (var f = 0; f < 4; f++) {
        if (__test_earthquake_front(first, f) != point) {
            test471_fail('front ' + f + ' at ' + __test_earthquake_front(first, f) + ' want ' + point)
            __test_signal_ready()
            return
        }
    }
    if (!meadow || __test_map_image(meadow.x, meadow.y) == 77777) {
        test471_fail('meadow tile ' + (meadow ? meadow.x + ',' + meadow.y : 'none') + ' was not redrawn')
        __test_signal_ready()
        return
    }
    __log_marker('earthquake_og_start_ok')

    // amount 1 -> 25 steps, one step every 2 ticks.
    __test_earthquake_tick(49)
    if (__test_event_state(first) != EARTHQUAKE_RUNNING || __test_earthquake_duration(first) != 24) {
        test471_fail('tick 49: state=' + __test_event_state(first) + ' duration=' + __test_earthquake_duration(first))
        __test_signal_ready()
        return
    }
    __test_earthquake_tick(1)
    if (__test_event_state(first) != EARTHQUAKE_OVER || __test_earthquake_duration(first) != 25) {
        test471_fail('tick 50: state=' + __test_event_state(first) + ' duration=' + __test_earthquake_duration(first))
        __test_signal_ready()
        return
    }
    __log_marker('earthquake_og_steps_ok')

    // The second quake waited; it starts on the next tick and runs 2 * 25 steps, one per tick.
    __test_earthquake_tick(1)
    if (__test_event_state(second) != EARTHQUAKE_RUNNING) {
        test471_fail('second did not start: ' + __test_event_state(second))
        __test_signal_ready()
        return
    }
    __test_earthquake_tick(50)
    if (__test_event_state(second) != EARTHQUAKE_OVER || __test_earthquake_duration(second) != 50) {
        test471_fail('second: state=' + __test_event_state(second) + ' duration=' + __test_earthquake_duration(second))
        __test_signal_ready()
        return
    }
    __log_marker('earthquake_og_second_ok')
    __test_set_earthquake_point(-1, -1)
    __test_signal_ready()
}

function check_valid() {
    var markers = ['earthquake_og_start_ok', 'earthquake_og_steps_ok', 'earthquake_og_second_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:471] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

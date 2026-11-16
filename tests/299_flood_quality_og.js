// OG floods.c: next flood quality = quality_initial + weighted step rolled from the game LFSR
// (random_generate_next, random1_15bit % 99 + 1), clamped 0..100. Scenario "worse/better flood"
// events shift quality_next by (-3 - crt_rand()%8)*10 / (crt_rand()%8 + 3)*10, clamped.

var __test299_ok = false
var TEST299_ROLLS = 2000
var TEST299_EVENTS = 24

var TEST299_STEPS = [
    [2, 100], [3, 80], [5, 60], [10, 40], [15, 20], [30, 0],
    [15, -20], [10, -40], [5, -60], [3, -80], [2, -100]
]

function test299_fail(msg) {
    __log_info_native('[test:299] FAIL: ' + msg)
    __test_signal_ready()
}

function test299_clamp(v) {
    return v < 0 ? 0 : (v > 100 ? 100 : v)
}

function test299_lfsr_step(iv) {
    for (var i = 0; i < 31; i++) {
        var bit = ((iv >>> 4) ^ iv) & 1
        iv = iv >>> 1
        if (bit) {
            iv = iv | 0x40000000
        }
    }
    return iv
}

function test299_delta_for_roll(roll) {
    var sum = 0
    for (var i = 0; i < TEST299_STEPS.length; i++) {
        sum += TEST299_STEPS[i][0]
        if (roll < sum) {
            return TEST299_STEPS[i][1]
        }
    }
    return 0
}

// MSVC rand() on the low 31 bits of the state; same as test 297.
function test299_crt_next(state) {
    var hi = Math.floor(state / 65536)
    var lo = state % 65536
    var mul = ((hi * 214013) % 32768) * 65536 + lo * 214013
    return (mul + 2531011) % 2147483648
}

function test299_crt_first_roll(state) {
    return Math.floor(test299_crt_next(state) / 65536)
}

function test299_check_rolls() {
    var seed = 12345
    var seen = {}
    var initials = [0, 30, 50, 70, 100]
    for (var i = 0; i < TEST299_ROLLS; i++) {
        seed = (seed * 16807) % 2147483647
        var iv1 = seed
        seed = (seed * 16807) % 2147483647
        var iv2 = seed
        var initial = initials[i % initials.length]
        var prev_next = (i * 7) % 101

        __test_random_set_state(iv1, iv2)
        __test_floods_set_quality(initial, prev_next)
        __test_floods_update_next_params()

        var next_iv1 = test299_lfsr_step(iv1)
        var roll = (next_iv1 & 0x7fff) % 99 + 1
        var delta = test299_delta_for_roll(roll)
        var expected = test299_clamp(initial + delta)
        var got = __test_floods_quality_next()
        if (got != expected) {
            test299_fail('roll ' + i + ' iv1=' + iv1 + ' initial=' + initial + ' roll=' + roll
                         + ' expected ' + expected + ' got ' + got)
            return false
        }
        if (__test_random_iv1() != next_iv1) {
            test299_fail('roll ' + i + ' LFSR not advanced exactly once: iv1=' + __test_random_iv1()
                         + ' expected ' + next_iv1)
            return false
        }
        if (__city_floods.quality_current != prev_next) {
            test299_fail('roll ' + i + ' quality_current=' + __city_floods.quality_current
                         + ' expected previous quality_next ' + prev_next)
            return false
        }
        seen[delta] = true
    }
    for (var s = 0; s < TEST299_STEPS.length; s++) {
        if (!seen[TEST299_STEPS[s][1]]) {
            test299_fail('step delta ' + TEST299_STEPS[s][1] + ' never rolled')
            return false
        }
    }
    return true
}

function test299_check_events(type, sign, tag_base) {
    for (var i = 0; i < TEST299_EVENTS; i++) {
        var start = (i * 13) % 101
        __test_floods_set_quality(start, start)
        var state = __test_crt_sync_state31()
        var r = test299_crt_first_roll(state) % 8
        var expected = test299_clamp(start + sign * (r + 3) * 10)
        city.create_chain_event({
            tag_id: tag_base + i,
            type: type,
            amount: 0,
            trigger: EVENT_TRIGGER_ONCE
        }).execute()
        var got = __test_floods_quality_next()
        if (got != expected) {
            test299_fail('event type ' + type + ' #' + i + ' start=' + start + ' r=' + r
                         + ' expected ' + expected + ' got ' + got)
            return false
        }
    }
    return true
}

function run_test() {
    __log_info_native('[test:299] flood quality OG')
    test_reload_city_session('data/default.map')

    if (!test299_check_rolls()) {
        return
    }
    __log_marker('test299_next_quality_table_ok')

    if (!test299_check_events(EVENT_TYPE_FAILED_FLOOD, -1, 29900)) {
        return
    }
    __log_marker('test299_worse_flood_event_ok')

    if (!test299_check_events(EVENT_TYPE_PERFECT_FLOOD, 1, 29950)) {
        return
    }
    __log_marker('test299_better_flood_event_ok')

    __test299_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test299_ok
        && __test_find_inlog('[test-marker] test299_next_quality_table_ok')
        && __test_find_inlog('[test-marker] test299_worse_flood_event_ok')
        && __test_find_inlog('[test-marker] test299_better_flood_event_ok')
}

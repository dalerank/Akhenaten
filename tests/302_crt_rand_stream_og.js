// OG crt_rand (MSVC rand, crt_compat.c) consumers outside the gods:
//  - figure_create draws one value (figure_core.c:95, phrase sequences);
//  - figure_name_init seeds 41 name counters high to low, one draw each (scenario_start.c:388-393);
//  - a fishing spot draws its start frame (scenario_start.c:406-408) and, while animating, one value per tick
//    (boats.c:427-431);
//  - the predator wall-clock reseed (animals.c:343-345) is off under integral tests.
// The stream is synced from the live state, so every draw is predicted exactly.

var __test302_ok = false

var TEST302_FISHING_SPOT_FRAMES = 24
var TEST302_FISHING_SPOT_RANDOM_PAUSE = 100
var TEST302_FISHING_SPOT_PAUSE = 25
var TEST302_SPOT_TICKS = 400

function test302_fail(msg) {
    __log_info_native('[test:302] FAIL: ' + msg)
    __test_signal_ready()
}

// MSVC rand() on the low 31 bits of the state; bit 31 never reaches an output.
function test302_next(state) {
    var hi = Math.floor(state / 65536)
    var lo = state % 65536
    var mul = ((hi * 214013) % 32768) * 65536 + lo * 214013
    return (mul + 2531011) % 2147483648
}

function test302_out(state) {
    return Math.floor(state / 65536)
}

function test302_advance(state, n) {
    for (var i = 0; i < n; i++) {
        state = test302_next(state)
    }
    return state
}

function test302_figure_create_draws_one() {
    for (var i = 0; i < 20; i++) {
        var s0 = __test_crt_sync_state31()
        var fid = __test_figure_create(FIGURE_TAX_COLLECTOR, -1, -1)
        if (!fid) {
            return 'figure_create failed'
        }
        var got = __test_crt_sync_state31()
        var expected = test302_advance(s0, 2)
        if (got != expected) {
            return 'figure_create #' + i + ' moved the stream to ' + got + ', expected ' + expected
        }
    }
    return ''
}

function test302_name_init_seeds_counters() {
    var s = __test_crt_sync_state31()
    __test_figure_name_init()
    for (var slot = 40; slot >= 0; slot--) {
        s = test302_next(s)
        var expected = test302_out(s) & 15
        var got = __test_figure_name_counter(slot)
        if (got != expected) {
            return 'slot ' + slot + ' = ' + got + ', expected ' + expected
        }
    }
    var after = __test_crt_sync_state31()
    if (after != test302_next(s)) {
        return 'figure_name_init drew a wrong number of values'
    }
    return ''
}

function test302_fishing_spot_stream() {
    var s = __test_crt_sync_state31()
    var fid = __test_fishing_spot_create(10, 10)
    if (!fid) {
        return 'fishing spot create failed'
    }
    s = test302_advance(s, 2)
    var frame = test302_out(s) & 31
    var wait = 0
    var pause = 0
    var state = __test_fishing_spot_state(fid)
    if (state != frame) {
        return 'start state ' + state + ', expected frame ' + frame
    }
    if (__test_crt_sync_state31() != test302_next(s)) {
        return 'fishing spot create drew a wrong number of values'
    }
    s = test302_next(s)

    var cycles = 0
    for (var t = 0; t < TEST302_SPOT_TICKS; t++) {
        if (frame < TEST302_FISHING_SPOT_FRAMES) {
            frame++
            s = test302_next(s)
            wait = test302_out(s) % TEST302_FISHING_SPOT_RANDOM_PAUSE
        } else {
            frame = TEST302_FISHING_SPOT_FRAMES
            pause++
            if (pause >= wait + TEST302_FISHING_SPOT_PAUSE) {
                pause = 0
                frame = 0
                cycles++
            }
        }
        __test_fishing_spot_og_tick(fid)
        var expected = frame | (wait << 8) | (pause << 16)
        var got = __test_fishing_spot_state(fid)
        if (got != expected) {
            return 'tick ' + t + ' state ' + got + ', expected ' + expected
        }
    }
    if (__test_crt_sync_state31() != test302_next(s)) {
        return 'fishing spot ticks drew a wrong number of values'
    }
    if (cycles == 0) {
        return 'fishing spot never finished a pause in ' + TEST302_SPOT_TICKS + ' ticks'
    }
    return ''
}

function test302_clock_reseed_off() {
    var s0 = __test_crt_sync_state31()
    __test_crt_reseed_from_clock(12345)
    var got = __test_crt_sync_state31()
    if (got != test302_next(s0)) {
        return 'predator clock reseed changed the stream under integral tests'
    }
    return ''
}

function run_test() {
    __log_info_native('[test:302] crt rand stream OG')
    test_reload_city_session('data/default.map')

    var err = test302_figure_create_draws_one()
    if (err) {
        return test302_fail(err)
    }
    __log_marker('test302_figure_create_one_draw_ok')

    err = test302_name_init_seeds_counters()
    if (err) {
        return test302_fail(err)
    }
    __log_marker('test302_name_init_ok')

    err = test302_fishing_spot_stream()
    if (err) {
        return test302_fail(err)
    }
    __log_marker('test302_fishing_spot_ok')

    err = test302_clock_reseed_off()
    if (err) {
        return test302_fail(err)
    }
    __log_marker('test302_clock_reseed_off_ok')

    __test302_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test302_ok
        && __test_find_inlog('[test-marker] test302_figure_create_one_draw_ok')
        && __test_find_inlog('[test-marker] test302_name_init_ok')
        && __test_find_inlog('[test-marker] test302_fishing_spot_ok')
        && __test_find_inlog('[test-marker] test302_clock_reseed_off_ok')
}

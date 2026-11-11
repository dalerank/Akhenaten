// OG gods.c Ra major curse: `if (rand()%3==0) A; else if (rand()%3==1) B; else C;`, two separate
// MSVC rand() draws (crt_compat.c). A = harsh trade, B = kingdom -15, C = no traders.
// The stream is synced from the live state, so each cast is predicted exactly.

var __test297_ok = false
var TEST297_CASTS = 900

function test297_fail(msg) {
    __log_info_native('[test:297] FAIL: ' + msg)
    __test_signal_ready()
}

// MSVC rand() on the low 31 bits of the state; bit 31 never reaches an output.
function test297_next(state) {
    var hi = Math.floor(state / 65536)
    var lo = state % 65536
    var mul = ((hi * 214013) % 32768) * 65536 + lo * 214013
    return (mul + 2531011) % 2147483648
}

function test297_out(state) {
    return Math.floor(state / 65536)
}

function test297_predict(state) {
    var s1 = test297_next(state)
    if (test297_out(s1) % 3 == 0) {
        return 'A'
    }
    var s2 = test297_next(s1)
    return (test297_out(s2) % 3 == 1) ? 'B' : 'C'
}

function test297_cast() {
    __test_ra_clear_curse_months()
    __test_kingdom_set_rating(80)
    var state = __test_crt_sync_state31()
    var expected = test297_predict(state)
    __test_run_console_command('god_major_curse ' + GOD_RA)

    var harsh = __test_ra_harsh_trade_months()
    var none = __test_ra_no_traders_months()
    var rating = __test_kingdom_rating()
    var got = '?'
    if (harsh == 12 && none == 0 && rating == 80) {
        got = 'A'
    } else if (harsh == 0 && none == 0 && rating == 65) {
        got = 'B'
    } else if (harsh == 0 && none == 12 && rating == 80) {
        got = 'C'
    }
    return { expected: expected, got: got, detail: 'harsh=' + harsh + ' none=' + none + ' rating=' + rating }
}

function run_test() {
    __log_info_native('[test:297] religion crt rand OG')
    test_reload_city_session('data/default.map')

    var counts = { A: 0, B: 0, C: 0 }
    var single_roll_mismatch = 0
    for (var i = 0; i < TEST297_CASTS; i++) {
        var r = test297_cast()
        if (r.got != r.expected) {
            return test297_fail('cast ' + i + ' expected ' + r.expected + ' got ' + r.got + ' (' + r.detail + ')')
        }
        counts[r.got]++
    }
    __log_marker('test297_ra_curse_predicted_ok')

    // A single roll would give ~1/3 each; OG gives 1/3, 2/9, 4/9.
    __log_info_native('[test:297] A=' + counts.A + ' B=' + counts.B + ' C=' + counts.C)
    if (!(counts.C > counts.A && counts.C > counts.B && counts.A > counts.B)) {
        return test297_fail('distribution is not OG-shaped: A=' + counts.A + ' B=' + counts.B + ' C=' + counts.C)
    }
    __log_marker('test297_ra_curse_distribution_ok')

    __test297_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test297_ok
        && __test_find_inlog('[test-marker] test297_ra_curse_predicted_ok')
        && __test_find_inlog('[test-marker] test297_ra_curse_distribution_ok')
}

// Determinism: the same map, run headless for the same number of ticks, must serialize to the
// same per-chunk state hash. On a mismatch the differing chunks are logged — that is the finding.

var __t290_ok = false
var __t290_ticks = 500

function t290_fail(msg) {
    __log_info_native('[test:290] FAIL: ' + msg)
    __test_signal_ready()
}

function t290_parse(hash) {
    var out = {}
    var parts = hash.split(';')
    for (var i = 0; i < parts.length; i++) {
        var kv = parts[i].split('=')
        if (kv.length == 2) {
            out[kv[0]] = kv[1]
        }
    }
    return out
}

function t290_diff(label, a, b) {
    var names = []
    for (var k in a) {
        if (k != 'total' && a[k] != b[k]) {
            names.push(k)
        }
    }
    for (var k in b) {
        if (k != 'total' && a[k] === undefined) {
            names.push(k)
        }
    }
    for (var i = 0; i < names.length; i++) {
        __log_info_native('[test:290] ' + label + ' chunk differs: ' + names[i] + ' ' + a[names[i]] + ' ' + b[names[i]])
    }
    return names
}

// Returns { start, end } hashes, or null on setup failure.
function t290_run(pass) {
    // Map load seeds the OG figure-name counters from crt_rand, so both passes start from the same crt state.
    __test_crt_srand(1)
    if (!test_reload_city_session('data/default.map')) {
        return null
    }
    __test_process_events()
    var start = __test_state_hash()
    var ran = __test_run_ticks(__t290_ticks)
    if (ran != __t290_ticks) {
        __log_info_native('[test:290] pass ' + pass + ' ran ' + ran + ' ticks')
        return null
    }
    var end = __test_state_hash()
    if (!start || !end) {
        return null
    }
    return { start: t290_parse(start), end: t290_parse(end) }
}

function run_test() {
    __log_info_native('[test:290] headless ticks state hash determinism')

    var a = t290_run(1)
    if (!a) {
        return t290_fail('pass 1 setup')
    }
    var b = t290_run(2)
    if (!b) {
        return t290_fail('pass 2 setup')
    }

    __log_info_native('[test:290] start ' + a.start.total + ' ' + b.start.total
        + ' end ' + a.end.total + ' ' + b.end.total)

    var start_diff = t290_diff('start', a.start, b.start)
    if (start_diff.length) {
        __log_marker('t290_start_differs:' + start_diff.join(','))
    }

    if (a.end.total != b.end.total) {
        var end_diff = t290_diff('end', a.end, b.end)
        __log_marker('t290_end_differs:' + end_diff.join(','))
        return t290_fail('hash after ' + __t290_ticks + ' ticks differs in ' + end_diff.length + ' chunks')
    }

    __log_marker('t290_headless_hash_equal')
    __t290_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __t290_ok && __test_find_inlog('[test-marker] t290_headless_hash_equal')
}

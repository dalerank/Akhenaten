// Determinism: the same map, run headless for the same number of ticks, must serialize to the
// same per-chunk state hash. On a mismatch the differing chunks are logged — that is the finding.

var __t304_ok = false
var __t304_ticks = 500

function t304_fail(msg) {
    __log_info_native('[test:304] FAIL: ' + msg)
    __test_signal_ready()
}

function t304_parse(hash) {
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

function t304_diff(label, a, b) {
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
        __log_info_native('[test:304] ' + label + ' chunk differs: ' + names[i] + ' ' + a[names[i]] + ' ' + b[names[i]])
    }
    return names
}

// Returns { start, end } hashes, or null on setup failure.
function t304_run(pass) {
    // Map load seeds the OG figure-name counters from crt_rand, so both passes start from the same crt state.
    __test_crt_srand(1)
    if (!test_reload_city_session('data/default.map')) {
        return null
    }
    __test_process_events()
    var start = __test_state_hash()
    var ran = __test_run_ticks(__t304_ticks)
    if (ran != __t304_ticks) {
        __log_info_native('[test:304] pass ' + pass + ' ran ' + ran + ' ticks')
        return null
    }
    var end = __test_state_hash()
    if (!start || !end) {
        return null
    }
    return { start: t304_parse(start), end: t304_parse(end) }
}

function run_test() {
    __log_info_native('[test:304] headless ticks state hash determinism')

    var a = t304_run(1)
    if (!a) {
        return t304_fail('pass 1 setup')
    }
    var b = t304_run(2)
    if (!b) {
        return t304_fail('pass 2 setup')
    }

    __log_info_native('[test:304] start ' + a.start.total + ' ' + b.start.total
        + ' end ' + a.end.total + ' ' + b.end.total)

    var start_diff = t304_diff('start', a.start, b.start)
    if (start_diff.length) {
        __log_marker('t304_start_differs:' + start_diff.join(','))
    }

    if (a.end.total != b.end.total) {
        var end_diff = t304_diff('end', a.end, b.end)
        __log_marker('t304_end_differs:' + end_diff.join(','))
        return t304_fail('hash after ' + __t304_ticks + ' ticks differs in ' + end_diff.length + ' chunks')
    }

    __log_marker('t304_headless_hash_equal')
    __t304_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __t304_ok && __test_find_inlog('[test-marker] t304_headless_hash_equal')
}

// Loading a map must not depend on what ran before it: load B, run some days; then load A, run some
// days and load B again, run the same days — both B runs must serialize to the same state, right after
// the load and after the days. A differing chunk is state that leaked from the previous session.
// Markers:
//   [test-marker] t794_load_invariant
//   [test-marker] t794_leak:<pair>:<stage>:<chunks>

var __t794_ok = false
var __t794_days_a = 40
var __t794_days_b = 20
var __t794_pairs = [
    { a: 'data/default.map', b: 'data/maps/m_000_nubt.map' },
    { a: 'data/maps/m_000_nubt.map', b: 'data/default.map' },
]

function t794_fail(msg) {
    __log_info_native('[test:794] FAIL: ' + msg)
    __test_signal_ready()
}

function t794_load(map, seed) {
    __test_crt_srand(seed)
    __test_libc_srand(seed)
    if (!test_reload_city_session(map)) {
        return false
    }
    __test_process_events()
    return true
}

function t794_run_days(days) {
    var ticks = days * 50
    return __test_run_ticks(ticks) == ticks
}

function t794_chunks(hash) {
    var out = {}
    var parts = hash.split(';')
    for (var i = 1; i < parts.length; i++) {
        var kv = parts[i].split('=')
        out[kv[0]] = kv[1]
    }
    return out
}

function t794_diff(a, b) {
    var ca = t794_chunks(a)
    var cb = t794_chunks(b)
    var names = []
    for (var k in ca) {
        if (ca[k] !== cb[k]) {
            names.push(k)
        }
    }
    return names.join(',')
}

function t794_snapshot() {
    return { digest: __test_state_digest(), chunks: __test_state_hash() }
}

// Returns { loaded, ran } snapshots of map B, or null on setup failure.
function t794_run_b(map) {
    if (!t794_load(map, 1)) {
        return null
    }
    var loaded = t794_snapshot()
    if (!t794_run_days(__t794_days_b)) {
        return null
    }
    return { loaded: loaded, ran: t794_snapshot() }
}

function t794_compare(label, stage, clean, now) {
    __log_info_native('[test:794] ' + label + ' ' + stage + ' ' + clean.digest + ' ' + now.digest)
    if (clean.digest == now.digest) {
        return ''
    }
    var diff = t794_diff(clean.chunks, now.chunks)
    __log_marker('t794_leak:' + label + ':' + stage + ':' + diff)
    return label + ' ' + stage + ' differs in ' + diff
}

function t794_check_pair(index, pair) {
    var label = 'pair' + index + '(' + pair.a + '->' + pair.b + ')'
    var clean = t794_run_b(pair.b)
    if (!clean) {
        return 'clean run of ' + pair.b
    }

    if (!t794_load(pair.a, 7)) {
        return 'load of ' + pair.a
    }
    __test_barracks_request_tower_sentry()
    if (!t794_run_days(__t794_days_a)) {
        return 'run of ' + pair.a
    }

    var dirty = t794_run_b(pair.b)
    if (!dirty) {
        return 'second run of ' + pair.b
    }
    return t794_compare(label, 'loaded', clean.loaded, dirty.loaded)
        || t794_compare(label, 'ran', clean.ran, dirty.ran)
}

function run_test() {
    __log_info_native('[test:794] load invariance')

    for (var i = 0; i < __t794_pairs.length; i++) {
        var err = t794_check_pair(i, __t794_pairs[i])
        if (err) {
            return t794_fail(err)
        }
    }

    __log_marker('t794_load_invariant')
    __t794_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __t794_ok && __test_find_inlog('[test-marker] t794_load_invariant')
}

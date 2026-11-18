// Loading a map clears the grids that only a previous session filled: the undo backups of the canal and
// sprite grids are copied when a building is placed and are part of the save, so after A (canal and
// sprite values set, a building placed) loading B must serialize exactly like a clean load of B.
// Markers:
//   [test-marker] t795_backups_cleared
//   [test-marker] t795_leak:<chunks>

var __t795_ok = false
var __t795_map_a = 'data/default.map'
var __t795_map_b = 'data/maps/m_000_nubt.map'

function t795_fail(msg) {
    __log_info_native('[test:795] FAIL: ' + msg)
    __test_signal_ready()
}

function t795_load(map) {
    __test_crt_srand(1)
    __test_libc_srand(1)
    if (!test_reload_city_session(map)) {
        return false
    }
    __test_process_events()
    return true
}

function t795_chunks(hash) {
    var out = {}
    var parts = hash.split(';')
    for (var i = 1; i < parts.length; i++) {
        var kv = parts[i].split('=')
        out[kv[0]] = kv[1]
    }
    return out
}

function t795_diff(a, b) {
    var ca = t795_chunks(a)
    var cb = t795_chunks(b)
    var names = []
    for (var k in ca) {
        if (ca[k] !== cb[k]) {
            names.push(k)
        }
    }
    return names.join(',')
}

function t795_fill_backups() {
    __test_set_treasury(10000)
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    for (var dx = 0; dx < 4; dx++) {
        var tile = { x: cx + dx, y: cy - 6 }
        __map_canal_set(tile, 3)
        __map_sprite_animation_set(tile, 5)
    }
    return test_building_place(BUILDING_WORK_CAMP, -1, -1) > 0
}

function run_test() {
    __log_info_native('[test:795] load clears undo backup grids')

    if (!t795_load(__t795_map_b)) {
        return t795_fail('clean load of ' + __t795_map_b)
    }
    var clean = __test_state_hash()

    if (!t795_load(__t795_map_a)) {
        return t795_fail('load of ' + __t795_map_a)
    }
    if (!t795_fill_backups()) {
        return t795_fail('no building placed on ' + __t795_map_a)
    }

    if (!t795_load(__t795_map_b)) {
        return t795_fail('second load of ' + __t795_map_b)
    }
    var dirty = __test_state_hash()

    var diff = t795_diff(clean, dirty)
    if (diff) {
        __log_marker('t795_leak:' + diff)
        return t795_fail(__t795_map_b + ' after ' + __t795_map_a + ' differs in ' + diff)
    }

    __log_marker('t795_backups_cleared')
    __t795_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __t795_ok && __test_find_inlog('[test-marker] t795_backups_cleared')
}

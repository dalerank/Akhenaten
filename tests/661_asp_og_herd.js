// FIGURE_ASP herd: OG create_herd_animals (animals_wild.c) and update_predators (herds.c).
// Markers:
//   [test-marker] asp_herd_create_ok
//   [test-marker] asp_herd_respawn_ok
//   [test-marker] asp_herd_move_ok

var __test661_ok = false

// OG formation layout 5 (herd_spawn_offsets).
var test661_spawn_offsets = [
    [0, 0], [0, -1], [1, 0], [0, 1], [-1, 0], [1, -1], [1, 1], [-1, 1],
    [-1, -1], [1, -1], [1, 1], [-1, 1], [-1, -1], [1, 0], [-1, 0], [0, 0]
]

function test661_fail(msg) {
    __log_info_native('[test:661] FAIL: ' + msg)
    __test_signal_ready()
}

function test661_unpack(packed) {
    return { x: (packed >> 16) & 0xffff, y: packed & 0xffff }
}

function test661_herd_asps(fid) {
    var out = []
    for (var i = 0; i < 16; i++) {
        var id = __test_formation_figure(fid, i)
        if (id > 0 && __figure_get_type(id) == FIGURE_ASP && __test_figure_is_alive(id)) {
            out.push(id)
        }
    }
    return out
}

function run_test() {
    __log_info_native('[test:661] asp OG herd')
    test_reload_city_session('data/default.map')
    city.remove_animals()

    var packed = __test_find_accessible_herd_tile(FIGURE_ASP)
    if (packed < 0) {
        return test661_fail('no accessible asp herd tile')
    }
    var home = test661_unpack(packed)

    // Creation: per animal one draw, then direction (& 7), then spawn wait (% 25) * 4.
    __test_random_set_state(0x1234567, 0x7654321)
    var want_waits = []
    for (var a = 0; a < 6; a++) {
        __test_random_generate_next()
        __test_random_generate_next()
        __test_random_generate_next()
        want_waits.push((__test_random_1_15bit() % 25) * 4)
    }
    __test_random_set_state(0x1234567, 0x7654321)

    var fid = __test_create_herd(home.x, home.y, FIGURE_ASP, 6)
    if (!fid) {
        return test661_fail('create_herd failed')
    }
    var asps = test661_herd_asps(fid)
    if (asps.length != 6) {
        return test661_fail('want 6 asps, got ' + asps.length)
    }
    var got_waits = []
    var got_tiles = []
    var want_tiles = []
    for (var k = 0; k < asps.length; k++) {
        if (__figure_get_action_state(asps[k]) != 24) {
            return test661_fail('asp ' + asps[k] + ' want SPAWNED 24, got ' + __figure_get_action_state(asps[k]))
        }
        got_waits.push(__test_figure_get_wait_ticks(asps[k]))
        got_tiles.push(__test_figure_tile_x(asps[k]) + ',' + __test_figure_tile_y(asps[k]))
        want_tiles.push((home.x + test661_spawn_offsets[k][0]) + ',' + (home.y + test661_spawn_offsets[k][1]))
    }
    var num_sort = function (a, b) { return a - b }
    if (got_waits.sort(num_sort).join(' ') != want_waits.sort(num_sort).join(' ')) {
        return test661_fail('spawn waits want ' + want_waits.join(' ') + ' got ' + got_waits.join(' '))
    }
    if (got_tiles.sort().join(' ') != want_tiles.sort().join(' ')) {
        return test661_fail('spawn tiles want ' + want_tiles.join(' ') + ' got ' + got_tiles.join(' '))
    }
    __log_marker('asp_herd_create_ok')

    // Respawn: a herd below max_figures spawns on the 17th update (spawn_delay 16), wait 10.
    __test_figure_kill(asps[5])
    for (var u = 0; u < 16; u++) {
        __test_herd_update(fid)
        if (test661_herd_asps(fid).length != 5) {
            return test661_fail('respawn before spawn_delay at update ' + (u + 1))
        }
    }
    __test_herd_update(fid)
    var after = test661_herd_asps(fid)
    if (after.length != 6) {
        return test661_fail('want respawn on update 17, count ' + after.length)
    }
    var fresh = 0
    for (var n = 0; n < after.length; n++) {
        if (asps.indexOf(after[n]) < 0) {
            fresh = after[n]
        }
    }
    if (__figure_get_action_state(fresh) != 24 || __test_figure_get_wait_ticks(fresh) != 10) {
        return test661_fail('respawned asp want SPAWNED wait 10, got ' + __figure_get_action_state(fresh)
            + ' wait ' + __test_figure_get_wait_ticks(fresh))
    }
    __log_marker('asp_herd_respawn_ok')

    // Full herd: destination moves on the 31st update (move_delay 30), one crt draw for the radius.
    var dest0 = __test_formation_destination(fid)
    for (var m = 0; m < 30; m++) {
        __test_herd_update(fid)
        if (__test_formation_destination(fid) != dest0) {
            return test661_fail('destination moved before move_delay at update ' + (m + 1))
        }
    }
    __test_crt_srand(777)
    __test_crt_sync_state31()
    var crt_ref = __test_crt_sync_state31()
    __test_crt_srand(777)
    __test_herd_update(fid)
    var crt_got = __test_crt_sync_state31()
    if (crt_got != crt_ref) {
        return test661_fail('herd move want exactly one crt draw')
    }
    var dest1 = __test_formation_destination(fid)
    if (dest1 == dest0) {
        return test661_fail('destination did not move on update 31')
    }
    var d1 = test661_unpack(dest1)
    var d0 = test661_unpack(dest0)
    if (Math.abs(d1.x - d0.x) > 2 || Math.abs(d1.y - d0.y) > 2) {
        return test661_fail('destination jumped beyond roam radius: ' + d0.x + ',' + d0.y + ' -> ' + d1.x + ',' + d1.y)
    }
    __log_marker('asp_herd_move_ok')

    __test661_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!__test661_ok) {
        return false
    }
    var markers = ['asp_herd_create_ok', 'asp_herd_respawn_ok', 'asp_herd_move_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:661] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    city.remove_animals()
}

// FIGURE_LION herd: OG create_herd_animals (animals_wild.c) and update_predators (herds.c) with the lion climate record
// (max_figures 4, spawn_only_when_present, spawn_delay 12, move_delay 18, roam_radius 10).
// Markers:
//   [test-marker] lion_herd_create_ok
//   [test-marker] lion_herd_respawn_ok
//   [test-marker] lion_herd_move_ok
//   [test-marker] lion_herd_empty_no_spawn_ok

var __test670_ok = false

// OG formation layout 5 (herd_spawn_offsets).
var test670_spawn_offsets = [
    [0, 0], [0, -1], [1, 0], [0, 1], [-1, 0], [1, -1], [1, 1], [-1, 1],
    [-1, -1], [1, -1], [1, 1], [-1, 1], [-1, -1], [1, 0], [-1, 0], [0, 0]
]

function test670_fail(msg) {
    __log_info_native('[test:670] FAIL: ' + msg)
    __test_signal_ready()
}

function test670_unpack(packed) {
    return { x: (packed >> 16) & 0xffff, y: packed & 0xffff }
}

function test670_herd_lions(fid) {
    var out = []
    for (var i = 0; i < 16; i++) {
        var id = __test_formation_figure(fid, i)
        if (id > 0 && __figure_get_type(id) == FIGURE_LION && __test_figure_is_alive(id)) {
            out.push(id)
        }
    }
    return out
}

function run_test() {
    __log_info_native('[test:670] lion OG herd')
    test_reload_city_session('data/default.map')
    city.remove_animals()

    var packed = __test_find_accessible_herd_tile(FIGURE_LION)
    if (packed < 0) {
        return test670_fail('no accessible lion herd tile')
    }
    var home = test670_unpack(packed)

    // Creation: per animal one draw, then direction (& 7), then spawn wait (% 25) * 4.
    __test_random_set_state(0x1234567, 0x7654321)
    var want_waits = []
    for (var a = 0; a < 4; a++) {
        __test_random_generate_next()
        __test_random_generate_next()
        __test_random_generate_next()
        want_waits.push((__test_random_1_15bit() % 25) * 4)
    }
    __test_random_set_state(0x1234567, 0x7654321)

    var fid = __test_create_herd(home.x, home.y, FIGURE_LION, 4)
    if (!fid) {
        return test670_fail('create_herd failed')
    }
    var lions = test670_herd_lions(fid)
    if (lions.length != 4) {
        return test670_fail('want 4 lions, got ' + lions.length)
    }
    var got_waits = []
    var got_tiles = []
    var want_tiles = []
    for (var k = 0; k < lions.length; k++) {
        if (__figure_get_action_state(lions[k]) != 24) {
            return test670_fail('lion ' + lions[k] + ' want SPAWNED 24, got ' + __figure_get_action_state(lions[k]))
        }
        got_waits.push(__test_figure_get_wait_ticks(lions[k]))
        got_tiles.push(__test_figure_tile_x(lions[k]) + ',' + __test_figure_tile_y(lions[k]))
        want_tiles.push((home.x + test670_spawn_offsets[k][0]) + ',' + (home.y + test670_spawn_offsets[k][1]))
    }
    var num_sort = function (a, b) { return a - b }
    if (got_waits.sort(num_sort).join(' ') != want_waits.sort(num_sort).join(' ')) {
        return test670_fail('spawn waits want ' + want_waits.join(' ') + ' got ' + got_waits.join(' '))
    }
    if (got_tiles.sort().join(' ') != want_tiles.sort().join(' ')) {
        return test670_fail('spawn tiles want ' + want_tiles.join(' ') + ' got ' + got_tiles.join(' '))
    }
    __log_marker('lion_herd_create_ok')

    // Respawn: a herd below max_figures spawns on the 13th update (spawn_delay 12), wait 10.
    __test_figure_kill(lions[3])
    for (var u = 0; u < 12; u++) {
        __test_herd_update(fid)
        if (test670_herd_lions(fid).length != 3) {
            return test670_fail('respawn before spawn_delay at update ' + (u + 1))
        }
    }
    __test_herd_update(fid)
    var after = test670_herd_lions(fid)
    if (after.length != 4) {
        return test670_fail('want respawn on update 13, count ' + after.length)
    }
    var fresh = 0
    for (var n = 0; n < after.length; n++) {
        if (lions.indexOf(after[n]) < 0) {
            fresh = after[n]
        }
    }
    if (__figure_get_action_state(fresh) != 24 || __test_figure_get_wait_ticks(fresh) != 10) {
        return test670_fail('respawned lion want SPAWNED wait 10, got ' + __figure_get_action_state(fresh)
            + ' wait ' + __test_figure_get_wait_ticks(fresh))
    }
    __log_marker('lion_herd_respawn_ok')

    // Full herd: destination moves on the 19th update (move_delay 18), radius 5 + crt % 5, one crt draw.
    var dest0 = __test_formation_destination(fid)
    for (var m = 0; m < 18; m++) {
        __test_herd_update(fid)
        if (__test_formation_destination(fid) != dest0) {
            return test670_fail('destination moved before move_delay at update ' + (m + 1))
        }
    }
    __test_crt_srand(777)
    __test_crt_sync_state31()
    var crt_ref = __test_crt_sync_state31()
    __test_crt_srand(777)
    __test_herd_update(fid)
    var crt_got = __test_crt_sync_state31()
    if (crt_got != crt_ref) {
        return test670_fail('herd move want exactly one crt draw')
    }
    var dest1 = __test_formation_destination(fid)
    if (dest1 == dest0) {
        return test670_fail('destination did not move on update 19')
    }
    var d1 = test670_unpack(dest1)
    var d0 = test670_unpack(dest0)
    if (Math.abs(d1.x - d0.x) > 9 || Math.abs(d1.y - d0.y) > 9) {
        return test670_fail('destination jumped beyond roam radius: ' + d0.x + ',' + d0.y + ' -> ' + d1.x + ',' + d1.y)
    }
    __log_marker('lion_herd_move_ok')

    // spawn_only_when_present: an emptied lion herd never respawns.
    var all = test670_herd_lions(fid)
    for (var z = 0; z < all.length; z++) {
        __test_figure_kill(all[z])
    }
    for (var e = 0; e < 40; e++) {
        __test_herd_update(fid)
    }
    if (test670_herd_lions(fid).length != 0) {
        return test670_fail('empty lion herd respawned ' + test670_herd_lions(fid).length)
    }
    __log_marker('lion_herd_empty_no_spawn_ok')

    __test670_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!__test670_ok) {
        return false
    }
    var markers = ['lion_herd_create_ok', 'lion_herd_respawn_ok', 'lion_herd_move_ok', 'lion_herd_empty_no_spawn_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:670] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    city.remove_animals()
}

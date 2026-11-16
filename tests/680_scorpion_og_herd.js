// FIGURE_SCORPION herd: OG create_herd_animals (animals_wild.c) and update_predators (herds.c) with the scorpion climate record
// (max_figures 2, spawn_delay 20, move_delay 20, roam_radius 7, spawns into an empty herd).
// Markers:
//   [test-marker] scorpion_herd_create_ok
//   [test-marker] scorpion_herd_respawn_ok
//   [test-marker] scorpion_herd_move_ok
//   [test-marker] scorpion_herd_empty_respawn_ok

var __test680_ok = false

// OG formation layout 5 (herd_spawn_offsets).
var test680_spawn_offsets = [
    [0, 0], [0, -1], [1, 0], [0, 1], [-1, 0], [1, -1], [1, 1], [-1, 1],
    [-1, -1], [1, -1], [1, 1], [-1, 1], [-1, -1], [1, 0], [-1, 0], [0, 0]
]

function test680_fail(msg) {
    __log_info_native('[test:680] FAIL: ' + msg)
    __test_signal_ready()
}

function test680_unpack(packed) {
    return { x: (packed >> 16) & 0xffff, y: packed & 0xffff }
}

function test680_herd_scorpions(fid) {
    var out = []
    for (var i = 0; i < 16; i++) {
        var id = __test_formation_figure(fid, i)
        if (id > 0 && __figure_get_type(id) == FIGURE_SCORPION && __test_figure_is_alive(id)) {
            out.push(id)
        }
    }
    return out
}

function run_test() {
    __log_info_native('[test:680] scorpion OG herd')
    test_reload_city_session('data/default.map')
    city.remove_animals()

    var packed = __test_find_accessible_herd_tile(FIGURE_SCORPION)
    if (packed < 0) {
        return test680_fail('no accessible scorpion herd tile')
    }
    var home = test680_unpack(packed)

    // Creation: per animal one draw, then direction (& 7), then spawn wait (% 25) * 4.
    __test_random_set_state(0x1234567, 0x7654321)
    var want_waits = []
    for (var a = 0; a < 2; a++) {
        __test_random_generate_next()
        __test_random_generate_next()
        __test_random_generate_next()
        want_waits.push((__test_random_1_15bit() % 25) * 4)
    }
    __test_random_set_state(0x1234567, 0x7654321)

    var fid = __test_create_herd(home.x, home.y, FIGURE_SCORPION, 2)
    if (!fid) {
        return test680_fail('create_herd failed')
    }
    var scorpions = test680_herd_scorpions(fid)
    if (scorpions.length != 2) {
        return test680_fail('want 2 scorpions, got ' + scorpions.length)
    }
    var got_waits = []
    var got_tiles = []
    var want_tiles = []
    for (var k = 0; k < scorpions.length; k++) {
        if (__figure_get_action_state(scorpions[k]) != 24) {
            return test680_fail('scorpion ' + scorpions[k] + ' want SPAWNED 24, got ' + __figure_get_action_state(scorpions[k]))
        }
        got_waits.push(__test_figure_get_wait_ticks(scorpions[k]))
        got_tiles.push(__test_figure_tile_x(scorpions[k]) + ',' + __test_figure_tile_y(scorpions[k]))
        want_tiles.push((home.x + test680_spawn_offsets[k][0]) + ',' + (home.y + test680_spawn_offsets[k][1]))
    }
    var num_sort = function (a, b) { return a - b }
    if (got_waits.sort(num_sort).join(' ') != want_waits.sort(num_sort).join(' ')) {
        return test680_fail('spawn waits want ' + want_waits.join(' ') + ' got ' + got_waits.join(' '))
    }
    if (got_tiles.sort().join(' ') != want_tiles.sort().join(' ')) {
        return test680_fail('spawn tiles want ' + want_tiles.join(' ') + ' got ' + got_tiles.join(' '))
    }
    __log_marker('scorpion_herd_create_ok')

    // Respawn: a herd below max_figures spawns on the 21st update (spawn_delay 20), wait 10.
    __test_figure_kill(scorpions[1])
    for (var u = 0; u < 20; u++) {
        __test_herd_update(fid)
        if (test680_herd_scorpions(fid).length != 1) {
            return test680_fail('respawn before spawn_delay at update ' + (u + 1))
        }
    }
    __test_herd_update(fid)
    var after = test680_herd_scorpions(fid)
    if (after.length != 2) {
        return test680_fail('want respawn on update 21, count ' + after.length)
    }
    var fresh = 0
    for (var n = 0; n < after.length; n++) {
        if (scorpions.indexOf(after[n]) < 0) {
            fresh = after[n]
        }
    }
    if (__figure_get_action_state(fresh) != 24 || __test_figure_get_wait_ticks(fresh) != 10) {
        return test680_fail('respawned scorpion want SPAWNED wait 10, got ' + __figure_get_action_state(fresh)
            + ' wait ' + __test_figure_get_wait_ticks(fresh))
    }
    __log_marker('scorpion_herd_respawn_ok')

    // Full herd: destination moves on the 21st update (move_delay 20), radius 3 + crt % 3, one crt draw.
    var dest0 = __test_formation_destination(fid)
    for (var m = 0; m < 20; m++) {
        __test_herd_update(fid)
        if (__test_formation_destination(fid) != dest0) {
            return test680_fail('destination moved before move_delay at update ' + (m + 1))
        }
    }
    __test_crt_srand(777)
    __test_crt_sync_state31()
    var crt_ref = __test_crt_sync_state31()
    __test_crt_srand(777)
    __test_herd_update(fid)
    var crt_got = __test_crt_sync_state31()
    if (crt_got != crt_ref) {
        return test680_fail('herd move want exactly one crt draw')
    }
    var dest1 = __test_formation_destination(fid)
    if (dest1 == dest0) {
        return test680_fail('destination did not move on update 21')
    }
    var d1 = test680_unpack(dest1)
    var d0 = test680_unpack(dest0)
    if (Math.abs(d1.x - d0.x) > 5 || Math.abs(d1.y - d0.y) > 5) {
        return test680_fail('destination jumped beyond roam radius: ' + d0.x + ',' + d0.y + ' -> ' + d1.x + ',' + d1.y)
    }
    __log_marker('scorpion_herd_move_ok')

    // No spawn_only_when_present: an emptied scorpion herd spawns again after spawn_delay.
    var all = test680_herd_scorpions(fid)
    for (var z = 0; z < all.length; z++) {
        __test_figure_kill(all[z])
    }
    for (var e = 0; e < 21; e++) {
        __test_herd_update(fid)
    }
    if (test680_herd_scorpions(fid).length != 1) {
        return test680_fail('empty scorpion herd want 1 respawn, got ' + test680_herd_scorpions(fid).length)
    }
    __log_marker('scorpion_herd_empty_respawn_ok')

    __test680_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!__test680_ok) {
        return false
    }
    var markers = ['scorpion_herd_create_ok', 'scorpion_herd_respawn_ok', 'scorpion_herd_move_ok', 'scorpion_herd_empty_respawn_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:680] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    city.remove_animals()
}

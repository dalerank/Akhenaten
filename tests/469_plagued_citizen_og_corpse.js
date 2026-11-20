// Plagued citizen corpse vs OG figure/plagues.c:89-93: the carrier's action has no corpse branch, so a killed
// carrier keeps lying on its tile and draws death frame figure_corpse_offsets[wait_ticks / 2] (figure_data.c:100),
// which does not change while it lies there. gameplay_change_plagued_citizen_remake restores the remake corpse
// that plays the death strip and is removed after corpse_time_delay.
// Markers:
//   [test-marker] plagued652_corpse_stays_ok
//   [test-marker] plagued652_corpse_frame_ok
//   [test-marker] plagued652_remake_corpse_fades_ok

var t469_remake_prev = false

function t469_fail(msg) {
    __log_info_native('[test:469] FAIL: ' + msg)
}

function t469_state(fid) {
    var f = city.get_figure(fid)
    return (f && __figure_is_valid(fid)) ? f.state : FIGURE_STATE_NONE
}

function t469_corpse(t) {
    var fid = test_figure_create(FIGURE_PLAGUED_CITIZEN, t.x, t.y)
    if (!fid) {
        return 0
    }
    __test_figure_kill(fid)
    return fid
}

function t469_tick(fid, n) {
    for (var i = 0; i < n && t469_state(fid) == FIGURE_STATE_DYING; i++) {
        __test_figure_action_perform_dying(fid)
    }
}

function run_test() {
    __log_info_native('[test:469] OG plagued citizen corpse')
    test_reload_city_session('data/default.map')
    game.paused = true
    t469_remake_prev = game_features.get('gameplay_change_plagued_citizen_remake') === true
    game_features.set('gameplay_change_plagued_citizen_remake', false)
    city.figures.remove_figures(FIGURE_PLAGUED_CITIZEN)

    var t = test_find_buildable_tile(BUILDING_HOUSE_CRUDE_HUT)
    var fid = t ? t469_corpse(t) : 0
    if (!fid || t469_state(fid) != FIGURE_STATE_DYING) {
        t469_fail('corpse create: fid=' + fid + ' state=' + t469_state(fid))
        __test_signal_ready()
        return
    }
    t469_tick(fid, 400)
    var f = city.get_figure(fid)
    if (t469_state(fid) != FIGURE_STATE_DYING || f.wait_ticks != 0 || __test_figure_death_frame(fid) != 0) {
        t469_fail('after 400 ticks state=' + t469_state(fid) + ' wait=' + (f ? f.wait_ticks : -1)
            + ' frame=' + __test_figure_death_frame(fid))
        __test_signal_ready()
        return
    }
    __log_marker('plagued652_corpse_stays_ok')

    // wait_ticks -> figure_corpse_offsets[wait_ticks / 2]
    var cases = [[20, 4], [40, 5], [100, 6], [200, 7], [258, 1], [300, 0], [500, 0]]
    for (var i = 0; i < cases.length; i++) {
        f.wait_ticks = cases[i][0]
        t469_tick(fid, 3)
        var frame = __test_figure_death_frame(fid)
        if (frame != cases[i][1] || f.wait_ticks != cases[i][0]) {
            t469_fail('wait_ticks ' + cases[i][0] + ' frame ' + frame + ' want ' + cases[i][1] + ' wait now ' + f.wait_ticks)
            __test_signal_ready()
            return
        }
    }
    __log_marker('plagued652_corpse_frame_ok')

    game_features.set('gameplay_change_plagued_citizen_remake', true)
    var remake = t469_corpse({ x: t.x + 1, y: t.y })
    t469_tick(remake, 400)
    game_features.set('gameplay_change_plagued_citizen_remake', t469_remake_prev)
    if (t469_state(remake) == FIGURE_STATE_DYING) {
        t469_fail('remake corpse still lying after 400 ticks')
        __test_signal_ready()
        return
    }
    __log_marker('plagued652_remake_corpse_fades_ok')
    __test_signal_ready()
}

function check_valid() {
    var markers = ['plagued652_corpse_stays_ok', 'plagued652_corpse_frame_ok', 'plagued652_remake_corpse_fades_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:469] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    game_features.set('gameplay_change_plagued_citizen_remake', t469_remake_prev)
    city.figures.remove_figures(FIGURE_PLAGUED_CITIZEN)
}

// C10 RT4: finished Small royal tomb is a burial target —
// robber steal + funeral spawn (city-level BP1).

var ACTION_TOMB_ROBBER_CREATED = 120
var ACTION_TOMB_ROBBER_GOING = 121
var ACTION_TOMB_ROBBER_CAUGHT = 124

function place_finished_small_royal() {
    if (!__scenario_building_allowed(BUILDING_SMALL_ROYAL_TOMB)) {
        __scenario_building_allow(BUILDING_SMALL_ROYAL_TOMB, true)
    }
    var cx = 40
    var cy = 40
    for (var dy = 0; dy < 20; dy++) {
        for (var dx = 0; dx < 11; dx++) {
            terrain.add({ x: cx + dx, y: cy + dy }, TERRAIN_ELEVATION)
        }
    }
    var bid = test_building_place(BUILDING_SMALL_ROYAL_TOMB, cx, cy)
    if (!bid) {
        return 0
    }
    var mon = city.get_monument(bid)
    if (!mon) {
        return 0
    }
    var total = mon.phases_total()
    __test_monument_set_phase(bid, total)
    var ph = __test_monument_phase(bid)
    if (ph != 255 && ph != -1) {
        return 0
    }
    return bid
}

function kill_tomb_robbers() {
    for (var i = 1; i < 2000; i++) {
        if (__figure_is_valid(i) && __figure_get_type(i) == FIGURE_TOMB_ROBER) {
            __test_figure_set_action(i, ACTION_TOMB_ROBBER_CAUGHT)
            __test_figure_action_perform(i)
        }
    }
}

function kill_funerals() {
    for (var i = 1; i < 2000; i++) {
        if (__figure_is_valid(i) && __figure_get_type(i) == FIGURE_FUNERAL_WALKER) {
            __test_figure_kill(i)
        }
    }
}

function run_test() {
    __log_info_native('[test:152] royal tomb burial + robber + funeral')
    test_reload_city_session('data/default.map')
    __test_set_treasury(500000)
    __test_burial_provisions_clear()
    __test_sentiment_set(10)

    var bid = place_finished_small_royal()
    if (!bid) {
        __log_info_native('[test:152] place/finish small royal failed')
        __test_signal_ready()
        return
    }
    __log_marker('rt_burial_tomb_ok:' + bid)

    if (!__test_burial_provisions_set(RESOURCE_LINEN, 4)) {
        __log_info_native('[test:152] burial set failed')
        __test_signal_ready()
        return
    }
    __test_burial_provisions_force_dispatched(RESOURCE_LINEN, 4)

    // Robber targets finished royal tomb.
    var fid = __test_tomb_robber_try_spawn(1)
    if (!fid || !__figure_is_valid(fid)) {
        __log_info_native('[test:152] try_spawn failed with royal+provisions')
        __test_signal_ready()
        return
    }
    __test_figure_set_action(fid, ACTION_TOMB_ROBBER_CREATED)
    __test_figure_action_perform(fid)
    if (__figure_get_destination_building_id(fid) != bid) {
        __log_info_native('[test:152] robber dest want ' + bid
            + ' got ' + __figure_get_destination_building_id(fid))
        __test_signal_ready()
        return
    }
    if (__figure_get_action_state(fid) != ACTION_TOMB_ROBBER_GOING) {
        __log_info_native('[test:152] robber want GOING got ' + __figure_get_action_state(fid))
        __test_signal_ready()
        return
    }
    __log_marker('rt_burial_robber_goto_ok')

    __test_kingdom_set_rating(50)
    var before_disp = __scenario_burial_provisions_dispatched(RESOURCE_LINEN)
    var before_kingdom = __test_kingdom_rating()
    if (!__test_tomb_robber_commit_plunder(fid)) {
        __log_info_native('[test:152] commit_plunder failed')
        __test_signal_ready()
        return
    }
    if (__scenario_burial_provisions_dispatched(RESOURCE_LINEN) != before_disp - 1) {
        __log_info_native('[test:152] steal dispatched want ' + (before_disp - 1)
            + ' got ' + __scenario_burial_provisions_dispatched(RESOURCE_LINEN))
        __test_signal_ready()
        return
    }
    if (__test_kingdom_rating() != before_kingdom - 10) {
        __log_info_native('[test:152] steal kingdom want -10')
        __test_signal_ready()
        return
    }
    __log_marker('rt_burial_robber_steal_ok')

    kill_tomb_robbers()

    // Funeral: re-complete provisions, spawn toward royal tomb.
    __test_burial_provisions_force_dispatched(RESOURCE_LINEN, 4)
    __test_monument_set_funeral_done(bid, 0)
    kill_funerals()

    var ffid = __test_funeral_try_spawn(1)
    if (!ffid) {
        __log_info_native('[test:152] funeral try_spawn failed')
        __test_signal_ready()
        return
    }
    __test_figure_set_action(ffid, ACTION_0_FUNERAL_CREATED)
    __test_figure_action_perform(ffid)
    if (__test_funeral_target_tomb(ffid) != bid
            && __figure_get_destination_building_id(ffid) != bid) {
        __log_info_native('[test:152] funeral target want ' + bid
            + ' runtime=' + __test_funeral_target_tomb(ffid)
            + ' dest=' + __figure_get_destination_building_id(ffid))
        __test_signal_ready()
        return
    }
    __log_marker('rt_burial_funeral_ok')
    __log_marker('rt_burial_loop_ok')
    __test_signal_ready()
}

function check_valid() {
    var required = [
        'rt_burial_tomb_ok',
        'rt_burial_robber_goto_ok',
        'rt_burial_robber_steal_ok',
        'rt_burial_funeral_ok',
        'rt_burial_loop_ok'
    ]
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + required[i])
            && !__test_find_inlog(required[i])) {
            __log_info_native('[test:152] missing marker ' + required[i])
            return false
        }
    }
    return true
}

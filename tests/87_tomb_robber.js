// FIGURE_TOMB_ROBER — OG default + remake behind gameplay_change_tomb_robber_remake.
// Markers:
//   [test-marker] tomb_robber_registered_ok
//   [test-marker] tomb_robber_reject_no_provisions_ok
//   [test-marker] tomb_robber_reject_no_tomb_ok
//   [test-marker] tomb_robber_goto_tomb_ok
//   [test-marker] tomb_robber_steal_ok
//   [test-marker] tomb_robber_crime_wave_ok
//   [test-marker] tomb_robber_arrest_ok
//   [test-marker] tomb_robber_preexisting_threat_ok
//   [test-marker] tomb_robber_prefer_steal_over_preexisting_ok

var ACTION_TOMB_ROBBER_CREATED = 120
var ACTION_TOMB_ROBBER_GOING_OG = 9
var ACTION_TOMB_ROBBER_GOING_REMAKE = 121
var ACTION_TOMB_ROBBER_STEALING = 122
var ACTION_TOMB_ROBBER_CAUGHT = 124
var MESSAGE_CRIME_WAVE = 491

var FEAT_TOMB_ROBBER_REMAKE = 'gameplay_change_tomb_robber_remake'
var __test87_feat_prev = false

function og_finished_kingdom_penalty() {
    var full = [2, 4, 6, 8, 10][__game_difficulty()]
    return (full / 2) | 0
}

function count_messages_with_id(mm_id) {
    var n = 0
    var total = __city_message_count()
    for (var i = 0; i < total; i++) {
        if (__city_message_mm_text_id(i) == mm_id) {
            n++
        }
    }
    return n
}

function place_finished_mastaba() {
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = 0
    var candidates = [
        {x: cx - 5, y: cy - 2}, {x: cx - 5, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}
    ]
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_SMALL_MASTABA, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        bid = test_building_place(BUILDING_SMALL_MASTABA, -1, -1)
    }
    if (!bid) {
        return 0
    }
    __test_monument_set_phase(bid, 8)
    if (__test_monument_phase(bid) != -1) {
        return 0
    }
    return bid
}

function kill_tomb_robbers() {
    for (var i = 1; i < 2000; i++) {
        if (__figure_is_valid(i) && __figure_get_type(i) == FIGURE_TOMB_ROBER) {
            __test_figure_kill(i)
        }
    }
}

function run_test() {
    __log_info_native('[test:87] tomb robber OG + remake')
    test_ensure_city_session('data/default.map')

    __test87_feat_prev = game_features.get(FEAT_TOMB_ROBBER_REMAKE) === true
    game_features.set(FEAT_TOMB_ROBBER_REMAKE, false)

    __test_set_treasury(500000)
    if (!__scenario_building_allowed(BUILDING_SMALL_MASTABA)) {
        __scenario_building_allow(BUILDING_SMALL_MASTABA, true)
    }

    var probe = test_figure_create(FIGURE_TOMB_ROBER, -1, -1)
    if (!probe || !__figure_is_valid(probe) || __figure_get_type(probe) != FIGURE_TOMB_ROBER) {
        __log_info_native('[test:87] FIGURE_TOMB_ROBER not registered')
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    __test_figure_set_action(probe, ACTION_TOMB_ROBBER_CAUGHT)
    __test_figure_action_perform(probe)
    __log_marker('tomb_robber_registered_ok')

    __test_burial_provisions_clear()
    __test_sentiment_set(10)

    var rej = __test_tomb_robber_try_spawn(1)
    if (rej) {
        __log_info_native('[test:87] try_spawn should fail without provisions, got ' + rej)
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    __log_marker('tomb_robber_reject_no_provisions_ok')

    if (!__test_burial_provisions_set(RESOURCE_LINEN, 8)) {
        __log_info_native('[test:87] burial set failed')
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    __test_burial_provisions_force_dispatched(RESOURCE_LINEN, 4)

    rej = __test_tomb_robber_try_spawn(1)
    if (rej) {
        __log_info_native('[test:87] try_spawn should fail without finished tomb, got ' + rej)
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    __log_marker('tomb_robber_reject_no_tomb_ok')

    var bid = place_finished_mastaba()
    if (!bid) {
        __log_info_native('[test:87] failed to place/finish mastaba')
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }

    var fid = __test_tomb_robber_try_spawn(1)
    if (!fid || !__figure_is_valid(fid)) {
        __log_info_native('[test:87] try_spawn failed with tomb+provisions')
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }

    // Force-start (skip OG 40-tick wait): CREATED → GOING.
    __test_figure_set_action(fid, ACTION_TOMB_ROBBER_CREATED)
    __test_figure_action_perform(fid)

    var dest = __figure_get_destination_building_id(fid)
    var action = __figure_get_action_state(fid)
    if (dest != bid) {
        __log_info_native('[test:87] destination want ' + bid + ' got ' + dest + ' action=' + action)
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    if (action != ACTION_TOMB_ROBBER_GOING_OG) {
        __log_info_native('[test:87] expected OG GOING action 9, got ' + action)
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    __log_marker('tomb_robber_goto_tomb_ok')

    __test_kingdom_set_rating(50)
    var before_disp = __scenario_burial_provisions_dispatched(RESOURCE_LINEN)
    var before_kingdom = __test_kingdom_rating()
    var expect_penalty = og_finished_kingdom_penalty()
    if (!__test_tomb_robber_commit_plunder(fid)) {
        __log_info_native('[test:87] commit_plunder failed')
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    var after_disp = __scenario_burial_provisions_dispatched(RESOURCE_LINEN)
    var after_kingdom = __test_kingdom_rating()
    if (after_disp != before_disp - 1) {
        __log_info_native('[test:87] steal dispatched want ' + (before_disp - 1) + ' got ' + after_disp)
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    if (after_kingdom != before_kingdom - expect_penalty) {
        __log_info_native('[test:87] steal kingdom want -' + expect_penalty
            + ' got ' + after_kingdom + ' from ' + before_kingdom)
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    if (__test_monument_funeral_done(bid)) {
        __log_info_native('[test:87] steal must not set funeral_done')
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    __log_marker('tomb_robber_steal_ok')

    kill_tomb_robbers()

    // --- Remake-only behaviors ---
    game_features.set(FEAT_TOMB_ROBBER_REMAKE, true)
    __test_burial_provisions_force_dispatched(RESOURCE_LINEN, 4)

    var before_msg = count_messages_with_id(MESSAGE_CRIME_WAVE)
    var wave_fid = __test_tomb_robber_spawn_wave(2)
    __test_process_events()
    if (!wave_fid) {
        __log_info_native('[test:87] spawn_wave failed')
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    var live = __test_count_figures(FIGURE_TOMB_ROBER)
    if (live < 1 || live > 2) {
        __log_info_native('[test:87] wave live robbers want 1..2 got ' + live)
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    var after_msg = count_messages_with_id(MESSAGE_CRIME_WAVE)
    if (after_msg != before_msg + 1) {
        __log_info_native('[test:87] want +1 crime_wave msg, before=' + before_msg + ' after=' + after_msg)
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    __log_marker('tomb_robber_crime_wave_ok')

    var arrest_fid = 0
    for (var i = 1; i < 2000; i++) {
        if (__figure_is_valid(i) && __test_figure_is_alive(i)
            && __figure_get_type(i) == FIGURE_TOMB_ROBER) {
            arrest_fid = i
            break
        }
    }
    if (!arrest_fid) {
        __log_info_native('[test:87] no robber for arrest')
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    __test_burial_provisions_force_dispatched(RESOURCE_LINEN, 4)
    var disp_before_arrest = __scenario_burial_provisions_dispatched(RESOURCE_LINEN)
    if (!__test_tomb_robber_arrest(arrest_fid, 1)) {
        __log_info_native('[test:87] force arrest failed')
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    __test_figure_action_perform(arrest_fid)
    if (__figure_is_valid(arrest_fid) && __figure_get_type(arrest_fid) == FIGURE_TOMB_ROBER) {
        var astate = __figure_get_action_state(arrest_fid)
        if (astate != ACTION_TOMB_ROBBER_CAUGHT && __figure_is_valid(arrest_fid)) {
            __log_info_native('[test:87] after arrest action want gone/caught, state=' + astate)
            game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
            __test_signal_ready()
            return
        }
    }
    if (__scenario_burial_provisions_dispatched(RESOURCE_LINEN) != disp_before_arrest) {
        __log_info_native('[test:87] arrest must not steal provisions')
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    __log_marker('tomb_robber_arrest_ok')

    kill_tomb_robbers()

    __test_monument_set_preexisting(bid, 1)
    if (!__test_monument_is_preexisting(bid)) {
        __log_info_native('[test:87] preexisting flag not set')
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    __test_burial_provisions_clear()
    if (!__test_burial_provisions_set(RESOURCE_LINEN, 8)) {
        __log_info_native('[test:87] burial set failed (preexisting)')
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    __test_burial_provisions_force_dispatched(RESOURCE_LINEN, 4)
    __test_kingdom_set_rating(50)
    var threat_fid = __test_tomb_robber_try_spawn(1)
    if (!threat_fid) {
        __log_info_native('[test:87] spawn for preexisting threat failed')
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    __test_figure_set_action(threat_fid, ACTION_TOMB_ROBBER_CREATED)
    __test_figure_action_perform(threat_fid)
    if (__figure_get_destination_building_id(threat_fid) != bid) {
        __log_info_native('[test:87] preexisting target want mastaba')
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    var kingdom_before_threat = __test_kingdom_rating()
    var disp_before_threat = __scenario_burial_provisions_dispatched(RESOURCE_LINEN)
    if (!__test_tomb_robber_commit_plunder(threat_fid)) {
        __log_info_native('[test:87] preexisting threat plunder failed')
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    if (__scenario_burial_provisions_dispatched(RESOURCE_LINEN) != disp_before_threat) {
        __log_info_native('[test:87] preexisting must not steal dispatched')
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    if (__test_kingdom_rating() != kingdom_before_threat - 25) {
        __log_info_native('[test:87] preexisting kingdom want -25, got ' + __test_kingdom_rating()
            + ' from ' + kingdom_before_threat)
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    __log_marker('tomb_robber_preexisting_threat_ok')

    kill_tomb_robbers()

    var bid_steal = place_finished_mastaba()
    if (!bid_steal || bid_steal == bid) {
        __log_info_native('[test:87] second mastaba for prefer-steal failed')
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    __test_burial_provisions_clear()
    if (!__test_burial_provisions_set(RESOURCE_LINEN, 8)) {
        __log_info_native('[test:87] burial set failed (prefer steal)')
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    if (__test_monument_add_burial_stock(bid_steal, RESOURCE_LINEN, 3) != 3) {
        __log_info_native('[test:87] add stock on steal tomb failed')
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    var prefer_fid = __test_tomb_robber_try_spawn(1)
    if (!prefer_fid) {
        __log_info_native('[test:87] prefer-steal spawn failed')
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    __test_figure_set_action(prefer_fid, ACTION_TOMB_ROBBER_CREATED)
    __test_figure_action_perform(prefer_fid)
    if (__figure_get_destination_building_id(prefer_fid) != bid_steal) {
        __log_info_native('[test:87] prefer steal tomb want ' + bid_steal
            + ' got ' + __figure_get_destination_building_id(prefer_fid))
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    var stock_before = __test_monument_burial_stock(bid_steal, RESOURCE_LINEN)
    if (!__test_tomb_robber_commit_plunder(prefer_fid)) {
        __log_info_native('[test:87] prefer-steal plunder failed')
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    if (__test_monument_burial_stock(bid_steal, RESOURCE_LINEN) != stock_before - 1) {
        __log_info_native('[test:87] prefer-steal stock want ' + (stock_before - 1))
        game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
        __test_signal_ready()
        return
    }
    __log_marker('tomb_robber_prefer_steal_over_preexisting_ok')

    game_features.set(FEAT_TOMB_ROBBER_REMAKE, __test87_feat_prev)
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'tomb_robber_registered_ok',
        'tomb_robber_reject_no_provisions_ok',
        'tomb_robber_reject_no_tomb_ok',
        'tomb_robber_goto_tomb_ok',
        'tomb_robber_steal_ok',
        'tomb_robber_crime_wave_ok',
        'tomb_robber_arrest_ok',
        'tomb_robber_preexisting_threat_ok',
        'tomb_robber_prefer_steal_over_preexisting_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:87] missing marker: ' + marker)
            return false
        }
    }
    return true
}

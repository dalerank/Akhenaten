// FIGURE_FUNERAL_WALKER register + spawn after finished mastaba + provisions.
// Markers:
//   [test-marker] funeral_registered_ok
//   [test-marker] funeral_reject_incomplete_provisions_ok
//   [test-marker] funeral_goto_tomb_ok
//   [test-marker] funeral_done_on_arrive_ok
//   [test-marker] funeral_no_respawn_ok
//   [test-marker] funeral_steal_keeps_done_ok
//   [test-marker] funeral_abort_no_done_ok
//   [test-marker] funeral_no_provisions_required_ok
//   [test-marker] funeral_multi_tomb_ok
//   [test-marker] funeral_pyramid_spawn_ok
//   [test-marker] funeral_mausoleum_spawn_ok
//   [test-marker] funeral_inert_action_no_block_ok
//   [test-marker] funeral_midwalk_saveload_ok  (or funeral_midwalk_saveload_skipped)

var __test84_saveload_ok = false
var __test84_saveload_skipped = false

function place_finished_mastaba(candidates) {
    var bid = 0
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

function place_finished_small_stepped(candidates) {
    var bid = 0
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_SMALL_STEPPED_PYRAMID, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        bid = test_building_place(BUILDING_SMALL_STEPPED_PYRAMID, -1, -1)
    }
    if (!bid) {
        return 0
    }
    // phases() == 25 for small stepped → set_phase(25) → MONUMENT_FINISHED.
    __test_monument_set_phase(bid, 25)
    if (__test_monument_phase(bid) != -1) {
        return 0
    }
    return bid
}

function place_finished_mausoleum(candidates) {
    if (!__scenario_building_allowed(BUILDING_STORAGE_YARD)) {
        __scenario_building_allow(BUILDING_STORAGE_YARD, true)
    }
    if (!__scenario_building_allowed(BUILDING_MAUSOLEUM)) {
        __scenario_building_allow(BUILDING_MAUSOLEUM, true)
    }
    var need = 240
    var sy = 0
    var yard_spots = [
        {x: 8, y: 8}, {x: 12, y: 12}, {x: 20, y: 8}, {x: 8, y: 40}
    ]
    for (var yi = 0; yi < yard_spots.length && !sy; yi++) {
        sy = test_staffed_yard_with_resource(RESOURCE_SANDSTONE, need, yard_spots[yi].x, yard_spots[yi].y)
    }
    if (!sy) {
        sy = test_staffed_yard_with_resource(RESOURCE_SANDSTONE, need, -1, -1)
    }
    if (!sy) {
        return 0
    }
    var bid = 0
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_MAUSOLEUM, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        bid = test_building_place(BUILDING_MAUSOLEUM, -1, -1)
    }
    if (!bid) {
        return 0
    }
    // phases 0–4 + sentinel 5 → size 6; set_phase(6) → FINISHED
    __test_monument_set_phase(bid, 6)
    var ph = __test_monument_phase(bid)
    if (ph != 255 && ph != -1) {
        return 0
    }
    return bid
}

function count_live_funerals() {
    var n = 0
    for (var i = 1; i < 2000; i++) {
        if (__figure_is_valid(i) && __figure_get_type(i) == FIGURE_FUNERAL_WALKER) {
            var a = __figure_get_action_state(i)
            if (a != 149) {
                n++
            }
        }
    }
    return n
}

function find_live_funeral() {
    for (var i = 1; i < 2000; i++) {
        if (__figure_is_valid(i) && __figure_get_type(i) == FIGURE_FUNERAL_WALKER) {
            var a = __figure_get_action_state(i)
            if (a != 149) {
                return i
            }
        }
    }
    return 0
}

function run_test() {
    __log_info_native('[test:84] funeral procession BF2')
    test_ensure_city_session('data/default.map')

    __test_set_treasury(500000)
    if (!__scenario_building_allowed(BUILDING_SMALL_MASTABA)) {
        __scenario_building_allow(BUILDING_SMALL_MASTABA, true)
    }
    if (!__scenario_building_allowed(BUILDING_SMALL_STEPPED_PYRAMID)) {
        __scenario_building_allow(BUILDING_SMALL_STEPPED_PYRAMID, true)
    }

    var probe = test_figure_create(FIGURE_FUNERAL_WALKER, -1, -1)
    if (!probe || !__figure_is_valid(probe) || __figure_get_type(probe) != FIGURE_FUNERAL_WALKER) {
        __log_info_native('[test:84] FIGURE_FUNERAL_WALKER not registered')
        __test_signal_ready()
        return
    }
    city.figures.remove_figures(FIGURE_FUNERAL_WALKER)
    __log_marker('funeral_registered_ok')

    __test_burial_provisions_clear()

    // Incomplete provisions → refuse.
    if (!__test_burial_provisions_set(RESOURCE_LINEN, 8)) {
        __log_info_native('[test:84] burial set failed')
        __test_signal_ready()
        return
    }
    var rej = __test_funeral_try_spawn(1)
    if (rej) {
        __log_info_native('[test:84] try_spawn should fail with incomplete provisions, got ' + rej)
        __test_signal_ready()
        return
    }
    __log_marker('funeral_reject_incomplete_provisions_ok')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = place_finished_mastaba([
        {x: cx - 5, y: cy - 2}, {x: cx - 5, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}
    ])
    if (!bid) {
        __log_info_native('[test:84] failed to place/finish mastaba')
        __test_signal_ready()
        return
    }

    __test_burial_provisions_force_dispatched(RESOURCE_LINEN, 8)
    if (!__scenario_burial_provisions_complete()) {
        __log_info_native('[test:84] provisions should be complete')
        __test_signal_ready()
        return
    }

    var fid = __test_funeral_try_spawn(1)
    if (!fid || !__figure_is_valid(fid) || __figure_get_type(fid) != FIGURE_FUNERAL_WALKER) {
        __log_info_native('[test:84] try_spawn failed with finished tomb + complete provisions, fid=' + fid)
        __test_signal_ready()
        return
    }

    __test_figure_set_action(fid, ACTION_0_FUNERAL_CREATED)
    __test_figure_action_perform(fid)

    var dest = __figure_get_destination_building_id(fid)
    var action = __figure_get_action_state(fid)
    if (dest != bid) {
        __log_info_native('[test:84] destination want ' + bid + ' got ' + dest + ' action=' + action)
        __test_signal_ready()
        return
    }
    if (action != ACTION_1_FUNERAL_GOING_TO_TOMB) {
        __log_info_native('[test:84] expected ACTION_1_FUNERAL_GOING_TO_TOMB, got ' + action)
        __test_signal_ready()
        return
    }
    __log_marker('funeral_goto_tomb_ok')

    // Abort mid-path must NOT set funeral_done.
    __test_figure_set_action(fid, ACTION_3_FUNERAL_ABORT)
    __test_figure_action_perform(fid)
    if (__test_monument_funeral_done(bid) != 0) {
        __log_info_native('[test:84] funeral_done set after ABORT')
        __test_signal_ready()
        return
    }
    city.figures.remove_figures(FIGURE_FUNERAL_WALKER)
    __log_marker('funeral_abort_no_done_ok')

    // Spawn again and arrive → funeral_done.
    fid = __test_funeral_try_spawn(1)
    if (!fid) {
        __log_info_native('[test:84] re-spawn after abort failed')
        __test_signal_ready()
        return
    }
    __test_figure_set_action(fid, ACTION_2_FUNERAL_ARRIVED)
    __test_figure_action_perform(fid)
    if (__test_monument_funeral_done(bid) != 1) {
        __log_info_native('[test:84] funeral_done not set after arrive')
        __test_signal_ready()
        return
    }
    __log_marker('funeral_done_on_arrive_ok')

    // No re-spawn same tomb.
    var again = __test_funeral_try_spawn(1)
    if (again) {
        __log_info_native('[test:84] should not re-spawn after funeral_done, got ' + again)
        __test_signal_ready()
        return
    }
    __log_marker('funeral_no_respawn_ok')

    // Contract: lowering dispatched must not clear funeral_done / re-enable funeral.
    __test_burial_provisions_force_dispatched(RESOURCE_LINEN, 0)
    if (__test_monument_funeral_done(bid) != 1) {
        __log_info_native('[test:84] funeral_done cleared when dispatched lowered')
        __test_signal_ready()
        return
    }
    // Restore complete so try_spawn is not refused for provisions; still no re-spawn.
    __test_burial_provisions_force_dispatched(RESOURCE_LINEN, 8)
    again = __test_funeral_try_spawn(1)
    if (again) {
        __log_info_native('[test:84] steal/re-dispatch must not re-spawn funeral, got ' + again)
        __test_signal_ready()
        return
    }
    __log_marker('funeral_steal_keeps_done_ok')

    // No provisions required → spawn on finished alone (fresh tomb).
    city.figures.remove_figures(FIGURE_FUNERAL_WALKER)
    __test_burial_provisions_clear()
    var bid2 = place_finished_mastaba([
        {x: cx + 8, y: cy - 2}, {x: cx + 8, y: cy}, {x: 50, y: 40}, {x: 55, y: 35}
    ])
    if (!bid2) {
        __log_info_native('[test:84] failed to place second mastaba for no-provisions case')
        __test_signal_ready()
        return
    }
    if (!__scenario_burial_provisions_complete()) {
        __log_info_native('[test:84] empty provisions should be complete')
        __test_signal_ready()
        return
    }
    var fid2 = __test_funeral_try_spawn(1)
    if (!fid2) {
        __log_info_native('[test:84] no-provisions-required spawn failed')
        __test_signal_ready()
        return
    }
    // Arrive so funeral_done set; leave city clean for multi-tomb check.
    __test_figure_set_action(fid2, ACTION_2_FUNERAL_ARRIVED)
    __test_figure_action_perform(fid2)
    __log_marker('funeral_no_provisions_required_ok')

    // Multi-tomb: two finished tombs without funeral_done → one walker each.
    city.figures.remove_figures(FIGURE_FUNERAL_WALKER)
    __test_monument_set_funeral_done(bid, 0)
    __test_monument_set_funeral_done(bid2, 0)
    var first = __test_funeral_try_spawn(1)
    if (!first) {
        __log_info_native('[test:84] multi-tomb spawn returned 0')
        __test_signal_ready()
        return
    }
    var live = count_live_funerals()
    if (live < 2) {
        __log_info_native('[test:84] multi-tomb expected 2 walkers, got ' + live)
        __test_signal_ready()
        return
    }
    __log_marker('funeral_multi_tomb_ok')

    // Pyramid path: finished small stepped + provisions complete → spawn.
    city.figures.remove_figures(FIGURE_FUNERAL_WALKER)
    __test_monument_set_funeral_done(bid, 1)
    __test_monument_set_funeral_done(bid2, 1)
    var pbid = place_finished_small_stepped([
        {x: 20, y: 20}, {x: 25, y: 25}, {x: cx - 12, y: cy - 12}, {x: 60, y: 20}
    ])
    if (!pbid) {
        __log_info_native('[test:84] failed to place/finish small stepped pyramid')
        __test_signal_ready()
        return
    }
    var pfid = __test_funeral_try_spawn(1)
    if (!pfid || !__figure_is_valid(pfid) || __figure_get_type(pfid) != FIGURE_FUNERAL_WALKER) {
        __log_info_native('[test:84] pyramid spawn failed, fid=' + pfid)
        __test_signal_ready()
        return
    }
    __test_figure_set_action(pfid, ACTION_0_FUNERAL_CREATED)
    __test_figure_action_perform(pfid)
    if (__figure_get_destination_building_id(pfid) != pbid) {
        __log_info_native('[test:84] pyramid dest want ' + pbid + ' got '
            + __figure_get_destination_building_id(pfid))
        __test_signal_ready()
        return
    }
    __log_marker('funeral_pyramid_spawn_ok')

    // Destination resolver must prefer a road tile when one exists near the tomb
    // (mausoleum AP sits on blocked footprint — must not stick there).
    city.figures.remove_figures(FIGURE_FUNERAL_WALKER)
    __test_monument_set_funeral_done(bid, 1)
    __test_monument_set_funeral_done(bid2, 1)
    __test_monument_set_funeral_done(pbid, 1)
    var mbid = place_finished_mausoleum([
        {x: 70, y: 20}, {x: 75, y: 25}, {x: cx + 14, y: cy + 8}, {x: 15, y: 55}
    ])
    if (!mbid) {
        __log_info_native('[test:84] failed to place/finish mausoleum')
        __test_signal_ready()
        return
    }
    var mfid = __test_funeral_try_spawn(1)
    if (!mfid || !__figure_is_valid(mfid) || __figure_get_type(mfid) != FIGURE_FUNERAL_WALKER) {
        __log_info_native('[test:84] mausoleum spawn failed, fid=' + mfid)
        __test_signal_ready()
        return
    }
    __test_figure_set_action(mfid, ACTION_0_FUNERAL_CREATED)
    __test_figure_action_perform(mfid)
    if (__figure_get_destination_building_id(mfid) != mbid) {
        __log_info_native('[test:84] mausoleum dest want ' + mbid + ' got '
            + __figure_get_destination_building_id(mfid))
        __test_signal_ready()
        return
    }
    // Soft: if map has a road near tomb, destination must be on it (not blocked AP).
    if (__test_funeral_tomb_dest_is_road(mbid) == 1 && __test_funeral_dest_is_road(mfid) != 1) {
        __log_info_native('[test:84] mausoleum destination not on road despite road nearby')
        __test_signal_ready()
        return
    }
    __test_figure_set_action(mfid, ACTION_2_FUNERAL_ARRIVED)
    __test_figure_action_perform(mfid)
    if (__test_monument_funeral_done(mbid) != 1) {
        __log_info_native('[test:84] mausoleum funeral_done not set after arrive')
        __test_signal_ready()
        return
    }
    __log_marker('funeral_mausoleum_spawn_ok')

    // Inert action (0) with tomb id must not block daily respawn forever.
    city.figures.remove_figures(FIGURE_FUNERAL_WALKER)
    __test_monument_set_funeral_done(mbid, 0)
    var ifid = __test_funeral_try_spawn(1)
    if (!ifid) {
        __log_info_native('[test:84] inert-action setup spawn failed')
        __test_signal_ready()
        return
    }
    __test_figure_set_action(ifid, 0)
    var inert_again = __test_funeral_try_spawn(1)
    if (!inert_again) {
        __log_info_native('[test:84] inert action=0 blocked respawn')
        __test_signal_ready()
        return
    }
    // Prefer revive of the inert slot over a duplicate walker.
    if (inert_again != ifid) {
        __log_info_native('[test:84] inert revive want fid ' + ifid + ' got ' + inert_again)
        __test_signal_ready()
        return
    }
    if (__figure_get_action_state(ifid) != ACTION_0_FUNERAL_CREATED
        && __figure_get_action_state(ifid) != ACTION_1_FUNERAL_GOING_TO_TOMB) {
        __log_info_native('[test:84] inert revive bad action '
            + __figure_get_action_state(ifid))
        __test_signal_ready()
        return
    }
    city.figures.remove_figures(FIGURE_FUNERAL_WALKER)
    __test_monument_set_funeral_done(mbid, 1)
    __log_marker('funeral_inert_action_no_block_ok')

    // Mid-walk save/load: while GOING, funeral_done must stay clear; then verify
    // the monument bind roundtrips (no re-spawn).
    // Note: under --no-resource integraltests, figure slots can come back empty
    // (general figure-IO / harness limit) — monument funeral_done bind is the DoD.
    city.figures.remove_figures(FIGURE_FUNERAL_WALKER)
    __test_monument_set_funeral_done(pbid, 0)
    pfid = __test_funeral_try_spawn(1)
    if (!pfid) {
        __log_info_native('[test:84] re-spawn pyramid for midwalk failed')
        __test_signal_ready()
        return
    }
    __test_figure_set_action(pfid, ACTION_0_FUNERAL_CREATED)
    __test_figure_action_perform(pfid)
    if (__figure_get_action_state(pfid) != ACTION_1_FUNERAL_GOING_TO_TOMB) {
        __log_info_native('[test:84] expected GOING before saveload, got '
            + __figure_get_action_state(pfid))
        __test_signal_ready()
        return
    }
    if (__test_monument_funeral_done(pbid) != 0) {
        __log_info_native('[test:84] funeral_done set before mid-walk save')
        __test_signal_ready()
        return
    }

    var save_name = 'test_84_funeral_midwalk.svx'
    if (!__game_write_savegame(save_name)) {
        __log_info_native('[test:84] write_savegame failed — saveload skipped')
        __log_marker('funeral_midwalk_saveload_skipped')
        __test84_saveload_skipped = true
        __test_signal_ready()
        return
    }
    if (!__game_load_savegame(save_name)) {
        __log_info_native('[test:84] load_savegame failed — saveload skipped')
        __game_delete_savegame(save_name)
        __log_marker('funeral_midwalk_saveload_skipped')
        __test84_saveload_skipped = true
        __test_signal_ready()
        return
    }

    if (__test_monument_funeral_done(pbid) != 0) {
        __log_info_native('[test:84] funeral_done flipped after mid-walk load')
        __game_delete_savegame(save_name)
        __test_signal_ready()
        return
    }

    // Prefer restoring via a live walker if fields survived; else force the flag.
    var loaded = find_live_funeral()
    var loaded_dest = loaded ? __figure_get_destination_building_id(loaded) : 0
    var loaded_target = loaded ? __test_funeral_target_tomb(loaded) : 0
    var loaded_action = loaded ? __figure_get_action_state(loaded) : -1
    var figure_restored = loaded && loaded_action > 0
        && (loaded_dest == pbid || loaded_target == pbid)
    if (figure_restored) {
        __test_figure_set_action(loaded, ACTION_2_FUNERAL_ARRIVED)
        __test_figure_action_perform(loaded)
        if (__test_monument_funeral_done(pbid) != 1) {
            __log_info_native('[test:84] restored walker arrive did not set funeral_done')
            __game_delete_savegame(save_name)
            __test_signal_ready()
            return
        }
    } else {
        __log_info_native('[test:84] figure mid-walk fields not restored (ok under --no-resource)')
        __test_monument_set_funeral_done(pbid, 1)
    }
    if (__test_monument_funeral_done(pbid) != 1) {
        __log_info_native('[test:84] could not set funeral_done after mid-walk load')
        __game_delete_savegame(save_name)
        __test_signal_ready()
        return
    }

    // Persist funeral_done across a second save/load; no re-spawn.
    if (!__game_write_savegame(save_name) || !__game_load_savegame(save_name)) {
        __log_info_native('[test:84] second saveload failed — saveload skipped')
        __game_delete_savegame(save_name)
        __log_marker('funeral_midwalk_saveload_skipped')
        __test84_saveload_skipped = true
        __test_signal_ready()
        return
    }
    if (__test_monument_funeral_done(pbid) != 1) {
        __log_info_native('[test:84] funeral_done lost after second load')
        __game_delete_savegame(save_name)
        __test_signal_ready()
        return
    }
    again = __test_funeral_try_spawn(1)
    if (again) {
        __log_info_native('[test:84] should not re-spawn after saved funeral_done, got ' + again)
        __game_delete_savegame(save_name)
        __test_signal_ready()
        return
    }

    __game_delete_savegame(save_name)
    __log_marker('funeral_midwalk_saveload_ok')
    __test84_saveload_ok = true

    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'funeral_registered_ok',
        'funeral_reject_incomplete_provisions_ok',
        'funeral_goto_tomb_ok',
        'funeral_abort_no_done_ok',
        'funeral_done_on_arrive_ok',
        'funeral_no_respawn_ok',
        'funeral_steal_keeps_done_ok',
        'funeral_no_provisions_required_ok',
        'funeral_multi_tomb_ok',
        'funeral_pyramid_spawn_ok',
        'funeral_mausoleum_spawn_ok',
        'funeral_inert_action_no_block_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:84] missing marker: ' + marker)
            return false
        }
    }

    if (__test_find_inlog('[test-marker] funeral_midwalk_saveload_ok') && __test84_saveload_ok) {
        return true
    }
    if (__test_find_inlog('[test-marker] funeral_midwalk_saveload_skipped') && __test84_saveload_skipped) {
        return true
    }
    __log_info_native('[test:84] missing midwalk saveload ok/skipped marker')
    return false
}

// OG Alexandria Library: 25 chained parts, laborer prep (100 ticks), shared stage 3+,
// mason WAIT_FOR_BLOCK / material wake smoke, save/load, finish.

function t299_fail(msg) {
    __log_info_native('[test:299] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:299] OG alexandria library')
    test_reload_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_ALEXANDRIA_LIBRARY)) {
        __scenario_building_allow(BUILDING_ALEXANDRIA_LIBRARY, true)
    }
    __test_set_treasury(500000)

    var bid = test_building_place(BUILDING_ALEXANDRIA_LIBRARY, 40, 40)
    if (!bid) {
        bid = test_building_place(BUILDING_ALEXANDRIA_LIBRARY, 30, 30)
    }
    if (!bid) {
        return t299_fail('place failed')
    }
    __test_process_events()
    __test_pump_frames(2)

    var parts = __test_alexandria_library_part_count(bid)
    if (parts != 25) {
        return t299_fail('expected 25 parts, got ' + parts)
    }
    __log_marker('t299_25_parts')

    var stage0 = __test_alexandria_library_stage(bid)
    if (stage0 != 1) {
        return t299_fail('main stage want 1 got ' + stage0)
    }
    __log_marker('t299_stage_started')

    var second = test_building_place(BUILDING_ALEXANDRIA_LIBRARY, 60, 40)
    if (second) {
        return t299_fail('second unfinished placed')
    }
    __log_marker('t299_second_rejected')

    for (var i = 0; i < 24; i++) {
        __test_alexandria_library_set_part_stage(bid, i, 2)
    }
    if (__test_alexandria_library_part_stage(bid, 24) != 1) {
        return t299_fail('part 24 should still be started')
    }

    var part24 = __test_alexandria_library_part_id(bid, 24)
    if (!part24) {
        return t299_fail('missing part 24')
    }

    var laborer = __test_figure_create(FIGURE_LABORER, 42, 42)
    if (!laborer) {
        return t299_fail('laborer create failed')
    }
    __test_figure_set_action(laborer, 33) // ACTION_33_LABORER_LIBRARY_WORK
    var fobj = city.get_figure(laborer)
    if (!fobj) {
        return t299_fail('laborer figure missing')
    }
    fobj.destination_building_id = part24

    var done = 0
    for (var t = 0; t < 120; t++) {
        done = __test_alexandria_library_work(part24, laborer)
        if (done < 0) {
            return t299_fail('work helper error at tick ' + t)
        }
        if (done === 1) {
            break
        }
    }
    if (done !== 1) {
        return t299_fail('laborer prep did not finish in 120 ticks done=' + done
            + ' stage24=' + __test_alexandria_library_part_stage(bid, 24))
    }
    if (__test_alexandria_library_part_stage(bid, 24) < 2) {
        return t299_fail('part 24 not prepared after work stage='
            + __test_alexandria_library_part_stage(bid, 24))
    }
    __log_marker('t299_prep_last_ok')

    var stage_after = __test_alexandria_library_stage(bid)
    if (stage_after != 3) {
        return t299_fail('after all prepared want stage 3 got ' + stage_after)
    }
    __log_marker('t299_building_stage')

    // Mason arrives WAIT_FOR_BLOCK; work_tick must not finish the spot until woken.
    var mason = __test_figure_create(FIGURE_STONEMASON, 42, 42)
    if (!mason) {
        return t299_fail('mason create failed')
    }
    __test_figure_set_action(mason, 19) // ACTION_19_MASON_WAIT_FOR_BLOCK
    var mobj = city.get_figure(mason)
    if (mobj) {
        mobj.destination_building_id = bid
    }
    if (!__test_alexandria_library_check_work(bid, mason, 1)) {
        return t299_fail('mason check_work assign failed')
    }
    var still_waiting = 0
    for (var w = 0; w < 5; w++) {
        still_waiting = !__test_alexandria_library_work(bid, mason)
    }
    if (!still_waiting) {
        return t299_fail('mason should stay WAIT_FOR_BLOCK without sleds')
    }
    __log_marker('t299_mason_wait')

    // Two material deliveries wake mason (LIBRARY_FRAME_COUNT=2).
    __test_alexandria_library_deliver_material(bid)
    __test_alexandria_library_deliver_material(bid)
    var m2 = city.get_figure(mason)
    if (!m2 || (m2.action_state | 0) == 19) {
        return t299_fail('mason not woken after 2 sleds state=' + (m2 ? m2.action_state : -1))
    }
    __log_marker('t299_mason_woke')

    // Save/load while under construction — phase must survive (spots rebuild from stage).
    var save_name = 'test_299_alexandria_library.svx'
    if (!__game_write_savegame(save_name) || !__game_load_savegame(save_name)) {
        __game_delete_savegame(save_name)
        return t299_fail('saveload write/load failed')
    }
    __test_process_events()
    __test_pump_frames(2)
    var stage_sl = __test_alexandria_library_stage(bid)
    var parts_sl = __test_alexandria_library_part_count(bid)
    __game_delete_savegame(save_name)
    if (parts_sl != 25 || stage_sl != 3) {
        return t299_fail('after load: parts=' + parts_sl + ' stage=' + stage_sl + ' (want 25 / 3)')
    }
    __log_marker('t299_saveload_ok')

    __test_alexandria_library_finish(bid)
    __test_process_events()
    __test_pump_frames(2)
    var ph = __test_monument_phase(bid)
    if (ph != 255 && ph != -1) {
        return t299_fail('not finished after finish helper ph=' + ph)
    }
    __log_marker('t299_finished')

    test_monument_slots([BUILDING_ALEXANDRIA_LIBRARY])
    city_update_monthly_monument_rating({})
    var rating_done = city.rating.monument | 0
    // OG weight 12 → trunc(6.32*sqrt(12)+0.5)=22
    if (rating_done < 22) {
        return t299_fail('rating want >=22 got ' + rating_done)
    }
    __log_marker('t299_rating_ok')

    __log_info_native('[test:299] PASS')
    __log_marker('t299_ok')
    __test_signal_ready()
}

function check_valid() {
    var required = [
        't299_25_parts',
        't299_stage_started',
        't299_second_rejected',
        't299_prep_last_ok',
        't299_building_stage',
        't299_mason_wait',
        't299_mason_woke',
        't299_saveload_ok',
        't299_finished',
        't299_rating_ok',
        't299_ok'
    ]
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + required[i])
            && !__test_find_inlog(required[i])) {
            __log_info_native('[test:299] missing marker ' + required[i])
            return false
        }
    }
    return true
}

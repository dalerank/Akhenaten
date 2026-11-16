// Abu Simbel — composite 9×21 (OG/Heaven); cliff bulk + clear entrance; finish → rating.

function run_test() {
    __log_info_native('[test:118] abu simbel cliff place + finish rating')
    test_reload_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_ABU_SIMBEL)) {
        __scenario_building_allow(BUILDING_ABU_SIMBEL, true)
    }

    __test_set_treasury(500000)

    var cx = 50
    var cy = 50
    // Heaven bulk 9×21: cliff under X0..5 except entrance column; midcut_front clear.
    // Wide plateau so default elevation edges sit far from the niche (GIF-style).
    var w = 9
    var h = 21
    var plateau_pad = 12

    function paint_cliff_site(ox, oy) {
        for (var dy = -plateau_pad; dy < h + plateau_pad; dy++) {
            for (var dx = -plateau_pad; dx < 6 + plateau_pad; dx++) {
                // Entrance column X6..8 stays clear inside the footprint.
                if (dx >= 6 && dx <= 8 && dy >= 0 && dy < h) {
                    continue
                }
                terrain.add({ x: ox + dx, y: oy + dy }, TERRAIN_ELEVATION)
            }
        }
    }

    // Reject on clear land (no cliffs).
    var rejected = test_building_place(BUILDING_ABU_SIMBEL, cx, cy)
    if (rejected) {
        __log_info_native('[test:118] unexpected place without cliffs bid=' + rejected)
        __test_signal_ready()
        return
    }
    __log_marker('abu_simbel_reject_no_cliff_ok')

    paint_cliff_site(cx, cy)
    __log_marker('abu_simbel_cliff_painted')

    var bid = test_building_place(BUILDING_ABU_SIMBEL, cx, cy)
    if (!bid) {
        __log_info_native('[test:118] failed to place BUILDING_ABU_SIMBEL on cliffs')
        __test_signal_ready()
        return
    }

    __test_process_events()
    __test_pump_frames(2)

    var b = city.get_building(bid)
    if (!b || b.type != BUILDING_ABU_SIMBEL) {
        __log_info_native('[test:118] placed building type mismatch')
        __test_signal_ready()
        return
    }
    __log_marker('abu_simbel_placed_ok:' + bid)

    // Second (while unfinished) must be rejected — only one ever.
    paint_cliff_site(cx + 20, cy)
    var second = test_building_place(BUILDING_ABU_SIMBEL, cx + 20, cy)
    if (second) {
        __log_info_native('[test:118] unexpected second unfinished place bid=' + second)
        __test_signal_ready()
        return
    }
    __log_marker('abu_simbel_reject_second_ok')

    // Walk progressive art stages (10 GIF milestones); screenshot each.
    __test_camera_center_building(bid)
    __test_process_events()
    __test_pump_frames(2)
    for (var stage = 1; stage <= 10; stage++) {
        __test_monument_set_phase(bid, stage - 1)
        __test_process_events()
        __test_pump_frames(4)
        var stage_name = (stage < 10) ? ('abu_simbel_stage_0' + stage) : ('abu_simbel_stage_' + stage)
        __game_save_screenshot_as(SCREENSHOT_DISPLAY, stage_name)
        __log_marker('abu_simbel_art_stage:' + stage)
    }
    __log_marker('abu_simbel_art_screenshot_ok')

    // 10 art stages + terminal → phases().size()==11; set_phase(11) → FINISHED
    __test_monument_set_phase(bid, 11)
    __test_process_events()
    __test_pump_frames(4)
    __game_save_screenshot_as(SCREENSHOT_DISPLAY, 'abu_simbel_stage_finish')

    var ph = __test_monument_phase(bid)
    if (ph != 255 && ph != -1) {
        __log_info_native('[test:118] not finished after set_phase(11) ph=' + ph)
        __test_signal_ready()
        return
    }
    __log_marker('abu_simbel_finished_ok')

    test_monument_slots([BUILDING_ABU_SIMBEL])
    city_update_monthly_monument_rating({})
    var rating_done = city.rating.monument | 0
    if (rating_done < 44) {
        __log_info_native('[test:118] finished rating want >=44 got ' + rating_done)
        __log_marker('abu_simbel_rating_fail:' + rating_done)
        __test_signal_ready()
        return
    }
    __log_marker('abu_simbel_rating_ok:' + rating_done)

    paint_cliff_site(cx + 20, cy)
    var third = test_building_place(BUILDING_ABU_SIMBEL, cx + 20, cy)
    if (third) {
        __log_info_native('[test:118] unexpected place after finish bid=' + third)
        __test_signal_ready()
        return
    }
    __log_marker('abu_simbel_reject_after_finish_ok')

    __log_info_native('[test:118] PASS')
    __log_marker('abu_simbel_ok')
    __test_signal_ready()
}

function check_valid() {
    var required = [
        'abu_simbel_reject_no_cliff_ok',
        'abu_simbel_placed_ok',
        'abu_simbel_reject_second_ok',
        'abu_simbel_art_screenshot_ok',
        'abu_simbel_finished_ok',
        'abu_simbel_rating_ok',
        'abu_simbel_reject_after_finish_ok',
        'abu_simbel_ok'
    ]
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + required[i])
            && !__test_find_inlog(required[i])) {
            __log_info_native('[test:118] missing marker ' + required[i])
            return false
        }
    }
    return true
}

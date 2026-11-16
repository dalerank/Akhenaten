// Mudbrick Pyramid Complex (20×20 + causeway-to-water). Annex temples still open.
// Schedule: height 0–35 → polish 36–40 (5 layers) → terminal 41; finish = set_phase(total).
// Grand uses same on-land body; smoke-place at end.

function run_test() {
    __log_info_native('[test:127] mudbrick pyramid complex place + phase walk')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_MUDBRICK_PYRAMID_COMPLEX)) {
        __scenario_building_allow(BUILDING_MUDBRICK_PYRAMID_COMPLEX, true)
    }
    if (!__scenario_building_allowed(BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX)) {
        __scenario_building_allow(BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX, true)
    }

    __test_set_treasury(500000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var px = cx - 10
    var py = cy - 10
    test_prepare_pyramid_complex_causeway(px, py, 20, 12, 4)

    var bid = test_building_place(BUILDING_MUDBRICK_PYRAMID_COMPLEX, px, py)
    if (!bid) {
        test_prepare_pyramid_complex_causeway(cx, cy, 20, 12, 4)
        bid = test_building_place(BUILDING_MUDBRICK_PYRAMID_COMPLEX, cx, cy)
    }
    if (!bid) {
        __log_info_native('[test:127] failed to place BUILDING_MUDBRICK_PYRAMID_COMPLEX')
        __test_signal_ready()
        return
    }

    var tile = __building_tile(bid)
    __log_marker('mudbrick_pyramid_complex_placed_ok:' + bid + ':' + tile.x + ',' + tile.y)

    __test_camera_center_building(bid)
    if (test_pyramid_complex_causeway_claimed(bid, tile.x, tile.y, 20, 12)) {
        __log_marker('mudbrick_pyramid_complex_causeway_claimed_ok')
    } else {
        __log_info_native('[test:127] causeway tiles not claimed')
        __log_marker('mudbrick_pyramid_complex_causeway_claimed_fail')
    }

    if (__building_type(bid) != BUILDING_MUDBRICK_PYRAMID_COMPLEX) {
        __log_info_native('[test:127] unexpected type ' + __building_type(bid))
        __test_signal_ready()
        return
    }

    var parts = [bid]
    var cur = city.get_building(bid)
    while (cur && cur.next_part_building_id > 0 && parts.length < 256) {
        parts.push(cur.next_part_building_id)
        cur = city.get_building(cur.next_part_building_id)
    }
    // 20×20 / 2×2 = 100 body parts (causeway is map claim, not linked parts)
    if (parts.length >= 80) {
        __log_marker('mudbrick_pyramid_complex_parts_ok:' + parts.length)
    } else {
        __log_marker('mudbrick_pyramid_complex_parts_fail:' + parts.length)
    }

    var mon0 = city.get_monument(bid)
    if (!mon0) {
        __log_info_native('[test:127] city.get_monument failed')
        __test_signal_ready()
        return
    }
    var total = mon0.phases_total()
    // height 0–35 + polish 36–40 + terminal → phases_total >= 41
    if (total < 41) {
        __log_info_native('[test:127] phases_total=' + total + ' want >=41')
        __log_marker('mudbrick_pyramid_complex_schedule_fail:' + total)
        __test_signal_ready()
        return
    }
    __log_marker('mudbrick_pyramid_complex_schedule_ok:' + total)

    var all_ok = true
    var check_phases = [0, 2, 24, 35, 36, 40]
    for (var ci = 0; ci < check_phases.length; ci++) {
        var want = check_phases[ci]
        __test_monument_set_phase(bid, want)
        __test_pump_frames(2)
        var got = __test_monument_phase(bid)
        if (got != want) {
            __log_info_native('[test:127] phase want ' + want + ' got ' + got)
            all_ok = false
        }
        // Polish check while still on phase 36 (before finish) — do not
        // re-open a finished monument or keep-window shows a broken body.
        if (want == 36) {
            var mon36 = city.get_monument(bid)
            if (mon36 && mon36.phase() == 36 && mon36.material_pct_min() == 100) {
                __log_marker('mudbrick_pyramid_complex_polish_no_lime_ok')
            } else {
                __log_marker('mudbrick_pyramid_complex_polish_fail')
                all_ok = false
            }
        }
    }

    __test_monument_set_phase(bid, total)
    __test_pump_frames(2)
    var fin = __test_monument_phase(bid)
    if (fin != -1 && fin != 255) {
        __log_info_native('[test:127] finish want -1 after set_phase(total), got ' + fin)
        all_ok = false
    }

    if (all_ok) {
        __log_marker('mudbrick_pyramid_complex_phases_ok')
    } else {
        __log_marker('mudbrick_pyramid_complex_phases_fail')
    }

    // Grand smoke: place elsewhere with causeway prep
    var gx = cx + 24
    var gy = cy - 10
    if (gx + 20 >= __scenario_map.width) {
        gx = 16
        gy = cy + 24
    }
    test_prepare_pyramid_complex_causeway(gx, gy, 20, 4, 3)
    var gbid = test_building_place(BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX, gx, gy)
    if (!gbid) {
        test_prepare_pyramid_complex_causeway(cx - 10, cy + 24, 20, 4, 3)
        gbid = test_building_place(BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX, cx - 10, cy + 24)
    }
    if (gbid && __building_type(gbid) == BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX) {
        var gmon = city.get_monument(gbid)
        var gtotal = gmon ? gmon.phases_total() : 0
        if (gtotal >= 41) {
            __log_marker('mudbrick_pyramid_grand_placed_ok:' + gbid + ':' + gtotal)
        } else {
            __log_marker('mudbrick_pyramid_grand_schedule_fail:' + gtotal)
        }
    } else {
        __log_info_native('[test:127] grand place failed (non-fatal for complex markers)')
        __log_marker('mudbrick_pyramid_grand_placed_fail')
    }

    __log_info_native('[test:127] done')
    __test_signal_ready()
}

function check_valid() {
    var required = [
        'mudbrick_pyramid_complex_placed_ok',
        'mudbrick_pyramid_complex_causeway_claimed_ok',
        'mudbrick_pyramid_complex_parts_ok',
        'mudbrick_pyramid_complex_schedule_ok',
        'mudbrick_pyramid_complex_phases_ok',
        'mudbrick_pyramid_complex_polish_no_lime_ok',
        'mudbrick_pyramid_grand_placed_ok'
    ]
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog(required[i])) {
            __log_info_native('[test:127] missing: ' + required[i])
            return false
        }
    }
    if (__test_find_inlog('mudbrick_pyramid_complex_phases_fail')
        || __test_find_inlog('mudbrick_pyramid_complex_parts_fail')
        || __test_find_inlog('mudbrick_pyramid_complex_polish_fail')
        || __test_find_inlog('mudbrick_pyramid_complex_schedule_fail')
        || __test_find_inlog('mudbrick_pyramid_complex_causeway_claimed_fail')
        || __test_find_inlog('mudbrick_pyramid_grand_placed_fail')
        || __test_find_inlog('mudbrick_pyramid_grand_schedule_fail')) {
        return false
    }
    return true
}

// CO1: monument store upsert + apply + survive troop activate(mask=0).
// CO1b: bad stored tile → clear-land / rock scan fallback.
// Markers:
//   [test-marker] monument_carry_set_ok
//   [test-marker] monument_carry_apply_ok
//   [test-marker] monument_carry_survive_troop_clear_ok
//   [test-marker] monument_carry_fallback_ok
//   [test-marker] monument_carry_all_ok

function find_preexisting_library() {
    for (var i = 1; i < 2000; i++) {
        var b = city.get_building(i)
        if (!b || b.type != BUILDING_ALEXANDRIA_LIBRARY) {
            continue
        }
        if (!__test_monument_is_preexisting(i)) {
            continue
        }
        return i
    }
    return 0
}

function run_test() {
    __log_info_native('[test:137] monument carry CO1 / CO1b')
    test_ensure_city_session('data/default.map')
    city.finance.treasury = 50000

    __campaign_carry_clear()
    // Large clear patch used by library place tests on default.map
    __campaign_carry_set_monument(0, BUILDING_ALEXANDRIA_LIBRARY, 70, 70, 0, 0)
    if (__campaign_carry_monument_type(0) != BUILDING_ALEXANDRIA_LIBRARY) {
        __log_info_native('[test:137] set_monument failed')
        __test_signal_ready()
        return
    }
    __log_marker('monument_carry_set_ok')

    if (!__scenario_building_allowed(BUILDING_ALEXANDRIA_LIBRARY)) {
        __scenario_building_allow(BUILDING_ALEXANDRIA_LIBRARY, true)
    }

    __campaign_carry_apply_monuments()
    __test_pump_frames(2)

    var found = find_preexisting_library()
    if (!found) {
        __log_info_native('[test:137] apply did not place library')
        __test_signal_ready()
        return
    }
    __log_marker('monument_carry_apply_ok')

    // Troop activate(mask=0) must clear troops only — monument store survives (Maritis gap).
    __campaign_carry_set_slot(0, 12, 1, 70)
    __campaign_carry_activate(0)
    if (__campaign_carry_pending_mask() != 0) {
        __log_info_native('[test:137] troops should be cleared')
        __test_signal_ready()
        return
    }
    if (__campaign_carry_monument_type(0) != BUILDING_ALEXANDRIA_LIBRARY) {
        __log_info_native('[test:137] monument store wiped by troop activate(0)')
        __test_signal_ready()
        return
    }
    __log_marker('monument_carry_survive_troop_clear_ok')

    // CO1b: fresh map + previous-map tile the 13×14 footprint cannot fit on (runs off the
    //       map edge) → clear-land / rock scan fallback. default.map is empty, so a low tile
    //       like 1,1 would legitimately fit and would not exercise the fallback at all.
    test_reload_city_session('data/default.map')
    city.finance.treasury = 50000
    if (!__scenario_building_allowed(BUILDING_ALEXANDRIA_LIBRARY)) {
        __scenario_building_allow(BUILDING_ALEXANDRIA_LIBRARY, true)
    }
    __campaign_carry_clear()
    var bad_x = __scenario_map.width - 2
    var bad_y = __scenario_map.height - 2
    __campaign_carry_set_monument(0, BUILDING_ALEXANDRIA_LIBRARY, bad_x, bad_y, 0, 0)
    __campaign_carry_apply_monuments()
    __test_pump_frames(2)
    found = find_preexisting_library()
    if (!found) {
        __log_info_native('[test:137] CO1b fallback did not place library')
        __test_signal_ready()
        return
    }
    var tile = __building_tile(found)
    if (!tile || (tile.x == bad_x && tile.y == bad_y)) {
        __log_info_native('[test:137] CO1b expected relocated tile, got '
            + (tile ? (tile.x + ',' + tile.y) : 'null'))
        __test_signal_ready()
        return
    }
    __log_marker('monument_carry_fallback_ok')
    __log_marker('monument_carry_all_ok')
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'monument_carry_set_ok',
        'monument_carry_apply_ok',
        'monument_carry_survive_troop_clear_ok',
        'monument_carry_fallback_ok',
        'monument_carry_all_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:137] missing marker: ' + marker)
            return false
        }
    }
    return true
}

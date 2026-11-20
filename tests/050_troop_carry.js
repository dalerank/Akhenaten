// CO2: troop carry snapshot → activate → fort place fills company.
// Markers:
//   [test-marker] troop_carry_snapshot_ok
//   [test-marker] troop_carry_activate_ok
//   [test-marker] troop_carry_apply_ok
//   [test-marker] troop_carry_expire_ok
//   [test-marker] troop_carry_menu_clear_ok
//   [test-marker] troop_carry_all_ok

function run_test() {
    __log_info_native('[test:050] troop carry CO2')
    test_ensure_city_session('data/default.map')
    city.finance.treasury = 50000

    __campaign_carry_clear()
    __campaign_carry_set_slot(0, 12, 1, 70) // infantry
    __campaign_carry_set_slot(2, 9, 1, 65)  // chariot
    if (__campaign_carry_slot_figures(0) != 12 || __campaign_carry_slot_figures(2) != 9) {
        __log_info_native('[test:050] set_slot failed')
        __test_signal_ready()
        return
    }
    __log_marker('troop_carry_snapshot_ok')

    // Qadesh mask: infantry + chariot (bits 0+2 = 5)
    __campaign_carry_activate(5)
    if (__campaign_carry_pending_mask() != 5) {
        __log_info_native('[test:050] pending_mask want 5 got ' + __campaign_carry_pending_mask())
        __test_signal_ready()
        return
    }
    if (!__campaign_carry_slot_pending(0) || !__campaign_carry_slot_pending(2)) {
        __log_info_native('[test:050] pending slots missing')
        __test_signal_ready()
        return
    }
    if (__campaign_carry_slot_pending(1)) {
        __log_info_native('[test:050] archer should not be pending')
        __test_signal_ready()
        return
    }
    __log_marker('troop_carry_activate_ok')

    if (!__scenario_building_allowed(BUILDING_FORT_INFANTRY)) {
        __scenario_building_allow(BUILDING_FORT_INFANTRY, true)
    }
    if (!__scenario_building_allowed(BUILDING_FORT_GROUND)) {
        __scenario_building_allow(BUILDING_FORT_GROUND, true)
    }

    var bid = test_building_place(BUILDING_FORT_INFANTRY, -1, -1)
    __test_pump_frames(2)
    if (!bid) {
        __log_info_native('[test:050] place fort failed')
        __test_signal_ready()
        return
    }
    if (__campaign_carry_slot_pending(0)) {
        __log_info_native('[test:050] infantry slot still pending after place')
        __test_signal_ready()
        return
    }
    var b = city.get_building(bid)
    var fid = b ? (b.formation_id | 0) : 0
    if (!fid) {
        __log_info_native('[test:050] fort has no formation')
        __test_signal_ready()
        return
    }
    var nvar = __formation_get_property(fid, "num_figures")
    var n = nvar === undefined || nvar === null ? -1 : (nvar | 0)
    if (n != 12) {
        __log_info_native('[test:050] formation figures want 12 got ' + n)
        __test_signal_ready()
        return
    }
    __log_marker('troop_carry_apply_ok')

    // CO2b: non-fort construction expires remaining pending (chariot still pending here).
    __campaign_carry_set_slot(2, 9, 1, 65)
    __campaign_carry_activate(4) // chariot only
    if (!__campaign_carry_slot_pending(2)) {
        __log_info_native('[test:050] chariot pending setup failed')
        __test_signal_ready()
        return
    }
    __campaign_carry_expire_troops()
    if (__campaign_carry_pending_mask() != 0) {
        __log_info_native('[test:050] expire left pending')
        __test_signal_ready()
        return
    }
    __log_marker('troop_carry_expire_ok')

    __campaign_carry_set_slot(0, 8, 0, 50)
    __campaign_carry_activate(1)
    __campaign_carry_clear()
    if (__campaign_carry_pending_mask() != 0) {
        __log_info_native('[test:050] clear left pending')
        __test_signal_ready()
        return
    }
    __log_marker('troop_carry_menu_clear_ok')
    __log_marker('troop_carry_all_ok')
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'troop_carry_snapshot_ok',
        'troop_carry_activate_ok',
        'troop_carry_apply_ok',
        'troop_carry_expire_ok',
        'troop_carry_menu_clear_ok',
        'troop_carry_all_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:050] missing marker: ' + marker)
            return false
        }
    }
    return true
}

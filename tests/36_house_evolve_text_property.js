// Verifies House.property runtime bindings via the generic {} accessor.
//  - evolve_text (xstring coerce) roundtrip
//  - worst_desirability_building_id (building_id / uint16) int roundtrip  [H1]
//  - full house info-window fill path (both determine helpers) runs without TypeError  [H1]
// Markers:
//   [test-marker] house_evolve_text_roundtrip_ok
//   [test-marker] house_evolve_text_clear_ok

function run_test() {
    __log_info_native('[test:36] house evolve_text xstring property roundtrip')
    test_ensure_city_session('data/default.map')

    var bid = __test_building_create(BUILDING_HOUSE_MEAGER_SHANTY, -1, -1)
    if (!bid) {
        __log_info_native('[test:36] __test_building_create failed')
        __test_signal_ready()
        return
    }

    var house = city.get_house(bid)
    if (!house) {
        __log_info_native('[test:36] city.get_house failed')
        __test_signal_ready()
        return
    }

    var key = "#cannot_evolve_cause_low_desirability"
    house.evolve_text = key
    if (house.evolve_text != key) {
        __log_info_native('[test:36] roundtrip failed got=[' + house.evolve_text + ']')
        __test_signal_ready()
        return
    }
    __log_marker('house_evolve_text_roundtrip_ok')

    house.evolve_text = ""
    if (house.evolve_text) {
        __log_info_native('[test:36] clear failed got=[' + house.evolve_text + ']')
        __test_signal_ready()
        return
    }
    __log_marker('house_evolve_text_clear_ok')

    // Second write after clear (same path as house_determine_evolve_text).
    house.evolve_text = "#house_upgrade_inprogress"
    if (house.evolve_text != "#house_upgrade_inprogress") {
        __log_info_native('[test:36] second write failed got=[' + house.evolve_text + ']')
        __test_signal_ready()
        return
    }
    __log_marker('house_evolve_text_rewrite_ok')

    // H1: worst_desirability_building_id is a building_id (uint16). Writing/reading it once
    // threw "TypeError: called object is not a function"; the generic {} accessor + House's
    // __property_getter override + inherited __property_setter now route it through archive_helper.
    house.worst_desirability_building_id = 42
    if (house.worst_desirability_building_id != 42) {
        __log_info_native('[test:36] worst_desirability roundtrip failed got=[' + house.worst_desirability_building_id + ']')
        __test_signal_ready()
        return
    }
    house.worst_desirability_building_id = 0
    if (house.worst_desirability_building_id != 0) {
        __log_info_native('[test:36] worst_desirability clear failed got=[' + house.worst_desirability_building_id + ']')
        __test_signal_ready()
        return
    }
    __log_marker('house_worst_desirability_int_roundtrip_ok')

    // H1 / UI branch: the info_window_house init fill path calls these two helpers, which read
    // and write worst_desirability_building_id and evolve_text. A regression re-introducing the
    // property-binding TypeError would throw here and the marker below would be missing.
    house_determine_worst_desirability_building(house)
    house_determine_evolve_text(house)
    if (typeof house.evolve_text != "string") {
        __log_info_native('[test:36] evolve_text not filled after determine, type=' + (typeof house.evolve_text))
        __test_signal_ready()
        return
    }
    __log_marker('house_info_window_determine_ok')

    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'house_evolve_text_roundtrip_ok',
        'house_evolve_text_clear_ok',
        'house_evolve_text_rewrite_ok',
        'house_worst_desirability_int_roundtrip_ok',
        'house_info_window_determine_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:36] missing marker: ' + marker)
            return false
        }
    }
    return true
}

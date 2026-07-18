// Verifies House.property.evolve_text roundtrip via generic {} binding (xstring coerce).
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

    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'house_evolve_text_roundtrip_ok',
        'house_evolve_text_clear_ok',
        'house_evolve_text_rewrite_ok'
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

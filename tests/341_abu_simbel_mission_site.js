// The Abu Simbel mission map carries the editor's monument rock; the OG layout must fit it somewhere
// and be placeable there.

function t341_fail(msg) {
    __log_info_native('[test:341] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:341] abu simbel on the mission map')
    test_reload_city_session('data/maps/m_043_abu_simbel.map')
    if (!__scenario_building_allowed(BUILDING_ABU_SIMBEL)) {
        __scenario_building_allow(BUILDING_ABU_SIMBEL, true)
    }

    var w = __scenario_map.width
    var h = __scenario_map.height
    var rock = 0
    var sites = []
    for (var y = 0; y < h; y++) {
        for (var x = 0; x < w; x++) {
            if (terrain.is({ x: x, y: y }, TERRAIN_ROCK_NEAR_MONUMENT)) {
                rock++
            }
            if (__test_abu_simbel_site_fits(x, y)) {
                sites.push({ x: x, y: y })
            }
        }
    }
    __log_info_native('[test:341] map ' + w + 'x' + h + ' monument rock ' + rock + ' sites ' + sites.length
        + (sites.length ? ' first ' + sites[0].x + ',' + sites[0].y : ''))
    if (rock == 0) {
        return t341_fail('mission map has no monument rock')
    }
    if (sites.length == 0) {
        return t341_fail('no site fits the OG layout')
    }
    __log_marker('t341_site_found')

    var bid = test_building_place(BUILDING_ABU_SIMBEL, sites[0].x, sites[0].y)
    if (!bid || __building_type(bid) != BUILDING_ABU_SIMBEL) {
        return t341_fail('place failed at ' + sites[0].x + ',' + sites[0].y)
    }
    __log_marker('t341_placed')
    __log_marker('t341_ok')
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] t341_ok')
}

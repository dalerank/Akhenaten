// OG house_evolve.c evolve_rules: a modest apartment merges with the three same-level 1x1 houses of its 2x2 block
// before it evolves (merge = 1), like every level from the crude hut to the spacious apartment.

var __test585_ok = false

function t585_fail(msg) {
    __log_info_native('[test:585] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)
    var all_merge = game_features.get('gameplay_change_all_houses_merge')
    game_features.set('gameplay_change_all_houses_merge', true)

    var x = ((__scenario_map.width / 2) | 0) - 6
    var y = ((__scenario_map.height / 2) | 0) - 6
    var type = BUILDING_HOUSE_MODEST_APARTMENT
    var ids = []
    var cells = [[0, 0], [1, 0], [0, 1], [1, 1]]
    for (var i = 0; i < cells.length; i++) {
        var bid = __test_building_create(type, x + cells[i][0], y + cells[i][1])
        if (!bid) {
            game_features.set('gameplay_change_all_houses_merge', all_merge)
            return t585_fail('house ' + i + ' not created')
        }
        __test_house_set_population(bid, 10)
        ids.push(bid)
    }

    __test_house_evolve_day(ids[0])
    game_features.set('gameplay_change_all_houses_merge', all_merge)

    var area = __test_houses_in_area(x - 1, y - 1, x + 2, y + 2)
    var parts = area.split(';').filter(function (s) { return s.length > 0 })
    if (parts.length != 1 || parts[0].split(':')[2] != '2' || parts[0].split(':')[3] != '40') {
        return t585_fail('modest apartments did not merge into one 2x2 house of 40: ' + area)
    }

    __log_marker('modest_apartment_merges_ok')
    __test585_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test585_ok && __test_find_inlog('[test-marker] modest_apartment_merges_ok')
}

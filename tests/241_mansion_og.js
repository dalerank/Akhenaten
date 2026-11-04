// OG mansion: one across Personal/Family/Dynasty, groundwater need, dynasty 5x5,
// tax_income_or_storage mirrors personal_savings, enemy destroy steals difficulty-%.
// Markers:
//   [test-marker] mansion_og_config_ok
//   [test-marker] mansion_og_unique_ok
//   [test-marker] mansion_og_savings_display_ok
//   [test-marker] mansion_og_enemy_destroy_ok

var ENEMY_THEFT_PCT = [0, 15, 30, 60, 100]

function run_test() {
    __log_info_native('[test:241] mansion OG behavior')
    test_ensure_city_session('data/default.map')

    var personal = get_building_config_by_id(BUILDING_PERSONAL_MANSION)
    var family = get_building_config_by_id(BUILDING_FAMILY_MANSION)
    var dynasty = get_building_config_by_id(BUILDING_DYNASTY_MANSION)
    if (!personal || !family || !dynasty) {
        __log_info_native('[test:241] missing mansion config')
        __test_signal_ready()
        return
    }
    if (!personal.needs || !personal.needs.groundwater
        || !family.needs || !family.needs.groundwater
        || !dynasty.needs || !dynasty.needs.groundwater) {
        __log_info_native('[test:241] groundwater need missing')
        __test_signal_ready()
        return
    }
    if ((personal.building_size | 0) !== 3 || (family.building_size | 0) !== 4
        || (dynasty.building_size | 0) !== 5) {
        __log_info_native('[test:241] sizes want 3/4/5 got '
            + personal.building_size + '/' + family.building_size + '/' + dynasty.building_size)
        __test_signal_ready()
        return
    }
    __log_marker('mansion_og_config_ok')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    // Drop any map-preplaced mansions so share table is a single Personal.
    __test_destroy_buildings_of_type(BUILDING_PERSONAL_MANSION)
    __test_destroy_buildings_of_type(BUILDING_FAMILY_MANSION)
    __test_destroy_buildings_of_type(BUILDING_DYNASTY_MANSION)
    city.kingdome.personal_savings = 1000

    var mid = __test_building_create(BUILDING_PERSONAL_MANSION, cx, cy)
    if (!mid) {
        __log_info_native('[test:241] create personal mansion failed')
        __test_signal_ready()
        return
    }
    __test_mansion_update_money_values()

    if (!building_is_unique_built(BUILDING_PERSONAL_MANSION)
        || !building_is_unique_built(BUILDING_FAMILY_MANSION)
        || !building_is_unique_built(BUILDING_DYNASTY_MANSION)) {
        __log_info_native('[test:241] unique across tiers failed after personal placed')
        __test_signal_ready()
        return
    }
    __log_marker('mansion_og_unique_ok')

    var b = city.get_building(mid)
    if ((b.tax_income_or_storage | 0) !== 1000) {
        __log_info_native('[test:241] savings display want 1000 got ' + b.tax_income_or_storage
            + ' (personal_count=' + __city_count_total_buildings(BUILDING_PERSONAL_MANSION) + ')')
        __test_signal_ready()
        return
    }
    __log_marker('mansion_og_savings_display_ok')

    var diff = __game_difficulty() | 0
    if (diff < 0 || diff > 4) {
        diff = 2
    }
    var pct = ENEMY_THEFT_PCT[diff]
    var expect_left = 1000 - ((1000 * pct / 100) | 0)
    if (!__test_building_destroy_by_enemy(mid)) {
        __log_info_native('[test:241] destroy_by_enemy failed')
        __test_signal_ready()
        return
    }
    if ((city.kingdome.personal_savings | 0) !== expect_left) {
        __log_info_native('[test:241] after enemy destroy savings want ' + expect_left
            + ' got ' + city.kingdome.personal_savings + ' (diff=' + diff + ' pct=' + pct + ')')
        __test_signal_ready()
        return
    }
    __log_marker('mansion_og_enemy_destroy_ok')
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'mansion_og_config_ok',
        'mansion_og_unique_ok',
        'mansion_og_savings_display_ok',
        'mansion_og_enemy_destroy_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:241] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

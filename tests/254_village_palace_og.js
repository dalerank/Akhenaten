// OG Village Palace: one palace city-wide, treasury share table (weight 50),
// tax office needs palace. Markers:
//   [test-marker] palace_og_unique_ok
//   [test-marker] palace_og_share_alone_ok
//   [test-marker] palace_og_share_with_tax_ok
//   [test-marker] palace_og_tax_needs_palace_ok

var __test254_ok = false

function test254_fail(msg) {
    __log_info_native('[test:254] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:254] village palace OG')
    test_ensure_city_session('data/default.map')
    __test_set_treasury(5200)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    if (__test_city_has_palace()) {
        return test254_fail('map already has a palace')
    }

    var palace = __test_building_create(BUILDING_VILLAGE_PALACE, cx, cy)
    if (!palace) {
        return test254_fail('create village palace failed')
    }
    __test_city_buildings_update_tick()
    if (!__test_city_has_palace()) {
        return test254_fail('has_palace false after create')
    }

    // OG palace_placed: any other palace tier blocked as unique.
    if (!building_is_unique_built(BUILDING_VILLAGE_PALACE)
        || !building_is_unique_built(BUILDING_TOWN_PALACE)
        || !building_is_unique_built(BUILDING_CITY_PALACE)) {
        return test254_fail('unique across palace tiers failed')
    }
    __log_marker('palace_og_unique_ok')

    // Alone: weight 50/50 → full treasury on palace display field.
    __test_building_set_workers(palace, 0)
    __test_government_distribute_treasury()
    var alone = city.get_building(palace).tax_income_or_storage | 0
    if (alone !== 5200) {
        return test254_fail('alone share want 5200 got ' + alone)
    }
    __log_marker('palace_og_share_alone_ok')

    // With tax office: palace 50/52, tax 2/52 of 5200 → 5000 / 200.
    var tax = __test_building_create(BUILDING_TAX_COLLECTOR, cx + 8, cy)
    if (!tax) {
        return test254_fail('create tax office failed')
    }
    __test_government_distribute_treasury()
    var pshare = city.get_building(palace).tax_income_or_storage | 0
    var tshare = city.get_building(tax).tax_income_or_storage | 0
    if (pshare !== 5000) {
        return test254_fail('palace+tax palace share want 5000 got ' + pshare)
    }
    if (tshare !== 200) {
        return test254_fail('palace+tax tax share want 200 got ' + tshare)
    }
    __log_marker('palace_og_share_with_tax_ok')

    // Planner tax gate uses has_palace() — clears after palace is gone and tick runs.
    __test_destroy_buildings_of_type(BUILDING_VILLAGE_PALACE)
    __test_city_buildings_update_tick()
    if (__test_city_has_palace()) {
        return test254_fail('has_palace still true after destroy')
    }
    __log_marker('palace_og_tax_needs_palace_ok')

    __test254_ok = true
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'palace_og_unique_ok',
        'palace_og_share_alone_ok',
        'palace_og_share_with_tax_ok',
        'palace_og_tax_needs_palace_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:254] missing marker: ' + markers[i])
            return false
        }
    }
    return __test254_ok
}

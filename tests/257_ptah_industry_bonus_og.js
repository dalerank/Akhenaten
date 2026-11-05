// OG Ptah industry bonus: stone quarry checks for Ptah complex + altar itself
// (industry_ptah_altar_bonus via quarry produce_uptick) → +num_workers/2 per tick.
// Markers:
//   [test-marker] ptah_industry_bonus_ok

var __test257_ok = false

function run_test() {
    __log_info_native('[test:257] ptah industry bonus for stone quarry')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    terrain.add({ x: cx + 2, y: cy }, TERRAIN_ROCK)
    terrain.add({ x: cx + 2, y: cy + 1 }, TERRAIN_ROCK)
    __test_map_quarry_deposits_init()

    var bid = test_building_place(BUILDING_STONE_QUARRY, cx, cy)
    if (!bid) {
        bid = __test_building_create(BUILDING_STONE_QUARRY, cx, cy)
    }
    if (!bid) {
        __log_info_native('[test:257] stone quarry place/create failed')
        __test_signal_ready()
        return
    }

    __test_building_set_workers(bid, 8)
    __test_building_update_day(bid)
    if (__building_industry_progress(bid) != 1) {
        __log_info_native('[test:257] progress after update_day=' + __building_industry_progress(bid))
        __test_signal_ready()
        return
    }

    __test_city_industry_update_production()
    var after_base = __building_industry_progress(bid)
    // quarry uptick = max(1, 8/2) = 4 → progress 5
    if (after_base != 5) {
        __log_info_native('[test:257] base tick expected 5 got ' + after_base)
        __test_signal_ready()
        return
    }

    var cid = test_building_place(BUILDING_TEMPLE_COMPLEX_PTAH, -1, -1)
    var complex = city.get_temple_complex()
    if (!cid || !complex || complex.type != BUILDING_TEMPLE_COMPLEX_PTAH) {
        __log_info_native('[test:257] ptah complex place failed id=' + cid)
        __test_signal_ready()
        return
    }

    __test_city_industry_update_production()
    var after_complex = __building_industry_progress(bid)
    // no altar yet → still +4 only
    if (after_complex != 9) {
        __log_info_native('[test:257] complex-only tick expected 9 got ' + after_complex)
        __test_signal_ready()
        return
    }

    complex.temple_complex_upgrades = TEMPLE_COMPLEX_UPGRADE_ALTAR
    __test_city_industry_update_production()
    var after_altar = __building_industry_progress(bid)
    // +4 uptick + floor(8/2)=4 Ptah → +8 → progress 17
    if (after_altar != 17) {
        __log_info_native('[test:257] altar tick expected 17 got ' + after_altar)
        __test_signal_ready()
        return
    }

    __log_marker('ptah_industry_bonus_ok')
    __test257_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test257_ok && __test_find_inlog('[test-marker] ptah_industry_bonus_ok')
}

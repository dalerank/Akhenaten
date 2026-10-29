// FIG_IMMIGRANT vs OG (0x00489CA0 / 0x00458D00):
// - wait_ticks = 10 + (house.map_random_7bit & 0x7f)
// - invisible while waiting (action 0/8)
// - no road within radius 2 of house → die
// - cart_image always 0
// Markers:
//   [test-marker] immigrant_wait_ticks_ok
//   [test-marker] immigrant_wait_invisible_ok
//   [test-marker] immigrant_no_road_dies_ok
//   [test-marker] immigrant_no_cart_ok

var __test215_ok = {
    wait_ticks: false,
    wait_invisible: false,
    no_road_dies: false,
    no_cart: false
}

function grant_house_road(bid) {
    var b = city.get_building(bid)
    var t = __building_tile(bid)
    var dx
    for (dx = -1; dx <= b.size; dx++) {
        terrain.add({ x: t.x + dx, y: t.y - 1 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    b.has_road_access = true
}

function run_test() {
    __log_info_native('[test:215] immigrant OG behavior')
    test_ensure_city_session('data/default.map')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    // --- wait_ticks from house map_random_7bit; invisible on wait ---
    var house_a = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx - 10, cy - 10)
    if (!house_a) {
        __log_info_native('[test:215] house_a create failed')
        __test_signal_ready()
        return
    }
    grant_house_road(house_a)
    // Vacant lot needs room: give population 0 so population_room > 0 via model max
    var ha = city.get_building(house_a)
    if (ha && ha.dcast_house) {
        // ensure house accepts immigrants (crude hut with 0 pop still has room)
    }

    var fid_a = __test_create_immigrant(house_a, 2)
    if (!fid_a) {
        __log_info_native('[test:215] create_immigrant A failed')
        __test_signal_ready()
        return
    }

    var expected_wait = 10 + (__test_building_map_random_7bit(house_a) & 0x7f)
    var got_wait = __test_figure_get_wait_ticks(fid_a)
    if (got_wait == expected_wait) {
        __test215_ok.wait_ticks = true
        __log_info_native('[test-marker] immigrant_wait_ticks_ok')
    } else {
        __log_info_native('[test:215] wait_ticks got=' + got_wait + ' expected=' + expected_wait)
    }

    __test_figure_action_perform(fid_a)
    if (__test_figure_is_visible(fid_a) == 0
        && (__test_figure_get_action(fid_a) == ACTION_0_IMMIGRANT_CREATED
            || __test_figure_get_action(fid_a) == ACTION_8_RECALCULATE)) {
        __test215_ok.wait_invisible = true
        __log_info_native('[test-marker] immigrant_wait_invisible_ok')
    } else {
        __log_info_native('[test:215] wait invisible/action fail vis='
            + __test_figure_is_visible(fid_a) + ' action=' + __test_figure_get_action(fid_a))
    }

    // After wait ends with road: arriving, cart must stay 0
    __test_figure_set_wait_ticks(fid_a, 0)
    __test_figure_action_perform(fid_a)
    __test_figure_update_animation(fid_a)
    if (__test_figure_is_alive(fid_a)
        && __test_figure_get_action(fid_a) == ACTION_1_IMMIGRANT_ARRIVING
        && __test_figure_cart_image_id(fid_a) == 0) {
        __test215_ok.no_cart = true
        __log_info_native('[test-marker] immigrant_no_cart_ok')
    } else {
        __log_info_native('[test:215] arrive/cart fail alive=' + __test_figure_is_alive(fid_a)
            + ' action=' + __test_figure_get_action(fid_a)
            + ' cart=' + __test_figure_cart_image_id(fid_a))
    }

    // --- no road within radius 2 → die ---
    var house_b = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx + 12, cy + 12)
    if (!house_b) {
        __log_info_native('[test:215] house_b create failed')
        __test_signal_ready()
        return
    }
    // Intentionally no road around house_b
    var fid_b = __test_create_immigrant(house_b, 1)
    if (!fid_b) {
        __log_info_native('[test:215] create_immigrant B failed')
        __test_signal_ready()
        return
    }
    __test_figure_set_wait_ticks(fid_b, 0)
    __test_figure_action_perform(fid_b)
    if (!__test_figure_is_alive(fid_b)) {
        __test215_ok.no_road_dies = true
        __log_info_native('[test-marker] immigrant_no_road_dies_ok')
    } else {
        __log_info_native('[test:215] no-road immigrant still alive action='
            + __test_figure_get_action(fid_b))
    }

    __test_signal_ready()
}

function check_valid() {
    return __test215_ok.wait_ticks
        && __test215_ok.wait_invisible
        && __test215_ok.no_road_dies
        && __test215_ok.no_cart
}

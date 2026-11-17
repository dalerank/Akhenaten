// Locust flight vs OG figure/plagues.c figure_locust_action and Figure_model row 107:
//   10 hit points, no height (current_height is never set), the swarm routes with TERRAIN_USAGE_ANYWHERE
//   instead of flying cross country, uses the eating strip (group 691) while it eats the crop, keeps its
//   route over a save round trip, and dies at the end of its fly-off route.
// Markers:
//   [test-marker] locust_og_hp_ok
//   [test-marker] locust_og_no_height_ok
//   [test-marker] locust_og_route_ok
//   [test-marker] locust_og_saveload_ok
//   [test-marker] locust_og_eating_ok
//   [test-marker] locust_og_fly_off_ok

var ACTION_LOCUST_CREATED = 120
var ACTION_LOCUST_GOING_TO_FIELD = 121
var ACTION_LOCUST_EATING = 122
var ACTION_LOCUST_FLYING_OFF = 123
var TEST750_ANYWHERE = (typeof TERRAIN_USAGE_ANYWHERE === 'number') ? TERRAIN_USAGE_ANYWHERE : -2

function test750_fail(msg) {
    __log_info_native('[test:750] FAIL: ' + msg)
}

function test750_place_farm() {
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var shifts = [[0, 0], [6, 0], [0, 6], [-6, 0], [0, -6], [6, 6], [-6, -6], [12, 0], [0, 12]]
    for (var i = 0; i < shifts.length; i++) {
        var x = cx + shifts[i][0]
        var y = cy + shifts[i][1]
        test_prepare_terrain_patch(x + 1, y + 1, 5, TERRAIN_FLOODPLAIN)
        var farm = test_building_place(BUILDING_GRAIN_FARM, x, y)
        if (farm) {
            return farm
        }
    }
    return 0
}

function test750_locusts() {
    var ids = []
    for (var i = 1; i < 2000; i++) {
        if (__figure_is_valid(i) && __figure_get_type(i) == FIGURE_LOCUST) {
            ids.push(i)
        }
    }
    return ids
}

function test750_fire() {
    for (var month = 1; month <= 12; month++) {
        __test_plagues_set_locusts_countdown(-1)
        __test_locust_update_month(month)
        if (__test_plagues_locusts_countdown() == 2632) {
            return month
        }
    }
    return 0
}

function test750_count_in(ids, action) {
    var n = 0
    for (var i = 0; i < ids.length; i++) {
        if (__figure_is_valid(ids[i]) && __figure_get_action_state(ids[i]) == action) {
            n++
        }
    }
    return n
}

function test750_run() {
    test_reload_city_session('data/default.map')
    __scenario_building_allow(BUILDING_GRAIN_FARM, true)
    __test_set_treasury(500000)
    city.figures.remove_figures(FIGURE_LOCUST)

    if (__figure_get_static_params_property(FIGURE_LOCUST, 'max_damage') != 10) {
        test750_fail('max_damage=' + __figure_get_static_params_property(FIGURE_LOCUST, 'max_damage') + ' (want 10)')
    } else {
        __log_marker('locust_og_hp_ok')
    }

    var farm = test750_place_farm()
    if (!farm) {
        test750_fail('no farm placed')
        return
    }
    __building_farm_set_progress(farm, 2000)
    if (!test750_fire()) {
        test750_fail('locusts never fired')
        return
    }
    var ids = test750_locusts()
    if (ids.length != 9) {
        test750_fail('want 9 locusts, got ' + ids.length)
        return
    }
    var raised = 0
    for (var i = 0; i < ids.length; i++) {
        if (__test_figure_current_height(ids[i]) != 0) {
            raised = ids[i]
        }
    }
    if (raised) {
        test750_fail('locust ' + raised + ' height=' + __test_figure_current_height(raised) + ' (want 0)')
    } else {
        __log_marker('locust_og_no_height_ok')
    }

    var going = 0
    for (var t = 0; t < 400 && !going; t++) {
        __test_run_ticks(1)
        going = test750_count_in(ids, ACTION_LOCUST_GOING_TO_FIELD)
    }
    __test_run_ticks(3)
    var flyer = 0
    for (var j = 0; j < ids.length; j++) {
        if (__figure_is_valid(ids[j]) && __figure_get_action_state(ids[j]) == ACTION_LOCUST_GOING_TO_FIELD) {
            flyer = ids[j]
            break
        }
    }
    if (!flyer) {
        test750_fail('no locust left the spawn point')
        return
    }
    if (__test_figure_use_cross_country(flyer) != 0 || __test_figure_terrain_usage(flyer) != TEST750_ANYWHERE) {
        test750_fail('flight: cross_country=' + __test_figure_use_cross_country(flyer) + ' terrain_usage='
            + __test_figure_terrain_usage(flyer) + ' (want 0, ' + TEST750_ANYWHERE + ')')
    } else {
        __log_marker('locust_og_route_ok')
    }

    var save_name = 'test_750_locusts.svx'
    if (!__test_save_memory(save_name) || !__test_load_memory(save_name)) {
        __test_drop_memory_save(save_name)
        test750_fail('save round trip')
        return
    }
    __test_drop_memory_save(save_name)
    if (!__figure_is_valid(flyer) || __figure_get_type(flyer) != FIGURE_LOCUST || __test_locust_farm(flyer) != farm) {
        test750_fail('locust ' + flyer + ' lost after load')
        return
    }
    __log_marker('locust_og_saveload_ok')

    var eating = 0
    for (var k = 0; k < 1200 && eating < ids.length; k++) {
        __test_run_ticks(1)
        eating = test750_count_in(ids, ACTION_LOCUST_EATING)
    }
    if (eating != ids.length) {
        test750_fail('only ' + eating + ' of ' + ids.length + ' locusts reached the farm, countdown='
            + __test_plagues_locusts_countdown())
        return
    }
    var countdown = __test_plagues_locusts_countdown()
    var progress = __building_farm_progress(farm)
    var key = __figure_get_anim_key(ids[0])
    if (key != 'eating' || progress > countdown - 1000) {
        test750_fail('eating: anim=' + key + ' progress=' + progress + ' countdown=' + countdown)
    } else {
        __log_marker('locust_og_eating_ok')
    }

    __test_plagues_set_locusts_countdown(1001)
    __test_run_ticks(2)
    if (test750_count_in(ids, ACTION_LOCUST_FLYING_OFF) != ids.length) {
        test750_fail('fly off: flying=' + test750_count_in(ids, ACTION_LOCUST_FLYING_OFF))
        return
    }
    for (var m = 0; m < 1500 && test750_locusts().length > 0; m++) {
        __test_run_ticks(1)
    }
    if (test750_locusts().length != 0 || m < 10) {
        test750_fail('fly-off: alive=' + test750_locusts().length + ' after ' + m + ' ticks (want 0, at least 10 ticks of flight)')
        return
    }
    __log_marker('locust_og_fly_off_ok')
}

function run_test() {
    __log_info_native('[test:750] OG locust flight')
    try {
        test750_run()
    } catch (e) {
        test750_fail('exception: ' + e)
    }
    __test_signal_ready()
}

function check_valid() {
    var markers = ['locust_og_hp_ok', 'locust_og_no_height_ok', 'locust_og_route_ok', 'locust_og_saveload_ok',
        'locust_og_eating_ok', 'locust_og_fly_off_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:750] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    city.figures.remove_figures(FIGURE_LOCUST)
}

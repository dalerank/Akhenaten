// Locusts vs OG city/locusts.c, scenario_events.c:208-217, laborer.c:1231,1473, plagues.c figure_locust_action:
//   the event only sets the countdown to -1 (and -15 happiness); nothing happens until the month update
//   two months before the flood, then 9 locusts per farm, the farm loses its workers, countdown 2632;
//   locusts clamp the crop to countdown - 1000 and fly off at 1000; laborers skip farms while it runs;
//   the countdown survives a save round trip.
// Markers:
//   [test-marker] locusts_event_waits_ok
//   [test-marker] locusts_fire_before_flood_ok
//   [test-marker] locusts_eat_fly_off_ok
//   [test-marker] locusts_laborer_skips_farm_ok
//   [test-marker] locusts_saveload_ok

var ACTION_LOCUST_EATING = 122
var ACTION_LOCUST_FLYING_OFF = 123

function test550_fail(msg) {
    __log_info_native('[test:550] FAIL: ' + msg)
}

function test550_fire_month() {
    var flood_month = ((__test_floods_season() / 30) | 0) - 1
    if (flood_month < 0) {
        flood_month += 12
    }
    var month = flood_month - 2
    if (month <= 0) {
        month += 12
    }
    return month
}

function test550_place_farm(x, y) {
    test_prepare_terrain_patch(x + 1, y + 1, 5, TERRAIN_FLOODPLAIN)
    var farm = test_building_place(BUILDING_GRAIN_FARM, x, y)
    if (!farm) {
        farm = __test_building_create(BUILDING_GRAIN_FARM, x, y)
    }
    return farm
}

function test550_plague() {
    test_reload_city_session('data/default.map')
    if (!__scenario_building_allowed(BUILDING_GRAIN_FARM)) {
        __scenario_building_allow(BUILDING_GRAIN_FARM, true)
    }
    __test_set_treasury(500000)
    city.figures.remove_figures(FIGURE_LOCUST)
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var farm = test550_place_farm(cx, cy)
    if (!farm) {
        test550_fail('no farm')
        return 0
    }
    var hid = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, -1, -1)
    __test_house_set_population(hid, 10)
    __test_house_set_happiness(hid, 50)

    city.create_chain_event({ tag_id: 55001, type: EVENT_TYPE_LOCUSTS, amount: 1, trigger: EVENT_TRIGGER_ONCE }).execute()
    var happiness = __test_house_happiness(hid)
    if (__test_plagues_locusts_countdown() != -1 || __test_count_figures(FIGURE_LOCUST) != 0 || happiness != 35) {
        test550_fail('event: countdown=' + __test_plagues_locusts_countdown() + ' locusts='
            + __test_count_figures(FIGURE_LOCUST) + ' happiness=' + happiness + ' (want -1, 0, 35)')
        return 0
    }
    __test_plagues_tick(100)
    var fire = test550_fire_month()
    __test_locust_update_month(fire % 12 + 1)
    if (__test_plagues_locusts_countdown() != -1 || __test_count_figures(FIGURE_LOCUST) != 0) {
        test550_fail('fired in the wrong month ' + (fire % 12 + 1) + ' (fire month ' + fire + ')')
        return 0
    }
    __log_marker('locusts_event_waits_ok')

    city.get_building(farm).num_workers = 5
    __building_farm_set_progress(farm, 2000)
    __test_locust_update_month(fire)
    var locusts = __test_count_figures(FIGURE_LOCUST)
    var workers = city.get_building(farm).num_workers
    if (__test_plagues_locusts_countdown() != 2632 || locusts < 9 || locusts % 9 != 0 || workers != 0) {
        test550_fail('fire: countdown=' + __test_plagues_locusts_countdown() + ' locusts=' + locusts + ' workers=' + workers)
        return 0
    }
    var on_farm = 0
    for (var i = 1; i < 2000; i++) {
        if (__figure_is_valid(i) && __figure_get_type(i) == FIGURE_LOCUST && __test_locust_farm(i) == farm) {
            on_farm++
        }
    }
    if (on_farm != 9) {
        test550_fail('want 9 locusts for the farm, got ' + on_farm)
        return 0
    }
    __log_marker('locusts_fire_before_flood_ok')
    return farm
}

function test550_eating(farm) {
    var fid = 0
    for (var i = 1; i < 2000; i++) {
        if (__figure_is_valid(i) && __figure_get_type(i) == FIGURE_LOCUST && __test_locust_farm(i) == farm) {
            fid = i
            break
        }
    }
    __test_figure_set_action(fid, ACTION_LOCUST_EATING)
    __test_figure_action_perform(fid)
    var progress = __building_farm_progress(farm)
    if (progress != 2632 - 1000 || __figure_get_action_state(fid) != ACTION_LOCUST_EATING) {
        test550_fail('eating: progress=' + progress + ' (want 1632) action=' + __figure_get_action_state(fid))
        return
    }
    __test_plagues_set_locusts_countdown(1000)
    __test_figure_action_perform(fid)
    if (__building_farm_progress(farm) != 0 || __figure_get_action_state(fid) != ACTION_LOCUST_FLYING_OFF) {
        test550_fail('fly off: progress=' + __building_farm_progress(farm) + ' action=' + __figure_get_action_state(fid))
        return
    }
    __test_plagues_tick(10)
    if (__test_plagues_locusts_countdown() != 990) {
        test550_fail('countdown ticks: ' + __test_plagues_locusts_countdown())
        return
    }
    __log_marker('locusts_eat_fly_off_ok')
}

function test550_laborer() {
    test_reload_city_session('data/default.map')
    __scenario_building_allow(BUILDING_WORK_CAMP, true)
    __scenario_building_allow(BUILDING_GRAIN_FARM, true)
    __test_set_treasury(500000)
    city.floods.state = FLOOD_STATE_FARMABLE

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var camp = test_building_place(BUILDING_WORK_CAMP, cx - 12, cy)
    if (!camp) {
        camp = test_building_place(BUILDING_WORK_CAMP, -1, -1)
    }
    var farm = test550_place_farm(cx, cy)
    if (!camp || !farm) {
        test550_fail('laborer setup camp=' + camp + ' farm=' + farm)
        return
    }
    var camp_tile = __building_tile(camp)
    var laborer_tile = { x: camp_tile.x + 1, y: camp_tile.y }
    __test_make_road(laborer_tile.x, laborer_tile.y)
    __test_building_set_road_access(camp, laborer_tile.x, laborer_tile.y)
    var fb = city.get_building(farm)
    fb.num_workers = 0
    fb.distance_from_entry = 1
    var farm_tile = __building_tile(farm)
    __test_make_road(farm_tile.x, farm_tile.y)
    __test_make_road(farm_tile.x + 1, farm_tile.y)
    __test_building_set_road_access(farm, laborer_tile.x, laborer_tile.y)
    __test_map_routing_update_land()

    __test_plagues_set_locusts_countdown(500)
    var fid = __test_figure_create(FIGURE_LABORER, laborer_tile.x, laborer_tile.y)
    __test_figure_set_home_slot(fid, camp)
    var busy = __worker_find_work(fid) | 0
    if (busy == farm) {
        test550_fail('laborer took the farm while the locusts eat')
        return
    }
    __test_plagues_set_locusts_countdown(0)
    var fid2 = __test_figure_create(FIGURE_LABORER, laborer_tile.x, laborer_tile.y)
    __test_figure_set_home_slot(fid2, camp)
    var free = __worker_find_work(fid2) | 0
    if (free != farm) {
        test550_fail('laborer after the locusts want farm ' + farm + ' got ' + free + ' requested=' + __farm_requested_workers(farm)
            + ' floodplain=' + __map_terrain_is(__building_tile(farm), TERRAIN_FLOODPLAIN))
        return
    }
    __log_marker('locusts_laborer_skips_farm_ok')
}

function test550_saveload() {
    __test_plagues_set_locusts_countdown(-1)
    var save_name = 'test_550_locusts.svx'
    if (!__game_write_savegame(save_name)) {
        test550_fail('write savegame')
        return
    }
    __test_plagues_set_locusts_countdown(0)
    if (!__game_load_savegame(save_name)) {
        __game_delete_savegame(save_name)
        test550_fail('load savegame')
        return
    }
    __game_delete_savegame(save_name)
    if (__test_plagues_locusts_countdown() != -1) {
        test550_fail('after load countdown=' + __test_plagues_locusts_countdown())
        return
    }
    __log_marker('locusts_saveload_ok')
}

function run_test() {
    __log_info_native('[test:550] OG locusts')
    var farm = test550_plague()
    if (farm) {
        test550_eating(farm)
    }
    test550_laborer()
    test550_saveload()
    __test_signal_ready()
}

function check_valid() {
    var markers = ['locusts_event_waits_ok', 'locusts_fire_before_flood_ok', 'locusts_eat_fly_off_ok',
        'locusts_laborer_skips_farm_ok', 'locusts_saveload_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:550] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    city.figures.remove_figures(FIGURE_LOCUST)
}

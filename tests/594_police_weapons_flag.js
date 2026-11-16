// Remake police weapons (gameplay_change_police_weapons). Off: OG, the station never asks a storage yard for
// weapons. On: with no stock the station sends its constable to the nearest yard holding weapons (ACTION_74), the
// yard carts them to the station, the next constable takes one and the info window shows the stock.

var __test594_ok = false
var __test594_flag_prev = false
var __test594_boost_prev = false

function test594_finish() {
    game_features.set('gameplay_change_police_weapons', __test594_flag_prev)
    game_features.set('gameplay_enhanced_walker_spawn_boost', __test594_boost_prev)
    __test_signal_ready()
}

function test594_fail(msg) {
    __log_info_native('[test:594] FAIL: ' + msg)
    test594_finish()
}

function test594_spawn(bid) {
    city.get_building(bid).figure_spawn_delay = 0
    __test_building_spawn_figure(bid)
    return __test_building_figure_id(bid, 0)
}

function run_test() {
    __log_info_native('[test:594] police weapons flag')
    __test594_flag_prev = game_features.get('gameplay_change_police_weapons') === true
    __test594_boost_prev = game_features.get('gameplay_enhanced_walker_spawn_boost') === true
    game_features.set('gameplay_enhanced_walker_spawn_boost', false)
    game_features.set('gameplay_change_police_weapons', false)

    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var station = __test_building_create(BUILDING_POLICE_STATION, cx, cy)
    var yard = __test_building_create(BUILDING_STORAGE_YARD, cx + 4, cy + 2)
    if (!station || !yard) {
        test594_fail('create failed station=' + station + ' yard=' + yard)
        return
    }
    for (var dx = -2; dx < 10; dx++) {
        terrain.add({ x: cx + dx, y: cy + 1 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    __test_building_set_road_access(station, cx, cy + 1)
    __test_building_set_road_access(yard, cx + 4, cy + 1)
    city.get_building(station).distance_from_entry = 1
    city.get_building(yard).distance_from_entry = 2
    __test_building_set_workers(station, 6)
    var yb = city.get_building(yard)
    yb.num_workers = yb.max_workers > 0 ? yb.max_workers : 1
    if (!__test_storage_yard_add_resource(yard, RESOURCE_WEAPONS, 200)) {
        test594_fail('yard weapons add failed')
        return
    }
    var yard_weapons = __test_yards_stored(RESOURCE_WEAPONS)

    var fid = test594_spawn(station)
    if (!fid || __figure_get_action_state(fid) != 70) {
        test594_fail('flag off: constable must leave as OG ACTION_70, got ' + (fid ? __figure_get_action_state(fid) : 'none'))
        return
    }
    for (var i = 0; i < 5; i++) {
        __test_building_spawn_figure(yard)
    }
    if (__test_yards_stored(RESOURCE_WEAPONS) != yard_weapons || __test_building_figure_id(yard, 0)) {
        test594_fail('flag off: the yard must not cart weapons to the station')
        return
    }
    __test_show_tile_info(station)
    __test_pump_frames(5)
    var hidden = __test_info_ui_enabled('weapon_stored') == 0
    window_go_back()
    __test_pump_frames(2)
    if (!hidden) {
        test594_fail('flag off: info window must hide the weapons stock')
        return
    }
    __log_marker('test594_off')

    city.figures.remove_figures(FIGURE_CONSTABLE)
    __test_figures_update()
    game_features.set('gameplay_change_police_weapons', true)

    fid = test594_spawn(station)
    if (!fid || __figure_get_action_state(fid) != 74) {
        test594_fail('flag on: constable must go for weapons (ACTION_74), got ' + (fid ? __figure_get_action_state(fid) : 'none'))
        return
    }
    var returning = false
    for (var t = 0; t < 400 && !returning; t++) {
        __test_figure_action_perform(fid)
        returning = __figure_get_action_state(fid) == 73
    }
    if (!returning) {
        test594_fail('constable must reach the yard and turn back, state ' + __figure_get_action_state(fid))
        return
    }
    __log_marker('test594_errand')

    __test_building_spawn_figure(yard)
    var cart = __test_building_figure_id(yard, 0)
    if (!cart || __test_figure_resource(cart) != RESOURCE_WEAPONS) {
        test594_fail('yard must send a weapons cart, cart=' + cart)
        return
    }
    for (var c = 0; c < 1000 && city.get_building(station).stored_resource(RESOURCE_WEAPONS) == 0; c++) {
        __test_figure_action_perform(cart)
    }
    var stock = city.get_building(station).stored_resource(RESOURCE_WEAPONS)
    if (stock <= 0) {
        test594_fail('weapons cart must deliver to the station')
        return
    }
    __log_marker('test594_delivered')

    city.figures.remove_figures(FIGURE_CONSTABLE)
    __test_figures_update()
    fid = test594_spawn(station)
    if (!fid || __figure_get_action_state(fid) != 70) {
        test594_fail('stocked station must send a roaming constable')
        return
    }
    if (city.get_building(station).stored_resource(RESOURCE_WEAPONS) != stock - 1) {
        test594_fail('constable must take one weapon: ' + stock + ' -> ' + city.get_building(station).stored_resource(RESOURCE_WEAPONS))
        return
    }
    __log_marker('test594_take_one')

    __test_show_tile_info(station)
    __test_pump_frames(5)
    var shown = __test_info_ui_enabled('weapon_stored') == 1 && __test_info_ui_text('weapon_stored') == String(stock - 1)
    window_go_back()
    __test_pump_frames(2)
    if (!shown) {
        test594_fail('info window must show the weapons stock')
        return
    }
    __log_marker('test594_info')

    __test594_ok = true
    test594_finish()
}

function check_valid() {
    return __test594_ok
        && __test_find_inlog('[test-marker] test594_off')
        && __test_find_inlog('[test-marker] test594_errand')
        && __test_find_inlog('[test-marker] test594_delivered')
        && __test_find_inlog('[test-marker] test594_take_one')
        && __test_find_inlog('[test-marker] test594_info')
}

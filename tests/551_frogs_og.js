// Frogs vs OG city_disasters.c:178-268 city_frogs_start and animals_wild.c figure_frog_action:
//   countdown = amount * 816, houses from the top level down while their people stay within 65% of the city,
//   each gets a frog with a 50% chance at the nearest water/marsh; the frog walks (AMPHIBIA) to a road
//   by its house and into it: the people leave, the house is shut for the months left on the countdown.
// Markers:
//   [test-marker] frogs_spawn_at_water_ok
//   [test-marker] frogs_enter_house_ok
//   [test-marker] frogs_saveload_ok

var ACTION_FROG_ENTERING_HOUSE = 122

function test551_fail(msg) {
    __log_info_native('[test:551] FAIL: ' + msg)
}

function test551_frog_ids() {
    var ids = []
    for (var i = 1; i < 2000; i++) {
        if (__figure_is_valid(i) && __figure_get_type(i) == FIGURE_FROG) {
            ids.push(i)
        }
    }
    return ids
}

function test551_setup() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(500000)
    city.figures.remove_figures(FIGURE_FROG)
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var houses = []
    for (var i = 0; i < 20; i++) {
        var x = cx - 10 + i
        terrain.remove({ x: x, y: cy }, TERRAIN_WATER)
        var hid = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, x, cy)
        if (hid && __test_house_set_population(hid, 10) > 0) {
            houses.push(hid)
        }
        __test_make_road(x, cy + 1)
        terrain.add({ x: x, y: cy + 3 }, TERRAIN_WATER)
        terrain.add({ x: x, y: cy + 4 }, TERRAIN_WATER)
    }
    __test_map_routing_update_land()
    __test_map_routing_update_water()
    return houses
}

function run_test() {
    __log_info_native('[test:551] OG frogs')
    var houses = test551_setup()
    if (houses.length < 20) {
        test551_fail('placed only ' + houses.length + ' houses')
        __test_signal_ready()
        return
    }

    city.create_chain_event({ tag_id: 55101, type: EVENT_TYPE_FROGS, amount: 2, trigger: EVENT_TRIGGER_ONCE }).execute()
    var frogs = test551_frog_ids()
    if (__test_plagues_frogs_countdown() != 2 * 816 || frogs.length < 1 || frogs.length > 13) {
        test551_fail('start: countdown=' + __test_plagues_frogs_countdown() + ' frogs=' + frogs.length + ' (want 1632, 1..13)')
        __test_signal_ready()
        return
    }
    for (var i = 0; i < frogs.length; i++) {
        var tile = __figure_get_tile(frogs[i])
        var hid = __test_frog_house(frogs[i])
        if (!__map_terrain_is(tile, TERRAIN_WATER) || houses.indexOf(hid) < 0) {
            test551_fail('frog ' + frogs[i] + ' at ' + tile.x + ',' + tile.y + ' house=' + hid)
            __test_signal_ready()
            return
        }
    }
    __log_marker('frogs_spawn_at_water_ok')

    var fid = frogs[0]
    var house = __test_frog_house(fid)
    var entered = false
    for (var t = 0; t < 6000 && __figure_is_valid(fid); t++) {
        __test_figure_action_perform(fid)
        if (__figure_get_action_state(fid) == ACTION_FROG_ENTERING_HOUSE) {
            entered = true
        }
    }
    var h = city.get_house(house)
    // 1632 ticks = 2 months of 16 days.
    if (!entered || __figure_is_valid(fid) || h.population != 0 || h.frog_infest_days != 32) {
        test551_fail('enter: entered=' + entered + ' alive=' + __figure_is_valid(fid) + ' pop=' + h.population
            + ' infest_days=' + h.frog_infest_days)
        __test_signal_ready()
        return
    }
    __log_marker('frogs_enter_house_ok')

    var save_name = 'test_551_frogs.svx'
    var countdown = __test_plagues_frogs_countdown()
    if (__game_write_savegame(save_name) && __game_load_savegame(save_name)) {
        if (__test_plagues_frogs_countdown() == countdown && countdown > 0) {
            __log_marker('frogs_saveload_ok')
        } else {
            test551_fail('after load countdown=' + __test_plagues_frogs_countdown() + ' want ' + countdown)
        }
    } else {
        test551_fail('save/load failed')
    }
    __game_delete_savegame(save_name)
    __test_signal_ready()
}

function check_valid() {
    var markers = ['frogs_spawn_at_water_ok', 'frogs_enter_house_ok', 'frogs_saveload_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:551] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    city.figures.remove_figures(FIGURE_FROG)
}

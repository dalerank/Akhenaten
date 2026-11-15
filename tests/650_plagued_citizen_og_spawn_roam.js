// Plagued citizen vs OG city_disasters.c:100-117 city_health_start_plague_at_house and figure/plagues.c:37-94
// figure_plague_citizen_action: an outbreak sends ONE carrier from the house tile (action 8, wait_ticks 500,
// home = house); it walks cross-country, hidden, to the closest road within 2 tiles of the house (action 9),
// roams (action 10) and dies on its 500th roam tick; on the way it infects the populated houses within 2 tiles
// but not the empty ones; a house with no road within 2 tiles loses its carrier on the first tick.
// Markers:
//   [test-marker] plagued650_one_carrier_ok
//   [test-marker] plagued650_to_road_ok
//   [test-marker] plagued650_roam_ok
//   [test-marker] plagued650_infect_ok
//   [test-marker] plagued650_no_road_ok

var ACTION_8_PLAGUED_CREATED = 8
var ACTION_9_PLAGUED_GOING_TO_ROAD = 9
var ACTION_10_PLAGUED_ROAMING = 10

function t650_fail(msg) {
    __log_info_native('[test:650] FAIL: ' + msg)
}

function t650_carriers() {
    var ids = []
    for (var i = 1; i < 2000; i++) {
        if (__figure_is_valid(i) && __figure_get_type(i) == FIGURE_PLAGUED_CITIZEN) {
            ids.push(i)
        }
    }
    return ids
}

function t650_road(x0, y, x1) {
    if (!test_planner_enter_build_mode(BUILDING_ROAD)) {
        return false
    }
    city_planner.update(x1, y)
    city_planner.construction_start(x0, y)
    city_planner.construction_update(x1, y)
    city_planner.construction_finalize()
    test_planner_exit_build_mode()
    for (var x = x0; x <= x1; x++) {
        if (!terrain.is({ x: x, y: y }, TERRAIN_ROAD)) {
            return false
        }
    }
    return true
}

// The house tool does not report the building it creates: read it from the tile.
function t650_house(x, y, pop) {
    if (__building_at(x, y) || !test_planner_enter_build_mode(BUILDING_HOUSE_CRUDE_HUT)) {
        return 0
    }
    city_planner.update(x, y)
    if (city_planner.can_be_placed() != CAN_PLACE) {
        test_planner_exit_build_mode()
        return 0
    }
    city_planner.construction_start(x, y)
    city_planner.construction_update(x, y)
    city_planner.construction_finalize()
    test_planner_exit_build_mode()
    var bid = __building_at(x, y)
    if (!bid || __building_type(bid) != BUILDING_HOUSE_CRUDE_HUT) {
        return 0
    }
    __test_house_set_population(bid, pop)
    return bid
}

// Road row oy from ox to ox + 8; sick houses north of it at ox + 1 and ox + 7, a populated healthy house at
// ox + 4 south of the road and an empty house next to it.
function t650_layout() {
    var base = test_find_buildable_tile(BUILDING_HOUSE_CRUDE_HUT)
    if (!base) {
        return null
    }
    for (var tries = 0; tries < 6; tries++) {
        var ox = base.x - 4 + tries * 3
        var oy = base.y + tries * 3
        if (!t650_road(ox, oy, ox + 8)) {
            continue
        }
        var sick_a = t650_house(ox + 1, oy - 1, 20)
        var sick_b = t650_house(ox + 7, oy - 1, 20)
        var healthy = t650_house(ox + 4, oy + 1, 20)
        var empty = t650_house(ox + 5, oy + 1, 0)
        if (sick_a && sick_b && healthy && empty) {
            return { ox: ox, oy: oy, sick: [sick_a, sick_b], healthy: healthy, empty: empty }
        }
    }
    return null
}

function t650_road_near(x, y) {
    for (var dy = -2; dy <= 2; dy++) {
        for (var dx = -2; dx <= 2; dx++) {
            if (terrain.is({ x: x + dx, y: y + dy }, TERRAIN_ROAD)) {
                return true
            }
        }
    }
    return false
}

function t650_same(a, b) {
    return a.x == b.x && a.y == b.y
}

function run_test() {
    __log_info_native('[test:650] OG plagued citizen spawn and roam')
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)
    game.paused = true
    city.figures.remove_figures(FIGURE_PLAGUED_CITIZEN)

    var lay = t650_layout()
    if (!lay) {
        t650_fail('layout')
        __test_signal_ready()
        return
    }

    // The healthy house must not be picked by the outbreak: it only counts people of the sick ones.
    __test_house_set_population(lay.healthy, 0)
    __test_run_console_command('plague_start 40')
    __test_house_set_population(lay.healthy, 20)
    var ids = t650_carriers()
    if (ids.length != 1) {
        t650_fail('carriers after outbreak ' + ids.length + ', want 1')
        __test_signal_ready()
        return
    }
    var fid = ids[0]
    var home = city.get_figure(fid).home_building_id
    var ht = __building_tile(home)
    var ft = __figure_get_tile(fid)
    if ((home != lay.sick[0] && home != lay.sick[1]) || !t650_same(ft, ht) || __test_figure_get_action(fid) != ACTION_8_PLAGUED_CREATED
        || __test_figure_get_wait_ticks(fid) != 500) {
        t650_fail('carrier home=' + home + ' tile=' + ft.x + ',' + ft.y + ' house=' + ht.x + ',' + ht.y
            + ' action=' + __test_figure_get_action(fid) + ' wait=' + __test_figure_get_wait_ticks(fid))
        __test_signal_ready()
        return
    }
    __log_marker('plagued650_one_carrier_ok')

    __test_figure_action_perform(fid)
    var dest = __figure_get_destination_tile(fid)
    if (__test_figure_get_action(fid) != ACTION_9_PLAGUED_GOING_TO_ROAD || __test_figure_is_visible(fid) != 0
        || !terrain.is(dest, TERRAIN_ROAD) || Math.abs(dest.y - ht.y) > 2 || Math.abs(dest.x - ht.x) > 2) {
        t650_fail('to road: action=' + __test_figure_get_action(fid) + ' visible=' + __test_figure_is_visible(fid)
            + ' dest=' + dest.x + ',' + dest.y)
        __test_signal_ready()
        return
    }
    var walk = 0
    while (__figure_is_valid(fid) && __test_figure_get_action(fid) == ACTION_9_PLAGUED_GOING_TO_ROAD && walk < 200) {
        __test_figure_action_perform(fid)
        walk++
    }
    ft = __figure_get_tile(fid)
    if (__test_figure_get_action(fid) != ACTION_10_PLAGUED_ROAMING || !t650_same(ft, dest)) {
        t650_fail('arrive: action=' + __test_figure_get_action(fid) + ' tile=' + ft.x + ',' + ft.y + ' ticks=' + walk)
        __test_signal_ready()
        return
    }
    __log_marker('plagued650_to_road_ok')

    var roam = 0
    while (__figure_is_valid(fid) && roam < 600) {
        __test_figure_action_perform(fid)
        roam++
    }
    if (__figure_is_valid(fid) || roam != 500) {
        t650_fail('roam ended after ' + roam + ' ticks, want 500')
        __test_signal_ready()
        return
    }
    __log_marker('plagued650_roam_ok')

    if (!__test_building_has_plague(lay.healthy) || __test_building_has_plague(lay.empty)) {
        t650_fail('infect: healthy=' + __test_building_has_plague(lay.healthy) + ' empty=' + __test_building_has_plague(lay.empty))
        __test_signal_ready()
        return
    }
    __log_marker('plagued650_infect_ok')

    // A house with no road within 2 tiles: the carrier dies on its first tick.
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)
    game.paused = true
    city.figures.remove_figures(FIGURE_PLAGUED_CITIZEN)
    var lone = 0
    var base = test_find_buildable_tile(BUILDING_HOUSE_CRUDE_HUT)
    for (var tries = 0; base && !lone && tries < 6; tries++) {
        var lx = base.x + tries * 5
        if (!t650_road_near(lx, base.y)) {
            lone = t650_house(lx, base.y, 20)
        }
    }
    if (!lone) {
        t650_fail('lone house')
        __test_signal_ready()
        return
    }
    __test_run_console_command('plague_start 40')
    ids = t650_carriers()
    if (ids.length != 1) {
        t650_fail('lone house carriers ' + ids.length + ', want 1')
        __test_signal_ready()
        return
    }
    __test_figure_action_perform(ids[0])
    if (__figure_is_valid(ids[0])) {
        t650_fail('carrier of a house without road still alive')
        __test_signal_ready()
        return
    }
    __log_marker('plagued650_no_road_ok')
    __test_signal_ready()
}

function check_valid() {
    var markers = ['plagued650_one_carrier_ok', 'plagued650_to_road_ok', 'plagued650_roam_ok', 'plagued650_infect_ok',
        'plagued650_no_road_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:650] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    city.figures.remove_figures(FIGURE_PLAGUED_CITIZEN)
}

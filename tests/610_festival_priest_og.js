// Festival priest vs OG building_figure_helpers.c building_festival_spawn_celebrants and walkers.c
// figure_festival_priest_action:
//   size * 10 celebrants shared 15/20/30/35% by schools+libraries / manors+estates / temples / venues+schools;
//   a group's share its working buildings cannot fill goes to the next group. Each comes out at its building's
//   road access, takes the building's walker slot, walks the roads to the square's middle (+2,+2), then picks
//   random tiles on the 5x5 square (any terrain) and dies after 10 arrivals. Its look follows the home building.
// Markers:
//   [test-marker] festival_priest_spawn_og_ok
//   [test-marker] festival_priest_trips_og_ok
//   [test-marker] festival_priest_saveload_ok

var ACTION_CREATED = 8
var ACTION_PICK_SPOT = 9
var ACTION_WALKING = 10
var ACTION_ARRIVED = 11

var t610 = {}

function t610_fail(msg) {
    __log_info_native('[test:610] FAIL: ' + msg)
}

function t610_priests() {
    var ids = []
    for (var i = 1; i < 2000; i++) {
        if (__test_figure_is_alive(i) && __figure_get_type(i) == FIGURE_FESTIVAL_PRIEST) {
            ids.push(i)
        }
    }
    return ids
}

function t610_place(type, x, y) {
    var bid = test_building_place(type, x, y)
    if (bid > 0) {
        __test_building_set_workers(bid, 20)
    }
    return bid
}

function t610_setup() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(1000000)
    __camera_rotate_north()
    city.figures.remove_figures(FIGURE_FESTIVAL_PRIEST)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    for (var x = cx - 30; x <= cx + 30; x++) {
        terrain.add({ x: x, y: cy }, TERRAIN_ROAD)
    }
    var sx = cx + 20
    for (var d = -2; d <= 2; d++) {
        terrain.add({ x: sx + 2, y: cy + d }, TERRAIN_ROAD)
    }
    t610.square_tile = { x: sx, y: cy - 2 }
    t610.square = test_building_place(BUILDING_FESTIVAL_SQUARE, sx, cy - 2)

    t610.ra = t610_place(BUILDING_TEMPLE_RA, cx - 28, cy + 1)
    t610.osiris = t610_place(BUILDING_TEMPLE_OSIRIS, cx - 24, cy + 1)
    t610.juggler = t610_place(BUILDING_JUGGLER_SCHOOL, cx - 20, cy + 1)
    t610.conservatory = t610_place(BUILDING_CONSERVATORY, cx - 16, cy + 1)
    t610.scribal = t610_place(BUILDING_SCRIBAL_SCHOOL, cx - 12, cy + 1)
    __test_map_routing_update_land()
    __test_city_buildings_update_tick()
    return t610.square > 0 && t610.ra > 0 && t610.osiris > 0 && t610.juggler > 0 && t610.conservatory > 0
        && t610.scribal > 0
}

function t610_check_spawn(want) {
    var ids = t610_priests()
    var homes = {}
    for (var i = 0; i < ids.length; i++) {
        var fid = ids[i]
        var home = __figure_get_home_building_id(fid)
        homes[home] = fid
        var look = __test_festival_priest_look(fid)
        if (want[home] === undefined || look != want[home]) {
            t610_fail('priest ' + fid + ' home ' + home + ' look ' + look + ' want ' + want[home])
            return false
        }
        if (__figure_get_action_state(fid) != ACTION_CREATED || __test_building_figure_id(home, 0) != fid) {
            t610_fail('priest ' + fid + ' action ' + __figure_get_action_state(fid) + ' slot0 '
                + __test_building_figure_id(home, 0))
            return false
        }
        var tile = __figure_get_tile(fid)
        if (!__map_terrain_is(tile, TERRAIN_ROAD)) {
            t610_fail('priest ' + fid + ' not on a road at ' + tile.x + ',' + tile.y)
            return false
        }
    }
    var want_count = 0
    for (var k in want) {
        want_count++
        if (homes[k] === undefined) {
            t610_fail('no priest from building ' + k)
            return false
        }
    }
    if (ids.length != want_count) {
        t610_fail('spawned ' + ids.length + ' want ' + want_count)
        return false
    }
    return true
}

function t610_walk(fid, until_arrivals) {
    for (var t = 0; t < 20000 && __figure_is_valid(fid); t++) {
        var before = __figure_get_action_state(fid)
        __test_figure_action_perform(fid)
        if (!__figure_is_valid(fid)) {
            break
        }
        var after = __figure_get_action_state(fid)
        if (after == ACTION_ARRIVED && before != ACTION_ARRIVED) {
            var tile = __figure_get_tile(fid)
            t610.arrivals++
            if (t610.arrivals == 1) {
                if (tile.x != t610.square_tile.x + 2 || tile.y != t610.square_tile.y + 2) {
                    t610_fail('first arrival at ' + tile.x + ',' + tile.y + ' want the square middle')
                    return false
                }
            } else if (tile.x < t610.square_tile.x || tile.x >= t610.square_tile.x + 5
                || tile.y < t610.square_tile.y || tile.y >= t610.square_tile.y + 5) {
                t610_fail('arrival ' + t610.arrivals + ' off the square at ' + tile.x + ',' + tile.y)
                return false
            }
            if (t610.arrivals == until_arrivals) {
                return true
            }
        }
    }
    return true
}

function run_test() {
    __log_info_native('[test:610] festival priest OG')
    if (!t610_setup()) {
        t610_fail('setup: square ' + t610.square + ' ra ' + t610.ra + ' osiris ' + t610.osiris + ' juggler '
            + t610.juggler + ' conservatory ' + t610.conservatory + ' scribal ' + t610.scribal)
        __test_signal_ready()
        return
    }

    // Size 5: schools 0 (15% of 5), manors 1 with none working -> carried, temples 1 + 1 = 2, venues 1:
    // the first of juggler school / conservatory by building id.
    __test_festival_spawn_celebrants(5)
    var want = {}
    want[t610.ra] = FIGURE_PRIEST
    want[t610.osiris] = FIGURE_PRIEST
    want[Math.min(t610.juggler, t610.conservatory)] = (t610.juggler < t610.conservatory) ? FIGURE_JUGGLER : FIGURE_MUSICIAN
    if (!t610_check_spawn(want)) {
        __test_signal_ready()
        return
    }
    city.figures.remove_figures(FIGURE_FESTIVAL_PRIEST)

    // A small festival (10): schools 1, temples 2 + carried, venues 2.
    __city_festival.planned_size = FESTIVAL_SMALL
    __city_festival.planned_god = GOD_RA
    __test_festival_execute()
    want = {}
    want[t610.ra] = FIGURE_PRIEST
    want[t610.osiris] = FIGURE_PRIEST
    want[t610.juggler] = FIGURE_JUGGLER
    want[t610.conservatory] = FIGURE_MUSICIAN
    want[t610.scribal] = FIGURE_TEACHER
    if (!t610_check_spawn(want)) {
        __test_signal_ready()
        return
    }
    var keys = { }
    keys[t610.ra] = 'priest_ra_walk'
    keys[t610.osiris] = 'priest_osiris_walk'
    keys[t610.juggler] = 'juggler_walk'
    keys[t610.conservatory] = 'musician_walk'
    keys[t610.scribal] = 'teacher_walk'
    var ids = t610_priests()
    for (var i = 0; i < ids.length; i++) {
        __test_figure_action_perform(ids[i])
        __test_figure_update_animation(ids[i])
        var key = __figure_get_anim_key(ids[i])
        var home = __figure_get_home_building_id(ids[i])
        if (key != keys[home] || __test_festival_priest_trips(ids[i]) != 10
            || __figure_get_action_state(ids[i]) != ACTION_WALKING) {
            t610_fail('priest ' + ids[i] + ' anim ' + key + ' want ' + keys[home] + ' trips '
                + __test_festival_priest_trips(ids[i]) + ' action ' + __figure_get_action_state(ids[i]))
            __test_signal_ready()
            return
        }
    }
    __log_marker('festival_priest_spawn_og_ok')

    var fid = __test_building_figure_id(t610.ra, 0)
    t610.arrivals = 0
    if (!t610_walk(fid, 4) || t610.arrivals != 4) {
        t610_fail('walk to 4 arrivals: ' + t610.arrivals)
        __test_signal_ready()
        return
    }

    var trips = __test_festival_priest_trips(fid)
    var save_name = 'test_610_festival_priest.svx'
    if (!__test_save_memory(save_name) || !__test_load_memory(save_name)) {
        t610_fail('save/load')
        __test_signal_ready()
        return
    }
    __test_drop_memory_save(save_name)
    if (!__figure_is_valid(fid) || __test_festival_priest_trips(fid) != trips
        || __test_festival_priest_look(fid) != FIGURE_PRIEST || __figure_get_action_state(fid) != ACTION_ARRIVED) {
        t610_fail('after load trips ' + __test_festival_priest_trips(fid) + ' want ' + trips + ' look '
            + __test_festival_priest_look(fid) + ' action ' + __figure_get_action_state(fid))
        __test_signal_ready()
        return
    }
    __log_marker('festival_priest_saveload_ok')

    if (!t610_walk(fid, 99) || __figure_is_valid(fid) || t610.arrivals != 10) {
        t610_fail('trips: arrivals ' + t610.arrivals + ' alive ' + __figure_is_valid(fid))
        __test_signal_ready()
        return
    }
    __log_marker('festival_priest_trips_og_ok')
    __test_signal_ready()
}

function check_valid() {
    var markers = ['festival_priest_spawn_og_ok', 'festival_priest_saveload_ok', 'festival_priest_trips_og_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:610] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    city.figures.remove_figures(FIGURE_FESTIVAL_PRIEST)
}

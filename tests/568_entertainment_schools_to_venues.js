// Each entertainment school sends its performer to a staffed venue on its road, and the arrival starts that
// venue's show (32 days): juggler -> pavilion / bandstand, musician -> pavilion / bandstand, dancer -> pavilion.
// Markers:
//   [test-marker] t568_ok
//   [test-marker] t568_fail:<what>

var __t568_failed = false

function t568_fail(what) {
    __log_info_native('[test-marker] t568_fail:' + what)
    __t568_failed = true
}

function t568_case(name, school_type, performer, field, venue_type) {
    if (!test_reload_city_session('data/default.map')) {
        return t568_fail(name + ':map_load')
    }
    __test_set_treasury(1000000)
    __camera_rotate_north()

    var ox = ((__scenario_map.width / 2) | 0) - 10
    var oy = ((__scenario_map.height / 2) | 0) - 20
    var venue_roads = venue_type == BUILDING_PAVILLION
        ? [[2, 0], [2, 1], [2, 2], [0, 3], [1, 3], [2, 3], [3, 3]]
        : [[0, 0], [0, 1], [0, 2], [1, 1], [2, 1]]
    for (var i = 0; i < venue_roads.length; i++) {
        terrain.add({ x: ox + venue_roads[i][0], y: oy + venue_roads[i][1] }, TERRAIN_ROAD)
    }
    var road_y = venue_type == BUILDING_PAVILLION ? oy + 3 : oy + 1
    for (var x = ox - 14; x < ox; x++) {
        terrain.add({ x: x, y: road_y }, TERRAIN_ROAD)
    }
    var venue = test_building_place(venue_type, ox, oy)
    var school = test_building_place(school_type, ox - 12, road_y + 1)
    if (!venue || !school) {
        return t568_fail(name + ':place')
    }
    __test_update_road_network()
    __test_check_kingdome_access()

    // The map has no workforce and the test road does not reach the map entry: labor and the road network
    // update would leave the venue unstaffed at distance 0, which performers skip. Hold both every tick.
    var keep_open = function() {
        __test_building_set_workers(venue, 30)
        __test_building_set_workers(school, 30)
        __test_building_set_distance_from_entry(venue, 5)
    }

    var before = __test_count_figures(performer)
    for (var k = 0; k < 120 && __test_count_figures(performer) == before; k++) {
        keep_open()
        __test_building_spawn_figure(school)
    }
    if (__test_count_figures(performer) == before) {
        return t568_fail(name + ':no_performer')
    }

    var arrived = -1
    for (var t = 0; t < 400 && arrived < 0; t++) {
        keep_open()
        __test_run_ticks(1)
        if (city.get_entertainment_building(venue)[field] > 0) {
            arrived = t
        }
    }
    var days = city.get_entertainment_building(venue)[field]
    __log_info_native('[test:568] ' + name + ' arrived after ' + arrived + ' ticks, ' + field + '=' + days)
    if (arrived < 0) {
        t568_fail(name + ':no_show')
    } else if (days != 32) {
        t568_fail(name + ':days_' + days)
    }
}

function run_test() {
    t568_case('juggler_pavilion', BUILDING_JUGGLER_SCHOOL, FIGURE_JUGGLER, 'juggler_visited', BUILDING_PAVILLION)
    t568_case('musician_pavilion', BUILDING_CONSERVATORY, FIGURE_MUSICIAN, 'musician_visited', BUILDING_PAVILLION)
    t568_case('dancer_pavilion', BUILDING_DANCE_SCHOOL, FIGURE_DANCER, 'dancer_visited', BUILDING_PAVILLION)
    t568_case('juggler_bandstand', BUILDING_JUGGLER_SCHOOL, FIGURE_JUGGLER, 'juggler_visited', BUILDING_BANDSTAND)
    t568_case('musician_bandstand', BUILDING_CONSERVATORY, FIGURE_MUSICIAN, 'musician_visited', BUILDING_BANDSTAND)

    test_reload_city_session('data/default.map')
    if (!__t568_failed) {
        __log_info_native('[test-marker] t568_ok')
    }
    __test_signal_ready()
}

function check_valid() {
    return !__t568_failed && __test_find_inlog('[test-marker] t568_ok')
}

// Build previews drawn from JS (booth plaza) must use the city view's render scale (its zoom), like the
// queued ghost images, or the two parts of the preview come apart whenever the zoom is not 100%.
// Markers:
//   [test-marker] t569_ok
//   [test-marker] t569_fail:<what>

var __t569_failed = false

function t569_fail(what) {
    __log_info_native('[test-marker] t569_fail:' + what)
    __t569_failed = true
}

function t569_run() {
    if (!test_reload_city_session('data/default.map')) {
        return t569_fail('map_load')
    }
    __camera_rotate_north()

    var x = ((__scenario_map.width / 2) | 0) - 30
    var y = ((__scenario_map.height / 2) | 0) - 20
    var roads = [[1, 0], [0, 1], [1, 1], [1, 2], [2, 1]]
    for (var i = 0; i < roads.length; i++) {
        terrain.add({ x: x + roads[i][0], y: y + roads[i][1] }, TERRAIN_ROAD)
    }

    if (!test_planner_enter_build_mode(BUILDING_BOOTH)) {
        return t569_fail('build_mode')
    }
    city_planner.update(x, y)
    // 150% zoom.
    var city_scale = 1 / 1.5
    var drawn = __test_city_planner_draw(city_scale)
    test_planner_exit_build_mode()

    __log_info_native('[test:569] city scale ' + city_scale + ' js preview scale ' + drawn)
    if (drawn == 0) {
        t569_fail('preview_not_drawn')
    } else if (Math.abs(drawn - city_scale) > 0.001) {
        t569_fail('scale:' + drawn)
    }
}

function run_test() {
    t569_run()
    if (!__t569_failed) {
        __log_info_native('[test-marker] t569_ok')
    }
    __test_signal_ready()
}

function check_valid() {
    return !__t569_failed && __test_find_inlog('[test-marker] t569_ok')
}

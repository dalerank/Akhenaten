// The build preview shows what the placement check decided: where the planner can place the building the preview
// has no red tile, and where it cannot (CAN_NOT_PLACE) the preview shows red. Monuments and venues check their site
// once per update and the preview only reads that result.
// Markers:
//   [test-marker] t572_ok
//   [test-marker] t572_fail:<what>

var __t572_failed = false

function t572_fail(what) {
    __log_info_native('[test-marker] t572_fail:' + what)
    __t572_failed = true
}

var __t572_types = [
    'BUILDING_SPHINX', 'BUILDING_CAESAREUM', 'BUILDING_PHAROS_LIGHTHOUSE', 'BUILDING_MAUSOLEUM',
    'BUILDING_SUN_TEMPLE', 'BUILDING_ALEXANDRIA_LIBRARY', 'BUILDING_BANDSTAND', 'BUILDING_PAVILLION'
]

function t572_probe(name, x, y) {
    city_planner.update(x, y)
    var can = city_planner.can_be_placed()
    var red = __test_planner_preview_red_tiles()
    __log_info_native('[test:572] ' + name + ' at ' + x + ',' + y + ' can=' + can + ' red=' + red)
    if (can == CAN_PLACE && red > 0) {
        t572_fail(name + ':red_but_placeable:' + x + ',' + y)
    } else if (can == CAN_NOT_PLACE && red == 0) {
        t572_fail(name + ':no_red_but_blocked:' + x + ',' + y)
    }
    return can
}

function t572_run() {
    if (!test_reload_city_session('data/default.map')) {
        return t572_fail('load')
    }
    __camera_rotate_north()
    __test_set_treasury(50000)
    var placeable = 0
    for (var i = 0; i < __t572_types.length; i++) {
        var type = eval(__t572_types[i])
        var free = test_find_buildable_tile(type)
        if (!test_planner_enter_build_mode(type)) {
            t572_fail(__t572_types[i] + ':build_mode')
            continue
        }
        if (free && t572_probe(__t572_types[i], free.x, free.y) == CAN_PLACE) {
            placeable++
        }
        t572_probe(__t572_types[i], 2, 2)
        test_planner_exit_build_mode()
    }
    if (placeable == 0) {
        t572_fail('nothing_placeable')
    }
}

function run_test() {
    t572_run()
    if (!__t572_failed) {
        __log_info_native('[test-marker] t572_ok')
    }
    __test_signal_ready()
}

function check_valid() {
    return !__t572_failed && __test_find_inlog('[test-marker] t572_ok')
}

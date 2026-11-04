// FIGURE_SEAGULLS: OG figure_seagulls_action (0x0049B390) — fishing-point ghost stub.
// create_flotsam places one at each scenario fishing point; no draw/AI beyond flags.
// Markers:
//   [test-marker] seagulls_create_ok   alive, invisible, at the fishing tile
//   [test-marker] seagulls_action_ok   action keeps invisible + any/cross-country
//   [test-marker] seagulls_with_points_ok  fishing_points.create spawns gulls + jumping fish

var __test246_ok = false

function test246_fail(msg) {
    __log_info_native('[test:246] ' + msg)
    __test_signal_ready()
}

function test246_count_type(ftype) {
    var n = 0
    for (var i = 1; i < 2000; i++) {
        if (__figure_is_valid(i) && __figure_get_type(i) == ftype && __test_figure_is_alive(i) == 1) {
            n++
        }
    }
    return n
}

function run_test() {
    __log_info_native('[test:246] seagulls')
    test_reload_city_session('data/default.map')
    city.figures.remove_figures(FIGURE_SEAGULLS)
    city.figures.remove_figures(FIGURE_FISHING_POINT)

    var fid = test_figure_create(FIGURE_SEAGULLS, 10, 10)
    if (!fid) {
        return test246_fail('create failed')
    }
    if (__test_figure_is_alive(fid) != 1 || __test_figure_is_visible(fid) != 0) {
        return test246_fail('want alive+invisible after create, alive=' + __test_figure_is_alive(fid)
            + ' visible=' + __test_figure_is_visible(fid))
    }
    var tile = __figure_get_tile(fid)
    if (tile.x != 10 || tile.y != 10) {
        return test246_fail('tile want 10,10 got ' + tile.x + ',' + tile.y)
    }
    __log_marker('seagulls_create_ok')

    __test_figure_set_visible(fid, 1)
    __test_figure_action_perform(fid)
    if (__test_figure_is_visible(fid) != 0 || __test_figure_is_alive(fid) != 1) {
        return test246_fail('action want stay invisible+alive, visible=' + __test_figure_is_visible(fid)
            + ' alive=' + __test_figure_is_alive(fid))
    }
    __log_marker('seagulls_action_ok')

    city.figures.remove_figures(FIGURE_SEAGULLS)
    city.figures.remove_figures(FIGURE_FISHING_POINT)
    __test_clear_scenario_fishing_points()
    __test_set_scenario_fishing_point(0, 12, 14)
    __test_set_scenario_fishing_point(1, 20, 22)
    __test_fishing_points_create()

    var gulls = test246_count_type(FIGURE_SEAGULLS)
    var fish = test246_count_type(FIGURE_FISHING_POINT)
    if (gulls != 2 || fish != 2) {
        return test246_fail('create want 2 seagulls + 2 fishing points, got gulls=' + gulls + ' fish=' + fish)
    }
    __log_marker('seagulls_with_points_ok')

    __test_fishing_points_clear()
    if (test246_count_type(FIGURE_SEAGULLS) != 0 || test246_count_type(FIGURE_FISHING_POINT) != 0) {
        return test246_fail('clear left figures behind')
    }

    __test246_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!__test246_ok) {
        return false
    }
    var markers = ['seagulls_create_ok', 'seagulls_action_ok', 'seagulls_with_points_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:246] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

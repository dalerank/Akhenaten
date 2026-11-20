// With the residency atlas on, a zoomed-out city (zoom above 100%, so sprites are drawn below their size
// with linear filtering) must still draw from the atlas page: more than half of the frame's draws must
// come from the atlas page once it has filled. Needs Pharaoh art; without it (--no-resource) the city
// draws only a few dozen sprites and the check is skipped.
// Markers:
//   [test-marker] t529_ok resident=<n> draws=<n> batches=<n> flushes=<n>
//   [test-marker] t529_fail resident=<n> draws=<n>
//   [test-marker] t529_art_skipped:no_resource

var __t529_ok = false

function run_test() {
    if (!test_reload_city_session('data/default.map')) {
        __test_signal_ready()
        return
    }
    var bid = __test_building_create(BUILDING_STONEMASONS_GUILD, -1, -1)
    if (!bid) {
        __test_signal_ready()
        return
    }

    var zoom_prev = game_features.get('gameui_zoom')
    game_features.set('gameui_zoom', true)
    __test_camera_center_building(bid)
    __zoom_set(180)
    __test_pump_frames(30)

    if (__test_render_draws() < 1000) {
        __log_info_native('[test-marker] t529_art_skipped:no_resource')
        __t529_ok = true
    } else {
        var draws = __test_render_draws()
        var resident = __test_render_resident_draws()
        if (draws > 0 && resident * 2 > draws) {
            __log_info_native('[test-marker] t529_ok resident=' + resident + ' draws=' + draws +
                ' batches=' + __test_render_batches() + ' flushes=' + __test_render_flushes())
            __t529_ok = true
        } else {
            __log_info_native('[test-marker] t529_fail resident=' + resident + ' draws=' + draws)
        }
    }

    __zoom_set(100)
    game_features.set('gameui_zoom', zoom_prev)
    __test_signal_ready()
}

function check_valid() {
    return __t529_ok
}

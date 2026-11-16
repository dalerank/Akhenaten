// Zoom wheel steps stay on zoom_default + k * zoom_speed even after clamping at zoom_min,
// so scrolling back always reaches exactly 100% (other values take the downscaled draw path).

var __test483_ok = false

function test483_fail(msg) {
    __log_info_native('[test:483] FAIL ' + msg)
    __test_signal_ready()
}

function test483_run_mode(smooth) {
    game_features.set('gameui_zoom', true)
    game_features.set('gameui_smooth_zoom', smooth)
    __zoom_set(100)
    __test_pump_frames(5)

    var cx = (screen.width / 2) | 0
    var cy = (screen.height / 2) | 0
    for (var i = 0; i < 4; i++) {
        __test_mouse_wheel(cx, cy, 1)
    }
    __test_pump_frames(30)
    var low = __zoom_target()
    if (low != 25) {
        return 'smooth=' + smooth + ': zoom in to the limit gave ' + low + ', want 25'
    }

    for (var j = 0; j < 3; j++) {
        __test_mouse_wheel(cx, cy, -1)
    }
    __test_pump_frames(30)
    var back = __zoom_target()
    if (back != 100) {
        return 'smooth=' + smooth + ': three steps back gave ' + back + ', want 100'
    }
    return ''
}

function run_test() {
    __log_info_native('[test:483] zoom wheel returns to default')
    test_reload_city_session('data/default.map')
    __test_pump_frames(10)

    var modes = [true, false]
    for (var i = 0; i < modes.length; i++) {
        var err = test483_run_mode(modes[i])
        if (err) {
            return test483_fail(err)
        }
    }
    __log_marker('zoom_wheel_returns_to_default')

    game_features.set('gameui_zoom', false)
    game_features.set('gameui_smooth_zoom', false)
    __zoom_set(100)
    __test483_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test483_ok && __test_find_inlog('[test-marker] zoom_wheel_returns_to_default')
}

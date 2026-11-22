// Every editor window draws through UI commands and render records: nothing reaches the device
// while the window draws, before ui::flush_commands. Counted by render_stats over the last frame.
// Markers:
//   [test-marker] editor_draws_through_commands_ok
//   [test-marker] editor_draws_through_commands_skipped:no_resource

var TEST586_WINDOWS = [
    ['map', 0],
    ['attributes', 0],
    ['allowed_buildings', 0],
    ['build_menu', 0],
    ['build_menu', 3],
    ['build_menu', 6],
    ['demand_changes', 0],
    ['edit_demand_change', 0],
    ['edit_invasion', 0],
    ['edit_price_change', 0],
    ['edit_request', 0],
    ['empire', 0],
    ['invasions', 0],
    ['price_changes', 0],
    ['requests', 0],
    ['special_events', 0],
    ['start_year', 0],
    ['starting_conditions', 0],
    ['win_criteria', 0],
]

var TEST586_TOOLS = [['grass', 0], ['road', 10], ['entry_point', 15], ['native_hut', 21], ['access_ramp', 9]]

function test586_fail(msg) {
    __log_info_native('[test:586] FAIL ' + msg)
    __test_signal_ready()
}

function test586_immediate(label) {
    __test_pump_frames(3)
    var immediate = __test_render_window_immediate_draws()
    __log_info_native('[test:586] ' + label + ' draws=' + __test_render_draws() + ' immediate=' + immediate)
    return immediate
}

function run_test() {
    __log_info_native('[test:586] editor draws through commands')

    if (!game.init_editor()) {
        return test586_fail('init_editor failed')
    }
    __test_editor_fill_events()
    if (!__test_editor_show_window('map', 0)) {
        return test586_fail('map window did not open')
    }
    __test_pump_frames(3)
    if (!__test_render_draws()) {
        __log_marker('editor_draws_through_commands_skipped:no_resource')
        __test_signal_ready()
        return
    }

    var failed = []
    for (var i = 0; i < TEST586_WINDOWS.length; i++) {
        var w = TEST586_WINDOWS[i]
        if (!__test_editor_show_window(w[0], w[1])) {
            return test586_fail('window ' + w[0] + ' did not open')
        }
        if (test586_immediate(w[0] + ':' + w[1])) {
            failed.push(w[0] + ':' + w[1])
        }
    }

    __test_editor_show_window('map', 0)
    __test_mouse_move(300, 300)
    for (var t = 0; t < TEST586_TOOLS.length; t++) {
        __test_editor_set_tool(TEST586_TOOLS[t][1])
        __test_mouse_move(300 + t, 300)
        if (test586_immediate('tool ' + TEST586_TOOLS[t][0])) {
            failed.push('tool ' + TEST586_TOOLS[t][0])
        }
    }

    if (failed.length) {
        return test586_fail('immediate draws in ' + failed.join(', '))
    }
    __log_marker('editor_draws_through_commands_ok')
    __test_signal_ready()
}

function check_valid() {
    return !!__test_find_inlog('[test-marker] editor_draws_through_commands_ok')
        || !!__test_find_inlog('[test-marker] editor_draws_through_commands_skipped:no_resource')
}

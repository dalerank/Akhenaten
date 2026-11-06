// Main-menu Free play opens the all-missions picker in e_scenario_selected mode.

function free_play_button_pos() {
    return {
        x: Math.floor(screen.width / 2),
        y: Math.floor(screen.height / 2) - 100 + 40 * 2 + 12,
    };
}

function run_test() {
    var p = free_play_button_pos();
    __log_info_native('[test:241] click free_play at (' + p.x + ', ' + p.y + ')');
    __test_mouse_click(p.x, p.y);
    __test_pump_frames(8);

    if (scenario.scmode == e_scenario_selected) {
        __log_info_native('[test-marker] free_play_scmode_selected');
    } else {
        __log_info_native('[test:241] bad scmode=' + scenario.scmode);
    }

    if (window_scenario_selection.free_play) {
        __log_info_native('[test-marker] free_play_flag_set');
    }

    if (window_scenario_selection.individual_missions) {
        __log_info_native('[test-marker] free_play_individual_list');
    }

    __test_signal_ready();
}

function check_valid() {
    return __test_find_inlog('[test-marker] window_show:window_scenario_selection_free_play')
        && __test_find_inlog('[test-marker] free_play_scmode_selected')
        && __test_find_inlog('[test-marker] free_play_flag_set')
        && __test_find_inlog('[test-marker] free_play_individual_list');
}

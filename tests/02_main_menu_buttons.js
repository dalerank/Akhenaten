// Clicks the main menu buttons (except `continue_game` per request and
// `quit_game` which would terminate the process), verifies that each opens
// the expected sub-window, and right-clicks to go back to the main menu.

var BUTTONS = [
    { name: "select_player", i: 1, window_id: "window_player_selection" },
    { name: "show_records",  i: 2, window_id: "records_window" },
    { name: "show_mods",     i: 4, window_id: "mods_window" },
];

function button_click_pos(i) {
    return {
        x: Math.floor(screen.width / 2),
        y: Math.floor(screen.height / 2) - 100 + 40 * i + 12,
    };
}

function go_back_pos() {
    return { x: Math.floor(screen.width / 2), y: 50 };
}

function click_one_button(b) {
    var p = button_click_pos(b.i);
    __log_info_native('[test:02] click ' + b.name + ' at (' + p.x + ', ' + p.y + ')');
    __test_mouse_click(p.x, p.y);
    __test_pump_frames(5);
    var g = go_back_pos();
    __log_info_native('[test:02] right-click at (' + g.x + ', ' + g.y + ') to go back');
    __test_mouse_right_click(g.x, g.y);
    __test_pump_frames(5);
}

function run_test() {
    __log_info_native('[test:02] screen size = ' + screen.width + 'x' + screen.height);
    for (var i = 0; i < BUTTONS.length; i++) {
        click_one_button(BUTTONS[i]);
    }
    __test_signal_ready();
}

function check_valid() {
    var log = __test_read_log_file();
    var all_ok = true;
    for (var i = 0; i < BUTTONS.length; i++) {
        var marker = '[test-marker] window_show:' + BUTTONS[i].window_id;
        if (log.indexOf(marker) < 0) {
            __log_info_native('[test:02] missing marker: ' + marker);
            all_ok = false;
        }
    }
    return all_ok;
}

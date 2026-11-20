// ED5: custom-map play loads Maps/*.meta.js price/demand before scenario_*_change_init().
// Markers:
//   [test-marker] editor_price_demand_meta_play_ok

function run_test() {
    __log_info_native('[test:093] editor price/demand meta play')

    if (!game.init_editor()) {
        __log_info_native('[test:093] init_editor failed')
        __test_signal_ready()
        return
    }

    if (!__test_editor_price_demand_meta_play()) {
        __log_info_native('[test:093] editor_price_demand_meta_play failed')
        __test_signal_ready()
        return
    }

    __log_marker('editor_price_demand_meta_play_ok')
    __test_signal_ready()
}

function check_valid() {
    return !!__test_find_inlog('[test-marker] editor_price_demand_meta_play_ok')
}

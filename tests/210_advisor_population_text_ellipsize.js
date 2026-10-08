// Population advisor info panel: long lines must end with "..." when they overflow
// the row width, and the ellipsized text must still fit on screen.
// Markers:
//   [test-marker] advisor_info_ellipsize_short_ok
//   [test-marker] advisor_info_ellipsize_long_ok
//   [test-marker] advisor_info_ellipsize_width_ok
//   [test-marker] advisor_info_click_popup_ok
//   [test-marker] advisor_info_close_btn_ok
//   [test-marker] advisor_info_click_full_no_popup_ok

function run_test() {
    __log_info_native('[test:210] advisor population info ellipsize')

    if (typeof advisor_population_text_ellipsize !== 'function') {
        __log_info_native('[test:210] helper missing')
        __test_signal_ready()
        return
    }

    var short = "A jelenlegi lakóhelyek befogadóképessége: 12"
    var out_short = advisor_population_text_ellipsize(short)
    if (out_short !== short) {
        __log_info_native('[test:210] short text changed: ' + out_short)
        __test_signal_ready()
        return
    }
    __log_marker('advisor_info_ellipsize_short_ok')

    var long = "Összességében emberek érkeznek, vagy szeretnének érkezni a városunkba. "
        + "Az alacsony bérek csökkentik a városunkba érkező bevándorlást."
    var out_long = advisor_population_text_ellipsize(long)
    if (out_long === long || out_long.substring(out_long.length - 3) !== "...") {
        __log_info_native('[test:210] long text not ellipsized: ' + out_long)
        __test_signal_ready()
        return
    }
    __log_marker('advisor_info_ellipsize_long_ok')

    var w_full = __ui_text_width(long, FONT_NORMAL_WHITE_ON_DARK)
    var w_out = __ui_text_width(out_long, FONT_NORMAL_WHITE_ON_DARK)
    if (w_out >= w_full) {
        __log_info_native('[test:210] ellipsized width ' + w_out + ' not below full ' + w_full)
        __test_signal_ready()
        return
    }
    __log_marker('advisor_info_ellipsize_width_ok')

    // Click on a truncated line opens a popup with the full text.
    if (typeof advisor_population_window_on_info_line_click !== 'function'
        || typeof ui.show_ok !== 'function') {
        __log_info_native('[test:210] click handler missing')
        __test_signal_ready()
        return
    }
    advisor_population_window._info_panel_full_lines = [short, long]
    advisor_population_window._info_panel_lines = [short, out_long]
    advisor_population_window.graph_order = 0
    advisor_population_window_on_info_line_click({ user_data: 1 })
    if (!ui.window_is('window_popup_dialog_ok')) {
        __log_info_native('[test:210] popup did not open for truncated line')
        __test_signal_ready()
        return
    }
    __log_marker('advisor_info_click_popup_ok')

    // The ok popup has an X close button (bottom-right, like building windows)
    // instead of the old "right click to continue" hint text.
    if (typeof window_popup_dialog_ok !== 'object' || !window_popup_dialog_ok.ui
        || !window_popup_dialog_ok.ui.btn_close) {
        __log_info_native('[test:210] popup layout missing btn_close')
        __test_signal_ready()
        return
    }
    __log_marker('advisor_info_close_btn_ok')
    window_go_back()

    // Untruncated line must not open a popup.
    advisor_population_window_on_info_line_click({ user_data: 0 })
    if (ui.window_is('window_popup_dialog_ok')) {
        __log_info_native('[test:210] popup opened for untruncated line')
        __test_signal_ready()
        return
    }
    __log_marker('advisor_info_click_full_no_popup_ok')

    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog("[test-marker] advisor_info_ellipsize_width_ok")
        && __test_find_inlog("[test-marker] advisor_info_click_popup_ok")
        && __test_find_inlog("[test-marker] advisor_info_close_btn_ok")
        && __test_find_inlog("[test-marker] advisor_info_click_full_no_popup_ok")
}

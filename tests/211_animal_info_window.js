// Figure info windows that inherit handlers from a parent [es=ParentType] tag
// (animals and enemies) must show the real figure name/class instead of the raw
// ${figure.name} / ${figure.class_name} template text.
//
// Regression: window_info_background and figure init were dispatched with
// ui.event() only (no parent fallback), so the animal/enemy windows never
// replaced their label templates — only their buttons worked.
//
// Markers:
//   [test-marker] figure_info_window_parent_fallback_ok

function test_211_check_window(label, bid, figure_type) {
    var tile = __building_tile(bid)
    var fig = test_figure_create(figure_type, tile.x, tile.y)
    if (!fig) {
        __log_info_native('[test:211] ' + label + ': figure create failed')
        return false
    }
    test_figure_set_speed(fig, 0)

    // Let the city draw once so main_cached_pos is computed; the info-window
    // figure radius check uses that pixel position.
    __test_pump_frames(3)

    __test_show_tile_info(bid)
    __test_pump_frames(10)

    var name = __test_info_ui_text('name')
    var typename = __test_info_ui_text('typename')
    var figs = __object_info_figure_count()
    // The big image must be the figure's real portrait (set by the parent
    // handler), not the default config image shown when setup never ran.
    // Animals resolve it via get_image(offset=f.type); enemies via their own
    // params.big_image — use the same lookup each window's setup performs.
    var expected_img = 0
    if (figure_type == FIGURE_ENEMY_EGYPTIAN_SPEAR) {
        expected_img = city.get_figure(fig).params.first_img('big_image')
    } else {
        var img = get_image({ pack: PACK_UNLOADED, id: 25, offset: figure_type })
        expected_img = img ? img.tid : 0
    }
    var got_img = __test_info_ui_image('bigimage')
    __log_info_native('[test:211] ' + label + ' window figcount=' + figs
        + ' name="' + name + '" typename="' + typename + '" bigimage_tid=' + got_img + ' expected=' + expected_img)

    if (figs <= 0 || !name || !typename) {
        __log_info_native('[test:211] ' + label + ': FAIL empty name/typename/figcount')
        window_go_back()
        return false
    }
    if (name.indexOf('${') != -1 || typename.indexOf('${') != -1) {
        __log_info_native('[test:211] ' + label + ': FAIL raw ${...} template leaked into info window')
        window_go_back()
        return false
    }
    if (got_img != expected_img) {
        __log_info_native('[test:211] ' + label + ': FAIL bigimage tid ' + got_img + ' != expected ' + expected_img)
        window_go_back()
        return false
    }

    window_go_back()
    __test_pump_frames(2)
    return true
}

function run_test() {
    __log_info_native('[test:211] figure info window parent fallback')
    test_ensure_city_session('data/default.map')

    var ok = true

    // Building only gives us a tile for __test_show_tile_info.
    var bid = __test_building_create(BUILDING_WORK_CAMP, -1, -1)
    if (!bid) {
        __log_info_native('[test:211] __test_building_create failed')
        __test_signal_ready()
        return
    }
    ok = test_211_check_window('animal', bid, FIGURE_BIRDS) && ok

    var tile = __building_tile(bid)
    var cx = tile.x + 6
    var cy = tile.y
    var bid2 = __test_building_create(BUILDING_WORK_CAMP, cx, cy)
    if (!bid2) {
        __log_info_native('[test:211] second building create failed')
        __test_signal_ready()
        return
    }
    ok = test_211_check_window('enemy', bid2, FIGURE_ENEMY_EGYPTIAN_SPEAR) && ok

    if (ok) {
        __log_marker('figure_info_window_parent_fallback_ok')
    }

    __test_signal_ready()
}

function check_valid() {
    if (!__test_find_inlog('[test-marker] figure_info_window_parent_fallback_ok')) {
        __log_info_native('[test:211] missing marker figure_info_window_parent_fallback_ok')
        return false
    }
    return true
}

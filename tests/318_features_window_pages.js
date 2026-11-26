var T318_EXPECTED = [
    { group: "interface", feature: "gameui_sidebar_info" },
    { group: "map_view", feature: "gameui_zoom" },
    { group: "graphics_sound", feature: "gameui_flat_buildings" },
    { group: "game", feature: "gameopt_unlock_all_campaigns" },
    { group: "fixes", feature: "gameplay_fix_immigration" },
    { group: "city", feature: "gameplay_change_global_labour" },
    { group: "services", feature: "gameplay_change_school_walkers" },
    { group: "industry", feature: "gameplay_change_soil_depletion" },
    { group: "storage_trade", feature: "gameplay_dynamic_granaries" },
    { group: "walkers", feature: "gameplay_change_follower_runaway" },
    { group: "military", feature: "gameplay_enable_extra_forts" },
    { group: "enhanced", feature: "gameplay_enhanced_flood_basins" }
]

function t318_group_index(id) {
    for (var g = 0; g < game_features.group_count(); g++) {
        if (game_features.group_id(g) === id)
            return g
    }
    return -1
}

function t318_tab_index(title) {
    var tabs = window_features_tabs()
    for (var t = 0; t < tabs.length; t++) {
        if (window_features.pages[tabs[t]].title === title)
            return t
    }
    return -1
}

function t318_page_lists(feature) {
    var page = window_features.pages[window_features.page]
    for (var i = 0; i < page.features.length; i++) {
        if (page.features[i].key === feature)
            return true
    }
    return false
}

function t318_check_groups() {
    var seen = {}
    for (var g = 0; g < game_features.group_count(); g++) {
        if (game_features.group_id(g) === "other") {
            __log_info_native('[test:318] FAIL group other is not empty')
            return false
        }
        for (var i = 0; i < game_features.group_size(g); i++) {
            var name = game_features.group_feature(g, i)
            if (seen[name]) {
                __log_info_native('[test:318] FAIL ' + name + ' is in two groups')
                return false
            }
            seen[name] = true
        }
    }
    for (var f = 0; f < game_features.count; f++) {
        var fname = game_features.name(f)
        if (typeof game_features.get(fname) !== "boolean" || !game_features.text(fname))
            continue
        if (!seen[fname]) {
            __log_info_native('[test:318] FAIL ' + fname + ' is in no group')
            return false
        }
    }
    return true
}

function t318_click_tab(tab) {
    var wpos = window_features_centered_pos()
    var p = wpostab(tab)
    __test_mouse_click(wpos[0] + p.x + 88, wpos[1] + p.y + 10)
    __test_pump_frames(3)
}

function run_test() {
    if (t318_check_groups()) {
        __log_info_native('[test:318] groups cover every toggleable feature once')
    }

    window_show_by_id("window_features")
    __test_pump_frames(5)

    var ok = 0
    for (var e = 0; e < T318_EXPECTED.length; e++) {
        var exp = T318_EXPECTED[e]
        var g = t318_group_index(exp.group)
        if (g < 0) {
            __log_info_native('[test:318] FAIL no group ' + exp.group)
            continue
        }
        var tab = t318_tab_index(game_features.group_title(g))
        if (tab < 0) {
            __log_info_native('[test:318] FAIL no tab for ' + exp.group)
            continue
        }
        t318_click_tab(tab)
        var page = window_features.pages[window_features.page]
        if (page.first !== window_features.page || window_features.page !== window_features_tabs()[tab]) {
            __log_info_native('[test:318] FAIL tab ' + exp.group + ' click shows page ' + window_features.page)
            continue
        }
        if (!t318_page_lists(exp.feature)) {
            __log_info_native('[test:318] FAIL tab ' + exp.group + ' does not list ' + exp.feature)
            continue
        }
        ok++
    }
    if (ok === T318_EXPECTED.length) {
        __log_info_native('[test:318] every tab lists its flag')
    }

    window_go_back()
    __test_pump_frames(2)
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test:318] groups cover every toggleable feature once')
        && __test_find_inlog('[test:318] every tab lists its flag')
}

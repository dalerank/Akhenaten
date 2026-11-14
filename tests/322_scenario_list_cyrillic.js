// #613: the mission selection list drew Russian titles as '?'.
function scenario_list_cyrillic_check() {
    if (!__game_language_set_current("ru")) {
        throw "could not switch language to ru"
    }

    window_scenario_selection.individual_missions = false
    window_scenario_selection.free_play = true
    window_scenario_selection.campaign_sub_dialog = -1
    window_show_by_id("window_scenario_selection")
    __test_pump_frames(5)
    __test_draw_frames(2)

    // Free play lists every mission config, so it needs no campaign data from --no-resource.
    var skip = {}
    for (var c = 0; c < custom_missions.length; c++) {
        skip[custom_missions[c].mission_id] = true
    }
    var expected = []
    for (var sid = 0; sid < 100; sid++) {
        if (!skip[sid] && get_mission_config(sid) !== undefined) {
            expected.push(mission_selection_title(sid))
        }
    }
    if (expected.length === 0) {
        throw "no free play missions"
    }

    var cyrillic = 0
    for (var j = 0; j < expected.length; j++) {
        var drawn = __test_window_list_draw_text("window_scenario_selection", "scenario_map_list", j)
        __log_info_native("[test:322] row " + j + " expected='" + expected[j] + "' drawn='" + drawn + "'")
        if (drawn !== expected[j]) {
            throw "row " + j + " draws '" + drawn + "' instead of '" + expected[j] + "'"
        }
        if (drawn.indexOf("?") >= 0 && expected[j].indexOf("?") < 0) {
            throw "row " + j + " has '?': " + drawn
        }
        if (/[Ѐ-ӿ]/.test(drawn)) {
            cyrillic++
        }
    }
    if (cyrillic === 0) {
        throw "no Cyrillic mission titles in the ru list"
    }
}

function run_test() {
    var prev_lang = __game_language_current()
    try {
        scenario_list_cyrillic_check()
        __log_marker("scenario_list_cyrillic_ok")
    } finally {
        window_scenario_selection.free_play = false
        __game_language_set_current(prev_lang && prev_lang !== "" ? prev_lang : "en")
    }
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog("[test-marker] scenario_list_cyrillic_ok")
}

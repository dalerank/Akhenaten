// #709: Single cities title must not fall through to history message 199 ("Bazaar")
// when campaign_scenario_id is -1 (map not in custom_missions).

function run_test() {
    var ok = true;

    try {
        var neg = mission_selection_title(-1);
        if (neg === "Bazaar") {
            __log_info_native("[cmapseltitle] mission_selection_title(-1) still 'Bazaar'");
            ok = false;
        }
        if (neg !== "No title") {
            __log_info_native("[cmapseltitle] mission_selection_title(-1) expected 'No title', got '" + neg + "'");
            ok = false;
        }
    } catch (e) {
        __log_info_native("[cmapseltitle] mission_selection_title(-1) threw: " + e);
        ok = false;
    }

    try {
        var a = custom_map_selection_title("Unreliant.map");
        var b = custom_map_selection_title("Maps/Unreliant.map");
        var c = custom_map_selection_title("Unreliant");
        if (a !== "Unreliant" || b !== "Unreliant" || c !== "Unreliant") {
            __log_info_native("[cmapseltitle] strip bad: '" + a + "' / '" + b + "' / '" + c + "'");
            ok = false;
        }
    } catch (e) {
        __log_info_native("[cmapseltitle] custom_map_selection_title threw: " + e);
        ok = false;
    }

    __log_info_native(ok ? "[cmapseltitle] ok" : "[cmapseltitle] fail");
    __test_signal_ready();
}

function check_valid() {
    return __test_find_inlog("[cmapseltitle] ok");
}

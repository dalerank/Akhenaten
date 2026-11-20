// Verifies selection_title for all ported campaign missions (0–10).

var PORTED_CAMPAIGN_MISSION_TITLES = {
    0: "Nubt",
    1: "Thinis",
    2: "Perwadjyt",
    3: "Nekhen",
    4: "Mennefer",
    5: "Timna",
    6: "Behdet",
    7: "Abydos",
    8: "Selima",
    9: "Abu",
    10: "Saqqara"
};

function run_test() {
    var ok = true;

    for (var id in PORTED_CAMPAIGN_MISSION_TITLES) {
        var expected = PORTED_CAMPAIGN_MISSION_TITLES[id];
        try {
            var title = mission_selection_title(id);
            if (title !== expected) {
                __log_info_native("[seltitles] mission " + id
                    + " bad: expected '" + expected + "', got '" + title + "'");
                ok = false;
            }
        } catch (e) {
            __log_info_native("[seltitles] mission " + id + " threw: " + e);
            ok = false;
        }
    }

    __log_info_native(ok ? "[seltitles] ok" : "[seltitles] fail");
    __test_signal_ready();
}

function check_valid() {
    return __test_find_inlog("[seltitles] ok");
}

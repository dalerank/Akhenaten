// Regression test for the campaign scenario-selection crash (#545 / PR #547).
//
// Campaign steps can reference scenario ids that have no JS mission config yet
// (only a subset of missions are ported). get_mission_config() returns undefined
// for those; the selection list used to dereference config.selection_title and
// crash with a TypeError. mission_selection_title() now guards that and returns
// "No title" instead.
//
// Data-less unit check: an unported id must yield "No title" and must not throw.

function run_test() {
    var ok = true;

    try {
        var title = mission_selection_title(999); // no mission config
        if (title !== "No title") {
            __log_info_native("[selguard] bad: got '" + title + "'");
            ok = false;
        }
    } catch (e) {
        __log_info_native("[selguard] threw: " + e);
        ok = false;
    }

    __log_info_native(ok ? "[selguard] ok" : "[selguard] fail");
    __test_signal_ready();
}

function check_valid() {
    return __test_find_inlog("[selguard] ok");
}

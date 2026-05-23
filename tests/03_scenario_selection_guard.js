// Regression test for the campaign scenario-selection crash (#545 / PR #547).
//
// Campaign steps can reference scenario ids that have no JS mission config yet
// (only a subset of missions are ported). get_mission_config() returns undefined
// for those; the selection list used to dereference config.selection_title and
// crash with a TypeError. mission_selection_title() now guards that and returns
// "No title" instead.
//
// This is a data-less unit check (the full window path needs mission1.pak, which
// is absent under --no-resource), so it exercises the guard function directly:
// an unported id must yield "No title" and must not throw.

function run_test() {
    try {
        var title = mission_selection_title(999); // 999 has no mission config
        __log_info_native(title === "No title"
            ? "[selguard] ok"
            : "[selguard] bad: got '" + title + "'");
    } catch (e) {
        __log_info_native("[selguard] threw: " + e);
    }
    __test_signal_ready();
}

function check_valid() {
    return __test_read_log_file().indexOf("[selguard] ok") >= 0;
}

// Goal lines must not use '@' (invisible Julius prefix) — missing glyph became '?'.

function run_test() {
    var line = scenario_info_goal_line(65, 44, 129)
    var ok = line.indexOf("@") < 0 && line.indexOf("?") < 0 && line.indexOf("65") >= 0
    __log_info_native(ok
        ? "[goal-line] ok: " + line
        : "[goal-line] fail: " + line)
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog("[goal-line] ok")
}

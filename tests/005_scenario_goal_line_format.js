// Goal lines must not use '@' (invisible Julius prefix) — missing glyph became '?'.
// Map-selection must omit monuments rating (Pharaoh 0x0041E5C0 skips label 0x83).

function run_test() {
    var line = scenario_info_goal_line(65, 44, 129)
    var ok = line.indexOf("@") < 0 && line.indexOf("?") < 0 && line.indexOf("65") >= 0
    __log_info_native(ok
        ? "[goal-line] ok: " + line
        : "[goal-line] fail: " + line)

    // Bridges-style: monuments rating 13 alone. Selection panel must not print it.
    __win_criteria.culture.enabled = false
    __win_criteria.prosperity.enabled = false
    __win_criteria.kingdom.enabled = false
    __win_criteria.population.enabled = false
    __win_criteria.housing_count.enabled = false
    __win_criteria.housing_level.enabled = false
    __win_criteria.monuments.enabled = true
    __win_criteria.monuments.goal = 13

    var mon_ok = scenario.monuments_goal == 13
    var lines = scenario_info_collect_goal_lines()
    var joined = lines.join("|")
    var mon_label = __loc(44, 131)
    var no_mon_line = lines.length == 0 && joined.indexOf(mon_label) < 0
    __log_info_native(mon_ok && no_mon_line
        ? "[goal-line] no-monument-rating ok: mon=" + scenario.monuments_goal
        : "[goal-line] no-monument-rating fail: [" + joined + "] mon=" + scenario.monuments_goal
            + " label=" + mon_label)

    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog("[goal-line] ok")
        && __test_find_inlog("[goal-line] no-monument-rating ok")
}

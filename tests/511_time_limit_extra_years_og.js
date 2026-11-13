// OG mission time rules (city/kingdom.c city_victory_check, widget/city_hud.c): a time limit gets 7 more years on
// Very Easy and 2 on Easy, a survival time none. Goals met before a time limit runs out win even in its last year;
// survival needs the goals met at its end year and waits until then; with no goals a time limit only loses. The
// time limit's defeat comes without the popup from Easy up, with it on Very Easy and for survival. The remake's
// gameplay_fix_editor_events keeps its own rule (a time limit loses even with the goals met).
// Markers:
//   [test-marker] time_extra_years_ok
//   [test-marker] time_goals_rules_ok
//   [test-marker] time_defeat_popup_ok
//   [test-marker] time_fix_editor_events_ok

var t511 = {}

function test511_set_difficulty(d) {
    for (var i = 0; i < 5; i++) {
        __game_decrease_difficulty()
    }
    for (var j = 0; j < d; j++) {
        __game_increase_difficulty()
    }
}

function test511_restore() {
    test_win_criteria_restore(t511.criteria)
    game.simtime.year = t511.year
    test511_set_difficulty(t511.difficulty)
    game_features.gameplay_fix_editor_events = t511.fix_editor_events
    city.mission.fired_message_shown = t511.fired
}

function test511_fail(msg) {
    __log_info_native('[test:511] FAIL ' + msg)
    test511_restore()
    __test_signal_ready()
}

function test511_setup(goal_met, time_limit, survival) {
    var wc = __win_criteria
    wc.population.enabled = goal_met !== null
    wc.population.goal = goal_met ? 0 : 1000000
    wc.time_limit.enabled = time_limit
    wc.time_limit.years = 5
    wc.survival_time.enabled = survival
    wc.survival_time.years = 5
    __test_scenario_init_max_year()
}

// [goal met (null: no goal), time limit, survival, years past the end year (negative: before it), state]
var T511_CASES = [
    [true, true, false, 0, 1],
    [true, true, false, -1, 1],
    [false, true, false, 0, -1],
    [false, true, false, -1, 0],
    [null, true, false, -1, 0],
    [null, true, false, 0, -1],
    [true, false, true, -1, 0],
    [true, false, true, 0, 1],
    [false, false, true, 0, -1],
    [false, false, true, -1, 0],
]

function run_test() {
    __log_info_native('[test:511] OG time limit extra years and end rules')
    test_ensure_city_session('data/default.map')

    t511 = {
        criteria: test_win_criteria_snapshot(),
        year: game.simtime.year,
        difficulty: game.difficulty,
        fix_editor_events: game_features.gameplay_fix_editor_events,
        fired: city.mission.fired_message_shown,
    }
    game_features.gameplay_fix_editor_events = false
    city.victory.reasons = {}
    var wc = __win_criteria
    wc.culture.enabled = false
    wc.prosperity.enabled = false
    wc.kingdom.enabled = false
    wc.monuments.enabled = false
    wc.housing_count.enabled = false
    wc.housing_level.enabled = false

    var extra = [7, 2, 0, 0, 0]
    for (var d = 0; d < 5; d++) {
        test511_set_difficulty(d)
        test511_setup(false, true, false)
        var max_year = __scenario_criteria_max_year()
        if (city.victory.end_year() != max_year + extra[d]) {
            return test511_fail('time limit, difficulty ' + d + ': end ' + city.victory.end_year() + ' max ' + max_year)
        }
        test511_setup(false, false, true)
        if (city.victory.end_year() != __scenario_criteria_max_year()) {
            return test511_fail('survival, difficulty ' + d + ': end ' + city.victory.end_year())
        }
    }
    __log_marker('time_extra_years_ok')

    test511_set_difficulty(2)
    for (var c = 0; c < T511_CASES.length; c++) {
        var tc = T511_CASES[c]
        test511_setup(tc[0], tc[1], tc[2])
        game.simtime.year = city.victory.end_year() + tc[3]
        var st = city_victory_determine_state()
        if (st != tc[4]) {
            return test511_fail('case ' + c + ': state ' + st + ' want ' + tc[4])
        }
    }
    __log_marker('time_goals_rules_ok')

    city.mission.fired_message_shown = false
    city.victory.lost_by_population = false
    var popups = [[0, true, true], [1, true, false], [4, true, false], [2, false, true]]
    for (var p = 0; p < popups.length; p++) {
        test511_set_difficulty(popups[p][0])
        __win_criteria.time_limit.enabled = popups[p][1]
        if (city_victory_lost_shows_popup() != popups[p][2]) {
            return test511_fail('popup case ' + p)
        }
    }
    city.mission.fired_message_shown = true
    test511_set_difficulty(0)
    if (city_victory_lost_shows_popup()) {
        return test511_fail('popup shown twice')
    }
    __log_marker('time_defeat_popup_ok')

    game_features.gameplay_fix_editor_events = true
    test511_set_difficulty(2)
    test511_setup(true, true, false)
    game.simtime.year = city.victory.end_year()
    var fixed = city_victory_determine_state()
    if (fixed != -1) {
        return test511_fail('fix_editor_events: goals met at the time limit gives ' + fixed)
    }
    __log_marker('time_fix_editor_events_ok')

    test511_restore()
    __test_signal_ready()
}

function check_valid() {
    var markers = ['time_extra_years_ok', 'time_goals_rules_ok', 'time_defeat_popup_ok', 'time_fix_editor_events_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:511] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

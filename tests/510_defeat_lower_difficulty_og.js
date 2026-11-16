// OG defeat by time limit (city/kingdom.c city_victory_check, window/victory_dialog.c city_defeat_options,
// window/mission_flow.c defeat_button_easier). On Normal the time limit ends the mission without the defeat popup
// and the defeat window offers "Lower Difficulty"; it lowers the difficulty to Easy and the city goes on with
// two more years. Losing again on Easy lowers to Very Easy with seven more years; on Very Easy the popup comes
// first and the window offers only replay / new game. Hard lowers straight to Easy.
// Markers:
//   [test-marker] defeat_normal_lower_offered
//   [test-marker] defeat_lower_to_easy_ok
//   [test-marker] defeat_lower_to_very_easy_ok
//   [test-marker] defeat_very_easy_replay_ok
//   [test-marker] defeat_hard_to_easy_ok

var t510 = {}

function test510_set_difficulty(d) {
    for (var i = 0; i < 5; i++) {
        __game_decrease_difficulty()
    }
    for (var j = 0; j < d; j++) {
        __game_increase_difficulty()
    }
}

function test510_fail(msg) {
    __log_info_native('[test:510] FAIL ' + msg)
    test510_restore()
    __test_signal_ready()
}

function test510_restore() {
    test_win_criteria_restore(t510.criteria)
    game.simtime.year = t510.year
    test510_set_difficulty(t510.difficulty)
    city.mission.fired_message_shown = t510.fired
    city.victory.state = 0
    ui.window_city_show()
}

// Loses by time at the current difficulty through the real outcome handler and opens the defeat window.
function test510_lose_by_time() {
    game.simtime.year = city.victory.end_year()
    city.victory.state = city_victory_determine_state()
    if (city.victory.state != -1 || city.victory.lost_by_population) {
        return false
    }
    city_victory_handle_outcome()
    return true
}

function run_test() {
    __log_info_native('[test:510] OG defeat options and Lower Difficulty')
    test_ensure_city_session('data/default.map')

    var wc = __win_criteria
    t510 = {
        criteria: test_win_criteria_snapshot(),
        year: game.simtime.year,
        difficulty: game.difficulty,
        fired: city.mission.fired_message_shown,
    }

    wc.culture.enabled = false
    wc.prosperity.enabled = false
    wc.kingdom.enabled = false
    wc.monuments.enabled = false
    wc.housing_count.enabled = false
    wc.housing_level.enabled = false
    wc.population.enabled = true
    wc.population.goal = 1000000
    wc.time_limit.enabled = true
    wc.time_limit.years = 5
    wc.survival_time.enabled = false
    __test_scenario_init_max_year()
    city.victory.reasons = {}
    var max_year = __scenario_criteria_max_year()

    test510_set_difficulty(2)
    city.mission.fired_message_shown = false
    if (city.victory.end_year() != max_year) {
        return test510_fail('normal end year ' + city.victory.end_year() + ' want ' + max_year)
    }
    if (!test510_lose_by_time()) {
        return test510_fail('normal: not lost by time, state ' + city.victory.state)
    }
    if (city.mission.fired_message_shown) {
        return test510_fail('normal: the defeat popup was posted')
    }
    city.victory.lost_can_replay = true
    __test_pump_frames(6)
    if (city.victory.defeat_options() != DEFEAT_OPTIONS_LOWER_DIFFICULTY
        || !__test_find_inlog('[test-marker] mission_lost_options:3')) {
        return test510_fail('normal: lower difficulty not offered, options ' + city.victory.defeat_options())
    }
    __log_marker('defeat_normal_lower_offered')

    window_mission_lost_on_lower_difficulty(null)
    __test_pump_frames(2)
    if (game.difficulty != 1 || city.victory.end_year() != max_year + 2) {
        return test510_fail('lower: difficulty ' + game.difficulty + ' end ' + city.victory.end_year())
    }
    if (city_victory_determine_state() != 0) {
        return test510_fail('lower: the city does not go on')
    }
    __log_marker('defeat_lower_to_easy_ok')

    if (!test510_lose_by_time() || city.mission.fired_message_shown) {
        return test510_fail('easy: not lost by time without popup')
    }
    city.victory.lost_can_replay = true
    __test_pump_frames(6)
    if (city.victory.defeat_options() != DEFEAT_OPTIONS_LOWER_DIFFICULTY) {
        return test510_fail('easy: options ' + city.victory.defeat_options())
    }
    window_mission_lost_on_lower_difficulty(null)
    __test_pump_frames(2)
    if (game.difficulty != 0 || city.victory.end_year() != max_year + 7) {
        return test510_fail('easy lower: difficulty ' + game.difficulty + ' end ' + city.victory.end_year())
    }
    __log_marker('defeat_lower_to_very_easy_ok')

    game.simtime.year = city.victory.end_year()
    city.victory.state = city_victory_determine_state()
    if (city.victory.state != -1 || !city_victory_lost_shows_popup()) {
        return test510_fail('very easy: the defeat popup is not due')
    }
    city.victory.lost_by_population = false
    city.victory.lost_can_replay = true
    if (city.victory.defeat_options() != DEFEAT_OPTIONS_REPLAY) {
        return test510_fail('very easy: options ' + city.victory.defeat_options())
    }
    city.victory.lost_can_replay = false
    if (city.victory.defeat_options() != DEFEAT_OPTIONS_NEW_GAME) {
        return test510_fail('very easy without replay: options ' + city.victory.defeat_options())
    }
    __log_marker('defeat_very_easy_replay_ok')

    test510_set_difficulty(3)
    city.victory.lower_difficulty()
    if (game.difficulty != 1) {
        return test510_fail('hard lowers to ' + game.difficulty)
    }
    __log_marker('defeat_hard_to_easy_ok')

    test510_restore()
    __test_pump_frames(2)
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'defeat_normal_lower_offered',
        'defeat_lower_to_easy_ok',
        'defeat_lower_to_very_easy_ok',
        'defeat_very_easy_replay_ok',
        'defeat_hard_to_easy_ok',
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:510] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

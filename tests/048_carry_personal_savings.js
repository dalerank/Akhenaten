// CO4: campaign personal savings apply on mission load; player_rank from mission JS
// (not campaign_scenario_id). Markers:
//   [test-marker] carry_savings_apply_ok
//   [test-marker] carry_player_rank_ok
//   [test-marker] carry_clear_ok
//   [test-marker] carry_personal_savings_all_ok

function run_test() {
    __log_info_native('[test:048] personal savings / player_rank carry')

    city.kingdome.campaign_carry_personal_savings = 1234
    __game_load_mission(48, 1)
    __test_pump_frames(2)

    if ((city.kingdome.personal_savings | 0) !== 1234) {
        __log_info_native('[test:048] personal_savings want 1234 got '
            + city.kingdome.personal_savings)
        __test_signal_ready()
        return
    }
    __log_marker('carry_savings_apply_ok')

    // mission48 player_rank : 5 — must not become scenario_id 48 (clamped to 10).
    if ((city.kingdome.player_rank | 0) !== 5) {
        __log_info_native('[test:048] player_rank want 5 got ' + city.kingdome.player_rank)
        __test_signal_ready()
        return
    }
    if ((city.kingdome.salary_rank | 0) !== 5) {
        __log_info_native('[test:048] salary_rank want 5 got ' + city.kingdome.salary_rank)
        __test_signal_ready()
        return
    }
    __log_marker('carry_player_rank_ok')

    // Menu Start / Individual: clear before load → next mission starts at 0.
    city.kingdome.campaign_carry_personal_savings = 0
    city.kingdome.personal_savings = 0
    __game_load_mission(41, 1)
    __test_pump_frames(2)

    if ((city.kingdome.personal_savings | 0) !== 0) {
        __log_info_native('[test:048] cleared carry want personal 0 got '
            + city.kingdome.personal_savings)
        __test_signal_ready()
        return
    }
    if ((city.kingdome.player_rank | 0) !== 6) {
        __log_info_native('[test:048] sumur player_rank want 6 got '
            + city.kingdome.player_rank)
        __test_signal_ready()
        return
    }
    __log_marker('carry_clear_ok')
    __log_marker('carry_personal_savings_all_ok')
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'carry_savings_apply_ok',
        'carry_player_rank_ok',
        'carry_clear_ok',
        'carry_personal_savings_all_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:048] missing marker: ' + marker)
            return false
        }
    }
    return true
}

// Repro: Individual Missions tab from Explore History (must not trip ourcity assert).
function run_test() {
    __log_info_native("[test:99i] open campaign then Individual Missions")

    window_scenario_selection_campaign.period_hover = -1
    window_scenario_selection_campaign.period_selected = 0
    window_scenario_selection_campaign.active_tab = CAMPAIGN_TAB_CAMPAIGNS
    window_scenario_selection.individual_missions = false
    window_show_by_id("window_scenario_selection_campaign")
    __test_pump_frames(5)

    __log_info_native("[test:99i] calling campaign_tab_individual")
    campaign_tab_individual()
    __test_pump_frames(20)

    __log_info_native("[test:99i] scenario_id=" + scenario.campaign_scenario_id)
    if (scenario.campaign_scenario_id < 0) {
        throw "expected a preview mission after Individual Missions"
    }
    __log_marker("explore_individual_ok")
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog("[test-marker] explore_individual_ok")
        && !__test_find_inlog("city.cpp:466")
}

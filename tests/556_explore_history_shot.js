// Dev helper: open Explore History and capture a display screenshot for layout QA.
function run_test() {
    __log_info_native("[test:556] open Explore History campaign window")

    window_scenario_selection_campaign.period_hover = -1
    window_scenario_selection_campaign.period_selected = 0
    window_scenario_selection_campaign.active_tab = CAMPAIGN_TAB_CAMPAIGNS
    window_scenario_selection.individual_missions = false

    window_show_by_id("window_scenario_selection_campaign")
    __test_pump_frames(20)

    __game_save_screenshot(SCREENSHOT_DISPLAY)
    __log_info_native("[test:556] screenshot saved")
    __log_marker("explore_history_shot_ok")

    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog("[test-marker] explore_history_shot_ok")
}

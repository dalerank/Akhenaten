log_info("akhenaten: mission_debug")

function mission_debug_show_mission_info() {
    if (!imgui.tree_node_ex("Mission Info")) {
        return
    }

    imgui.begin_table("MissionInfo", 2, imgui.table_flags_debug_props())
    __debug_props_show("scenario_id", scenario.campaign_scenario_id)
    __debug_props_show("campaign_id", __game_campaign_id_for_scenario(scenario.campaign_scenario_id))
    __debug_props_show("mission_rank", __scenario_settings.campaign_mission_rank)
    __debug_props_show("starting_kingdom", __scenario_settings.starting_kingdom)
    __debug_props_show("personal_savings", city.kingdome.personal_savings)
    __debug_props_show("scenario_mode", __scenario_settings_scmode())
    __debug_props_show("is_custom", __scenario_is_custom_mission())

    imgui.end_table()
    imgui.tree_pop()
}

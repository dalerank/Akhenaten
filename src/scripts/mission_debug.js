log_info("akhenaten: mission_debug")

[es=event_draw_debug_properties]
function mission_debug_draw_properties_mission_info(ev) {
    if (!imgui.tree_node_ex("Mission Info")) {
        return
    }

    imgui.begin_table("MissionInfo", 2, imgui.table_flags_debug_props())
    imgui.property_input("scenario_id", scenario, "campaign_scenario_id")
    imgui.property_input("campaign_id", __game_campaign_id_for_scenario(scenario.campaign_scenario_id))
    imgui.property_input("mission_rank", __scenario_settings, "campaign_mission_rank")
    imgui.property_input("starting_kingdom", __scenario_settings, "starting_kingdom")
    imgui.property_input("personal_savings", city.kingdome, "personal_savings")
    imgui.property_input("scenario_mode", __scenario_settings_scmode())
    imgui.property_input("is_custom", __scenario_is_custom_mission())

    imgui.end_table()
    imgui.tree_pop()
}

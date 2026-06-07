log_info("akhenaten: mission_debug")

[es=event_draw_debug_properties]
function mission_debug_draw_properties_mission_info(ev) {
    if (!imgui.tree_node_ex("Mission Info")) {
        return
    }

    imgui.begin_table("MissionInfo", 2, imgui.table_flags_debug_props())
    imgui.property_input("scenario_id", scenario, "campaign_scenario_id")
    imgui.property_input("campaign_id", __game_campaign_id_for_scenario(scenario.campaign_scenario_id))
    imgui.property_input("mission_rank", scenario, "campaign_mission_rank")
    imgui.property_input("starting_kingdom", __scenario_settings, "starting_kingdom")
    imgui.property_input("personal_savings", city.kingdome, "personal_savings")
    imgui.property_input("scenario_mode", scenario.scmode)
    imgui.property_input("is_custom", scenario.scmode != e_scenario_normal)

    imgui.end_table()
    imgui.tree_pop()
}

[es=event_draw_debug_properties]
function mission_debug_draw_properties_victory_status(ev) {
    if (!imgui.tree_node_ex("Victory Status")) {
        return
    }

    imgui.begin_table("VictoryStatus", 2, imgui.table_flags_debug_props())

    var state_text = "None"
    if (__scenario_victory.state == 1) { state_text = "WON" }
    else if (__scenario_victory.state == -1) { state_text = "LOST" }

    imgui.property_input("victory_state", state_text)
    imgui.property_input("force_win", __scenario_victory, "force_win")
    imgui.property_input("force_lost", __scenario_victory, "force_lost")
    __debug_feature_bool("gameopt_disable_victory", "disable_victory")

    if (scenario.population_goal > 0) {
        imgui.property_input("population: " + city.population + " / " + scenario.population_goal,
                             city.population >= scenario.population_goal)
    }

    if (scenario.culture_goal > 0) {
        imgui.property_input("culture: " + city.rating.culture + " / " + scenario.culture_goal,
                             city.rating.culture >= scenario.culture_goal)
    }

    if (scenario.prosperity_goal > 0) {
        imgui.property_input("prosperity: " + city.rating.prosperity + " / " + scenario.prosperity_goal,
                             city.rating.prosperity >= scenario.prosperity_goal)
    }

    if (scenario.monuments_goal > 0) {
        imgui.property_input("monuments: " + city.rating.monument + " / " + scenario.monuments_goal,
                             city.rating.monument >= scenario.monuments_goal)
    }

    if (scenario.kingdom_goal > 0) {
        imgui.property_input("kingdom: " + city.rating.kingdom + " / " + scenario.kingdom_goal,
                             city.rating.kingdom >= scenario.kingdom_goal)
    }

    if (scenario.housing_count_goal > 0) {
        imgui.property_input("housing[lvl " + scenario.housing_level_goal + "]: "
                             + __scenario_victory_houses_of_required_level() + " / " + scenario.housing_count_goal,
                             __scenario_victory_is_housing_condition_met())
    }

    if (__win_criteria.time_limit.enabled) {
        var years_left = __scenario_criteria_max_year() - game.simtime.year
        imgui.property_input("time_limit: " + years_left + " years left", years_left > 0)
    }

    if (__win_criteria.survival_time.enabled) {
        var years_left = __scenario_criteria_max_year() - game.simtime.year
        imgui.property_input("survival_time: " + years_left + " years left", years_left <= 0)
    }

    imgui.end_table()
    imgui.tree_pop()
}

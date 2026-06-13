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
    if (city.victory.state == 1) { state_text = "WON" }
    else if (city.victory.state == -1) { state_text = "LOST" }

    imgui.property_input("victory_state", state_text)
    imgui.property_input("force_win", city.victory, "force_win")
    imgui.property_input("force_lost", city.victory, "force_lost")
    __debug_feature_bool("gameopt_disable_victory", "disable_victory")

    if (city.winning.population.enabled) {
        imgui.property_input("population: " + city.population + " / " + city.winning.population.goal,
                             city.population >= city.winning.population.goal)
    }

    if (city.winning.culture.enabled) {
        imgui.property_input("culture: " + city.rating.culture + " / " + city.winning.culture.goal,
                             city.rating.culture >= city.winning.culture.goal)
    }

    if (city.winning.prosperity.enabled) {
        imgui.property_input("prosperity: " + city.rating.prosperity + " / " + city.winning.prosperity.goal,
                             city.rating.prosperity >= city.winning.prosperity.goal)
    }

    if (city.winning.monuments.enabled) {
        imgui.property_input("monuments: " + city.rating.monument + " / " + city.winning.monuments.goal,
                             city.rating.monument >= city.winning.monuments.goal)
    }

    if (city.winning.kingdom.enabled) {
        imgui.property_input("kingdom: " + city.rating.kingdom + " / " + city.winning.kingdom.goal,
                             city.rating.kingdom >= city.winning.kingdom.goal)
    }

    if (city.winning.housing_count.enabled) {
        imgui.property_input("housing[lvl " + city.winning.housing_level.goal + "]: "
                             + city.victory.houses_of_required_level() + " / " + city.winning.housing_count.goal,
                             city.victory.is_housing_condition_met())
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

[es=event_draw_debug_properties]
function mission_debug_draw_properties_victory_reasons(ev) {
    if (!imgui.tree_node_ex("Victory Reasons")) {
        return
    }

    var reasons = city.victory.reasons
    var names = Object.keys(reasons)
    if (names.length <= 0) {
        imgui.tree_pop()
        return
    }

    imgui.begin_table("VictoryReasons", 2, imgui.table_flags_debug_props())
    for (var i = 0; i < names.length; i++) {
        imgui.property_input(names[i], reasons[names[i]])
    }

    imgui.end_table()
    imgui.tree_pop()
}

[es=event_draw_debug_properties]
function mission_debug_draw_properties_migration_caps(ev) {
    if (!imgui.tree_node_ex("Migration Caps")) {
        return
    }

    var caps = __city_migration_caps()
    var names = Object.keys(caps)
    if (names.length <= 0) {
        return
    }

    imgui.begin_table("MigrationCaps", 2, imgui.table_flags_debug_props())
    for (var i = 0; i < names.length; i++) {
        imgui.property_input(names[i], caps[names[i]])
    }
    imgui.end_table()
    imgui.tree_pop()
}

log_info("akhenaten: scenario started")

function scenario_win_criteria_goal(c) {
    return c.enabled ? c.goal : 0
}

scenario = extend(__scenario, {
    map: __scenario_map,
    has_animals: __scenario_has_animals
    flotsam_enabled: __scenario_flotsam_enabled
    building_allowed: __scenario_building_allowed
    // => is_open_play
    // => kingdom_supplies_grain
    // => climate
    // => image_id
    // => start_year
    // => campaign_scenario_id

    @culture_goal: { get: function() { return scenario_win_criteria_goal(__win_criteria.culture); } }
    @prosperity_goal: { get: function() { return scenario_win_criteria_goal(__win_criteria.prosperity); } }
    @monuments_goal: { get: function() { return scenario_win_criteria_goal(__win_criteria.monuments); } }
    @kingdom_goal: { get: function() { return scenario_win_criteria_goal(__win_criteria.kingdom); } }
    @housing_count_goal: { get: function() { return scenario_win_criteria_goal(__win_criteria.housing_count); } }
    @housing_level_goal: { get: function() { return scenario_win_criteria_goal(__win_criteria.housing_level); } }
    @population_goal: { get: function() { return scenario_win_criteria_goal(__win_criteria.population); } }
})
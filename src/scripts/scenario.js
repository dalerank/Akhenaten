log_info("akhenaten: scenario started")

function scenario_win_criteria_goal(c) {
    return c.enabled ? c.goal : 0
}

function mission_selection_title(scenario_id) {
    // Use the original "history" message name (id 200 + scenario_id) as the primary
    // title. These use the Egyptian place names (e.g. "Abedju") and match the mission
    // briefing window, keeping the Explore History list consistent. The JS config's
    // selection_title is an Anglicized fallback (e.g. "Abydos") for any mission whose
    // history message is missing; "No title" is the last resort for unported ids with
    // neither.
    var orig = __lang_message_title_text(200 + scenario_id)
    if (orig && orig.length > 0) {
        return orig
    }
    var config = get_mission_config(scenario_id)
    if (config && config.selection_title && config.selection_title.length > 0) {
        return config.selection_title
    }
    return "No title"
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
    // => subtitle
    // => player_rank

    @culture_goal: { get: function() { return scenario_win_criteria_goal(__win_criteria.culture); } }
    @prosperity_goal: { get: function() { return scenario_win_criteria_goal(__win_criteria.prosperity); } }
    @monuments_goal: { get: function() { return scenario_win_criteria_goal(__win_criteria.monuments); } }
    @kingdom_goal: { get: function() { return scenario_win_criteria_goal(__win_criteria.kingdom); } }
    @housing_count_goal: { get: function() { return scenario_win_criteria_goal(__win_criteria.housing_count); } }
    @housing_level_goal: { get: function() { return scenario_win_criteria_goal(__win_criteria.housing_level); } }
    @population_goal: { get: function() { return scenario_win_criteria_goal(__win_criteria.population); } }
    @is_custom: { get: function() { return __scenario.scmode != e_scenario_normal; } }
})
log_info("akhenaten: scenario started")

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
})

function scenario_win_criteria_goal(c) {
    return c.enabled ? c.goal : 0
}
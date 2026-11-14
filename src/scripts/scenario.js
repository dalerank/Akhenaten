log_info("akhenaten: scenario started")

function scenario_win_criteria_goal(c) {
    return c.enabled ? c.goal : 0
}

function mission_selection_title(scenario_id) {
    if (scenario_id === undefined || scenario_id === null || scenario_id < 0) {
        return "No title"
    }
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

function custom_map_selection_title(filename) {
    var base = filename || ""
    var slash = base.lastIndexOf("/")
    var bslash = base.lastIndexOf("\\")
    var cut = slash > bslash ? slash : bslash
    if (cut >= 0) {
        base = base.substring(cut + 1)
    }
    var n = base.length
    if (n >= 4 && base.substring(n - 4).toLowerCase() === ".map") {
        return base.substring(0, n - 4)
    }
    return base
}

scenario = extend(__scenario, {
    map: __scenario_map,
    has_animals: __scenario_has_animals
    @flotsam_enabled: {
        get: function() { return __scenario_flotsam_enabled }
        set: function(v) { __scenario_flotsam_enabled = !!v }
    }
    building_allowed: __scenario_building_allowed
    // Live bind (extend would snapshot a bool and desync from C++ / map load).
    @hide_nilometer: {
        get: function() { return __scenario_hide_nilometer }
        set: function(v) { __scenario_hide_nilometer = !!v }
    }
    // => is_open_play
    // => kingdom_supplies_grain
    // => climate
    // => image_id
    // => start_year
    // => campaign_scenario_id
    // => subtitle
    // => player_rank

    @has_prey_points: { get: function() { return !!__scenario_has_prey_points() } }

    // Live bind (extend would snapshot a bool and desync from C++ / map load).
    @alt_predator_type: {
        get: function() { return __scenario_alt_predator_type }
        set: function(v) { __scenario_alt_predator_type = !!v }
    }

    @culture_goal: { get: function() { return scenario_win_criteria_goal(__win_criteria.culture); } }
    @prosperity_goal: { get: function() { return scenario_win_criteria_goal(__win_criteria.prosperity); } }
    @monuments_goal: { get: function() { return scenario_win_criteria_goal(__win_criteria.monuments); } }
    @kingdom_goal: { get: function() { return scenario_win_criteria_goal(__win_criteria.kingdom); } }
    @housing_count_goal: { get: function() { return scenario_win_criteria_goal(__win_criteria.housing_count); } }
    @housing_level_goal: { get: function() { return scenario_win_criteria_goal(__win_criteria.housing_level); } }
    @population_goal: { get: function() { return scenario_win_criteria_goal(__win_criteria.population); } }
    @is_custom: { get: function() { return __scenario.scmode != e_scenario_normal; } }
})

// OG scenario_events.c scenario_event_rules and scenario_rules.c troops_loss_brackets: request reminder and overdue
// months, the kingdom penalty for an ignored request, default travel months, the random event months margin, and the
// troop losses by the strength left over (percent below which the bracket applies; past the last one nobody is lost).
scenario_request_rules {
    reminder_months : 6
    overdue_months : 24
    ignored_kingdom_penalty : 3
    troops_months_default : 12
    troops_return_early_months : 2
    travel_months_default : 12
    months_margin_min : 4
    months_margin_choices : 5
    troops_loss : [
        { below_percent : 10, losses : 70 },
        { below_percent : 25, losses : 50 },
        { below_percent : 50, losses : 25 },
        { below_percent : 75, losses : 15 },
        { below_percent : 100, losses : 10 },
        { below_percent : 150, losses : 5 }
    ]
}

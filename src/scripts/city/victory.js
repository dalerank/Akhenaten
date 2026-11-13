log_info("akhenaten: city victory started")

// time_limit_extra_years: years added to a time limit per difficulty (OG 7 on Very Easy, 2 on Easy).
// lost_population_*: the city is lost when enemies and kingdom soldiers outnumber its soldiers by more than
// extra_enemies and the population falls under highest_ever / fraction (OG 2 and 4).
// lower_difficulty_max: "Lower Difficulty" after a lost time limit leaves at most this difficulty (OG 1, Easy).
victory_rules {
  time_limit_extra_years [7, 2, 0, 0, 0]
  lost_population_extra_enemies : 2
  lost_population_fraction : 4
  lower_difficulty_max : 1
}

var VICTORY_DIFFICULTY_EASY = 1

city.victory = extend(__city_victory, {
    reasons: {},

    set_reason: function(name, value) {
        this.reasons[name] = value
    },

    continue_governing: function(months) {
        scenario.has_won = true
        scenario.continue_months_left += months
        scenario.continue_months_chosen = months
        city.kingdome.salary_rank = 0
        city.kingdome.salary_amount = 0
    },

    houses_of_required_level: function() {
        var min_level = city.winning.housing_level.enabled ? city.winning.housing_level.goal : 0
        return city.count_houses_at_least(min_level)
    },

    is_housing_condition_met: function() {
        if (!city.winning.housing_count.enabled) {
            return true
        }
        return city.victory.houses_of_required_level() >= city.winning.housing_count.goal
    },

    end_year: __city_victory_end_year,
    defeat_options: __city_victory_defeat_options,
    lower_difficulty: __city_victory_lower_difficulty
})

function city_victory_all_reasons_met() {
    var reasons = city.victory.reasons
    var names = Object.keys(reasons)
    if (names.length <= 0) {
        return true
    }

    for (var i = 0; i < names.length; i++) {
        if (!reasons[names[i]]) {
            return false
        }
    }
    return true
}

function city_victory_determine_state() {
    return __city_victory_determine_state(city_victory_all_reasons_met())
}

// OG city_victory_check: a lost city first gets the defeat popup, unless the time limit ran out on Easy or
// harder, where the mission ends at once.
function city_victory_lost_shows_popup() {
    if (city.mission.fired_message_shown) {
        return false
    }
    return city.victory.lost_by_population
        || !__win_criteria.time_limit.enabled
        || game.difficulty < VICTORY_DIFFICULTY_EASY
}

function city_victory_handle_outcome() {
    if (game_features.gameopt_disable_victory) {
        return
    }

    if (city.victory.state == 0) {
        return
    }

    __city_planner_reset()

    if (city.victory.state == -1) {
        if (city_victory_lost_shows_popup()) {
            city.mission.fired_message_shown = true
            ui.popup_message("message_mission_defeat", 0, 0)
        } else {
            __city_victory_lost_cleanup()
            mission_end_show(1)
        }
        city.victory.force_win = false
    } else if (city.victory.state == 1) {
        __game_sound.music_stop()
        if (city.mission.victory_message_shown) {
            mission_end_show(0)
            city.victory.force_win = false
        } else {
            city.mission.victory_message_shown = true
            emit event_show_window { id: "window_victory_dialog" }
        }
    }
}

[es=event_advance_month]
function city_victory_on_advance_month(ev) {
    if (scenario.has_won) {
        scenario.continue_months_left--
    }
}

[es=(city_victory, reset)]
function city_victory_on_reset(ev) {
    city.victory.reasons = {}
}

[es=(city_victory, victory_check)]
function city_victory_on_check(ev) {
    if (scenario.is_open_play) {
        return
    }

    emit event_update_victory_state { population: city.population }
    city.victory.state = city_victory_determine_state()

    if (scenario.has_won) {
        city.victory.state = scenario.continue_months_left <= 0 ? 1 : 0
    }

    if (city.victory.force_win) {
        city.victory.state = 1
    }

    if (city.victory.force_lost) {
        city.victory.state = -1
    }

    city_victory_handle_outcome()
}

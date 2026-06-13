log_info("akhenaten: city victory started")

city.victory = extend(__city_victory, {
    continue_governing: function(months) {
        scenario.has_won = true
        scenario.continue_months_left += months
        scenario.continue_months_chosen = months
        city.kingdome.salary_rank = 0
        city.kingdome.salary_amount = 0
    },

    houses_of_required_level: function() {
        var min_level = city.winning.housing_level.enabled ? city.winning.housing_level.goal : 0
        var count = 0
        for (var i = min_level; i < 20; i++) {
            count += city.housing_type_count_at(i)
        }
        return count
    },

    is_housing_condition_met: function() {
        if (!city.winning.housing_count.enabled) {
            return true
        }
        return city.victory.houses_of_required_level() >= city.winning.housing_count.goal
    }
})

function city_victory_all_reasons_met() {
    var reasons = __city_victory_reasons()
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
    var state = 1
    var has_criteria = 0

    if (city.winning.culture.enabled) {
        has_criteria = 1
        if (city.rating.culture < city.winning.culture.goal) {
            state = 0
        }
    }

    if (city.winning.prosperity.enabled) {
        has_criteria = 1
        if (city.rating.prosperity < city.winning.prosperity.goal) {
            state = 0
        }
    }

    if (city.winning.monuments.enabled) {
        has_criteria = 1
        if (city.rating.monument < city.winning.monuments.goal) {
            state = 0
        }
    }

    if (city.winning.kingdom.enabled) {
        has_criteria = 1
        if (city.rating.kingdom < city.winning.kingdom.goal) {
            state = 0
        }
    }

    if (city.winning.population.enabled) {
        has_criteria = 1
        if (city.population < city.winning.population.goal) {
            state = 0
        }
    }

    if (city.winning.housing_count.enabled) {
        has_criteria = 1
        if (!city.victory.is_housing_condition_met()) {
            state = 0
        }
    }

    if (!city_victory_all_reasons_met()) {
        state = 0
    }

    if (!has_criteria) {
        state = 0
    }

    var fix_editor_events = game_features.gameplay_fix_editor_events
    var max_year = __scenario_criteria_max_year()

    if (fix_editor_events) {
        if (game.simtime.year >= max_year) {
            if (__win_criteria.time_limit.enabled) {
                state = -1
            } else if (__win_criteria.survival_time.enabled) {
                if (!has_criteria) {
                    state = 1
                } else if (state != 1) {
                    state = -1
                }
            }
        } else if (__win_criteria.survival_time.enabled) {
            state = 0
        }

        if (__win_criteria.time_limit.enabled || __win_criteria.survival_time.enabled) {
            has_criteria = 1
        }
    } else {
        if (!has_criteria) {
            if (__win_criteria.time_limit.enabled || __win_criteria.survival_time.enabled) {
                has_criteria = 1
            }
        }

        if (game.simtime.year >= max_year) {
            if (__win_criteria.time_limit.enabled) {
                state = -1
            } else if (__win_criteria.survival_time.enabled) {
                state = 1
            }
        }
    }

    var invaders = __city_figures_total_invading_enemies()
    if (invaders > 2 + city.figures.soldiers) {
        if (city.population < city.population_stats.highest_ever / 4) {
            state = -1
        }
    }

    if (invaders > 0 && city.population <= 0) {
        state = -1
    }

    if (!has_criteria) {
        state = 0
    }

    return state
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
        if (city.mission.fired_message_shown) {
            mission_end_show(1)
        } else {
            city.mission.fired_message_shown = true
            ui.popup_message("message_mission_defeat", 0, 0)
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

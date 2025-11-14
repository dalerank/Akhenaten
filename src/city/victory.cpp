#include "victory.h"

#include "building/building_house.h"
#include "building/construction/build_planner.h"
#include "city/city.h"
#include "city/city_finance.h"
#include "city/city_message.h"
#include "game/game.h"
#include "game/game_config.h"
#include "scenario/criteria.h"
#include "scenario/scenario.h"
#include "sound/sound.h"
#include "window/mission_end.h"
#include "window/victory_dialog.h"
#include "js/js_game.h"

#include "dev/debug.h"
#include <iostream>

declare_console_command_p(victory) {
    g_city.victory_state.force_win = true;
}

declare_console_command_p(defeat) {
    g_city.victory_state.force_lost = true;
}

svector<victory_condition, 16> g_victory_conditions;
std::unordered_map<xstring, bool> g_victory_reasons;

void city_set_victory_reason(xstring reason, bool value) {
    g_victory_reasons[reason] = value;
}
ANK_FUNCTION_2(city_set_victory_reason)

void victory_state_t::reset() {
   state = e_victory_state_none;
   force_win = false;
   g_victory_conditions.clear();
   g_victory_reasons.clear();
}

int winning_conditions() {
    return g_victory_conditions.size() > 0;
}

int winning_reasons() {
    return g_victory_reasons.size() > 0;
}

int victory_state_t::houses_of_required_level() {
    const auto &blds = city_buildings();
    const int houses_of_required_level = std::count_if(blds.begin(), blds.end(), [] (auto &b) {
        auto house = b.dcast_house();
        const bool abobe_goal = (house && house->is_valid() && house->house_level() >= winning_houselevel());
        return abobe_goal;
    });

    return houses_of_required_level;
}

void victory_state_t::determine_state() {
    const auto& ratings = g_city.ratings;
    const auto& kingdome = g_city.kingdome;
    const auto& population = g_city.population;
    const auto& figures = g_city.figures;

    e_victory_state state = e_victory_state_won;
    int has_criteria = 0;

    if (winning_culture()) {
        has_criteria = 1;
        if (ratings.culture < winning_culture()) {
            state = e_victory_state_none;
        }
    }

    if (winning_prosperity()) {
        has_criteria = 1;
        if (ratings.prosperity < winning_prosperity()) {
            state = e_victory_state_none;
        }
    }

    if (winning_monuments()) {
        has_criteria = 1;
        if (ratings.monument < winning_monuments()) {
            state = e_victory_state_none;
        }
    }

    if (winning_kingdom()) {
        has_criteria = 1;
        if (kingdome.rating < winning_kingdom()) {
            state = e_victory_state_none;
        }
    }

    if (winning_population()) {
        has_criteria = 1;
        if (population.current < winning_population()) {
            state = e_victory_state_none;
        }
    }

    if (winning_housing()) {
        has_criteria = 1;
        if (!is_housing_condition_met()) {
            state = e_victory_state_none;
        }
    }

    if (winning_conditions()) {
        for (const auto &condition : g_victory_conditions) {
            if (!condition()) {
                state = e_victory_state_none;
                break;
            }
        }
    }

    if (winning_reasons()) {
        for (const auto &reason : g_victory_reasons) {
            if (!reason.second) {
                state = e_victory_state_none;
                break;
            }
        }
    }

    if (!has_criteria) {
        state = e_victory_state_none;
    }

    if (!!game_features::gameplay_fix_editor_events) {
        // More sensible options for surival time:
        // require the user to play to the end, even if other win criteria have been set and are met.
        // At the end, let the user lose if the other win criteria are not met
        if (game.simtime.year >= scenario_criteria_max_year()) {
            if (scenario_criteria_time_limit_enabled()) {
                // Lose game automatically when you go over the time limit
                state = e_victory_state_lost;
            } else if (scenario_criteria_survival_enabled()) {
                if (!has_criteria) {
                    state = e_victory_state_won;
                } else if (state != e_victory_state_won) {
                    // Lose game if you do not meet the criteria at the end of the road
                    state = e_victory_state_lost;
                }
            }
        } else if (scenario_criteria_survival_enabled()) {
            // Do not win the game when other criteria are met when survival time is enabled
            state = e_victory_state_none;
        }

        if (scenario_criteria_time_limit_enabled() || scenario_criteria_survival_enabled()) {
            has_criteria = 1;
        }

    } else {
        // Original buggy code for survival time and time limit:
        // the survival time only works if no other criteria have been set
        if (!has_criteria) {
            if (scenario_criteria_time_limit_enabled() || scenario_criteria_survival_enabled())
                has_criteria = 1;
        }

        if (game.simtime.year >= scenario_criteria_max_year()) {
            if (scenario_criteria_time_limit_enabled())
                state = e_victory_state_lost;
            else if (scenario_criteria_survival_enabled())
                state = e_victory_state_won;
        }
    }

    if (figures.total_invading_enemies() > 2 + figures.soldiers) {
        if (population.current < population.highest_ever / 4)
            state = e_victory_state_lost;
    }

    if (figures.total_invading_enemies() > 0 && population.current <= 0) {
        state = e_victory_state_lost;
    }

    if (!has_criteria) {
        state = e_victory_state_none;
    }
}

void city_t::victory_check() {
    if (scenario_is_open_play()) {
        return;
    }

    events::emit(event_update_victory_state{ g_city.population.current });
    victory_state.determine_state();

    if (mission.has_won) {
        victory_state.state = mission.continue_months_left <= 0 ? e_victory_state_won : e_victory_state_none;
    }

    if (victory_state.force_win) {
        victory_state.state = e_victory_state_won;
    }

    if (victory_state.force_lost) {
        victory_state.state = e_victory_state_lost;
    }

    if (victory_state.state != e_victory_state_none) {
        g_city_planner.reset();
        if (victory_state.state == e_victory_state_lost) {
            if (mission.fired_message_shown)
                window_mission_end_show_fired();
            else {
                mission.fired_message_shown = 1;
                messages::popup("message_mission_defeat", 0, 0);
            }
            victory_state.force_win = 0;
        } else if (victory_state.state == e_victory_state_won) {
            g_sound.music_stop();
            if (mission.victory_message_shown) {
                ui::window_mission_won::show();
                victory_state.force_win = 0;
            } else {
                mission.victory_message_shown = 1;
                window_victory_dialog_show();
            }
        }
    }
}

void victory_state_t::update_months_to_govern() {
    if (g_city.mission.has_won) {
        g_city.mission.continue_months_left--;
    }
}

void victory_state_t::continue_governing(int months) {
    g_city.mission.has_won = 1;
    g_city.mission.continue_months_left += months;
    g_city.mission.continue_months_chosen = months;
    g_city.kingdome.salary_rank = 0;
    g_city.kingdome.salary_amount = 0;
}

void victory_state_t::stop_governing() {
    g_city.mission.has_won = 0;
    g_city.mission.continue_months_left = 0;
    g_city.mission.continue_months_chosen = 0;
}

bool victory_state_t::has_won() {
    return g_city.mission.has_won;
}

bool victory_state_t::is_housing_condition_met() {
    const int should_check_houses_level = winning_housing();
    if (should_check_houses_level <= 0) {
        return true;
    }

    const int houses_if_required_level = houses_of_required_level();
    return (houses_if_required_level >= should_check_houses_level);
}

void victory_state_t::add_condition(victory_condition cond) {
    g_victory_conditions.push_back(cond);
}

const std::unordered_map<xstring, bool> &get_victory_reasons() {
    return g_victory_reasons;
}
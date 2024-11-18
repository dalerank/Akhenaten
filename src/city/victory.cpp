#include "victory.h"

#include "building/building_house.h"
#include "building/construction/build_planner.h"
#include "city/city.h"
#include "city/finance.h"
#include "city/message.h"
#include "game/time.h"
#include "config/config.h"
#include "scenario/criteria.h"
#include "scenario/scenario.h"
#include "sound/music.h"
#include "window/mission_end.h"
#include "window/victory_dialog.h"

#include "dev/debug.h"
#include <iostream>

declare_console_command_p(victory, game_cheat_force_victory)
declare_console_command_p(defeat, game_cheat_force_defeat)

void game_cheat_force_defeat(std::istream &is, std::ostream &os) {
    g_city.victory_state.force_lost = true;
}

void game_cheat_force_victory(std::istream &is, std::ostream &os) {
    g_city.victory_state.force_win = true;
}

void vistory_state_t::reset() {
   state = e_victory_state_none;
   force_win = false;
}

e_victory_state city_t::determine_victory_state() {
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
        if (ratings.kingdom < winning_kingdom()) {
            state = e_victory_state_none;
        }
    }
    if (winning_population()) {
        has_criteria = 1;
        if (population.population < winning_population()) {
            state = e_victory_state_none;
        }
    }
    if (winning_housing()) {
        has_criteria = 1;
        int houses_of_required_level = 0;
        for (int i = 0; i < building_get_highest_id(); i++) {
            building* b = building_get(i);
            if (b->state == BUILDING_STATE_VALID && b->type == winning_houselevel() + BUILDING_HOUSE_CRUDE_HUT) {
                houses_of_required_level++;
            }
        }
        if (houses_of_required_level < winning_housing()) {
            state = e_victory_state_none;
        }
    }

    if (!has_criteria) {
        state = e_victory_state_none;
    }

    if (config_get(CONFIG_GP_FIX_EDITOR_EVENTS)) {
        // More sensible options for surival time:
        // require the user to play to the end, even if other win criteria have been set and are met.
        // At the end, let the user lose if the other win criteria are not met
        if (gametime().year >= scenario_criteria_max_year()) {
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
        if (gametime().year >= scenario_criteria_max_year()) {
            if (scenario_criteria_time_limit_enabled())
                state = e_victory_state_lost;
            else if (scenario_criteria_survival_enabled())
                state = e_victory_state_won;
        }
    }

    if (figures_total_invading_enemies() > 2 + figures.soldiers) {
        if (population.population < population.highest_ever / 4)
            state = e_victory_state_lost;
    }
    if (g_city.figures_total_invading_enemies() > 0) {
        if (population.population <= 0)
            state = e_victory_state_lost;
    }
    if (!has_criteria)
        state = e_victory_state_none;

    return state;
}

void city_t::victory_check() {
    if (scenario_is_open_play()) {
        return;
    }

    victory_state.state = determine_victory_state();

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
        Planner.reset();
        if (victory_state.state == e_victory_state_lost) {
            if (mission.fired_message_shown)
                window_mission_end_show_fired();
            else {
                mission.fired_message_shown = 1;
                city_message_post(true, MESSAGE_FIRED, 0, 0);
            }
            victory_state.force_win = 0;
        } else if (victory_state.state == e_victory_state_won) {
            sound_music_stop();
            if (mission.victory_message_shown) {
                window_mission_end_show_won();
                victory_state.force_win = 0;
            } else {
                mission.victory_message_shown = 1;
                window_victory_dialog_show();
            }
        }
    }
}

void vistory_state_t::update_months_to_govern() {
    if (g_city.mission.has_won)
        g_city.mission.continue_months_left--;
}

void vistory_state_t::continue_governing(int months) {
    g_city.mission.has_won = 1;
    g_city.mission.continue_months_left += months;
    g_city.mission.continue_months_chosen = months;
    g_city.kingdome.salary_rank = 0;
    g_city.kingdome.salary_amount = 0;
    city_finance_update_salary();
}

void vistory_state_t::stop_governing(void) {
    g_city.mission.has_won = 0;
    g_city.mission.continue_months_left = 0;
    g_city.mission.continue_months_chosen = 0;
}

bool vistory_state_t::has_won() {
    return g_city.mission.has_won;
}

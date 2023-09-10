#include "victory.h"

#include "building/building.h"
#include "building/house.h"
#include "building/construction/build_planner.h"
#include "city/data_private.h"
#include "city/figures.h"
#include "city/finance.h"
#include "city/message.h"
#include "game/time.h"
#include "io/config/config.h"
#include "scenario/criteria.h"
#include "scenario/property.h"
#include "sound/music.h"
#include "window/mission_end.h"
#include "window/victory_dialog.h"

struct vistory_data_t {
    e_victory_state state;
    bool force_win;
};

vistory_data_t g_vistory_data;

void city_victory_reset(void) {
    g_vistory_data.state = VICTORY_STATE_NONE;
    g_vistory_data.force_win = false;
}

void city_victory_force_win(void) {
    g_vistory_data.force_win = true;
}

e_victory_state city_victory_state(void) {
    return g_vistory_data.state;
}

#include "buildings.h"

static e_victory_state determine_victory_state(void) {
    e_victory_state state = VICTORY_STATE_WON;
    int has_criteria = 0;

    if (winning_culture()) {
        has_criteria = 1;
        if (city_data.ratings.culture < winning_culture())
            state = VICTORY_STATE_NONE;
    }
    if (winning_prosperity()) {
        has_criteria = 1;
        if (city_data.ratings.prosperity < winning_prosperity())
            state = VICTORY_STATE_NONE;
    }
    if (winning_monuments()) {
        has_criteria = 1;
        if (city_data.ratings.monument < winning_monuments())
            state = VICTORY_STATE_NONE;
    }
    if (winning_kingdom()) {
        has_criteria = 1;
        if (city_data.ratings.kingdom < winning_kingdom())
            state = VICTORY_STATE_NONE;
    }
    if (winning_population()) {
        has_criteria = 1;
        if (city_data.population.population < winning_population())
            state = VICTORY_STATE_NONE;
    }
    if (winning_housing()) {
        has_criteria = 1;
        int houses_of_required_level = 0;
        for (int i = 0; i < building_get_highest_id(); i++) {
            building* b = building_get(i);
            if (b->state == BUILDING_STATE_VALID && b->type == winning_houselevel() + BUILDING_HOUSE_SMALL_HUT)
                houses_of_required_level++;
        }
        if (houses_of_required_level < winning_housing())
            state = VICTORY_STATE_NONE;
    }

    if (!has_criteria)
        state = VICTORY_STATE_NONE;

    if (config_get(CONFIG_GP_FIX_EDITOR_EVENTS)) {
        // More sensible options for surival time:
        // require the user to play to the end, even if other win criteria have been set and are met.
        // At the end, let the user lose if the other win criteria are not met
        if (game_time_year() >= scenario_criteria_max_year()) {
            if (scenario_criteria_time_limit_enabled()) {
                // Lose game automatically when you go over the time limit
                state = VICTORY_STATE_LOST;
            } else if (scenario_criteria_survival_enabled()) {
                if (!has_criteria)
                    state = VICTORY_STATE_WON;
                else if (state != VICTORY_STATE_WON) {
                    // Lose game if you do not meet the criteria at the end of the road
                    state = VICTORY_STATE_LOST;
                }
            }
        } else if (scenario_criteria_survival_enabled()) {
            // Do not win the game when other criteria are met when survival time is enabled
            state = VICTORY_STATE_NONE;
        }
        if (scenario_criteria_time_limit_enabled() || scenario_criteria_survival_enabled())
            has_criteria = 1;

    } else {
        // Original buggy code for survival time and time limit:
        // the survival time only works if no other criteria have been set
        if (!has_criteria) {
            if (scenario_criteria_time_limit_enabled() || scenario_criteria_survival_enabled())
                has_criteria = 1;
        }
        if (game_time_year() >= scenario_criteria_max_year()) {
            if (scenario_criteria_time_limit_enabled())
                state = VICTORY_STATE_LOST;
            else if (scenario_criteria_survival_enabled())
                state = VICTORY_STATE_WON;
        }
    }

    if (city_figures_total_invading_enemies() > 2 + city_data.figure.soldiers) {
        if (city_data.population.population < city_data.population.highest_ever / 4)
            state = VICTORY_STATE_LOST;
    }
    if (city_figures_total_invading_enemies() > 0) {
        if (city_data.population.population <= 0)
            state = VICTORY_STATE_LOST;
    }
    if (!has_criteria)
        state = VICTORY_STATE_NONE;

    return state;
}

void city_victory_check(void) {
    if (scenario_is_open_play())
        return;
    g_vistory_data.state = determine_victory_state();

    if (city_data.mission.has_won)
        g_vistory_data.state = city_data.mission.continue_months_left <= 0 ? VICTORY_STATE_WON : VICTORY_STATE_NONE;

    if (g_vistory_data.force_win)
        g_vistory_data.state = VICTORY_STATE_WON;

    if (g_vistory_data.state != VICTORY_STATE_NONE) {
        Planner.reset();
        if (g_vistory_data.state == VICTORY_STATE_LOST) {
            if (city_data.mission.fired_message_shown)
                window_mission_end_show_fired();
            else {
                city_data.mission.fired_message_shown = 1;
                city_message_post(true, MESSAGE_FIRED, 0, 0);
            }
            g_vistory_data.force_win = 0;
        } else if (g_vistory_data.state == VICTORY_STATE_WON) {
            sound_music_stop();
            if (city_data.mission.victory_message_shown) {
                window_mission_end_show_won();
                g_vistory_data.force_win = 0;
            } else {
                city_data.mission.victory_message_shown = 1;
                window_victory_dialog_show();
            }
        }
    }
}

void city_victory_update_months_to_govern(void) {
    if (city_data.mission.has_won)
        city_data.mission.continue_months_left--;
}

void city_victory_continue_governing(int months) {
    city_data.mission.has_won = 1;
    city_data.mission.continue_months_left += months;
    city_data.mission.continue_months_chosen = months;
    city_data.emperor.salary_rank = 0;
    city_data.emperor.salary_amount = 0;
    city_finance_update_salary();
}

void city_victory_stop_governing(void) {
    city_data.mission.has_won = 0;
    city_data.mission.continue_months_left = 0;
    city_data.mission.continue_months_chosen = 0;
}

int city_victory_has_won(void) {
    return city_data.mission.has_won;
}

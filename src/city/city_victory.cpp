#include "city/city_victory.h"

#include "building/building_type.h"
#include "city/city.h"
#include "content/vfs.h"
#include "game/game.h"
#include "game/game_config.h"
#include "io/gamestate/boilerplate.h"
#include "js/js_game.h"
#include "core/profiler.h"
#include "scenario/criteria.h"
#include "scenario/scenario.h"

#include <algorithm>

victory_rules_t ANK_VARIABLE(victory_rules);

void city_victory_t::reset() {
    state = e_victory_state_none;
    force_win = false;
    force_lost = false;
    lost_by_population = false;
    lost_can_replay = false;
    emit(js_helpers::es_hash_str(esid(), __func__));
}

void city_victory_t::victory_check() {
    emit(js_helpers::es_hash_str(esid(), __func__));
}

int city_victory_end_year() {
    int end_year = scenario_criteria_max_year();
    if (g_scenario.win_criteria.time_limit.enabled) {
        end_year += victory_rules.time_limit_extra_years.get();
    }
    return end_year;
}

int city_count_houses_at_least(int min_level) {
    if (min_level < HOUSE_CRUDE_HUT) {
        min_level = HOUSE_CRUDE_HUT;
    }

    int count = 0;
    for (int level = min_level; level < HOUSE_LEVEL_MAX; level++) {
        count += g_city.population.housing_type_counts[level];
    }
    return count;
}

static bool burial_provisions_complete() {
    for (int r = RESOURCES_MIN; r < RESOURCES_MAX; r++) {
        const auto& bp = g_scenario.monuments.burial_provisions[r];
        if (bp.dispatched < bp.required) {
            return false;
        }
    }
    return true;
}

// The remake's editor-events fix: a time limit ends the mission even with the goals met, and survival wins at the
// end year when the mission has no other goal.
static e_victory_state fixed_editor_events_time_check(e_victory_state st, bool& has_goals) {
    const auto& wc = g_scenario.win_criteria;
    const bool had_goals = has_goals;
    if (game.simtime.year >= city_victory_end_year()) {
        if (wc.time_limit.enabled) {
            st = e_victory_state_lost;
        } else if (wc.survival_time.enabled) {
            if (!had_goals) {
                st = e_victory_state_won;
            } else if (st != e_victory_state_won) {
                st = e_victory_state_lost;
            }
        }
    } else if (wc.survival_time.enabled) {
        st = e_victory_state_none;
    }

    if (wc.time_limit.enabled || wc.survival_time.enabled) {
        has_goals = true;
    }
    return st;
}

e_victory_state city_victory_t::determine_state(bool script_goals_met) {
    const auto& wc = g_scenario.win_criteria;
    lost_by_population = false;

    e_victory_state st = e_victory_state_won;
    int goals = 0;
    if (wc.culture.enabled) {
        goals++;
        if (g_city.ratings.culture < wc.culture.goal) {
            st = e_victory_state_none;
        }
    }
    if (wc.prosperity.enabled) {
        goals++;
        if (g_city.ratings.prosperity < wc.prosperity.goal) {
            st = e_victory_state_none;
        }
    }
    if (wc.population.enabled) {
        goals++;
        if (g_city.population.current < wc.population.goal) {
            st = e_victory_state_none;
        }
    }
    if (wc.monuments.enabled) {
        goals++;
        if (g_city.ratings.monument < wc.monuments.goal || !burial_provisions_complete()) {
            st = e_victory_state_none;
        }
    }
    if (wc.kingdom.enabled) {
        goals++;
        if (g_city.kingdome.rating < wc.kingdom.goal) {
            st = e_victory_state_none;
        }
    }
    if (wc.housing_count.enabled) {
        goals++;
        const int min_level = wc.housing_level.enabled ? wc.housing_level.goal : 0;
        if (city_count_houses_at_least(min_level) < wc.housing_count.goal) {
            st = e_victory_state_none;
        }
    }
    if (!script_goals_met) {
        st = e_victory_state_none;
    }

    if (!!game_features::gameplay_fix_editor_events) {
        bool has_goals = goals > 0;
        if (!has_goals) {
            st = e_victory_state_none;
        }
        st = fixed_editor_events_time_check(st, has_goals);
        goals = has_goals ? 1 : 0;
    } else {
        const bool time_limit = wc.time_limit.enabled;
        const bool survival = wc.survival_time.enabled;
        bool check_time = true;
        if (goals <= 0) {
            st = e_victory_state_none;
            goals += time_limit ? 1 : 0;
            goals += survival ? 1 : 0;
        } else if (st == e_victory_state_won && !survival) {
            check_time = false;
        }

        if (check_time) {
            if (game.simtime.year >= city_victory_end_year()) {
                if (time_limit) {
                    st = e_victory_state_lost;
                } else if (survival && st == e_victory_state_none) {
                    st = e_victory_state_lost;
                }
            } else if (survival) {
                st = e_victory_state_none;
            }
        }
    }

    const auto& figures = g_city.figures;
    const int invaders = figures.total_invading_enemies();
    const int fraction = std::max(1, victory_rules.lost_population_fraction);
    if (invaders > figures.soldiers + victory_rules.lost_population_extra_enemies
        && g_city.population.current < g_city.population.highest_ever / fraction) {
        st = e_victory_state_lost;
        lost_by_population = true;
    }
    if (invaders > 0 && g_city.population.current <= 0) {
        st = e_victory_state_lost;
        lost_by_population = true;
    }

    if (goals <= 0) {
        st = e_victory_state_none;
    }
    return st;
}

void city_victory_t::lost_cleanup() {
    if (g_scenario.scmode == e_scenario_normal) {
        lost_can_replay = true;
        return;
    }
    lost_can_replay = vfs::file_exists(fullpath_saves("autosave_replay.svx"));
}

e_defeat_options city_victory_t::defeat_options() const {
    if (!lost_by_population) {
        if (!lost_can_replay) {
            return e_defeat_options_new_game;
        }
        if (g_scenario.win_criteria.time_limit.enabled && game_difficulty() > DIFFICULTY_VERY_EASY) {
            return e_defeat_options_lower_difficulty;
        }
    }
    return lost_can_replay ? e_defeat_options_replay : e_defeat_options_new_game;
}

void city_victory_t::lower_difficulty() {
    const int value = std::min<int>(game_difficulty() - 1, victory_rules.lower_difficulty_max);
    game.difficulty.set((e_difficulty)value);
}

// OG city_victory_score (monument_city.c); OG has no guard against the first month (months 0).
int city_victory_score(int months, int monument_weight) {
    const double m = std::max(months, 1);
    const double weight = monument_weight;
    const int ratings = g_city.kingdome.rating + g_city.ratings.prosperity + g_city.ratings.culture;
    const double rating_part = (double)ratings * ((double)g_city.population.current * 0.002);
    const double monument_part = (weight / (m * m * 0.00015625)) * (weight * 20.0);
    double score = monument_part + rating_part;
    score = score + (double)(int)g_city.finance.treasury / (m * 0.03333333333333333);
    score = score * (((double)game_difficulty() + 1.0) * 0.3333333333333333);
    return (int)(int64_t)score;
}

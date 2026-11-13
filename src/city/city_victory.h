#pragma once

#include "core/archive.h"
#include "core/xstring.h"
#include "game/difficulty.h"
#include "game/game_system.h"

struct event_update_victory_state { int population; };

enum e_victory_state {
    e_victory_state_lost = -1,
    e_victory_state_none = 0,
    e_victory_state_won = 1
};

enum e_defeat_options {
    e_defeat_options_new_game = 1,
    e_defeat_options_replay = 2,
    e_defeat_options_lower_difficulty = 3
};

// time_limit_extra_years: years added to a time limit per difficulty (OG EXTRA_YEARS_VERY_EASY/EASY).
// lost_population_extra_enemies / lost_population_fraction: the city is lost when enemies and kingdom soldiers
// outnumber its soldiers by more than extra_enemies and the population falls under highest_ever / fraction.
// lower_difficulty_max: the highest difficulty "Lower Difficulty" can leave (OG DEFEAT_EASIER_MAX_DIFFICULTY).
struct victory_rules_t {
    int_dcy time_limit_extra_years;
    int lost_population_extra_enemies;
    int lost_population_fraction;
    int lower_difficulty_max;
};
ANK_CONFIG_STRUCT(victory_rules_t, time_limit_extra_years, lost_population_extra_enemies, lost_population_fraction,
  lower_difficulty_max)
extern victory_rules_t victory_rules;

struct city_victory_t : public game_system {
    ANK_ESID(city_victory)

    e_victory_state state;
    bool force_win;
    bool force_lost;
    bool lost_by_population;
    bool lost_can_replay;

    void reset();
    void victory_check();

    e_victory_state determine_state(bool script_goals_met);
    void lost_cleanup();
    e_defeat_options defeat_options() const;
    void lower_difficulty();
};

int city_victory_end_year();
int city_count_houses_at_least(int min_level);

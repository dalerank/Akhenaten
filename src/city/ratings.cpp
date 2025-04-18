#include "ratings.h"

#include "building/building.h"
#include "building/model.h"
#include "city/coverage.h"
#include "city/city.h"
#include "city/city_population.h"
#include "game/game_config.h"
#include "core/calc.h"
#include "scenario/criteria.h"
#include "scenario/scenario.h"
#include "game/game.h"
#include "js/js_game.h"

#include "dev/debug.h"
#include <iostream>

declare_console_command_p(addprosperity, game_cheat_add_prosperity)
declare_console_command_p(updatekingdome, game_cheat_update_kingdome)
declare_console_command_p(addkingdome, game_cheat_add_kingdome)
declare_console_command_p(addculture, game_cheat_add_culture)

struct rating_points {
    using points_t = svector<city_ratings_t::point, 32>;
    points_t points;

    void load(pcstr section) {
        points.clear();
        g_config_arch.r_array(section, [this] (archive arch) {
            auto &step = points.emplace_back();
            step.coverage = arch.r_int("coverage");
            step.points = arch.r_int("points");
        });
        assert(!points.empty());
    }

    int find(int coverage) {
        for (const auto &p : points) {
            if (coverage >= p.coverage) {
                return p.points;
            }
        }
        return 0;
    }
};

rating_points ANK_VARIABLE(culture_religion_rating_points);
rating_points ANK_VARIABLE(culture_booth_rating_points);

void game_cheat_add_prosperity(std::istream &is, std::ostream &os) {
    std::string args; is >> args;
    int amount = atoi(args.empty() ? (pcstr)"10" : args.c_str());
    g_city.ratings.prosperity = calc_bound(g_city.ratings.prosperity + amount, 0, 100);
};

void game_cheat_add_kingdome(std::istream &is, std::ostream &os) {
    std::string args; is >> args;
    int amount = atoi(args.empty() ? (pcstr)"10" : args.c_str());
    g_city.ratings.kingdom = calc_bound(g_city.ratings.kingdom + amount, 0, 100);
};

void game_cheat_add_culture(std::istream &is, std::ostream &os) {
    std::string args; is >> args;
    int amount = atoi(args.empty() ? (pcstr)"10" : args.c_str());
    g_city.ratings.culture = calc_bound(g_city.ratings.culture + amount, 0, 100);
};

void game_cheat_update_kingdome(std::istream &is, std::ostream &os) {
    std::string args; is >> args;
    int value = atoi(args.empty() ? (pcstr)"0" : args.c_str());
    g_city.ratings.update_kingdom_rating(!!value);
}

int city_ratings_t::selected_explanation() {
    switch (selected) {
    case e_selected_rating_culture:
        return culture_explanation;
    case e_selected_rating_prosperity:
        return prosperity_explanation;
    case e_selected_rating_monument:
        return monument_explanation;
    case e_selected_rating_kingdom:
        return kingdom_explanation;
    default:
        return 0;
    }
}

void city_ratings_t::reduce_prosperity_after_bailout() {
    prosperity -= 3;
    if (prosperity < 0) {
        prosperity = 0;
    }

    prosperity_explanation = 8;
}

void city_ratings_t::monument_building_destroyed(e_building_type type) {
    if (building_is_monument(type)) {
        monument_destroyed_buildings++;
    }

    monument_destroyed_buildings = std::min(monument_destroyed_buildings, 12);
}

void city_ratings_t::monument_record_criminal() {
    monument_num_criminals++;
}

void city_ratings_t::monument_record_rioter() {
    monument_num_rioters++;
    monument_riot_cause = g_city.sentiment.low_mood_cause;
}

void city_ratings_t::change_kingdom(int amount) {
    kingdom = calc_bound(kingdom + amount, 0, 100);
}

void city_ratings_t::reset_kingdom() {
    kingdom = 50;
}

void city_ratings_t::reduce_kingdom_missed_request(int penalty) {
    change_kingdom(-penalty);
    kingdom_ignored_request_penalty = penalty;
}

void city_ratings_t::increase_kingdom_success_request(int value) {
    change_kingdom(value);
}

void city_ratings_t::limit_kingdom(int max_kingdom) {
    if (kingdom > max_kingdom) {
        kingdom = max_kingdom;
    }
}

void city_ratings_t::update_culture_explanation() {
    int min_percentage = 100;
    int reason = 1;
    if (g_city.avg_coverage.average_religion < min_percentage) {
        min_percentage = g_city.avg_coverage.average_religion;
        reason = 4;
    }

    const auto &coverage = g_city.coverage;
    if (coverage.booth < min_percentage) {
        min_percentage = coverage.booth;;
        reason = 5;
    }

    if (coverage.library < min_percentage) {
        min_percentage = coverage.library;
        reason = 2;
    }
    
    if (coverage.school < min_percentage) {
        min_percentage = coverage.school;
        reason = 1;
    }

    if (coverage.academy < min_percentage) {
        reason = 3;
    }

    culture_explanation = reason;
}

void city_ratings_t::update_monument_explanation() {
    int reason;
    if (g_city.figures.kingdome_soldiers) {
        reason = 8; // FIXED: 7+8 interchanged
    } else if (g_city.figures.enemies) {
        reason = 7;
    } else if (g_city.figures.rioters) {
        reason = 6;
    } else {
        if (g_city.ratings.monument < 10)
            reason = 0;
        else if (g_city.ratings.monument < 30)
            reason = 1;
        else if (g_city.ratings.monument < 60)
            reason = 2;
        else if (g_city.ratings.monument < 90)
            reason = 3;
        else if (g_city.ratings.monument < 100)
            reason = 4;
        else { // >= 100
            reason = 5;
        }
    }
    g_city.ratings.monument_explanation = reason;
}

void city_ratings_t::update_kingdom_explanation() {
    kingdom_salary_penalty = 0;
    int salary_delta = g_city.kingdome.salary_rank - g_city.kingdome.player_rank;
    if (g_city.kingdome.player_rank != 0) {
        if (salary_delta > 0) {
            kingdom_salary_penalty = salary_delta + 1;
        }

    } else if (salary_delta > 0) {
        kingdom_salary_penalty = salary_delta;
    }

    if (kingdom_salary_penalty >= 8)
        kingdom_explanation = 1;
    else if (g_city.finance.tribute_not_paid_total_years >= 3)
        kingdom_explanation = 2;
    else if (kingdom_ignored_request_penalty >= 5)
        kingdom_explanation = 3;
    else if (kingdom_salary_penalty >= 5)
        kingdom_explanation = 4;
    else if (g_city.finance.tribute_not_paid_total_years >= 2)
        kingdom_explanation = 5;
    else if (kingdom_ignored_request_penalty >= 3)
        kingdom_explanation = 6;
    else if (kingdom_salary_penalty >= 3)
        kingdom_explanation = 7;
    else if (g_city.finance.tribute_not_paid_last_year)
        kingdom_explanation = 8;
    else if (kingdom_salary_penalty >= 2)
        kingdom_explanation = 9;
    else if (kingdom_milestone_penalty)
        kingdom_explanation = 10;
    else if (kingdom_salary_penalty)
        kingdom_explanation = 11;
    else if (kingdom_change == 2) { // rising
        kingdom_explanation = 12;
    } else if (kingdom_change == 1) { // the same
        kingdom_explanation = 13;
    } else {
        kingdom_explanation = 0;
    }
}

void city_ratings_t::update_culture_rating() {
    culture = 0;
    culture_explanation = 0;

    if (g_city.population.current <= 0) {
        return;
    }

    culture_points.entertainment = culture_booth_rating_points.find(g_city.coverage.booth);
    culture += culture_points.entertainment;

    culture_points.religion = culture_religion_rating_points.find(g_city.religion.coverage_common);
    culture += culture_points.religion;

    const int pct_school = g_city.coverage.school;
    if (pct_school >= 100)
        culture_points.school = 15;
    else if (pct_school > 85)
        culture_points.school = 10;
    else if (pct_school > 70)
        culture_points.school = 6;
    else if (pct_school > 50)
        culture_points.school = 4;
    else if (pct_school > 30)
        culture_points.school = 1;
    else {
        culture_points.school = 0;
    }
    culture += culture_points.school;

    const int pct_academy = g_city.coverage.academy;
    if (pct_academy >= 100)
        culture_points.academy = 10;
    else if (pct_academy > 85)
        culture_points.academy = 7;
    else if (pct_academy > 70)
        culture_points.academy = 4;
    else if (pct_academy > 50)
        culture_points.academy = 2;
    else if (pct_academy > 30)
        culture_points.academy = 1;
    else {
        culture_points.academy = 0;
    }
    culture += culture_points.academy;

    const int pct_library = g_city.coverage.library;
    if (pct_library >= 100)
        culture_points.library = 20;
    else if (pct_library > 85)
        culture_points.library = 14;
    else if (pct_library > 70)
        culture_points.library = 8;
    else if (pct_library > 50)
        culture_points.library = 4;
    else if (pct_library > 30)
        culture_points.library = 2;
    else {
        culture_points.library = 0;
    }
    culture += culture_points.library;

    culture = calc_bound(culture, 0, 100);
    update_culture_explanation();
}

void city_ratings_t::update_monument_rating() {
    int change = 0;
    if (monument_years_of_monument < 2)
        change += 2;
    else {
        change += 5;
    }
    if (monument_num_criminals)
        change -= 1;

    if (monument_num_rioters)
        change -= 5;

    if (monument_destroyed_buildings)
        change -= monument_destroyed_buildings;

    if (monument_num_rioters || monument_destroyed_buildings)
        monument_years_of_monument = 0;
    else {
        monument_years_of_monument += 1;
    }

    monument_num_criminals = 0;
    monument_num_rioters = 0;
    monument_destroyed_buildings = 0;

    int max_population_limit = std::min<int>(city_population(), 4000);
    int monument_ratings_cap = std::max(1, max_population_limit / 1000) * 25;

    monument = calc_bound(monument + change, 0, monument_ratings_cap);
    update_monument_explanation();
}

void city_ratings_t::update_kingdom_rating_year() {
    kingdom_salary_penalty = 0;
    kingdom_milestone_penalty = 0;
    kingdom_ignored_request_penalty = 0;

    const bool can_update_rating = !game_features::gameplay_save_year_kingdome_rating;
    if (can_update_rating && scenario_is_before_mission(3)) {
        kingdom -= 2;
    }

    // tribute penalty
    if (g_city.finance.tribute_not_paid_last_year) {
        if (g_city.finance.tribute_not_paid_total_years <= 1) {
            kingdom -= 3;
        } else if (g_city.finance.tribute_not_paid_total_years <= 2) {
            kingdom -= 5;
        } else {
            kingdom -= 8;
        }
    }

    // rank salary
    int salary_delta = g_city.kingdome.salary_rank - g_city.kingdome.player_rank;
    if (g_city.kingdome.player_rank != 0) {
        if (salary_delta > 0) {
            // salary too high
            kingdom -= salary_delta;
            kingdom_salary_penalty = salary_delta + 1;
        } else if (salary_delta < 0) {
            // salary lower than rank
            kingdom += 1;
        }
    } else if (salary_delta > 0) {
        kingdom -= salary_delta;
        kingdom_salary_penalty = salary_delta;
    }

    // milestone
    int milestone_pct = 0;
    if (scenario_criteria_milestone_year(25) == game.simtime.year) {
        milestone_pct = 25;
    } else if (scenario_criteria_milestone_year(50) == game.simtime.year) {
        milestone_pct = 50;
    } else if (scenario_criteria_milestone_year(75) == game.simtime.year) {
        milestone_pct = 75;
    }

    if (milestone_pct) {
        int bonus = 1;
        if (winning_culture() && culture < calc_adjust_with_percentage(winning_culture(), milestone_pct)) {
            bonus = 0;
        }
        if (winning_prosperity() && prosperity < calc_adjust_with_percentage(winning_prosperity(), milestone_pct)) {
            bonus = 0;
        }
        if (winning_monuments() && monument < calc_adjust_with_percentage(winning_monuments(), milestone_pct)) {
            bonus = 0;
        }
        if (winning_kingdom() && kingdom < calc_adjust_with_percentage(winning_kingdom(), milestone_pct)) {
            bonus = 0;
        }
        if (winning_population() && g_city.population.current < calc_adjust_with_percentage(winning_population(), milestone_pct)) {
            bonus = 0;
        }

        if (bonus) {
            kingdom += 5;
        } else {
            kingdom -= 2;
            kingdom_milestone_penalty = 2;
        }
    }

    if (kingdom < kingdom_last_year) {
        kingdom_change = e_rating_dropping;
    } else if (kingdom == kingdom_last_year) {
        kingdom_change = e_rating_stalling;
    } else {
        kingdom_change = e_rating_rising;
    }

    kingdom_last_year = kingdom;
}

void city_ratings_t::update_kingdom_rating(bool is_yearly_update) {
    if (scenario_is_open_play()) {
        kingdom = 50;
        return;
    }

    g_city.kingdome.months_since_gift++;
    if (g_city.kingdome.months_since_gift >= 12) {
        g_city.kingdome.gift_overdose_penalty = 0;
    }

    if (is_yearly_update) {
        update_kingdom_rating_year();
    }

    kingdom = calc_bound(kingdom, 0, 100);
    update_kingdom_explanation();
}
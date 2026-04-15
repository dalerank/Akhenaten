#include "ratings.h"

#include "building/building.h"
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

declare_console_command_p(addprosperity) {
    std::string args; is >> args;
    int amount = atoi(args.empty() ? (pcstr)"10" : args.c_str());
    g_city.ratings.prosperity = calc_bound(g_city.ratings.prosperity + amount, 0, 100);
}

declare_console_command_p(addculture) {
    std::string args; is >> args;
    int amount = atoi(args.empty() ? (pcstr)"10" : args.c_str());
    g_city.ratings.culture = calc_bound(g_city.ratings.culture + amount, 0, 100);
};

struct rating_points {
    using points_t = svector<city_ratings_t::point, 32>;
    points_t points;

    void archive_init() { verify_no_crash(!points.empty()); }

    void archive_unload() { points.clear(); }
    auto &emplace_back() { return points.emplace_back(); }

    int find(int coverage) {
        for (const auto &p : points) {
            if (coverage >= p.coverage) {
                return p.points;
            }
        }
        return 0;
    }
};
ANK_CONFIG_STRUCT(rating_points, points)

rating_points ANK_OBJECTS_VARIABLE(culture_religion_rating_points);
rating_points ANK_OBJECTS_VARIABLE(culture_booth_rating_points);
rating_points ANK_OBJECTS_VARIABLE(culture_school_rating_points);
rating_points ANK_OBJECTS_VARIABLE(culture_academy_rating_points);
rating_points ANK_OBJECTS_VARIABLE(culture_library_rating_points);

void city_ratings_t::reduce_prosperity_after_bailout() {
    prosperity -= 3;
    if (prosperity < 0) {
        prosperity = 0;
    }

    prosperity_explanation = 8;
}

void city_ratings_t::monument_building_destroyed(e_building_type type) {
    const auto &bparams = building_static_params::get(type);
    if (bparams.flags.is_monument) {
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

    culture_points.school = culture_school_rating_points.find(g_city.coverage.school);
    culture += culture_points.school;

    culture_points.academy = culture_academy_rating_points.find(g_city.coverage.academy);
    culture += culture_points.academy;

    culture_points.library = culture_library_rating_points.find(g_city.coverage.library);
    culture += culture_points.library;

    // Add culture bonus from working jewels workshops: +1 per every 3 workshops (if enabled)
    if (!!game_features::gameplay_jewels_workshops_culture_bonus) {
        int active_jewels_workshops = g_city.buildings.buildings[BUILDING_JEWELS_WORKSHOP].active;
        int jewels_workshops_culture_bonus = active_jewels_workshops / 3;
        culture += jewels_workshops_culture_bonus;
    }

    culture = calc_bound(culture, 0, 100);
}
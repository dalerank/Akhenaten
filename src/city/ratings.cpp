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


declare_console_command_p(addprosperity) {
    int amount = args.next_int(10);
    g_city.ratings.prosperity = calc_bound(g_city.ratings.prosperity + amount, 0, 100);
}

declare_console_command_p(addculture) {
    int amount = args.next_int(10);
    g_city.ratings.culture = calc_bound(g_city.ratings.culture + amount, 0, 100);
};

struct culture_rating_record {
    xstring coverage;
    svector<int, 8> points;
    svector<int, 8> limits;
};
ANK_CONFIG_STRUCT(culture_rating_record, coverage, points, limits)

// OG culture_records (city_data.c) and city_ratings_culture_bonus, in scripts/city/ratings.js.
struct culture_rating_params_t {
    svector<culture_rating_record, 16> records;
    svector<int, 8> bonus_limits;
    int bonus_margin;
    int bonus_points;
};
ANK_CONFIG_STRUCT(culture_rating_params_t, records, bonus_limits, bonus_margin, bonus_points)
culture_rating_params_t ANK_VARIABLE(culture_rating);

namespace {

    int culture_coverage_value(const xstring& coverage) {
        const auto& c = g_city.coverage;
        if (coverage == "jugglers")
            return c.booth;
        if (coverage == "musicians")
            return c.bandstand;
        if (coverage == "dancers")
            return c.pavilion;
        if (coverage == "senet")
            return c.senet_house;
        if (coverage == "zoo")
            return c.zoo;
        if (coverage == "school")
            return c.school;
        if (coverage == "library")
            return c.library;
        if (coverage == "religion")
            return g_city.religion.coverage_common;
        if (coverage == "dentist")
            return c.dentist;
        if (coverage == "physician")
            return c.physician;
        if (coverage == "mortuary")
            return c.mortuary;
        logs::error("[culture] unknown coverage %s in culture_rating.records", coverage.c_str());
        return 0;
    }

    // Band i (i >= 1) is coverage below limits[i]; band 0 is coverage up to limits[0]; past the last limit
    // the last points apply.
    int culture_points(const svector<int, 8>& points, const svector<int, 8>& limits, int coverage) {
        if (points.empty()) {
            return 0;
        }
        if (!limits.empty() && coverage <= limits[0]) {
            return points[0];
        }
        for (size_t band = 1; band < limits.size() && band < points.size(); ++band) {
            if (coverage < limits[band]) {
                return points[band];
            }
        }
        return points.back();
    }

} // namespace

void city_ratings_t::reduce_prosperity_after_bailout() {
    prosperity -= 3;
    if (prosperity < 0) {
        prosperity = 0;
    }

    prosperity_explanation = e_prosperity_reason_tribute_not_paid;
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
    const auto& records = culture_rating.records;
    int lowest_points = 100;
    int lowest_index = 0;
    for (int i = 0; i < (int)records.size(); ++i) {
        const int points
          = culture_points(records[i].points, records[i].limits, culture_coverage_value(records[i].coverage));
        if (points < lowest_points) {
            lowest_points = points;
            lowest_index = i;
        }
    }

    // OG quirk: a category earns the bonus when its points are bonus_margin *below* the lowest, which only
    // the 90-limit records (dentist, physician) can reach, at 90..99% coverage.
    int bonus = 0;
    for (const auto& r : records) {
        const int points = culture_points(r.points, culture_rating.bonus_limits, culture_coverage_value(r.coverage));
        if (points + culture_rating.bonus_margin < lowest_points) {
            bonus += culture_rating.bonus_points;
        }
    }

    culture = lowest_points + bonus;

    if (!!game_features::gameplay_jewels_workshops_culture_bonus) {
        const int active_jewels_workshops = g_city.buildings.buildings[BUILDING_JEWELS_WORKSHOP].active;
        culture += active_jewels_workshops / 3;
    }

    culture = calc_bound(culture, 0, 100);
    culture_explanation = lowest_index;
}

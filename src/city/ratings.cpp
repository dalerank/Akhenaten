#include "ratings.h"
#include "city/city_kingdome_relations.h"
#include "city/city_religion.h"
#include "city/ratings.h"
#include "city/entertainment.h"
#include "io/gamestate/save_versions.h"
#include "io/chunk_serializer.h"
#include "core/xvalue.h"
#include "city/ratings_chunks.h"
#include "city/city_sentiment.h"
#include "game/simulation.h"
#include "core/app_module.h"
#include "game/sim_schedule.h"

#include "building/building.h"
#include "city/coverage.h"
#include "city/city.h"
#include "city/city_population.h"
#include "game/game_config.h"
#include "core/calc.h"
#include "scenario/criteria.h"
#include "scenario/scenario.h"
#include "game/game.h"
#include "js/js_register.h"

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
        const auto& c = city_coverage();
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
            return city_gods().coverage_common;
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
    monument_riot_cause = city_sentiment().low_mood_cause;
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

void city_ratings_t::update(bool is_yearly_update) {
    update_culture_rating();
    if (is_yearly_update) {
        city_kingdome().advance_year();
    }
    calculate_max_prosperity();

    if (is_prosperity_update_month(g_simulation.simtime.month)) {
        update_prosperity_rating();
    }
}

city_ratings_t& city_ratings() {
    return xvalue<city_ratings_t>::ref();
}

void city_ratings_t::reset() {
    *this = {};
}

class ratings_sim_system : public sim_system {
public:
    const char* name() const override { return "ratings"; }
    void on_reset() override { city_ratings().reset(); }
    void push_save_sections(int file_version) override {
        if (file_version >= save_version_city_sections) {
            g_chunk_io.push_chunk<city_ratings_chunk>(city_ratings_chunk::size, false);
        }
    }
    void register_steps(sim_schedule_t& schedule) override {
        schedule.add({sim_step_ratings_year, SIM_PHASE_YEAR, [](int) { city_ratings().update(true); }});
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_ratings_system) {
    static ratings_sim_system system;
    g_simulation.register_system(&system);
}

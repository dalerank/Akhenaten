#pragma once

#include <cstdint>
#include "building/building_type.h"
#include "core/archive.h"
#include "city/city_kingdome_relations.h"

enum e_prosperity_trend {
    e_prosperity_rising = 0,
    e_prosperity_falling = 1,
    e_prosperity_same = 2,
};

// OG prosperity_reason: the ratings advisor shows text 53/(20 + reason).
enum e_prosperity_reason {
    e_prosperity_reason_none = 0,
    e_prosperity_reason_at_cap = 3,
    e_prosperity_reason_finances = 4,
    e_prosperity_reason_unemployment = 5,
    e_prosperity_reason_wages = 6,
    e_prosperity_reason_too_many_huts = 7,
    e_prosperity_reason_tribute_not_paid = 8,
    e_prosperity_reason_workers_needed = 10,
    e_prosperity_reason_trade = 11,
};

struct ratings_state {
    int32_t culture;
    int32_t prosperity;
    int32_t monument;
    int32_t prosperity_trend;

    int32_t prosperity_max;
    int32_t monument_destroyed_buildings;
    int32_t monument_years_of_monument;
    int32_t monument_num_criminals;
    int32_t monument_num_rioters;
    int32_t monument_riot_cause;

    int32_t culture_explanation;
    int32_t prosperity_explanation;

    void reduce_prosperity_after_bailout();
};

ANK_CONFIG_PROPERTY(ratings_state, culture, prosperity, monument, culture_explanation, prosperity_explanation,
  prosperity_max, prosperity_trend)

struct finance_state;
struct city_labor_t;
struct city_resources_t;
struct population_state;
struct city_entertainment_t;
struct city_coverage_t;
struct gods_state;
struct city_sentiment_t;
struct city_buildings_t;

struct ratings_context {
    const finance_state& finance;
    const city_labor_t& labor;
    city_resources_t& resource;
    const population_state& population;
    const city_entertainment_t& entertainment;
    const city_coverage_t& coverage;
    const gods_state& gods;
    const city_sentiment_t& sentiment;
    const city_buildings_t& buildings;
    kingdome_system kingdome_sys;
    bool ra_oracle;
    int year;
    int month;
    int start_year;
};

class ratings_system {
public:
    ratings_system(ratings_state& state, const ratings_context& ctx) : _state(state), _ctx(ctx) {}

    static bool is_prosperity_update_month(int month);

    void update(bool is_yearly_update);
    void update_culture_rating();
    void update_prosperity_rating();
    void update_prosperity_explanation();
    void calculate_max_prosperity();
    void monument_building_destroyed(e_building_type type);
    void monument_record_criminal();
    void monument_record_rioter();

private:
    ratings_state& _state;
    ratings_context _ctx;
};

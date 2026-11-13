#pragma once

#include <cstdint>
#include "building/building_type.h"
#include "core/archive.h"

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

struct city_ratings_t {
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
    void monument_building_destroyed(e_building_type type);
    void monument_record_criminal();
    void monument_record_rioter();

    void update_culture_rating();
};

ANK_CONFIG_PROPERTY(city_ratings_t, culture, prosperity, monument, culture_explanation, prosperity_explanation,
  prosperity_max, prosperity_trend)

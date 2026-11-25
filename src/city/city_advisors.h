#pragma once

#include "city/constants.h"

struct city_advisors_t {
    e_availability advisors[ADVISOR_MAX];
    e_availability empire_screen = AVAILABLE;

    e_availability is_advisor_available(e_advisor advisor) const { return advisors[advisor]; }
    void set_advisor_available(e_advisor advisor, e_availability available) { advisors[advisor] = available; }

    e_availability is_empire_available() const { return empire_screen; }
    void set_empire_available(e_availability available) { empire_screen = available; }

    void reset();
};

city_advisors_t& city_advisors();

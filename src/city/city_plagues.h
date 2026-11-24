#pragma once

#include <cstdint>

// OG city_locusts_countdown (-1 = waiting for the flood), city_frogs_countdown, mummies_max.
struct city_plagues_t {
    int32_t locusts_countdown;
    int32_t frogs_countdown;
    int32_t mummies_max;

    void reset();
    void decrease_countdowns();
};

city_plagues_t& city_plagues();

#pragma once

#include <cstdint>

struct city_entertainment_t {
    int32_t booth_shows;
    int32_t booth_no_shows_weighted;
    int32_t bandstand_shows;
    int32_t bandstand_no_shows_weighted;
    int32_t pavilion_shows;
    int32_t pavilion_no_shows_weighted;
    int32_t senet_house_plays;
    int32_t senet_house_no_shows_weighted;
    int32_t venue_needing_shows;
    bool senet_house_has_plays;
    bool senet_house_message_shown;
    bool pavilion_message_shown;

    void calculate_shows();
    int show_message_pavilion();
    int show_message_senet_house();
};
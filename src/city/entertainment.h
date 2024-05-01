#pragma once

#include <cstdint>

struct city_entertainment_t {
    int32_t theater_shows;
    int32_t theater_no_shows_weighted;
    int32_t amphitheater_shows;
    int32_t amphitheater_no_shows_weighted;
    int32_t colosseum_shows;
    int32_t colosseum_no_shows_weighted;
    int32_t hippodrome_shows;
    int32_t hippodrome_no_shows_weighted;
    int32_t venue_needing_shows;
    int32_t hippodrome_has_race;
    int32_t hippodrome_message_shown;
    int32_t colosseum_message_shown;

    void calculate_shows(void);
    int show_message_colosseum(void);
    int show_message_hippodrome(void);
};
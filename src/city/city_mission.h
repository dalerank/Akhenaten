#pragma once

struct city_mission_t {
    bool fired_message_shown;
    bool victory_message_shown;

    void reset();
};

city_mission_t& city_mission();

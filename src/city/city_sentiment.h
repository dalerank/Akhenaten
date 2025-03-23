#pragma once

#include <cstdint>

struct city_sentiment_t {
    int32_t value;
    int32_t previous_value;
    int32_t message_delay;

    bool include_huts;
    uint8_t unemployment_pct;
    int32_t wages;
    int32_t low_mood_cause;

    int32_t protesters;
    int32_t criminals; // muggers+rioters
    bool can_create_mugger;
    bool can_create_protestor;
    short last_mugger_message;
    int32_t contribution_taxes;
    int32_t contribution_wages;
    int32_t contribution_employment;
    int32_t contribution_food;
    int32_t contribution_huts;
    int32_t contribution_penalty_huts;
    int32_t contribution_religion_coverage;
    int32_t contribution_monuments;

    void init();
    void update();
    void update_day();
    int calc_contribution_religion_coverage();
    int calc_contribution_monuments();
    int calc_contribution_employment();
    int calc_sentiment_contribution_wages();
    int calc_penalty_for_hut_dwellers();

    void reset_protesters_criminals();
};

void city_show_message_criminal(int message_id, int money_stolen, int tile_offset);


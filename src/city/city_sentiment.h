#pragma once

#include <cstdint>

struct city_sentiment_t {
    int32_t value;
    int32_t previous_value;
    int32_t message_delay;

    bool include_huts;
    int32_t unemployment;
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

    void update();
    void update_day();
};

bool city_can_create_mugger();
bool city_can_create_protestor();

void city_set_can_create_mugger(bool v);
void city_set_can_create_protestor(bool v);

void city_show_message_criminal(int message_id, int money_stolen, int tile_offset);

void city_sentiment_change_happiness(int amount);

void city_sentiment_set_max_happiness(int max);

void city_sentiment_reset_protesters_criminals();

void city_sentiment_add_protester();
void city_sentiment_add_criminal();

int city_sentiment_protesters();
int city_sentiment_criminals();

void city_criminals_update_day();
void city_plague_update_day();
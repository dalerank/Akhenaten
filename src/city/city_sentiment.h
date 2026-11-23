#pragma once

#include "core/archive.h"
#include <cstdint>

struct sentiment_state {
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
};

struct population_state;
struct finance_state;
struct gods_state;
struct labor_state;
struct city_buildings_t;

struct sentiment_context {
    const population_state& population;
    const finance_state& finance;
    gods_state& gods;
    const labor_state& labor;
    city_buildings_t& buildings;
    bool hathor_oracle;
    int day;
    int campaign_scenario_id;
};

class sentiment_system {
public:
    sentiment_system(sentiment_state& state, const sentiment_context& ctx) : _state(state), _ctx(ctx) {}

    void init();
    void update();
    void update_day();
    int calc_contribution_religion_coverage();
    int calc_contribution_monuments();
    int calc_contribution_employment();
    int calc_sentiment_contribution_wages();
    int calc_penalty_for_hut_dwellers();
    void reset_protesters_criminals();

private:
    sentiment_state& _state;
    sentiment_context _ctx;
};
ANK_CONFIG_PROPERTY(sentiment_state, value, criminals)

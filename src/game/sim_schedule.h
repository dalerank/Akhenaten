#pragma once

#include "core/custom_span.hpp"

#include <cstdint>

class city_t;

enum e_sim_phase : uint8_t {
    SIM_PHASE_TICK_BEGIN,
    SIM_PHASE_TICK_SLOT,
    SIM_PHASE_TICK_CITY_END,
    SIM_PHASE_TICK_END,
    SIM_PHASE_DAY,
    SIM_PHASE_WEEK,
    SIM_PHASE_MONTH_CITY,
    SIM_PHASE_MONTH,
    SIM_PHASE_MONTH_END,
    SIM_PHASE_YEAR,
    SIM_PHASE_COUNT
};

enum e_sim_area : uint32_t {
    SIM_AREA_NONE = 0,
    SIM_AREA_POPULATION = 1u << 0,
    SIM_AREA_HOUSES = 1u << 1,
    SIM_AREA_BUILDINGS = 1u << 2,
    SIM_AREA_FIGURES = 1u << 3,
    SIM_AREA_FINANCE = 1u << 4,
    SIM_AREA_RESOURCES = 1u << 5,
    SIM_AREA_RELIGION = 1u << 6,
    SIM_AREA_COVERAGE = 1u << 7,
    SIM_AREA_HEALTH = 1u << 8,
    SIM_AREA_LABOR = 1u << 9,
    SIM_AREA_TRADE = 1u << 10,
    SIM_AREA_KINGDOM = 1u << 11,
    SIM_AREA_SENTIMENT = 1u << 12,
    SIM_AREA_CRIME = 1u << 13,
    SIM_AREA_MAP = 1u << 14,
    SIM_AREA_MILITARY = 1u << 15,
    SIM_AREA_MIGRATION = 1u << 16,
    SIM_AREA_RATINGS = 1u << 17,
    SIM_AREA_MESSAGES = 1u << 18,
    SIM_AREA_EMPIRE = 1u << 19,
    SIM_AREA_SCENARIO = 1u << 20,
    SIM_AREA_MONUMENTS = 1u << 21,
    SIM_AREA_FLOODS = 1u << 22,
    SIM_AREA_FESTIVAL = 1u << 23,
    SIM_AREA_TIME = 1u << 24,
    SIM_AREA_RANDOM = 1u << 25,
    SIM_AREA_UNDO = 1u << 26,
    SIM_AREA_VICTORY = 1u << 27,
    SIM_AREA_EVENTS = 1u << 28,
};

struct sim_step {
    e_sim_phase phase;
    int slot;
    const char* name;
    uint32_t writes;
    void (*run)(city_t& city);
};

span_const<sim_step> sim_schedule_steps();
void sim_schedule_run(e_sim_phase phase, city_t& city, int slot = -1);
const char* sim_phase_name(e_sim_phase phase);

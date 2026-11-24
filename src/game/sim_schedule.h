#pragma once

#include "core/custom_span.hpp"
#include "core/xstring.h"

#include <array>
#include <cstdint>


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
    SIM_AREA_TAXES = 1u << 29,
};

enum e_sim_step : uint16_t {
    sim_step_housing_type_counts,
    sim_step_random,
    sim_step_undo_time,
    sim_step_floods,
    sim_step_buildings_tick,
    sim_step_religion,
    sim_step_coverage,
    sim_step_tree_growth,
    sim_step_kingdome,
    sim_step_irrigation_value,
    sim_step_formations,
    sim_step_natives_land,
    sim_step_road_network,
    sim_step_stocks,
    sim_step_house_service_decay,
    sim_step_desirability,
    sim_step_trade_export_keep,
    sim_step_houses_covered_decay,
    sim_step_storageyard_stocks,
    sim_step_food_stocks,
    sim_step_vegetation_growth,
    sim_step_open_water_access,
    sim_step_industry_production,
    sim_step_kingdome_access,
    sim_step_population_room,
    sim_step_migration,
    sim_step_population_migration,
    sim_step_evict_overcrowded,
    sim_step_labor,
    sim_step_water_supply,
    sim_step_religion_supply,
    sim_step_formations_skip_morale,
    sim_step_crime,
    sim_step_tower_sentry_decay,
    sim_step_generate_figures,
    sim_step_empire_traders,
    sim_step_trade,
    sim_step_building_counters,
    sim_step_avg_coverage_33,
    sim_step_health_coverage,
    sim_step_farms,
    sim_step_distribute_treasury,
    sim_step_house_health,
    sim_step_culture_aggregates,
    sim_step_malaria_risk,
    sim_step_building_desirability,
    sim_step_house_evolve,
    sim_step_building_state,
    sim_step_burning_ruins,
    sim_step_building_destroying,
    sim_step_reset_protesters,
    sim_step_criminals,
    sim_step_building_malaria_risk,
    sim_step_house_tax_coverage_decay,
    sim_step_avg_coverage_49,
    sim_step_plagues,
    sim_step_figures,
    sim_step_scenario,
    sim_step_distant_battle,
    sim_step_invasion_auto_resolve,
    sim_step_sentiment,
    sim_step_criminals_day,
    sim_step_funeral_walkers,
    sim_step_plague_day,
    sim_step_flotsam,
    sim_step_buildings_day,
    sim_step_figures_day,
    sim_step_population_day,
    sim_step_victory,
    sim_step_avg_coverage_day,
    sim_step_event_advance_day,
    sim_step_food_weekly,
    sim_step_industry_nearby_houses,
    sim_step_event_advance_week,
    sim_step_migration_month,
    sim_step_health_month,
    sim_step_population_at_levels,
    sim_step_taxes_month,
    sim_step_finance_month,
    sim_step_food_monthly,
    sim_step_resource_month,
    sim_step_food_supply_month,
    sim_step_allowed_foods,
    sim_step_population_record,
    sim_step_local_cults,
    sim_step_festival,
    sim_step_buildings_month,
    sim_step_fishing_points,
    sim_step_kingdome_month,
    sim_step_tomb_robbers_month,
    sim_step_distant_battle_month,
    sim_step_random_month,
    sim_step_empire_month,
    sim_step_random_events,
    sim_step_invasions,
    sim_step_scenario_events,
    sim_step_invasion_bind_resolutions,
    sim_step_invasion_process,
    sim_step_morale_at_rest,
    sim_step_messages,
    sim_step_roads_images,
    sim_step_land_citizen_routing,
    sim_step_locusts_month,
    sim_step_estimate_taxes,
    sim_step_event_advance_month,
    sim_step_empire_expansion,
    sim_step_undo_disable,
    sim_step_simtime_year,
    sim_step_population_yearly_request,
    sim_step_taxes_year,
    sim_step_finance_year,
    sim_step_migration_year,
    sim_step_monuments_year,
    sim_step_yearly_trade_amounts,
    sim_step_ratings_year,
    sim_step_temple_complexes,
    sim_step_buildings_year,

    sim_step_count
};

struct sim_step {
    e_sim_step id;
    e_sim_phase phase;
    int slot;
    uint32_t writes;
    void (*run)();
};

class sim_schedule_t {
public:
    void add(const sim_step& step);
    span_const<sim_step> steps();
    void run(e_sim_phase phase, int slot = -1);

    static xstring phase_name(e_sim_phase phase);
    static xstring step_name(e_sim_step id);

private:
    void check();

    std::array<sim_step, sim_step_count> _steps{};
    std::array<bool, sim_step_count> _registered{};
    bool _checked = false;
};

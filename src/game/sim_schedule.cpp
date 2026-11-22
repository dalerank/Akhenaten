#include "game/sim_schedule.h"

#include "building/building_barracks.h"
#include "building/building_burning_ruin.h"
#include "building/building_granary.h"
#include "city/buildings.h"
#include "city/city.h"
#include "city/city_desirability.h"
#include "city/city_floods.h"
#include "city/city_industry.h"
#include "city/city_malaria_risk.h"
#include "city/city_message.h"
#include "city/city_population.h"
#include "core/random.h"
#include "empire/empire.h"
#include "empire/empire_traders.h"
#include "figure/formation.h"
#include "figuretype/figure_flotsam.h"
#include "figuretype/figure_funeral_walker.h"
#include "figuretype/figure_locust.h"
#include "figuretype/figure_tomb_robber.h"
#include "game/game.h"
#include "game/game_config.h"
#include "game/undo.h"
#include "grid/crime.h"
#include "grid/irrigation_value.h"
#include "grid/malaria_risk.h"
#include "grid/natives.h"
#include "grid/routing/routing_terrain.h"
#include "grid/tiles.h"
#include "grid/trees.h"
#include "grid/vegetation.h"
#include "scenario/distant_battle.h"
#include "scenario/empire.h"
#include "scenario/invasion_auto_resolve.h"
#include "scenario/scenario.h"
#include "scenario/scenario_event_manager.h"
#include "scenario/scenario_invasion.h"

#include <array>

static const sim_step k_sim_steps[] = {
  {SIM_PHASE_TICK_BEGIN, -1, "housing_type_counts", SIM_AREA_POPULATION,
    [](city_t& c) { c.population.housing_type_counts_update(); }},
  {SIM_PHASE_TICK_BEGIN, -1, "random", SIM_AREA_RANDOM, [](city_t&) { random_generate_next(); }},
  {SIM_PHASE_TICK_BEGIN, -1, "undo_time", SIM_AREA_UNDO, [](city_t&) { game_undo_reduce_time_available(); }},
  {SIM_PHASE_TICK_BEGIN, -1, "floods", SIM_AREA_FLOODS | SIM_AREA_MAP, [](city_t&) { g_floods.tick_update(false); }},
  {SIM_PHASE_TICK_BEGIN, -1, "buildings_tick", SIM_AREA_BUILDINGS,
    [](city_t& c) { c.buildings.update_tick(game.paused); }},

  {SIM_PHASE_TICK_SLOT, 1, "religion", SIM_AREA_RELIGION, [](city_t& c) { c.religion.update(); }},
  {SIM_PHASE_TICK_SLOT, 1, "coverage", SIM_AREA_COVERAGE, [](city_t& c) { c.coverage.update(); }},
  {SIM_PHASE_TICK_SLOT, 2, "tree_growth", SIM_AREA_MAP, [](city_t&) { map_tree_growth_update(); }},
  {SIM_PHASE_TICK_SLOT, 4, "kingdome", SIM_AREA_KINGDOM, [](city_t& c) { c.kingdome.update(); }},
  {SIM_PHASE_TICK_SLOT, 5, "irrigation_value", SIM_AREA_MAP, [](city_t&) { g_irrigation_value.update(); }},
  {SIM_PHASE_TICK_SLOT, 5, "formations", SIM_AREA_MILITARY, [](city_t&) { formation_update_all(false); }},
  {SIM_PHASE_TICK_SLOT, 6, "natives_land", SIM_AREA_MAP, [](city_t&) { map_natives_check_land(); }},
  {SIM_PHASE_TICK_SLOT, 7, "road_network", SIM_AREA_MAP, [](city_t& c) { c.map.update_road_network(); }},
  {SIM_PHASE_TICK_SLOT, 8, "stocks", SIM_AREA_RESOURCES, [](city_t& c) { c.resource.calculate_stocks(); }},
  {SIM_PHASE_TICK_SLOT, 9, "house_service_decay", SIM_AREA_HOUSES, [](city_t& c) { c.house_decay_services(); }},
  {SIM_PHASE_TICK_SLOT, 10, "desirability", SIM_AREA_MAP, [](city_t&) { g_desirability.update(); }},
  {SIM_PHASE_TICK_SLOT, 11, "trade_export_keep", SIM_AREA_TRADE, [](city_t&) { city_trade_update_export_keep(); }},
  {SIM_PHASE_TICK_SLOT, 12, "houses_covered_decay", SIM_AREA_BUILDINGS,
    [](city_t& c) { c.house_service_decay_houses_covered(); }},
  {SIM_PHASE_TICK_SLOT, 16, "storageyard_stocks", SIM_AREA_RESOURCES,
    [](city_t&) { city_resource_calculate_storageyard_stocks(); }},
  {SIM_PHASE_TICK_SLOT, 17, "food_stocks", SIM_AREA_RESOURCES,
    [](city_t& c) { c.resource.calculate_food_stocks_and_supply_wheat(); }},
  {SIM_PHASE_TICK_SLOT, 18, "vegetation_growth", SIM_AREA_MAP, [](city_t&) { map_vegetation_growth_update(); }},
  {SIM_PHASE_TICK_SLOT, 19, "open_water_access", SIM_AREA_BUILDINGS,
    [](city_t& c) { c.buildings_update_open_water_access(); }},
  {SIM_PHASE_TICK_SLOT, 20, "industry_production", SIM_AREA_BUILDINGS,
    [](city_t& c) { c.industry.update_production(); }},
  {SIM_PHASE_TICK_SLOT, 21, "kingdome_access", SIM_AREA_BUILDINGS,
    [](city_t& c) { c.maintenance.check_kingdome_access(); }},
  {SIM_PHASE_TICK_SLOT, 22, "population_room", SIM_AREA_POPULATION, [](city_t& c) { c.population.update_room(); }},
  {SIM_PHASE_TICK_SLOT, 23, "migration", SIM_AREA_MIGRATION, [](city_t& c) { c.migration.update(); }},
  {SIM_PHASE_TICK_SLOT, 23, "population_migration", SIM_AREA_POPULATION,
    [](city_t& c) { c.population.update_migration(); }},
  {SIM_PHASE_TICK_SLOT, 24, "evict_overcrowded", SIM_AREA_POPULATION | SIM_AREA_FIGURES,
    [](city_t& c) { c.population.evict_overcrowded(); }},
  {SIM_PHASE_TICK_SLOT, 25, "labor", SIM_AREA_LABOR, [](city_t& c) { c.labor.update(); }},
  {SIM_PHASE_TICK_SLOT, 27, "water_supply", SIM_AREA_BUILDINGS, [](city_t& c) { c.buildings.update_water_supply(); }},
  {SIM_PHASE_TICK_SLOT, 28, "religion_supply", SIM_AREA_HOUSES,
    [](city_t& c) { c.buildings.update_religion_supply_houses(); }},
  {SIM_PHASE_TICK_SLOT, 29, "formations_skip_morale", SIM_AREA_MILITARY, [](city_t&) { formation_update_all(true); }},
  {SIM_PHASE_TICK_SLOT, 30, "crime", SIM_AREA_CRIME, [](city_t&) { g_crime.update(); }},
  {SIM_PHASE_TICK_SLOT, 31, "tower_sentry_decay", SIM_AREA_MILITARY,
    [](city_t&) { building_barracks_decay_tower_sentry_request(); }},
  {SIM_PHASE_TICK_SLOT, 31, "generate_figures", SIM_AREA_FIGURES, [](city_t& c) { c.buildings_generate_figure(); }},
  {SIM_PHASE_TICK_SLOT, 32, "empire_traders", SIM_AREA_TRADE | SIM_AREA_FIGURES,
    [](city_t&) { g_empire_traders.update(); }},
  {SIM_PHASE_TICK_SLOT, 32, "trade", SIM_AREA_TRADE | SIM_AREA_FIGURES, [](city_t& c) { c.trade_update(); }},
  {SIM_PHASE_TICK_SLOT, 33, "building_counters", SIM_AREA_BUILDINGS, [](city_t& c) { c.buildings.update_counters(); }},
  {SIM_PHASE_TICK_SLOT, 33, "avg_coverage", SIM_AREA_COVERAGE, [](city_t& c) { c.avg_coverage.update(); }},
  {SIM_PHASE_TICK_SLOT, 33, "health_coverage", SIM_AREA_COVERAGE | SIM_AREA_HEALTH,
    [](city_t& c) { c.health.update_coverage(); }},
  {SIM_PHASE_TICK_SLOT, 33, "farms", SIM_AREA_BUILDINGS, [](city_t&) { building_industry_update_farms(); }},
  {SIM_PHASE_TICK_SLOT, 34, "distribute_treasury", SIM_AREA_FINANCE | SIM_AREA_BUILDINGS,
    [](city_t& c) { c.government_distribute_treasury(); }},
  {SIM_PHASE_TICK_SLOT, 35, "house_health", SIM_AREA_HOUSES, [](city_t& c) { c.house_service_update_health(); }},
  {SIM_PHASE_TICK_SLOT, 36, "culture_aggregates", SIM_AREA_HOUSES,
    [](city_t& c) { c.house_service_calculate_culture_aggregates(); }},
  {SIM_PHASE_TICK_SLOT, 37, "malaria_risk", SIM_AREA_MAP, [](city_t&) { g_malaria_risk.update(); }},
  {SIM_PHASE_TICK_SLOT, 38, "building_desirability", SIM_AREA_BUILDINGS,
    [](city_t&) { building_update_desirability(); }},
  {SIM_PHASE_TICK_SLOT, 39, "house_evolve", SIM_AREA_HOUSES | SIM_AREA_BUILDINGS | SIM_AREA_MAP,
    [](city_t& c) { c.house_process_evolve(); }},
  {SIM_PHASE_TICK_SLOT, 40, "building_state", SIM_AREA_BUILDINGS, [](city_t&) { building_update_state(); }},
  {SIM_PHASE_TICK_SLOT, 43, "burning_ruins", SIM_AREA_BUILDINGS,
    [](city_t&) { building_burning_ruin::update_all_ruins(); }},
  {SIM_PHASE_TICK_SLOT, 44, "building_destroying", SIM_AREA_BUILDINGS,
    [](city_t& c) { c.maintenance.check_building_destroying(); }},
  {SIM_PHASE_TICK_SLOT, 44, "reset_protesters", SIM_AREA_SENTIMENT,
    [](city_t& c) { c.sentiment.reset_protesters_criminals(); }},
  {SIM_PHASE_TICK_SLOT, 45, "criminals", SIM_AREA_FIGURES | SIM_AREA_CRIME,
    [](city_t& c) { c.figures_generate_criminals(); }},
  {SIM_PHASE_TICK_SLOT, 46, "building_malaria_risk", SIM_AREA_BUILDINGS,
    [](city_t&) { building_update_malaria_risk(); }},
  {SIM_PHASE_TICK_SLOT, 48, "house_tax_coverage_decay", SIM_AREA_HOUSES,
    [](city_t& c) { c.house_decay_tax_coverage(); }},
  {SIM_PHASE_TICK_SLOT, 49, "avg_coverage", SIM_AREA_COVERAGE, [](city_t& c) { c.avg_coverage.update(); }},

  {SIM_PHASE_TICK_CITY_END, -1, "plague_countdowns", SIM_AREA_HEALTH,
    [](city_t& c) {
        if (c.plagues.locusts_countdown > 0) {
            c.plagues.locusts_countdown--;
        }
        if (c.plagues.frogs_countdown > 0) {
            c.plagues.frogs_countdown--;
        }
    }},

  {SIM_PHASE_TICK_END, -1, "figures", SIM_AREA_FIGURES, [](city_t& c) { c.figures.update(); }},
  {SIM_PHASE_TICK_END, -1, "scenario", SIM_AREA_SCENARIO, [](city_t&) { g_scenario.update(); }},

  {SIM_PHASE_DAY, -1, "distant_battle", SIM_AREA_MILITARY, [](city_t&) { g_distant_battle.update_day(); }},
  {SIM_PHASE_DAY, -1, "invasion_auto_resolve", SIM_AREA_MILITARY,
    [](city_t&) { g_invasion_auto_resolve.update_day(); }},
  {SIM_PHASE_DAY, -1, "sentiment", SIM_AREA_SENTIMENT, [](city_t& c) { c.sentiment.update_day(); }},
  {SIM_PHASE_DAY, -1, "criminals_day", SIM_AREA_CRIME | SIM_AREA_HOUSES, [](city_t& c) { c.criminals_update_day(); }},
  {SIM_PHASE_DAY, -1, "funeral_walkers", SIM_AREA_FIGURES,
    [](city_t&) { figure_funeral_walker::try_spawn_all(false); }},
  {SIM_PHASE_DAY, -1, "plague_day", SIM_AREA_HEALTH | SIM_AREA_HOUSES, [](city_t& c) { c.plague_update_day(); }},
  {SIM_PHASE_DAY, -1, "flotsam", SIM_AREA_FIGURES, [](city_t&) { figure_flotsam::spawn_update_day(); }},
  {SIM_PHASE_DAY, -1, "buildings_day", SIM_AREA_BUILDINGS, [](city_t& c) { c.buildings.update_day(); }},
  {SIM_PHASE_DAY, -1, "figures_day", SIM_AREA_FIGURES, [](city_t& c) { c.figures_update_day(); }},
  {SIM_PHASE_DAY, -1, "population_day", SIM_AREA_POPULATION, [](city_t& c) { c.population.update_day(); }},
  {SIM_PHASE_DAY, -1, "victory_check", SIM_AREA_VICTORY, [](city_t& c) { c.victory.victory_check(); }},
  {SIM_PHASE_DAY, -1, "avg_coverage", SIM_AREA_COVERAGE, [](city_t& c) { c.avg_coverage.update(); }},
  {SIM_PHASE_DAY, -1, "event_advance_day", SIM_AREA_EVENTS,
    [](city_t&) { events::emit(event_advance_day::from_simtime(g_simulation.simtime)); }},

  {SIM_PHASE_WEEK, -1, "food_weekly", SIM_AREA_RESOURCES | SIM_AREA_HOUSES,
    [](city_t& c) { c.resource.consume_food_weekly(g_simulation.simtime); }},
  {SIM_PHASE_WEEK, -1, "industry_nearby_houses", SIM_AREA_BUILDINGS,
    [](city_t& c) { c.industry.update_nearby_houses_weekly(); }},
  {SIM_PHASE_WEEK, -1, "event_advance_week", SIM_AREA_EVENTS,
    [](city_t&) { events::emit(event_advance_week::from_simtime(g_simulation.simtime)); }},

  {SIM_PHASE_MONTH_CITY, -1, "migration_month", SIM_AREA_MIGRATION, [](city_t& c) { c.migration.update_month(); }},
  {SIM_PHASE_MONTH_CITY, -1, "health_month", SIM_AREA_HEALTH, [](city_t& c) { c.health.update_month(); }},
  {SIM_PHASE_MONTH_CITY, -1, "finance_month", SIM_AREA_FINANCE,
    [](city_t& c) { finance_system::advance_month(c.finance, c.finance_ctx()); }},
  {SIM_PHASE_MONTH_CITY, -1, "food_monthly", SIM_AREA_RESOURCES | SIM_AREA_HOUSES,
    [](city_t& c) { c.resource.consume_food_monthly(); }},
  {SIM_PHASE_MONTH_CITY, -1, "resource_month", SIM_AREA_RESOURCES, [](city_t& c) { c.resource.advance_month(); }},
  {SIM_PHASE_MONTH_CITY, -1, "food_supply_month", SIM_AREA_RESOURCES, [](city_t& c) { c.food_supply.advance_month(); }},
  {SIM_PHASE_MONTH_CITY, -1, "allowed_foods", SIM_AREA_RESOURCES, [](city_t& c) { c.update_allowed_foods(); }},
  {SIM_PHASE_MONTH_CITY, -1, "population_record", SIM_AREA_POPULATION,
    [](city_t& c) { c.population.record_monthly(); }},
  {SIM_PHASE_MONTH_CITY, -1, "local_cults_month", SIM_AREA_RELIGION, [](city_t& c) { c.local_cults.advance_month(); }},
  {SIM_PHASE_MONTH_CITY, -1, "festival_month", SIM_AREA_FESTIVAL, [](city_t& c) { c.festival.advance_month(); }},
  {SIM_PHASE_MONTH_CITY, -1, "buildings_month", SIM_AREA_BUILDINGS, [](city_t& c) { c.buildings.update_month(); }},
  {SIM_PHASE_MONTH_CITY, -1, "fishing_points_month", SIM_AREA_FIGURES,
    [](city_t& c) {
        if (game_features::gameplay_change_fishing_points_monthly_respawn.to_bool()
            && c.can_produce_resource(RESOURCE_FISH) && !g_scenario.events.blood_river_sweep_active()) {
            c.fishing_points.update_month();
        }
    }},
  {SIM_PHASE_MONTH_CITY, -1, "kingdome_month", SIM_AREA_KINGDOM, [](city_t& c) { c.kingdome.advance_month(); }},
  {SIM_PHASE_MONTH_CITY, -1, "tomb_robbers_month", SIM_AREA_FIGURES,
    [](city_t&) {
        if (game_features::gameplay_change_tomb_robber_remake.to_bool()) {
            figure_tomb_robber::try_spawn(false);
            figure_tomb_robber::try_professional_wave();
        }
    }},

  {SIM_PHASE_MONTH, -1, "distant_battle_month", SIM_AREA_MILITARY, [](city_t&) { g_distant_battle.update_month(); }},
  {SIM_PHASE_MONTH, -1, "random_month", SIM_AREA_RANDOM, [](city_t&) { random_generate_next(); }},
  {SIM_PHASE_MONTH, -1, "empire_month", SIM_AREA_EMPIRE, [](city_t&) { g_empire.update_month(); }},
  {SIM_PHASE_MONTH, -1, "random_events", SIM_AREA_SCENARIO, [](city_t&) { g_scenario.events.process_random_events(); }},
  {SIM_PHASE_MONTH, -1, "invasions", SIM_AREA_SCENARIO | SIM_AREA_MILITARY,
    [](city_t&) { g_scenario.events.process_invasions(); }},
  {SIM_PHASE_MONTH, -1, "scenario_events", SIM_AREA_SCENARIO, [](city_t&) { g_scenario.events.process_events(); }},
  {SIM_PHASE_MONTH, -1, "invasion_bind_resolutions", SIM_AREA_MILITARY,
    [](city_t&) { g_invasions.process_bind_resolutions(); }},
  {SIM_PHASE_MONTH, -1, "invasion_process", SIM_AREA_SCENARIO | SIM_AREA_MILITARY,
    [](city_t&) { scenario_invasion_process(); }},
  {SIM_PHASE_MONTH, -1, "morale_at_rest", SIM_AREA_MILITARY,
    [](city_t&) { formation_update_monthly_morale_at_rest(); }},
  {SIM_PHASE_MONTH, -1, "message_delays", SIM_AREA_MESSAGES, [](city_t&) { city_message_decrease_delays(); }},
  {SIM_PHASE_MONTH, -1, "roads_images", SIM_AREA_MAP, [](city_t&) { map_tiles_update_all_roads(); }},
  {SIM_PHASE_MONTH, -1, "land_citizen_routing", SIM_AREA_MAP, [](city_t&) { map_routing_update_land_citizen(); }},
  {SIM_PHASE_MONTH, -1, "locusts_month", SIM_AREA_FIGURES,
    [](city_t&) { figure_locust::update_month(g_simulation.simtime.month + 1); }},

  {SIM_PHASE_MONTH_END, -1, "estimate_taxes", SIM_AREA_FINANCE,
    [](city_t& c) { finance_system::update_estimate_taxes(c.finance, c.finance_ctx()); }},
  {SIM_PHASE_MONTH_END, -1, "event_advance_month", SIM_AREA_EVENTS,
    [](city_t&) { events::emit(event_advance_month::from_simtime(g_simulation.simtime)); }},

  {SIM_PHASE_YEAR, -1, "empire_expansion", SIM_AREA_EMPIRE, [](city_t&) { scenario_empire_process_expansion(); }},
  {SIM_PHASE_YEAR, -1, "undo_disable", SIM_AREA_UNDO, [](city_t&) { game_undo_disable(); }},
  {SIM_PHASE_YEAR, -1, "simtime_year", SIM_AREA_TIME, [](city_t&) { g_simulation.simtime.advance_year(); }},
  {SIM_PHASE_YEAR, -1, "population_yearly_request", SIM_AREA_POPULATION,
    [](city_t&) { city_population_request_yearly_update(); }},
  {SIM_PHASE_YEAR, -1, "finance_year", SIM_AREA_FINANCE,
    [](city_t& c) { finance_system::advance_year(c.finance, c.finance_ctx()); }},
  {SIM_PHASE_YEAR, -1, "migration_year", SIM_AREA_MIGRATION, [](city_t& c) { c.migration.advance_year(); }},
  {SIM_PHASE_YEAR, -1, "monuments_year", SIM_AREA_MONUMENTS, [](city_t& c) { c.monuments.advance_year(); }},
  {SIM_PHASE_YEAR, -1, "yearly_trade_amounts", SIM_AREA_EMPIRE | SIM_AREA_TRADE,
    [](city_t&) { g_empire.reset_yearly_trade_amounts(); }},
  {SIM_PHASE_YEAR, -1, "ratings_year", SIM_AREA_RATINGS, [](city_t& c) { c.ratings_update(true); }},
  {SIM_PHASE_YEAR, -1, "ra_yearly_favour", SIM_AREA_RELIGION, [](city_t& c) { c.ra_temple_complex_yearly_favour(); }},
  {SIM_PHASE_YEAR, -1, "buildings_year", SIM_AREA_BUILDINGS, [](city_t& c) { c.buildings.update_year(); }},
};

span_const<sim_step> sim_schedule_steps() {
    return make_span(k_sim_steps);
}

void sim_schedule_run(e_sim_phase phase, city_t& city, int slot) {
    for (const sim_step& step : k_sim_steps) {
        if (step.phase == phase && (phase != SIM_PHASE_TICK_SLOT || step.slot == slot)) {
            step.run(city);
        }
    }
}

const char* sim_phase_name(e_sim_phase phase) {
    static const std::array<const char*, SIM_PHASE_COUNT> names = {"tick_begin", "tick_slot", "tick_city_end",
      "tick_end", "day", "week", "month_city", "month", "month_end", "year"};
    return phase < SIM_PHASE_COUNT ? names[phase] : "?";
}

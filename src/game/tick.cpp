#include "tick.h"

#include "io/manager.h"
#include "city/floods.h"
#include "grid/vegetation.h"
#include "scenario/events.h"
#include "building/count.h"
#include "building/building_dock.h"
#include "building/figure.h"
#include "building/government.h"
#include "building/building_granary.h"
#include "building/house_evolution.h"
#include "building/house_population.h"
#include "building/house_service.h"
#include "building/industry.h"
#include "building/maintenance.h"
#include "building/building_storage_yard.h"
#include "city/coverage.h"
#include "city/city.h"
#include "city/festival.h"
#include "city/buildings.h"
#include "city/finance.h"
#include "city/gods.h"
#include "city/health.h"
#include "city/labor.h"
#include "city/message.h"
#include "city/migration.h"
#include "city/population.h"
#include "city/ratings.h"
#include "city/resource.h"
#include "city/sentiment.h"
#include "city/trade.h"
#include "city/victory.h"
#include "core/random.h"
#include "core/profiler.h"
#include "core/bstring.h"
#include "editor/editor.h"
#include "empire/empire.h"
#include "figure/formation.h"
#include "figuretype/crime.h"
#include "figure/formation_herd.h"
#include "game/settings.h"
#include "game/time.h"
#include "game/tutorial.h"
#include "game/undo.h"
#include "game/game.h"
#include "grid/desirability.h"
#include "grid/natives.h"
#include "grid/religion_supply.h"
#include "grid/road_network.h"
#include "grid/routing/routing_terrain.h"
#include "grid/tiles.h"
#include "grid/building.h"
#include "grid/water_supply.h"
#include "io/gamestate/boilerplate.h"
#include "scenario/demand_change.h"
#include "scenario/distant_battle.h"
#include "scenario/earthquake.h"
#include "scenario/emperor_change.h"
#include "scenario/empire.h"
#include "scenario/gladiator_revolt.h"
#include "scenario/invasion.h"
#include "scenario/price_change.h"
#include "scenario/random_event.h"
#include "scenario/request.h"
#include "sound/music.h"
#include "widget/minimap.h"
#include "window/file_dialog.h"

static void advance_year(void) {
    scenario_empire_process_expansion();
    game_undo_disable();
    game_time_advance_year();
    city_population_request_yearly_update();
    city_finance_handle_year_change();
    g_city.migration_advance_year();
    g_empire.reset_yearly_trade_amounts();
    building_maintenance_update_fire_direction();
    g_city.ratings_update(/*yearly_update*/true);
    //    city_gods_reset_yearly_blessings();
}

static void advance_month() {
    g_city.migration_reset_newcomers();
    g_city.health.update();
    scenario_random_event_process();
    city_finance_handle_month_change();
    city_resource_consume_food();
    scenario_distant_battle_process();
    random_generate_next();                  // TODO: find out the source / reason for this
    scenario_event_process();
    
    g_city.victory_state.update_months_to_govern();
    formation_update_monthly_morale_at_rest();
    city_message_decrease_delays();

    map_tiles_update_all_roads();
    //    map_tiles_river_refresh_entire();
    map_routing_update_land_citizen();
    //    city_message_sort_and_compact();

    if (game_time_advance_month()) {
        advance_year();
    } else {
        g_city.ratings_update(/*yearly_update*/false);
    }

    city_population_record_monthly();
    city_festival_update();
    city_buildings_update_month();

    if (g_city.can_produce_resource(RESOURCE_FISH)) {
        g_city.fishing_points.update(0);
    }

    if (g_settings.monthly_autosave) {
        bstring256 autosave_file("autosave_month.", saved_game_data_expanded.extension);
        GamestateIO::write_savegame(autosave_file);
    }
}

static void advance_day() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Advance Day");
    //    map_advance_floodplain_growth();

    if (game_time_advance_day()) {
        advance_month();
    }

    city_sentiment_update_day();
    city_criminals_update_day();
    city_plague_update_day();
    g_city.environment.river_update_flotsam();
    city_buildings_update_day();
    g_city.figures_update_day();

    tutorial_on_day_tick();
}

static void update_building_tick(bool refresh_only) {
    for (auto it = building_begin(), end = building_end(); it != end; ++it) {
        if (it->is_valid()) {
            it->update_tick(refresh_only);
        }
    }
}

static void advance_tick(void) {
    tutorial_starting_message();
    floodplains_tick_update(false);

    update_building_tick(game.paused);

    switch (game_time_tick()) {
    case 1:
        city_gods_update(false);
        break;
    case 2:
        sound_music_update(false);
        break;
    case 3:
        widget_minimap_invalidate();
        break;
    case 4:
        g_city.kingdome.update();
        break;
    case 5:
        formation_update_all(false);
        break;
    case 6:
        map_natives_check_land();
        break;
    case 7:
        map_road_network_update();
        break;
    case 8:
        city_granaries_calculate_stocks();
        break;
    case 9:
        // nothing yet
    case 10:
        building_update_highest_id();
        break;
    case 12:
        house_service_decay_houses_covered();
        break;
    case 16:
        city_resource_calculate_storageyard_stocks();
        break;
    case 17:
        city_resource_calculate_food_stocks_and_supply_wheat();
        break;
    case 18:
        map_vegetation_growth_update();
        break;
    case 19:
        building_river_update_open_water_access();
        break;
    case 20:
        building_industry_update_production();
        break;
    case 21:
        building_maintenance_check_kingdome_access();
        break;
    case 22:
        house_population_update_room();
        break;
    case 23:
        house_population_update_migration();
        break;
    case 24:
        house_population_evict_overcrowded();
        break;
    case 25:
        g_city.labor.update();
        break;
    case 27:
        map_update_wells_range();
        map_update_canals();
        break;
    case 28:
        map_water_supply_update_houses();
        map_religion_supply_update_houses();
        break;
    case 29:
        formation_update_all(true);
        break;
    case 30:
        widget_minimap_invalidate();
        break;
    case 31:
        building_figure_generate();
        break;
    case 32:
        city_trade_update();
        break;
    case 33:
        building_count_update();
        city_culture_update_coverage();
        city_health_update_coverage();
        building_industry_update_farms();
        break;
    case 34:
        building_government_distribute_treasury();
        break;
    case 35:
        house_service_decay_services();
        house_service_update_health();
        break;
    case 36:
        house_service_calculate_culture_aggregates();
        break;
    case 37:
        g_desirability.update();
        break;
    case 38:
        building_update_desirability();
        break;
    case 39:
        building_house_process_evolve_and_consume_goods();
        break;
    case 40:
        building_update_state();
        break;
    case 43:
        building_maintenance_update_burning_ruins();
        break;
    case 44:
        building_maintenance_check_fire_collapse();
        break;
    case 45:
        figure_generate_criminals();
        break;
    case 46:
        building_industry_update_wheat_production();
        break;
    case 48:
        house_service_decay_tax_collector();
        break;
    case 49:
        city_culture_calculate();
        break;
    case 50:
        break;
    }

    if (game_time_advance_tick()) {
        advance_day();
    }
}

void game_tick_run(void) {
    OZZY_PROFILER_SECTION("Game/Run/Tick");
    if (editor_is_active()) {
        random_generate_next(); // update random to randomize native huts
        figure_action_handle(); // just update the flag figures
        return;
    }
    random_generate_next();
    game_undo_reduce_time_available();
    advance_tick();
    figure_action_handle();
    scenario_earthquake_process();
    //scenario_gladiator_revolt_process();
    scenario_kingdome_change_process();
    g_city.victory_check();
}

void game_tick_cheat_year(void) {
    advance_year();
}

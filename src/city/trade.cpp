#include "trade.h"

#include "building/building_storage_yard.h"
#include "city/constants.h"
#include "city/city.h"
#include "core/profiler.h"
#include "empire/empire.h"
#include "game/game_config.h"

static auto &city_data = g_city;
void city_trade_update() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Trade Update");

    city_data.trade.num_sea_routes = 0;
    city_data.trade.num_land_routes = 0;
    // Wine types
    city_data.resource.wine_types_available = g_city.buildings.count_industry_total(RESOURCE_BEER) > 0 ? 1 : 0;
    if (city_data.resource.trade_status[RESOURCE_BEER] == TRADE_STATUS_IMPORT
        || g_ankh_config.get(CONFIG_GP_CH_WINE_COUNTS_IF_OPEN_TRADE_ROUTE)) {
        city_data.resource.wine_types_available += g_empire.count_wine_sources();
    }

    // Update trade problems
    if (city_data.trade.land_trade_problem_duration > 0) {
        city_data.trade.land_trade_problem_duration--;
    } else {
        city_data.trade.land_trade_problem_duration = 0;
    }

    if (city_data.trade.sea_trade_problem_duration > 0) {
        city_data.trade.sea_trade_problem_duration--;
    } else {
        city_data.trade.sea_trade_problem_duration = 0;
    }

    g_empire.generate_traders();
}

bool city_resource_trade_surplus_papyrus() {
    int papyrus_amount_in_city = city_resource_ready_for_using(RESOURCE_PAPYRUS);
    const uint32_t scribal_school_count = g_city.buildings.count_active(BUILDING_SCRIBAL_SCHOOL);
    const uint32_t library_count = g_city.buildings.count_active(BUILDING_LIBRARY);

    int papyrus_need_for_works = library_count * 100 + scribal_school_count * 100;

    return (papyrus_amount_in_city > (papyrus_need_for_works + 100));
}

bool city_resource_trade_surplus(e_resource resource) {
    switch (resource) {
    case RESOURCE_PAPYRUS:
        return city_resource_trade_surplus_papyrus();

    default:
        break;
    }

    return false;
}

void city_trade_add_land_trade_route() {
    city_data.trade.num_land_routes++;
}

void city_trade_add_sea_trade_route() {
    city_data.trade.num_sea_routes++;
}

int city_trade_has_land_trade_route() {
    return city_data.trade.num_land_routes > 0;
}

int city_trade_has_sea_trade_route() {
    return city_data.trade.num_sea_routes > 0;
}

void city_trade_start_land_trade_problems(int duration) {
    city_data.trade.land_trade_problem_duration = duration;
}

void city_trade_start_sea_trade_problems(int duration) {
    city_data.trade.sea_trade_problem_duration = duration;
}

int city_trade_has_land_trade_problems() {
    return city_data.trade.land_trade_problem_duration > 0;
}

int city_trade_has_sea_trade_problems() {
    return city_data.trade.sea_trade_problem_duration > 0;
}

e_resource city_trade_current_caravan_import_resource() {
    return city_data.trade.caravan_import_resource;
}

e_resource city_trade_next_caravan_import_resource() {
    city_data.trade.caravan_import_resource = (e_resource)(city_data.trade.caravan_import_resource + 1);
    if (city_data.trade.caravan_import_resource >= RESOURCES_MAX)
        city_data.trade.caravan_import_resource = RESOURCE_MIN;

    return city_data.trade.caravan_import_resource;
}

e_resource city_trade_next_caravan_backup_import_resource() {
    city_data.trade.caravan_backup_import_resource = (e_resource)(city_data.trade.caravan_backup_import_resource + 1);
    if (city_data.trade.caravan_backup_import_resource >= RESOURCES_MAX)
        city_data.trade.caravan_backup_import_resource = RESOURCE_MIN;

    return city_data.trade.caravan_backup_import_resource;
}

e_resource city_trade_next_docker_import_resource() {
    city_data.trade.docker_import_resource = ++city_data.trade.docker_import_resource;
    if (city_data.trade.docker_import_resource >= RESOURCES_MAX)
        city_data.trade.docker_import_resource = RESOURCE_MIN;

    return city_data.trade.docker_import_resource;
}

e_resource city_trade_next_docker_export_resource() {
    city_data.trade.docker_export_resource = (e_resource)(city_data.trade.docker_export_resource + 1);
    if (city_data.trade.docker_export_resource >= RESOURCES_MAX)
        city_data.trade.docker_export_resource = RESOURCE_MIN;

    return city_data.trade.docker_export_resource;
}

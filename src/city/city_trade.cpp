#include "city_trade.h"

#include "building/building_storage_yard.h"
#include "city/constants.h"
#include "building/monuments.h"
#include "city/buildings.h"
#include "city/city.h"
#include "core/profiler.h"
#include "empire/empire.h"
#include "game/game_config.h"
#include "scenario/request.h"
#include "scenario/scenario.h"

#include <algorithm>
#include <array>

void city_t::trade_update() {
    OZZY_PROFILER_FUNCTION();

    trade.num_sea_routes = 0;
    trade.num_land_routes = 0;
    // Wine types
    resource.beer_types_available = buildings.count_industry_total(RESOURCE_BEER) > 0 ? 1 : 0;
    if (resource.trade_status[RESOURCE_BEER] == TRADE_STATUS_IMPORT || !!game_features::gameplay_change_beer_open_trade_route_counts) {
        resource.beer_types_available += g_empire.count_beer_sources();
    }

    // Update trade problems
    if (trade.land_trade_problem_duration > 0) {
        trade.land_trade_problem_duration--;
    } else {
        trade.land_trade_problem_duration = 0;
    }

    if (trade.sea_trade_problem_duration > 0) {
        trade.sea_trade_problem_duration--;
    } else {
        trade.sea_trade_problem_duration = 0;
    }

    g_empire.generate_traders();
}

static auto &city_data = g_city;

static int trade_recommended_keep(int good_index) {
    const int population = g_city.population.current;
    for (const auto& row : empire_trade_rules.recommends) {
        if (row.population_below > 0 && population >= row.population_below) {
            continue;
        }
        const int amounts[] = {row.food, row.pottery, row.beer, row.linen, row.papyrus, row.luxury_goods};
        return amounts[good_index];
    }
    return 0;
}

// OG empire_food_resources: any food shares the first column, then the advisor's goods.
static int trade_recommended_good_index(e_resource resource) {
    if (resource >= RESOURCES_FOOD_MIN && resource < RESOURCES_FOODS_MAX) {
        return 0;
    }
    switch (resource) {
    case RESOURCE_POTTERY:
        return 1;
    case RESOURCE_BEER:
        return 2;
    case RESOURCE_LINEN:
        return 3;
    case RESOURCE_PAPYRUS:
        return 4;
    case RESOURCE_LUXURY_GOODS:
        return 5;
    default:
        return -1;
    }
}

static int trade_workshops_using(e_resource resource) {
    int count = 0;
    buildings_valid_do([&](building& b) {
        if (b.num_workers > 0 && (b.input.resource == resource || b.input.resource_second == resource)) {
            ++count;
        }
    });
    return count;
}

static int trade_monument_need(e_resource resource) {
    int total = 0;
    std::array<int, BUILDING_MAX> placed = {};
    buildings_valid_do([&](building& b) {
        auto* monument = b.dcast_monument();
        if (!monument || !b.is_main()) {
            return;
        }
        ++placed[b.type];
        total += monument->remaining_resource_need(resource);
    });

    for (
      const int monument_id : {g_scenario.monuments.first, g_scenario.monuments.second, g_scenario.monuments.third}) {
        const auto& needs = empire_trade_rules.monument_unplaced_needs;
        auto need = std::find_if(needs.begin(), needs.end(), [&](auto& n) { return n.monument == monument_id; });
        if (monument_id <= 0 || need == needs.end()) {
            continue;
        }
        if (placed[need->building] > 0) {
            --placed[need->building];
            continue;
        }
        if (need->resource != RESOURCE_NONE && need->resource == resource) {
            total += need->amount;
        } else if (resource == RESOURCE_LIMESTONE) {
            total += need->limestone;
        }
    }
    return total;
}

static int trade_material_keep(e_resource resource) {
    const auto& rules = empire_trade_rules;
    switch (resource) {
    case RESOURCE_REEDS:
    case RESOURCE_CLAY:
    case RESOURCE_GEMS:
    case RESOURCE_BARLEY:
    case RESOURCE_FLAX:
    case RESOURCE_STRAW:
    case RESOURCE_COPPER:
    case RESOURCE_TIMBER:
    case RESOURCE_HENNA:
        return (trade_workshops_using(resource) + 1) * rules.keep_workshop_amount;

    case RESOURCE_STONE:
    case RESOURCE_LIMESTONE:
    case RESOURCE_BRICKS:
    case RESOURCE_GRANITE:
    case RESOURCE_SANDSTONE:
        return trade_monument_need(resource) + rules.keep_monument_amount;

    default:
        return rules.keep_other_amount;
    }
}

static int trade_cap_amount(e_resource resource, int amount) {
    if (amount < 0) {
        return 0;
    }
    const auto& rules = empire_trade_rules;
    int cap;
    switch (resource) {
    case RESOURCE_WEAPONS:
    case RESOURCE_CHARIOTS:
        cap = rules.stock_cap_small;
        break;
    case RESOURCE_BRICKS:
    case RESOURCE_STONE:
    case RESOURCE_LIMESTONE:
    case RESOURCE_GRANITE:
    case RESOURCE_SANDSTONE:
        cap = rules.stock_cap_large;
        break;
    default:
        cap = rules.stock_cap_default;
        break;
    }
    return std::min(amount, cap);
}

void city_trade_update_export_keep() {
    int requested[RESOURCES_MAX] = {};
    for (const auto& request : scenario_get_visible_requests()) {
        if (request.resource >= RESOURCES_MIN && request.resource < RESOURCES_MAX) {
            requested[request.resource] += request.resource_amount();
        }
    }

    auto& keep = city_data.trade.export_keep;
    keep[RESOURCE_NONE] = 0;
    for (e_resource r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
        const auto& provisions = g_scenario.monuments.burial_provisions[r];
        const int amount = requested[r] + (provisions.required - provisions.dispatched) * 100;
        const int good_index = trade_recommended_good_index(r);
        const int base = good_index >= 0 ? trade_recommended_keep(good_index) : trade_material_keep(r);
        keep[r] = trade_cap_amount(r, base + amount);
    }
}

int city_trade_export_keep(e_resource resource) {
    if (resource < RESOURCES_MIN || resource >= RESOURCES_MAX) {
        return 0;
    }
    return city_data.trade.export_keep[resource];
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
        city_data.trade.caravan_import_resource = RESOURCES_MIN;

    return city_data.trade.caravan_import_resource;
}

e_resource city_trade_next_caravan_backup_import_resource() {
    city_data.trade.caravan_backup_import_resource = (e_resource)(city_data.trade.caravan_backup_import_resource + 1);
    if (city_data.trade.caravan_backup_import_resource >= RESOURCES_MAX)
        city_data.trade.caravan_backup_import_resource = RESOURCES_MIN;

    return city_data.trade.caravan_backup_import_resource;
}

e_resource city_trade_next_docker_import_resource() {
    city_data.trade.docker_import_resource = ++city_data.trade.docker_import_resource;
    if (city_data.trade.docker_import_resource >= RESOURCES_MAX)
        city_data.trade.docker_import_resource = RESOURCES_MIN;

    return city_data.trade.docker_import_resource;
}

e_resource city_trade_next_docker_export_resource() {
    city_data.trade.docker_export_resource = (e_resource)(city_data.trade.docker_export_resource + 1);
    if (city_data.trade.docker_export_resource >= RESOURCES_MAX)
        city_data.trade.docker_export_resource = RESOURCES_MIN;

    return city_data.trade.docker_export_resource;
}

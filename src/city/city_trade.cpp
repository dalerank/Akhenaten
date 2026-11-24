#include "city_trade.h"
#include "game/simulation.h"
#include "core/app_module.h"
#include "game/sim_schedule.h"

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

void trade_system::update() {
    OZZY_PROFILER_FUNCTION();

    _state.num_sea_routes = 0;
    _state.num_land_routes = 0;
    _ctx.resource.luxury_goods_kinds = _ctx.empire.count_luxury_goods_kinds();

    // Update trade problems
    if (_state.land_trade_problem_duration > 0) {
        _state.land_trade_problem_duration--;
    } else {
        _state.land_trade_problem_duration = 0;
    }

    if (_state.sea_trade_problem_duration > 0) {
        _state.sea_trade_problem_duration--;
    } else {
        _state.sea_trade_problem_duration = 0;
    }

    _ctx.empire.generate_traders();
}

int trade_system::recommended_keep(int good_index) const {
    const int population = _ctx.population.current;
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

int trade_system::monument_need(e_resource resource) const {
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

    for (const int monument_id :
      {_ctx.scenario.monuments.first, _ctx.scenario.monuments.second, _ctx.scenario.monuments.third}) {
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

int trade_system::material_keep(e_resource resource) const {
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
        return monument_need(resource) + rules.keep_monument_amount;

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

void trade_system::update_export_keep() {
    int requested[RESOURCES_MAX] = {};
    for (const auto& request : scenario_get_visible_requests()) {
        if (request.resource >= RESOURCES_MIN && request.resource < RESOURCES_MAX) {
            requested[request.resource] += request.resource_amount();
        }
    }

    auto& keep = _state.export_keep;
    keep[RESOURCE_NONE] = 0;
    for (e_resource r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
        const auto& provisions = _ctx.scenario.monuments.burial_provisions[r];
        const int amount = requested[r] + (provisions.required - provisions.dispatched) * 100;
        const int good_index = trade_recommended_good_index(r);
        const int base = good_index >= 0 ? recommended_keep(good_index) : material_keep(r);
        keep[r] = trade_cap_amount(r, base + amount);
    }
}

int trade_state::keep_for_export(e_resource resource) const {
    if (resource < RESOURCES_MIN || resource >= RESOURCES_MAX) {
        return 0;
    }
    return export_keep[resource];
}

void trade_system::add_land_route() {
    _state.num_land_routes++;
}

void trade_system::add_sea_route() {
    _state.num_sea_routes++;
}

void trade_system::start_land_problems(int duration) {
    _state.land_trade_problem_duration = duration;
}

void trade_system::start_sea_problems(int duration) {
    _state.sea_trade_problem_duration = duration;
}

e_resource trade_system::next_caravan_import() {
    _state.caravan_import_resource = (e_resource)(_state.caravan_import_resource + 1);
    if (_state.caravan_import_resource >= RESOURCES_MAX)
        _state.caravan_import_resource = RESOURCES_MIN;

    return _state.caravan_import_resource;
}

e_resource trade_system::next_caravan_backup_import() {
    _state.caravan_backup_import_resource = (e_resource)(_state.caravan_backup_import_resource + 1);
    if (_state.caravan_backup_import_resource >= RESOURCES_MAX)
        _state.caravan_backup_import_resource = RESOURCES_MIN;

    return _state.caravan_backup_import_resource;
}

e_resource trade_system::next_docker_import() {
    _state.docker_import_resource = ++_state.docker_import_resource;
    if (_state.docker_import_resource >= RESOURCES_MAX)
        _state.docker_import_resource = RESOURCES_MIN;

    return _state.docker_import_resource;
}

e_resource trade_system::next_docker_export() {
    _state.docker_export_resource = (e_resource)(_state.docker_export_resource + 1);
    if (_state.docker_export_resource >= RESOURCES_MAX)
        _state.docker_export_resource = RESOURCES_MIN;

    return _state.docker_export_resource;
}

class trade_sim_system : public sim_system {
public:
    const char* name() const override { return "trade"; }
    void register_steps() override {
        sim_schedule_add({sim_step_trade_export_keep, SIM_PHASE_TICK_SLOT, 11, SIM_AREA_TRADE,
          [] { g_city.trade_sys().update_export_keep(); }});
        sim_schedule_add({sim_step_trade, SIM_PHASE_TICK_SLOT, 32, SIM_AREA_TRADE | SIM_AREA_FIGURES,
          [] { g_city.trade_sys().update(); }});
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_trade_system) {
    static trade_sim_system system;
    g_simulation.register_system(&system);
}

#include "city_resource.h"
#include "core/app_module.h"
#include "game/simulation.h"
#include "game/sim_schedule.h"
#include "city/city_resource_chunks.h"
#include "core/xvalue.h"
#include "io/chunk_serializer.h"

#include "building/building.h"
#include "city/city_industry.h"
#include "building/building_storage_yard.h"
#include "building/building_storage_room.h"
#include "building/building_granary.h"
#include "building/building_food_mill.h"
#include "building/building_bazaar.h"
#include "building/building_house.h"
#include "city/city.h"
#include "city/city_population.h"
#include "city/city_food_supply.h"
#include "city/city_warnings.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "empire/empire.h"
#include "grid/road_access.h"
#include "scenario/scenario.h"
#include "game/game_config.h"
#include "game/game_events.h"

struct available_data_t {
    resource_list resources;
    resource_list foods;
    resource_list market_goods;
};

available_data_t g_available_data;
resource_list g_city_gettable_storages;

int city_resources_t::yards_stored(e_resource resource) {
    return stored_in_storages[resource];
}

int city_resources_t::yards_stored_staffed(e_resource resource) {
    int total = 0;
    buildings_valid_do([&](building &b) {
        building_storage_yard *yard = b.dcast_storage_yard();
        if (!yard || !yard->is_valid() || !yard->is_staffed()) {
            return;
        }
        total += yard->amount(resource);
    });
    return total;
}

int city_resources_t::granary_stored(e_resource resource) {
    if (!resource_is_food(resource)) {
        return 0;
    }
    return granary_food_stored[resource];
}

int city_resources_t::stored(e_resource resource) {
    return yards_stored(resource) + granary_stored(resource);
}

int city_resources_t::gettable(e_resource resource) {
    return g_city_gettable_storages[resource];
}

const resource_list &city_resources_t::available() {
    return g_available_data.resources;
}

const resource_list &city_resources_t::available_foods() {
    return g_available_data.foods;
}

const resource_list &city_resources_t::available_market_goods() {
    return g_available_data.market_goods;
}

int city_resource_food_supply_months() {
    return city_resource().food_supply_months;
}

int city_resource_operating_granaries() {
    return city_resource().granaries.operating;
}

void city_granaries_remove_resource(event_granaries_remove_resource &ev) {
    if (ev.amount <= 0) {
        return;
    }

    // first go for non-getting warehouses
    buildings_valid_do<building_granary>([&] (building_granary *granary) {
        assert(granary);
        if (granary->is_valid() && !granary->is_getting(ev.resource)) {
            ev.amount = granary->remove_resource(ev.resource, ev.amount);
        }
    });

    // if that doesn't work, take it anyway
    buildings_valid_do< building_granary>([&] (building_granary *granary) {
        assert(granary);
        if (granary->is_valid()) {
            ev.amount = granary->remove_resource(ev.resource, ev.amount);
        }
    });
}

void city_storageyards_add_resource(event_storageyards_add_resource ev) {
    if (ev.amount <= 0) {
        return;
    }

    buildings_valid_do<building_storage_yard>([&] (auto warehouse) {
        assert(warehouse && warehouse->is_valid());
        while (ev.amount && warehouse->add_resource(ev.resource, UNITS_PER_LOAD, /*force*/false)) {
            ev.amount -= UNITS_PER_LOAD;
        }
    });
}

void city_storageyards_remove_resource(event_storageyards_remove_resource &ev) {
    if (ev.amount <= 0) {
        return;
    }

    auto yard_ok = [&](building_storage_yard *warehouse) {
        return warehouse && warehouse->is_valid() && (!ev.staffed_only || warehouse->is_staffed());
    };

    // first go for non-getting warehouses
    buildings_valid_do([&](building &b) {
        building_storage_yard *warehouse = b.dcast_storage_yard();
        if (yard_ok(warehouse) && !warehouse->is_getting(ev.resource)) {
            ev.amount = warehouse->remove_resource(ev.resource, ev.amount);
        }
    });
    // if that doesn't work, take it anyway (still respecting staffed_only)
    buildings_valid_do([&](building &b) {
        building_storage_yard *warehouse = b.dcast_storage_yard();
        if (yard_ok(warehouse)) {
            ev.amount = warehouse->remove_resource(ev.resource, ev.amount);
        }
    });
}

void city_remove_resource(event_city_remove_resource ev) {
    event_storageyards_remove_resource wh_ev{ev.resource, ev.amount, ev.staffed_only};
    city_storageyards_remove_resource(wh_ev);

    if (!ev.staffed_only) {
        event_granaries_remove_resource gr_ev{wh_ev.resource, wh_ev.amount};
        city_granaries_remove_resource(gr_ev);
    }
}

void city_resources_t::calculate_stocks() {
    OZZY_PROFILER_FUNCTION();

    g_city_gettable_storages.clear();

    buildings_valid_do([] (building &b) {
        auto &storages = g_city_gettable_storages;
        if (!b.has_road_access || b.distance_from_entry <= 0) {
            return;
        }

        // ACCEPT stocks are get-from sources; GET-state buildings are sinks (see better_getting_source).
        building_storage_yard *warehouse = b.dcast_storage_yard();
        if (warehouse) {
            for (const auto &r : resource_list::foods) {
                storages[r.type] += !warehouse->is_gettable(r.type) ? warehouse->amount(r.type) : 0;
            }
        }

        building_granary *granary = b.dcast_granary();
        if (granary) {
            for (const auto &r : resource_list::foods) {
                storages[r.type] += !granary->is_gettable(r.type) ? granary->amount(r.type) : 0;
            }
        }
    }, { BUILDING_GRANARY, BUILDING_STORAGE_YARD });
}

int city_resources_t::is_stockpiled(e_resource resource) {
    return stockpiled[resource];
}

int city_resource_ready_for_using(e_resource resource) {
    if (city_resource().is_stockpiled(resource)) {
        return 0;
    }

    int amount = 0;
    buildings_valid_do<building_storage_yard>([&] (auto warehouse) {
        amount += warehouse->amount(resource);
    });

    return amount;
}

void city_resources_t::toggle_stockpiled(e_resource resource) {
    if (stockpiled[resource])
        stockpiled[resource] = 0;
    else {
        stockpiled[resource] = 1;
        if (trade_status[resource] == TRADE_STATUS_EXPORT || trade_status[resource] == TRADE_STATUS_EXPORT_SURPLUS) {
            trade_status[resource] = TRADE_STATUS_NONE;
        }
    }
}

bool city_resources_t::is_mothballed(e_resource resource) {
    return mothballed[resource];
}

void city_resources_t::toggle_mothballed(e_resource resource) {
    mothballed[resource] = mothballed[resource] ? 0 : 1;
}

void city_resource_remove_from_granary(int food, int amount) {
    city_resource().granary_food_stored[food] -= amount;
}

city_resources_t& city_resource() {
    return xvalue<city_resources_t>::ref();
}

void city_resources_t::reset() {
    *this = {};
}

bool city_resources_t::is_food_allowed(e_resource resource) const {
    bool result = false;
    for (int i = 0; i < 4; i++) {
        if (allowed_foods(i) == resource) {
            result = true;
        }
    }
    // for etc etc todo: other resources?
    return result;
}

void city_resources_t::update_allowed_foods() {
    int food_index = 0;

    std::fill_n(std::begin(food_types_allowed), RESOURCES_FOODS_MAX, RESOURCE_NONE);

    for (e_resource resource = RESOURCES_MIN; resource < RESOURCES_FOODS_MAX; ++resource) {
        bool can_import_food = g_empire.can_import_resource(resource, false);
        bool can_produce_food = g_empire.can_produce_resource(resource);
        if (can_import_food || can_produce_food) {
            set_allowed_food(food_index, resource);
            food_index++;
        }
    }
}

void city_resources_t::subscribe_events() {
    events::subscribe([](event_stats_remove_resource ev) {
        auto& res = city_resource();
        res.space_in_storages[ev.resource] += ev.amount;
        res.stored_in_storages[ev.resource] -= ev.amount;
    });

    events::subscribe([](event_stats_append_resource ev) {
        auto& res = city_resource();
        res.space_in_storages[ev.resource] -= ev.amount;
        res.stored_in_storages[ev.resource] += ev.amount;
    });

    events::subscribe([](event_produced_resources ev) {
        auto& res = city_resource();
        res.res_this_month.produced[ev.resource] += ev.amount;
    });

    events::subscribe(&city_granaries_remove_resource);
    events::subscribe(&city_storageyards_add_resource);
    events::subscribe(&city_storageyards_remove_resource);
    events::subscribe(&city_remove_resource);

    events::subscribe([](event_toggle_industry_mothballed ev) {
        auto& res = city_resource();
        res.mothballed[ev.resource] = !res.mothballed[ev.resource];
    });
}

void city_resource_calculate_storageyard_stocks() {
    OZZY_PROFILER_FUNCTION();
    for (int i = 0; i < RESOURCES_MAX; i++) {
        city_resource().space_in_storages[i] = 0;
        city_resource().stored_in_storages[i] = 0;
    }

    for (int i = 1; i < MAX_BUILDINGS; i++) {
        auto warehouse = building_get(i)->dcast_storage_yard();
        if (!warehouse || !warehouse->is_valid()) {
            continue;
        }
        
        tile2i road_access_tile = map_has_road_access_rotation(warehouse->base.orientation, warehouse->base.tile, warehouse->base.size);
        warehouse->base.has_road_access = road_access_tile.valid();
    }

    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building_storage_room* room = building_get(i)->dcast_storage_room();
        if (!room ||!room->is_valid()) {
            continue;
        }

        auto warehouse = room->yard();
        if (!warehouse || !warehouse->has_road_access()) {
            return;
        }

        room->base.has_road_access = warehouse->has_road_access();
        if (room->resource()) {
            const auto r = room->base.stored_first();
            city_resource().stored_in_storages[r.type] += r.value;
            city_resource().space_in_storages[r.type] += 400 - r.value;
        } else {
            city_resource().space_in_storages[RESOURCE_NONE] += 4;
        }
    }

    for (int i = 1; i < MAX_BUILDINGS; i++) {
        auto warehouse = building_get(i)->dcast_storage_yard();
        if (!warehouse || !warehouse->is_valid()) {
            continue;
        }

        int total_stored = warehouse->total_stored();
        if (total_stored > 100) {
            events::emit(event_warehouse_filled{ warehouse->id() });
        }
    }
}

void city_resource_determine_available() {
    g_available_data.resources.clear();
    g_available_data.foods.clear();
    g_available_data.market_goods.clear();

    for (const auto &r: resource_list::foods) {
        if (g_empire.can_produce_resource(r.type) || g_empire.can_import_resource(r.type, false)) {
            g_available_data.foods[r.type] = 1;
            g_available_data.market_goods[r.type] = 1;
        }
    }

    for (const auto &r : resource_list::all) {
        if (g_empire.can_produce_resource(r.type) || g_empire.can_import_resource(r.type, false)) {
            g_available_data.resources[r.type] = 1;
            switch (r.type) {
            case RESOURCE_POTTERY:
            case RESOURCE_BEER:
            case RESOURCE_LINEN:
            case RESOURCE_LUXURY_GOODS:
                g_available_data.market_goods[r.type] = 1;
                break;
            }
        }

        const e_resource raw = get_raw_resource(r.type);
        if (raw != r.type) {
            if (g_empire.can_produce_resource(raw) || g_empire.can_import_resource(raw, false)) {
                g_available_data.resources[r.type] = 1;
            }
        }
    }
}

void city_resources_t::calculate_available_food() {
    for (int i = 0; i < RESOURCES_FOODS_MAX; i++) {
        granary_food_stored[i] = 0;
        food_types_available[i] = 0;
    }

    granary_total_stored = 0;
    food_supply_months = 0;
    granaries.operating = 0;
    granaries.understaffed = 0;
    granaries.not_operating = 0;
    granaries.not_operating_with_food = 0;

    buildings_valid_do([this] (building &b) {
        b.has_road_access = false;
        if (!map_has_road_access(b.tile, b.size)) { // map_has_road_access_granary(b->tile.x(), b->tile.y(), 0)
            return;
        }

        b.has_road_access = true;
        int pct_workers = b.worker_percentage();
        if (pct_workers < 100) {
            granaries.understaffed++;
        }

        int amount_stored = 0;
        const auto &granary = b.dcast_granary()->runtime_data();
        for (int r = RESOURCES_FOOD_MIN; r < RESOURCES_FOODS_MAX; r++) {
            amount_stored += granary.resource_stored[r];
        }

        if (pct_workers < 50) {
            granaries.not_operating++;
            if (amount_stored > 0)
                granaries.not_operating_with_food++;

        } else {
            granaries.operating++;
            for (int r = 0; r < RESOURCES_FOODS_MAX; r++) {
                granary_food_stored[r] += granary.resource_stored[r];
            }
        }
    }, BUILDING_GRANARY);

    // Enhanced Food Mill: stock counts toward city food months / types available.
    buildings_valid_do([this](building &b) {
        auto *mill = b.dcast_food_mill();
        if (!mill || !map_has_road_access(b.tile, b.size)) {
            return;
        }
        if (calc_percentage<int>(b.num_workers, b.max_workers) < 50) {
            return;
        }
        for (e_resource r = RESOURCES_FOOD_MIN; r < RESOURCES_FOODS_MAX; ++r) {
            if (resource_is_food(r)) {
                granary_food_stored[r] += mill->amount(r);
            }
        }
    }, BUILDING_FOOD_MILL);

    for (int i = RESOURCES_FOOD_MIN; i < RESOURCES_FOODS_MAX; i++) {
        granary_total_stored += granary_food_stored[i];
        food_types_available[i] = granary_food_stored[i] > 0 ? 1 : 0;
    }

    food_needed_per_month = calc_adjust_with_percentage(city_population().current, city_food_consumption_percentage());
    if (food_needed_per_month > 0) {
        food_supply_months = granary_total_stored / food_needed_per_month;
    } else {
        food_supply_months = granary_total_stored > 0 ? 1 : 0;
    }

    if (g_scenario.kingdom_supplies_grain) {
        food_supply_months = 12;
        for (int i = 0; i < RESOURCES_FOODS_MAX; i++) {
            food_types_available[i] = 0;
        }
        food_types_available[RESOURCE_GRAIN] = 1;
    }
}

void city_resources_t::calculate_food_stocks_and_supply_wheat() {
    OZZY_PROFILER_FUNCTION();
    calculate_available_food();
    if (!g_scenario.kingdom_supplies_grain) {
        return;
    }

    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building_bazaar* bazaar = building_get(i)->dcast_bazaar();
        if (bazaar && bazaar->state() == BUILDING_STATE_VALID) {
            bazaar->runtime_data().inventory[0].value = 200;
        }
    }
}

// Remake model (scripts/building/house.js): the model's percentage, twice a month.
void city_resources_t::consume_food_weekly(const simulation_time_t& t) {
    if (!game_features::gameplay_change_food_consumption_remake.to_bool()) {
        return;
    }

    calculate_available_food();

    for (int i = 0; i < RESOURCES_FOODS_MAX; i++) {
        food_types_eaten[i] = 0;
    }
    food_types_eaten_max_value = 0;

    buildings_house_do([&] (building_house *house) {
        house->consume_food_weekly();

        const uint8_t num_foods = house->runtime_data().num_foods;
        if (num_foods > food_types_eaten_max_value) {
            food_types_eaten_max_value = num_foods;
        }
    });
}

// OG city/resources.c city_resource_consume_food: once a month every house eats the percentage of its people,
// split over the food kinds its level needs, from the first city foods it has in stock. A kind it has less of
// than its share is emptied and still counts as eaten (and as the full share consumed).
void city_resources_t::consume_food_monthly() {
    OZZY_PROFILER_FUNCTION();
    if (game_features::gameplay_change_food_consumption_remake.to_bool()) {
        return;
    }

    calculate_available_food();

    for (int i = 0; i < RESOURCES_FOODS_MAX; i++) {
        food_types_eaten[i] = 0;
    }
    food_types_eaten_max_value = 1;

    const int percentage = city_food_consumption_percentage();
    buildings_house_do([&](building_house* house) {
        auto& d = house->runtime_data();
        if (!d.hsize) {
            return;
        }

        const int types = house->model().food_types;
        int amount = calc_adjust_with_percentage<int>(house->house_population(), percentage);
        if (types > 1) {
            amount /= types;
        }

        d.num_foods = 0;
        if (g_scenario.kingdom_supplies_grain) {
            d.foods[0] = (uint16_t)amount;
            d.num_foods = 1;
            return;
        }

        if (types <= 0) {
            return;
        }

        for (int i = INVENTORY_MIN_FOOD; i < INVENTORY_MAX_FOOD; i++) {
            const e_resource food = city_resource().allowed_foods(i);
            if (food == RESOURCE_NONE) {
                continue;
            }

            uint16_t& stock = d.foods[i];
            bool eaten = false;
            if (stock >= amount) {
                stock = (uint16_t)(stock - amount);
                eaten = true;
            } else if (stock != 0) {
                stock = 0;
                eaten = true;
            }

            if (eaten) {
                res_this_month.consumed[food] += (uint16_t)amount;
                food_types_eaten[food] = 1;
                d.num_foods++;
            }

            food_types_eaten_max_value = std::max<uint8_t>(food_types_eaten_max_value, d.num_foods);
            if (d.num_foods >= types) {
                break;
            }
        }
    });
}

void city_resources_t::advance_month() {
    res_last_month.consumed = res_this_month.consumed;
    res_last_month.produced = res_this_month.produced;
    res_this_month.clear();
}

int city_resources_t::food_types_available_num() const {
    int total_available = 0;
    for (e_resource r = RESOURCES_FOOD_MIN; r < RESOURCES_FOODS_MAX; ++r) {
        if (resource_is_food(r) && food_types_available[r] > 0) {
            total_available++;
        }
    }
    return total_available;
}

int city_resources_t::food_types_eaten_max() {
    int max_foods = 0;
    buildings_house_do([&](building_house *house) {
        if (!house->hsize()) {
            return;
        }
        const int n = house->runtime_data().num_foods;
        if (n > max_foods) {
            max_foods = n;
        }
    });
    food_types_eaten_max_value = (uint8_t)max_foods;
    return max_foods;
}

void city_resource_add_items(e_resource res, int amount) {
    building_storage_yard* chosen_yard = nullptr;
    int lowest_stock_found = 10000;
    buildings_valid_do<building_storage_yard>([&] (auto warehouse) {
        int total_stored = warehouse->amount(res);
        int free_space = warehouse->freespace(res);

        if (free_space >= amount && total_stored < lowest_stock_found) {
            lowest_stock_found = total_stored;
            chosen_yard = warehouse;
        }
    });

    if (chosen_yard == nullptr) {
        return;
    }

    chosen_yard->add_resource(res, amount, /*force*/true); // because I'm lazy.
}

void city_resource_was_added_warning(e_resource res) {
    xstring text;
    text.printf("Added %s", resource_name(res));
    events::emit(event_city_warning{ text });
}

class resource_system : public sim_system {
public:
    const char* name() const override { return "resource"; }
    void on_reset() override { city_resource().reset(); }
    void push_save_sections(int file_version) override {
        g_chunk_io.push_chunk<city_resource_chunk>(city_resource_chunk::size, false);
    }
    void register_steps(sim_schedule_t& schedule) override {
        schedule.add({sim_step_stocks, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 8) {
                              return;
                          }
                          city_resource().calculate_stocks();
                      }});
        schedule.add({sim_step_storageyard_stocks, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 16) {
                              return;
                          }
                          city_resource_calculate_storageyard_stocks();
                      }});
        schedule.add({sim_step_food_stocks, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 17) {
                              return;
                          }
                          city_resource().calculate_food_stocks_and_supply_wheat();
                      }});
        schedule.add({sim_step_food_weekly, SIM_PHASE_WEEK,
          [](int) { city_resource().consume_food_weekly(g_simulation.simtime); }});
        schedule.add(
          {sim_step_food_monthly, SIM_PHASE_MONTH_CITY, [](int) { city_resource().consume_food_monthly(); }});
        schedule.add({sim_step_resource_month, SIM_PHASE_MONTH_CITY, [](int) { city_resource().advance_month(); }});
        schedule.add(
          {sim_step_allowed_foods, SIM_PHASE_MONTH_CITY, [](int) { city_resource().update_allowed_foods(); }});
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_resource_system) {
    static resource_system system;
    g_simulation.register_system(&system);
}

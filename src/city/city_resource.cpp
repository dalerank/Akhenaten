#include "city_resource.h"

#include "building/building.h"
#include "city/city_industry.h"
#include "building/building_storage_yard.h"
#include "building/building_storage_room.h"
#include "building/building_granary.h"
#include "building/building_bazaar.h"
#include "building/building_house.h"
#include "city/city.h"
#include "game/game_events.h"
#include "city/city_warnings.h"
#include "graphics/window.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "empire/empire.h"
#include "game/tutorial.h"
#include "grid/road_access.h"
#include "scenario/scenario.h"
#include "js/js_game.h"

struct available_data_t {
    resource_list resources;
    resource_list foods;
    resource_list market_goods;
};

available_data_t g_available_data;
resource_list g_city_gettable_storages;

int __city_yards_stored(int resource) {
    return g_city.resource.yards_stored((e_resource)resource);
}
ANK_FUNCTION_1(__city_yards_stored)

int city_resources_t::yards_stored(e_resource resource) {
    return stored_in_storages[resource];
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

int city_resource_multiple_wine_available() {
    return g_city.resource.beer_types_available >= 2;
}

int city_resource_food_supply_months() {
    return g_city.resource.food_supply_months;
}
int city_resources_t::food_percentage_produced() {
    return calc_percentage(food_produced_last_month(), food_consumed_last_month());
}

int city_resource_operating_granaries() {
    return g_city.resource.granaries.operating;
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

    // first go for non-getting warehouses
    buildings_valid_do([&] (building &b) {
        building_storage_yard *warehouse = b.dcast_storage_yard();
        if (warehouse && warehouse->is_valid() && !warehouse->is_getting(ev.resource)) {
            ev.amount = warehouse->remove_resource(ev.resource, ev.amount);
        }
    });
    // if that doesn't work, take it anyway
    buildings_valid_do([&] (building &b) {
        building_storage_yard *warehouse = b.dcast_storage_yard();
        if (warehouse && warehouse->is_valid()) {
            ev.amount = warehouse->remove_resource(ev.resource, ev.amount);
        }
    });
}

void city_remove_resource(event_city_remove_resource ev) {
    event_storageyards_remove_resource wh_ev{ ev.resource, ev.amount };
    city_storageyards_remove_resource(wh_ev);

    event_granaries_remove_resource gr_ev{ wh_ev.resource, wh_ev.amount };
    city_granaries_remove_resource(gr_ev);
}

void city_resources_t::calculate_stocks() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Storages Calculate Stocks");

    g_city_gettable_storages.clear();

    buildings_valid_do([] (building &b) {
        auto &storages = g_city_gettable_storages;
        if (!b.has_road_access || b.distance_from_entry <= 0) {
            return;
        }

        building_storage_yard *warehouse = b.dcast_storage_yard();
        if (warehouse) {
            for (const auto &r : resource_list::foods) {
                storages[r.type] += warehouse->is_gettable(r.type) ? warehouse->amount(r.type) : 0;
            }
        }

        building_granary *granary = b.dcast_granary();
        if (granary) {
            for (const auto &r : resource_list::foods) {
                storages[r.type] += granary->is_gettable(r.type) ? granary->amount(r.type) : 0;
            }
        }
    }, { BUILDING_GRANARY, BUILDING_STORAGE_YARD });
}

int city_resources_t::is_stockpiled(e_resource resource) {
    return stockpiled[resource];
}

int city_resource_ready_for_using(e_resource resource) {
    if (g_city.resource.is_stockpiled(resource)) {
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
    g_city.resource.granary_food_stored[food] -= amount;
}

void city_resources_t::init() {
    events::subscribe([this] (event_stats_remove_resource ev) {
        space_in_storages[ev.resource] += ev.amount;
        stored_in_storages[ev.resource] -= ev.amount;
    });

    events::subscribe([this] (event_stats_append_resource ev) {
        space_in_storages[ev.resource] -= ev.amount;
        stored_in_storages[ev.resource] += ev.amount;
    });

    events::subscribe([this] (event_produced_resources ev) {
        res_this_month.produced[ev.resource] += ev.amount;
    });

    events::subscribe(&city_granaries_remove_resource);
    events::subscribe(&city_storageyards_add_resource);
    events::subscribe(&city_storageyards_remove_resource);
    events::subscribe(&city_remove_resource);

    events::subscribe([this] (event_toggle_industry_mothballed ev) {
        mothballed[ev.resource] = !mothballed[ev.resource];
    });
}

void city_resource_calculate_storageyard_stocks() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Warehouse Stocks Update");
    for (int i = 0; i < RESOURCES_MAX; i++) {
        g_city.resource.space_in_storages[i] = 0;
        g_city.resource.stored_in_storages[i] = 0;
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
            int amounts = room->base.stored_amount_first;
            e_resource resource = room->resource();
            g_city.resource.stored_in_storages[resource] += amounts;
            g_city.resource.space_in_storages[resource] += 400 - amounts;
        } else {
            g_city.resource.space_in_storages[RESOURCE_NONE] += 4;
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
        if (g_city.can_produce_resource(r.type) || g_empire.can_import_resource(r.type, false)) {
            g_available_data.foods[r.type] = 1;
            g_available_data.market_goods[r.type] = 1;
        }
    }

    for (const auto &r : resource_list::all) {
        if (g_city.can_produce_resource(r.type) || g_empire.can_import_resource(r.type, false)) {
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
            if (g_city.can_produce_resource(raw) || g_empire.can_import_resource(raw, false)) {
                g_available_data.resources[r.type] = 1;
            }
        }
    }
}

void city_resources_t::calculate_available_food() {
    for (int i = 0; i < RESOURCES_FOODS_MAX; i++) {
        granary_food_stored[i] = 0;
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
        int pct_workers = calc_percentage<int>(b.num_workers, b.max_workers);
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

    for (int i = RESOURCES_FOOD_MIN; i < RESOURCES_FOODS_MAX; i++) {
        const bool hasInCity = granary_food_stored[i];
        granary_total_stored += granary_food_stored[i];
    }

    food_needed_per_month = calc_adjust_with_percentage(g_city.population.current, 50);
    if (food_needed_per_month > 0) {
        food_supply_months = granary_total_stored / food_needed_per_month;
    } else {
        food_supply_months = granary_total_stored > 0 ? 1 : 0;
    }

    if (g_scenario.kingdom_supplies_grain) {
        food_supply_months = 12;
    }
}

void city_resources_t::calculate_food_stocks_and_supply_wheat() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Food Stocks Update");
    calculate_available_food();
    if (!g_scenario.kingdom_supplies_grain) {
        return;
    }

    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building_bazaar* bazaar = building_get(i)->dcast_bazaar();
        if (bazaar && bazaar->state() == BUILDING_STATE_VALID) {
            bazaar->runtime_data().inventory[0] = 200;
        }
    }
}

void city_resources_t::consume_goods_weekly(const simulation_time_t& t) {
    resource_list consumed_goods;
    buildings_house_do([&] (building_house *house) {
        auto house_consumed = house->consume_goods_weekly();
        consumed_goods.append(house_consumed);
    });

    res_this_month.consumed.append(consumed_goods);
}

void city_resources_t::consume_food_weekly(const simulation_time_t& t) {
    calculate_available_food();
    resource_list consumed_food;
    buildings_house_do([&] (building_house *house) {
        resource_list consumed = house->consume_food_weekly();
        consumed_food.append(consumed);
    });

    res_this_month.consumed.append(consumed_food);
}

void city_resources_t::advance_month() {
    res_last_month.consumed = res_this_month.consumed;
    res_last_month.produced = res_this_month.produced;
    res_this_month.clear();
}

int city_resources_t::food_types_available_num() {
    int total_available = 0;
    for (int t = INVENTORY_MIN_FOOD; t < INVENTORY_MAX_FOOD; t++) {
        const bool available = food_types_available[t] > 0;
        total_available += (available ? 1 : 0);
    }

    return total_available;
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

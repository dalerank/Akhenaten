#include "city_resource.h"

#include "building/building.h"
#include "building/industry.h"
#include "building/model.h"
#include "building/building_storage_yard.h"
#include "building/building_granary.h"
#include "city/city.h"
#include "city/warning.h"
#include "graphics/window.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "empire/empire.h"
#include "game/tutorial.h"
#include "grid/road_access.h"
#include "scenario/scenario.h"

struct available_data_t {
    resource_list resources;
    resource_list foods;
    resource_list market_goods;
};

available_data_t g_available_data;

static auto &city_data = g_city;
int city_resource_warehouse_stored(e_resource resource) {
    return city_data.resource.stored_in_warehouses[resource];
}

int city_resource_granary_stored(e_resource resource) {
    if (!resource_is_food(resource)) {
        return 0;
    }
    return city_data.resource.granary_food_stored[resource];
}

int city_resource_storages_stored(e_resource resource) {
    return city_resource_warehouse_stored(resource) 
            + city_resource_granary_stored(resource);
}

const resource_list &city_resource_get_available() {
    return g_available_data.resources;
}

const resource_list &city_resource_get_available_foods() {
    return g_available_data.foods;
}

const resource_list &city_resource_get_available_market_goods() {
    return g_available_data.market_goods;
}

int city_resource_multiple_wine_available() {
    return city_data.resource.wine_types_available >= 2;
}

int city_resource_food_types_available() {
    return city_data.resource.food_types_available_num;
}
int city_resource_food_stored() {
    return city_data.resource.granary_total_stored;
}
int city_resource_food_needed() {
    return city_data.resource.food_needed_per_month;
}
int city_resource_food_supply_months() {
    return city_data.resource.food_supply_months;
}
int city_resource_food_percentage_produced() {
    return calc_percentage(city_data.resource.food_produced_last_month, city_data.resource.food_consumed_last_month);
}

int city_resource_operating_granaries() {
    return city_data.resource.granaries.operating;
}
int city_resource_last_used_storageyard() {
    return city_data.resource.last_used_warehouse;
}
void city_resource_set_last_used_storageyard(int warehouse_id) {
    city_data.resource.last_used_warehouse = warehouse_id;
}

e_trade_status city_resource_trade_status(e_resource resource) {
    return city_data.resource.trade_status[resource];
}

void city_resource_cycle_trade_status(e_resource resource) {
    auto &trade_status = city_data.resource.trade_status[resource];
    trade_status = (e_trade_status)((int)trade_status + 1);
    if (trade_status > TRADE_STATUS_EXPORT) {
        trade_status = TRADE_STATUS_NONE;
    }

    if (trade_status == TRADE_STATUS_IMPORT && !g_empire.can_import_resource(resource, true)) {
        trade_status = TRADE_STATUS_EXPORT;
    }

    if (trade_status == TRADE_STATUS_EXPORT && !g_empire.can_export_resource(resource, true)) {
        trade_status = TRADE_STATUS_NONE;
    }

    if (trade_status == TRADE_STATUS_EXPORT) {
        trade_status = TRADE_STATUS_NONE;
    }
}

void city_resource_cycle_trade_import(e_resource resource) {
    // no sellers?
    if (!g_empire.can_import_resource(resource, true))
        return;

    switch (city_data.resource.trade_status[resource]) {
    default:
        city_data.resource.trade_status[resource] = TRADE_STATUS_IMPORT_AS_NEEDED;
        break;
    case TRADE_STATUS_IMPORT_AS_NEEDED:
        city_data.resource.trade_status[resource] = TRADE_STATUS_IMPORT;
        break;
    case TRADE_STATUS_IMPORT:
        city_data.resource.trade_status[resource] = TRADE_STATUS_NONE;
        break;
    }
}

void city_resource_cycle_trade_export(e_resource resource) {
    // no buyers?
    if (!g_empire.can_export_resource(resource, true))
        return;

    switch (city_data.resource.trade_status[resource]) {
    default:
        city_data.resource.trade_status[resource] = TRADE_STATUS_EXPORT_SURPLUS;
        city_data.resource.stockpiled[resource] = false;
        break;

    case TRADE_STATUS_EXPORT_SURPLUS:
        city_data.resource.trade_status[resource] = TRADE_STATUS_EXPORT;
        city_data.resource.stockpiled[resource] = false;
        break;

    case TRADE_STATUS_EXPORT:
        city_data.resource.trade_status[resource] = TRADE_STATUS_NONE;
        break;
    }
}

int city_resource_trading_amount(e_resource resource) {
    return city_data.resource.trading_amount[resource];
}

void city_resource_change_trading_amount(e_resource resource, int delta) {
    city_data.resource.trading_amount[resource] = calc_bound(city_data.resource.trading_amount[resource] + delta, 0, 10000);
}

int city_resource_is_stockpiled(e_resource resource) {
    return city_data.resource.stockpiled[resource];
}

int city_resource_ready_for_using(e_resource resource) {
    if (city_resource_is_stockpiled(resource)) {
        return 0;
    }

    int amount = 0;
    buildings_valid_do<building_storage_yard>([&] (building_storage_yard *warehouse) {
        amount += warehouse->amount(resource);
    });

    return amount;
}

void city_resource_toggle_stockpiled(e_resource resource) {
    if (city_data.resource.stockpiled[resource])
        city_data.resource.stockpiled[resource] = 0;
    else {
        city_data.resource.stockpiled[resource] = 1;
        if (city_data.resource.trade_status[resource] == TRADE_STATUS_EXPORT
            || city_data.resource.trade_status[resource] == TRADE_STATUS_EXPORT_SURPLUS)
            city_data.resource.trade_status[resource] = TRADE_STATUS_NONE;
    }
}

int city_resource_is_mothballed(e_resource resource) {
    return city_data.resource.mothballed[resource];
}

void city_resource_toggle_mothballed(e_resource resource) {
    city_data.resource.mothballed[resource] = city_data.resource.mothballed[resource] ? 0 : 1;
}

void city_resource_add_produced_to_granary(int amount) {
    city_data.resource.food_produced_this_month += amount;
}
void city_resource_remove_from_granary(int food, int amount) {
    city_data.resource.granary_food_stored[food] -= amount;
}

void city_resource_add_to_storageyard(e_resource resource, int amount) {
    city_data.resource.space_in_warehouses[resource] -= amount;
    city_data.resource.stored_in_warehouses[resource] += amount;
}

void city_resource_remove_from_storageyard(e_resource resource, int amount) {
    city_data.resource.space_in_warehouses[resource] += amount;
    city_data.resource.stored_in_warehouses[resource] -= amount;
}

int city_storageyards_remove_resource(e_resource resource, int amount) {
    int amount_left = amount;

    // first go for non-getting warehouses
    buildings_valid_do([&] (building &b) {
        building_storage_yard *warehouse = b.dcast_storage_yard();
        if (warehouse && warehouse->is_valid() && !warehouse->is_getting(resource)) {
            amount_left = warehouse->remove_resource(resource, amount_left);
        }
    });
    // if that doesn't work, take it anyway
    buildings_valid_do([&] (building &b) {
        building_storage_yard *warehouse = b.dcast_storage_yard();
        if (warehouse && warehouse->is_valid()) {
            amount_left = warehouse->remove_resource(resource, amount_left);
        }
    });

    return amount - amount_left;
}

int city_granaries_remove_resource(e_resource resource, int amount) {
    int amount_left = amount;

    // first go for non-getting warehouses
    buildings_valid_do([&] (building &b) {
        building_granary *granary = b.dcast_granary();
        if (granary && granary->is_valid() && !granary->is_getting(resource)) {
            amount_left = granary->remove_resource(resource, amount_left);
        }
    });
    // if that doesn't work, take it anyway
    buildings_valid_do([&] (building &b) {
        building_granary *granary = b.dcast_granary();
        if (granary && granary->is_valid()) {
            amount_left = granary->remove_resource(resource, amount_left);
        }
    });

    return amount - amount_left;
}


void city_resource_calculate_storageyard_stocks() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Warehouse Stocks Update");
    for (int i = 0; i < RESOURCES_MAX; i++) {
        city_data.resource.space_in_warehouses[i] = 0;
        city_data.resource.stored_in_warehouses[i] = 0;
    }

    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_STORAGE_YARD) {
            tile2i road_access_tile = map_has_road_access_rotation(b->orientation, b->tile, b->size);
            b->has_road_access = road_access_tile.valid();
        }
    }

    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_STORAGE_ROOM)
            continue;

        building* warehouse = b->main();
        if (warehouse->has_road_access) {
            b->has_road_access = warehouse->has_road_access;
            if (b->data.warehouse.resource_id) {
                int amounts = b->stored_amount_first;
                int resource = b->data.warehouse.resource_id;
                city_data.resource.stored_in_warehouses[resource] += amounts;
                city_data.resource.space_in_warehouses[resource] += 400 - amounts;
            } else {
                city_data.resource.space_in_warehouses[RESOURCE_NONE] += 4;
            }
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

static void calculate_available_food() {
    for (int i = 0; i < RESOURCES_FOODS_MAX; i++) {
        city_data.resource.granary_food_stored[i] = 0;
    }
    city_data.resource.granary_total_stored = 0;
    city_data.resource.food_types_available_num = 0;
    city_data.resource.food_supply_months = 0;
    city_data.resource.granaries.operating = 0;
    city_data.resource.granaries.understaffed = 0;
    city_data.resource.granaries.not_operating = 0;
    city_data.resource.granaries.not_operating_with_food = 0;

    buildings_valid_do([] (building &b) {
        b.has_road_access = false;
        if (map_has_road_access(b.tile, b.size)) { // map_has_road_access_granary(b->tile.x(), b->tile.y(), 0)
            b.has_road_access = true;
            int pct_workers = calc_percentage<int>(b.num_workers, model_get_building(b.type)->laborers);
            if (pct_workers < 100) {
                city_data.resource.granaries.understaffed++;
            }

            int amount_stored = 0;
            for (int r = RESOURCE_FOOD_MIN; r < RESOURCES_FOODS_MAX; r++) {
                amount_stored += b.data.granary.resource_stored[r];
            }

            if (pct_workers < 50) {
                city_data.resource.granaries.not_operating++;
                if (amount_stored > 0)
                    city_data.resource.granaries.not_operating_with_food++;

            } else {
                city_data.resource.granaries.operating++;
                for (int r = 0; r < RESOURCES_FOODS_MAX; r++)
                    city_data.resource.granary_food_stored[r] += b.data.granary.resource_stored[r];

                if (amount_stored >= 100)
                    tutorial_on_filled_granary(amount_stored);
            }
        }
    }, BUILDING_GRANARY);

    for (int i = RESOURCE_FOOD_MIN; i < RESOURCES_FOODS_MAX; i++) {
        if (city_data.resource.granary_food_stored[i]) {
            city_data.resource.granary_total_stored += city_data.resource.granary_food_stored[i];
            city_data.resource.food_types_available_num++;
        }
    }

    city_data.resource.food_needed_per_month = calc_adjust_with_percentage(city_data.population.population, 50);
    if (city_data.resource.food_needed_per_month > 0) {
        city_data.resource.food_supply_months
          = city_data.resource.granary_total_stored / city_data.resource.food_needed_per_month;
    } else {
        city_data.resource.food_supply_months = city_data.resource.granary_total_stored > 0 ? 1 : 0;
    }
    if (scenario_property_kingdom_supplies_grain()) {
        //        city_data.resource.food_types_available = 1;
        city_data.resource.food_supply_months = 12;
    }
}

void city_resource_calculate_food_stocks_and_supply_wheat() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Food Stocks Update");
    calculate_available_food();
    if (scenario_property_kingdom_supplies_grain()) {
        for (int i = 1; i < MAX_BUILDINGS; i++) {
            building* b = building_get(i);
            if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_BAZAAR)
                b->data.market.inventory[0] = 200;
        }
    }
}

void city_resource_consume_food() {
    calculate_available_food();
    city_data.resource.food_types_eaten_num = 0;
    city_data.unused.unknown_00c0 = 0;
    int total_consumed = 0;
    buildings_house_do([&total_consumed] (building &b) {
        if (!b.house_size) {
            return;
        }

        int num_types = model_get_house(b.data.house.level)->food_types;
        short amount_per_type = calc_adjust_with_percentage<short>(b.house_population, 35);
        if (num_types > 1) {
            amount_per_type /= num_types;
        }

        b.data.house.num_foods = 0;
        if (scenario_property_kingdom_supplies_grain()) {
            city_data.resource.food_types_eaten_num = 1;
            b.data.house.foods[0] = amount_per_type;
            b.data.house.num_foods = 1;
            return;
        } 
        
        if (num_types <= 0) {
            return;
        }

        for (int t = INVENTORY_MIN_FOOD; t < INVENTORY_MAX_FOOD && b.data.house.num_foods < num_types; t++) {
            if (b.data.house.foods[t] >= amount_per_type) {
                b.data.house.foods[t] -= amount_per_type;
                b.data.house.num_foods++;
                total_consumed += amount_per_type;
            } else if (b.data.house.foods[t] > 0) {
                // has food but not enough
                total_consumed += b.data.house.foods[t];
                b.data.house.foods[t] = 0;
                b.data.house.num_foods++;
            }

            if (b.data.house.num_foods > city_data.resource.food_types_eaten_num) {
                city_data.resource.food_types_eaten_num = b.data.house.num_foods;
            }
        }
    });

    city_data.resource.food_consumed_last_month = total_consumed;
    city_data.resource.food_produced_last_month = city_data.resource.food_produced_this_month;
    city_data.resource.food_produced_this_month = 0;
}

void city_resource_add_items(e_resource res, int amount) {
    building_storage_yard* chosen_yard = nullptr;
    int lowest_stock_found = 10000;
    buildings_valid_do<building_storage_yard>([&] (building_storage_yard *warehouse) {
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

    chosen_yard->add_resource(res, false, amount, /*force*/true); // because I'm lazy.
}

void city_resource_was_added_warning(e_resource res) {
    city_warning_show_console(bstring128("Added ", resource_name(res)).c_str());
}

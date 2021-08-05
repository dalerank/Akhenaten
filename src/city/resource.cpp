#include "resource.h"

#include "building/building.h"
#include "building/industry.h"
#include "building/model.h"
#include "city/data_private.h"
#include "core/calc.h"
#include "empire/city.h"
#include "game/tutorial.h"
#include "map/road_access.h"
#include "scenario/building.h"
#include "scenario/property.h"

static struct {
    resources_list resource_list;
    resources_list food_list;
    resources_list market_goods_list;
} available;

int city_resource_count(int resource) {
    return city_data.resource.stored_in_warehouses[resource];
}

const resources_list *city_resource_get_available(void) {
    return &available.resource_list;
}
const resources_list *city_resource_get_available_foods(void) {
    return &available.food_list;
}
const resources_list *city_resource_get_available_market_goods(void) {
    return &available.market_goods_list;
}


int city_resource_multiple_wine_available(void) {
    return city_data.resource.wine_types_available >= 2;
}

int city_resource_food_types_available(void) {
    return city_data.resource.food_types_available_num;
}
int city_resource_food_stored(void) {
    return city_data.resource.granary_total_stored;
}
int city_resource_food_needed(void) {
    return city_data.resource.food_needed_per_month;
}
int city_resource_food_supply_months(void) {
    return city_data.resource.food_supply_months;
}
int city_resource_food_percentage_produced(void) {
    return calc_percentage(city_data.resource.food_produced_last_month, city_data.resource.food_consumed_last_month);
}

int city_resource_operating_granaries(void) {
    return city_data.resource.granaries.operating;
}
int city_resource_last_used_warehouse(void) {
    return city_data.resource.last_used_warehouse;
}
void city_resource_set_last_used_warehouse(int warehouse_id) {
    city_data.resource.last_used_warehouse = warehouse_id;
}

int city_int(int resource) {
    return city_data.resource.trade_status[resource];
}

void city_resource_cycle_trade_status(int resource) {
    ++city_data.resource.trade_status[resource];
    if (city_data.resource.trade_status[resource] > TRADE_STATUS_EXPORT)
        city_data.resource.trade_status[resource] = TRADE_STATUS_NONE;

    if (city_data.resource.trade_status[resource] == TRADE_STATUS_IMPORT &&
        !empire_can_import_resource(resource, true)) {
        city_data.resource.trade_status[resource] = TRADE_STATUS_EXPORT;
    }
    if (city_data.resource.trade_status[resource] == TRADE_STATUS_EXPORT &&
        !empire_can_export_resource(resource, true)) {
        city_data.resource.trade_status[resource] = TRADE_STATUS_NONE;
    }
    if (city_data.resource.trade_status[resource] == TRADE_STATUS_EXPORT)
        city_data.resource.stockpiled[resource] = 0;
}
void city_resource_cycle_trade_import(int resource) {
    // no sellers?
    if (!empire_can_import_resource(resource, true))
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
void city_resource_cycle_trade_export(int resource) {
    // no buyers?
    if (!empire_can_export_resource(resource, true))
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
int city_resource_trading_amount(int resource) {
    return city_data.resource.trading_amount[resource];
}
void city_resource_change_trading_amount(int resource, int delta) {
    city_data.resource.trading_amount[resource] = calc_bound(city_data.resource.trading_amount[resource] + delta, 0, 100);
}

int city_resource_is_stockpiled(int resource) {
    return city_data.resource.stockpiled[resource];
}
void city_resource_toggle_stockpiled(int resource) {
    if (city_data.resource.stockpiled[resource])
        city_data.resource.stockpiled[resource] = 0;
    else {
        city_data.resource.stockpiled[resource] = 1;
        if (city_data.resource.trade_status[resource] == TRADE_STATUS_EXPORT
            || city_data.resource.trade_status[resource] == TRADE_STATUS_EXPORT_SURPLUS)
            city_data.resource.trade_status[resource] = TRADE_STATUS_NONE;
    }
}
int city_resource_is_mothballed(int resource) {
    return city_data.resource.mothballed[resource];
}
void city_resource_toggle_mothballed(int resource) {
    city_data.resource.mothballed[resource] = city_data.resource.mothballed[resource] ? 0 : 1;
}

int city_resource_has_workshop_with_room(int workshop_type) {
    // todo: prevent oversending goods from warehouses etc.
    return city_data.resource.space_in_workshops[workshop_type] > 0;
}
void city_resource_add_produced_to_granary(int amount) {
    city_data.resource.food_produced_this_month += amount;
}
void city_resource_remove_from_granary(int food, int amount) {
    city_data.resource.granary_food_stored[food] -= amount;
}
void city_resource_add_to_warehouse(int resource, int amount) {
    city_data.resource.space_in_warehouses[resource] -= amount;
    city_data.resource.stored_in_warehouses[resource] += amount;
}
void city_resource_remove_from_warehouse(int resource, int amount) {
    city_data.resource.space_in_warehouses[resource] += amount;
    city_data.resource.stored_in_warehouses[resource] -= amount;
}

void city_resource_calculate_warehouse_stocks(void) {
    for (int i = 0; i < RESOURCE_MAX[GAME_ENV]; i++) {
        city_data.resource.space_in_warehouses[i] = 0;
        city_data.resource.stored_in_warehouses[i] = 0;
    }
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        building *b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_WAREHOUSE) {
            b->has_road_access = 0;
            if (map_has_road_access_rotation(b->subtype.orientation, b->x, b->y, b->size, 0))
                b->has_road_access = 1;
            else if (map_has_road_access_rotation(b->subtype.orientation, b->x, b->y, 3, 0))
                b->has_road_access = 2;

        }
    }
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        building *b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_WAREHOUSE_SPACE)
            continue;

        building *warehouse = b->main();
        if (warehouse->has_road_access) {
            b->has_road_access = warehouse->has_road_access;
            if (b->subtype.warehouse_resource_id) {
                int loads = b->loads_stored;
                int resource = b->subtype.warehouse_resource_id;
                city_data.resource.stored_in_warehouses[resource] += loads;
                city_data.resource.space_in_warehouses[resource] += 4 - loads;
            } else {
                city_data.resource.space_in_warehouses[RESOURCE_NONE] += 4;
            }
        }
    }
}
void city_resource_determine_available(void) {
    for (int i = 0; i < RESOURCE_MAX[GAME_ENV]; i++) {
        available.resource_list.items[i] = 0;
        available.food_list.items[i] = 0;
    }
    available.resource_list.size = 0;
    available.food_list.size = 0;
    available.market_goods_list.size = 0;

    for (int i = RESOURCE_MIN_FOOD; i < RESOURCE_MAX_FOOD[GAME_ENV]; i++) {
        if (GAME_ENV == ENGINE_ENV_C3 && (i == RESOURCE_OLIVES || i == RESOURCE_VINES))
            continue;

        if (empire_can_produce_resource(i, true) || empire_can_import_resource(i, false) ||
            (GAME_ENV == ENGINE_ENV_C3 && i == RESOURCE_MEAT_C3 && scenario_building_allowed(BUILDING_WHARF))) {
            available.food_list.items[available.food_list.size++] = i;
            available.market_goods_list.items[available.market_goods_list.size++] = i;
        }
    }
    for (int i = RESOURCE_MIN; i < RESOURCE_MAX[GAME_ENV]; i++) {
        if (empire_can_produce_resource(i, true) || empire_can_import_resource(i, false) ||
            (GAME_ENV == ENGINE_ENV_C3 && i == RESOURCE_MEAT_C3 && scenario_building_allowed(BUILDING_WHARF))) {
            available.resource_list.items[available.resource_list.size++] = i;
            switch (i) {
                case RESOURCE_POTTERY_PH:
                case RESOURCE_BEER:
                case RESOURCE_LINEN:
                case RESOURCE_LUXURY_GOODS:
                    available.market_goods_list.items[available.market_goods_list.size++] = i;
                    break;
            }
        }
    }
}
static void calculate_available_food(void) {
    for (int i = 0; i < RESOURCE_MAX_FOOD[GAME_ENV]; i++) {
        city_data.resource.granary_food_stored[i] = 0;
    }
    city_data.resource.granary_total_stored = 0;
    city_data.resource.food_types_available_num = 0;
    city_data.resource.food_supply_months = 0;
    city_data.resource.granaries.operating = 0;
    city_data.resource.granaries.understaffed = 0;
    city_data.resource.granaries.not_operating = 0;
    city_data.resource.granaries.not_operating_with_food = 0;
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        building *b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_GRANARY)
            continue;

        b->has_road_access = 0;
        if (map_has_road_access(b->x, b->y, b->size, 0)) { //map_has_road_access_granary(b->x, b->y, 0)
            b->has_road_access = 1;
            int pct_workers = calc_percentage(
                    b->num_workers, model_get_building(b->type)->laborers);
            if (pct_workers < 100)
                city_data.resource.granaries.understaffed++;

            int amount_stored = 0;
            for (int r = RESOURCE_MIN_FOOD; r < RESOURCE_MAX_FOOD[GAME_ENV]; r++) {
                amount_stored += b->data.granary.resource_stored[r];
            }
            if (pct_workers < 50) {
                city_data.resource.granaries.not_operating++;
                if (amount_stored > 0)
                    city_data.resource.granaries.not_operating_with_food++;

            } else {
                city_data.resource.granaries.operating++;
                for (int r = 0; r < RESOURCE_MAX_FOOD[GAME_ENV]; r++)
                    city_data.resource.granary_food_stored[r] += b->data.granary.resource_stored[r];
                if (amount_stored >= 100)
                    tutorial_on_filled_granary(amount_stored);
            }
        }
    }
    for (int i = RESOURCE_MIN_FOOD; i < RESOURCE_MAX_FOOD[GAME_ENV]; i++) {
        if (city_data.resource.granary_food_stored[i]) {
            city_data.resource.granary_total_stored += city_data.resource.granary_food_stored[i];
            city_data.resource.food_types_available_num++;
        }
    }
    city_data.resource.food_needed_per_month =
            calc_adjust_with_percentage(city_data.population.population, 50);
    if (city_data.resource.food_needed_per_month > 0) {
        city_data.resource.food_supply_months =
                city_data.resource.granary_total_stored / city_data.resource.food_needed_per_month;
    } else {
        city_data.resource.food_supply_months =
                city_data.resource.granary_total_stored > 0 ? 1 : 0;
    }
    if (scenario_property_rome_supplies_wheat()) {
//        city_data.resource.food_types_available = 1;
        city_data.resource.food_supply_months = 12;
    }
}
void city_resource_calculate_food_stocks_and_supply_wheat(void) {
    calculate_available_food();
    if (scenario_property_rome_supplies_wheat()) {
        for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
            building *b = building_get(i);
            if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_MARKET)
                b->data.market.inventory[0] = 200;

        }
    }
}
void city_resource_calculate_workshop_stocks(void) {
    for (int i = 0; i < 6; i++) {
        city_data.resource.stored_in_workshops[i] = 0;
        city_data.resource.space_in_workshops[i] = 0;
    }
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        building *b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || !building_is_workshop(b->type))
            continue;

        b->has_road_access = 0;
        if (map_has_road_access(b->x, b->y, b->size, 0)) {
            b->has_road_access = 1;
            int room = 2 - b->loads_stored;
            if (room < 0)
                room = 0;

            int workshop_resource = b->subtype.workshop_type;
            city_data.resource.space_in_workshops[workshop_resource] += room;
            city_data.resource.stored_in_workshops[workshop_resource] += b->loads_stored;
        }
    }
}

void city_resource_consume_food(void) {
    calculate_available_food();
    city_data.resource.food_types_eaten_num = 0;
    city_data.unused.unknown_00c0 = 0;
    int total_consumed = 0;
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        building *b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->house_size) {
            int num_types = model_get_house(b->subtype.house_level)->food_types;
            int amount_per_type = calc_adjust_with_percentage(b->house_population, 50);
            if (num_types > 1)
                amount_per_type /= num_types;

            b->data.house.num_foods = 0;
            if (scenario_property_rome_supplies_wheat()) {
                city_data.resource.food_types_eaten_num = 1;
//                city_data.resource.food_types_available = 1;
                b->data.house.inventory[0] = amount_per_type;
                b->data.house.num_foods = 1;
            } else if (num_types > 0) {
                for (int t = INVENTORY_MIN_FOOD; t < INVENTORY_MAX_FOOD && b->data.house.num_foods < num_types; t++) {
                    if (b->data.house.inventory[t] >= amount_per_type) {
                        b->data.house.inventory[t] -= amount_per_type;
                        b->data.house.num_foods++;
                        total_consumed += amount_per_type;
                    } else if (b->data.house.inventory[t]) {
                        // has food but not enough
                        b->data.house.inventory[t] = 0;
                        b->data.house.num_foods++;
                        total_consumed += amount_per_type;
                    }
                    if (b->data.house.num_foods > city_data.resource.food_types_eaten_num)
                        city_data.resource.food_types_eaten_num = b->data.house.num_foods;

                }
            }
        }
    }
    city_data.resource.food_consumed_last_month = total_consumed;
    city_data.resource.food_produced_last_month = city_data.resource.food_produced_this_month;
    city_data.resource.food_produced_this_month = 0;
}

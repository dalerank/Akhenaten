#include "city.h"

#include "city/buildings.h"
#include "city/finance.h"
#include "city/map.h"
#include "city/message.h"
#include "city/trade.h"
#include "empire/object.h"
#include "empire/trade_route.h"
#include "empire/type.h"
#include "figuretype/trader.h"
#include "scenario/map.h"
#include "core/game_environment.h"

#include <string.h>
#include <city/data_private.h>

const static int MAX_CITIES[2] = {
        41,
        61
};

static empire_city cities[61];

void empire_city_clear_all(void) {
    memset(cities, 0, sizeof(cities));
}

empire_city *empire_city_get(int city_id) {
    if (city_id >= 0 && city_id < MAX_CITIES[GAME_ENV])
        return &cities[city_id];
    else
        return 0;
}

int empire_city_get_route_id(int city_id) {
    return cities[city_id].route_id;
}

bool empire_can_import_resource(int resource, bool check_if_open) {
    for (int i = 0; i < MAX_CITIES[GAME_ENV]; i++) {
        if (cities[i].in_use &&
            empire_city_type_can_trade(cities[i].type) &&
            (cities[i].is_open || !check_if_open) &&
            cities[i].sells_resource[resource]) {
            return true;
        }
    }
    return false;
}
bool empire_can_export_resource(int resource, bool check_if_open) {
    for (int i = 0; i < MAX_CITIES[GAME_ENV]; i++) {
        if (cities[i].in_use &&
            empire_city_type_can_trade(cities[i].type) &&
            (cities[i].is_open || !check_if_open) &&
            cities[i].buys_resource[resource]) {
            return true;
        }
    }
    return false;
}

static bool can_produce_resource(int resource) {
    for (int i = 0; i < MAX_CITIES[GAME_ENV]; i++) {
        if (cities[i].in_use &&
            ((GAME_ENV == ENGINE_ENV_C3 && cities[i].type == EMPIRE_CITY_PHARAOH_TRADING)
            || (GAME_ENV == ENGINE_ENV_PHARAOH && cities[i].type == EMPIRE_CITY_OURS))) {
            if (cities[i].sells_resource[resource] == 1)
                return true;
        }
    }
    return false;
}
static int get_raw_resource(int resource) {
    if (GAME_ENV == ENGINE_ENV_C3)
        switch (resource) {
            case RESOURCE_POTTERY:
                return RESOURCE_CLAY;
            case RESOURCE_LUXURY_GOODS:
                return RESOURCE_GEMS;
            case RESOURCE_MEAT:
                return RESOURCE_STRAW;
            case RESOURCE_BEER:
                return RESOURCE_BARLEY;
            case RESOURCE_WEAPONS:
                return RESOURCE_COPPER;
            default:
                return resource;
        }
    else if (GAME_ENV == ENGINE_ENV_PHARAOH)
        switch (resource) {
            case RESOURCE_STRAW:
                return RESOURCE_GRAIN;
            case RESOURCE_POTTERY:
                return RESOURCE_CLAY;
            case RESOURCE_LUXURY_GOODS:
                return RESOURCE_GEMS;
            case RESOURCE_LINEN:
                return RESOURCE_FLAX;
            case RESOURCE_BEER:
                return RESOURCE_BARLEY;
            case RESOURCE_WEAPONS:
                return RESOURCE_COPPER;
            case RESOURCE_PAPYRUS:
                return RESOURCE_REEDS;
            case RESOURCE_CHARIOTS:
                return RESOURCE_TIMBER;
            case RESOURCE_PAINT:
                return RESOURCE_HENNA;
            case RESOURCE_LAMPS:
                return RESOURCE_OIL;
            default:
                return resource;
        }
}

bool empire_can_produce_resource(int resource, bool check_if_open) {
    int raw_resource = get_raw_resource(resource);
    // finished goods: check imports of raw materials
    if (raw_resource != resource && empire_can_import_resource(raw_resource, false))
        return true;

//    // if food, see if it's enabled
//    if (is_food_allowed(resource))
//        return true;

    // check if we can produce the raw materials
    return can_produce_resource(raw_resource);
}

int empire_city_get_for_object(int empire_object_id) {
    for (int i = 0; i < MAX_CITIES[GAME_ENV]; i++) {
        if (cities[i].in_use && cities[i].empire_object_id == empire_object_id)
            return i;
    }
    return 0;
}
int empire_city_get_for_trade_route(int route_id) {
    for (int i = 0; i < MAX_CITIES[GAME_ENV]; i++) {
        if (cities[i].in_use && cities[i].route_id == route_id)
            return i;
    }
    return -1;
}

bool empire_city_is_trade_route_open(int route_id) {
    for (int i = 0; i < MAX_CITIES[GAME_ENV]; i++) {
        if (cities[i].in_use && cities[i].route_id == route_id)
            return cities[i].is_open; // ? true : false;
    }
    return false;
}
void empire_city_reset_yearly_trade_amounts(void) {
    for (int i = 0; i < MAX_CITIES[GAME_ENV]; i++) {
        if (cities[i].in_use && cities[i].is_open)
            trade_route_reset_traded(cities[i].route_id);
    }
}

int empire_city_count_wine_sources(void) {
    int sources = 0;
    for (int i = 1; i < MAX_CITIES[GAME_ENV]; i++) {
        if (cities[i].in_use &&
            cities[i].is_open &&
            cities[i].sells_resource[RESOURCE_BEER]) {
            sources++;
        }
    }
    return sources;
}

int empire_city_get_vulnerable_roman(void) {
    int city = 0;
    for (int i = 0; i < MAX_CITIES[GAME_ENV]; i++) {
        if (cities[i].in_use) {
            if (cities[i].type == EMPIRE_CITY_FOREIGN_TRADING)
                city = i;
        }
    }
    return city;
}

void empire_city_expand_empire(void) {
    for (int i = 0; i < MAX_CITIES[GAME_ENV]; i++) {
        if (!cities[i].in_use)
            continue;

        if (cities[i].type == EMPIRE_CITY_EGYPTIAN_TRADING)
            cities[i].type = EMPIRE_CITY_PHARAOH;
        else if (cities[i].type == EMPIRE_CITY_FOREIGN)
            cities[i].type = EMPIRE_CITY_OURS;
        else {
            continue;
        }
        empire_object_set_expanded(cities[i].empire_object_id, cities[i].type);
    }
}

static bool generate_trader(int city_id, empire_city *city) {
    if (city_data.religion.ra_no_traders_months_left > 0)
        return false;
    int max_traders = 0;
    int num_resources = 0;
    for (int r = RESOURCE_MIN; r < RESOURCES_MAX; r++) {
        if (city->buys_resource[r] || city->sells_resource[r]) {
            ++num_resources;
            switch (trade_route_limit(city->route_id, r)) {
                case 15:
                    max_traders += 1;
                    break;
                case 25:
                    max_traders += 2;
                    break;
                case 40:
                    max_traders += 3;
                    break;
            }
        }
    }
    if (num_resources > 1) {
        if (max_traders % num_resources)
            max_traders = max_traders / num_resources + 1;
        else
            max_traders = max_traders / num_resources;
    }
    if (max_traders <= 0)
        return false;

    int index;
    if (max_traders == 1) {
        if (!city->trader_figure_ids[0])
            index = 0;
        else
            return false;
    } else if (max_traders == 2) {
        if (!city->trader_figure_ids[0])
            index = 0;
        else if (!city->trader_figure_ids[1])
            index = 1;
        else
            return false;
    } else { // 3
        if (!city->trader_figure_ids[0])
            index = 0;
        else if (!city->trader_figure_ids[1])
            index = 1;
        else if (!city->trader_figure_ids[2])
            index = 2;
        else
            return false;
    }

    if (city->trader_entry_delay > 0) {
        city->trader_entry_delay--;
        return false;
    }
    city->trader_entry_delay = city->is_sea_trade ? 30 : 4;

    if (city->is_sea_trade) {
        // generate ship
        if (city_buildings_has_working_dock() && scenario_map_has_river_entry() &&
            !city_trade_has_sea_trade_problems()) {
            map_point river_entry = scenario_map_river_entry();
            city->trader_figure_ids[index] = figure_create_trade_ship(river_entry.x(), river_entry.y(), city_id);
            return true;
        }
    } else {
        // generate caravan and donkeys
        if (!city_trade_has_land_trade_problems()) {
            // caravan head
            map_point *entry = city_map_entry_point();
            city->trader_figure_ids[index] = figure_create_trade_caravan(entry->x(), entry->y(), city_id);
            return true;
        }
    }
    return false;
}
void empire_city_open_trade(int city_id) {
    empire_city *city = &cities[city_id];
    city_finance_process_construction(city->cost_to_open);
    city->is_open = 1;
}
void empire_city_generate_trader(void) {
    for (int i = 1; i < MAX_CITIES[GAME_ENV]; i++) {
        if (!cities[i].in_use || !cities[i].is_open)
            continue;

        if (cities[i].is_sea_trade) {
            if (!city_buildings_has_working_dock()) {
                // delay of 384 = 1 year
                if (GAME_ENV == ENGINE_ENV_C3)
                    city_message_post_with_message_delay(MESSAGE_CAT_NO_WORKING_DOCK, 1, MESSAGE_NO_WORKING_DOCK, 384);
                else if (GAME_ENV == ENGINE_ENV_PHARAOH)
                    city_message_post_with_message_delay(MESSAGE_CAT_NO_WORKING_DOCK, 1, MESSAGE_NO_WORKING_DOCK_PH, 384);
                continue;
            }
            if (!scenario_map_has_river_entry())
                continue;

            city_trade_add_sea_trade_route();
        } else {
            city_trade_add_land_trade_route();
        }
        if (generate_trader(i, &cities[i]))
            break;

    }
}
void empire_city_remove_trader(int city_id, int figure_id) {
    for (int i = 0; i < 3; i++) {
        if (cities[city_id].trader_figure_ids[i] == figure_id)
            cities[city_id].trader_figure_ids[i] = 0;

    }
}

void empire_city_set_vulnerable(int city_id) {
    cities[city_id].type = EMPIRE_CITY_FOREIGN_TRADING;
}
void empire_city_set_foreign(int city_id) {
    cities[city_id].type = EMPIRE_CITY_EGYPTIAN;
}

io_buffer *iob_empire_cities = new io_buffer([](io_buffer *iob) {
//    int last_city = 0;
    for (int i = 0; i < MAX_CITIES[GAME_ENV]; i++) {
        empire_city *city = &cities[i];
        iob->bind(BIND_SIGNATURE_UINT8, &city->in_use);
        iob->bind____skip(1);
        iob->bind(BIND_SIGNATURE_UINT8, &city->type);
        iob->bind(BIND_SIGNATURE_UINT8, &city->name_id);
        iob->bind(BIND_SIGNATURE_UINT8, &city->route_id);
        iob->bind(BIND_SIGNATURE_UINT8, &city->is_open);
        for (int r = 0; r < RESOURCES_MAX; r++)
            iob->bind(BIND_SIGNATURE_UINT8, &city->buys_resource[r]);
        for (int r = 0; r < RESOURCES_MAX; r++) {
            iob->bind(BIND_SIGNATURE_UINT8, &city->sells_resource[r]);
        }
        iob->bind(BIND_SIGNATURE_INT16, &city->cost_to_open);
        iob->bind(BIND_SIGNATURE_INT16, &city->ph_unk01);
        iob->bind(BIND_SIGNATURE_INT16, &city->trader_entry_delay);
        iob->bind(BIND_SIGNATURE_INT16, &city->ph_unk02);
        iob->bind(BIND_SIGNATURE_INT16, &city->empire_object_id);
        iob->bind(BIND_SIGNATURE_UINT8, &city->is_sea_trade);
        iob->bind____skip(1);
        for (int f = 0; f < 3; f++)
            iob->bind(BIND_SIGNATURE_INT16, &city->trader_figure_ids[f]);
        iob->bind____skip(10);
//        if (city->in_use && last_city == 0) {
////            int a = 24;
//            for (int i = 0; i < RESOURCE_MAX_FOOD; i++) {
//                int can_do_food_x = empire_can_produce_resource(i);
//                if (can_do_food_x) {
//                    city_data.resource.food_types_allowed[food_index] = i;
//                    food_index++;
//                }
//            }
//        }
    }
    int food_index = 0;
    for (int resource = 1; resource < RESOURCES_FOODS_MAX; resource++) {
        int can_do_food_x = empire_can_produce_resource(resource, true);
        if (can_do_food_x) {
            set_allowed_food(food_index, resource);
            food_index++;
        }
    }
});
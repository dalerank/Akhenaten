#include "empire_map.h"

#include "building/count.h"
#include "city/constants.h"
#include "city/population.h"
#include "city/resource.h"
#include "city/trade.h"
#include "core/calc.h"
#include "core/log.h"
#include "empire/empire.h"
#include "empire/empire_object.h"
#include "empire/trade_route.h"
#include "io/io.h"
#include "type.h"

#include "io/io_buffer.h"
#include <string.h>

empire_map_t g_empire_map;

const static vec2i EMPIRE_SIZE{1200, 1600};

enum E_EMPIRE {
    //    EMPIRE_WIDTH = 2000,
    //    EMPIRE_HEIGHT = 1000,
    EMPIRE_HEADER_SIZE = 1280,
    //    EMPIRE_DATA_SIZE = 12800
};

const static int EMPIRE_DATA_SIZE[2] = {12800, 15200};
const char SCENARIO_FILE[2][2][100] = {{"c32.emp", "c3.emp"}, {"", "Pharaoh2.emp"}};

void empire_map_t::check_scroll_boundaries() {
    int max_x = EMPIRE_SIZE.x - viewport_width;
    int max_y = EMPIRE_SIZE.y - viewport_height + 20;

    scroll_x = calc_bound(scroll_x, 0, max_x);
    scroll_y = calc_bound(scroll_y, 0, max_y);
}

void empire_load_editor(int empire_id, int viewport_width, int viewport_height) {
    //    empire_load_external_c3(1, empire_id);
    //    empire_object_init_cities();
    //
    //    const empire_object *our_city = empire_object_get_our_city();
    //
    //    data.viewport_width = viewport_width;
    //    data.viewport_height = viewport_height;
    //    if (our_city) {
    //        data.scroll_x = our_city->x - data.viewport_width / 2;
    //        data.scroll_y = our_city->y - data.viewport_height / 2;
    //    } else {
    //        data.scroll_x = data.initial_scroll_x;
    //        data.scroll_y = data.initial_scroll_y;
    //    }
    //    check_scroll_boundaries();
}
void empire_map_t::init_scenario() {
    scroll_x = initial_scroll_x;
    scroll_y = initial_scroll_y;
    viewport_width = EMPIRE_SIZE.x;
    viewport_height = EMPIRE_SIZE.y;

    empire_object_init_cities();
}

void empire_map_t::set_viewport(vec2i size) {
    viewport_width = size.x;
    viewport_height = size.y;
    check_scroll_boundaries();
}

vec2i empire_map_t::get_scroll() {
    return {scroll_x, scroll_y};
}

vec2i empire_map_t::adjust_scroll(vec2i pos) {
    return {pos.x - scroll_x, pos.y - scroll_y};
}

void empire_map_t::set_scroll(vec2i pos) {
    scroll_x = pos.x;
    scroll_y = pos.y;
    check_scroll_boundaries();
}

void empire_map_t::scroll_map(vec2i pos) {
    scroll_x += pos.x;
    scroll_y += pos.y;
    check_scroll_boundaries();
}

int empire_map_t::selected_object() {
    return selected_obj;
}

void empire_map_t::clear_selected_object() {
    selected_obj = 0;
}

void empire_map_t::select_object(vec2i pos) {
    int map_x = pos.x + scroll_x;
    int map_y = pos.y + scroll_y;

    selected_obj = empire_object_get_closest(vec2i(map_x, map_y));
}

bool empire_can_export_resource_to_city(int city_id, e_resource resource) {
    empire_city* city = g_empire.city(city_id);
    if (city_id && trade_route_limit_reached(city->route_id, resource)) {
        // quota reached
        return false;
    }
    if (city_resource_count(resource) <= city_resource_trading_amount(resource)) {
        // stocks too low
        return false;
    }
    if (city_id == 0 || city->buys_resource[resource]) {
        int status = city_resource_trade_status(resource);
        switch (status) {
        case TRADE_STATUS_EXPORT: return true;
        case TRADE_STATUS_EXPORT_SURPLUS: return city_resource_trade_surplus(resource);
        }
    }
    
    return false;
}

static int get_max_food_stock_for_population(e_resource resource) {
    switch (resource) {
    case RESOURCE_GRAIN:
    case RESOURCE_MEAT:
    case RESOURCE_LETTUCE:
    case RESOURCE_GAMEMEAT:
    case RESOURCE_POTTERY:
    case RESOURCE_LUXURY_GOODS:
    case RESOURCE_OIL:
    case RESOURCE_BEER:
        return std::max(100, (city_population() / 100) * 100);
    }

    return 0;
}

static int get_max_raw_stock_for_population(e_resource resource) {
    int finished_good = RESOURCE_NONE;
    switch (resource) {
    case RESOURCE_CLAY: finished_good = RESOURCE_POTTERY; break;
    case RESOURCE_TIMBER: finished_good = RESOURCE_LUXURY_GOODS; break;
    case RESOURCE_STRAW: finished_good = RESOURCE_OIL; break;
    case RESOURCE_BARLEY: finished_good = RESOURCE_BEER; break;
    case RESOURCE_COPPER: finished_good = RESOURCE_WEAPONS; break;
    }

    int max_in_stock = 0;
    if (finished_good) {
        max_in_stock = 200 + 200 * building_count_industry_active(resource);
    }

    return max_in_stock;
}

int empire_can_import_resource_from_city(int city_id, e_resource resource) {
    empire_city* city = g_empire.city(city_id);
    if (!city->sells_resource[resource])
        return 0;

    int status = city_resource_trade_status(resource);
    switch (status) {
    case TRADE_STATUS_IMPORT:
    case TRADE_STATUS_IMPORT_AS_NEEDED:
        ;
        break;

    default:
        return 0;
    }

    if (trade_route_limit_reached(city->route_id, resource)) {
        return 0;
    }

    int in_stock = city_resource_count(resource);
    int max_in_stock = 0;

    if (status == TRADE_STATUS_IMPORT_AS_NEEDED) {
        switch (resource) {
        // food and finished materials
        case RESOURCE_GRAIN:
        case RESOURCE_MEAT:
        case RESOURCE_LETTUCE:
        case RESOURCE_GAMEMEAT:
        case RESOURCE_OIL:
        case RESOURCE_BEER:
            max_in_stock = get_max_food_stock_for_population(resource);
            break;

        case RESOURCE_MARBLE:
        case RESOURCE_WEAPONS:
            max_in_stock = 10;
            break;

        case RESOURCE_CLAY:
        case RESOURCE_TIMBER:
        case RESOURCE_STRAW: 
        case RESOURCE_BARLEY:
        case RESOURCE_COPPER:
            max_in_stock = get_max_raw_stock_for_population(resource);
            break;

        case RESOURCE_BRICKS:
            max_in_stock = std::max(100, (city_population() / 100) * 100);
            break;

        case RESOURCE_POTTERY:
        case RESOURCE_LUXURY_GOODS:
            max_in_stock = std::max(100, (city_population() / 100) * 50);
            break;

        case RESOURCE_PAPYRUS:
            max_in_stock = std::max(100, (building_count_active(BUILDING_SCRIBAL_SCHOOL) + building_count_active(BUILDING_LIBRARY)) * 100);
            break;

        default:
            max_in_stock = 100;
            break;
        }
    } else {
        max_in_stock = city_resource_trading_amount(resource);
    }

    return in_stock < max_in_stock ? 1 : 0;
}

io_buffer* iob_empire_map_params = new io_buffer([](io_buffer* iob, size_t version) {
    auto& data = g_empire_map;
    iob->bind(BIND_SIGNATURE_INT32, &data.scroll_x);
    iob->bind(BIND_SIGNATURE_INT32, &data.scroll_y);
    iob->bind(BIND_SIGNATURE_INT32, &data.selected_obj);
});
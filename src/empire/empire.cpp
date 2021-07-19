#include "empire.h"

#include "building/count.h"
#include "city/constants.h"
#include "city/population.h"
#include "city/resource.h"
#include "core/calc.h"
#include "core/log.h"
#include "core/io.h"
#include "empire/city.h"
#include "empire/object.h"
#include "empire/trade_route.h"

#include <string.h>

const static int EMPIRE_WIDTH[2] = {
        2000,
        1200,
};
const static int EMPIRE_HEIGHT[2] = {
        1000,
        1600,
};

enum {
//    EMPIRE_WIDTH = 2000,
//    EMPIRE_HEIGHT = 1000,
    EMPIRE_HEADER_SIZE = 1280,
//    EMPIRE_DATA_SIZE = 12800
};

const static int EMPIRE_DATA_SIZE[2] = {
        12800,
        15200
};

static struct {
    int initial_scroll_x;
    int initial_scroll_y;
    int scroll_x;
    int scroll_y;
    int selected_object;
    int viewport_width;
    int viewport_height;
} data;

const char SCENARIO_FILE[2][2][100] = {
        {"c32.emp", "c3.emp"},
        {"", "Pharaoh2.emp"}
};

void empire_load_external_c3(int is_custom_scenario, int empire_id) {
    buffer *buf = new buffer(EMPIRE_DATA_SIZE[GAME_ENV]);
    const char *filename = is_custom_scenario ? SCENARIO_FILE[GAME_ENV][0] : SCENARIO_FILE[GAME_ENV][1];

    if (is_custom_scenario && GAME_ENV == ENGINE_ENV_PHARAOH) // in Pharaoh, custom map data is saved internally
        return;

    // read header with scroll positions
    if (!io_read_file_part_into_buffer(filename, NOT_LOCALIZED, buf, 4, 32 * empire_id)) {
        buf->write_u32(0);
        buf->reset_offset();
    }
    data.initial_scroll_x = buf->read_i16();
    data.initial_scroll_y = buf->read_i16();

    // read data section with objects
    int offset = EMPIRE_HEADER_SIZE + EMPIRE_DATA_SIZE[GAME_ENV] * empire_id;
    if (io_read_file_part_into_buffer(filename, NOT_LOCALIZED, buf, EMPIRE_DATA_SIZE[GAME_ENV], offset) != EMPIRE_DATA_SIZE[GAME_ENV]) {
        // load empty empire when loading fails
        log_error("Unable to load empire data from file", filename, 0);
        buf->fill(0);
    }
    empire_object_load(buf, is_custom_scenario);
}
void empire_load_internal_ph(buffer *buf) {
    if (buf->size() == 15200)
//        return;
        empire_object_load(buf, 0);
    else
        empire_object_load(buf, 1);
}

static void check_scroll_boundaries(void) {
    int max_x = EMPIRE_WIDTH[GAME_ENV] - data.viewport_width;
    int max_y = EMPIRE_HEIGHT[GAME_ENV] - data.viewport_height + 20;

    data.scroll_x = calc_bound(data.scroll_x, 0, max_x);
    data.scroll_y = calc_bound(data.scroll_y, 0, max_y);
}

void empire_load_editor(int empire_id, int viewport_width, int viewport_height) {
    empire_load_external_c3(1, empire_id);
    empire_object_init_cities();

    const empire_object *our_city = empire_object_get_our_city();

    data.viewport_width = viewport_width;
    data.viewport_height = viewport_height;
    if (our_city) {
        data.scroll_x = our_city->x - data.viewport_width / 2;
        data.scroll_y = our_city->y - data.viewport_height / 2;
    } else {
        data.scroll_x = data.initial_scroll_x;
        data.scroll_y = data.initial_scroll_y;
    }
    check_scroll_boundaries();
}
void empire_init_scenario(void) {
    data.scroll_x = data.initial_scroll_x;
    data.scroll_y = data.initial_scroll_y;
    data.viewport_width = EMPIRE_WIDTH[GAME_ENV];
    data.viewport_height = EMPIRE_HEIGHT[GAME_ENV];

    empire_object_init_cities();
}

void empire_set_viewport(int width, int height) {
    data.viewport_width = width;
    data.viewport_height = height;
    check_scroll_boundaries();
}
void empire_get_scroll(int *x_scroll, int *y_scroll) {
    *x_scroll = data.scroll_x;
    *y_scroll = data.scroll_y;
}
void empire_adjust_scroll(int *x_offset, int *y_offset) {
    *x_offset = *x_offset - data.scroll_x;
    *y_offset = *y_offset - data.scroll_y;
}
void empire_set_scroll(int x, int y) {
    data.scroll_x = x;
    data.scroll_y = y;
    check_scroll_boundaries();
}
void empire_scroll_map(int x, int y) {
    data.scroll_x += x;
    data.scroll_y += y;
    check_scroll_boundaries();
}

int empire_selected_object(void) {
    return data.selected_object;
}
void empire_clear_selected_object(void) {
    data.selected_object = 0;
}
void empire_select_object(int x, int y) {
    int map_x = x + data.scroll_x;
    int map_y = y + data.scroll_y;

    data.selected_object = empire_object_get_closest(map_x, map_y);
}

static int get_max_stock_for_population(void) {
    int population = city_population();
    if (population < 2000)
        return 10;
    else if (population < 4000)
        return 20;
    else if (population < 6000)
        return 30;
    else {
        return 40;
    }
}

int empire_can_export_resource_to_city(int city_id, int resource) {
    empire_city *city = empire_city_get(city_id);
    if (city_id && trade_route_limit_reached(city->route_id, resource)) {
        // quota reached
        return 0;
    }
    if (city_resource_count(resource) <= city_resource_export_over(resource)) {
        // stocks too low
        return 0;
    }
    if (city_id == 0 || city->buys_resource[resource])
        return city_int(resource) == TRADE_STATUS_EXPORT;
    else {
        return 0;
    }
}
int empire_can_import_resource_from_city(int city_id, int resource) {
    empire_city *city = empire_city_get(city_id);
    if (!city->sells_resource[resource])
        return 0;

    if (city_int(resource) != TRADE_STATUS_IMPORT)
        return 0;

    if (trade_route_limit_reached(city->route_id, resource))
        return 0;


    int in_stock = city_resource_count(resource);
    int max_in_stock = 0;
    int finished_good = RESOURCE_NONE;
    /*switch (resource) {
        // food and finished materials
        case RESOURCE_WHEAT:
        case RESOURCE_VEGETABLES:
        case RESOURCE_FRUIT:
        case RESOURCE_MEAT:
        case RESOURCE_POTTERY:
        case RESOURCE_FURNITURE:
        case RESOURCE_OIL:
        case RESOURCE_WINE:
            max_in_stock = get_max_stock_for_population();
            break;

        case RESOURCE_MARBLE:
        case RESOURCE_WEAPONS:
            max_in_stock = 10;
            break;

        case RESOURCE_CLAY:
            finished_good = RESOURCE_POTTERY;
            break;
        case RESOURCE_TIMBER:
            finished_good = RESOURCE_FURNITURE;
            break;
        case RESOURCE_OLIVES:
            finished_good = RESOURCE_OIL;
            break;
        case RESOURCE_VINES:
            finished_good = RESOURCE_WINE;
            break;
        case RESOURCE_IRON:
            finished_good = RESOURCE_WEAPONS;
            break;
    }
    if (finished_good)
        max_in_stock = 2 + 2 * building_count_industry_active(finished_good);
*/
    max_in_stock = city_resource_export_over(resource);
    return in_stock < max_in_stock ? 1 : 0;
}

void empire_save_state(buffer *buf) {
    buf->write_i32(data.scroll_x);
    buf->write_i32(data.scroll_y);
    buf->write_i32(data.selected_object);
}
void empire_load_state(buffer *buf) {
    data.scroll_x = buf->read_i32();
    data.scroll_y = buf->read_i32();
    data.selected_object = buf->read_i32();
}

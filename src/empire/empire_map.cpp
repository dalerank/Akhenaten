#include "empire_map.h"

#include "city/constants.h"
#include "city/city_resource.h"
#include "core/calc.h"
#include "core/log.h"
#include "empire/empire.h"
#include "empire/empire_object.h"
#include "empire/empire_traders.h"
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

    selected_obj = g_empire.get_closest_object(vec2i(map_x, map_y));
}

io_buffer* iob_empire_map_params = new io_buffer([](io_buffer* iob, size_t version) {
    auto& data = g_empire_map;
    iob->bind(BIND_SIGNATURE_INT32, &data.scroll_x);
    iob->bind(BIND_SIGNATURE_INT32, &data.scroll_y);
    iob->bind(BIND_SIGNATURE_INT32, &data.selected_obj);
});
#include "empire_city.h"
#include "empire/empire.h"
#include "empire_object.h"
#include "game/game_config.h"
#include "io/gamefiles/lang.h"
#include "js/js_game.h"

const e_empire_city_tokens_t e_empire_city_tokens;

empire_city_options_t ANK_VARIABLE(empire_city_options);

void empire_city::remove_trader(int figure_id) {
    for (int i = 0; i < 3; i++) {
        if (trader_figure_ids[i] == figure_id)
            trader_figure_ids[i] = 0;
    }
}

bool empire_city::can_trade() const {
    // Cannot trade if city is under siege
    if (months_under_siege > 0) {
        return false;
    }
    
    switch (type) {
        case EMPIRE_CITY_PHARAOH_TRADING:
        case EMPIRE_CITY_EGYPTIAN_TRADING:
        case EMPIRE_CITY_FOREIGN_TRADING:
        return true;
    }

    return false;
}

trade_route &empire_city::get_route() {
    return g_empire.get_route(route_id);
}

const trade_route &empire_city::get_route() const {
    return g_empire.get_route(route_id);
}

const empire_object *empire_city::get_empire_object() const {
    return g_empire.get_object(empire_object_id);
}

const full_empire_object *empire_city::get_full_empire_object() const {
    return g_empire.get_full_object(empire_object_id);
}

int empire_city::get_free_slot(int max_traders) const {
    for (int i = 0; i < max_traders; i++) {
        if (!trader_figure_ids[i]) {
            return i;
        }
    }
    return -1;
}

bstring32 empire_city::get_display_name(int nid) {
    int text_group = !!game_features::gameui_empire_city_old_names 
                            ? empire_city_options.text_group_old_names 
                            : empire_city_options.text_group_new_names;

    return lang_get_string(text_group, nid);
}

const trade_route& empire_city_handle::get_route() const {
    auto city = g_empire.city(handle);
    return g_empire.get_route(city->route_id);
}

trade_route& empire_city_handle::get_route() {
    auto city = g_empire.city(handle);
    return g_empire.get_route(city->route_id);
}

bool empire_city_handle::buys_resource(e_resource r) const {
    return ref().buys_resource[r];
}

bool empire_city_handle::sells_resource(e_resource r) const {
    return ref().sells_resource[r];
}

void empire_city_handle::remove_trader(figure_id fid) {
    ref().remove_trader(fid);
}

void empire_city_handle::set_under_siege(uint8_t months) {
    ref().set_under_siege(months);
}

xstring empire_city_handle::name() const {
    const int group = !!game_features::gameui_empire_city_old_names ? 195 : 21;
    pcstr name = (pcstr)lang_get_string(group, ref().name_id);
    return xstring(name);
}

empire_city& empire_city_handle::ref() { 
    return *g_empire.city(handle);
}

const empire_city& empire_city_handle::ref() const {
    return *g_empire.city(handle);
}

empire_city& empire_city_handle::operator*() {
    return *g_empire.city(handle);
}

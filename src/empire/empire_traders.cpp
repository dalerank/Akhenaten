#include "empire_traders.h"

#include "empire/empire.h"
#include "empire/empire_object.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/graphics.h"
#include "figuretype/figure_kingdome_trader.h"
#include "figuretype/figure_trader_ship.h"
#include "core/calc.h"
#include "game/game.h"
#include "dev/debug.h"
#include "city/city.h"
#include "core/log.h"

empire_traders_manager g_empire_traders;

declare_console_command_p(empire_traders_reset) {
    g_empire_traders.clear_all();
    logs::info("Cleared all empire traders");
};

declare_console_command_p(empire_traders_create) {
    std::string args; is >> args;
    int city_id = atoi(args.empty() ? (pcstr)"0" : args.c_str());

    const empire_city &city = *g_empire.city(city_id);
    g_empire_traders.create_trader(city.route_id, -1);
};

declare_console_command_p(empire_traders_update) {
    g_empire_traders.update();
    logs::info("Updated all empire traders");
};

void empire_trader::update() {
    if (!is_active) {
        return;
    }

    if (state == estate_trading) {
        return;
    }

    if (movement_delay > 0) {
        movement_delay--;
        return;
    }

    const map_route_object& route = empire_get_route_object(trade_route_id);
    if (!route.in_use || current_route_point >= route.num_points) {
        is_active = false;
        return;
    }

    current_route_point++;
    const auto& point = (state == estate_returning_home)
                            ? route.points[current_route_point]
                            : route.points[route.num_points - current_route_point];
    current_position = point.p;

    if (is_at_destination()) {
        complete_trade();
        return;
    }

    movement_delay = route.route_type == 1 ? 2 : 4;
}

bool empire_trader::is_at_destination() const {
    if (destination_city_id < 0) {
        return false;
    }

    const auto base_city_id = g_empire.get_city_for_trade_route(trade_route_id);
    const empire_city* city = g_empire.city((state == estate_returning_home) ? base_city_id : destination_city_id);
    if (!city || !city->in_use) {
        return false;
    }

    const empire_object* obj = city->get_empire_object();
    if (!obj) {
        return false;
    }

    int distance = calc_maximum_distance(current_position, obj->pos);
    return distance <= 40; 
}

void empire_trader::complete_trade() {
    if (state == estate_moving_to_destination) {
        state = estate_trading;
        current_route_point = 0;
        movement_delay = 10;
        const auto base_city_id = g_empire.get_city_for_trade_route(trade_route_id);
        if (is_ship) {
            events::emit(event_trade_ship_arrival{ base_city_id, id, SOURCE_LOCATION });
        } else {
            events::emit(event_trade_caravan_arrival{ base_city_id, id, SOURCE_LOCATION });
        }
        return;
    } 

    if (state == estate_returning_home) {
        is_active = false;
    }
}

void empire_traders_manager::init() {
    clear_all();
}

void empire_traders_manager::update() {
    for (auto &trader : traders) {
        trader.update();
    }
}

void empire_traders_manager::create_trader(int trade_route_id, int destination_city_id) {
    int traders_on_route = 0;
    for (auto &trader : traders) {
        if (trader.is_active && trader.trade_route_id == trade_route_id) {
            traders_on_route++;
        }
    }
    
    if (traders_on_route >= 2) {
        return;
    }

    empire_trader* trader = get_free_trader();
    if (!trader) {
        return;
    }

    if (destination_city_id == -1) {
        destination_city_id = g_city.ourcity().name_id;
    }

    const map_route_object& route = empire_get_route_object(trade_route_id);
    trader->trade_route_id = trade_route_id;
    trader->destination_city_id = destination_city_id;
    trader->current_route_point = 0;
    trader->movement_delay = 0;
    trader->is_active = true;
    trader->state = empire_trader::estate_moving_to_destination;
    trader->is_ship = (route.route_type == 2);

    if (route.in_use && route.num_points > 0) {
        const auto &point = route.points[route.num_points - 1];
        trader->current_position = point.p;
    }
}

void empire_traders_manager::remove_trader(int trader_id) {
    for (auto& trader: traders) {
        if (trader.id == trader_id) {
            trader.is_active = false;
            break;
        }
    }
}

void empire_traders_manager::clear_all() {
    for (int i = 0; i < traders.size(); ++i) {
        traders[i].id = i;
        traders[i].is_active = false;
    }
}

empire_trader* empire_traders_manager::get_free_trader() {
    for (auto &trader : traders) {
        if (!trader.is_active) {
            return &trader;
        }
    }
    return nullptr;
}

vec2i empire_traders_manager::get_position_on_route(int route_id, int point_index) {
    const map_route_object& route = empire_get_route_object(route_id);
    if (route.in_use && point_index < route.num_points) {
        return route.points[point_index].p;
    }
    return vec2i{0, 0};
}

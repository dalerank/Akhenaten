#include "empire_city.h"
#include "empire/empire.h"

const token_holder<e_empire_city, EMPIRE_CITY_OURS, EMPIRE_CITY_COUNT> e_empire_city_tokens;

void empire_city::remove_trader(int figure_id) {
    for (int i = 0; i < 3; i++) {
        if (trader_figure_ids[i] == figure_id)
            trader_figure_ids[i] = 0;
    }
}

bool empire_city::can_trade() const {
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

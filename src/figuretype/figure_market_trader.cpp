#include "figure_market_trader.h"

#include "building/building_bazaar.h"
#include "building/building_house.h"
#include "city/city_recorded_paths.h"
#include "figuretype/figure_market_buyer.h"
#include "figure/service.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_market_trader);

void figure_market_trader::figure_roaming_action() {
    switch (action_state()) {
    case FIGURE_ACTION_149_CORPSE:
        base.figure_combat_handle_corpse();
        break;

    case ACTION_125_MARKET_TRADER_ROAMING:
        base.do_roam();
        break;

    case ACTION_126_MARKET_TRADER_RETURNING:
        if (base.do_returnhome()) {
            building *h = home();
            if (h && h->params().flags.keeps_visitor_paths) {
                building *main = h->main();
                if (main) {
                    g_recorded_paths.handoff_to_building(base, main->id);
                }
            }
        }
        break;

    default:
        advance_action(ACTION_126_ROAMER_RETURNING);
        break;
    }
}

void figure_market_trader::figure_action() {
    building_bazaar* bazaar = home()->dcast_bazaar();
    if (!bazaar) {
        return;
    }

    // force return on out of stock
    int stock = bazaar->max_food_stock() + bazaar->max_goods_stock();
    if (base.roam_length >= 96 && stock <= 0) {
        base.roam_length = base.max_roam_length;
    }
}

int figure_market_trader::provide_service() {
    int houses_serviced = provide_market_goods(home(), tile());
    figure_provide_service(tile(), &base, [] (building *b, figure *f) {
        auto house = b->dcast_house();

        if (!house) {
            return;
        }

        if (house->house_population() > 0) {
            house->runtime_data().bazaar_access = MAX_COVERAGE;
        }
    });
    return houses_serviced;
}
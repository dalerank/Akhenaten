#include "figure_market_trader.h"

#include "building/building_bazaar.h"
#include "building/building_house.h"
#include "figuretype/figure_market_buyer.h"
#include "figure/service.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_market_trader);

void figure_market_trader::figure_action() {
    if (action_state() != FIGURE_ACTION_125_ROAMING) {
        return;
    }

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

figure_sound_t figure_market_trader::get_sound_reaction(xstring key) const {
    return current_params().sounds[key];
}

sound_key figure_market_trader::phrase_key() const {
    if (base.action_state == FIGURE_ACTION_126_ROAMER_RETURNING) {
        return "goods_are_finished";
    } else {
        return "we_are_selling_goods";
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
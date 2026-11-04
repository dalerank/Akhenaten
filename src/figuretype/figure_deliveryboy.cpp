#include "figure_deliveryboy.h"

#include "game/game_config.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "city/city_figures.h"
#include "building/building_bazaar.h"
#include "figuretype/figure_cartpusher.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_delivery_boy);

bool delivery_boy_alone_return_enabled() {
    return !!game_features::gameplay_change_delivery_boy_goes_to_market_alone;
}

void delivery_boy_deposit_or_return(figure_delivery_boy &boy) {
    auto *bazaar = boy.home() ? boy.home()->dcast_bazaar() : nullptr;
    if (!bazaar) {
        boy.poof();
        return;
    }

    if (delivery_boy_alone_return_enabled()) {
        boy.base.leading_figure_id = 0;
        if (boy.do_returnhome(TERRAIN_USAGE_ROADS)) {
            bazaar->runtime_data().inventory[boy.base.collecting_item_id].value += 100;
            boy.poof();
        }
        return;
    }

    bazaar->runtime_data().inventory[boy.base.collecting_item_id].value += 100;
    boy.poof();
}

// OG carriers.c delivery_boy_find_buyer.
static figure *delivery_boy_find_buyer(figure &boy) {
    int id = boy.leading_figure_id;
    for (int i = 0; i < 8; i++) {
        figure *f = figure_get(id);
        if (!f) {
            return nullptr;
        }
        if (f->type == FIGURE_MARKET_BUYER) {
            return f;
        }
        id = f->leading_figure_id;
    }
    return nullptr;
}

void figure_delivery_boy::figure_before_action() {
    if (is_follower_runaway()) {
        return;
    }

    // Alone-return clears leading_id while walking home — do not treat as runaway.
    if (base.leading_figure_id <= 0) {
        if (!delivery_boy_alone_return_enabled()) {
            start_follower_runaway();
        }
        return;
    }

    figure *leader = figure_get(base.leading_figure_id);
    if (leader->action_state == FIGURE_ACTION_149_CORPSE) {
        start_follower_runaway();
    }
}

void figure_delivery_boy::figure_action() {
    if (is_follower_runaway()) {
        do_follower_runaway_tick();
        return;
    }

    // OG: is_ghost = 0 each tick, then ferry / leader may set it again.
    base.set_flag(e_figure_flag_invisible, false);
    base.cart_image_id = 0;

    if (base.leading_figure_id <= 0) {
        if (delivery_boy_alone_return_enabled()) {
            delivery_boy_deposit_or_return(*this);
        } else {
            start_follower_runaway();
        }
        return;
    }

    figure *leader = figure_get(base.leading_figure_id);
    if (leader->action_state == FIGURE_ACTION_149_CORPSE
        || leader->action_state == FIGURE_ACTION_132_FOLLOWER_RUNAWAY) {
        start_follower_runaway();
        return;
    }

    figure *buyer = delivery_boy_find_buyer(base);
    const int buyer_state = buyer ? buyer->action_state : -1;
    short wait_act = ACTION_7_CARTPUSHER_WAIT_FOR_FERRY;
    short ride_act = ACTION_6_CARTPUSHER_ON_FERRY;
    if (buyer) {
        if (figure_impl *bimpl = buyer->dcast()) {
            wait_act = bimpl->ferry_wait_action();
            ride_act = bimpl->ferry_ride_action();
        }
    }

    if (leader->state == FIGURE_STATE_ALIVE) {
        if (leader->type == FIGURE_MARKET_BUYER || leader->type == FIGURE_DELIVERY_BOY) {
            // OG: do not follow while buyer waits for / rides a ferry.
            if (buyer_state != wait_act && buyer_state != ride_act) {
                follow_ticks(1);
            }
        } else {
            poof();
            return;
        }
    } else {
        // Leader finished route (market arrival) — deposit goods, not runaway.
        delivery_boy_deposit_or_return(*this);
        return;
    }

    // OG: ghost while buyer is aboard; freeze walk frame while waiting at landing.
    if (buyer_state == ride_act) {
        base.set_flag(e_figure_flag_invisible, true);
        base.main_image_id = 0;
        return;
    }
    if (buyer_state == wait_act) {
        base.animctx.frame = 0;
    }
    // OG: inherit leader is_ghost (boarding chain / ferry_remove_followers).
    if (!leader->is_visible()) {
        base.set_flag(e_figure_flag_invisible, true);
        base.main_image_id = 0;
    }
}

void figure_delivery_boy::update_animation() {
    if (!base.is_visible()) {
        return;
    }
    figure_impl::update_animation();
}

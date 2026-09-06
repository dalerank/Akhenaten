#include "figure_deliveryboy.h"

#include "game/game_config.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "city/city_figures.h"
#include "building/building_bazaar.h"
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

    if (leader->state == FIGURE_STATE_ALIVE) {
        if (leader->type == FIGURE_MARKET_BUYER || leader->type == FIGURE_DELIVERY_BOY) {
            follow_ticks(1);
        } else {
            poof();
        }
        return;
    }

    // Leader finished route (market arrival) — deposit goods, not runaway.
    delivery_boy_deposit_or_return(*this);
}

void figure_delivery_boy::update_animation() {
    figure_impl::update_animation();
}

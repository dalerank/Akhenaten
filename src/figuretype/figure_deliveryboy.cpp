#include "figure_deliveryboy.h"

#include "config/config.h"
#include "figure/image.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "city/city_figures.h"

figures::model_t<figure_delivery_boy> delivery_boy_m;

void figure_delivery_boy::figure_before_action() {
    figure* leader = figure_get(base.leading_figure_id);
    if (base.leading_figure_id <= 0) {
        //poof();
    }

    if (leader->action_state == FIGURE_ACTION_149_CORPSE) {  
        poof(); // TODO make runaway from this tile
    }
}

void figure_delivery_boy::figure_action() {
    figure* leader = figure_get(base.leading_figure_id);
    if (leader->state == FIGURE_STATE_ALIVE) {
        if (leader->type == FIGURE_MARKET_BUYER || leader->type == FIGURE_DELIVERY_BOY) {
            follow_ticks(1);
        } else {
            poof();
        }
    } else { // leader arrived at market, drop resource at market
        if (config_get(CONFIG_GP_CH_DELIVERY_BOY_GOES_TO_MARKET_ALONE)) {
            base.leading_figure_id = 0;
            if (do_returnhome(TERRAIN_USAGE_ROADS)) {
                home()->data.market.inventory[base.collecting_item_id] += 100;
                poof();
            }
        } else {
            home()->data.market.inventory[base.collecting_item_id] += 100;
            poof();
        }
    }
}

sound_key figure_delivery_boy::phrase_key() const {
    svector<sound_key, 10> keys{"those_baskets_too_heavy",
                                "i_works_all_day",
                                "upon_ill_be_market_owner"};

    int index = rand() % keys.size();
    return keys[index];
}

figure_sound_t figure_delivery_boy::get_sound_reaction(xstring key) const {
    return delivery_boy_m.sounds[key];
}

const animations_t &figure_delivery_boy::anim() const {
    return delivery_boy_m.anim;
}

void figure_delivery_boy::update_animation() {
    figure_impl::update_animation();
}

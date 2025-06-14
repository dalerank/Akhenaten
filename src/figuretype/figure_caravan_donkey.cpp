#include "figure_caravan_donkey.h"

#include "figure/trader.h"

#include "building/building_storage_yard.h"
#include "building/building_storage_room.h"

#include "empire/empire.h"
#include "empire/empire_map.h"
#include "empire/trade_prices.h"

#include "city/trade.h"
#include "city/city_resource.h"
#include "city/city_finance.h"
#include "figure/image.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "game/game.h"
#include "graphics/elements/lang_text.h"
#include "window/window_figure_info.h"
#include "core/profiler.h"

figures::model_t<figure_caravan_donkey> caravan_donkey_m;

struct figure_caravan_donkey_info_window : public figure_info_window {
    virtual void window_info_background(object_info &c) override;
    virtual bool check(object_info &c) override {
        return !!c.figure_get<figure_caravan_donkey>();
    }
};

figure_caravan_donkey_info_window figure_caravan_donkey_infow;

const empire_city *figure_caravan_donkey::get_empire_city() const {
    const empire_city *city = g_empire.city(base.empire_city_id);
    return city;
}

void figure_caravan_donkey::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/CaravanDonkey");
    figure* leader = figure_get(base.leading_figure_id);
    if (leader->action_state == FIGURE_ACTION_149_CORPSE)
        poof();
    else if (leader->state != FIGURE_STATE_ALIVE)
        poof();
    else if (leader->type != FIGURE_TRADE_CARAVAN && leader->type != FIGURE_TRADE_CARAVAN_DONKEY)
        poof();
    else
        follow_ticks(1);

    int dir = figure_image_normalize_direction(direction() < 8 ? direction() : base.previous_tile_direction);
    int image_id = anim(animkeys().walk).first_img();
    base.sprite_image_id = image_id + dir + 8 * base.anim.frame;
}

void figure_caravan_donkey::figure_before_action() {
    figure* leader = figure_get(base.leading_figure_id);
    if (base.leading_figure_id <= 0) {
        //poof();
    }

    if (leader->action_state == FIGURE_ACTION_149_CORPSE) {  
        poof(); // TODO make runaway from this tile
    }
}

void figure_caravan_donkey::update_animation() {
    /*nothing*/
}

figure* figure_caravan_donkey::get_head_of_caravan() {
    figure* f = &base;
    while (f->type == FIGURE_TRADE_CARAVAN_DONKEY) {
        f = figure_get(f->leading_figure_id);
    }
    return f;
}

void figure_caravan_donkey_info_window::window_info_background(object_info &c) {
    common_info_window::window_info_background(c);

    figure_caravan_donkey *donkey = c.figure_get<figure_caravan_donkey>();
    figure* f = donkey->get_head_of_caravan();

    const empire_city* city = donkey->get_empire_city();
    ui["name"].text_var("%s %s", ui::str(64, f->type), ui::str(21, city->name_id));
    ui["type"].text_var("%s %s %u", ui::str(129, 1), ui::str(8, 10), 800);

    int trader_id = f->trader_id;
    
    int text_id;
    switch (f->action_state) {
    case FIGURE_ACTION_101_TRADE_CARAVAN_ARRIVING: text_id = 12; break;
    case FIGURE_ACTION_102_TRADE_CARAVAN_TRADING: text_id = 10; break;
    case FIGURE_ACTION_103_TRADE_CARAVAN_LEAVING: text_id = trader_has_traded(trader_id) ? 11 : 13; break;
    default: text_id = 11; break;
    }

    ui["phrase"] = ui::str(129, text_id);

    if (trader_has_traded(trader_id)) {
        // bought
        bstring256 bought_items = ui::str(129, 4);
        for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r) {
            if (trader_bought_resources(trader_id, r)) {
                int amount = trader_bought_resources(trader_id, r);
                int image_id = image_id_resource_icon(r);

                bought_items.append("%d @Y%u& ", amount, image_id);
            }
        }
        ui["bought_items"] = bought_items;

        // sold
        bstring256 sold_items = ui::str(129, 5);
        for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r) {
            if (trader_sold_resources(trader_id, r)) {
                int amount = trader_sold_resources(trader_id, r);
                int image_id = image_id_resource_icon(r);

                sold_items.append("%d @Y%u& ", amount, image_id);
            }
        }
        ui["sold_items"] = sold_items;

        return;
    }
    
    // nothing sold/bought (yet)
    // buying
    bstring256 buing_items = ui::str(129, 2);
    for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r) {
        if (city->buys_resource[r]) {
            int image_id = image_id_resource_icon(r);
            buing_items.append("@Y%u& ", image_id);
        }
    }
    ui["bought_items"] = buing_items;

    // selling
    bstring256 selling_items = ui::str(129, 3);
    for (int r = RESOURCE_MIN; r < RESOURCES_MAX; r++) {
        if (city->sells_resource[r]) {
            int image_id = image_id_resource_icon(r);
            buing_items.append("@Y%u& ", image_id);
        }
    }
    ui["sold_items"] = selling_items;
}

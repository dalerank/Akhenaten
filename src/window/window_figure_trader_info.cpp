#include "window/window_figure_info.h"

#include "figure/trader.h"
#include "empire/empire.h"
#include "window/building/figures.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "figuretype/figure_kingdome_trader.h"
#include "figuretype/figure_trader_ship.h"
#include "figuretype/figure_caravan_donkey.h"
#include "grid/figure.h"
#include "game/game.h"
#include "js/js_game.h"

struct figure_trader_info_window : public figure_info_window_t<figure_trader_info_window> {
    virtual void init(object_info &c) override;
};

figure_trader_info_window figure_trader_infow;

void figure_trader_info_window::init(object_info &c) {
    figure_info_window::init(c);

    figure *f = c.figure_get();

    empire_trader_handle trader;
    empire_city_handle city;

    if (auto donkey = f->dcast<figure_caravan_donkey>(); donkey != nullptr) {
        auto head = donkey->head_of_caravan()->dcast<figure_trade_caravan>();
        trader = head ? head->empire_trader() : empire_trader_handle{};
        city =  head ? head->empire_city() : empire_city_handle{};
    } else if(auto caravan = f->dcast<figure_trade_caravan>(); caravan != nullptr) {
        trader = caravan->empire_trader();
        city = caravan->empire_city();
    } else if(auto ship = f->dcast<figure_trade_ship>(); ship != nullptr) {
        trader = ship->empire_trader();
        city = ship->empire_city();
    }

    assert(trader.valid());
    if (trader.has_traded()) {
        ui["buy"] = "#trader_bought";
        ui["sell"] = "#trader_sold";

        // bought
        bstring128 bought_items;
        for (e_resource r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
            int amount = trader.bought_resources(r);
            if (amount > 0) {
                int image_id = image_id_resource_icon(r);
                bought_items.append_fmt(" @I%u& %u", image_id, amount);
            }
        }
        ui["buy_text"] = bought_items;

        // sold
        bstring128 sold_items;
        for (e_resource r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
            int amount = trader.sold_resources(r);
            if (amount > 0) {
                int image_id = image_id_resource_icon(r);
                sold_items.append_fmt(" @I%u& %u", image_id, amount);
            }
        }
        ui["sell_text"] = sold_items;
    } else { // nothing sold/bought (yet)
        // buying
        ui["buy"] = "#trader_buys";
        ui["sell"] = "#trader_sells";

        bstring128 buy_items;
        for (e_resource r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
            if (city.buys_resource(r)) {
                int image_id = image_id_resource_icon(r);
                buy_items.append_fmt("@I%u& ", image_id);
            }
        }
        ui["buy_text"] = buy_items;

        // selling
        bstring128 sell_items;
        for (e_resource r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
            if (city.sells_resource(r)) {
                int image_id = image_id_resource_icon(r);
                sell_items.append_fmt("@I%u& ", image_id);
            }
        }
        ui["sell_text"] = sell_items;
    }
}

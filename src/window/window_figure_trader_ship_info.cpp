#include "window/window_figure_info.h"

#include "figure/trader.h"
#include "empire/empire.h"
#include "window/building/figures.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "grid/figure.h"
#include "game/game.h"
#include "js/js_game.h"

struct figure_trader_ship_info_window : public figure_info_window_t<figure_trader_ship_info_window> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return !!c.figure_get<figure_trade_ship>();
    }
};

figure_trader_ship_info_window figure_trader_ship_infow;

void figure_trader_ship_info_window::init(object_info &c) {
    figure_info_window::init(c);

    figure* f = c.figure_get();
    empire_city* city = g_empire.city(f->empire_city_id);

    int trader_id = f->trader_id;
    if (trader_has_traded(trader_id)) {
        // bought
        int index = 0;
        ui["buy"] = ui::str(129, 4);
        ui["sell"] = ui::str(129, 5);
        for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r, ++index) {
            if (trader_bought_resources(trader_id, r)) {
                bstring64 boughtid; boughtid.printf("buy_%d", index);
                ui[boughtid] = bstring32(trader_bought_resources(trader_id, r));

                bstring64 imgid; imgid.printf("buy_img_%d", index);
                ui[imgid].image(image_id_resource_icon(r));
            }
        }
        // sold
        index = 0;
        for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r) {
            if (trader_sold_resources(trader_id, r)) {
                bstring64 soldid; soldid.printf("sell_%d", index);
                ui[soldid] = bstring32(trader_sold_resources(trader_id, r));

                bstring64 imgid; imgid.printf("sell_img_%d", index);
                ui[imgid].image(image_id_resource_icon(r));
            }
        }
    } else { // nothing sold/bought (yet)
        // buying
        ui["buy"] = ui::str(129, 2);
        ui["sell"] = ui::str(129, 3);

        int index = 0;
        for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r, ++index) {
            if (city->buys_resource[r]) {
                bstring64 imgid; imgid.printf("buy_img_%d", index);
                ui[imgid] = bstring32(trader_sold_resources(trader_id, r));
            }
        }
        // selling
        for (int r = RESOURCE_MIN; r < RESOURCES_MAX; r++) {
            if (city->sells_resource[r]) {
                bstring64 imgid; imgid.printf("sell_img_%d", index);
                ui[imgid].image(image_id_resource_icon(r));
            }
        }
    }

}

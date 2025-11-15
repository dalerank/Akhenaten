#include "window/window_figure_info.h"

#include "figuretype/figure_market_buyer.h"
#include "window/building/figures.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "grid/figure.h"
#include "game/game.h"

struct figure_market_buyer_window : public figure_info_window_t<figure_market_buyer_window> {
    virtual void init(object_info &c) override {    
        figure_info_window::init(c);

        auto buyer = c.figure_get<figure_market_buyer>();
        if (!buyer) {
            return;
        }

        const uint16_t big_image = buyer->anim(animkeys().big_image).first_img();
        ui["big_image"].image(big_image);

        const uint16_t res_image = image_id_resource_icon(buyer->base.collecting_item_id);
        ui["resource_image"].image(res_image);
    }
};

figure_market_buyer_window figure_market_buyer_infow;
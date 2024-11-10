#include "city_overlay_other.h"

#include "building/building.h"
#include "building/model.h"
#include "city/constants.h"

#include "core/calc.h"
#include "figure/figure.h"
#include "game/resource.h"
#include "game/state.h"
#include "graphics/graphics.h"
#include "graphics/elements/tooltip.h"
#include "grid/building.h"
#include "grid/desirability.h"
#include "grid/image.h"
#include "grid/property.h"
#include "grid/random.h"
#include "grid/terrain.h"
#include "config/config.h"
#include "overlays/city_overlay.h"

city_overlay* city_overlay_for_food_stocks() {
    static city_overlay_food_stocks overlay;
    return &overlay;
}

int city_overlay_food_stocks::get_column_height(const building *b) const {
    if (b->house_size && model_get_house(b->subtype.house_level)->food_types) {
        int pop = b->house_population;
        int stocks = 0;
        
        for (int i = INVENTORY_MIN_FOOD; i < INVENTORY_MAX_FOOD; i++) {
            stocks += b->data.house.foods[i];
        }

        int pct_stocks = calc_percentage(stocks, pop);
        if (pct_stocks <= 0)
            return 10;
        
        if (pct_stocks < 100)
            return 5;
        
        if (pct_stocks <= 200)
            return 1;
    }
    return NO_COLUMN;
}

xstring city_overlay_food_stocks::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->house_population <= 0) {
        return 0;
    }

    if (!model_get_house(b->subtype.house_level)->food_types) {
        return ui::str(66, 104);
    } else {
        int stocks_present = 0;
        for (int i = INVENTORY_MIN_FOOD; i < INVENTORY_MAX_FOOD; i++) {
            stocks_present += b->data.house.foods[i];
        }

        int stocks_per_pop = calc_percentage<int>(stocks_present, b->house_population);
        if (stocks_per_pop <= 0) {
            return ui::str(66, 4);
        } else if (stocks_per_pop < 100) {
            return ui::str(66, 5);
        } else if (stocks_per_pop <= 200) {
            return ui::str(66, 6);
        } else {
            return ui::str(66, 7);
        }
    }
}

bool city_overlay_food_stocks::show_figure(const figure *f) const {
    if (f->type == FIGURE_MARKET_BUYER || f->type == FIGURE_MARKET_TRADER || f->type == FIGURE_DELIVERY_BOY
        || f->type == FIGURE_FISHING_BOAT) {
        return 1;
    } else if (f->type == FIGURE_CART_PUSHER) {
        return resource_is_food(f->get_resource());
    }

    return 0;
}

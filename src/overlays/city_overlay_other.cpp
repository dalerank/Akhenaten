#include "city_overlay_other.h"

#include "building/building.h"
#include "building/model.h"
#include "city/constants.h"

#include "core/calc.h"
#include "figure/figure.h"
#include "game/resource.h"
#include "game/state.h"
#include "graphics/boilerplate.h"
#include "graphics/elements/tooltip.h"
#include "grid/building.h"
#include "grid/desirability.h"
#include "grid/image.h"
#include "grid/property.h"
#include "grid/random.h"
#include "grid/terrain.h"
#include "io/config/config.h"
#include "overlays/city_overlay.h"

static int show_building_food_stocks(const building* b) {
    return b->type == BUILDING_MARKET || b->type == BUILDING_FISHING_WHARF || b->type == BUILDING_GRANARY;
}


static int show_figure_food_stocks(const figure* f) {
    if (f->type == FIGURE_MARKET_BUYER || f->type == FIGURE_MARKET_TRADER || f->type == FIGURE_DELIVERY_BOY
        || f->type == FIGURE_FISHING_BOAT) {
        return 1;
    } else if (f->type == FIGURE_CART_PUSHER) {
        return resource_is_food(f->get_resource());
    }

    return 0;
}

static int get_column_height_food_stocks(const building* b) {
    if (b->house_size && model_get_house(b->subtype.house_level)->food_types) {
        int pop = b->house_population;
        int stocks = 0;
        for (int i = INVENTORY_MIN_FOOD; i < INVENTORY_MAX_FOOD; i++)
            stocks += b->data.house.inventory[i];
        int pct_stocks = calc_percentage(stocks, pop);
        if (pct_stocks <= 0)
            return 10;
        else if (pct_stocks < 100)
            return 5;
        else if (pct_stocks <= 200)
            return 1;
    }
    return NO_COLUMN;
}

static int get_tooltip_food_stocks(tooltip_context* c, const building* b) {
    if (b->house_population <= 0) {
        return 0;
    }

    if (!model_get_house(b->subtype.house_level)->food_types) {
        return 104;
    } else {
        int stocks_present = 0;
        for (int i = INVENTORY_MIN_FOOD; i < INVENTORY_MAX_FOOD; i++) {
            stocks_present += b->data.house.inventory[i];
        }

        int stocks_per_pop = calc_percentage(stocks_present, b->house_population);
        if (stocks_per_pop <= 0) {
            return 4;
        } else if (stocks_per_pop < 100) {
            return 5;
        } else if (stocks_per_pop <= 200) {
            return 6;
        } else {
            return 7;
        }
    }
}

const city_overlay* city_overlay_for_food_stocks(void) {
    static city_overlay overlay = {
        OVERLAY_FOOD_STOCKS,
        COLUMN_TYPE_RISK,
        show_building_food_stocks,
        show_figure_food_stocks,
        get_column_height_food_stocks,
        0,
        get_tooltip_food_stocks,
        0,
        0
    };
    return &overlay;
}
#include "city_overlay_other.h"

#include "building/building_house.h"
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
#include "game/game_config.h"
#include "overlays/city_overlay.h"

city_overlay_food_stocks g_city_overlay_food_stocks;

int city_overlay_food_stocks::get_column_height(const building *b) const {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return COLUMN_TYPE_NONE;
    }

    auto &housed = house->runtime_data();
    if (house->model().food_types) {
        int pop = housed.population;
        int stocks = 0;
        
        for (int i = INVENTORY_MIN_FOOD; i < INVENTORY_MAX_FOOD; i++) {
            stocks += housed.foods[i];
        }

        int pct_stocks = calc_percentage(stocks, pop);
        if (pct_stocks <= 0)
            return 10;
        
        if (pct_stocks < 100)
            return 5;
        
        if (pct_stocks <= 200)
            return 1;
    }

    return COLUMN_TYPE_NONE;
}

xstring city_overlay_food_stocks::get_tooltip_for_building(tooltip_context *c, const building *b) {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return {};
    }

    if (current_building_id == b->id) {
        return current_tooltip;
    }

    current_building_id = b->id;
    const tooltips_t *tooltips = nullptr;

    auto &housed = house->runtime_data();
    if (housed.population <= 0) {
        return {};
    }

    if (!house->model().food_types) {
        tooltips = &get_tooltips("not_provided");
    } else {
        int stocks_present = 0;
        for (int i = INVENTORY_MIN_FOOD; i < INVENTORY_MAX_FOOD; i++) {
            stocks_present += housed.foods[i];
        }

        int stocks_per_pop = calc_percentage<int>(stocks_present, housed.population);
        if (stocks_per_pop <= 0) {
            tooltips = &get_tooltips("none");
        } else if (stocks_per_pop < 100) {
            tooltips = &get_tooltips("low");
        } else if (stocks_per_pop <= 200) {
            tooltips = &get_tooltips("medium");
        } else {
            tooltips = &get_tooltips("high");
        }
    }

    xstring tooltip = "#unknown_tooltip_food_stock";
    if (tooltips && !tooltips->values.empty()) {
        int index = rand() % tooltips->values.size();
        tooltip = tooltips->values[index];
    }

    current_tooltip = lang_xtext_from_key(tooltip);
    return current_tooltip;
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

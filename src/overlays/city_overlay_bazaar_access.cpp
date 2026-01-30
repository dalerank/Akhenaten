#include "city_overlay_bazaar_access.h"

#include "core/calc.h"
#include "grid/floodplain.h"
#include "building/building_house.h"
#include "figure/figure.h"
#include "grid/property.h"
#include "grid/building.h"
#include "grid/terrain.h"
#include "grid/image.h"
#include "graphics/color.h"
#include "graphics/graphics.h"
#include "grid/point.h"
#include "game/state.h"

city_overlay_bazaar_access g_city_overlay_bazaar_access;

int city_overlay_bazaar_access::get_column_height(const building *b) const {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return COLUMN_TYPE_NONE;
    }
    
    if (house->house_population() <= 0) {
        return COLUMN_TYPE_NONE;
    }

    auto &housed = house->runtime_data();
    return std::clamp<int>(housed.bazaar_access / 10, 0, 8);
}

xstring city_overlay_bazaar_access::get_tooltip_for_building(tooltip_context *c, const building *b) {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return ui::str(66, 7);
    }

    auto &housed = house->runtime_data();
    if (housed.population <= 0) {
        return {};
    }

    if (!house->model().food_types) {
        return ui::str(66, 104);
    } else {
        int stocks_present = 0;
        for (int i = INVENTORY_MIN_FOOD; i < INVENTORY_MAX_FOOD; i++) {
            stocks_present += housed.foods[i];
        }

        int stocks_per_pop = calc_percentage<int>(stocks_present, housed.population);
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

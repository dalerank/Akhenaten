#include "city_overlay_courthouse.h"

#include "game/state.h"
#include "grid/building.h"
#include "grid/property.h"
#include "figure/figure.h"

#include "building/building_house.h"

city_overlay_courthouse g_city_overlay_courthouse;

int city_overlay_courthouse::get_column_height(const building *b) const {
    auto house = ((building*)b)->dcast_house();

    if (house && house->house_population() > 0) {
        auto &housed = house->runtime_data();
        if (housed.magistrate) {
            return housed.magistrate / 10;
        }
        return 0;
    }

    return COLUMN_TYPE_NONE;
}

xstring city_overlay_courthouse::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    auto house = ((building *)b)->dcast_house();
    if (!house) {
        return  ui::str(66, 159);
    }

    auto &housed = house->runtime_data();
    if (housed.magistrate <= 0) {
        return ui::str(66, 158);
    } else if (housed.magistrate <= 33) {
        return ui::str(66, 161);
    } else if (housed.magistrate <= 66) {
        return ui::str(66, 160);
    } else {
        return ui::str(66, 159);
    }
}

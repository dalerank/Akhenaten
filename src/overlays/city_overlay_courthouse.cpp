#include "city_overlay_courthouse.h"

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

void city_overlay_courthouse::get_tooltip_for_building(tooltip_context *c, const building *b, xstring &tooltip){
    auto house = ((building *)b)->dcast_house();
    if (!house) {
        tooltip = ui::str(66, 159);
        return;
    }

    auto &housed = house->runtime_data();
    if (housed.magistrate <= 0) {
        tooltip = ui::str(66, 158);
        return;
    } else if (housed.magistrate <= 33) {
        tooltip = ui::str(66, 161);
        return;
    } else if (housed.magistrate <= 66) {
        tooltip = ui::str(66, 160);
        return;
    } else {
        tooltip = ui::str(66, 159);
        return;
    }
}

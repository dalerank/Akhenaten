#include "city_overlay_juggler.h"

#include "grid/property.h"
#include "grid/building.h"
#include "graphics/elements/tooltip.h"
#include "building/building_house.h"
#include "figure/figure.h"

city_overlay_booth g_city_overlay_booth;

int city_overlay_booth::get_column_height(const building *b) const {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return COLUMN_TYPE_NONE;
    }

    auto &housed = house->runtime_data();
    if (housed.booth_juggler || housed.bandstand_juggler) {
        return std::max<int>(housed.booth_juggler, housed.bandstand_juggler) / 10;
    }

    return COLUMN_TYPE_NONE;
}

void city_overlay_booth::get_tooltip_for_building(tooltip_context *c, const building *b, xstring &tooltip){
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        tooltip = ui::str(66, 78);
        return;
    }

    auto &housed = house->runtime_data();
    int juggler_value = std::max<int>(housed.booth_juggler, housed.bandstand_juggler);

    if (juggler_value <= 0) {
        tooltip = ui::str(66, 75);
        return;
        }
    else if (juggler_value >= 80) {
        tooltip = ui::str(66, 76);
        return;
        }
    else if (juggler_value >= 20) {
        tooltip = ui::str(66, 77);
        return;
        }
    else {
        tooltip = ui::str(66, 78);
        return;
    }
}
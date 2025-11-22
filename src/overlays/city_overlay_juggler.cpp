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

xstring city_overlay_booth::get_tooltip_for_building(tooltip_context *c, const building *b) {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return ui::str(66, 78);
    }

    auto &housed = house->runtime_data();
    int juggler_value = std::max<int>(housed.booth_juggler, housed.bandstand_juggler);

    if (juggler_value <= 0)
        return ui::str(66, 75);
    else if (juggler_value >= 80)
        return ui::str(66, 76);
    else if (juggler_value >= 20)
        return ui::str(66, 77);
    else {
        return ui::str(66, 78);
    }
}
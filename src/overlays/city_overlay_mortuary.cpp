#include "city_overlay_health.h"

#include "grid/property.h"
#include "grid/building.h"
#include "figure/figure.h"
#include "city_overlay_mortuary.h"
#include "building/building_house.h"

city_overlay_mortuary g_city_overlay_mortuary;

int city_overlay_mortuary::get_column_height(const building *b) const {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return COLUMN_TYPE_NONE;
    }

    auto &housed = house->runtime_data();
    return (housed.mortuary > 0) ? housed.mortuary / 10 : COLUMN_TYPE_NONE;
}

xstring city_overlay_mortuary::get_tooltip_for_building(tooltip_context *c, const building *b) {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return ui::str(66, 42);
    }

    auto &housed = house->runtime_data();
    if (housed.mortuary <= 0) {
        return ui::str(66, 39);
    } else if (housed.mortuary >= 80) {
        return ui::str(66, 40);
    } else if (housed.mortuary >= 20) {
        return ui::str(66, 41);
    }

    return ui::str(66, 42);
}

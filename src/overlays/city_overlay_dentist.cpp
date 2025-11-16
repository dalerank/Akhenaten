#include "city_overlay_dentist.h"

#include "city/constants.h"
#include "grid/property.h"
#include "grid/building.h"
#include "figure/figure.h"
#include "building/building_house.h"

city_overlay_dentist g_city_overlay_dentist;

int city_overlay_dentist::get_column_height(const building *b) const {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return COLUMN_TYPE_NONE;
    }

    auto &housed = house->runtime_data();
    return housed.dentist > 0 ? housed.dentist / 10 : COLUMN_TYPE_NONE;
}

xstring city_overlay_dentist::get_tooltip_for_building(tooltip_context *c, const building *b) {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return ui::str(66, 11);
    }

    auto &housed = house->runtime_data();
    if (housed.dentist <= 0)
        return ui::str(66, 8);
    else if (housed.dentist >= 80)
        return ui::str(66, 9);
    else if (housed.dentist >= 20)
        return ui::str(66, 10);
    else {
        return ui::str(66, 11);
    }
}

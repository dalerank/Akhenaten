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

void city_overlay_dentist::get_tooltip_for_building(tooltip_context *c, const building *b, xstring &tooltip){
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        tooltip = ui::str(66, 11);
        return;
    }

    auto &housed = house->runtime_data();
    if (housed.dentist <= 0) {
        tooltip = ui::str(66, 8);
        return;
        }
    else if (housed.dentist >= 80) {
        tooltip = ui::str(66, 9);
        return;
        }
    else if (housed.dentist >= 20) {
        tooltip = ui::str(66, 10);
        return;
        }
    else {
        tooltip = ui::str(66, 11);
        return;
    }
}

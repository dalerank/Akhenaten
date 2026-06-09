#include "city_overlay_physician.h"

#include "grid/property.h"
#include "grid/building.h"
#include "graphics/elements/tooltip.h"
#include "building/building_house.h"
#include "figure/figure.h"

city_overlay_physician g_city_overlay_physician;

int city_overlay_physician::get_column_height(const building *b) const {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return COLUMN_TYPE_NONE;
    }

    auto &housed = house->runtime_data();
    return (house->house_population() > 0)
             ? housed.physician
                ? housed.physician / 10
                : 0
             : COLUMN_TYPE_NONE;
}

void city_overlay_physician::get_tooltip_for_building(tooltip_context *c, const building *b, xstring &tooltip){
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        tooltip = ui::str(66, 135);
        return;
    }

    auto &housed = house->runtime_data();
    if (housed.physician <= 0) {
        tooltip = ui::str(66, 132);
        return;
    } else if (housed.physician <= 33) {
        tooltip = ui::str(66, 133);
        return;
    } else if (housed.physician <= 66) {
        tooltip = ui::str(66, 134);
        return;
    } else {
        tooltip = ui::str(66, 135);
        return;
    }
}

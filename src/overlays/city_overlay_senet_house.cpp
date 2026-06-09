#include "city_overlay_entertainment.h"

#include "figure/figure.h"
#include "city_overlay.h"
#include "building/building_house.h"

int city_overlay_senet_house::get_column_height(const building *b) const {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return COLUMN_TYPE_NONE;
    }

    auto &housed = house->runtime_data();
    return (house->house_population() > 0) ? housed.senet_player / 10 : COLUMN_TYPE_NONE;
}

void city_overlay_senet_house::get_tooltip_for_building(tooltip_context *c, const building *b, xstring &tooltip){
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        tooltip = ui::str(66, 90);
        return;
    }

    auto &housed = house->runtime_data();
    if (housed.senet_player <= 0) {
        tooltip = ui::str(66, 87);
        return;
    } else if (housed.senet_player >= 80) {
        tooltip = ui::str(66, 88);
        return;
    } else if (housed.senet_player >= 20) {
        tooltip = ui::str(66, 89);
        return;
    } else {
        tooltip = ui::str(66, 90);
        return;
    }
}
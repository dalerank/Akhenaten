#include "city_overlay_entertainment.h"

#include "game/state.h"
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

xstring city_overlay_senet_house::get_tooltip_for_building(tooltip_context *c, const building *b) {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return ui::str(66, 90);
    }

    auto &housed = house->runtime_data();
    if (housed.senet_player <= 0) {
        return ui::str(66, 87);
    } else if (housed.senet_player >= 80) {
        return ui::str(66, 88);
    } else if (housed.senet_player >= 20) {
        return ui::str(66, 89);
    } else {
        return ui::str(66, 90);
    }
}
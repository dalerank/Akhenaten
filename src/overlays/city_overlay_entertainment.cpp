#include "city_overlay_entertainment.h"

#include "game/state.h"
#include "figure/figure.h"
#include "city_overlay.h"
#include "building/building_house.h"

city_overlay_entertainment g_city_overlay_entertainment;
city_overlay_senet_house g_city_overlay_senet_house;

int city_overlay_entertainment::get_column_height(const building *b) const {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return COLUMN_TYPE_NONE;
    }

    return (house->house_population() > 0) ? house->runtime_data().entertainment / 10 : COLUMN_TYPE_NONE;
}

xstring city_overlay_entertainment::get_tooltip_for_building(tooltip_context *c, const building *b) {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return ui::str(66, 74);;
    }

    auto &housed = house->runtime_data();
    if (housed.entertainment <= 0) {
        return ui::str(66, 64);
    } else if (housed.entertainment < 10) {
        return ui::str(66, 65);
    } else if (housed.entertainment < 20) {
        return ui::str(66, 66);
    } else if (housed.entertainment < 30) {
        return ui::str(66, 67);
    } else if (housed.entertainment < 40) {
        return ui::str(66, 68);
    } else if (housed.entertainment < 50) {
        return ui::str(66, 69);
    } else if (housed.entertainment < 60) {
        return ui::str(66, 70);
    } else if (housed.entertainment < 70) {
        return ui::str(66, 71);
    } else if (housed.entertainment < 80) {
        return ui::str(66, 72);
    } else if (housed.entertainment < 90) {
        return ui::str(66, 73);
    } else {
        return ui::str(66, 74);
    }
}
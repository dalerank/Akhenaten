#include "city_overlay_entertainment.h"

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

void city_overlay_entertainment::get_tooltip_for_building(tooltip_context *c, const building *b, xstring &tooltip){
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        tooltip = ui::str(66, 74);;
        return;
    }

    auto &housed = house->runtime_data();
    if (housed.entertainment <= 0) {
        tooltip = ui::str(66, 64);
        return;
    } else if (housed.entertainment < 10) {
        tooltip = ui::str(66, 65);
        return;
    } else if (housed.entertainment < 20) {
        tooltip = ui::str(66, 66);
        return;
    } else if (housed.entertainment < 30) {
        tooltip = ui::str(66, 67);
        return;
    } else if (housed.entertainment < 40) {
        tooltip = ui::str(66, 68);
        return;
    } else if (housed.entertainment < 50) {
        tooltip = ui::str(66, 69);
        return;
    } else if (housed.entertainment < 60) {
        tooltip = ui::str(66, 70);
        return;
    } else if (housed.entertainment < 70) {
        tooltip = ui::str(66, 71);
        return;
    } else if (housed.entertainment < 80) {
        tooltip = ui::str(66, 72);
        return;
    } else if (housed.entertainment < 90) {
        tooltip = ui::str(66, 73);
        return;
    } else {
        tooltip = ui::str(66, 74);
        return;
    }
}
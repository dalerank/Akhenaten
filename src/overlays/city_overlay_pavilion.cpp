#include "city_overlay_pavilion.h"

#include "game/state.h"
#include "grid/property.h"
#include "grid/building.h"
#include "figure/figure.h"
#include "figuretype/figure_musician.h"
#include "figuretype/figure_dancer.h"
#include "building/building_house.h"

city_overlay_pavilion g_city_overlay_pavilion;

bool city_overlay_pavilion::show_figure(const figure *f) const {
    figure_musician *musician = smart_cast<figure_musician>((figure *)f);
    if (musician) {
        return musician->current_destination()->type == BUILDING_PAVILLION;
    }

    figure_dancer *dancer = smart_cast<figure_dancer>((figure *)f);
    if (dancer) {
        return true;
    }

    return false;
}

int city_overlay_pavilion::get_column_height(const building *b) const {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return COLUMN_TYPE_NONE;
    }

    auto &housed = house->runtime_data();
    return (house->house_population())
                ? housed.pavillion_dancer / 10 
                : COLUMN_TYPE_NONE;
}

xstring city_overlay_pavilion::get_tooltip_for_building(tooltip_context *c, const building *b) {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return ui::str(66, 86);
    }

    auto &housed = house->runtime_data();
    if (housed.senet_player <= 0) {
        return ui::str(66, 83);
    } else if (housed.senet_player >= 80) {
        return ui::str(66, 84);
    } else if (housed.senet_player >= 20) {
        return ui::str(66, 85);
    } else {
        return ui::str(66, 86);
    }
}


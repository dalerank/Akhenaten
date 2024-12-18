#include "city_overlay_pavilion.h"

#include "game/state.h"
#include "grid/property.h"
#include "grid/building.h"
#include "figure/figure.h"
#include "figuretype/figure_musician.h"
#include "figuretype/figure_dancer.h"

city_overlay* city_overlay_for_pavilion() {
    static city_overlay_pavilion inst;
    return &inst;
}

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
    return (b->house_size)
        ? b->data.house.pavillion_dancer / 10 
        : COLUMN_TYPE_NONE;
}

xstring city_overlay_pavilion::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.senet_player <= 0) {
        return ui::str(66, 83);
    } else if (b->data.house.senet_player >= 80) {
        return ui::str(66, 84);
    } else if (b->data.house.senet_player >= 20) {
        return ui::str(66, 85);
    } else {
        return ui::str(66, 86);
    }
}


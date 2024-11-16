#include "city_overlay_entertainment.h"

#include "game/state.h"
#include "figure/figure.h"
#include "city_overlay.h"

city_overlay *city_overlay_for_senet_house() {
    static city_overlay_senet_house overlay;
    return &overlay;
}

int city_overlay_senet_house::get_column_height(const building *b) const {
    return b->house_size ? b->data.house.senet_player / 10 : NO_COLUMN;
}

xstring city_overlay_senet_house::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.senet_player <= 0) {
        return ui::str(66, 87);
    } else if (b->data.house.senet_player >= 80) {
        return ui::str(66, 88);
    } else if (b->data.house.senet_player >= 20) {
        return ui::str(66, 89);
    } else {
        return ui::str(66, 90);
    }
}
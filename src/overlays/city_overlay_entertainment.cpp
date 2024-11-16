#include "city_overlay_entertainment.h"

#include "game/state.h"
#include "figure/figure.h"
#include "city_overlay.h"

city_overlay* city_overlay_for_entertainment() {
    static city_overlay_entertainment overlay;
    return &overlay;
}

int city_overlay_entertainment::get_column_height(const building *b) const {
    return b->house_size ? b->data.house.entertainment / 10 : NO_COLUMN;
}

xstring city_overlay_entertainment::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.entertainment <= 0) {
        return ui::str(66, 64);
    } else if (b->data.house.entertainment < 10) {
        return ui::str(66, 65);
    } else if (b->data.house.entertainment < 20) {
        return ui::str(66, 66);
    } else if (b->data.house.entertainment < 30) {
        return ui::str(66, 67);
    } else if (b->data.house.entertainment < 40) {
        return ui::str(66, 68);
    } else if (b->data.house.entertainment < 50) {
        return ui::str(66, 69);
    } else if (b->data.house.entertainment < 60) {
        return ui::str(66, 70);
    } else if (b->data.house.entertainment < 70) {
        return ui::str(66, 71);
    } else if (b->data.house.entertainment < 80) {
        return ui::str(66, 72);
    } else if (b->data.house.entertainment < 90) {
        return ui::str(66, 73);
    } else {
        return ui::str(66, 74);
    }
}
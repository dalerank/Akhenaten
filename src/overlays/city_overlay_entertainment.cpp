#include "city_overlay_entertainment.h"

#include "game/state.h"
#include "figure/figure.h"
#include "city_overlay.h"

city_overlay* city_overlay_for_entertainment() {
    static city_overlay_entertainment overlay;
    return &overlay;
}

city_overlay* city_overlay_for_senet_house() {
    static city_overlay_senet_house overlay;
    return &overlay;
}

city_overlay_entertainment::city_overlay_entertainment() {
    type = OVERLAY_ENTERTAINMENT;
    column_type = COLUMN_TYPE_WATER_ACCESS;
}

int city_overlay_entertainment::get_column_height(const building *b) const {
    return b->house_size && b->data.house.entertainment ? b->data.house.entertainment / 10 : NO_COLUMN;
}

int city_overlay_entertainment::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.entertainment <= 0) {
        return 64;
    } else if (b->data.house.entertainment < 10) {
        return 65;
    } else if (b->data.house.entertainment < 20) {
        return 66;
    } else if (b->data.house.entertainment < 30) {
        return 67;
    } else if (b->data.house.entertainment < 40) {
        return 68;
    } else if (b->data.house.entertainment < 50) {
        return 69;
    } else if (b->data.house.entertainment < 60) {
        return 70;
    } else if (b->data.house.entertainment < 70) {
        return 71;
    } else if (b->data.house.entertainment < 80) {
        return 72;
    } else if (b->data.house.entertainment < 90) {
        return 73;
    } else {
        return 74;
    }
}

city_overlay_senet_house::city_overlay_senet_house() {
    type = OVERLAY_SENET_HOUSE;
    column_type = COLUMN_TYPE_WATER_ACCESS;
}

int city_overlay_senet_house::get_column_height(const building *b) const {
    return b->house_size && b->data.house.hippodrome ? b->data.house.hippodrome / 10 : NO_COLUMN;
}

int city_overlay_senet_house::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.hippodrome <= 0) {
        return 87;
    } else if (b->data.house.hippodrome >= 80) {
        return 88;
    } else if (b->data.house.hippodrome >= 20) {
        return 89;
    } else {
        return 90;
    }
}

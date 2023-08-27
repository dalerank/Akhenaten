#include "city_overlay_health.h"

#include "building/type.h"
#include "city_overlay.h"

static int show_building_bathhouse(const building* b) {
    return b->type == BUILDING_MENU_MONUMENTS;
}

static int show_building_hospital(const building* b) {
    return b->type == BUILDING_MORTUARY;
}

static int show_figure_bathhouse(const figure* f) {
    return f->type == FIGURE_BATHHOUSE_WORKER;
}

static int show_figure_hospital(const figure* f) {
    return f->type == FIGURE_SURGEON;
}

static int get_column_height_bathhouse(const building* b) {
    return b->house_size && b->data.house.bathhouse ? b->data.house.bathhouse / 10 : NO_COLUMN;
}

static int get_column_height_hospital(const building* b) {
    return b->house_size && b->data.house.hospital ? b->data.house.hospital / 10 : NO_COLUMN;
}

static int get_tooltip_bathhouse(tooltip_context* c, const building* b) {
    if (b->data.house.bathhouse <= 0)
        return 8;
    else if (b->data.house.bathhouse >= 80)
        return 9;
    else if (b->data.house.bathhouse >= 20)
        return 10;
    else {
        return 11;
    }
}

static int get_tooltip_hospital(tooltip_context* c, const building* b) {
    if (b->data.house.hospital <= 0)
        return 39;
    else if (b->data.house.hospital >= 80)
        return 40;
    else if (b->data.house.hospital >= 20)
        return 41;
    else {
        return 42;
    }
}

const city_overlay* city_overlay_for_bathhouse(void) {
    static city_overlay overlay = {OVERLAY_BATHHOUSE,
                                   COLUMN_TYPE_WATER_ACCESS,
                                   show_building_bathhouse,
                                   show_figure_bathhouse,
                                   get_column_height_bathhouse,
                                   0,
                                   get_tooltip_bathhouse,
                                   0,
                                   0};
    return &overlay;
}

const city_overlay* city_overlay_for_hospital(void) {
    static city_overlay overlay = {OVERLAY_HOSPITAL,
                                   COLUMN_TYPE_WATER_ACCESS,
                                   show_building_hospital,
                                   show_figure_hospital,
                                   get_column_height_hospital,
                                   0,
                                   get_tooltip_hospital,
                                   0,
                                   0};
    return &overlay;
}

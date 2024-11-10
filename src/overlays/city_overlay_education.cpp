#include "city_overlay_education.h"

#include "building/building_type.h"
#include "figure/figure.h"
#include "game/state.h"
#include "grid/property.h"

city_overlay_education g_city_overlay_education;

city_overlay* city_overlay_for_education() {
    return &g_city_overlay_education;
}

city_overlay_libraries g_city_overlay_libraries;

city_overlay* city_overlay_for_library() {
    return &g_city_overlay_libraries;
}

city_overlay_academy g_city_overlay_academy;

city_overlay* city_overlay_for_academy() {
    return &g_city_overlay_academy;
}

city_overlay_education::city_overlay_education() {
    type = OVERLAY_EDUCATION;
}

int city_overlay_education::get_column_height(const building *b) const {
    return b->house_size && b->data.house.education ? b->data.house.education * 3 - 1 : NO_COLUMN;
}

xstring city_overlay_education::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    switch (b->data.house.education) {
    case 0:
        return ui::str(66, 100);
    case 1:
        return ui::str(66, 101);
    case 2:
        return ui::str(66, 102);
    case 3:
        return ui::str(66, 103);
    default:
        return 0;
    }
}

city_overlay_academy::city_overlay_academy() {
    type = OVERLAY_ACADEMY;
    column_type = COLUMN_TYPE_WATER_ACCESS;
}

xstring city_overlay_academy::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.academy <= 0)
        return ui::str(66, 27);
    else if (b->data.house.academy >= 80)
        return ui::str(66, 28);
    else if (b->data.house.academy >= 20)
        return ui::str(66, 29);
    
    return ui::str(66, 30);
}

int city_overlay_academy::get_column_height(const building *b) const {
    return b->house_size && b->data.house.academy ? b->data.house.academy / 10 : NO_COLUMN;
}

city_overlay_libraries::city_overlay_libraries() {
    type = OVERLAY_LIBRARY;
    column_type = COLUMN_TYPE_WATER_ACCESS;
}

int city_overlay_libraries::get_column_height(const building *b) const {
    return b->house_size && b->data.house.library ? b->data.house.library / 10 : NO_COLUMN;
}

xstring city_overlay_libraries::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.library <= 0)
        return ui::str(66, 23);
    else if (b->data.house.library >= 80)
        return ui::str(66, 24);
    else if (b->data.house.library >= 20)
        return ui::str(66, 25);

    return ui::str(66, 26);
}
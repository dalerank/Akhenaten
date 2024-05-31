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
    column_type = COLUMN_TYPE_WATER_ACCESS;
}

int city_overlay_education::get_column_height(const building *b) const {
    return b->house_size && b->data.house.education ? b->data.house.education * 3 - 1 : NO_COLUMN;
}

int city_overlay_education::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    switch (b->data.house.education) {
    case 0:
        return 100;
    case 1:
        return 101;
    case 2:
        return 102;
    case 3:
        return 103;
    default:
        return 0;
    }
}

bool city_overlay_education::show_building(const building *b) const {
    return b->type == BUILDING_SCRIBAL_SCHOOL || b->type == BUILDING_LIBRARY || b->type == BUILDING_ACADEMY;
}

bool city_overlay_education::show_figure(const figure *f) const {
    return f->type == FIGURE_SCRIBER || f->type == FIGURE_LIBRARIAN || f->type == FIGURE_TEACHER;
}

city_overlay_academy::city_overlay_academy() {
    type = OVERLAY_ACADEMY;
    column_type = COLUMN_TYPE_WATER_ACCESS;
}

bool city_overlay_academy::show_figure(const figure *f) const {
    return f->type == FIGURE_SCRIBER;
}

int city_overlay_academy::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.academy <= 0)
        return 27;
    else if (b->data.house.academy >= 80)
        return 28;
    else if (b->data.house.academy >= 20)
        return 29;
    else {
        return 30;
    }
}

int city_overlay_academy::get_column_height(const building *b) const {
    return b->house_size && b->data.house.academy ? b->data.house.academy / 10 : NO_COLUMN;
}

bool city_overlay_academy::show_building(const building *b) const {
    return b->type == BUILDING_ACADEMY;
}

city_overlay_libraries::city_overlay_libraries() {
    type = OVERLAY_LIBRARY;
    column_type = COLUMN_TYPE_WATER_ACCESS;
}

bool city_overlay_libraries::show_figure(const figure *f) const {
    return f->type == FIGURE_LIBRARIAN;
}

int city_overlay_libraries::get_column_height(const building *b) const {
    return b->house_size && b->data.house.library ? b->data.house.library / 10 : NO_COLUMN;
}

int city_overlay_libraries::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.library <= 0)
        return 23;
    else if (b->data.house.library >= 80)
        return 24;
    else if (b->data.house.library >= 20)
        return 25;
    else {
        return 26;
    }
}

bool city_overlay_libraries::show_building(const building *b) const {
    return b->type == BUILDING_LIBRARY;
}

#include "city_overlay_education.h"

#include "building/building_type.h"
#include "figure/figure.h"
#include "grid/property.h"
#include "building/building_house.h"

city_overlay_education g_city_overlay_education;
city_overlay_academy g_city_overlay_academy;
city_overlay_libraries g_city_overlay_libraries;

int city_overlay_education::get_column_height(const building *b) const {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return COLUMN_TYPE_NONE;
    }

    auto &housed = house->runtime_data();
    return (housed.education > 0) ? housed.education * 3 - 1 : COLUMN_TYPE_NONE;
}

void city_overlay_education::get_tooltip_for_building(tooltip_context *c, const building *b, xstring &tooltip){
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return;
    }

    auto &housed = house->runtime_data();
    switch (housed.education) {
    case 0:
        tooltip = ui::str(66, 100);
        return;
    case 1:
        tooltip = ui::str(66, 101);
        return;
    case 2:
        tooltip = ui::str(66, 102);
        return;
    case 3:
        tooltip = ui::str(66, 103);
        return;
    default:
        return;
    }
}

void city_overlay_academy::get_tooltip_for_building(tooltip_context *c, const building *b, xstring &tooltip){
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        tooltip = ui::str(66, 30);
        return;
    }

    auto &housed = house->runtime_data();
    if (housed.academy <= 0) {
        tooltip = ui::str(66, 27);
        return;
        }
    else if (housed.academy >= 80) {
        tooltip = ui::str(66, 28);
        return;
        }
    else if (housed.academy >= 20) {
        tooltip = ui::str(66, 29);
        return;
        }
    
    tooltip = ui::str(66, 30);
    return;
}

int city_overlay_academy::get_column_height(const building *b) const {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return COLUMN_TYPE_NONE;
    }

    auto &housed = house->runtime_data();
    return (housed.academy > 0) ? housed.academy / 10 : COLUMN_TYPE_NONE;
}

int city_overlay_libraries::get_column_height(const building *b) const {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return COLUMN_TYPE_NONE;
    }

    auto &housed = house->runtime_data();
    return (housed.library > 0) ? housed.library / 10 : COLUMN_TYPE_NONE;
}

void city_overlay_libraries::get_tooltip_for_building(tooltip_context *c, const building *b, xstring &tooltip){
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        tooltip = ui::str(66, 26);
        return;
    }

    auto &housed = house->runtime_data();
    if (housed.library <= 0) {
        tooltip = ui::str(66, 23);
        return;
    } else if (housed.library >= 80) {
        tooltip = ui::str(66, 24);
        return;
    } else if (housed.library >= 20) {
        tooltip = ui::str(66, 25);
        return;
    }

    tooltip = ui::str(66, 26);
    return;
}
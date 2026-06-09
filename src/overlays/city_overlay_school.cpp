#include "city_overlay_school.h"

#include "building/building_house.h"
#include "figure/figure.h"
#include "grid/property.h"
#include "grid/building.h"

city_overlay_schools g_city_overlay_schools;

int city_overlay_schools::get_column_height(const building *b) const {
    auto house = ((building *)b)->dcast_house();
    if (!house) {
        return COLUMN_TYPE_NONE;
    }

    if (!house->house_population()) {
        return COLUMN_TYPE_NONE;
    }

    auto &housed = house->runtime_data();
    return housed.school / 10;
}

void city_overlay_schools::get_tooltip_for_building(tooltip_context *c, const building *b, xstring &tooltip){
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        tooltip = ui::str(66, 22);
        return;
    }

    auto &housed = house->runtime_data();
    if (housed.school <= 0) {
        tooltip = ui::str(66, 19);
        return;
        }
    
    if (housed.school >= 80) {
        tooltip = ui::str(66, 20);
        return;
        }
    
    if (housed.school >= 20) {
        tooltip = ui::str(66, 21);
        return;
        }
    
    tooltip = ui::str(66, 22);
    return;
}

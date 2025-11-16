#include "city_overlay_school.h"

#include "building/building_house.h"
#include "figure/figure.h"
#include "game/state.h"
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

xstring city_overlay_schools::get_tooltip_for_building(tooltip_context *c, const building *b) {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return ui::str(66, 22);
    }

    auto &housed = house->runtime_data();
    if (housed.school <= 0)
        return ui::str(66, 19);
    
    if (housed.school >= 80)
        return ui::str(66, 20);
    
    if (housed.school >= 20)
        return ui::str(66, 21);
    
    return ui::str(66, 22);
}

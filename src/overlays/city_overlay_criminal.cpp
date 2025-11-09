#include "city_overlay_criminal.h"

#include "building/building_house.h"
#include "figure/figure.h"
#include "grid/property.h"
#include "grid/building.h"
#include "game/state.h"

city_overlay_crime g_city_overlay_crime;

int city_overlay_crime::get_column_height(const building* b) const {
    auto house = ((building*)b)->dcast_house();
    if (!house) {
        return COLUMN_TYPE_NONE;
    }

    if (house->house_population() > 0) {
        int crime = house->runtime_data().criminal_active;
        return crime / 10;
    }
    return COLUMN_TYPE_NONE;
}

xstring city_overlay_crime::get_tooltip_for_building(tooltip_context* c, const building* b) const {
    auto house = ((building *)b)->dcast_house();
    if (!house || house->house_population() <= 0) {
        return ui::str(66, 63);
    }

    auto &housed = house->runtime_data();
    if (housed.criminal_active >= 80)
        return ui::str(66, 63);
    else if (housed.criminal_active >= 60)
        return ui::str(66, 62);
    else if (housed.criminal_active >= 40)
        return ui::str(66, 61);
    else if (housed.criminal_active >= 30)
        return ui::str(66, 60);
    else if (housed.criminal_active >= 20)
        return ui::str(66, 59);
    else {
        return ui::str(66, 58);
    }
}

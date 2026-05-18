#include "city_overlay_brewery.h"

#include "grid/building.h"
#include "figure/figure.h"
#include "building/building_house.h"
#include "game/resource.h"

city_overlay_brewery g_city_overlay_brewery;

int city_overlay_brewery::get_column_height(const building* b) const {
    auto house = ((building*)b)->dcast_house();

    if (!house || house->house_population() <= 0) {
        return COLUMN_TYPE_NONE;
    }

    const auto& housed = house->runtime_data();
    return std::clamp<int>(housed.inventory[INVENTORY_GOOD4] / 10, 0, 10);
}

xstring city_overlay_brewery::get_tooltip_for_building(tooltip_context* c, const building* b) {
    auto house = ((building*)b)->dcast_house();

    if (!house) {
        return ui::str(66, 90);
    }

    const auto& housed = house->runtime_data();
    if (housed.inventory[INVENTORY_GOOD4] <= 0) {
        return ui::str(66, 87);
    } else if (housed.inventory[INVENTORY_GOOD4] <= 30) {
        return ui::str(66, 88);
    } else if (housed.inventory[INVENTORY_GOOD4] <= 70) {
        return ui::str(66, 89);
    } else {
        return ui::str(66, 90);
    }
}

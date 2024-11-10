#include "city_overlay_juggler.h"

#include "grid/property.h"
#include "grid/building.h"
#include "graphics/elements/tooltip.h"
#include "figure/figure.h"

city_overlay_booth g_city_overlay_booth;

city_overlay* city_overlay_for_booth() {
    return &g_city_overlay_booth;
}

city_overlay_booth::city_overlay_booth() {
    type = OVERLAY_BOOTH;
}

int city_overlay_booth::get_column_height(const building *b) const {
    if (b->house_size) {
        if (b->data.house.juggler || b->data.house.bandstand_juggler) {
            return std::max<int>(b->data.house.juggler, b->data.house.bandstand_juggler) / 10;
        }
    }

    return NO_COLUMN;
}

xstring city_overlay_booth::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.juggler <= 0)
        return ui::str(66, 75);
    else if (b->data.house.juggler >= 80)
        return ui::str(66, 76);
    else if (b->data.house.juggler >= 20)
        return ui::str(66, 77);
    else {
        return ui::str(66, 78);
    }
}
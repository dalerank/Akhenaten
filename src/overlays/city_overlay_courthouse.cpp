#include "city_overlay_courthouse.h"

#include "building/model.h"
#include "game/state.h"
#include "grid/building.h"
#include "grid/property.h"
#include "figure/figure.h"

city_overlay_courthouse g_city_overlay_courthouse;

city_overlay* city_overlay_for_courthouse() {
    return &g_city_overlay_courthouse;
}

int city_overlay_courthouse::get_column_height(const building *b) const {
    if (b->house_size) {
        if (b->data.house.magistrate) {
            return b->data.house.magistrate / 10;
        }
        return 0;
    }

    return COLUMN_TYPE_NONE;
}

xstring city_overlay_courthouse::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.magistrate <= 0) {
        return ui::str(66, 158);
    } else if (b->data.house.magistrate <= 33) {
        return ui::str(66, 161);
    } else if (b->data.house.magistrate <= 66) {
        return ui::str(66, 160);
    } else {
        return ui::str(66, 159);
    }
}

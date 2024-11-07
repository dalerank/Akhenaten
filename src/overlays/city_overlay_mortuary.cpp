#include "city_overlay_health.h"

#include "grid/property.h"
#include "grid/building.h"
#include "figure/figure.h"
#include "city_overlay_mortuary.h"

city_overlay_mortuary g_city_overlay_mortuary;

city_overlay* city_overlay_for_mortuary() {
    return &g_city_overlay_mortuary;
}

city_overlay_mortuary::city_overlay_mortuary() {
    type = OVERLAY_MORTUARY;
    column_type = COLUMN_TYPE_POSITIVE;
}

int city_overlay_mortuary::get_column_height(const building *b) const {
    return b->house_size && b->data.house.mortuary ? b->data.house.mortuary / 10 : NO_COLUMN;
}

xstring city_overlay_mortuary::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.mortuary <= 0) {
        return ui::str(66, 39);
    } else if (b->data.house.mortuary >= 80) {
        return ui::str(66, 40);
    } else if (b->data.house.mortuary >= 20) {
        return ui::str(66, 41);
    }

    return ui::str(66, 42);
}

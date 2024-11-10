#include "city_overlay_physician.h"

#include "grid/property.h"
#include "grid/building.h"
#include "graphics/elements/tooltip.h"
#include "figure/figure.h"

city_overlay_physician g_city_overlay_physician;

city_overlay* city_overlay_for_physician() {
    return &g_city_overlay_physician;
}

int city_overlay_physician::get_column_height(const building *b) const {
    return b->house_size && b->subtype.house_level
             ? b->data.house.physician
                ? b->data.house.physician / 10
                : 0
             : NO_COLUMN;
}

xstring city_overlay_physician::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.physician <= 0) {
        return ui::str(66, 132);
    } else if (b->data.house.physician <= 33) {
        return ui::str(66, 133);
    } else if (b->data.house.physician <= 66) {
        return ui::str(66, 134);
    } else {
        return ui::str(66, 135);
    }
}

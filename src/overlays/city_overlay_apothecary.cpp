#include "city_overlay_apothecary.h"

#include "city/constants.h"
#include "grid/property.h"
#include "grid/building.h"
#include "building/building.h"
#include "graphics/elements/tooltip.h"
#include "figure/figure.h"

city_overlay_apothecary g_city_overlay_apothecary;

city_overlay* city_overlay_for_apothecary() {
    return &g_city_overlay_apothecary;
}

xstring city_overlay_apothecary::get_tooltip_for_building(tooltip_context* c, const building* b) const {
    if (b->data.house.apothecary <= 0)
        return ui::str(66, 31);
    else if (b->data.house.apothecary >= 80)
        return ui::str(66, 32);
    else if (b->data.house.apothecary < 20)
        return ui::str(66, 33);
    else {
        return ui::str(66, 34);
    }
}

int city_overlay_apothecary::get_column_height(const building *b) const {
    return b->house_size && b->data.house.level > 0
                ? b->data.house.apothecary / 10 
                : COLUMN_TYPE_NONE;
}

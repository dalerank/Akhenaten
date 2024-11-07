#include "city_overlay_dentist.h"

#include "city/constants.h"
#include "grid/property.h"
#include "grid/building.h"
#include "figure/figure.h"

city_overlay_dentist g_city_overlay_dentist;

city_overlay* city_overlay_for_dentist() {
    return &g_city_overlay_dentist;
}

city_overlay_dentist::city_overlay_dentist() {
    type = OVERLAY_DENTIST;
    column_type = COLUMN_TYPE_POSITIVE;
}

int city_overlay_dentist::get_column_height(const building *b) const {
    return b->house_size && b->data.house.dentist ? b->data.house.dentist / 10 : NO_COLUMN;
}

xstring city_overlay_dentist::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.dentist <= 0)
        return ui::str(66, 8);
    else if (b->data.house.dentist >= 80)
        return ui::str(66, 9);
    else if (b->data.house.dentist >= 20)
        return ui::str(66, 10);
    else {
        return ui::str(66, 11);
    }
}

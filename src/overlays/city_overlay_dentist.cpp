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

bool city_overlay_dentist::show_figure(const figure *f) const {
    return f->type == FIGURE_DENTIST;
}

void city_overlay_dentist::draw_custom_top(vec2i pixel, tile2i tile, painter &ctx) const {
    if (!map_property_is_draw_tile(tile)) {
        return;
    }

    if (map_building_at(tile)) {
        city_overlay::draw_building_top(pixel, tile, ctx);
    }
}

int city_overlay_dentist::get_column_height(const building *b) const {
    return b->house_size && b->data.house.dentist ? b->data.house.dentist / 10 : NO_COLUMN;
}

int city_overlay_dentist::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.dentist <= 0)
        return 8;
    else if (b->data.house.dentist >= 80)
        return 9;
    else if (b->data.house.dentist >= 20)
        return 10;
    else {
        return 11;
    }
}

bool city_overlay_dentist::show_building(const building *b) const {
    return b->type == BUILDING_DENTIST;
}

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

city_overlay_apothecary::city_overlay_apothecary() {
    type = OVERLAY_APOTHECARY;
    column_type = COLUMN_TYPE_POSITIVE;
}

int city_overlay_apothecary::get_tooltip_for_building(tooltip_context* c, const building* b) const {
    if (b->data.house.apothecary <= 0)
        return 31;
    else if (b->data.house.apothecary >= 80)
        return 32;
    else if (b->data.house.apothecary < 20)
        return 33;
    else {
        return 34;
    }
}

bool city_overlay_apothecary::show_figure(const figure *f) const {
    return f->type == FIGURE_HERBALIST;
}

int city_overlay_apothecary::get_column_height(const building *b) const {
    return b->house_size && b->subtype.house_level > 0
                ? b->data.house.apothecary / 10 
                : NO_COLUMN;
}

void city_overlay_apothecary::draw_custom_top(vec2i pixel, tile2i tile, painter &ctx) const {
    if (!map_property_is_draw_tile(tile)) {
        return;
    }

    if (map_building_at(tile)) {
        city_overlay::draw_building_top(pixel, tile, ctx);
    }
}

bool city_overlay_apothecary::show_building(const building *b) const {
    return b->type == BUILDING_APOTHECARY;
}

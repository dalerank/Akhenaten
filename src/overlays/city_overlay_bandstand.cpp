#include "city_overlay_juggler.h"

#include "figure/figure.h"
#include "grid/property.h"
#include "grid/building.h"
#include "graphics/elements/tooltip.h"
#include "figuretype/figure_musician.h"
#include "city_overlay_bandstand.h"

city_overlay_bandstand g_city_overlay_bandstand;

city_overlay* city_overlay_for_bandstand() {
    return &g_city_overlay_bandstand;
}

city_overlay_bandstand::city_overlay_bandstand() {
    type = OVERLAY_BANDSTAND;
    column_type = COLUMN_TYPE_POSITIVE;
}

int city_overlay_bandstand::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.bandstand_musician <= 0)
        return 79;
    else if (b->data.house.bandstand_musician >= 80)
        return 80;
    else if (b->data.house.bandstand_musician >= 20)
        return 81;
    else {
        return 82;
    }
}

bool city_overlay_bandstand::show_figure(const figure *f) const {
    figure_musician *musician = ((figure *)f)->dcast_musician();
    return musician
        ? musician->current_destination()->type == BUILDING_BANDSTAND
        : false;
}

int city_overlay_bandstand::get_column_height(const building *b) const {
    if (b->house_size) {
        if (b->data.house.bandstand_musician) {
            return b->data.house.bandstand_musician / 10;
        }
    }

    return NO_COLUMN;
}

void city_overlay_bandstand::draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const {
    int grid_offset = point.grid_offset();
    if (!map_property_is_draw_tile(grid_offset)) {
        return;
    }

    if (map_building_at(grid_offset)) {
        city_overlay::draw_building_top(pixel, point, ctx);
    }
}

inline bool city_overlay_bandstand::show_building(const building *b) const {
    return b->type == BUILDING_CONSERVATORY || b->type == BUILDING_BANDSTAND;
}

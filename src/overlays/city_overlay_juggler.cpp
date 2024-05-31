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
    column_type = COLUMN_TYPE_POSITIVE;
}

bool city_overlay_booth::show_figure(const figure *f) const {
    return f->type == FIGURE_JUGGLER;
}

void city_overlay_booth::draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const {
    if (!map_property_is_draw_tile(point)) {
        return;
    }

    if (map_building_at(point)) {
        city_overlay::draw_building_top(pixel, point, ctx);
    }
}

int city_overlay_booth::get_column_height(const building *b) const {
    if (b->house_size) {
        if (b->data.house.juggler || b->data.house.bandstand_juggler) {
            return std::max<int>(b->data.house.juggler, b->data.house.bandstand_juggler) / 10;
        }
    }

    return NO_COLUMN;
}

int city_overlay_booth::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.juggler <= 0)
        return 75;
    else if (b->data.house.juggler >= 80)
        return 76;
    else if (b->data.house.juggler >= 20)
        return 77;
    else {
        return 78;
    }
}

inline bool city_overlay_booth::show_building(const building *b) const {
    return b->type == BUILDING_JUGGLER_SCHOOL || b->type == BUILDING_BOOTH;
}

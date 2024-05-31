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

bool city_overlay_mortuary::show_figure(const figure *f) const {
    return f->type == FIGURE_EMBALMER;
}

void city_overlay_mortuary::draw_custom_top(vec2i pixel, tile2i tile, painter &ctx) const {
    if (!map_property_is_draw_tile(tile)) {
        return;
    }

    if (map_building_at(tile)) {
        city_overlay::draw_building_top(pixel, tile, ctx);
    }
}

int city_overlay_mortuary::get_column_height(const building *b) const {
    return b->house_size && b->data.house.mortuary ? b->data.house.mortuary / 10 : NO_COLUMN;
}

int city_overlay_mortuary::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.mortuary <= 0)
        return 39;
    else if (b->data.house.mortuary >= 80)
        return 40;
    else if (b->data.house.mortuary >= 20)
        return 41;
    else {
        return 42;
    }
}

bool city_overlay_mortuary::show_building(const building *b) const {
    return b->type == BUILDING_MORTUARY;
}

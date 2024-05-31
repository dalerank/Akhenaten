#include "city_overlay_physician.h"

#include "grid/property.h"
#include "grid/building.h"
#include "graphics/elements/tooltip.h"
#include "figure/figure.h"

city_overlay_physician g_city_overlay_physician;

city_overlay* city_overlay_for_physician() {
    return &g_city_overlay_physician;
}

city_overlay_physician::city_overlay_physician() {
    type = OVERLAY_PHYSICIAN;
    column_type = COLUMN_TYPE_WATER_ACCESS;
}

bool city_overlay_physician::show_figure(const figure *f) const {
    return f->type == FIGURE_PHYSICIAN;
}

void city_overlay_physician::draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const {
    if (!map_property_is_draw_tile(point)) {
        return;
    }

    if (map_building_at(point)) {
        city_overlay::draw_building_top(pixel, point, ctx);
    }
}

int city_overlay_physician::get_column_height(const building *b) const {
    return b->house_size && b->subtype.house_level
             ? b->data.house.physician
                ? b->data.house.physician / 10
                : 0
             : NO_COLUMN;
}

int city_overlay_physician::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.physician <= 0) {
        return 132;
    } else if (b->data.house.physician <= 33) {
        return 133;
    } else if (b->data.house.physician <= 66) {
        return 134;
    } else {
        return 135;
    }
}

bool city_overlay_physician::show_building(const building *b) const {
    return b->type == BUILDING_PHYSICIAN;
}

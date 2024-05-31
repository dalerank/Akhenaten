#include "city_overlay_courthouse.h"

#include "building/model.h"
#include "game/state.h"
#include "grid/building.h"
#include "grid/property.h"
#include "figure/figure.h"

city_overlay_courthouse g_city_overlay_courthouse;

city_overlay* city_overlay_for_courthouse() {
    return &g_city_overlay_courthouse;
}

city_overlay_courthouse::city_overlay_courthouse() {
    type = OVERLAY_COUTHOUSE;
    column_type = COLUMN_TYPE_WATER_ACCESS;
}

bool city_overlay_courthouse::show_figure(const figure *f) const {
    return f->type == FIGURE_MAGISTRATE;
}

int city_overlay_courthouse::get_column_height(const building *b) const {
    if (b->house_size) {
        if (b->data.house.magistrate) {
            return b->data.house.magistrate / 10;
        }
        return 0;
    }

    return NO_COLUMN;
}

int city_overlay_courthouse::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.magistrate <= 0) {
        return 158;
    } else if (b->data.house.magistrate <= 33) {
        return 161;
    } else if (b->data.house.magistrate <= 66) {
        return 160;
    } else {
        return 159;
    }
}

void city_overlay_courthouse::draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const {
    if (!map_property_is_draw_tile(point)) {
        return;
    }

    if (map_building_at(point)) {
        city_overlay::draw_building_top(pixel, point, ctx);
    }
}

bool city_overlay_courthouse::show_building(const building *b) const {
    return b->type == BUILDING_COURTHOUSE;
}

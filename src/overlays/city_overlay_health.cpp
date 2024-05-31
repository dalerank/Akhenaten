#include "city_overlay_health.h"

#include "grid/property.h"
#include "grid/building.h"
#include "figure/figure.h"

city_overlay_health g_city_overlay_health;

city_overlay* city_overlay_for_health() {
    return &g_city_overlay_health;
}

city_overlay_health::city_overlay_health() {
    type = OVERLAY_HEALTH;
    column_type = COLUMN_TYPE_RISK;
}

int city_overlay_health::get_column_height(const building *b) const {
    if (!b->house_size || !b->house_population) {
        return NO_COLUMN;
    }

    if (b->disease_days > 0) {
        return 10;
    }

    return (100 - b->common_health) / 10;
}

int city_overlay_health::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->disease_days > 0) {
        return 131;
    }

    if (b->common_health < 25) {
        return 130;
    } else if (b->common_health < 50) {
        return 129;
    } else if (b->common_health < 75) {
        return 128;
    } else {
        return 127;
    }
}

bool city_overlay_health::show_figure(const figure *f) const {
    return (f->type == FIGURE_EMBALMER || f->type == FIGURE_HERBALIST || f->type == FIGURE_PHYSICIAN || f->type == FIGURE_DENTIST);
}

void city_overlay_health::draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const {
    if (!map_property_is_draw_tile(point)) {
        return;
    }

    if (map_building_at(point)) {
        city_overlay::draw_building_top(pixel, point, ctx);
    }
}

bool city_overlay_health::show_building(const building *b) const {
    return (b->type == BUILDING_MORTUARY || b->type == BUILDING_APOTHECARY || b->type == BUILDING_PHYSICIAN || b->type == BUILDING_DENTIST);
}

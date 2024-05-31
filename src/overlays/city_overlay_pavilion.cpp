#include "city_overlay_pavilion.h"

#include "game/state.h"
#include "grid/property.h"
#include "grid/building.h"
#include "figure/figure.h"
#include "figuretype/figure_musician.h"
#include "figuretype/figure_dancer.h"

city_overlay_pavilion g_city_overlay_pavilion;

city_overlay* city_overlay_for_pavilion() {
    return &g_city_overlay_pavilion;
}

city_overlay_pavilion::city_overlay_pavilion() {
    type = OVERLAY_PAVILION;
    column_type = COLUMN_TYPE_WATER_ACCESS;
}

bool city_overlay_pavilion::show_figure(const figure *f) const {
    figure_musician *musician = ((figure *)f)->dcast_musician();
    if (musician) {
        return musician->current_destination()->type == BUILDING_PAVILLION;
    }

    figure_dancer *dancer = ((figure *)f)->dcast_dancer();
    if (dancer) {
        return true;
    }

    return false;
}

int city_overlay_pavilion::get_column_height(const building *b) const {
    return (b->house_size && b->data.house.senet_player)
        ? b->data.house.senet_player / 10 
        : NO_COLUMN;
}

int city_overlay_pavilion::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.senet_player <= 0) {
        return 83;
    } else if (b->data.house.senet_player >= 80) {
        return 84;
    } else if (b->data.house.senet_player >= 20) {
        return 85;
    } else {
        return 86;
    }
}

void city_overlay_pavilion::draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const {
    int grid_offset = point.grid_offset();
    if (!map_property_is_draw_tile(grid_offset)) {
        return;
    }

    if (map_building_at(grid_offset)) {
        city_overlay::draw_building_top(pixel, point, ctx);
    }
}

bool city_overlay_pavilion::show_building(const building *b) const {
    return building_type_any_of(b->type, BUILDING_CONSERVATORY, BUILDING_DANCE_SCHOOL, BUILDING_PAVILLION);
}

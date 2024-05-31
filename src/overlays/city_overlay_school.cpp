#include "city_overlay_school.h"

#include "building/building_type.h"
#include "figure/figure.h"
#include "game/state.h"
#include "grid/property.h"
#include "grid/building.h"

city_overlay_schools::city_overlay_schools() {
    type = OVERLAY_SCRIBAL_SCHOOL;
    column_type = COLUMN_TYPE_WATER_ACCESS;
}

city_overlay_schools g_city_overlay_schools;

city_overlay* city_overlay_for_scribal_school() {
    return &g_city_overlay_schools;
}

bool city_overlay_schools::show_figure(const figure *f) const {
    return f->type == FIGURE_TEACHER;
}

void city_overlay_schools::draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const {
    if (!map_property_is_draw_tile(point)) {
        return;
    }

    if (map_building_at(point)) {
        city_overlay::draw_building_top(pixel, point, ctx);
    }
}

int city_overlay_schools::get_column_height(const building *b) const {
    return b->house_size && b->data.house.school ? b->data.house.school / 10 : NO_COLUMN;
}

int city_overlay_schools::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.school <= 0)
        return 19;
    else if (b->data.house.school >= 80)
        return 20;
    else if (b->data.house.school >= 20)
        return 21;
    else {
        return 22;
    }
}

bool city_overlay_schools::show_building(const building *b) const {
    return b->type == BUILDING_SCRIBAL_SCHOOL;
}

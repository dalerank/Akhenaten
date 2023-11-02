#include "city_overlay_education.h"

#include "building/building_type.h"
#include "figure/figure.h"
#include "game/state.h"
#include "grid/property.h"
#include "grid/building.h"


static int show_figure_school(const figure* f) {
    return f->type == FIGURE_TEACHER;
}

static int get_column_height_school(const building* b) {
    return b->house_size && b->data.house.school ? b->data.house.school / 10 : NO_COLUMN;
}

static int get_tooltip_school(tooltip_context* c, const building* b) {
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

struct city_overlay_schools : public city_overlay {
    city_overlay_schools() {
        type = OVERLAY_SCRIBAL_SCHOOL;
        column_type = COLUMN_TYPE_WATER_ACCESS;

        show_figure_func = show_figure_school;
        get_column_height = get_column_height_school;
        get_tooltip_for_building = get_tooltip_school;
    }

    void draw_custom_top(vec2i pixel, tile2i point, view_context &ctx) const override {
        int grid_offset = point.grid_offset();
        int x = pixel.x;
        int y = pixel.y;
        if (!map_property_is_draw_tile(grid_offset)) {
            return;
        }

        if (map_building_at(grid_offset)) {
            city_with_overlay_draw_building_top(pixel, point, ctx);
        }
    }

    bool show_building(const building* b) const override {
        return b->type == BUILDING_SCRIBAL_SCHOOL;
    }
};

city_overlay_schools g_city_overlay_schools;

city_overlay* city_overlay_for_scribal_school() {
    return &g_city_overlay_schools;
}
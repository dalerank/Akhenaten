#pragma once

#include "overlays/city_overlay.h"

struct city_overlay_schools : public city_overlay {
    city_overlay_schools() {
        type = OVERLAY_SCRIBAL_SCHOOL;
        column_type = COLUMN_TYPE_WATER_ACCESS;

        show_figure_func = show_figure_school;
        get_column_height = get_column_height_school;
        get_tooltip_for_building = get_tooltip_school;
    }

    void draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const override {
        int grid_offset = point.grid_offset();
        int x = pixel.x;
        int y = pixel.y;
        if (!map_property_is_draw_tile(grid_offset)) {
            return;
        }

        if (map_building_at(grid_offset)) {
            city_overlay::draw_building_top(pixel, point, ctx);
        }
    }

    bool show_building(const building* b) const override {
        return b->type == BUILDING_SCRIBAL_SCHOOL;
    }
};
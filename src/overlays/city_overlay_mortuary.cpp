#include "city_overlay_health.h"

#include "city_overlay.h"
#include "grid/property.h"
#include "grid/building.h"
#include "figure/figure.h"

static int get_column_height_mortuary(const building* b) {
    return b->house_size && b->data.house.mortuary ? b->data.house.mortuary / 10 : NO_COLUMN;
}

static int get_tooltip_mortuary(tooltip_context* c, const building* b) {
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

struct city_overlay_mortuary : public city_overlay {
    city_overlay_mortuary() {
        type = OVERLAY_MORTUARY;
        column_type = COLUMN_TYPE_POSITIVE;

        get_column_height = get_column_height_mortuary;
        get_tooltip_for_building = get_tooltip_mortuary;
    }

    bool show_figure(const figure* f) const override {
        return f->type == FIGURE_EMBALMER;
    }

    void draw_custom_top(vec2i pixel, map_point point) const override {
        int grid_offset = point.grid_offset();
        int x = pixel.x;
        int y = pixel.y;
        if (!map_property_is_draw_tile(grid_offset)) {
            return;
        }

        if (map_building_at(grid_offset)) {
            city_with_overlay_draw_building_top(pixel, point);
        }
    }

    bool show_building(const building *b) const override {
        return b->type == BUILDING_MORTUARY;
    }
};

city_overlay_mortuary g_city_overlay_mortuary;

const city_overlay* city_overlay_for_mortuary(void) {
    return &g_city_overlay_mortuary;
}

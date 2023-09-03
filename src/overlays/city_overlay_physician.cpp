#include "city_overlay_physician.h"

#include "city_overlay.h"
#include "grid/property.h"
#include "grid/building.h"
#include "graphics/elements/tooltip.h"

static int get_column_height_physician(const building* b) {
    return b->house_size && b->subtype.house_level
             ? b->data.house.physician
                ? b->data.house.physician / 10
                : 1
             : NO_COLUMN;
}

static int get_tooltip_physician(tooltip_context* c, const building* b) {
    if (b->data.house.physician <= 0)
        return 35;
    else if (b->data.house.physician >= 80)
        return 36;
    else if (b->data.house.physician >= 20)
        return 37;
    else {
        return 38;
    }
}

struct city_overlay_physician : public city_overlay {
    city_overlay_physician() {
        type = OVERLAY_PHYSICIAN;
        column_type = COLUMN_TYPE_POSITIVE;

        get_column_height = get_column_height_physician;
        get_tooltip_for_building = get_tooltip_physician;
    }

    bool show_figure(const figure* f) const override {
        return f->type == FIGURE_PHYSICIAN;
    }

    void draw_custom_top(vec2i pixel, map_point point) const override {
        int grid_offset = point.grid_offset();
        if (!map_property_is_draw_tile(grid_offset)) {
            return;
        }

        if (map_building_at(grid_offset)) {
            city_with_overlay_draw_building_top(pixel, point);
        }
    }

    bool show_building(const building *b) const override {
        return b->type == BUILDING_PHYSICIAN;
    }
};

city_overlay_physician g_city_overlay_physician;

const city_overlay* city_overlay_for_physician(void) {
    return &g_city_overlay_physician;
}

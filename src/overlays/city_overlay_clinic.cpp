#include "city_overlay_clinic.h"

#include "city_overlay.h"
#include "grid/property.h"
#include "grid/building.h"
#include "graphics/elements/tooltip.h"

static int get_column_height_clinic(const building* b) {
    return b->house_size && b->subtype.house_level
             ? b->data.house.clinic
                ? b->data.house.clinic / 10
                : 1
             : NO_COLUMN;
}

static int get_tooltip_clinic(tooltip_context* c, const building* b) {
    if (b->data.house.clinic <= 0)
        return 35;
    else if (b->data.house.clinic >= 80)
        return 36;
    else if (b->data.house.clinic >= 20)
        return 37;
    else {
        return 38;
    }
}

struct city_overlay_clinic : public city_overlay {
    city_overlay_clinic() {
        type = OVERLAY_CLINIC;
        column_type = COLUMN_TYPE_POSITIVE;

        get_column_height = get_column_height_clinic;
        get_tooltip_for_building = get_tooltip_clinic;
    }

    bool show_figure(const figure* f) const override {
        return f->type == FIGURE_DOCTOR;
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
        return b->type == BUILDING_APOTHECARY;
    }
};

city_overlay_clinic g_city_overlay_clinic;

const city_overlay* city_overlay_for_clinic(void) {
    return &g_city_overlay_clinic;
}

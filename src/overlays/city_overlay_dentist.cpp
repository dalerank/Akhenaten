#include "city_overlay_dentist.h"

#include "city_overlay.h"
#include "city/constants.h"
#include "grid/property.h"
#include "grid/building.h"

static int get_column_height_dentist(const building* b) {
    return b->house_size && b->data.house.dentist ? b->data.house.dentist / 10 : NO_COLUMN;
}

static int get_tooltip_dentist(tooltip_context* c, const building* b) {
    if (b->data.house.dentist <= 0)
        return 8;
    else if (b->data.house.dentist >= 80)
        return 9;
    else if (b->data.house.dentist >= 20)
        return 10;
    else {
        return 11;
    }
}

struct city_overlay_dentist : public city_overlay {
    city_overlay_dentist() {
        type = OVERLAY_DENTIST;
        column_type = COLUMN_TYPE_POSITIVE;

        get_column_height = get_column_height_dentist;
        get_tooltip_for_building = get_tooltip_dentist;
    }

    bool show_figure(const figure* f) const override {
        return f->type == FIGURE_DENTIST;
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
        return b->type == BUILDING_DENTIST;
    }
};

city_overlay_dentist g_city_overlay_dentist;

const city_overlay* city_overlay_for_dentist(void) {
    return &g_city_overlay_dentist;
}
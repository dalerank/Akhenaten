#include "city_overlay_barber.h"

#include "city_overlay.h"
#include "city/constants.h"
#include "grid/property.h"
#include "grid/building.h"
#include "building/building.h"
#include "graphics/elements/tooltip.h"

static int get_column_height_barber(const building* b) {
    return b->house_size && b->data.house.barber ? b->data.house.barber / 10 : NO_COLUMN;
}

static int get_tooltip_barber(tooltip_context* c, const building* b) {
    if (b->data.house.barber <= 0)
        return 31;
    else if (b->data.house.barber >= 80)
        return 32;
    else if (b->data.house.barber < 20)
        return 33;
    else {
        return 34;
    }
}

struct city_overlay_barber : public city_overlay {
    city_overlay_barber() {
        type = OVERLAY_BARBER;
        column_type = COLUMN_TYPE_POSITIVE;

        get_column_height = get_column_height_barber;
        get_tooltip_for_building = get_tooltip_barber;
    }

    bool show_figure(const figure* f) const override {
        return f->type == FIGURE_BARBER;
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

city_overlay_barber g_city_overlay_barber;

const city_overlay* city_overlay_for_barber(void) {
    return &g_city_overlay_barber;
}
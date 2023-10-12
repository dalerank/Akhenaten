#include "city_overlay_courthouse.h"

#include "city_overlay.h"
#include "building/model.h"
#include "game/state.h"
#include "grid/building.h"
#include "grid/property.h"
#include "figure/figure.h"

static int get_column_height_courthouse(const building* b) {
    if (b->house_size) {
        if (b->data.house.magistrate) {
            return b->data.house.magistrate / 10;
        }
        return 0;
    }

    return NO_COLUMN;
}

static int get_tooltip_courthouse(tooltip_context* c, const building* b) {
    if (b->data.house.magistrate <= 0) {
        return 158;
    } else if (b->data.house.magistrate <= 33) {
        return 161;
    } else if (b->data.house.magistrate <= 66) {
        return 160;
    } else {
        return 159;
    }
}

struct city_overlay_courthouse : public city_overlay {
    city_overlay_courthouse() {
        type = OVERLAY_COUTHOUSE;
        column_type = COLUMN_TYPE_WATER_ACCESS;

        get_column_height = get_column_height_courthouse;
        get_tooltip_for_building = get_tooltip_courthouse;
    }

    bool show_figure(const figure* f) const override {
        return f->type == FIGURE_MAGISTRATE;
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

    bool show_building(const building* b) const override {
        return b->type == BUILDING_COURTHOUSE;
    }
};

city_overlay_courthouse g_city_overlay_courthouse;

const city_overlay* city_overlay_for_courthouse(void) {
    return &g_city_overlay_courthouse;
}
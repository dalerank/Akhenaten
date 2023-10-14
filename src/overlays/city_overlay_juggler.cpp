#include "city_overlay_juggler.h"

#include "city_overlay.h"
#include "grid/property.h"
#include "grid/building.h"
#include "graphics/elements/tooltip.h"
#include "figure/figure.h"

static int get_column_height_juggler(const building* b) {
    if (b->house_size) {
        if (b->data.house.juggler || b->data.house.bandstand_juggler) {
            return std::max<int>(b->data.house.juggler, b->data.house.bandstand_juggler) / 10;
        }
    }
    
    return NO_COLUMN;
}

static int get_tooltip_juggler(tooltip_context* c, const building* b) {
    if (b->data.house.juggler <= 0)
        return 75;
    else if (b->data.house.juggler >= 80)
        return 76;
    else if (b->data.house.juggler >= 20)
        return 77;
    else {
        return 78;
    }
}

struct city_overlay_booth : public city_overlay {
    city_overlay_booth() {
        type = OVERLAY_BOOTH;
        column_type = COLUMN_TYPE_POSITIVE;

        get_column_height = get_column_height_juggler;
        get_tooltip_for_building = get_tooltip_juggler;
    }

    bool show_figure(const figure* f) const override {
        return f->type == FIGURE_JUGGLER;
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
        return b->type == BUILDING_JUGGLER_SCHOOL || b->type == BUILDING_BOOTH;
    }
};

city_overlay_booth g_city_overlay_booth;

city_overlay* city_overlay_for_booth() {
    return &g_city_overlay_booth;
}

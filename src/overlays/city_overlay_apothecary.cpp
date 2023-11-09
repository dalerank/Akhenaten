#include "city_overlay_apothecary.h"

#include "city_overlay.h"
#include "city/constants.h"
#include "grid/property.h"
#include "grid/building.h"
#include "building/building.h"
#include "graphics/elements/tooltip.h"
#include "figure/figure.h"

static int get_column_height_apothecary(const building* b) {
    return b->house_size && b->subtype.house_level > 0
                    ? b->data.house.apothecary / 10 
                    : NO_COLUMN;
}

static int get_tooltip_apothecary(tooltip_context* c, const building* b) {
    if (b->data.house.apothecary <= 0)
        return 31;
    else if (b->data.house.apothecary >= 80)
        return 32;
    else if (b->data.house.apothecary < 20)
        return 33;
    else {
        return 34;
    }
}

struct city_overlay_apothecary : public city_overlay {
    city_overlay_apothecary() {
        type = OVERLAY_APOTHECARY;
        column_type = COLUMN_TYPE_POSITIVE;

        get_column_height = get_column_height_apothecary;
        get_tooltip_for_building = get_tooltip_apothecary;
    }

    bool show_figure(const figure* f) const override {
        return f->type == FIGURE_HERBALIST;
    }

    void draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const override {
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

    bool show_building(const building *b) const override {
        return b->type == BUILDING_APOTHECARY;
    }
};

city_overlay_apothecary g_city_overlay_apothecary;

city_overlay* city_overlay_for_apothecary() {
    return &g_city_overlay_apothecary;
}
#include "city_overlay_pavilion.h"

#include "game/state.h"
#include "grid/property.h"
#include "city_overlay.h"
#include "grid/building.h"
#include "figure/figure.h"

static int get_column_height_colosseum(const building* b) {
    return b->house_size && b->data.house.colosseum_gladiator ? b->data.house.colosseum_gladiator / 10 : NO_COLUMN;
}

static int get_tooltip_colosseum(tooltip_context* c, const building* b) {
    if (b->data.house.colosseum_gladiator <= 0) {
        return 83;
    } else if (b->data.house.colosseum_gladiator >= 80) {
        return 84;
    } else if (b->data.house.colosseum_gladiator >= 20) {
        return 85;
    } else {
        return 86;
    }
}

struct city_overlay_pavilion : public city_overlay {
    city_overlay_pavilion() {
        type = OVERLAY_PAVILION;
        column_type = COLUMN_TYPE_WATER_ACCESS;

        get_column_height = get_column_height_colosseum;
        get_tooltip_for_building = get_tooltip_colosseum;
    }

    bool show_figure(const figure* f) const override {
        if (f->type == FIGURE_MUSICIAN) {
            return ((figure *)f)->get_entertainment_building()->type == BUILDING_PAVILLION;
        } else if (f->type == FIGURE_DANCER) {
            return 1;
        }

        return 0;
    }

    void draw_custom_top(vec2i pixel, tile2i point, view_context &ctx) const override {
        int grid_offset = point.grid_offset();
        if (!map_property_is_draw_tile(grid_offset)) {
            return;
        }

        if (map_building_at(grid_offset)) {
            city_with_overlay_draw_building_top(pixel, point, ctx);
        }
    }

    bool show_building(const building *b) const override {
        return (b->type == BUILDING_CONSERVATORY || b->type == BUILDING_DANCE_SCHOOL || b->type == BUILDING_PAVILLION);
    }
};

city_overlay_pavilion g_city_overlay_pavilion;

city_overlay* city_overlay_for_pavilion() {
    return &g_city_overlay_pavilion;
}
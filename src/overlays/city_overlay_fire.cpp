#include "city_overlay_fire.h"

#include "city_overlay.h"
#include "building/model.h"
#include "game/state.h"
#include "grid/building.h"
#include "grid/property.h"

static int get_column_height_fire(const building* b) {
    auto model = model_get_building(b->type);

    if (b->prev_part_building_id || !model->fire_risk)
        return NO_COLUMN;

    if (b->type == BUILDING_HOUSE_VACANT_LOT || b->type == BUILDING_GARDENS
        || b->type == BUILDING_BANDSTAND || b->type == BUILDING_BOOTH) {
        return NO_COLUMN;
    }

    return b->fire_risk / 100;
}

static int get_tooltip_fire(tooltip_context* c, const building* b) {
    if (b->fire_risk <= 0)
        return 46;
    else if (b->fire_risk <= 200)
        return 47;
    else if (b->fire_risk <= 400)
        return 48;
    else if (b->fire_risk <= 600)
        return 49;
    else if (b->fire_risk <= 800)
        return 50;
    else
        return 51;
}

struct city_overlay_fire : public city_overlay {
    city_overlay_fire() {
        type = OVERLAY_FIRE;
        column_type = COLUMN_TYPE_RISK;

        get_column_height = get_column_height_fire;
        get_tooltip_for_building = get_tooltip_fire;
    }

    bool show_figure(const figure* f) const override {
        return f->type == FIGURE_FIREMAN;
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
        return b->type == BUILDING_FIREHOUSE || b->type == BUILDING_BURNING_RUIN || b->type == BUILDING_FESTIVAL_SQUARE;
    }
};

city_overlay_fire g_city_overlay_fire;

const city_overlay* city_overlay_for_fire(void) {
    return &g_city_overlay_fire;
}

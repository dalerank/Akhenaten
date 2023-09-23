#include "city_overlay_fire.h"

#include "city_overlay.h"
#include "building/model.h"
#include "game/state.h"
#include "grid/building.h"
#include "grid/property.h"
#include "figure/figure.h"

static int get_column_height_damage(const building* b) {
    auto model = model_get_building(b->type);
    if (b->prev_part_building_id || !model->damage_risk)
        return NO_COLUMN;
    return b->damage_risk / 100;
}

static int get_tooltip_damage(tooltip_context* c, const building* b) {
    if (b->damage_risk <= 0)
        return 52;
    else if (b->damage_risk <= 40)
        return 53;
    else if (b->damage_risk <= 80)
        return 54;
    else if (b->damage_risk <= 120)
        return 55;
    else if (b->damage_risk <= 160)
        return 56;
    else {
        return 57;
    }
}

struct city_overlay_damage : public city_overlay {
    city_overlay_damage() {
        type = OVERLAY_DAMAGE;
        column_type = COLUMN_TYPE_RISK;

        get_column_height = get_column_height_damage;
        get_tooltip_for_building = get_tooltip_damage;
    }

    bool show_figure(const figure* f) const override {
        return f->type == FIGURE_ENGINEER;
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
        return b->type == BUILDING_ENGINEERS_POST || b->type == BUILDING_FESTIVAL_SQUARE;
    }
};

city_overlay_damage g_city_overlay_damage;

const city_overlay* city_overlay_for_damage(void) {
    return &g_city_overlay_damage;
}
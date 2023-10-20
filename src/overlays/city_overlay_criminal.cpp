#include "city_overlay_criminal.h"

#include "city_overlay.h"

#include "building/model.h"
#include "building/building.h"
#include "figure/figure.h"
#include "grid/property.h"
#include "grid/building.h"
#include "game/state.h"


static int get_column_height_crime(const building* b) {
    if (b->house_size && b->house_population > 0) {
        int crime = b->house_criminal_active;
        return crime / 10;
    }
    return NO_COLUMN;
}

static int get_tooltip_crime(tooltip_context* c, const building* b) {
    if (b->house_population <= 0) {
        return 63;
    }

    if (b->house_criminal_active >= 80)
        return 63;
    else if (b->house_criminal_active >= 60)
        return 62;
    else if (b->house_criminal_active >= 40)
        return 61;
    else if (b->house_criminal_active >= 30)
        return 60;
    else if (b->house_criminal_active >= 20)
        return 59;
    else {
        return 58;
    }
}

struct city_overlay_crime : public city_overlay {
    city_overlay_crime() {
        type = OVERLAY_CRIME;
        column_type = COLUMN_TYPE_RISK;

        get_column_height = get_column_height_crime;
        get_tooltip_for_building = get_tooltip_crime;
    }

    bool show_figure(const figure* f) const override {
        return f->type == FIGURE_POLICEMAN || f->type == FIGURE_PROTESTER || f->type == FIGURE_CRIMINAL
            || f->type == FIGURE_RIOTER;
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

    bool show_building(const building* b) const override {
        return b->type == BUILDING_POLICE_STATION || b->type == BUILDING_FESTIVAL_SQUARE;
    }
};

city_overlay_crime g_city_overlay_crime;

city_overlay* city_overlay_for_crime() {
    return &g_city_overlay_crime;
}

#include "city_overlay_fire.h"

#include "city_overlay.h"
#include "building/model.h"
#include "game/state.h"
#include "grid/building.h"
#include "grid/property.h"
#include "figure/figure.h"

static int get_column_height_labor(const building* b) {
    if (b->state == BUILDING_STATE_VALID) {
        return NO_COLUMN;
    }

    int need_workers = model_get_building(b->type)->laborers;
    if (!need_workers) {
        return NO_COLUMN;
    }

    int percentage = ((building*)b)->worker_percentage();
    return 10 - percentage / 10;
}

static int get_tooltip_labor(tooltip_context* c, const building* b) {
    int percentage = ((building*)b)->worker_percentage();
    if (percentage <= 0)
        return 52;
    else if (percentage <= 20)
        return 53;
    else if (percentage <= 40)
        return 54;
    else if (percentage <= 60)
        return 55;
    else if (percentage <= 80)
        return 56;
    else {
        return 57;
    }
}

struct city_overlay_labor : public city_overlay {
    city_overlay_labor() {
        type = OVERLAY_LABOR;
        column_type = COLUMN_TYPE_RISK;

        get_column_height = get_column_height_labor;
        get_tooltip_for_building = get_tooltip_labor;
    }

    bool show_figure(const figure* f) const override {
        if (f->type == FIGURE_LABOR_SEEKER) {
            return ((figure *)f)->home()->show_on_problem_overlay;
        }

        return false;
    }

    void draw_custom_top(vec2i pixel, map_point point) const override {
        int grid_offset = point.grid_offset();
        if (!map_property_is_draw_tile(grid_offset)) {
            return;
        }

        if (map_building_at(grid_offset)) {
            city_with_overlay_draw_building_top(pixel, point);
        }
    }

    bool show_building(const building* b) const override {
        if (b->type == BUILDING_WORK_CAMP) {
            return true;
        }

        if (b->state == BUILDING_STATE_VALID) {
            if (b->show_on_problem_overlay)
                return true;

            int need_workers = model_get_building(b->type)->laborers;
            if (need_workers > 0 && b->num_workers <= 0)
                return true;
        }

        return false;
    }
};

city_overlay_labor g_city_overlay_labor;

const city_overlay* city_overlay_for_labor(void) {
    return &g_city_overlay_labor;
}
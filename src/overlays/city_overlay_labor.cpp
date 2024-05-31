#include "city_overlay_fire.h"

#include "building/model.h"
#include "game/state.h"
#include "grid/building.h"
#include "grid/property.h"
#include "figure/figure.h"
#include "city_overlay_labor.h"

city_overlay_labor g_city_overlay_labor;

city_overlay* city_overlay_for_labor() {
    return &g_city_overlay_labor;
}

city_overlay_labor::city_overlay_labor() {
    type = OVERLAY_LABOR;
    column_type = COLUMN_TYPE_RISK;
}

bool city_overlay_labor::show_figure(const figure *f) const {
    if (f->type == FIGURE_LABOR_SEEKER) {
        return ((figure *)f)->home()->show_on_problem_overlay;
    }

    return false;
}

int city_overlay_labor::get_column_height(const building *b) const {
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

int city_overlay_labor::get_tooltip_for_building(tooltip_context *c, const building *b) const {
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

void city_overlay_labor::draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const {
    if (!map_property_is_draw_tile(point)) {
        return;
    }

    if (map_building_at(point)) {
        city_overlay::draw_building_top(pixel, point, ctx);
    }
}

bool city_overlay_labor::show_building(const building *b) const {
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

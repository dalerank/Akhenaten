#include "city_overlay.h"

#include "building/building.h"
#include "game/state.h"
#include "grid/building.h"
#include "grid/property.h"
#include "figure/figure.h"

struct city_overlay_labor : public city_overlay_t<OVERLAY_LABOR> {
    virtual bool show_figure(const figure *f) const override {
        if (f->type == FIGURE_LABOR_SEEKER) {
            return ((figure *)f)->home()->show_on_problem_overlay;
        }

        return false;
    }
    virtual int get_column_height(const building *b) const override;
    virtual xstring get_tooltip_for_building(tooltip_context *c, const building *b) override;
    virtual bool show_building(const building *b) const override;
};

city_overlay_labor g_city_overlay_labor;

int city_overlay_labor::get_column_height(const building *b) const {
    if (!b->is_valid()) {
        return COLUMN_TYPE_NONE;
    }

    if (!b->max_workers) {
        return COLUMN_TYPE_NONE;
    }

    int percentage = b->worker_percentage();
    return 10 - percentage / 10;
}

xstring city_overlay_labor::get_tooltip_for_building(tooltip_context *c, const building *b) {
    int percentage = b->worker_percentage();
    if (percentage <= 0)
        return ui::str(66, 52);
    else if (percentage <= 20)
        return ui::str(66, 53);
    else if (percentage <= 40)
        return ui::str(66, 54);
    else if (percentage <= 60)
        return ui::str(66, 55);
    else if (percentage <= 80)
        return ui::str(66, 56);

    return ui::str(66, 57);
}

bool city_overlay_labor::show_building(const building *b) const {
    if (b->type == BUILDING_WORK_CAMP) {
        return true;
    }

    if (b->is_valid()) {
        if (b->show_on_problem_overlay) {
            return true;
        }

        if (b->max_workers > 0 && b->num_workers <= 0) {
            return true;
        }
    }

    return false;
}



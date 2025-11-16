#include "city_overlay.h"

#include "city/constants.h"
#include "grid/property.h"
#include "grid/building.h"
#include "building/building.h"
#include "graphics/elements/tooltip.h"
#include "building/building_house.h"
#include "figure/figure.h"

struct city_overlay_labor_access : public city_overlay_t<OVERLAY_LABOR_ACCESS> {
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

city_overlay_labor_access g_city_overlay_labor_access;

xstring city_overlay_labor_access::get_tooltip_for_building(tooltip_context *c, const building *b) {
    return ui::str(66, 57);
}

int city_overlay_labor_access::get_column_height(const building *b) const {
    if (!b->is_valid()) {
        return COLUMN_TYPE_NONE;
    }

    if (b->dcast<building_house>()) {
        return COLUMN_TYPE_NONE;
    }

    const auto &params = b->dcast()->current_params();
    if (!params.min_houses_coverage) {
        return COLUMN_TYPE_NONE;
    }

    int percentage = calc_percentage<int>(b->houses_covered, params.min_houses_coverage);
    return std::clamp(percentage / 10, 0, 10);
}

bool city_overlay_labor_access::show_building(const building *b) const {
    if (b->dcast<building_house>()) {
        return false;
    }

    const auto &params = b->dcast()->current_params();
    if (!params.min_houses_coverage) {
        return false;
    }

    if (b->is_valid()) {
        int percentage = calc_percentage<int>(b->houses_covered, params.min_houses_coverage);

        if (percentage < 50) {
            return true;
        }
    }

    return false;
}

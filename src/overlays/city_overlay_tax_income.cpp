#include "city_overlay_tax_income.h"

#include "building/building.h"
#include "graphics/elements/tooltip.h"
#include "core/calc.h"
#include "city/finance.h"
#include "grid/property.h"
#include "grid/building.h"
#include "figure/figure.h"

city_overlay_tax_income g_city_overlay_tax_income;

city_overlay* city_overlay_for_tax_income() {
    return &g_city_overlay_tax_income;
}

inline city_overlay_tax_income::city_overlay_tax_income() {
    type = OVERLAY_TAX_INCOME;
    column_type = COLUMN_TYPE_WATER_ACCESS;
}

inline bool city_overlay_tax_income::show_figure(const figure *f) const {
    return f->type == FIGURE_TAX_COLLECTOR;
}

inline void city_overlay_tax_income::draw_custom_top(vec2i pixel, map_point point, painter &ctx) const {
    int grid_offset = point.grid_offset();
    if (!map_property_is_draw_tile(grid_offset)) {
        return;
    }

    if (map_building_at(grid_offset)) {
        city_overlay::draw_building_top(pixel, point, ctx);
    }
}

int city_overlay_tax_income::get_column_height(const building *b) const {
    if (b->house_size) {
        int pct = calc_adjust_with_percentage(b->tax_income_or_storage / 2, city_finance_tax_percentage());
        if (pct > 0) {
            return pct / 25;
        }
    }

    return NO_COLUMN;
}

int city_overlay_tax_income::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    int denarii = calc_adjust_with_percentage(b->tax_income_or_storage / 2, city_finance_tax_percentage());
    if (denarii > 0) {
        c->has_numeric_prefix = 1;
        c->numeric_prefix = denarii;
        return 45;
    } else if (b->house_tax_coverage > 0) {
        return 44;
    } else {
        return 43;
    }
}

inline bool city_overlay_tax_income::show_building(const building *b) const {
    return b->type == BUILDING_TAX_COLLECTOR || b->type == BUILDING_TAX_COLLECTOR_UPGRADED || ((building *)b)->is_palace();
}

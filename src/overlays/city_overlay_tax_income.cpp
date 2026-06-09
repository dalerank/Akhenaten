#include "city_overlay_tax_income.h"

#include "building/building_house.h"
#include "graphics/elements/tooltip.h"
#include "core/calc.h"
#include "city/city.h"
#include "grid/property.h"
#include "grid/building.h"
#include "figure/figure.h"

city_overlay_tax_income g_city_overlay_tax_income;

int city_overlay_tax_income::get_column_height(const building *b) const {
    auto house = ((building *)b)->dcast_house();
    if (!house) {
        return COLUMN_TYPE_NONE;
    }

    if (house->house_population()) {
        auto &housed = house->runtime_data();
        int pct = calc_adjust_with_percentage<int>(housed.tax_income_or_storage / 2, g_city.finance.tax_percentage);
        return pct / 10;
    }

    return COLUMN_TYPE_NONE;
}

void city_overlay_tax_income::get_tooltip_for_building(tooltip_context *c, const building *b, xstring &tooltip){
    auto house = ((building*)b)->dcast_house();
    if (!house) {
        tooltip = ui::str(66, 43);
        return;
    }

    auto &housed = house->runtime_data();
    int denarii = calc_adjust_with_percentage<int>(housed.tax_income_or_storage / 2, g_city.finance.tax_percentage);
    if (denarii > 0) {
        c->has_numeric_prefix = 1;
        c->numeric_prefix = denarii;
        tooltip = ui::str(66, 45);
        return;
    } else if (housed.tax_coverage > 0) {
        tooltip = ui::str(66, 44);
        return;
    } else {
        tooltip = ui::str(66, 43);
        return;
    }
}
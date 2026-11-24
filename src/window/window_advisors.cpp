#include "window_advisors.h"
#include "city/city_health.h"

#include "city/constants.h"
#include "city/coverage.h"
#include "city/city_finance.h"
#include "city/city.h"
#include "city/city_taxes.h"
#include "city/city_labor.h"
#include "city/city_migration.h"
#include "city/city_resource.h"
#include "figure/formation.h"
#include "js/js_game.h"

void window_advisors_prepare_opening() {
    city_labor().allocate_workers();

    g_city.finance_sys().estimate_wages();
    g_city.finance_sys().update_interest();
    city_taxes().update_estimate();
    g_city.finance_sys().calculate_totals();

    g_city.migration_sys().determine_reason();

    g_city.houses_calculate_culture_demands();
    g_city.avg_coverage.update();
    city_health().update_month();

    g_city.resource.calculate_food_stocks_and_supply_wheat();
    g_formations.calculate_figures();
}

ANK_FUNCTION(window_advisors_prepare_opening)

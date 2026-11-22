#include "window_advisors.h"

#include "city/constants.h"
#include "city/coverage.h"
#include "city/city_finance.h"
#include "city/city.h"
#include "city/city_labor.h"
#include "city/city_migration.h"
#include "city/city_resource.h"
#include "figure/formation.h"
#include "js/js_game.h"

void window_advisors_prepare_opening() {
    g_city.labor.allocate_workers();

    finance_system::estimate_wages(g_city.finance, g_city.finance_ctx());
    finance_system::update_interest(g_city.finance);
    finance_system::update_estimate_taxes(g_city.finance, g_city.finance_ctx());
    finance_system::calculate_totals(g_city.finance);

    g_city.migration.determine_reason();

    g_city.houses_calculate_culture_demands();
    g_city.avg_coverage.update();
    g_city.health.update_month();

    g_city.resource.calculate_food_stocks_and_supply_wheat();
    g_formations.calculate_figures();
}

ANK_FUNCTION(window_advisors_prepare_opening)

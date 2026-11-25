#include "window_advisors.h"
#include "city/city_houses.h"
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

    city_finance().estimate_wages();
    city_finance().update_interest();
    city_taxes().update_estimate();
    city_finance().calculate_totals();

    city_migration().determine_reason();

    city_houses().calculate_culture_demands();
    city_avg_coverage().update();
    city_health().update_month();

    city_resource().calculate_food_stocks_and_supply_wheat();
    g_formations.calculate_figures();
}

ANK_FUNCTION(window_advisors_prepare_opening)

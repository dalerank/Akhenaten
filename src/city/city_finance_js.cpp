#include "city/city_finance.h"

#include "city/city.h"
#include "core/profiler.h"
#include "js/js_game.h"
#include "js/js_global_object.h"

void ank_global_obj_bind_field(js_State *J, js_StringNode name, city_finance_t::treasury_t *ptr) {
    js_register_bound_int_property(J, name, &ptr->value);
}

ANK_GLOBAL_OBJECT(g_city.finance, __city_finance,
    treasury,
    wages,
    wages_kingdome,
    tax_percentage,
    estimated_wages,
    wages_so_far,
    cheated_money,
    tribute_not_paid_last_year,
    wage_rate_paid_this_year,
    wage_rate_paid_last_year);

std::optional<bvariant> __city_finance_income(pcstr property, bool this_year) {
    auto &year = this_year ? g_city.finance.this_year.income : g_city.finance.last_year.income;
    return archive_helper::get(year, property, true);
}
ANK_FUNCTION_2(__city_finance_income)

std::optional<bvariant> __city_finance_expenses(pcstr property, bool this_year) {
    auto &year = this_year ? g_city.finance.this_year.expenses : g_city.finance.last_year.expenses;
    return archive_helper::get(year, property, true);
}
ANK_FUNCTION_2(__city_finance_expenses)

std::optional<bvariant> __city_finance_overview(pcstr property, bool this_year) {
    auto &year = this_year ? g_city.finance.this_year : g_city.finance.last_year;
    return archive_helper::get(year, property, true);
}
ANK_FUNCTION_2(__city_finance_overview)

void __city_finance_update_estimate_taxes() {
    g_city.finance.update_estimate_taxes();
}
ANK_FUNCTION(__city_finance_update_estimate_taxes)

void __city_finance_calculate_totals() {
    g_city.finance.calculate_totals();
}
ANK_FUNCTION(__city_finance_calculate_totals)

std::optional<bvariant> __city_get_taxes_property(pcstr property) {
    return archive_helper::get(g_city.taxes, property, true);
}
ANK_FUNCTION_1(__city_get_taxes_property)

bool __city_finance_is_out_of_money() {
    return g_city.finance.is_out_of_money();
}
ANK_FUNCTION(__city_finance_is_out_of_money)

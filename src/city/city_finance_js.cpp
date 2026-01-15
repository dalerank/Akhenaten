#include "city_finance.h"

#include "city/city.h"
#include "js/js_game.h"

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

void __city_finance_set_tax_percentage(int tax) {
    g_city.finance.change_tax(tax);
}
ANK_FUNCTION_1(__city_finance_set_tax_percentage)

std::optional<bvariant> __city_get_finance_property(pcstr property) {
    return archive_helper::get(g_city.finance, property, true);
}
ANK_FUNCTION_1(__city_get_finance_property)

std::optional<bvariant> __city_get_taxes_property(pcstr property) {
    return archive_helper::get(g_city.taxes, property, true);
}
ANK_FUNCTION_1(__city_get_taxes_property)


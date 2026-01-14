#include "city_finance.h"

#include "city/city.h"
#include "js/js_game.h"

int __city_finance_income(int type) {
    switch (type) {
    case e_finance_value_gold_delivered: return g_city.finance.this_year.income.gold_delivered;
    }

    return 0;
}
ANK_FUNCTION_1(__city_finance_income)

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


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

int __city_finance_treasury() { return g_city.finance.treasury; }
ANK_FUNCTION(__city_finance_treasury)
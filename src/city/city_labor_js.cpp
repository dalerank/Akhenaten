#include "city/city_labor.h"

#include "city/city.h"
#include "js/js_game.h"
#include "js/js_global_object.h"

void __city_labor_set_priority(int category, int new_priority) {
    g_city.labor.set_priority(category, new_priority);
}
ANK_FUNCTION_2(__city_labor_set_priority)

int __city_labor_max_selectable_priority(int category) {
    return g_city.labor.max_selectable_priority(category);
}
ANK_FUNCTION_1(__city_labor_max_selectable_priority)

ANK_GLOBAL_OBJECT(g_city.labor, __city_labor,
    workers_available,
    workers_employed,
    workers_unemployed,
    workers_needed,
    unemployment_percentage_for_goverment,
    unemployment_percentage);

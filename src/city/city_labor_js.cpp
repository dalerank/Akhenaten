#include "city/city_labor.h"

#include "city/city.h"
#include "js/js_game.h"
#include "js/js_global_object.h"

ANK_GLOBAL_OBJECT(g_city.labor, __city_labor,
    workers_available,
    workers_employed,
    workers_unemployed,
    workers_needed,
    unemployment_percentage_for_goverment,
    unemployment_percentage);

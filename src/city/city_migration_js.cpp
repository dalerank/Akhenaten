#include "city_migration.h"
#include "city/city.h"
#include "js/js_game.h"

void __migration_set_population_cap(xstring reason, int cap) {
    g_city.migration.set_migration_cap(reason, cap);
}
ANK_FUNCTION_2(__migration_set_population_cap)

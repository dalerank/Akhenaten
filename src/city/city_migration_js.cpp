#include "city_migration.h"
#include "city/city.h"
#include "js/js_game.h"

void set_population_cap(int cap) {
    g_city.migration.population_cap = cap;
}
ANK_FUNCTION_1(set_population_cap)

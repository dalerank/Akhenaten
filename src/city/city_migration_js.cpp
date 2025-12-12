#include "city_migration.h"
#include "city/city.h"
#include "js/js_game.h"

void __migration_set_population_cap(xstring reason, int cap) {
    g_city.migration.set_migration_cap(reason, cap);
}
ANK_FUNCTION_2(__migration_set_population_cap)

void ANK_FUNCTION_UNIFIED(__migration_set_unemployments_cap)(const bvariant_map &args) {
    g_city.migration.set_unemployments_cap(args.s("reason"), args.n("min"), args.n("max"));
}

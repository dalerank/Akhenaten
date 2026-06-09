#include "city_migration.h"

#include "city/city.h"
#include "js/js_game.h"
#include "core/profiler.h"

ANK_GLOBAL_OBJECT(g_city.migration, __city_migration,
    invading_cap,
    migration_cap,
    percentage_by_sentiment,
    percentage_by_unemployments,
    emigration_message_shown,
    newcomers,
    percentage,
    no_immigration_cause,
    refused_immigrants_today,
    emigrated_today,
    immigrated_today,
    emigration_queue_size,
    immigration_queue_size,
    immigration_duration,
    emigration_amount_per_batch,
    emigration_duration,
    immigration_amount_per_batch,
    nobles_leave_city_this_year);

void __migration_set_population_cap(xstring reason, int cap) {
    g_city.migration.set_migration_cap(reason, cap);
}
ANK_FUNCTION_2(__migration_set_population_cap)

void ANK_FUNCTION_UNIFIED(__migration_set_unemployments_cap)(const bvariant_map &args) {
    g_city.migration.set_unemployments_cap(args.s("reason"), args.n("min"), args.n("max"));
}

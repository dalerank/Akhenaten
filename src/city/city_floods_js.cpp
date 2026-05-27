#include "city/city_floods.h"

#include "core/profiler.h"
#include "js/js_game.h"
#include "js/js_global_object.h"

int __city_floods_expected_quality() {
    return g_floods.expected_quality();
}
ANK_FUNCTION(__city_floods_expected_quality)

int __city_floods_expected_month() {
    return g_floods.expected_month();
}
ANK_FUNCTION(__city_floods_expected_month)

ANK_GLOBAL_OBJECT(g_floods, __city_floods,
    state,
    has_floodplains,
    flood_progress,
    flood_progress_target,
    floodplain_width,
    quality_current,
    quality_next,
    quality_last,
    season,
    duration);

#include "city/city_floods.h"

#include "core/profiler.h"
#include "grid/floodplain.h"
#include "grid/water.h"
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

void __map_water_cache_river_tiles() {
    map_water_cache_river_tiles();
}
ANK_FUNCTION(__map_water_cache_river_tiles)

void __map_floodplain_rebuild_shores() {
    map_floodplain_rebuild_shores();
}
ANK_FUNCTION(__map_floodplain_rebuild_shores)

void __map_floodplain_update_inundation(int leading_row, int is_flooding) {
    map_floodplain_update_inundation(leading_row, is_flooding, g_floods.fticks);
}
ANK_FUNCTION_2(__map_floodplain_update_inundation)

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
    season_initial,
    duration,
    fticks);

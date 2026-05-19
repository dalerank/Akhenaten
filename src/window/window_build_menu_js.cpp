#include "building/building.h"
#include "building/building_temple_complex.h"
#include "building/construction/build_planner.h"
#include "graphics/window.h"
#include "city/city.h"
#include "city/buildings.h"
#include "graphics/elements/lang_text.h"
#include "js/js_game.h"
#include "scenario/scenario.h"
#include "widget/widget_city.h"
#include "game/game_config.h"

void __ui_screen_city_clear_current_tile() {
    g_screen_city.clear_current_tile();
}
ANK_FUNCTION(__ui_screen_city_clear_current_tile)

void __ui_city_planner_reset() {
    g_city_planner.reset();
}
ANK_FUNCTION(__ui_city_planner_reset)

bool __city_has_temple_complex() {
    return g_city.buildings.has_temple_complex();
}
ANK_FUNCTION(__city_has_temple_complex)

int __city_temple_complex_id() {
    return g_city.buildings.temple_complex_id();
}
ANK_FUNCTION(__city_temple_complex_id)

int __city_temple_complex_types_count() {
    return (int)g_city.buildings.temple_complex_types().size();
}
ANK_FUNCTION(__city_temple_complex_types_count)

int __city_temple_complex_type_at(int idx) {
    const auto types = g_city.buildings.temple_complex_types();
    return (idx >= 0 && idx < (int)types.size()) ? (int)types[idx] : 0;
}
ANK_FUNCTION_1(__city_temple_complex_type_at)
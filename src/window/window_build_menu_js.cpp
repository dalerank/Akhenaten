#include "building/building.h"
#include "building/building_temple_complex.h"
#include "building/construction/build_planner.h"
#include "graphics/window.h"
#include "city/city_temple_complexes.h"
#include "city/buildings.h"
#include "graphics/elements/lang_text.h"
#include "js/js_game.h"
#include "scenario/scenario.h"
#include "widget/widget_city.h"
#include "game/game_config.h"

ANK_GLOBAL_OBJECT(g_screen_city, __screen_city,
    capture_input,
    current_tile,
    selected_tile);

void __ui_city_planner_reset() {
    g_city_planner.reset();
}
ANK_FUNCTION(__ui_city_planner_reset)

bool __city_has_temple_complex() {
    return city_temple_complexes().has_any();
}
ANK_FUNCTION(__city_has_temple_complex)

int __city_temple_complex_id(int type) {
    if (type <= 0) {
        return city_temple_complexes().any_id();
    }
    return city_temple_complexes().id((e_building_type)type);
}
ANK_FUNCTION_1(__city_temple_complex_id)

int __city_temple_complex_types_count() {
    return (int)temple_complexes_system::types().size();
}
ANK_FUNCTION(__city_temple_complex_types_count)

int __city_temple_complex_type_at(int idx) {
    const auto types = temple_complexes_system::types();
    return (idx >= 0 && idx < (int)types.size()) ? (int)types[idx] : 0;
}
ANK_FUNCTION_1(__city_temple_complex_type_at)
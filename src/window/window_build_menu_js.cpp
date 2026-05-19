#include "building/building.h"
#include "building/building_static_params.h"
#include "building/building_temple_complex.h"
#include "building/construction/build_planner.h"
#include "graphics/window.h"
#include "city/city.h"
#include "city/buildings.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/ui.h"
#include "input/mouse.h"
#include "js/js_game.h"
#include "scenario/scenario.h"
#include "widget/widget_city.h"
#include "game/game_config.h"

#include <cstring>

void __ui_screen_city_clear_current_tile() {
    g_screen_city.clear_current_tile();
}
ANK_FUNCTION(__ui_screen_city_clear_current_tile)

void __ui_city_planner_reset() {
    g_city_planner.reset();
}
ANK_FUNCTION(__ui_city_planner_reset)

bool __ui_building_is_unique_built(int type) {
    const auto &params = building_static_params::get((e_building_type)type);
    if (!params.planner_update_rule.unique_building) {
        return false;
    }
    return g_city.buildings.count_total((e_building_type)type) > 0;
}
ANK_FUNCTION_1(__ui_building_is_unique_built)

int __ui_draw_build_menu_button(vec2i pos, vec2i size, int flags) {
    const bool is_underlying = g_window_manager.underlying_windows_redrawing > 0;
    flags |= is_underlying ? UiFlags_Readonly : UiFlags_None;

    auto &btn = ui::button("", pos, size,
        fonts_vec{ FONT_NORMAL_BLACK_ON_DARK, FONT_NORMAL_BLACK_ON_LIGHT },
        (UiFlags)flags);

    if (is_underlying) {
        return 0;
    }

    int lmb_click = 0;
    generic_buttons_handle_mouse(&mouse::ref(), vec2i{ 0, 0 }, &btn, 1, nullptr, &lmb_click);
    if (lmb_click) {
        return 1;
    }
    return btn.hovered ? 2 : 0;
}
ANK_FUNCTION_3(__ui_draw_build_menu_button)


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
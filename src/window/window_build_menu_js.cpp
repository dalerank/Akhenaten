#include "building/building.h"
#include "building/construction/build_planner.h"
#include "graphics/window.h"
#include "city/city.h"
#include "city/city_building_menu_ctrl.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/ui.h"
#include "input/mouse.h"
#include "js/js_game.h"
#include "widget/widget_city.h"

void __ui_screen_city_clear_current_tile() {
    g_screen_city.clear_current_tile();
}
ANK_FUNCTION(__ui_screen_city_clear_current_tile)

void __ui_city_planner_reset() {
    g_city_planner.reset();
}
ANK_FUNCTION(__ui_city_planner_reset)

void __ui_building_menu_update_temple_complexes() {
    g_building_menu_ctrl.update_temple_complexes();
}
ANK_FUNCTION(__ui_building_menu_update_temple_complexes)

int __ui_building_menu_next_index(int submenu, int index) {
    return g_building_menu_ctrl.next_index(submenu, index);
}
ANK_FUNCTION_2(__ui_building_menu_next_index)

int __ui_building_menu_item_type(int submenu, int index) {
    return g_building_menu_ctrl.type(submenu, index);
}
ANK_FUNCTION_2(__ui_building_menu_item_type)

bool __ui_building_menu_is_visible(int type) {
    return g_building_menu_ctrl.is_visible(type);
}
ANK_FUNCTION_1(__ui_building_menu_is_visible)

bool __ui_building_menu_is_submenu(int type) {
    return g_building_menu_ctrl.is_submenu(type);
}
ANK_FUNCTION_1(__ui_building_menu_is_submenu)

bool __ui_building_is_unique_built(int type) {
    const auto &params = building_static_params::get((e_building_type)type);
    if (!params.planner_update_rule.unique_building) {
        return false;
    }
    return g_city.buildings.count_total((e_building_type)type) > 0;
}
ANK_FUNCTION_1(__ui_building_is_unique_built)

int __ui_building_menu_cost(int type) {
    if (type == BUILDING_MENU_FORTS) {
        return 0;
    }
    return building_static_params::get((e_building_type)type).get_cost();
}
ANK_FUNCTION_1(__ui_building_menu_cost)

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

void __ui_text_abs(pcstr text, vec2i pos, int font) {
    ui::text_abs(text, pos, (e_font)font, 0);
}
ANK_FUNCTION_3(__ui_text_abs)

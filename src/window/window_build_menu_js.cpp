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

void __scenario_building_allow(int type, bool enabled) {
    scenario_building_allow((e_building_type)type, enabled);
}
ANK_FUNCTION_2(__scenario_building_allow)

bool __city_can_produce_resource(int resource) {
    return g_city.can_produce_resource((e_resource)resource);
}
ANK_FUNCTION_1(__city_can_produce_resource)

int __scenario_player_rank() {
    return scenario_property_player_rank();
}
ANK_FUNCTION(__scenario_player_rank)

bool __building_static_flag(int type, pcstr flag_name) {
    const auto &flags = building_static_params::get((e_building_type)type).flags;
    if (!strcmp(flag_name, "is_farm"))           return flags.is_farm;
    if (!strcmp(flag_name, "is_fort"))           return flags.is_fort;
    if (!strcmp(flag_name, "is_defense"))        return flags.is_defense;
    if (!strcmp(flag_name, "is_shrine"))         return flags.is_shrine;
    if (!strcmp(flag_name, "is_temple"))         return flags.is_temple;
    if (!strcmp(flag_name, "is_temple_complex")) return flags.is_temple_complex;
    if (!strcmp(flag_name, "is_guild"))          return flags.is_guild;
    if (!strcmp(flag_name, "is_beautification")) return flags.is_beautification;
    if (!strcmp(flag_name, "is_water_crossing")) return flags.is_water_crossing;
    if (!strcmp(flag_name, "is_monument"))       return flags.is_monument;
    if (!strcmp(flag_name, "is_education"))      return flags.is_education;
    if (!strcmp(flag_name, "is_extractor"))      return flags.is_extractor;
    if (!strcmp(flag_name, "is_harvester"))      return flags.is_harvester;
    if (!strcmp(flag_name, "is_workshop"))       return flags.is_workshop;
    return false;
}
ANK_FUNCTION_2(__building_static_flag)

int __building_type_max() {
    return BUILDING_MAX;
}
ANK_FUNCTION(__building_type_max)

bool __building_static_needs(int type, pcstr field) {
    const auto &needs = building_static_params::get((e_building_type)type).needs;
    if (!strcmp(field, "altar"))  return needs.altar;
    if (!strcmp(field, "oracle")) return needs.oracle;
    return false;
}
ANK_FUNCTION_2(__building_static_needs)

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

bool __city_temple_complex_has_upgrade(int id, int upgrade) {
    auto *b = building_get_ex<building_temple_complex>(id);
    return b ? b->has_upgrade((e_temple_compex_upgrade)upgrade) : false;
}
ANK_FUNCTION_2(__city_temple_complex_has_upgrade)

int __city_temple_complex_allowed_altar_count(int id) {
    auto *b = building_get_ex<building_temple_complex>(id);
    return b ? (int)b->base_params().allowed_altar.size() : 0;
}
ANK_FUNCTION_1(__city_temple_complex_allowed_altar_count)

int __city_temple_complex_allowed_altar_at(int id, int idx) {
    auto *b = building_get_ex<building_temple_complex>(id);
    return (b && idx >= 0 && idx < (int)b->base_params().allowed_altar.size())
        ? (int)b->base_params().allowed_altar[idx] : 0;
}
ANK_FUNCTION_2(__city_temple_complex_allowed_altar_at)

int __city_temple_complex_allowed_oracle_count(int id) {
    auto *b = building_get_ex<building_temple_complex>(id);
    return b ? (int)b->base_params().allowed_oracle.size() : 0;
}
ANK_FUNCTION_1(__city_temple_complex_allowed_oracle_count)

int __city_temple_complex_allowed_oracle_at(int id, int idx) {
    auto *b = building_get_ex<building_temple_complex>(id);
    return (b && idx >= 0 && idx < (int)b->base_params().allowed_oracle.size())
        ? (int)b->base_params().allowed_oracle[idx] : 0;
}
ANK_FUNCTION_2(__city_temple_complex_allowed_oracle_at)

bool __gameplay_multiple_temple_complexes() {
    return !!game_features::gameplay_change_multiple_temple_complexes;
}
ANK_FUNCTION(__gameplay_multiple_temple_complexes)

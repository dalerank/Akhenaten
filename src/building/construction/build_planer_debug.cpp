#include "building/construction/build_planner.h"

#include "widget/debug_console.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "graphics/view/lookup.h"
#include "game/game.h"

ANK_REGISTER_PROPS_ITERATOR(config_show_build_planer_properties);
void config_show_build_planer_properties(bool header) {
    if (header) {
        return;
    }

    bool common_open = ImGui::TreeNodeEx("Build planer", ImGuiTreeNodeFlags_None, "Build planer");
    if (common_open) {
        ImGui::BeginTable("Build planer", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

        game_debug_show_property("type", g_city_planner.build_type);
        game_debug_show_property("in progress", g_city_planner.in_progress);
        game_debug_show_property("draw as con.", g_city_planner.draw_as_constructing);
        game_debug_show_property("orientation abs", g_city_planner.absolute_orientation);
        game_debug_show_property("orientation rel", g_city_planner.relative_orientation);
        game_debug_show_property("variant:", g_city_planner.building_variant);
        game_debug_show_property("start", g_city_planner.start);
        game_debug_show_property("end", g_city_planner.end.x());
        game_debug_show_property("", g_city_planner.end.y());

        vec2i screen_start = tile_to_screen(g_city_planner.start);
        vec2i screen_end = tile_to_screen(g_city_planner.end);
        game_debug_show_property("screen start", screen_start, true);
        game_debug_show_property("screen ebd", screen_end, true);
        
        game_debug_show_property("cost:", g_city_planner.total_cost);

        ImGui::EndTable();

        ImGui::TreePop();
    }
}
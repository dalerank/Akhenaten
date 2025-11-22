#include "city/city.h"

#include "widget/debug_console.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "game/game.h"

ANK_REGISTER_PROPS_ITERATOR(config_show_gametime_properties);
void config_show_gametime_properties(bool header) {
    if (header) {
        return;
    }

    bool common_open = ImGui::TreeNodeEx("Game Time", ImGuiTreeNodeFlags_None, "Game Time");
    if (common_open) {
        ImGui::BeginTable("Game Time", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

        auto &gtime = game.simtime;

        game_debug_show_property("day:", game.simtime.day);
        game_debug_show_property("month:", game.simtime.month);
        game_debug_show_property("year:", game.simtime.year);
        game_debug_show_property("abs. tick:", game.simtime.absolute_tick(true), true);
        game_debug_show_property("year tick:", game.simtime.absolute_tick(false), true);
        game_debug_show_property("abs. day:", game.simtime.absolute_day(true), true);   
        game_debug_show_property("year day:", game.simtime.absolute_day(false), true); 

        ImGui::EndTable();
        ImGui::TreePop();
    }
}
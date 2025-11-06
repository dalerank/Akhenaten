#include "city/city_religion.h"

#include "widget/debug_console.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "city/city.h"
#include "tutorial.h"
#include "game/game.h"

ANK_REGISTER_PROPS_ITERATOR(config_show_tutorial_properties);
void config_show_tutorial_properties(bool header) {
    if (header) {
        return;
    }

    bool common_open = ImGui::TreeNodeEx("Tutotial", ImGuiTreeNodeFlags_None, "Tutotial");
    if (common_open) {
        ImGui::BeginTable("Tutotial", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

        const auto &flags = g_tutorials_flags;
        game_debug_show_property("tut3 start", flags.tutorial_3.started);
        game_debug_show_property("3:figs", flags.tutorial_3.figs_stored);
        game_debug_show_property("3:pottery_100", flags.tutorial_3.pottery_made_1);
        game_debug_show_property("3:pottery_100", flags.tutorial_3.pottery_made_2);
        game_debug_show_property("tut4 start", flags.tutorial_4.started);
        game_debug_show_property("3:disease", flags.tutorial_3.disease);
        game_debug_show_property("4:beer_300", flags.tutorial_4.beer_made);
        game_debug_show_property("tut5 start", flags.tutorial_5.started);
        game_debug_show_property("5:apartment", flags.tutorial_5.spacious_apartment);
        game_debug_show_property("tut6 start", flags.tutorial_6.started);
        game_debug_show_property("tut7 start", flags.pharaoh.tut7_start);
        game_debug_show_property("tut8 start" , flags.pharaoh.tut8_start);

        ImGui::EndTable();

        ImGui::TreePop();
    }
}
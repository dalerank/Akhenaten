#include "city/city_religion.h"

#include "widget/debug_console.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "city/city.h"
#include "tutorial.h"
#include "game/game.h"
#include "scenario/scenario.h"
#include "game/mission.h"

ANK_REGISTER_PROPS_ITERATOR(config_show_tutorial_properties);
void config_show_tutorial_properties(bool header) {
    if (header) {
        return;
    }

    bool tutorial_open = ImGui::TreeNodeEx("Tutorial", ImGuiTreeNodeFlags_None, "Tutorial");
    if (tutorial_open) {
        ImGui::BeginTable("Tutorial", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

        const auto &flags = g_tutorials_flags;
        
        // Tutorial 4 flags
        game_debug_show_property("tut4 started", flags.tutorial_4.started);
        game_debug_show_property("tut4:beer_made", flags.tutorial_4.beer_made);
        game_debug_show_property("tut4:tax_collector_built", flags.tutorial_4.tax_collector_built);
        
        // Tutorial 5 flags
        game_debug_show_property("tut5 started", flags.tutorial_5.started);
        game_debug_show_property("tut5:spacious_apartment", flags.tutorial_5.spacious_apartment);
        game_debug_show_property("tut5:papyrus_made", flags.tutorial_5.papyrus_made);
        game_debug_show_property("tut5:bricks_bought", flags.tutorial_5.bricks_bought);
        game_debug_show_property("tut5:can_trade_finally", flags.tutorial_5.can_trade_finally);
        
        // Tutorial 6 flags
        game_debug_show_property("tut6 started", flags.tutorial_6.started);
        
        // Pharaoh tutorial flags
        game_debug_show_property("pharaoh:crime", flags.pharaoh.crime);
        game_debug_show_property("pharaoh:tut7_start", flags.pharaoh.tut7_start);
        game_debug_show_property("pharaoh:tut8_start", flags.pharaoh.tut8_start);
        
        // Pharaoh flags array (show first 10 for brevity)
        for (int i = 0; i < 10; i++) {
            if (flags.pharaoh.flags[i]) {
                bstring64 label;
                label.printf("pharaoh:flag[%d]", i);
                game_debug_show_property(label.c_str(), flags.pharaoh.flags[i]);
            }
        }

        ImGui::EndTable();
        ImGui::TreePop();
    }

    // Mission Information
    bool mission_open = ImGui::TreeNodeEx("Mission Info", ImGuiTreeNodeFlags_None, "Mission Info");
    if (mission_open) {
        ImGui::BeginTable("MissionInfo", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

        game_debug_show_property("scenario_id", g_scenario.settings.campaign_scenario_id);
        game_debug_show_property("campaign_id", get_scenario_campaign_id(g_scenario.settings.campaign_scenario_id));
        game_debug_show_property("mission_rank", g_scenario.settings.campaign_mission_rank);
        game_debug_show_property("starting_kingdom", g_scenario.settings.starting_kingdom);
        game_debug_show_property("starting_savings", g_scenario.settings.starting_personal_savings);
        game_debug_show_property("scenario_mode", (int)g_scenario.settings.scmode);
        game_debug_show_property("is_custom", g_scenario.mode() != e_scenario_normal);

        ImGui::EndTable();
        ImGui::TreePop();
    }

    // Mission Variables
    bool vars_open = ImGui::TreeNodeEx("Mission Variables", ImGuiTreeNodeFlags_None, "Mission Variables");
    if (vars_open) {
        ImGui::BeginTable("MissionVars", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

        // Iterate through all mission variables
        g_scenario.vars.foreach_vars([](xstring name, const setting_variant& value) {
            game_debug_show_property(name.c_str(), value);
        });

        ImGui::EndTable();
        ImGui::TreePop();
    }
}
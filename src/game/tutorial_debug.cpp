#include "city/city_religion.h"

#include "widget/debug_console.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "city/city.h"
#include "tutorial.h"
#include "game/game.h"
#include "scenario/scenario.h"
#include "game/mission.h"
#include "city/victory.h"
#include "scenario/criteria.h"

ANK_REGISTER_PROPS_ITERATOR(config_show_tutorial_properties);
void config_show_tutorial_properties(bool header) {
    if (header) {
        return;
    }

    bool tutorial_open = ImGui::TreeNodeEx("Tutorial", ImGuiTreeNodeFlags_None, "Tutorial");
    if (tutorial_open) {
        ImGui::BeginTable("Tutorial", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

        const auto &flags = g_tutorials_flags;               
        
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

    bool victory_open = ImGui::TreeNodeEx("Victory Status", ImGuiTreeNodeFlags_None, "Victory Status");
    if (victory_open) {
        ImGui::BeginTable("VictoryStatus", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

        // Overall victory state
        const char* state_text = "None";
        switch (g_city.victory_state.state) {
            case e_victory_state_won: state_text = "WON"; break;
            case e_victory_state_lost: state_text = "LOST"; break;
            case e_victory_state_none: state_text = "None"; break;
        }
        game_debug_show_property("victory_state", state_text);
        game_debug_show_property("force_win", g_city.victory_state.force_win);
        game_debug_show_property("force_lost", g_city.victory_state.force_lost);

        if (winning_population() > 0) {
            bstring64 label;
            label.printf("population: %d / %d", g_city.population.current, winning_population());
            bool met = g_city.population.current >= winning_population();
            game_debug_show_property(label.c_str(), met);
        }

        if (winning_culture() > 0) {
            bstring64 label;
            label.printf("culture: %d / %d", g_city.ratings.culture, winning_culture());
            bool met = g_city.ratings.culture >= winning_culture();
            game_debug_show_property(label.c_str(), met);
        }

        if (winning_prosperity() > 0) {
            bstring64 label;
            label.printf("prosperity: %d / %d", g_city.ratings.prosperity, winning_prosperity());
            bool met = g_city.ratings.prosperity >= winning_prosperity();
            game_debug_show_property(label.c_str(), met, true);
        }

        if (winning_monuments() > 0) {
            bstring64 label;
            label.printf("monuments: %d / %d", g_city.ratings.monument, winning_monuments());
            bool met = g_city.ratings.monument >= winning_monuments();
            game_debug_show_property(label.c_str(), met, true);
        }

        if (winning_kingdom() > 0) {
            bstring64 label;
            label.printf("kingdom: %d / %d", g_city.kingdome.rating, winning_kingdom());
            bool met = g_city.kingdome.rating >= winning_kingdom();
            game_debug_show_property(label.c_str(), met, true);
        }

        if (winning_housing() > 0) {
            bstring64 label;
            label.printf("housing[lvl %d]: %d / %d", winning_houselevel(), g_city.victory_state.houses_of_required_level(), winning_housing());
            game_debug_show_property(label.c_str(), g_city.victory_state.is_housing_condition_met(), true);
        }

        if (scenario_criteria_time_limit_enabled()) {
            bstring64 label;
            int years_left = scenario_criteria_max_year() - game.simtime.year;
            label.printf("time_limit: %d years left", years_left);
            game_debug_show_property(label.c_str(), years_left > 0);
        }

        if (scenario_criteria_survival_enabled()) {
            bstring64 label;
            int years_left = scenario_criteria_max_year() - game.simtime.year;
            label.printf("survival_time: %d years left", years_left);
            game_debug_show_property(label.c_str(), years_left <= 0);
        }

        ImGui::EndTable();
        ImGui::TreePop();
    }

    // Victory Reasons (custom mission-specific reasons)
    if (!get_victory_reasons().empty()) {
        bool reasons_open = ImGui::TreeNodeEx("Victory Reasons", ImGuiTreeNodeFlags_None, "Victory Reasons");
        if (reasons_open) {
            ImGui::BeginTable("VictoryReasons", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

            for (const auto& [reason, met] : get_victory_reasons()) {
                game_debug_show_property(reason.c_str(), met);
            }

            ImGui::EndTable();
            ImGui::TreePop();
        }
    }

    // Migration Caps (population limits)
    if (!g_city.migration.get_migration_caps().empty()) {
        bool caps_open = ImGui::TreeNodeEx("Migration Caps", ImGuiTreeNodeFlags_None, "Migration Caps");
        if (caps_open) {
            ImGui::BeginTable("MigrationCaps", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

            for (const auto& [reason, cap] : g_city.migration.get_migration_caps()) {
                game_debug_show_property(reason.c_str(), cap);
            }

            ImGui::EndTable();
            ImGui::TreePop();
        }
    }
}
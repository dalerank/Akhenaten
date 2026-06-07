#include "city/city_religion.h"

#include "widget/debug_console.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "city/city.h"
#include "scenario/scenario.h"
#include "js/js_events.h"

ANK_REGISTER_PROPS_ITERATOR(config_show_mission_properties);
void config_show_mission_properties(bool header) {
    if (header) {
        return;
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

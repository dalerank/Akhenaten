#include "scenario/scenario.h"

#include "widget/debug_console.h"
#include "imgui.h"
#include "imgui_internal.h"

ANK_REGISTER_PROPS_ITERATOR(config_load_scenario_properties);
void config_load_scenario_properties(bool header) {
    static bool _debug_buildng_open = true;

    if (header) {
        return;
    }

    bool common_open = ImGui::TreeNodeEx("Scenario", ImGuiTreeNodeFlags_None, "Scenario");

    if (common_open) {
        ImGui::BeginTable("split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

        g_scenario.vars.foreach_vars([] (xstring name, const setting_variant &var) {
            game_debug_show_property(name.c_str(), var);
        });
           
        ImGui::EndTable();

        ImGui::TreePop();
    }
}

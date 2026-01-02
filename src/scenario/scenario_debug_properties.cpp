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

    bool common_open = ImGui::TreeNodeEx("Mission Variables", ImGuiTreeNodeFlags_None, "Mission Variables");

    if (common_open) {
        ImGui::BeginTable("split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

        struct name_var {
            pcstr name;
            const setting_variant *value;
        };
        hvector<name_var, 32> sorted_vars;
        g_scenario.vars.foreach_vars([&] (xstring name, const setting_variant &var) {
            sorted_vars.push_back({ name.c_str(), &var });
        });
        std::sort(sorted_vars.begin(), sorted_vars.end(), [] (auto &lhs, auto &rhs) { return strcmp(lhs.name, rhs.name) < 0; });

        for (auto &it: sorted_vars) {
            game_debug_show_property(it.name, *it.value);
        }
           
        ImGui::EndTable();

        ImGui::TreePop();
    }
}

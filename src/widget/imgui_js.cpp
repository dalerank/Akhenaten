#include "js/js_game.h"

#if !defined(GAME_PLATFORM_ANDROID)

#include "core/profiler.h"
#include "imgui.h"

bool __imgui_tree_node_ex(pcstr label) {
    return ImGui::TreeNodeEx(label, ImGuiTreeNodeFlags_None, "%s", label);
}

void __imgui_tree_pop() {
    ImGui::TreePop();
}

void __imgui_begin_table(pcstr id, int columns, int flags) {
    ImGui::BeginTable(id, columns, (ImGuiTableFlags)flags);
}

void __imgui_end_table() {
    ImGui::EndTable();
}

int __imgui_table_flags_debug_props() {
    return (int)(ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);
}

#else

bool __imgui_tree_node_ex(pcstr) {
    return false;
}

void __imgui_tree_pop() {}

void __imgui_begin_table(pcstr, int, int) {}

void __imgui_end_table() {}

int __imgui_table_flags_debug_props() {
    return 0;
}

#endif

ANK_FUNCTION_1(__imgui_tree_node_ex)
ANK_FUNCTION(__imgui_tree_pop)
ANK_FUNCTION_3(__imgui_begin_table)
ANK_FUNCTION(__imgui_end_table)
ANK_FUNCTION(__imgui_table_flags_debug_props)
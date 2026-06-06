#include "js/js_game.h"
#include "core/profiler.h"
#include "core/xstring.h"

#include <cstring>

#if !defined(GAME_PLATFORM_ANDROID)

#include "imgui.h"

bool __imgui_tree_node_ex(pcstr label) {
    return ImGui::TreeNodeEx(label, ImGuiTreeNodeFlags_None, "%s", label);
}

bool __imgui_tree_node_ex2(pcstr id, pcstr label) {
    return ImGui::TreeNodeEx(id, ImGuiTreeNodeFlags_None, "%s", label);
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

void __imgui_text(pcstr text) {
    ImGui::TextUnformatted(text ? text : "");
}

void __imgui_same_line() {
    ImGui::SameLine();
}

bool __imgui_button(pcstr label) {
    return ImGui::Button(label);
}

void __imgui_set_next_item_width(float width) {
    ImGui::SetNextItemWidth(width);
}

float __imgui_content_region_avail_x() {
    return ImGui::GetContentRegionAvail().x;
}

xstring __imgui_input_text(xstring id, xstring text) {
    char buf[256] = "";
    if (!text.empty()) {
        strncpy(buf, text.c_str(), sizeof(buf) - 1);
        buf[sizeof(buf) - 1] = '\0';
    }
    ImGui::InputText(id.c_str(), buf, sizeof(buf));
    return xstring(buf);
}

#else

bool __imgui_tree_node_ex(pcstr) {
    return false;
}

bool __imgui_tree_node_ex2(pcstr, pcstr) {
    return false;
}

void __imgui_tree_pop() {}

void __imgui_begin_table(pcstr, int, int) {}

void __imgui_end_table() {}

int __imgui_table_flags_debug_props() {
    return 0;
}

void __imgui_text(pcstr) {}

void __imgui_same_line() {}

bool __imgui_button(pcstr) {
    return false;
}

void __imgui_set_next_item_width(float) {}

float __imgui_content_region_avail_x() {
    return 0.f;
}

xstring __imgui_input_text(xstring, xstring text) {
    return text;
}

#endif

ANK_FUNCTION_1(__imgui_tree_node_ex)
ANK_FUNCTION_2(__imgui_tree_node_ex2)
ANK_FUNCTION(__imgui_tree_pop)
ANK_FUNCTION_3(__imgui_begin_table)
ANK_FUNCTION(__imgui_end_table)
ANK_FUNCTION(__imgui_table_flags_debug_props)
ANK_FUNCTION_1(__imgui_text)
ANK_FUNCTION(__imgui_same_line)
ANK_FUNCTION_1(__imgui_button)
ANK_FUNCTION_1(__imgui_set_next_item_width)
ANK_FUNCTION(__imgui_content_region_avail_x)
ANK_FUNCTION_2(__imgui_input_text)
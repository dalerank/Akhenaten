#include "imui.h"

#include "graphics/elements/panel.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "core/vec2i.h"
#include "imgui_internal.h"

namespace ui {

bool Begin(const char* name, bool* p_open, ImGuiWindowFlags flags) {
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
    
    bool result = ImGui::Begin(name, p_open, flags);
    
    if (result && ImGui::GetCurrentWindow()) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        
        ImVec2 pos = window->Pos;
        ImVec2 size = window->Size;
        
        vec2i panel_pos = {static_cast<int>(pos.x), static_cast<int>(pos.y)};
        vec2i panel_size = {static_cast<int>(size.x), static_cast<int>(size.y)};
        
        // Draw panel with exact size
        outer_panel_draw_exact(panel_pos, panel_size);
    }
    
    ImGui::PopStyleColor();
    
    return result;
}

} // namespace ui


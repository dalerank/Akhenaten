#include "widget/debug_console.h"
#include "imgui/imgui.h"
#include "js/js_game.h"
#include "platform/renderer.h"
#include "game/game.h"
#include "graphics/imagepak_holder.h"
#include "graphics/font.h"

#include <memory>
#include <vector>
#include <unordered_map>

static int g_current_codepoint_start = 0x0410; // Cyrillic А
static int g_current_codepoint_end = 0x044F;   // Cyrillic я
static char g_preview_text[256] = "AbcdefABCDEF";
static bool g_show_atlas = false;

ANK_REGISTER_PROPS_ITERATOR(config_load_font_preview_properties);
void config_load_font_preview_properties(bool header) {
    if (header) {
        return;
    }

    bool font_preview_open = ImGui::TreeNodeEx("Font Preview", ImGuiTreeNodeFlags_None, "Font Preview");
    if (!font_preview_open) {
        return;
    }

    ImGui::Text("Font Generator - Runtime Preview");
    ImGui::Separator();
    
    ImGui::InputInt("Start Codepoint (hex)", &g_current_codepoint_start, 1, 16, ImGuiInputTextFlags_CharsHexadecimal);
    ImGui::InputInt("End Codepoint (hex)", &g_current_codepoint_end, 1, 16, ImGuiInputTextFlags_CharsHexadecimal);
    
    g_current_codepoint_start = std::max(0, std::min(0xFFFF, g_current_codepoint_start));
    g_current_codepoint_end = std::max(g_current_codepoint_start, std::min(0xFFFF, g_current_codepoint_end));
    
    ImGui::Checkbox("Show Atlas Texture", &g_show_atlas);                     
        
    if (g_show_atlas) {
        painter ctx = game.painter();
        const auto &font_pack = g_image_data->pak_list[PACK_CUSTOM_FONT];
        const auto &atlas = font_pack.handle->atlas_pages.front();
        
        ImageDraw::fill_rect({ 0, 0 }, { atlas.width, atlas.height }, COLOR_YELLOW);
        ctx.draw(atlas.texture, { 0, 0 }, {0, 0}, {atlas.width, atlas.height}, COLOR_MASK_NONE, 1.f, 1.f, 0, 0);
    }
    
    ImGui::TreePop();
}

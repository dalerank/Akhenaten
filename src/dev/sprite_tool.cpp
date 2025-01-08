#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "widget/debug_console.h"
#include "graphics/imagepak_holder.h"
#include "dev/debug.h"

ANK_REGISTER_PROPS_ITERATOR(dev_sprite_tool);

void game_debug_show_properties_object(imagepak_handle ipak) {
    ImGui::PushID(0x82000000 | ipak.id);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx((void*)ipak.name.c_str(), ImGuiTreeNodeFlags_DefaultOpen, "%s", ipak.name);
    ImGui::TableSetColumnIndex(1); 

    if (common_open) {
        game_debug_show_property("id", ipak.id, true);
        game_debug_show_property("index", ipak.index, true);

        const auto &names = ipak.handle->names();
        const auto &ids = ipak.handle->image_ids();
        for (int i = 0, size = names.size(); i < size; ++i) {
            ImGui::PushID(0x83000000 | i);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::AlignTextToFramePadding();
            bool anim_open = ImGui::TreeNodeEx((void*)names[i].c_str(), ImGuiTreeNodeFlags_DefaultOpen, "%s", names[i].c_str());
            ImGui::TableSetColumnIndex(1);

            const int offset = ids[i];

            if (anim_open) {
                game_debug_show_property("id", i, true);
                game_debug_show_property("offset", offset, true);

                ImGui::TreePop();
            }
            ImGui::PopID();
        }

        ImGui::TreePop();
    }

    ImGui::PopID();
}


void dev_sprite_tool(bool header) {
    static bool _debug_sprites_open = false;

    if (header) {
        ImGui::Checkbox("Sprites", &_debug_sprites_open);
        return;
    } 

    if (_debug_sprites_open && ImGui::BeginTable("split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable)) {
        for (const auto &imgpak : g_image_data->common) {
            if (imgpak.name.empty()) {
                continue;
            }

            game_debug_show_properties_object(imgpak);
        }
        ImGui::EndTable();
    }
}
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
    bool common_open = ImGui::TreeNodeEx((void*)ipak.name.c_str(), ImGuiTreeNodeFlags_DefaultOpen, "%s", ipak.name.c_str());
    ImGui::TableSetColumnIndex(1); 

    if (common_open) {
        game_debug_show_property("id", ipak.id, true);
        game_debug_show_property("id-name", e_pack_type_tokens.name((e_pack)ipak.id));
        game_debug_show_property("index", ipak.index, true);

        const auto &names = ipak.handle->names();
        const auto &ids = ipak.handle->image_ids(); 
        for (int i = 0, size = names.size(); i < size; ++i) {
            ImGui::PushID(0x83000000 + i);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::AlignTextToFramePadding();
            const image_t* img = image_get(image_desc{ipak.id, i, 0});
            bool anim_open = ImGui::TreeNodeEx(img, ImGuiTreeNodeFlags_DefaultOpen, "%s", img->bmp.name.c_str());
            ImGui::TableSetColumnIndex(1);

            const int ioffset = ids[i];

            if (anim_open) {
                game_debug_show_property("id", i, true);
                game_debug_show_property("i_offset", ioffset, true);

                if (img && img->atlas.p_atlas) {
                    game_debug_show_property("sprites", img->animation.num_sprites);
                    const vec2i tx_offset = img->atlas.offset;

                    ImGui::PushID(0x88000000 + i);
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::AlignTextToFramePadding();
                    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
                    ImGui::TreeNodeEx("Field", flags, "Image");
                    ImGui::TableSetColumnIndex(1);
                    ImGui::SetNextItemWidth(-FLT_MIN);

                    ImGui::InputInt2("Image", (int *)&tx_offset);

                    const vec2i atlas_size(img->atlas.p_atlas->width, img->atlas.p_atlas->height);
                    ImVec2 uv_min(tx_offset.x / (float)atlas_size.x, tx_offset.y / (float)atlas_size.y);
                    ImVec2 uv_max((tx_offset.x + img->width) / (float)atlas_size.x, (tx_offset.y + img->height) / (float)atlas_size.y);
                    ImGui::Image(img->atlas.p_atlas->texture, ImVec2(img->width, img->height), uv_min, uv_max);

                    ImGui::NextColumn();
                    ImGui::PopID();
                }

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
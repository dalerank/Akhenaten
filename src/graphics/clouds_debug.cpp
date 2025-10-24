#include "clouds.h"

#include "widget/debug_console.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "city/city.h"

ANK_REGISTER_PROPS_ITERATOR(config_show_clouds_properties);
void config_show_clouds_properties(bool header) {
    if (header) {
        return;
    }
    bool common_open = ImGui::TreeNodeEx("Clouds", ImGuiTreeNodeFlags_None, "Clouds");
    if (common_open) {
        {
            ImGui::BeginTable("split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

            for (int i = 0; i < NUM_CLOUDS; i++) {
                ImGui::PushID(bstring32("CloudTable", i).hash());

                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::AlignTextToFramePadding();
                bool anim_open = ImGui::TreeNodeEx(bstring32("Cloud", i), ImGuiTreeNodeFlags_None, "Cloud %d", i);
                ImGui::TableSetColumnIndex(1);

                if (anim_open) {
                    const cloud_type *cloud = &g_clouds.clouds[i];
                    e_cloud_status status = cloud->status;
                    bstring32 status_text[3] = { "INACTIVE", "CREATED", "MOVING" };

                    game_debug_show_property("status ", status_text[status]);
                    game_debug_show_property("speedx ", cloud->speed.x.current_speed);
                    game_debug_show_property("speedy ", cloud->speed.y.current_speed);
                    game_debug_show_property("pos", cloud->pos);
                    game_debug_show_property("render_pos", cloud->render_pos);

                    ImGui::TreePop();
                }

                ImGui::PopID();
            }

            ImGui::EndTable();
        }

        ImGui::TreePop();
    }
}

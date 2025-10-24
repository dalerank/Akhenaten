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

            auto &config = g_clouds.config;
            game_debug_show_property("Reset Clouds", [i=0] { g_clouds.init_cloud_images(); });
            game_debug_show_property("num_cloud_ellipses", config.num_cloud_ellipses);
            game_debug_show_property("cloud_alpha_increase", config.cloud_alpha_increase);
            game_debug_show_property("cloud_columns", config.cloud_columns);
            game_debug_show_property("cloud_rows", config.cloud_rows);
            game_debug_show_property("cloud_width", config.cloud_width);
            game_debug_show_property("cloud_height", config.cloud_height);
            game_debug_show_property("cloud_size_ratio", config.cloud_size_ratio);
            game_debug_show_property("cloud_scale", config.cloud_scale);
            game_debug_show_property("cloud_min_creation_timeout", config.cloud_min_creation_timeout);
            game_debug_show_property("cloud_max_creation_timeout", config.cloud_max_creation_timeout);
            game_debug_show_property("pause_min_frames", config.pause_min_frames);

            pcstr status_text[3] = { "INACTIVE", "CREATED", "MOVING" };
            for (int i = 0; i < g_clouds.clouds.size(); i++) {
                ImGui::PushID(bstring32("CloudTable", i).hash());

                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::AlignTextToFramePadding();
                bool anim_open = ImGui::TreeNodeEx(bstring32("Cloud", i).c_str(), ImGuiTreeNodeFlags_None, "Cloud %d", i);
                ImGui::TableSetColumnIndex(1);

                if (anim_open) {
                    const auto &cloud = g_clouds.clouds[i];
                    e_cloud_status status = cloud.status;

                    game_debug_show_property("status ", status_text[status]);
                    game_debug_show_property("speedx ", cloud.speed.x.current_speed);
                    game_debug_show_property("speedy ", cloud.speed.y.current_speed);
                    game_debug_show_property("pos", cloud.pos);
                    game_debug_show_property("render_pos", cloud.render_pos);

                    ImGui::TreePop();
                }

                ImGui::PopID();
            }

            ImGui::EndTable();
        }

        ImGui::TreePop();
    }
}

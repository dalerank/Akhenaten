#include "enemy_army.h"

#include "widget/debug_console.h"
#include "imgui.h"
#include "imgui_internal.h"

ANK_REGISTER_PROPS_ITERATOR(config_show_enemy_armies_properties);

void config_show_enemy_armies_properties_battalions(pcstr prefix, enemy_army *army) {
    ImGui::PushID(0x82000000 | army->army_id);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool battalions_open = ImGui::TreeNodeEx("Battalions", ImGuiTreeNodeFlags_None, "Battalions");
    ImGui::TableSetColumnIndex(1);

    if (battalions_open) {
        uint8_t battalion_index = 0;
        for (int i = 1; i < MAX_FORMATIONS; i++) {
           formation *m = formation_get(i);
           if (m->in_use && !m->is_herd && !m->own_batalion && m->invasion_id == army->army_id) {
               game_debug_show_property(bstring32("battalion ", battalion_index++).c_str(), m->id);
           }
        }

        ImGui::TreePop();
    }
    ImGui::PopID();
}


void config_show_enemy_armies_properties(bool header) {
    if (header) {
        return;
    }

    bool common_open = ImGui::TreeNodeEx("Enemy Armies", ImGuiTreeNodeFlags_None, "Enemy Armies");
    if (!common_open) {
        return;
    }

    {
        ImGui::BeginTable("EnemyArmies", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);
        for (size_t i = 0; i < g_enemy_armies.data.size(); ++i) {
            auto &army = g_enemy_armies.data[i];
            if (army.formation_id == 0) {
                continue;
            }

            ImGui::PushID(static_cast<int>(i));

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::AlignTextToFramePadding();
            bool army_open = ImGui::TreeNodeEx("Army", ImGuiTreeNodeFlags_DefaultOpen, "Army #%u (invasion_id: %zu)", army.army_id, i);

            ImGui::TableSetColumnIndex(1);
            if (army_open) {
                game_debug_show_property("army_id", army.army_id);
                game_debug_show_property("formation_id", army.formation_id);
                game_debug_show_property("layout", army.layout);
                game_debug_show_property("home", army.home);
                game_debug_show_property("destination", army.destination);
                game_debug_show_property("destination_building_id", army.destination_building_id);
                game_debug_show_property("num_batalions", army.num_batalions, true);
                config_show_enemy_armies_properties_battalions("battalions", &army);
                game_debug_show_property("ignore_pharaoh_soldiers", army.ignore_pharaoh_soldiers);
                game_debug_show_property("buildings_to_destroy", army.buildings_to_destroy);
                game_debug_show_property("buildings_destroyed", army.buildings_destroyed);

                ImGui::TreePop();
            }

            ImGui::PopID();
        }
        ImGui::EndTable();
    }

    ImGui::TreePop();
}


#include "city/city_religion.h"

#include "widget/debug_console.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "city/city.h"
#include "game/game.h"

ANK_REGISTER_PROPS_ITERATOR(config_show_religion_properties);
void config_show_religion_properties(bool header) {
    if (header) {
        return;
    }

    bool common_open = ImGui::TreeNodeEx("Religion", ImGuiTreeNodeFlags_None, "Religion");
    if (common_open) {
        ImGui::BeginTable("Religion", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

        for (int i = 0; i < MAX_GODS; i++) {
            if (g_city.religion.is_god_known((e_god)i) != GOD_STATUS_UNKNOWN) {
                ImGui::PushID(bstring32("GOD", i).hash());

                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::AlignTextToFramePadding();
                bool anim_open = ImGui::TreeNodeEx(bstring32("GOD", i).c_str(), ImGuiTreeNodeFlags_None, e_god_tokens.name((e_god)i));
                ImGui::TableSetColumnIndex(1);

                auto &god = g_city.religion.gods[i];
                auto &static_params = god.static_params();
                if (anim_open) {
                    game_debug_show_property("Mood", god.mood); 
                    game_debug_show_property("Target mood", god.target_mood);
                    game_debug_show_property("Wraths bolds", god.wrath_bolts);
                    game_debug_show_property("Happy ankhs", god.happy_ankhs);
                    game_debug_show_property("Shrines", g_city.buildings.count_total(static_params.shrine_type));
                    game_debug_show_property("Templs", g_city.buildings.count_active(static_params.temple_type));
                    game_debug_show_property("Complex", g_city.buildings.count_active(static_params.complex_type));
                    game_debug_show_property("Coverage", g_city.religion.coverage_avg(god.type));
                    game_debug_show_property("Months since fest", god.months_since_festival);
                 
                    ImGui::TreePop();
                }

                ImGui::PopID();
            }
        }

        game_debug_show_property("150% export profits", g_city.religion.ra_150_export_profits_months_left);
        game_debug_show_property("No traders", g_city.religion.ra_no_traders_months_left);
        game_debug_show_property("Slightly increased trades", g_city.religion.ra_slightly_increased_trading_months_left);
        game_debug_show_property("Slightly reduced trades", g_city.religion.ra_slightly_reduced_trading_months_left);
        game_debug_show_property("Harshly reduced trades:", g_city.religion.ra_harshly_reduced_trading_months_left);

        game_debug_show_property("Enemy troops kill", g_city.religion.seth_crush_enemy_troops);
        game_debug_show_property("Player troops protection:", g_city.religion.seth_protect_player_troops);

        game_debug_show_property("Double farm yields days:", g_city.religion.osiris_double_farm_yield_days);
        game_debug_show_property("Floods will destroy farms:", g_city.religion.osiris_flood_will_destroy_active);


        ImGui::EndTable();

        ImGui::TreePop();
    }
}
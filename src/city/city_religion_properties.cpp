#include "city/city_religion.h"

#include "widget/debug_console.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "city/city_religion_osiris.h"
#include "city/city.h"

ANK_REGISTER_PROPS_ITERATOR(config_load_god_properties);
void game_debug_show_properties_religion(pcstr prefix, city_religion_t &religion) {
    ImGui::PushID(0x80000000 | 1);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Religion", ImGuiTreeNodeFlags_DefaultOpen, "Religion");
    ImGui::TableSetColumnIndex(1); 

    if (common_open) {
        bstring256 type_name;
        type_name.printf("%s [%d]", token::find_name(e_god_tokens, religion.least_happy_god), religion.least_happy_god);
        game_debug_show_property("least_happy_god", type_name);
        game_debug_show_property("angry_message_delay", religion.angry_message_delay);
        game_debug_show_property("bast_curse_active", religion.bast_curse_active);
        game_debug_show_property("ra_150_export_profits_months_left", religion.ra_150_export_profits_months_left);
        game_debug_show_property("ra_harshly_reduced_trading_months_left", religion.ra_harshly_reduced_trading_months_left);
        game_debug_show_property("ra_no_traders_months_left", religion.ra_no_traders_months_left);
        game_debug_show_property("ra_slightly_reduced_trading_months_left", religion.ra_slightly_reduced_trading_months_left);
        game_debug_show_property("ra_slightly_increased_trading_months_left", religion.ra_slightly_increased_trading_months_left);
        game_debug_show_property("osiris_sank_ships", god_osiris.sank_ships);
        game_debug_show_property("seth_crush_enemy_troops", religion.seth_crush_enemy_troops);
        game_debug_show_property("seth_protect_player_troops_months", religion.seth_protect_player_troops_months);
        game_debug_show_property("osiris_double_farm_yield_days", religion.osiris_double_farm_yield_days);
        game_debug_show_property("osiris_flood_will_destroy_active", religion.osiris_flood_will_destroy_active);
        game_debug_show_property("coverage_common", religion.coverage_common);

        ImGui::TreePop();
    }
    ImGui::PopID();
}

void game_debug_show_properties_object(pcstr prefix, city_religion_t &religion, const god_state &god) {
    ImGui::PushID(0x80000000 | god.type);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("God", ImGuiTreeNodeFlags_DefaultOpen, "%s", token::find_name(e_god_tokens, god.type));
    ImGui::TableSetColumnIndex(1); 

    if (common_open) {
        game_debug_show_property("type", god.type, true);
        game_debug_show_property("mood", god.mood);
        game_debug_show_property("target_mood", god.target_mood);
        game_debug_show_property("wrath_bolts", god.wrath_bolts);
        game_debug_show_property("happy_ankhs", god.happy_ankhs);
        game_debug_show_property("blessing_done", god.blessing_done);
        game_debug_show_property("curse_done", god.curse_done);
        game_debug_show_property("months_since_festival", god.months_since_festival);
        game_debug_show_property("unused1", god.unused1);
        game_debug_show_property("unused2", god.unused2);
        game_debug_show_property("unused3", god.unused3);
        game_debug_show_property("is_known", god.is_known);
        game_debug_show_property("coverage", religion.coverage[god.type]);

        ImGui::TreePop();
    }
    ImGui::PopID();
}

void config_load_god_properties(bool header) {
    if (header) {
        return;
    } 

    auto &religion = g_city.religion;
    bool common_open = ImGui::TreeNodeEx("Religion", ImGuiTreeNodeFlags_None, "Religion");
    if (common_open) {
        if (ImGui::BeginTable("split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable)) {
            game_debug_show_properties_religion("Religion", religion);

            for (e_god i = GOD_OSIRIS; i < MAX_GODS; ++i) {
                game_debug_show_properties_object("God", religion, g_city.religion.gods[i]);
            }
            ImGui::EndTable();
        }

        ImGui::TreePop();
    }
}
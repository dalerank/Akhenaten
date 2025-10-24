#include "city_sentiment.h"

#include "widget/debug_console.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "city/city.h"

ANK_REGISTER_PROPS_ITERATOR(config_show_sentiment_properties);
void config_show_sentiment_properties(bool header) {
    if (header) {
        return;
    }

    bool common_open = ImGui::TreeNodeEx("Sentiment", ImGuiTreeNodeFlags_None, "Sentiment");
    if (common_open) {
        ImGui::BeginTable("Sentiment", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

        auto &migration = g_city.migration;
        game_debug_show_property("invading_cap", migration.invading_cap);

        auto &sentiment = g_city.sentiment;
        game_debug_show_property("value:", sentiment.value);
        game_debug_show_property("previous_value:", sentiment.previous_value);
        game_debug_show_property("message_delay:", sentiment.message_delay);
        game_debug_show_property("include_tents:", sentiment.include_huts);
        game_debug_show_property("unemployment_pct:", sentiment.unemployment_pct);
        game_debug_show_property("wages:", sentiment.wages);
        game_debug_show_property("low_mood_cause:", sentiment.low_mood_cause);
        game_debug_show_property("protesters:", sentiment.protesters);
        game_debug_show_property("criminals:", sentiment.criminals);
        game_debug_show_property("can_create_mugger:", sentiment.can_create_mugger);
        game_debug_show_property("can_create_protestor:", sentiment.can_create_protestor);
        game_debug_show_property("last_mugger_message:", sentiment.last_mugger_message);
        game_debug_show_property("contribution_taxes:", sentiment.contribution_taxes);
        game_debug_show_property("contribution_wages:", sentiment.contribution_wages);
        game_debug_show_property("contribution_employment:", sentiment.contribution_employment);
        game_debug_show_property("penalty_huts:", sentiment.contribution_penalty_huts);
        game_debug_show_property("monuments:", sentiment.contribution_monuments);
        game_debug_show_property("religion_coverage:", sentiment.contribution_religion_coverage);

        ImGui::EndTable();

        ImGui::TreePop();
    }
}
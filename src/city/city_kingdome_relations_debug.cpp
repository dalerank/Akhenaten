#include "city_kingdome_relations.h"

#include "widget/debug_console.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "city/city.h"

ANK_REGISTER_PROPS_ITERATOR(config_show_kingdome_properties);
void config_show_kingdome_properties(bool header) {
    if (header) {
        return;
    }

    bool common_open = ImGui::TreeNodeEx("Kingdome", ImGuiTreeNodeFlags_None, "Kingdome");
    if (!common_open) {
        return;
    }

    ImGui::BeginTable("Kingdome", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

    auto &kingdome = g_city.kingdome;

    game_debug_show_property("rating", kingdome.rating);
    game_debug_show_property("rating_last_year", kingdome.rating_last_year);
    game_debug_show_property("rating_cap", kingdome.rating_cap);
    game_debug_show_property("kingdom_change", kingdome.kingdom_change);
    game_debug_show_property("months_since_gift", kingdome.months_since_gift);
    game_debug_show_property("gift_overdose_penalty", kingdome.gift_overdose_penalty);
    game_debug_show_property("donate_amount", kingdome.donate_amount);
    game_debug_show_property("personal_savings", kingdome.personal_savings);
    game_debug_show_property("player_rank", kingdome.player_rank);
    game_debug_show_property("salary_rank", kingdome.salary_rank);
    game_debug_show_property("salary_amount", kingdome.salary_amount);
    game_debug_show_property("months_in_debt", kingdome.months_in_debt);
    game_debug_show_property("debt_state", kingdome.debt_state);
    game_debug_show_property("kingdom_salary_penalty", kingdome.kingdom_salary_penalty);
    game_debug_show_property("kingdom_milestone_penalty", kingdome.kingdom_milestone_penalty);
    game_debug_show_property("kingdom_ignored_request_penalty", kingdome.kingdom_ignored_request_penalty);
    game_debug_show_property("kingdom_explanation", kingdome.kingdom_explanation);

    game_debug_show_property("gift_modest_id", kingdome.gifts[GIFT_MODEST].id);
    game_debug_show_property("gift_modest_cost", kingdome.gifts[GIFT_MODEST].cost);
    game_debug_show_property("gift_generous_id", kingdome.gifts[GIFT_GENEROUS].id);
    game_debug_show_property("gift_generous_cost", kingdome.gifts[GIFT_GENEROUS].cost);
    game_debug_show_property("gift_lavish_id", kingdome.gifts[GIFT_LAVISH].id);
    game_debug_show_property("gift_lavish_cost", kingdome.gifts[GIFT_LAVISH].cost);

    game_debug_show_property("invasion.count", kingdome.invasion.count);
    game_debug_show_property("invasion.size", kingdome.invasion.size);
    game_debug_show_property("invasion.soldiers_killed", kingdome.invasion.soldiers_killed);
    game_debug_show_property("invasion.warnings_given", kingdome.invasion.warnings_given);
    game_debug_show_property("invasion.days_until_invasion", kingdome.invasion.days_until_invasion);
    game_debug_show_property("invasion.duration_day_countdown", kingdome.invasion.duration_day_countdown);
    game_debug_show_property("invasion.retreat_message_shown", kingdome.invasion.retreat_message_shown);

    ImGui::EndTable();

    ImGui::TreePop();
}
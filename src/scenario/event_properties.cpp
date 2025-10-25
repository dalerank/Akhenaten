#include "scenario_event_manager.h"

#include "widget/debug_console.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "game/game.h"

void game_debug_show_properties_object(pcstr prefix, event_ph_t &e) {
    ImGui::PushID(0x80000000 | e.event_id);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Event", ImGuiTreeNodeFlags_None, "Event %d", e.event_id);
    ImGui::TableSetColumnIndex(1); 

    if (common_open) {
        game_debug_show_property("event_id", e.event_id, true);

        bstring256 type_name;
        game_debug_show_property("Execute", [&] { 
            auto date = game.simtime.date();
            e.time.year = date.year;
            e.time.month = date.month;
            e.event_trigger_type = EVENT_TRIGGER_ONCE;
            g_scenario.events.process_events();
        });

        type_name.printf("%s [%d]", token::find_name(e_event_type_tokens, e.type), e.type);
        game_debug_show_property("tag_id", e.tag_id);
        game_debug_show_property("<type>", type_name);
        game_debug_show_property("time", e.time.year);
        game_debug_show_property("month", e.time.month);
        bstring32 time_str; time_str.printf("%s %d %s", ui::str(25, e.time.month), e.time.year + scenario_property_start_year(), lang_text_from_key("#AD"));
        game_debug_show_property("date", time_str.c_str());
        //game_debug_show_property("time.f_fixed", e.time.unk01);
        game_debug_show_property("months_initial", e.months_initial);
        game_debug_show_property("quest_months_left", e.quest_months_left);

        type_name.printf("%s [%d]", token::find_name(e_event_state_tokens, e.event_state), e.event_state);
        game_debug_show_property("<event_state>", type_name);
        game_debug_show_property("event_state", (int8_t&)e.event_state);
        game_debug_show_property("is_overdue", e.is_overdue);
        game_debug_show_property("is_active", e.is_active);
        game_debug_show_property("can_comply_dialog_shown", e.can_comply_dialog_shown);
        game_debug_show_property("festival_deity", e.festival_deity);
        game_debug_show_property("on_too_late_action", e.on_too_late_action);
        game_debug_show_property("on_defeat_action", e.on_defeat_action);
        game_debug_show_property("sender_faction", e.sender_faction);

        type_name.printf("%s [%d]", token::find_name(e_event_trigger_type_tokens, e.event_trigger_type), e.event_trigger_type);
        game_debug_show_property("<event_trigger_type>", type_name);
        game_debug_show_property("event_trigger_type", (int8_t&)e.event_trigger_type);

        if (e.type == EVENT_TYPE_REQUEST) {
            type_name.printf("%s [%d]", resource_name((e_resource)e.item.value), e.item.value);
            game_debug_show_property("<item.value>", type_name);
        }

        game_debug_show_property("item.value", e.item.value);
        game_debug_show_property("item.f_fixed", e.item.f_fixed);

        ImGui::TreePop();
    }
    ImGui::PopID();
}

ANK_REGISTER_PROPS_ITERATOR(config_load_event_properties);
void config_load_event_properties(bool header) {
    if (header) {
        return;
    } 

    bool common_open = ImGui::TreeNodeEx("Events", ImGuiTreeNodeFlags_None, "Events");
    if (common_open) {
        ImGui::BeginTable("split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);
        for (int i = 0; i < g_scenario.events.events_count(); ++i) {
            event_ph_t *evt = g_scenario.events.at(i);
            assert(evt);
            game_debug_show_properties_object("Events", *evt);
        }
        ImGui::EndTable();

        ImGui::TreePop();
    }
}
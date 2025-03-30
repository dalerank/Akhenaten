#include "events.h"

#include "widget/debug_console.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

ANK_REGISTER_PROPS_ITERATOR(config_load_event_properties);

void game_debug_show_properties_object(pcstr prefix, const event_ph_t &e) {
    ImGui::PushID(0x80000000 | e.event_id);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Event", ImGuiTreeNodeFlags_DefaultOpen, "Event %d", e.event_id);
    ImGui::TableSetColumnIndex(1); 

    if (common_open) {
        game_debug_show_property("event_id", e.event_id, true);

        bstring256 type_name;

        type_name.printf("%s [%d]", token::find_name(e_event_type_tokens, e.type), e.type);
        game_debug_show_property("<type>", type_name);
        game_debug_show_property("month", e.month);
        game_debug_show_property("time.year", e.time.value);
        game_debug_show_property("time.f_fixed", e.time.f_fixed);
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


void config_load_event_properties(bool header) {
    static bool _debug_events_open = false;

    if (header) {
        ImGui::Checkbox("Events", &_debug_events_open);
        return;
    } 

    if (_debug_events_open && ImGui::BeginTable("split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable)) {
        for (int i = 0; i < g_scenario.events.events_count(); ++i) {
            const event_ph_t *evt = g_scenario.events.at(i);
            assert(evt);
            game_debug_show_properties_object("Events", *evt);
        }
        ImGui::EndTable();
    }
}
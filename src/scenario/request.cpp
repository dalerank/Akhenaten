#include "request.h"

#include "building/building_storage_yard.h"
#include "game/game_events.h"
#include "city/city_finance.h"
#include "city/city_message.h"
#include "city/ratings.h"
#include "city/city_resource.h"
#include "city/city.h"
#include "core/random.h"
#include "core/svector.h"
#include "scenario_event_manager.h"
#include "game/resource.h"
#include "game/tutorial.h"
#include "scenario/scenario.h"
#include "event_phrases.h"

void scenario_request_init() {
    //for (int i = 0; i < MAX_REQUESTS; i++) {
    //    random_generate_next();
    //    if (g_scenario.requests[i].resource) {
    //        g_scenario.requests[i].month = (random_byte() & 7) + 2;
    //        g_scenario.requests[i].months_to_comply = 12 * g_scenario.requests[i].deadline_years;
    //    }
    //}
}

void scenario_request_activate(event_ph_t &event) {
    // the event is coming, but hasn't fired yet. this is always a slave / proper event object.
    // the "facade" event is taken care of the VIA_EVENT check from above - it will never fire.
    if (event.is_active) {
        return;
    }

    event.quest_months_left = event.months_initial;
    event.is_active = true;
    event.is_overdue = false;
    event.can_comply_dialog_shown = false;
}

void scenario_request_handle(event_ph_t &event, int caller_event_id, e_event_action &next_action) {
    if (!event.is_active) {
        return;
    }

    // advance time
    if (event.quest_months_left > 0) {
        event.quest_months_left--;
    }

    scenario_request request = scenario_request_get(event);
    if (request.event_id < 0) {
        return;
    }

    // handle request event immediately after activation!
    next_action = EVENT_ACTION_NONE;
    int pharaoh_alt_shift = (event.sender_faction == EVENT_FACTION_REQUEST_FROM_CITY ? 1 : 0);
    switch (event.event_state) {
    case e_event_state_finished:
        messages::popup("message_request_received", event.event_id, 0);
        if (!event.is_overdue) {
            g_city.kingdome.increase_success_request(3);
        }
        event.event_state = e_event_state_received;
        event.is_active = false;
        break;

    case e_event_state_finished_late:
        assert(!event.is_overdue);
        messages::popup("message_request_received_late", event.event_id, 0);
        g_city.kingdome.increase_success_request(1);
        event.event_state = e_event_state_received;
        event.is_active = false;
        break;

    case e_event_state_initial:
        event.event_state = e_event_state_in_progress;
        break;

    case e_event_state_in_progress:
        if (!event.can_comply_dialog_shown && g_city.resource.stored(request.resource) >= request.amount) {
            event.can_comply_dialog_shown = true;
            city_message &message = g_message_manager.post_common(true, "message_storage_yards_ready_to_fulfill_request", event.event_id, 0, GOD_UNKNOWN, 0);
            message.req_amount = request.resource_amount();
            message.req_resource = request.resource;
            message.req_months_left = request.months_to_comply;
        } else if (!event.appear_dialgow_shown) {
            // initial quest message
            event.appear_dialgow_shown = true;
            city_message_post_full(true, "message_template_request", &event, caller_event_id,
                                   PHRASE_general_request_title_P + pharaoh_alt_shift,
                                   PHRASE_general_request_initial_announcement_P + pharaoh_alt_shift,
                                   PHRASE_general_request_no_reason_P_A + pharaoh_alt_shift * 3,
                                   event.event_id, 0);

        } 
        
        if (event.quest_months_left == 6) {
            // reminder of 6 months left
            city_message_post_full(true, "message_template_request", &event, caller_event_id,
                                   PHRASE_general_request_title_P + pharaoh_alt_shift,
                                   PHRASE_general_request_reminder_P + pharaoh_alt_shift,
                                   PHRASE_general_request_no_reason_P_A + pharaoh_alt_shift * 3,
                                   event.event_id, 0);

        } else if (event.quest_months_left == 0) {
            g_city.kingdome.reduce_missed_request(3);
            event.event_state = e_event_state_overdue;
            event.is_overdue = true;
            event.quest_months_left = 24; // hardcoded

            // reprimand message
            city_message_post_full(true, "message_template_request", &event, caller_event_id,
                                   PHRASE_general_request_title_P + pharaoh_alt_shift,
                                   PHRASE_general_request_overdue_P + pharaoh_alt_shift,
                                   PHRASE_general_request_no_reason_P_A + pharaoh_alt_shift * 3,
                                   event.event_id,
                                   0);
        }
        break;

    case e_event_state_overdue:
        if (event.quest_months_left == 6) {
            // angry reminder of 6 months left?
            //                        city_message_post_full(true, MESSAGE_TEMPLATE_REQUEST, id,
            //                        caller_event_id,
            //                                               PHRASE_general_request_title_P + faction_mod,
            //                                               PHRASE_general_request_warning_P + faction_mod,
            //                                               PHRASE_general_request_no_reason_P_A + faction_mod
            //                                               * 3, id, 0);
        } else if (event.quest_months_left == 0) {
            g_city.kingdome.reduce_missed_request(2);
            event.event_state = e_event_state_failed;
            event.is_active = false;
            next_action = EVENT_ACTION_REFUSED;
        }
        break;
    }
}

void scenario_request_dispatch(int id) {
    scenario_request request = scenario_request_get_visible(id);
    if (!request.is_valid()) {
        return;
    }

    e_event_state new_state = (request.months_to_comply > 0)
                                    ? e_event_state_finished
                                    : e_event_state_finished_late;

    scenario_request_set_state(request, new_state);

    if (request.resource == RESOURCE_DEBEN) {
        events::emit(event_finance_process_request{ efinance_request_kigdome, uint32_t(request.amount) });
    } else if (request.resource == RESOURCE_TROOPS) {
        g_city.population.remove_for_troop_request(request.amount);
        events::emit(event_storageyards_remove_resource{ RESOURCE_WEAPONS, request.amount });
    } else {
        int amount = request.resource_amount();
        events::emit(event_city_remove_resource{ request.resource, amount });
    }
}

int scenario_requests_active_count() {
    int count = 0;
    for (int i = 0; i < g_scenario.events.events_count(); i++) {
        const event_ph_t* event = g_scenario.events.at(i);
        if (event->type == EVENT_TYPE_REQUEST && event->is_active
            && event->event_state <= e_event_state_overdue) {
            count++;
        }
    }
    return count;
}

scenario_request scenario_request_get(const event_ph_t &event) {
    scenario_request request;

    request.event_id = event.event_id;
    request.amount = event.amount.value;
    request.resource = (e_resource)event.item.value;
    request.state = event.event_state;
    request.months_to_comply = event.quest_months_left;

    return request;
}

void scenario_request_set_state(const scenario_request &request, e_event_state new_state) {
    event_ph_t *event = g_scenario.events.at(request.event_id);
    event->event_state = new_state;
}

void scenario_request_set_active(const scenario_request &request, bool active) {
    event_ph_t &event = *g_scenario.events.at(request.event_id);
    event.is_active = active;
}

std::vector<scenario_request> scenario_get_visible_requests() {
    std::vector<scenario_request> requests;

    for (int i = 0, size = g_scenario.events.events_count(); i < size; i++) {
        const event_ph_t* event = g_scenario.events.at(i);
        if (event->type == EVENT_TYPE_REQUEST && event->is_active && event->event_state <= e_event_state_overdue) {
            requests.push_back(scenario_request_get(*event));
        }
    }

    return requests;
}

scenario_request scenario_request_get_visible(int index) {
    int event_index = 0;
    if (index >= g_scenario.events.events_count()) {
        return {};
    }

    for (int i = 0; i < MAX_REQUESTS; i++) {
        const event_ph_t* event = g_scenario.events.at(i);
        if (!(event->type == EVENT_TYPE_REQUEST && event->is_active && event->event_state <= e_event_state_overdue)) {
            continue;
        }

        if (event_index == index) {
            return scenario_request_get(*event);
        }
        ++event_index;
    }

    return {};
}
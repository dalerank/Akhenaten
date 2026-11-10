#include "request.h"

#include "building/building_storage_yard.h"
#include "game/game_events.h"
#include "city/city_finance.h"
#include "city/city_message.h"
#include "city/city_warnings.h"
#include "city/ratings.h"
#include "city/city_resource.h"
#include "city/city.h"
#include "core/random.h"
#include "core/svector.h"
#include "graphics/elements/lang_text.h"
#include "scenario_event_manager.h"
#include "game/resource.h"
#include "scenario/scenario.h"
#include "scenario/distant_battle.h"
#include "city/legion_requests.h"
#include "figure/formation.h"
#include "event_phrases.h"

#include <algorithm>

namespace {
request_cleared_snapshot_t g_last_request_cleared;
} // namespace

void scenario_request_emit_cleared(const event_ph_t &event, bool fulfilled) {
    const int tag_id = (int)event.tag_id;
    const int resource = (int)event.item.value;
    const int fulfilled_i = fulfilled ? 1 : 0;
    const int was_overdue_i = event.is_overdue ? 1 : 0;

    g_last_request_cleared.tag_id = tag_id;
    g_last_request_cleared.resource = resource;
    g_last_request_cleared.fulfilled = fulfilled_i;
    g_last_request_cleared.was_overdue = was_overdue_i;
    g_last_request_cleared.seq += 1;

    events::emit(event_request_cleared{ tag_id, resource, fulfilled_i, was_overdue_i });
}

const request_cleared_snapshot_t &scenario_request_last_cleared() {
    return g_last_request_cleared;
}

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
        if (event.on_completed_action >= 0) {
            g_scenario.events.process_event(event.on_completed_action, true, EVENT_ACTION_COMPLETED, event.event_id);
        }
        scenario_request_emit_cleared(event, true);
        break;

    case e_event_state_finished_late:
        // Overdue-grace fulfill uses this path: was_overdue stays true for JS facts.
        messages::popup("message_request_received_late", event.event_id, 0);
        g_city.kingdome.increase_success_request(1);
        event.event_state = e_event_state_received;
        event.is_active = false;
        if (event.on_too_late_action >= 0) {
            g_scenario.events.process_event(event.on_too_late_action, true, EVENT_ACTION_TOOLATE, event.event_id);
        }
        scenario_request_emit_cleared(event, true);
        break;

    case e_event_state_initial:
        event.event_state = e_event_state_in_progress;
        // go to show message

    case e_event_state_in_progress:
        if (!event.can_comply_dialog_shown && g_city.resource.stored(request.resource) >= request.resource_amount()) {
            event.can_comply_dialog_shown = true;
            // OG Popup Messages: selected Compliance → auto-dispatch goods/deben + banner (I6).
            // Troop requests still need a manual advisor confirm (distant battle side-effects).
            if (popup_messages_want_banner(POPUP_MSG_COMPLIANCE)
                && request.resource != RESOURCE_TROOPS
                && scenario_request_dispatch_event(event.event_id)) {
                g_warning_manager.show_message_banner(lang_text_from_key("#goods_auto_dispatched"));
                break;
            }
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
            if (event.on_refusal_action >= 0) {
                g_scenario.events.process_event(event.on_refusal_action, true, EVENT_ACTION_REFUSED, event.event_id);
            }
            scenario_request_emit_cleared(event, false);
        }
        break;
    }
}

void scenario_request_dispatch(int id) {
    scenario_request request = scenario_request_get_visible(id);
    if (!request.is_valid()) {
        return;
    }

    event_ph_t *ev = g_scenario.events.at(request.event_id);
    if (!ev) {
        return;
    }

    // Troop asks with a defeat chain: defer ok/defeat to distant-battle resolution.
    // Requests without on_defeat_action keep the old immediate finished → completed path
    // (Selima and earlier missions).
    if (request.resource == RESOURCE_TROOPS && ev->on_defeat_action >= 0) {
        g_city.population.remove_for_troop_request(request.amount);
        events::emit(event_storageyards_remove_resource{ RESOURCE_WEAPONS, request.amount });

        ev->is_active = false; // hide from advisor; awaiting fight_distant_battle

        const int enemy_strength = std::min(255, std::max(1, request.amount));
        g_distant_battle.init_distant_battle(enemy_strength);
        if (ev->city_id > 0) {
            g_distant_battle.battle.city = (uint8_t)ev->city_id;
        } else {
            g_distant_battle.determine_distant_battle_city();
        }
        g_distant_battle.source_request_event_id = (int16_t)ev->event_id;
        // OG legion_requests: sea (aboard transport / warship) or land (exit) by route kind.
        formation_legions_dispatch_to_request(ev->event_id);

        int warships = 0;
        int legions = 0;
        int strength = formation_request_strength(ev->event_id, &warships, &legions);
        if (strength > 255) {
            strength = 255;
        }

        int num_soldiers = 0;
        bool any_on_ship = false;
        for (int i = 1; i < MAX_FORMATIONS; i++) {
            formation *m = formation_get(i);
            if (!m || !m->in_use || !m->own_batalion || m->request_event_id != ev->event_id) {
                continue;
            }
            num_soldiers += m->num_figures;
            if (formation_legion_is_on_ship(i)) {
                any_on_ship = true;
            }
        }

        if (strength > 0) {
            g_distant_battle.dispatch_to_distant_battle(strength, (uint8_t)std::min(255, num_soldiers));
            // Sea request: troops stay aboard — do not wait for land exit join.
            if (any_on_ship) {
                g_distant_battle.dispatched_army.await_soldiers = 0;
            }
        } else {
            g_distant_battle.battle.egyptian_strength = 0;
        }

        g_distant_battle.battle.months_until_battle = 1;
        if (g_distant_battle.battle.egyptian_months_to_travel_forth > 0) {
            g_distant_battle.battle.egyptian_months_to_travel_forth = 1;
        }
        return;
    }

    // Overdue-grace fulfill is late (on_too_late), not ok (on_completed).
    e_event_state new_state;
    if (ev->is_overdue) {
        new_state = e_event_state_finished_late;
    } else if (request.months_to_comply > 0) {
        new_state = e_event_state_finished;
    } else {
        new_state = e_event_state_finished_late;
    }

    scenario_request_set_state(request, new_state);

    if (request.resource == RESOURCE_DEBEN) {
        events::emit(event_finance_request{ efinance_request_kigdome, request.amount });
    } else if (request.resource == RESOURCE_TROOPS) {
        g_city.population.remove_for_troop_request(request.amount);
        events::emit(event_storageyards_remove_resource{ RESOURCE_WEAPONS, request.amount });
    } else {
        int amount = request.resource_amount();
        events::emit(event_city_remove_resource{ request.resource, amount });
    }
}

bool scenario_request_dispatch_event(int event_id) {
    const auto visible = scenario_get_visible_requests();
    for (int i = 0; i < (int)visible.size(); i++) {
        if (visible[i].event_id == event_id) {
            scenario_request_dispatch(i);
            return true;
        }
    }
    return false;
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
    if (event_ph_t* event = g_scenario.events.at(request.event_id)) {
        event->event_state = new_state;
    }
}

void scenario_request_set_active(const scenario_request &request, bool active) {
    if (event_ph_t* event = g_scenario.events.at(request.event_id)) {
        event->is_active = active;
    }
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
    const int total_events = g_scenario.events.events_count();
    if (index >= total_events) {
        return {};
    }

    for (int i = 0; i < total_events; i++) {
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

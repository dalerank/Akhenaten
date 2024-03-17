#include "request.h"

#include "building/building_storage_yard.h"
#include "city/finance.h"
#include "city/message.h"
#include "city/population.h"
#include "city/ratings.h"
#include "city/resource.h"
#include "core/random.h"
#include "core/svector.h"
#include "events.h"
#include "game/resource.h"
#include "game/time.h"
#include "game/tutorial.h"
#include "scenario/scenario_data.h"

void scenario_request_init() {
    //for (int i = 0; i < MAX_REQUESTS; i++) {
    //    random_generate_next();
    //    if (g_scenario_data.requests[i].resource) {
    //        g_scenario_data.requests[i].month = (random_byte() & 7) + 2;
    //        g_scenario_data.requests[i].months_to_comply = 12 * g_scenario_data.requests[i].deadline_years;
    //    }
    //}
}

void scenario_request_process_C3() {
    //for (int i = 0; i < MAX_REQUESTS; i++) {
    //    if (!g_scenario_data.requests[i].resource || g_scenario_data.requests[i].state > e_request_state_dispatched_late)
    //        continue;
    //
    //    int state = g_scenario_data.requests[i].state;
    //    if (state == e_request_state_dispatched || state == e_request_state_dispatched_late) {
    //        --g_scenario_data.requests[i].months_to_comply;
    //        if (g_scenario_data.requests[i].months_to_comply <= 0) {
    //            if (state == e_request_state_dispatched) {
    //                city_message_post(true, MESSAGE_REQUEST_RECEIVED, i, 0);
    //                city_ratings_change_kingdom(g_scenario_data.requests[i].kingdom);
    //            } else {
    //                city_message_post(true, MESSAGE_REQUEST_RECEIVED_LATE, i, 0);
    //                city_ratings_change_kingdom(g_scenario_data.requests[i].kingdom / 2);
    //            }
    //            g_scenario_data.requests[i].state = e_request_state_received;
    //            g_scenario_data.requests[i].visible = false;
    //        }
    //    } else {
    //        // normal or overdue
    //        if (g_scenario_data.requests[i].visible) {
    //            --g_scenario_data.requests[i].months_to_comply;
    //            if (state == e_request_state_normal) {
    //                if (g_scenario_data.requests[i].months_to_comply == 12) {
    //                    // reminder
    //                    city_message_post(true, MESSAGE_REQUEST_REMINDER, i, 0);
    //                } else if (g_scenario_data.requests[i].months_to_comply <= 0) {
    //                    city_message_post(true, MESSAGE_REQUEST_REFUSED, i, 0);
    //                    g_scenario_data.requests[i].state = e_request_state_overdue;
    //                    g_scenario_data.requests[i].months_to_comply = 24;
    //                    city_ratings_reduce_kingdom_missed_request(3);
    //                }
    //            } else if (state == e_request_state_overdue) {
    //                if (g_scenario_data.requests[i].months_to_comply <= 0) {
    //                    city_message_post(true, MESSAGE_REQUEST_REFUSED_OVERDUE, i, 0);
    //                    g_scenario_data.requests[i].state = e_request_state_ignored;
    //                    g_scenario_data.requests[i].visible = false;
    //                    city_ratings_reduce_kingdom_missed_request(5);
    //                }
    //            }
    //            if (!g_scenario_data.requests[i].can_comply_dialog_shown
    //                && city_resource_count(g_scenario_data.requests[i].resource)
    //                     >= g_scenario_data.requests[i].amount) {
    //                g_scenario_data.requests[i].can_comply_dialog_shown = 1;
    //                city_message_post(true, MESSAGE_REQUEST_CAN_COMPLY, i, 0);
    //            }
    //        } else {
    //            // request is not visible
    //            int year = g_scenario_data.start_year;
    //            if (!tutorial_adjust_request_year(&year))
    //                return;
    //            if (game_time_year() == year + g_scenario_data.requests[i].year
    //                && game_time_month() == g_scenario_data.requests[i].month) {
    //                g_scenario_data.requests[i].visible = true;
    //                if (city_resource_count(g_scenario_data.requests[i].resource) >= g_scenario_data.requests[i].amount)
    //                    g_scenario_data.requests[i].can_comply_dialog_shown = 1;
    //
    //                if (g_scenario_data.requests[i].resource == RESOURCE_DEBEN)
    //                    city_message_post(true, MESSAGE_KINGDOME_REQUESTS_MONEY, i, 0);
    //                else if (g_scenario_data.requests[i].resource == RESOURCE_TROOPS)
    //                    city_message_post(true, MESSAGE_KINGDOME_REQUESTS_ARMY, i, 0);
    //                else
    //                    city_message_post(true, MESSAGE_KINGDOME_REQUESTS_GOODS, i, 0);
    //            }
    //        }
    //    }
    //}
}

void scenario_request_dispatch(int id) {
    const scenario_request* request = scenario_request_get_visible(id);
    if (!request) {
        return;
    }

    e_request_stat new_state = (request->state == e_request_state_normal)
                                    ? e_request_state_dispatched
                                    : e_request_state_dispatched_late;

    scenario_request_set_state(*request, new_state);
    //scenario_request_delay(id, (random_byte() & 3) + 1);
    scenario_request_set_active(*request, false);

    if (request->resource == RESOURCE_DEBEN) {
        city_finance_process_requests_and_festivals(request->amount);
    } else if (request->resource == RESOURCE_TROOPS) {
        city_population_remove_for_troop_request(request->amount);
        building_storageyards_remove_resource(RESOURCE_WEAPONS, request->amount);
    } else {
        int amount = request->get_resource_amount();
        building_storageyards_remove_resource(request->resource, amount);
    }
}

int scenario_requests_active_count() {
    int count = 0;
    for (int i = 0; i < get_scenario_events_num(); i++) {
        const event_ph_t* event = get_scenario_event(i);
        if (event->type == EVENT_TYPE_REQUEST && event->is_active != 0
            && event->event_state <= EVENT_STATE_IN_PROGRESS) {
            count++;
        }
    }
    return count;
}

static const scenario_request *scenario_request_get(const event_ph_t &event) {
    static scenario_request request;

    request.event_id = event.event_id;
    request.amount = event.amount_fields[0];
    request.resource = (e_resource)event.item_fields[0];
    request.state = event.event_state;
    request.months_to_comply = event.quest_months_left;

    return &request;
}

void scenario_request_set_state(const scenario_request &request, e_request_stat new_state) {
    event_ph_t &event = *set_scenario_event(request.event_id);
    event.event_state = new_state;
}

void scenario_request_set_active(const scenario_request &request, bool active) {
    event_ph_t &event = *set_scenario_event(request.event_id);
    event.is_active = active;
}

const scenario_request* scenario_request_get_visible(int index) {
    int event_index = 0;
    for (int i = 0; i < MAX_REQUESTS; i++) {
        if (i >= get_scenario_events_num()) {
            return nullptr;
        }
        
        const event_ph_t* event = get_scenario_event(i);
        if (event->type == EVENT_TYPE_REQUEST && event->is_active && event->event_state <= EVENT_STATE_IN_PROGRESS) {
            if (event_index == index) {
                return scenario_request_get(*event);
            }
            ++event_index;
        }
    }

    return nullptr;
}

int scenario_request_foreach_visible(int start_index, void (*callback)(int index, const scenario_request* request)) {
    int index = start_index;
    for (int i = 0; i < MAX_REQUESTS; i++) {
        auto request = scenario_request_get_visible(i);
        if (request) {
            callback(index, request);
            index++;
        }
    }

    return index;
}
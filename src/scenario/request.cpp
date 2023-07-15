#include "request.h"

#include "building/warehouse.h"
#include "city/finance.h"
#include "city/message.h"
#include "city/population.h"
#include "city/ratings.h"
#include "city/resource.h"
#include "core/random.h"
#include "game/resource.h"
#include "game/time.h"
#include "game/tutorial.h"
#include "scenario/data.h"
#include "events.h"

void scenario_request_init(void) {
    for (int i = 0; i < MAX_REQUESTS; i++) {
        random_generate_next();
        if (g_scenario_data.requests[i].resource) {
            g_scenario_data.requests[i].month = (random_byte() & 7) + 2;
            g_scenario_data.requests[i].months_to_comply = 12 * g_scenario_data.requests[i].deadline_years;
        }
    }
}

void scenario_request_process_C3(void) {
    for (int i = 0; i < MAX_REQUESTS; i++) {
        if (!g_scenario_data.requests[i].resource || g_scenario_data.requests[i].state > REQUEST_STATE_DISPATCHED_LATE)
            continue;

        int state = g_scenario_data.requests[i].state;
        if (state == REQUEST_STATE_DISPATCHED || state == REQUEST_STATE_DISPATCHED_LATE) {
            --g_scenario_data.requests[i].months_to_comply;
            if (g_scenario_data.requests[i].months_to_comply <= 0) {
                if (state == REQUEST_STATE_DISPATCHED) {
                    city_message_post(true, MESSAGE_REQUEST_RECEIVED, i, 0);
                    city_ratings_change_kingdom(g_scenario_data.requests[i].kingdom);
                } else {
                    city_message_post(true, MESSAGE_REQUEST_RECEIVED_LATE, i, 0);
                    city_ratings_change_kingdom(g_scenario_data.requests[i].kingdom / 2);
                }
                g_scenario_data.requests[i].state = REQUEST_STATE_RECEIVED;
                g_scenario_data.requests[i].visible = false;
            }
        } else {
            // normal or overdue
            if (g_scenario_data.requests[i].visible) {
                --g_scenario_data.requests[i].months_to_comply;
                if (state == REQUEST_STATE_NORMAL) {
                    if (g_scenario_data.requests[i].months_to_comply == 12) {
                        // reminder
                        city_message_post(true, MESSAGE_REQUEST_REMINDER, i, 0);
                    } else if (g_scenario_data.requests[i].months_to_comply <= 0) {
                        city_message_post(true, MESSAGE_REQUEST_REFUSED, i, 0);
                        g_scenario_data.requests[i].state = REQUEST_STATE_OVERDUE;
                        g_scenario_data.requests[i].months_to_comply = 24;
                        city_ratings_reduce_kingdom_missed_request(3);
                    }
                } else if (state == REQUEST_STATE_OVERDUE) {
                    if (g_scenario_data.requests[i].months_to_comply <= 0) {
                        city_message_post(true, MESSAGE_REQUEST_REFUSED_OVERDUE, i, 0);
                        g_scenario_data.requests[i].state = REQUEST_STATE_IGNORED;
                        g_scenario_data.requests[i].visible = false;
                        city_ratings_reduce_kingdom_missed_request(5);
                    }
                }
                if (!g_scenario_data.requests[i].can_comply_dialog_shown &&
                    city_resource_count(g_scenario_data.requests[i].resource) >= g_scenario_data.requests[i].amount) {
                    g_scenario_data.requests[i].can_comply_dialog_shown = 1;
                    city_message_post(true, MESSAGE_REQUEST_CAN_COMPLY, i, 0);
                }
            } else {
                // request is not visible
                int year = g_scenario_data.start_year;
                if (!tutorial_adjust_request_year(&year))
                    return;
                if (game_time_year() == year + g_scenario_data.requests[i].year &&
                    game_time_month() == g_scenario_data.requests[i].month) {
                    g_scenario_data.requests[i].visible = true;
                    if (city_resource_count(g_scenario_data.requests[i].resource) >= g_scenario_data.requests[i].amount)
                        g_scenario_data.requests[i].can_comply_dialog_shown = 1;

                    if (g_scenario_data.requests[i].resource == RESOURCE_DEBEN)
                        city_message_post(true, MESSAGE_CAESAR_REQUESTS_MONEY, i, 0);
                    else if (g_scenario_data.requests[i].resource == RESOURCE_TROOPS)
                        city_message_post(true, MESSAGE_CAESAR_REQUESTS_ARMY, i, 0);
                    else
                        city_message_post(true, MESSAGE_CAESAR_REQUESTS_GOODS, i, 0);
                }
            }
        }
    }
}
void scenario_request_dispatch(int id) {
    if (g_scenario_data.requests[id].state == REQUEST_STATE_NORMAL)
        g_scenario_data.requests[id].state = REQUEST_STATE_DISPATCHED;
    else {
        g_scenario_data.requests[id].state = REQUEST_STATE_DISPATCHED_LATE;
    }
    g_scenario_data.requests[id].months_to_comply = (random_byte() & 3) + 1;
    g_scenario_data.requests[id].visible = 0;
    int amount = g_scenario_data.requests[id].amount;
    if (g_scenario_data.requests[id].resource == RESOURCE_DEBEN)
        city_finance_process_requests_and_festivals(amount);
    else if (g_scenario_data.requests[id].resource == RESOURCE_TROOPS) {
        city_population_remove_for_troop_request(amount);
        building_warehouses_remove_resource(RESOURCE_WEAPONS, amount);
    } else
        building_warehouses_remove_resource(g_scenario_data.requests[id].resource, amount);
}

int scenario_requests_active_count() {
    int count = 0;
    if (GAME_ENV == ENGINE_ENV_C3) {
        for (int i = 0; i < MAX_REQUESTS; i++) {
            if (g_scenario_data.requests[i].resource && g_scenario_data.requests[i].visible &&
                g_scenario_data.requests[i].state <= 1) {
                count++;
            }
        }
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        for (int i = 0; i < get_scenario_events_num(); i++) {
            const event_ph_t *event = get_scenario_event(i);
            if (event->type == EVENT_TYPE_REQUEST && event->is_active != 0 &&
                event->event_state <= EVENT_STATE_IN_PROGRESS) {
                count++;
            }
        }
    }
    return count;
}

const scenario_request *scenario_request_get(int id) {
    static scenario_request request;
    if (GAME_ENV == ENGINE_ENV_C3) {
        request.id = id;
        request.amount = g_scenario_data.requests[id].amount;
        request.resource = g_scenario_data.requests[id].resource;
        request.state = g_scenario_data.requests[id].state;
        request.months_to_comply = g_scenario_data.requests[id].months_to_comply;
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        request.id = id;
        auto event = get_scenario_event(id);
        request.amount = event->amount_fields[0];
        request.resource = event->item_fields[0];
        request.state = event->event_state;
        request.months_to_comply = event->quest_months_left;
    }
    return &request;
}
const scenario_request *scenario_request_get_visible(int index) {
    if (GAME_ENV == ENGINE_ENV_C3) {
        for (int i = 0; i < MAX_REQUESTS; i++) {
            if (g_scenario_data.requests[i].resource && g_scenario_data.requests[i].visible &&
                g_scenario_data.requests[i].state <= 1) {
                if (index == 0)
                    return scenario_request_get(i);
                index--; // I have no idea
            }
        }
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        int event_index = -1;
        for (int i = 0; i < MAX_REQUESTS; i++) {
            const event_ph_t *event;
            do {
                event_index++;
                if (event_index >= get_scenario_events_num())
                    return 0;
                event = get_scenario_event(event_index);
            } while (event->type != EVENT_TYPE_REQUEST || event->is_active == 0);

            if (event->event_state <= EVENT_STATE_IN_PROGRESS) {
                if (index == 0)
                    return scenario_request_get(event_index);
                index--;
            }
        }
    }
    return 0;
}

int scenario_request_foreach_visible(int start_index, void (*callback)(int index, const scenario_request *request)) {
    int index = start_index;
    if (GAME_ENV == ENGINE_ENV_C3) {
        for (int i = 0; i < MAX_REQUESTS; i++) {
            if (g_scenario_data.requests[i].resource && g_scenario_data.requests[i].visible) {
                callback(index, scenario_request_get(i));
                index++;
            }
        }
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        for (int i = 0; i < MAX_REQUESTS; i++) {
            auto request = scenario_request_get_visible(i);
            if (request) {
                callback(index, request);
                index++;
            }
        }
    }
    return index;
}
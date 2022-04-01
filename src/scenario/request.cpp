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
    for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++) {
        random_generate_next();
        if (scenario_data.requests[i].resource) {
            scenario_data.requests[i].month = (random_byte() & 7) + 2;
            scenario_data.requests[i].months_to_comply = 12 * scenario_data.requests[i].deadline_years;
        }
    }
}

void scenario_request_process_C3(void) {
    for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++) {
        if (!scenario_data.requests[i].resource || scenario_data.requests[i].state > REQUEST_STATE_DISPATCHED_LATE)
            continue;

        int state = scenario_data.requests[i].state;
        if (state == REQUEST_STATE_DISPATCHED || state == REQUEST_STATE_DISPATCHED_LATE) {
            --scenario_data.requests[i].months_to_comply;
            if (scenario_data.requests[i].months_to_comply <= 0) {
                if (state == REQUEST_STATE_DISPATCHED) {
                    city_message_post(true, MESSAGE_REQUEST_RECEIVED, i, 0);
                    city_ratings_change_favor(scenario_data.requests[i].favor);
                } else {
                    city_message_post(true, MESSAGE_REQUEST_RECEIVED_LATE, i, 0);
                    city_ratings_change_favor(scenario_data.requests[i].favor / 2);
                }
                scenario_data.requests[i].state = REQUEST_STATE_RECEIVED;
                scenario_data.requests[i].visible = false;
            }
        } else {
            // normal or overdue
            if (scenario_data.requests[i].visible) {
                --scenario_data.requests[i].months_to_comply;
                if (state == REQUEST_STATE_NORMAL) {
                    if (scenario_data.requests[i].months_to_comply == 12) {
                        // reminder
                        city_message_post(true, MESSAGE_REQUEST_REMINDER, i, 0);
                    } else if (scenario_data.requests[i].months_to_comply <= 0) {
                        city_message_post(true, MESSAGE_REQUEST_REFUSED, i, 0);
                        scenario_data.requests[i].state = REQUEST_STATE_OVERDUE;
                        scenario_data.requests[i].months_to_comply = 24;
                        city_ratings_reduce_favor_missed_request(3);
                    }
                } else if (state == REQUEST_STATE_OVERDUE) {
                    if (scenario_data.requests[i].months_to_comply <= 0) {
                        city_message_post(true, MESSAGE_REQUEST_REFUSED_OVERDUE, i, 0);
                        scenario_data.requests[i].state = REQUEST_STATE_IGNORED;
                        scenario_data.requests[i].visible = false;
                        city_ratings_reduce_favor_missed_request(5);
                    }
                }
                if (!scenario_data.requests[i].can_comply_dialog_shown &&
                    city_resource_count(scenario_data.requests[i].resource) >= scenario_data.requests[i].amount) {
                    scenario_data.requests[i].can_comply_dialog_shown = 1;
                    city_message_post(true, MESSAGE_REQUEST_CAN_COMPLY, i, 0);
                }
            } else {
                // request is not visible
                int year = scenario_data.start_year;
                if (!tutorial_adjust_request_year(&year))
                    return;
                if (game_time_year() == year + scenario_data.requests[i].year &&
                    game_time_month() == scenario_data.requests[i].month) {
                    scenario_data.requests[i].visible = true;
                    if (city_resource_count(scenario_data.requests[i].resource) >= scenario_data.requests[i].amount)
                        scenario_data.requests[i].can_comply_dialog_shown = 1;

                    if (scenario_data.requests[i].resource == RESOURCE_DENARII)
                        city_message_post(true, MESSAGE_CAESAR_REQUESTS_MONEY, i, 0);
                    else if (scenario_data.requests[i].resource == RESOURCE_TROOPS_C3)
                        city_message_post(true, MESSAGE_CAESAR_REQUESTS_ARMY, i, 0);
                    else
                        city_message_post(true, MESSAGE_CAESAR_REQUESTS_GOODS, i, 0);
                }
            }
        }
    }
}
void scenario_request_dispatch(int id) {
    if (scenario_data.requests[id].state == REQUEST_STATE_NORMAL)
        scenario_data.requests[id].state = REQUEST_STATE_DISPATCHED;
    else {
        scenario_data.requests[id].state = REQUEST_STATE_DISPATCHED_LATE;
    }
    scenario_data.requests[id].months_to_comply = (random_byte() & 3) + 1;
    scenario_data.requests[id].visible = 0;
    int amount = scenario_data.requests[id].amount;
    if (scenario_data.requests[id].resource == RESOURCE_DENARII)
        city_finance_process_requests_and_festivals(amount);
    else if (scenario_data.requests[id].resource == RESOURCE_TROOPS_C3) {
        city_population_remove_for_troop_request(amount);
        building_warehouses_remove_resource(RESOURCE_WEAPONS_C3, amount);
    } else
        building_warehouses_remove_resource(scenario_data.requests[id].resource, amount);
}

int scenario_requests_active_count() {
    int count = 0;
    if (GAME_ENV == ENGINE_ENV_C3) {
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++) {
            if (scenario_data.requests[i].resource && scenario_data.requests[i].visible &&
                scenario_data.requests[i].state <= 1) {
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
        request.amount = scenario_data.requests[id].amount;
        request.resource = scenario_data.requests[id].resource;
        request.state = scenario_data.requests[id].state;
        request.months_to_comply = scenario_data.requests[id].months_to_comply;
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
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++) {
            if (scenario_data.requests[i].resource && scenario_data.requests[i].visible &&
                scenario_data.requests[i].state <= 1) {
                if (index == 0)
                    return scenario_request_get(i);
                index--; // I have no idea
            }
        }
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        int event_index = -1;
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++) {
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
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++) {
            if (scenario_data.requests[i].resource && scenario_data.requests[i].visible) {
                callback(index, scenario_request_get(i));
                index++;
            }
        }
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++) {
            auto request = scenario_request_get_visible(i);
            if (request) {
                callback(index, request);
                index++;
            }
        }
    }
    return index;
}
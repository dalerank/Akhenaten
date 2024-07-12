#pragma once

#include "game/resource.h"
#include "scenario/events.h"
#include <functional>

struct scenario_request {
    int event_id = -1;
    int state = 0;
    e_resource resource = RESOURCE_NONE;
    int amount = 0;
    int months_to_comply = 0;

    bool is_valid() const { return event_id >= 0; }
    int resource_amount() const { return resource == RESOURCE_DEBEN ? amount : amount * 100; }
};

void scenario_request_init();

void scenario_request_dispatch(int id);

int scenario_requests_active_count();
void scenario_request_set_state(const scenario_request &r, e_event_state new_state);
void scenario_request_set_active(const scenario_request &r, bool active);
void scenario_request_handle(event_ph_t &event, int caller_event_id, e_event_action &next_action);

scenario_request scenario_request_get_visible(int index);

using request_visitor = std::function<void(int, const scenario_request *)>;
int scenario_request_foreach_visible(int start_index, request_visitor cb);

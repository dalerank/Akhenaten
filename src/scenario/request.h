#pragma once

#include "game/resource.h"

enum e_request_stat {
    e_request_state_normal = 0,
    e_request_state_in_progress = 1,
    e_request_state_overdue = 1,
    e_request_state_dispatched = 2,
    e_request_state_dispatched_late = 3,
    e_request_state_ignored = 4,
    e_request_state_received = 5
};

struct scenario_request {
    int event_id = 0;
    int state = 0;
    e_resource resource = RESOURCE_NONE;
    int amount = 0;
    int months_to_comply = 0;

    int get_resource_amount() const { return amount * 100; }
};

void scenario_request_init();

void scenario_request_process_C3();
void scenario_request_dispatch(int id);

int scenario_requests_active_count();
void scenario_request_set_state(const scenario_request &r, e_request_stat new_state);
void scenario_request_set_active(const scenario_request &r, bool active);

const scenario_request* scenario_request_get_visible(int index);

int scenario_request_foreach_visible(int start_index, void (*callback)(int index, const scenario_request* request));

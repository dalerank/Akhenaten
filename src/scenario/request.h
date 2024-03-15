#pragma once

#include "game/resource.h"

enum e_request_stat {
    e_request_state_normal = 0,
    e_request_state_overdue = 1,
    e_request_state_dispatched = 2,
    e_request_state_dispatched_late = 3,
    e_request_state_ignored = 4,
    e_request_state_received = 5
};

struct scenario_request {
    int id;
    int state;
    e_resource resource;
    int amount;
    int months_to_comply;
};

void scenario_request_init(void);

void scenario_request_process_C3(void);
void scenario_request_dispatch(int id);

int scenario_requests_active_count();

const scenario_request* scenario_request_get(int id);
const scenario_request* scenario_request_get_visible(int index);

int scenario_request_foreach_visible(int start_index, void (*callback)(int index, const scenario_request* request));

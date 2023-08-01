#ifndef SCENARIO_REQUEST_H
#define SCENARIO_REQUEST_H

enum {
    REQUEST_STATE_NORMAL = 0,
    REQUEST_STATE_OVERDUE = 1,
    REQUEST_STATE_DISPATCHED = 2,
    REQUEST_STATE_DISPATCHED_LATE = 3,
    REQUEST_STATE_IGNORED = 4,
    REQUEST_STATE_RECEIVED = 5
};

typedef struct {
    int id;
    int state;
    int resource;
    int amount;
    int months_to_comply;
} scenario_request;

void scenario_request_init(void);

void scenario_request_process_C3(void);
void scenario_request_dispatch(int id);

int scenario_requests_active_count();

const scenario_request* scenario_request_get(int id);
const scenario_request* scenario_request_get_visible(int index);

int scenario_request_foreach_visible(int start_index, void (*callback)(int index, const scenario_request* request));

#endif // SCENARIO_REQUEST_H

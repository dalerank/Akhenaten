#pragma once

#include "game/resource.h"
#include "scenario/scenario_event_manager.h"
#include "core/bstring.h"
#include <functional>

// Factual request close signal for JS. C++ stores/emits facts only —
// ok/late/refuse policy and chain reactions live in scripts.
struct event_request_cleared {
    int tag_id = 0;
    int resource = 0;
    int fulfilled = 0;   // 1 = player dispatched goods/troops/deben
    int was_overdue = 0; // 1 = past initial deadline (grace or refuse)
};

inline void describe_into(bstring256 &s, const event_request_cleared &ev) {
    s.printf("tag=%d res=%d fulfilled=%d overdue=%d", ev.tag_id, ev.resource, ev.fulfilled, ev.was_overdue);
}

struct scenario_request {
    int event_id = -1;
    int state = 0;
    e_resource resource = RESOURCE_NONE;
    int amount = 0;
    int months_to_comply = 0;

    bool is_valid() const { return event_id >= 0; }
    int resource_amount() const { return resource == RESOURCE_DEBEN ? amount : amount * 100; }
};

// Last cleared snapshot for integral tests / debug (updated on every emit).
struct request_cleared_snapshot_t {
    int tag_id = 0;
    int resource = 0;
    int fulfilled = 0;
    int was_overdue = 0;
    int seq = 0;
};

const request_cleared_snapshot_t &scenario_request_last_cleared();

// Emit factual close for JS (ok/late/refuse policy stays in scripts).
void scenario_request_emit_cleared(const event_ph_t &event, bool fulfilled);

void scenario_request_init();

void scenario_request_dispatch(int id);
// Dispatch by event_id (finds visible slot). Returns false if not visible/active.
bool scenario_request_dispatch_event(int event_id);

int scenario_requests_active_count();
void scenario_request_set_state(const scenario_request &r, e_event_state new_state);
void scenario_request_set_active(const scenario_request &r, bool active);
void scenario_request_handle(event_ph_t &event, int caller_event_id, e_event_action &next_action);
void scenario_request_activate(event_ph_t &event);

// The empire route of the request city, -1 without one.
int scenario_request_route(const event_ph_t& e);
// OG event_helpers.c scenario_event_travel_months for a request; 0 without a route.
int scenario_request_travel_months(const event_ph_t& e);

scenario_request scenario_request_get(const event_ph_t &event);
scenario_request scenario_request_get_visible(int index);

std::vector<scenario_request> scenario_get_visible_requests();

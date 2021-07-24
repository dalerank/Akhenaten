#include <core/buffer.h>
#include "events.h"

#define MAX_EVENTS 150

struct {
    event_ph_t events[MAX_EVENTS];
    int num_of_events;
} data;

const event_ph_t *get_scenario_event(int id) {
    return &data.events[id];
}


static void single_event_activate(int id, bool via_event_trigger) {
    event_ph_t *event = &data.events[id];

    // can not invoke event from an event if trigger is set to global update
    // also, can not invoke from global update if trigger is set to event only
    if (event->event_trigger_type == EVENT_TRIGGER_ONLY_VIA_EVENT && !via_event_trigger)
        return;
    if (event->event_trigger_type != EVENT_TRIGGER_ONLY_VIA_EVENT && via_event_trigger)
        return;

    // ..... TODO: actual event mechanisms...
}
static bool single_event_process_from_global_update(int id) {
    event_ph_t *event = &data.events[id];
    switch (event->event_trigger_type) {
        case EVENT_TRIGGER_ONCE:
            break;
        case EVENT_TRIGGER_RECURRING:
            break;
        case EVENT_TRIGGER_BY_RATING:
            break;
    }
}
void scenario_event_process() {
    for (int i = 0; i < data.num_of_events; i++)
        single_event_process_from_global_update(i);
}

void scenario_events_save_state(buffer *buf) {

}
void scenario_events_load_state(buffer *buf) {
    data.num_of_events = 0;
    for (int i = 0; i < MAX_EVENTS; i++) {

        // first value is total number of events stored
        int recorded_total_header = buf->read_i16();
        if (i == 0 && recorded_total_header != -1)
            data.num_of_events = recorded_total_header;
        if (i >= data.num_of_events)
            return;

        event_ph_t *event = &data.events[i];
            event->__unk01 = buf->read_i16();
        event->event_id = buf->read_i16();
        event->event_type = buf->read_i8();
        event->month = buf->read_i8();
            event->__unk03 = buf->read_i16();
        event->item_1 = buf->read_i16();
        event->item_2 = buf->read_i16();
        event->item_3 = buf->read_i16();
            event->__unk04 = buf->read_i16();
        event->amount_FIXED = buf->read_i16();
        event->amount_MIN = buf->read_i16();
        event->amount_MAX = buf->read_i16();
            event->__unk05 = buf->read_i16();
        event->year_or_month_FIXED = buf->read_i16();
        event->year_or_month_MIN = buf->read_i16();
        event->year_or_month_MAX = buf->read_i16();
            event->__unk06 = buf->read_i16();
        event->city_or_marker_FIXED = buf->read_i16();
        event->city_or_marker_MIN = buf->read_i16();
        event->city_or_marker_MAX = buf->read_i16();
        event->on_complete_action = buf->read_i16();
        event->on_refusal_action = buf->read_i16();
        event->event_trigger_type = buf->read_i16();
            event->__unk07 = buf->read_i16();
        event->timer_initial = buf->read_i16();
        event->timer_time_until = buf->read_i16(); // 0B 00 ......   XX 00 --> 0C 00
        event->timer_trigger_state = buf->read_i16();
        event->timer_missed_but_keep_trying = buf->read_i16();
            event->__unk11 = buf->read_i16();
        event->festival_deity = buf->read_i8();
            event->__unk12_i8 = buf->read_i8();
        event->invasion_attack_target = buf->read_i8();
            // ...
            // ...
            // ...
            buf->skip(25);
        event->on_tooLate_action = buf->read_i16();
        event->on_defeat_action = buf->read_i16();
        event->event_source_faction = buf->read_i8();
            event->__unk13_i8 = buf->read_i8();
            event->__unk14 = buf->read_i16();
        event->route_FIXED = buf->read_i16();
        event->route_MIN = buf->read_i16();
        event->route_MAX = buf->read_i16();
        event->event_subtype = buf->read_i8();
            event->__unk15_i8 = buf->read_i8();
            event->__unk16 = buf->read_i16();
            event->__unk17 = buf->read_i16();
            event->__unk18 = buf->read_i16();
            event->__unk19 = buf->read_i16();
        event->on_complete_msgAlt = buf->read_i8();
        event->on_refusal_msgAlt = buf->read_i8();
        event->on_tooLate_msgAlt = buf->read_i8();
        event->on_loss_msgAlt = buf->read_i8();
            event->__unk20_FIXED = buf->read_i16();
            event->__unk20_MIN = buf->read_i16();
            event->__unk20_MAX = buf->read_i16();
            event->__unk21 = buf->read_i16();
            event->__unk22 = buf->read_i16();
    }
}

#include "scenario/scenario_event_manager_chunks.h"

#include "scenario/scenario_event_manager.h"
#include "core/xvalue.h"
#include "io/io_buffer.h"

#include <algorithm>

static void bind_event_ph(io_buffer* iob, event_ph_t& event) {
    iob->bind(BIND_SIGNATURE_INT16, &event.num_total_header);
    iob->bind(BIND_SIGNATURE_INT16, &event.__unk01);
    iob->bind(BIND_SIGNATURE_INT16, &event.event_id);
    iob->bind(BIND_SIGNATURE_INT8, &event.type);
    iob->bind(BIND_SIGNATURE_INT8, &event.time.month);
    iob->bind(BIND_SIGNATURE_INT16, &event.item.value);
    iob->bind(BIND_SIGNATURE_INT16, &event.item.f_fixed);
    iob->bind(BIND_SIGNATURE_INT16, &event.item.f_min);
    iob->bind(BIND_SIGNATURE_INT16, &event.item.f_max);
    iob->bind(BIND_SIGNATURE_INT16, &event.amount.value);
    iob->bind(BIND_SIGNATURE_INT16, &event.amount.f_fixed);
    iob->bind(BIND_SIGNATURE_INT16, &event.amount.f_min);
    iob->bind(BIND_SIGNATURE_INT16, &event.amount.f_max);
    iob->bind(BIND_SIGNATURE_INT16, &event.time.year);
    iob->bind____skip(2); // (BIND_SIGNATURE_INT16, &event.time.unk01);
    iob->bind(BIND_SIGNATURE_INT16, &event.time.unk02);
    iob->bind(BIND_SIGNATURE_INT16, &event.time.unk03);
    iob->bind(BIND_SIGNATURE_INT16, &event.location_fields[0]);
    iob->bind(BIND_SIGNATURE_INT16, &event.location_fields[1]);
    iob->bind(BIND_SIGNATURE_INT16, &event.location_fields[2]);
    iob->bind(BIND_SIGNATURE_INT16, &event.location_fields[3]);
    iob->bind(BIND_SIGNATURE_INT16, &event.on_completed_action);
    iob->bind(BIND_SIGNATURE_INT16, &event.on_refusal_action);
    iob->bind(BIND_SIGNATURE_INT8, &event.event_trigger_type);
    iob->bind____skip(1);
    iob->bind_u16(event.tag_id); // original unk07; JS mission requests key off this
    iob->bind(BIND_SIGNATURE_INT16, &event.months_initial);
    iob->bind(BIND_SIGNATURE_INT16, &event.quest_months_left);
    iob->bind(BIND_SIGNATURE_INT8, &event.event_state);
    iob->bind(BIND_SIGNATURE_INT8, &event.is_overdue);
    iob->bind(BIND_SIGNATURE_INT8, &event.is_active);
    iob->bind(BIND_SIGNATURE_INT8, &event.can_comply_dialog_shown);
    iob->bind(BIND_SIGNATURE_INT16, &event.parent_id);
    iob->bind(BIND_SIGNATURE_INT8, &event.phrase_var);
    iob->bind(BIND_SIGNATURE_INT8, &event.reserved_unk12);
    iob->bind(BIND_SIGNATURE_INT8, &event.invasion_attack_target);
    iob->bind_bool(event.appear_dialgow_shown);
    iob->bind(BIND_SIGNATURE_INT16, &event.data.earthquake.duration);
    iob->bind(BIND_SIGNATURE_INT16, &event.data.earthquake.delay);
    iob->bind(BIND_SIGNATURE_INT16, &event.data.earthquake.ticks);
    for (int16_t& l : event.data.earthquake.locations) {
        iob->bind(BIND_SIGNATURE_INT16, &l);
    }
    iob->bind(BIND_SIGNATURE_INT16, &event.earthquake_step);
    iob->bind(BIND_SIGNATURE_INT16, &event.on_too_late_action);
    iob->bind(BIND_SIGNATURE_INT16, &event.on_defeat_action);
    iob->bind(BIND_SIGNATURE_INT8, &event.sender_faction);
    iob->bind(BIND_SIGNATURE_UINT8, &event.invasion_warnings_shown);
    iob->bind(BIND_SIGNATURE_INT16, &event.route_fields[0]);
    iob->bind(BIND_SIGNATURE_INT16, &event.route_fields[1]);
    iob->bind(BIND_SIGNATURE_INT16, &event.route_fields[2]);
    iob->bind(BIND_SIGNATURE_INT16, &event.route_fields[3]);
    iob->bind(BIND_SIGNATURE_INT8, &event.subtype);
    iob->bind(BIND_SIGNATURE_INT8, &event.city_id);
    iob->bind(BIND_SIGNATURE_UINT8, &event.coin);
    iob->bind(BIND_SIGNATURE_UINT8, &event.parent_city);
    iob->bind(BIND_SIGNATURE_INT16, &event.image.pack);
    iob->bind(BIND_SIGNATURE_INT16, &event.image.id);
    iob->bind(BIND_SIGNATURE_INT16, &event.image.offset);
    iob->bind(BIND_SIGNATURE_INT8, &event.on_completed_msgAlt);
    iob->bind(BIND_SIGNATURE_INT8, &event.on_refusal_msgAlt);
    iob->bind(BIND_SIGNATURE_INT8, &event.on_tooLate_msgAlt);
    iob->bind(BIND_SIGNATURE_INT8, &event.on_defeat_msgAlt);
    iob->bind(BIND_SIGNATURE_INT16, &event.reserved_1);
    iob->bind(BIND_SIGNATURE_RAW, event.reasons.data(), sizeof(event.reasons));
}

void scenario_events_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = xvalue<events_data_t>::ref();

    if (iob->is_read_access()) {
        data.event_list.clear();
        event_ph_t first{};
        bind_event_ph(iob, first);
        int n = first.num_total_header;
        if (n < 1) {
            n = 1;
        }
        if (n > MAX_EVENTS) {
            n = MAX_EVENTS;
        }
        data.event_list.resize(n);
        data.event_list[0] = first;
        for (int i = 1; i < n; i++) {
            bind_event_ph(iob, data.event_list[i]);
        }
        return;
    }

    if (!data.event_list.empty()) {
        data.event_list.front().num_total_header = (int16_t)data.event_list.size();
    }
    const int n = std::min((int)data.event_list.size(), MAX_EVENTS);
    for (int i = 0; i < n; i++) {
        bind_event_ph(iob, data.event_list[i]);
    }
}

void scenario_events_extra_chunk::bind_data(io_buffer* iob, size_t version) {
    // TODO ????????
}

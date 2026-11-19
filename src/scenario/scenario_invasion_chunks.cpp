#include "scenario/scenario_invasion_chunks.h"

#include "scenario/scenario_invasion.h"
#include "io/io_buffer.h"

void invasion_warnings_chunk::bind_data(io_buffer* iob, size_t version) {
    for (auto& w : g_invasions.warnings) {
        iob->bind_bool(w.in_use);
        iob->bind_bool(w.handled);
        iob->bind(BIND_SIGNATURE_UINT8, &w.invasion_path_id);
        iob->bind(BIND_SIGNATURE_UINT8, &w.warning_years);
        iob->bind_vec2i_compat(w.pos);
        iob->bind(BIND_SIGNATURE_INT16, &w.image_id);
        iob->bind(BIND_SIGNATURE_INT16, &w.empire_object_id);
        iob->bind(BIND_SIGNATURE_INT16, &w.month_notified);
        iob->bind(BIND_SIGNATURE_INT16, &w.year_notified);
        iob->bind(BIND_SIGNATURE_INT32, &w.months_to_go);
        iob->bind(BIND_SIGNATURE_UINT8, &w.invasion_id);
        iob->bind____skip(11);
    }
}

void invasion_event_pending_chunk::bind_data(io_buffer* iob, size_t version) {
    iob->bind____skip(272);
}

void invasion_event_pending_chunk::load_defaults(size_t version) {
    // v172 stub: the chunk holds no state, it only keeps a slot in the old positional
    // layout. The defaulter exists to mark it optional for saves older than v172.
}

void invasion_runtime_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_invasions;
    iob->bind(BIND_SIGNATURE_INT32, &data.history_count);
    iob->bind(BIND_SIGNATURE_INT32, &data.history_next);
    for (auto& b : data.binds) {
        iob->bind_bool(b.in_use);
        iob->bind_bool(b.enemies_seen);
        iob->bind_u8(b.invasion_id);
        iob->bind____skip(1);
        iob->bind_u16(b.seq);
        iob->bind_u16(b.on_completed_tag);
        iob->bind_u16(b.on_refusal_tag);
        iob->bind_u16(b.on_defeat_tag);
    }
    for (auto& h : data.history) {
        iob->bind_u16(h.seq);
        iob->bind(BIND_SIGNATURE_INT16, &h.year);
        iob->bind(BIND_SIGNATURE_INT8, &h.month);
        iob->bind_u8(h.invasion_id);
        iob->bind_u8(h.enemy_type);
        iob->bind_u8(h.mode);
        iob->bind_u8(h.attack_type);
        iob->bind____skip(1);
        iob->bind_u16(h.size);
        iob->bind(BIND_SIGNATURE_INT16, &h.tile_x);
        iob->bind(BIND_SIGNATURE_INT16, &h.tile_y);
        iob->bind_u8(h.want_destroy);
        iob->bind_u8(h.outcome);
        iob->bind____skip(2);
    }
}

void invasion_runtime_chunk::load_defaults(size_t version) {
    // saves older than v173 have no resolve binds or history
    // ring
    g_invasions.history_count = 0;
    g_invasions.history_next = 0;
    for (auto& b : g_invasions.binds) {
        b = {};
    }
}

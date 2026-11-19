#include "scenario/invasion_auto_resolve_chunks.h"

#include "scenario/invasion_auto_resolve.h"
#include "io/io_buffer.h"

void invasion_auto_resolve_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& ar = g_invasion_auto_resolve;
    iob->bind_u8(ar.count);
    uint8_t head_unused = 0;
    iob->bind_u8(head_unused); // was ar.head; keep layout
    for (int i = 0; i < INVASION_AUTO_RESOLVE_MAX_PENDING; ++i) {
        iob->bind_u8(ar.order[i]);
    }
    for (auto& p : ar.queue) {
        iob->bind_bool(p.in_use);
        iob->bind_u16(p.seq);
        iob->bind_u8(p.invasion_id);
        iob->bind_i16(p.days_left);
        iob->bind_bool(p.grace_armed); // was flag_snapshot; same layout
        iob->bind____skip(1);
    }
    iob->bind____skip(6);
}

void invasion_auto_resolve_chunk::load_defaults(size_t version) {
    // saves older than v177 have no pending auto-resolve queue
    g_invasion_auto_resolve = {};
}

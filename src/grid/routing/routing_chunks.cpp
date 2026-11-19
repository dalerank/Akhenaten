#include "grid/routing/routing_chunks.h"

#include "grid/routing/routing.h"
#include "core/xvalue.h"
#include "io/io_buffer.h"

void junk8_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& stats = xvalue<routing_stats_t>::ref();
    iob->bind____skip(4);
    iob->bind____skip(4); // resets to zero at the start of a new scenario
    iob->bind____skip(4); // unused counter
    iob->bind_u32(stats.total_routes_calculated);
    iob->bind_u32(stats.enemy_routes_calculated);
    iob->bind_u32(stats.noncitizen_routes_calculated);
    iob->bind_u32(stats.amphibia_routes_calculated);
    iob->bind____skip(4); // ??? coords?
    iob->bind____skip(8); // ??? coords?
    iob->bind____skip(2); // ??? something empire map related?
    iob->bind____skip(8); // ??? something storage related?
}

void junk8_chunk::reset() {
    map_routing_stats_clear();
}

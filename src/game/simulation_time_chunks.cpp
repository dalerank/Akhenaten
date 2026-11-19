#include "game/simulation_time_chunks.h"

#include "io/io_buffer.h"
#include "game/simulation.h"

void game_time_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_simulation.simtime;
    // OG stores all of these as int32; BC years are negative and need the
    // sign-extension bytes.
    iob->bind(BIND_SIGNATURE_INT32, &data.tick);
    iob->bind(BIND_SIGNATURE_INT32, &data.day);
    iob->bind(BIND_SIGNATURE_INT32, &data.month);
    iob->bind(BIND_SIGNATURE_INT32, &data.year);
    iob->bind(BIND_SIGNATURE_INT32, &data.total_days);
}

void game_time_chunk::reset() {
    g_simulation.simtime.init(2098);
}

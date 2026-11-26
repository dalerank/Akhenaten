#include "city/city_chunks.h"

#include "io/io_buffer.h"
#include "scenario/scenario.h"

void city_graph_order_chunk::bind_data(io_buffer* iob) {
    iob->bind____skip(8);
}

// The first 64 bytes held the 16 cloud positions; they live in the "clouds" chunk now (v200) and
// these bytes are written as zero.
void building_list_small_chunk::bind_data(io_buffer* iob) {
    iob->bind____skip(64);
    iob->bind____skip(36);
    iob->bind____skip(900);
}

void building_list_large_chunk::bind_data(io_buffer* iob) {
    iob->bind____skip(6000);
    g_scenario.bind_data(iob, 2000);
}

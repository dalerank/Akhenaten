#include "building/building_chunks.h"

#include "io/io_buffer.h"
#include "city/city.h"

void building_extra_highest_id_chunk::bind_data(io_buffer* iob, size_t version) {
    // iob->bind(BIND_SIGNATURE_INT32, &building_extra_data.highest_id_in_use);
    iob->bind____skip(4);
}

void building_extra_highest_id_ever_chunk::bind_data(io_buffer* iob, size_t version) {
    // iob->bind(BIND_SIGNATURE_INT32,
    // &building_extra_data.highest_id_ever);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_INT32, &g_city.plagues.locusts_countdown);
}

#include "city/city_health_chunks.h"

#include "city/city_health.h"
#include "io/io_buffer.h"

void city_health_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& health = city_health();
    iob->bind(BIND_SIGNATURE_INT32, &health.target_value);
    iob->bind(BIND_SIGNATURE_INT32, &health.value);
    iob->bind(BIND_SIGNATURE_INT32, &health.num_mortuary_workers);
    verify_no_crash(iob->get_offset() == city_health_chunk::size);
}

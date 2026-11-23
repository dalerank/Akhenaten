#include "city/city_health_chunks.h"

#include "city/city.h"
#include "io/io_buffer.h"

void city_health_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_city;
    iob->bind(BIND_SIGNATURE_INT32, &data.health.target_value);
    iob->bind(BIND_SIGNATURE_INT32, &data.health.value);
    iob->bind(BIND_SIGNATURE_INT32, &data.health.num_mortuary_workers);
    verify_no_crash(iob->get_offset() == city_health_chunk::size);
}

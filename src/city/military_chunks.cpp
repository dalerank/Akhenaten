#include "city/military_chunks.h"

#include "city/city.h"
#include "io/io_buffer.h"

void city_military_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_city;
    iob->bind(BIND_SIGNATURE_INT32, &data.military.native_attack_duration);
    iob->bind(BIND_SIGNATURE_UINT8, &data.military.infantry_batalions);
    iob->bind(BIND_SIGNATURE_UINT8, &data.military.total_batalions);
    iob->bind(BIND_SIGNATURE_UINT8, &data.military.kingdome_service_batalions);
    iob->bind(BIND_SIGNATURE_UINT8, &data.military.total_soldiers);
    verify_no_crash(iob->get_offset() == city_military_chunk::size);
}

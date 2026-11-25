#include "city/military_chunks.h"

#include "city/military.h"
#include "io/io_buffer.h"

void city_military_chunk::bind_data(io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT32, &city_military().native_attack_duration);
    iob->bind(BIND_SIGNATURE_UINT8, &city_military().infantry_batalions);
    iob->bind(BIND_SIGNATURE_UINT8, &city_military().total_batalions);
    iob->bind(BIND_SIGNATURE_UINT8, &city_military().kingdome_service_batalions);
    iob->bind(BIND_SIGNATURE_UINT8, &city_military().total_soldiers);
    verify_no_crash(iob->get_offset() == city_military_chunk::size);
}

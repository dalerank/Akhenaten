#include "city/city_festival_chunks.h"

#include "city/city_festival.h"
#include "io/io_buffer.h"

void city_festival_chunk::bind_data(io_buffer* iob) {
    auto& festival = city_festival();
    iob->bind(BIND_SIGNATURE_INT8, &festival.months_since_festival);
    iob->bind(BIND_SIGNATURE_UINT8, &festival.planned_size);
    iob->bind(BIND_SIGNATURE_INT8, &festival.months_till_next);
    iob->bind(BIND_SIGNATURE_UINT8, &festival.planned_god);
    iob->bind(BIND_SIGNATURE_UINT8, &festival.first_festival_effect_months);
    iob->bind(BIND_SIGNATURE_UINT8, &festival.second_festival_effect_months);
    verify_no_crash(iob->get_offset() == city_festival_chunk::size);
}

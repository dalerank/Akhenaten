#include "city/city_festival_chunks.h"

#include "city/city.h"
#include "io/io_buffer.h"

void city_festival_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_city;
    iob->bind(BIND_SIGNATURE_INT8, &data.festival.months_since_festival);
    iob->bind(BIND_SIGNATURE_UINT8, &data.festival.planned_size);
    iob->bind(BIND_SIGNATURE_INT8, &data.festival.months_till_next);
    iob->bind(BIND_SIGNATURE_UINT8, &data.festival.planned_god);
    iob->bind(BIND_SIGNATURE_UINT8, &data.festival.first_festival_effect_months);
    iob->bind(BIND_SIGNATURE_UINT8, &data.festival.second_festival_effect_months);
    verify_no_crash(iob->get_offset() == city_festival_chunk::size);
}

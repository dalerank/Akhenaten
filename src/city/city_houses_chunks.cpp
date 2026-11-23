#include "city/city_houses_chunks.h"

#include "city/city.h"
#include "io/io_buffer.h"

void city_houses_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_city;
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.fountain);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.well);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.more_entertainment);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.more_education);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.education);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.requiring.school);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.requiring.library);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.dentist);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.courthouse);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.food);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.health);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.more_health);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.requiring.dentist);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.requiring.courthouse);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.requiring.health);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.religion);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.second_religion);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.third_religion);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.requiring.religion);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.entertainment);
    iob->bind(BIND_SIGNATURE_UINT8, &data.houses.health);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.religion);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.education);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.entertainment);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.second_luxury);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.requiring.more_courthouse);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.any_courthouse);
    verify_no_crash(iob->get_offset() == city_houses_chunk::size);
}

#include "city/city_houses_chunks.h"

#include "city/city_houses.h"
#include "io/io_buffer.h"

void city_houses_chunk::bind_data(io_buffer* iob) {
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().missing.fountain);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().missing.well);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().missing.more_entertainment);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().missing.more_education);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().missing.education);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().requiring.school);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().requiring.library);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().missing.dentist);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().missing.courthouse);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().missing.food);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().missing.health);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().missing.more_health);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().requiring.dentist);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().requiring.courthouse);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().requiring.health);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().missing.religion);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().missing.second_religion);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().missing.third_religion);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().requiring.religion);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().missing.entertainment);
    iob->bind(BIND_SIGNATURE_UINT8, &city_houses().health);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().religion);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().education);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().entertainment);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().missing.second_luxury);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().requiring.more_courthouse);
    iob->bind(BIND_SIGNATURE_INT32, &city_houses().missing.any_courthouse);
    verify_no_crash(iob->get_offset() == city_houses_chunk::size);
}

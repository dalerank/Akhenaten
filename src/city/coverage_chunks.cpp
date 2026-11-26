#include "city/coverage_chunks.h"

#include "city/coverage.h"
#include "io/io_buffer.h"

void city_avg_coverage_chunk::bind_data(io_buffer* iob) {
    iob->bind(BIND_SIGNATURE_INT32, &city_avg_coverage().average_entertainment);
    iob->bind(BIND_SIGNATURE_INT32, &city_avg_coverage().average_religion);
    iob->bind(BIND_SIGNATURE_INT32, &city_avg_coverage().average_education);
    iob->bind(BIND_SIGNATURE_INT32, &city_avg_coverage().average_health);
    verify_no_crash(iob->get_offset() == city_avg_coverage_chunk::size);
}

#include "city/ratings_chunks.h"

#include "city/ratings.h"
#include "io/io_buffer.h"

void city_ratings_chunk::bind_data(io_buffer* iob) {
    auto& ratings = city_ratings();
    iob->bind(BIND_SIGNATURE_INT32, &ratings.monument_riot_cause);
    iob->bind(BIND_SIGNATURE_UINT16, &ratings.monument_years_of_monument);
    iob->bind(BIND_SIGNATURE_INT32, &ratings.culture);
    iob->bind(BIND_SIGNATURE_INT32, &ratings.prosperity);
    iob->bind(BIND_SIGNATURE_INT32, &ratings.monument);
    iob->bind(BIND_SIGNATURE_INT32, &ratings.prosperity_trend);
    iob->bind(BIND_SIGNATURE_INT32, &ratings.monument_num_criminals);
    iob->bind(BIND_SIGNATURE_INT32, &ratings.monument_num_rioters);
    iob->bind(BIND_SIGNATURE_INT32, &ratings.culture_explanation);
    iob->bind(BIND_SIGNATURE_INT32, &ratings.prosperity_explanation);
    iob->bind(BIND_SIGNATURE_UINT8, &ratings.monument_destroyed_buildings);
    iob->bind(BIND_SIGNATURE_UINT8, &ratings.prosperity_max);
    verify_no_crash(iob->get_offset() == city_ratings_chunk::size);
}

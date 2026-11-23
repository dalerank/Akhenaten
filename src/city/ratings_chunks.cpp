#include "city/ratings_chunks.h"

#include "city/city.h"
#include "io/io_buffer.h"

void city_ratings_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_city;
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.monument_riot_cause);
    iob->bind(BIND_SIGNATURE_UINT16, &data.ratings.monument_years_of_monument);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.culture);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.prosperity);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.monument);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.prosperity_trend);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.monument_num_criminals);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.monument_num_rioters);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.culture_explanation);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.prosperity_explanation);
    iob->bind(BIND_SIGNATURE_UINT8, &data.ratings.monument_destroyed_buildings);
    iob->bind(BIND_SIGNATURE_UINT8, &data.ratings.prosperity_max);
    verify_no_crash(iob->get_offset() == city_ratings_chunk::size);
}

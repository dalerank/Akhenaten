#include "city/entertainment_chunks.h"

#include "city/city.h"
#include "io/io_buffer.h"

void city_entertainment_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_city;
    iob->bind(BIND_SIGNATURE_INT32, &data.entertainment.booth_shows);
    iob->bind(BIND_SIGNATURE_INT32, &data.entertainment.booth_no_shows_weighted);
    iob->bind(BIND_SIGNATURE_INT32, &data.entertainment.bandstand_shows);
    iob->bind(BIND_SIGNATURE_INT32, &data.entertainment.bandstand_no_shows_weighted);
    iob->bind(BIND_SIGNATURE_INT32, &data.entertainment.pavilion_shows);
    iob->bind(BIND_SIGNATURE_INT32, &data.entertainment.pavilion_no_shows_weighted);
    iob->bind(BIND_SIGNATURE_INT32, &data.entertainment.senet_house_plays);
    iob->bind(BIND_SIGNATURE_INT32, &data.entertainment.senet_house_no_shows_weighted);
    iob->bind(BIND_SIGNATURE_INT32, &data.entertainment.venue_needing_shows);
    iob->bind(BIND_SIGNATURE_UINT8, &data.entertainment.senet_house_has_plays);
    iob->bind(BIND_SIGNATURE_UINT8, &data.entertainment.senet_house_message_shown);
    iob->bind(BIND_SIGNATURE_UINT8, &data.entertainment.pavilion_message_shown);
    verify_no_crash(iob->get_offset() == city_entertainment_chunk::size);
}

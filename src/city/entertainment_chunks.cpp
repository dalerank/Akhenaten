#include "city/entertainment_chunks.h"

#include "city/entertainment.h"
#include "io/io_buffer.h"

void city_entertainment_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& entertainment = city_entertainment();
    iob->bind(BIND_SIGNATURE_INT32, &entertainment.booth_shows);
    iob->bind(BIND_SIGNATURE_INT32, &entertainment.booth_no_shows_weighted);
    iob->bind(BIND_SIGNATURE_INT32, &entertainment.bandstand_shows);
    iob->bind(BIND_SIGNATURE_INT32, &entertainment.bandstand_no_shows_weighted);
    iob->bind(BIND_SIGNATURE_INT32, &entertainment.pavilion_shows);
    iob->bind(BIND_SIGNATURE_INT32, &entertainment.pavilion_no_shows_weighted);
    iob->bind(BIND_SIGNATURE_INT32, &entertainment.senet_house_plays);
    iob->bind(BIND_SIGNATURE_INT32, &entertainment.senet_house_no_shows_weighted);
    iob->bind(BIND_SIGNATURE_INT32, &entertainment.venue_needing_shows);
    iob->bind(BIND_SIGNATURE_UINT8, &entertainment.senet_house_has_plays);
    iob->bind(BIND_SIGNATURE_UINT8, &entertainment.senet_house_message_shown);
    iob->bind(BIND_SIGNATURE_UINT8, &entertainment.pavilion_message_shown);
    verify_no_crash(iob->get_offset() == city_entertainment_chunk::size);
}

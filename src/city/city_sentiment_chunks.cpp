#include "city/city_sentiment_chunks.h"

#include "city/city.h"
#include "io/io_buffer.h"

void city_sentiment_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_city;
    iob->bind(BIND_SIGNATURE_INT32, &data.sentiment.value);
    iob->bind(BIND_SIGNATURE_INT32, &data.sentiment.message_delay);
    iob->bind(BIND_SIGNATURE_INT32, &data.sentiment.protesters);
    iob->bind(BIND_SIGNATURE_INT32, &data.sentiment.criminals);
    iob->bind(BIND_SIGNATURE_UINT8, &data.sentiment.unemployment_pct);
    iob->bind(BIND_SIGNATURE_INT32, &data.sentiment.previous_value);
    iob->bind(BIND_SIGNATURE_INT32, &data.sentiment.low_mood_cause);
    iob->bind(BIND_SIGNATURE_INT8, &data.sentiment.wages);
    iob->bind(BIND_SIGNATURE_INT8, &data.sentiment.include_huts);
    verify_no_crash(iob->get_offset() == city_sentiment_chunk::size);
}

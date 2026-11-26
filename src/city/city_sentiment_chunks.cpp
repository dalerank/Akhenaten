#include "city/city_sentiment_chunks.h"

#include "city/city_sentiment.h"
#include "io/io_buffer.h"

void city_sentiment_chunk::bind_data(io_buffer* iob) {
    auto& sentiment = city_sentiment();
    iob->bind(BIND_SIGNATURE_INT32, &sentiment.value);
    iob->bind(BIND_SIGNATURE_INT32, &sentiment.message_delay);
    iob->bind(BIND_SIGNATURE_INT32, &sentiment.protesters);
    iob->bind(BIND_SIGNATURE_INT32, &sentiment.criminals);
    iob->bind(BIND_SIGNATURE_UINT8, &sentiment.unemployment_pct);
    iob->bind(BIND_SIGNATURE_INT32, &sentiment.previous_value);
    iob->bind(BIND_SIGNATURE_INT32, &sentiment.low_mood_cause);
    iob->bind(BIND_SIGNATURE_INT8, &sentiment.wages);
    iob->bind(BIND_SIGNATURE_INT8, &sentiment.include_huts);
    verify_no_crash(iob->get_offset() == city_sentiment_chunk::size);
}

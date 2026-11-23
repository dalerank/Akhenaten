#pragma once

#include <cstddef>

class io_buffer;

struct city_sentiment_chunk {
    static constexpr const char* name = "city_sentiment";
    static constexpr int size = 27;
    static void bind_data(io_buffer* iob, size_t version);
};

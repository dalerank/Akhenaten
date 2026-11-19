#pragma once

#include <cstddef>

class io_buffer;

struct trade_prices_chunk {
    static constexpr const char* name = "trade_prices";
    static void bind_data(io_buffer* iob, size_t version);
};

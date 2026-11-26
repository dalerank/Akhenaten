#pragma once

#include <cstddef>

class io_buffer;

struct city_trade_chunk {
    static constexpr const char* name = "city_trade";
    static constexpr int size = 16;
    static void bind_data(io_buffer* iob);
};

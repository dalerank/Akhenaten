#pragma once

#include <cstddef>

class io_buffer;

struct city_finance_chunk {
    static constexpr const char* name = "city_finance";
    static constexpr int size = 137;
    static void bind_data(io_buffer* iob, size_t version);
};

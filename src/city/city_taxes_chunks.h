#pragma once

#include <cstddef>

class io_buffer;

struct city_taxes_chunk {
    static constexpr const char* name = "city_taxes";
    static constexpr int size = 59;
    static void bind_data(io_buffer* iob);
};

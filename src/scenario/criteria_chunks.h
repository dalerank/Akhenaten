#pragma once

#include <cstddef>

class io_buffer;

struct max_year_chunk {
    static constexpr const char* name = "max_year";
    static void bind_data(io_buffer* iob, size_t version);
};

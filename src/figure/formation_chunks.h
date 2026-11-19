#pragma once

#include <cstddef>

class io_buffer;

struct formations_chunk {
    static constexpr const char* name = "formations";
    static void bind_data(io_buffer* iob, size_t version);
    static void reset();
};

struct formations_info_chunk {
    static constexpr const char* name = "formations_info";
    static void bind_data(io_buffer* iob, size_t version);
};

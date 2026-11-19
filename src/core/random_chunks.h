#pragma once

#include <cstddef>

class io_buffer;

struct random_iv_chunk {
    static constexpr const char* name = "random_iv";
    static void bind_data(io_buffer* iob, size_t version);
};

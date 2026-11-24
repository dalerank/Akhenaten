#pragma once

#include <cstddef>

class io_buffer;

struct local_cults_chunk {
    static constexpr const char* name = "enhanced_religion";
    static void bind_data(io_buffer* iob, size_t version);
    static void load_defaults(size_t version);
};

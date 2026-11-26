#pragma once

#include <cstddef>

class io_buffer;

struct local_cults_chunk {
    static constexpr const char* name = "enhanced_religion";
    static void bind_data(io_buffer* iob);
    static void load_defaults();
};

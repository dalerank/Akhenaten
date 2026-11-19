#pragma once

#include <cstddef>

class io_buffer;

struct tutorial_flags_struct_chunk {
    static constexpr const char* name = "tutorial_flags_struct";
    static void bind_data(io_buffer* iob, size_t version);
};

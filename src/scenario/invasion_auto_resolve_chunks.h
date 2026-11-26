#pragma once

#include <cstddef>

class io_buffer;

struct invasion_auto_resolve_chunk {
    static constexpr const char* name = "invasion_auto_resolve";
    static void bind_data(io_buffer* iob);
    static void load_defaults();
};

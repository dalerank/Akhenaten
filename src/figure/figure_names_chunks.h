#pragma once

#include <cstddef>

class io_buffer;

struct figure_names_chunk {
    static constexpr const char* name = "figure_names";
    static void bind_data(io_buffer* iob, size_t version);
};

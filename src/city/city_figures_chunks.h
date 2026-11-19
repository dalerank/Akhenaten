#pragma once

#include <cstddef>

class io_buffer;

struct figures_chunk {
    static constexpr const char* name = "figures";
    static void bind_data(io_buffer* iob, size_t version);
    static void reset();
};

struct figure_sequence_chunk {
    static constexpr const char* name = "figure_sequence";
    static void bind_data(io_buffer* iob, size_t version);
};

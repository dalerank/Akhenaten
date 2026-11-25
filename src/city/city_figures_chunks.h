#pragma once

#include <cstddef>

class io_buffer;

struct figures_chunk {
    static constexpr const char* name = "figures";
    static void bind_data(io_buffer* iob, size_t version);
};

struct figure_sequence_chunk {
    static constexpr const char* name = "figure_sequence";
    static void bind_data(io_buffer* iob, size_t version);
};

struct city_figures_chunk {
    static constexpr const char* name = "city_figures";
    static constexpr int size = 22;
    static void bind_data(io_buffer* iob, size_t version);
};

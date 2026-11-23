#pragma once

#include <cstddef>

class io_buffer;

struct city_kingdome_chunk {
    static constexpr const char* name = "city_kingdome";
    static constexpr int size = 117;
    static void bind_data(io_buffer* iob, size_t version);
};

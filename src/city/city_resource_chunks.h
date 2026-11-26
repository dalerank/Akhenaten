#pragma once

#include <cstddef>

class io_buffer;

struct city_resource_chunk {
    static constexpr const char* name = "city_resource";
    static constexpr int size = 586;
    static void bind_data(io_buffer* iob);
};

#pragma once

#include <cstddef>

class io_buffer;

struct city_migration_chunk {
    static constexpr const char* name = "city_migration";
    static constexpr int size = 23;
    static void bind_data(io_buffer* iob, size_t version);
};

#pragma once

#include <cstddef>

class io_buffer;

struct city_labor_chunk {
    static constexpr const char* name = "city_labor";
    static constexpr int size = 224;
    static void bind_data(io_buffer* iob, size_t version);
};

struct labor_storage_priority_chunk {
    static constexpr const char* name = "labor_storage_priority";
    static void bind_data(io_buffer* iob, size_t version);
    static void load_defaults(size_t version);
};

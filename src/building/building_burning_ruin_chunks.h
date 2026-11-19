#pragma once

#include <cstddef>

class io_buffer;

struct building_list_burning_chunk {
    static constexpr const char* name = "building_list_burning";
    static void bind_data(io_buffer* iob, size_t version);
};

struct building_burning_list_info_chunk {
    static constexpr const char* name = "building_burning_list_info";
    static void bind_data(io_buffer* iob, size_t version);
};

#pragma once

#include <cstddef>

class io_buffer;

struct city_data_chunk {
    static constexpr const char* name = "city_data";
    static void bind_data(io_buffer* iob, size_t version);
};

struct city_data_extra_chunk {
    static constexpr const char* name = "city_data_extra";
    static void bind_data(io_buffer* iob, size_t version);
};

struct city_graph_order_chunk {
    static constexpr const char* name = "city_graph_order";
    static void bind_data(io_buffer* iob, size_t version);
};

struct building_list_small_chunk {
    static constexpr const char* name = "building_list_small";
    static void bind_data(io_buffer* iob, size_t version);
};

struct building_list_large_chunk {
    static constexpr const char* name = "building_list_large";
    static void bind_data(io_buffer* iob, size_t version);
};

struct city_mission_chunk {
    static constexpr const char* name = "city_mission";
    static constexpr int size = 2;
    static void bind_data(io_buffer* iob, size_t version);
};

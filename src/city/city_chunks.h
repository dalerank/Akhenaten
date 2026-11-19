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

struct labor_storage_priority_chunk {
    static constexpr const char* name = "labor_storage_priority";
    static void bind_data(io_buffer* iob, size_t version);
    static void load_defaults(size_t version);
};

struct enhanced_religion_chunk {
    static constexpr const char* name = "enhanced_religion";
    static void bind_data(io_buffer* iob, size_t version);
    static void load_defaults(size_t version);
};

struct city_graph_order_chunk {
    static constexpr const char* name = "city_graph_order";
    static void bind_data(io_buffer* iob, size_t version);
};

struct bookmarks_chunk {
    static constexpr const char* name = "bookmarks";
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

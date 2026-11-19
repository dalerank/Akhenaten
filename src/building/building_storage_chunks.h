#pragma once

#include <cstddef>

class io_buffer;

struct building_storages_chunk {
    static constexpr const char* name = "building_storages";
    static void bind_data(io_buffer* iob, size_t version);
    static void reset();
};

struct storages_empty_all_backup_chunk {
    static constexpr const char* name = "storages_empty_all_backup";
    static void bind_data(io_buffer* iob, size_t version);
    static void load_defaults(size_t version);
};

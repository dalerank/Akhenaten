#pragma once

class io_buffer;

struct aqueduct_grid_chunk {
    static constexpr const char* name = "aqueduct_grid";
    static void bind_data(io_buffer* iob, size_t version);
};

struct aqueduct_backup_grid_chunk {
    static constexpr const char* name = "aqueduct_backup_grid";
    static void bind_data(io_buffer* iob, size_t version);
};

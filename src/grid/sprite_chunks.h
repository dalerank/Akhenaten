#pragma once

class io_buffer;

struct sprite_grid_chunk {
    static constexpr const char* name = "sprite_grid";
    static void bind_data(io_buffer* iob, size_t version);
};

struct sprite_backup_grid_chunk {
    static constexpr const char* name = "sprite_backup_grid";
    static void bind_data(io_buffer* iob, size_t version);
};

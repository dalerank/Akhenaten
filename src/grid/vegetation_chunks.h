#pragma once

class io_buffer;

struct vegetation_growth_chunk {
    static constexpr const char* name = "vegetation_growth";
    static void bind_data(io_buffer* iob, size_t version);
};

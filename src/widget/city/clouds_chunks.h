#pragma once

class io_buffer;

struct clouds_chunk {
    static constexpr const char* name = "clouds";
    static void bind_data(io_buffer* iob, size_t version);
    static void load_defaults(size_t version);
};

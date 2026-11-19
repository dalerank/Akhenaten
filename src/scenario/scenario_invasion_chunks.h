#pragma once

#include <cstddef>

class io_buffer;

struct invasion_warnings_chunk {
    static constexpr const char* name = "invasion_warnings";
    static void bind_data(io_buffer* iob, size_t version);
};

struct invasion_event_pending_chunk {
    static constexpr const char* name = "invasion_event_pending";
    static void bind_data(io_buffer* iob, size_t version);
    static void load_defaults(size_t version);
};

struct invasion_runtime_chunk {
    static constexpr const char* name = "invasion_runtime";
    static void bind_data(io_buffer* iob, size_t version);
    static void load_defaults(size_t version);
};

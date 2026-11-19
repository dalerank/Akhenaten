#pragma once

#include <cstddef>

class io_buffer;

struct scenario_events_chunk {
    static constexpr const char* name = "scenario_events";
    static void bind_data(io_buffer* iob, size_t version);
};

struct scenario_events_extra_chunk {
    static constexpr const char* name = "scenario_events_extra";
    static void bind_data(io_buffer* iob, size_t version);
};

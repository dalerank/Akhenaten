#pragma once

#include <cstddef>

class io_buffer;

struct floodplain_settings_chunk {
    static constexpr const char* name = "floodplain_settings";
    static void bind_data(io_buffer* iob, size_t version);
};

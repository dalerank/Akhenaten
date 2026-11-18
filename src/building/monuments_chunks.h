#pragma once

class io_buffer;

struct monuments_progress_chunk {
    static constexpr const char* name = "monuments_progress";
    static void bind_data(io_buffer* iob, size_t version);
};

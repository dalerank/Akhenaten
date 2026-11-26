#pragma once

#include <cstddef>

class io_buffer;

struct bookmarks_chunk {
    static constexpr const char* name = "bookmarks";
    static void bind_data(io_buffer* iob);
};

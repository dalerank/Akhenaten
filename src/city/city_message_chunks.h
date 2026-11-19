#pragma once

#include <cstddef>

class io_buffer;

struct messages_chunk {
    static constexpr const char* name = "messages";
    static void bind_data(io_buffer* iob, size_t version);
    static void reset();
};

struct message_extra_chunk {
    static constexpr const char* name = "message_extra";
    static void bind_data(io_buffer* iob, size_t version);
};

#pragma once

#include <cstddef>

class io_buffer;

struct messages_chunk {
    static constexpr const char* name = "messages";
    static void bind_data(io_buffer* iob);
};

struct message_extra_chunk {
    static constexpr const char* name = "message_extra";
    static void bind_data(io_buffer* iob);
};

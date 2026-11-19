#pragma once

#include <cstddef>

class io_buffer;

struct campaign_carry_troops_chunk {
    static constexpr const char* name = "campaign_carry_troops";
    static void bind_data(io_buffer* iob, size_t version);
    static void load_defaults(size_t version);
    static void reset();
};

struct campaign_carry_monuments_chunk {
    static constexpr const char* name = "campaign_carry_monuments";
    static void bind_data(io_buffer* iob, size_t version);
    static void load_defaults(size_t version);
    static void reset();
};

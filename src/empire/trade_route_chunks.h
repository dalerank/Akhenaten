#pragma once

#include <cstddef>

class io_buffer;

struct trade_routes_limits_chunk {
    static constexpr const char* name = "trade_routes_limits";
    static void bind_data(io_buffer* iob, size_t version);
};

struct trade_routes_traded_chunk {
    static constexpr const char* name = "trade_routes_traded";
    static void bind_data(io_buffer* iob, size_t version);
};

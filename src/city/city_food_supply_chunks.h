#pragma once

#include <cstddef>

class io_buffer;

struct city_food_supply_chunk {
    static constexpr const char* name = "city_food_supply";
    static constexpr int size = 24;
    static void bind_data(io_buffer* iob);
};

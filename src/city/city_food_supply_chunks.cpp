#include "city/city_food_supply_chunks.h"

#include "city/city.h"
#include "io/io_buffer.h"

void city_food_supply_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_city;
    iob->bind(BIND_SIGNATURE_INT32, &data.food_supply.hunting_lodges_working);
    iob->bind(BIND_SIGNATURE_INT32, &data.food_supply.game_meat_last_month);
    iob->bind(BIND_SIGNATURE_INT32, &data.food_supply.game_meat_this_month);
    iob->bind(BIND_SIGNATURE_INT32, &data.food_supply.fishing_wharfs_working);
    iob->bind(BIND_SIGNATURE_INT32, &data.food_supply.fish_last_month);
    iob->bind(BIND_SIGNATURE_INT32, &data.food_supply.fish_this_month);
    verify_no_crash(iob->get_offset() == city_food_supply_chunk::size);
}

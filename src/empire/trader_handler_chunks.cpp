#include "empire/trader_handler_chunks.h"

#include "io/io_buffer.h"
#include "empire/empire_traders.h"

void empire_traders_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_empire_traders;
    verify_no_crash(data.traders.size() == 100);
    for (int i = 0; i < data.traders.size(); i++) {
        empire_trader& t = data.traders[i];
        t.id = i;
        iob->bind_u16(t.bought_amount);
        iob->bind_u8(t.trade_route_id);
        iob->bind_u8(t.current_route_point);
        iob->bind_u16(t.sold_amount);
        iob->bind_bool(t.is_active);
        iob->bind_bool(t.is_ship);

        // Stored on disk in loads (1 byte), kept in memory in amount units (x100).
        auto bind_loads = [iob](uint16_t& amount) {
            uint8_t loads = (uint8_t)(amount / 100);
            iob->bind_u8(loads);
            if (iob->is_read_access()) {
                amount = loads * 100;
            }
        };

        iob->bind_u8(t.movement_delay_max);
        for (int r = 1; r < RESOURCES_MAX; r++)
            bind_loads(t.bought_resources[r]);

        iob->bind____skip(1);
        for (int r = 1; r < RESOURCES_MAX; r++)
            bind_loads(t.sold_resources[r]);

        iob->bind_u16(t.bought_value);
        iob->bind_u8(t.destination_city_id);
        iob->bind_u8((uint8_t&)t.state);
        iob->bind_u16(t.sold_value);
        iob->bind_u8(t.movement_delay);
        iob->bind____skip(1);
    }

    iob->bind____skip(4);
}

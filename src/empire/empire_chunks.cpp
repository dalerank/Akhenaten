#include "empire/empire_chunks.h"

#include "empire/empire.h"
#include "io/io_buffer.h"
#include "io/chunk_serializer.h"

void empire_cities_chunk::bind_data(io_buffer* iob, size_t version) {
    // v178+: Cleopatra name ids 61+ need array slots. Older files keep classic 61.
    const int city_count = (g_chunk_io.get_file_version() > 177) ? empire_t::MAX_CITIES : empire_t::MAX_CITIES_CLASSIC;
    for (int i = 0; i < city_count; i++) {
        empire_city& city = g_empire.get_cities()[i];
        city.lookup_id = i;
        iob->bind_u8(city.in_use);
        uint8_t reserved = 0;
        iob->bind_u8(reserved);
        iob->bind_u8((uint8_t&)city.type);

        iob->bind(BIND_SIGNATURE_UINT8, &city.name_id);
        iob->bind(BIND_SIGNATURE_UINT8, &city.route_id);
        iob->bind(BIND_SIGNATURE_UINT8, &city.is_open);

        for (int r = 0; r < RESOURCES_MAX; r++) {
            iob->bind_bool(city.buys_resource[r]);
        }

        for (int r = 0; r < RESOURCES_MAX; r++) {
            iob->bind_bool(city.sells_resource[r]);
        }

        iob->bind_i16(city.cost_to_open);
        iob->bind(BIND_SIGNATURE_INT16, &city.ph_unk01);
        iob->bind(BIND_SIGNATURE_INT16, &city.trader_entry_delay);
        iob->bind(BIND_SIGNATURE_INT16, &city.trader_blocked);
        iob->bind(BIND_SIGNATURE_INT16, &city.empire_object_id);
        iob->bind(BIND_SIGNATURE_UINT8, &city.is_sea_trade);
        iob->bind_u8(city.months_under_siege);

        for (int f = 0; f < 3; f++) {
            iob->bind(BIND_SIGNATURE_INT16, &city.trader_figure_ids[f]);
        }

        iob->bind_u8(city.trader_entry_delay_override);
        iob->bind_u8(city.ship_movement_delay_min);
        iob->bind_u8(city.ship_movement_delay_max);
        iob->bind____skip(7);
    }
}

void empire_cities_chunk::reset() {
    g_empire.clear_cities_data();
}

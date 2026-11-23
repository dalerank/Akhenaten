#include "city/map_chunks.h"

#include "city/city.h"
#include "io/io_buffer.h"

void city_map_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_city;
    iob->bind(BIND_SIGNATURE_INT32, data.map.entry_point);
    iob->bind(BIND_SIGNATURE_INT32, data.map.exit_point);
    for (int i = 0; i < 10; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &data.map.largest_road_networks[i].id);
        iob->bind(BIND_SIGNATURE_INT32, &data.map.largest_road_networks[i].size);
    }
    verify_no_crash(iob->get_offset() == city_map_chunk::size);
}

#include "city/map_chunks.h"

#include "city/map.h"
#include "io/io_buffer.h"

void city_map_chunk::bind_data(io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT32, city_map().entry_point);
    iob->bind(BIND_SIGNATURE_INT32, city_map().exit_point);
    for (int i = 0; i < 10; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &city_map().largest_road_networks[i].id);
        iob->bind(BIND_SIGNATURE_INT32, &city_map().largest_road_networks[i].size);
    }
    verify_no_crash(iob->get_offset() == city_map_chunk::size);
}

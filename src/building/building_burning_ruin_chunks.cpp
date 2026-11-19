#include "building/building_burning_ruin_chunks.h"

#include "building/building_burning_ruin.h"
#include "core/xvalue.h"
#include "io/io_buffer.h"

void building_list_burning_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& ruins = xvalue<burning_ruins_t>::ref().ids;
    for (int i = 0; i < ruins.capacity(); i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &ruins[i]);
    }
}

void building_burning_list_info_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& ruins = xvalue<burning_ruins_t>::ref().ids;
    uint32_t total = ruins.capacity();
    uint32_t size = ruins.size();
    iob->bind(BIND_SIGNATURE_UINT32, &total);
    iob->bind(BIND_SIGNATURE_UINT32, &size);

    ruins.resize(size);
}

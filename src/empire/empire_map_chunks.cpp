#include "empire/empire_map_chunks.h"

#include "empire/empire_map.h"
#include "io/io_buffer.h"

void empire_map_params_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_empire_map;
    iob->bind(BIND_SIGNATURE_INT32, &data.scroll_x);
    iob->bind(BIND_SIGNATURE_INT32, &data.scroll_y);
    iob->bind(BIND_SIGNATURE_INT32, &data.selected_obj);
}

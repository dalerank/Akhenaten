#include "figure/route_chunks.h"

#include "figure/route.h"
#include "core/xvalue.h"
#include "io/io_buffer.h"

void route_figures_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = xvalue<figure_route_data_t>::ref();
    for (int i = 0; i < figure_route_data_t::MAX_ROUTES; i++) {
        iob->bind(BIND_SIGNATURE_INT16, &data.figure_ids[i]);
    }
}

void route_figures_chunk::reset() {
    figure_route_clear_all();
}

void route_paths_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = xvalue<figure_route_data_t>::ref();
    for (int i = 0; i < figure_route_data_t::MAX_ROUTES; i++) {
        iob->bind(BIND_SIGNATURE_RAW, &data.direction_paths[i], MAX_PATH_LENGTH);
    }
}

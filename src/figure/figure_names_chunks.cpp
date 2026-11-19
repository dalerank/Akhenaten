#include "figure/figure_names_chunks.h"

#include "figure/figure_names.h"
#include "core/xvalue.h"
#include "io/io_buffer.h"

enum {
    FIGURE_NAME_SAVED_SLOT_FIRST = 40,
    FIGURE_NAME_SAVED_SLOT_LAST = 20,
};

void figure_names_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& counters = xvalue<figure_name_counters_t>::ref().counters;
    for (int slot = FIGURE_NAME_SAVED_SLOT_FIRST; slot >= FIGURE_NAME_SAVED_SLOT_LAST; slot--) {
        iob->bind(BIND_SIGNATURE_INT32, &counters[slot]);
    }
}

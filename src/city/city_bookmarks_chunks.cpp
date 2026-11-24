#include "city/city_bookmarks_chunks.h"

#include "city/city_bookmarks.h"
#include "io/io_buffer.h"

void bookmarks_chunk::bind_data(io_buffer* iob, size_t version) {
    static_assert(map_bookmarks_t::MAX_BOOKMARKS == 4);
    // OG layout: {int32 grid_offset, int32 unused} per bookmark; OG keeps the second at -1.
    for (int i = 0; i < map_bookmarks_t::MAX_BOOKMARKS; i++) {
        tile2i& point = city_bookmarks().points[i];
        int32_t offset = point.valid() ? point.grid_offset() : -1;
        int32_t unused = -1;
        iob->bind(BIND_SIGNATURE_INT32, &offset);
        iob->bind(BIND_SIGNATURE_INT32, &unused);
        if (iob->is_read_access()) {
            point = offset >= 0 ? tile2i(offset) : tile2i::invalid;
        }
    }
}

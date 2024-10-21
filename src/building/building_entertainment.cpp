#include "building_entertainment.h"

#include "io/io_buffer.h"

void building_entertainment::bind_dynamic(io_buffer *iob, size_t version) {
    iob->bind____skip(26);
    iob->bind____skip(58);
    iob->bind(BIND_SIGNATURE_UINT8, &data.entertainment.num_shows);
    iob->bind(BIND_SIGNATURE_UINT8, &data.entertainment.juggler_visited);
    iob->bind(BIND_SIGNATURE_UINT8, &data.entertainment.musician_visited);
    iob->bind(BIND_SIGNATURE_UINT8, &data.entertainment.dancer_visited);
    iob->bind(BIND_SIGNATURE_INT8, &data.entertainment.play_index);
    iob->bind____skip(19);
    iob->bind(BIND_SIGNATURE_UINT32, &data.entertainment.latched_venue_main_grid_offset);
    iob->bind(BIND_SIGNATURE_UINT32, &data.entertainment.latched_venue_add_grid_offset);
    iob->bind(BIND_SIGNATURE_UINT8, &data.entertainment.orientation);
    iob->bind(BIND_SIGNATURE_UINT8, &data.entertainment.ent_reserved_u8);
    iob->bind____skip(6);
    iob->bind(BIND_SIGNATURE_UINT8, &data.entertainment.consume_material_id);
    iob->bind(BIND_SIGNATURE_UINT8, &data.entertainment.spawned_entertainer_days);
    iob->bind(BIND_SIGNATURE_UINT32, &data.entertainment.booth_corner_grid_offset);
}

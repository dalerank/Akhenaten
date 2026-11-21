#include "io/gamestate/presentation_chunks.h"

#include "grid/orientation.h"
#include "graphics/view/view.h"
#include "io/io_buffer.h"

void city_view_orientation_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_camera;

    iob->bind(BIND_SIGNATURE_INT32, &data.orientation);

    if (data.orientation >= 0 && data.orientation <= 6)
        data.orientation = 2 * (data.orientation / 2); // ensure even number
    else
        data.orientation = 0;

    map_view_orientation_set(data.orientation);
}

void city_view_camera_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_camera;

    iob->bind(BIND_SIGNATURE_INT32, &data.tile_internal.x);
    iob->bind(BIND_SIGNATURE_INT32, &data.tile_internal.y);

    //    city_view_go_to_position(x, y);
    //    set_viewport_with_sidebar();
    data.go_to_corner_tile(data.tile_internal, false);
    data.update_derived_camera_state();
}

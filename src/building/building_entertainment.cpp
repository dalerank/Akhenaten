#include "building_entertainment.h"

#include "io/io_buffer.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "grid/image.h"
#include "grid/gardens.h"
#include "grid/building_tiles.h"
#include "graphics/view/view.h"

int building_entertainment::bandstand_main_img_offset(int orientation) {
    int offset = 0;
    if (orientation == 2) {
        switch (city_view_orientation() / 2) {
        case 0: offset = 1; break;
        case 1: offset = 2; break;
        case 2: offset = 0; break;
        case 3: offset = 3; break;
        }
    } else if (orientation == 3) {
        switch (city_view_orientation() / 2) {
        case 0: offset = 3; break;
        case 1: offset = 1; break;
        case 2: offset = 2; break;
        case 3: offset = 0; break;
        }
    } else if (orientation == 0) {
        switch (city_view_orientation() / 2) {
        case 0: offset = 1; break;
        case 1: offset = 2; break;
        case 2: offset = 0; break;
        case 3: offset = 3; break;
        }
    } else if (orientation == 1) {
        switch (city_view_orientation() / 2) {
        case 0: offset = 2; break;
        case 1: offset = 0; break;
        case 2: offset = 3; break;
        case 3: offset = 1; break;
        }
    }
    return offset;
}

int building_entertainment::bandstand_add_img_offset(int orientation) {
    int offset = 0;
    if (orientation == 2) {
        switch (city_view_orientation() / 2) {
        case 0: offset = 0; break;
        case 1: offset = 3; break;
        case 2: offset = 1; break;
        case 3: offset = 2; break;
        }
    } else if (orientation == 3) {
        switch (city_view_orientation() / 2) {
        case 0: offset = 2; break;
        case 1: offset = 0; break;
        case 2: offset = 3; break;
        case 3: offset = 1; break;
        }
    } else if (orientation == 0) {
        switch (city_view_orientation() / 2) {
        case 0: offset = 0; break;
        case 1: offset = 3; break;
        case 2: offset = 1; break;
        case 3: offset = 2; break;
        }
    } else if (orientation == 1) {
        switch (city_view_orientation() / 2) {
        case 0: offset = 3; break;
        case 1: offset = 1; break;
        case 2: offset = 2; break;
        case 3: offset = 0; break;
        }
    }
    return offset;
}

void building_entertainment::place_latch_on_venue(e_building_type type, int dx, int dy, int orientation, bool main_venue) {
    tile2i point = base.tile.shifted(dx, dy);
    // set map graphics accordingly

    auto &d = runtime_data();
    switch (type) {
    case BUILDING_GARDENS:
        map_terrain_add(point, TERRAIN_GARDEN);
        map_tiles_gardens_update_all();
        break;

    case BUILDING_BOOTH:
    {
        int booth = anim(animkeys().booth).first_img();
        map_image_set(point, booth);
    }
    break;

    case BUILDING_BANDSTAND:
        if (main_venue) {
            int stand_sn_s = anim("stand_sn_s").first_img();
            d.latched_venue_main_grid_offset = point.grid_offset();
            int offset = bandstand_main_img_offset(orientation);
            map_image_set(point, stand_sn_s + offset);
        } else {
            int stand_sn_s = anim("stand_sn_s").first_img();
            d.latched_venue_add_grid_offset = point.grid_offset();
            int offset = bandstand_add_img_offset(orientation);
            map_image_set(point, stand_sn_s + offset);
        }
        break;

    case BUILDING_PAVILLION: {
        map_building_tiles_add(id(), point, 2, base_img(), TERRAIN_BUILDING);
    }
    break;
    }
}

void building_entertainment::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();

    iob->bind____skip(26);
    iob->bind____skip(58);
    iob->bind(BIND_SIGNATURE_UINT8, &d.num_shows);
    iob->bind(BIND_SIGNATURE_UINT8, &d.juggler_visited);
    iob->bind(BIND_SIGNATURE_UINT8, &d.musician_visited);
    iob->bind(BIND_SIGNATURE_UINT8, &d.dancer_visited);
    iob->bind(BIND_SIGNATURE_INT8, &d.play_index);
    iob->bind____skip(19);
    iob->bind(BIND_SIGNATURE_UINT32, &d.latched_venue_main_grid_offset);
    iob->bind(BIND_SIGNATURE_UINT32, &d.latched_venue_add_grid_offset);
    iob->bind(BIND_SIGNATURE_UINT8, &base.orientation);
    iob->bind(BIND_SIGNATURE_UINT8, &d.conservatory_help);
    iob->bind____skip(6);
    iob->bind(BIND_SIGNATURE_UINT8, &d.consume_material_id);
    iob->bind(BIND_SIGNATURE_UINT8, &d.spawned_entertainer_days);
    iob->bind(BIND_SIGNATURE_UINT32, &d.booth_corner_grid_offset);
}

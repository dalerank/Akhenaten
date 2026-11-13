#include "building_entertainment.h"

#include "io/io_buffer.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "grid/image.h"
#include "grid/gardens.h"
#include "grid/building_tiles.h"
#include "graphics/view/view.h"

BUILDING_RUNTIME_DATA_IMPL(building_entertainment)

int building_entertainment::bandstand_main_img_offset(int orientation) {
    int offset = 0;
    if (orientation == 2) {
        switch (g_camera.orientation / 2) {
        case 0: offset = 1; break;
        case 1: offset = 2; break;
        case 2: offset = 0; break;
        case 3: offset = 3; break;
        }
    } else if (orientation == 3) {
        switch (g_camera.orientation / 2) {
        case 0: offset = 3; break;
        case 1: offset = 1; break;
        case 2: offset = 2; break;
        case 3: offset = 0; break;
        }
    } else if (orientation == 0) {
        switch (g_camera.orientation / 2) {
        case 0: offset = 1; break;
        case 1: offset = 2; break;
        case 2: offset = 0; break;
        case 3: offset = 3; break;
        }
    } else if (orientation == 1) {
        switch (g_camera.orientation / 2) {
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
        switch (g_camera.orientation / 2) {
        case 0: offset = 0; break;
        case 1: offset = 3; break;
        case 2: offset = 1; break;
        case 3: offset = 2; break;
        }
    } else if (orientation == 3) {
        switch (g_camera.orientation / 2) {
        case 0: offset = 2; break;
        case 1: offset = 0; break;
        case 2: offset = 3; break;
        case 3: offset = 1; break;
        }
    } else if (orientation == 0) {
        switch (g_camera.orientation / 2) {
        case 0: offset = 0; break;
        case 1: offset = 3; break;
        case 2: offset = 1; break;
        case 3: offset = 2; break;
        }
    } else if (orientation == 1) {
        switch (g_camera.orientation / 2) {
        case 0: offset = 3; break;
        case 1: offset = 1; break;
        case 2: offset = 2; break;
        case 3: offset = 0; break;
        }
    }
    return offset;
}

void building_entertainment::map_add_bandstand_tiles(int stand_orientation) {
    auto &d = runtime_data();
    if (!d.latched_venue_main_grid_offset || !d.latched_venue_add_grid_offset) {
        return;
    }

    int stand_sn_s = anim("stand_sn_s").first_img();
    map_image_set(d.latched_venue_main_grid_offset, stand_sn_s + bandstand_main_img_offset(stand_orientation));
    map_image_set(d.latched_venue_add_grid_offset, stand_sn_s + bandstand_add_img_offset(stand_orientation));
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

void building_entertainment::on_post_load() {
    // Saves before the record fit lost these past the record end and load them as 0; all follow from tile/orientation.
    auto& d = runtime_data();
    if (!d.booth_corner_grid_offset
        && building_type_any_of(base.type, {BUILDING_BOOTH, BUILDING_BANDSTAND, BUILDING_PAVILLION})) {
        d.booth_corner_grid_offset = tile().grid_offset();
    }

    inherited::on_post_load();
}

void building_entertainment::latch_stand_offsets(vec2i main_offset, vec2i add_offset) {
    auto& d = runtime_data();
    d.latched_venue_main_grid_offset = base.tile.shifted(main_offset.x, main_offset.y).grid_offset();
    d.latched_venue_add_grid_offset = base.tile.shifted(add_offset.x, add_offset.y).grid_offset();
}

void building_entertainment::latch_stand_offsets(const venue_place_offset& place) {
    vec2i main_offset, add_offset;
    for (const auto& item : place.items) {
        if (item.type == BUILDING_BANDSTAND) {
            (item.main ? main_offset : add_offset) = item.offset;
        }
    }
    latch_stand_offsets(main_offset, add_offset);
}

void building_entertainment::place_venue_items(const venue_place_offset& place, int stand_orientation) {
    for (const auto& item : place.items) {
        place_latch_on_venue(item.type, item.offset.x, item.offset.y, stand_orientation, item.main);
    }
}

// Offsets inside the dynamic part, which starts at record 0x52; OG data.entertainment starts at 0x54.
// OG keeps juggler/musician/dancer figure ids at 76..81 and num_shows + show_days_left at 84..87 (0xA6..0xA9);
// 2..75 and 88..101 are unused there, so the remake-only fields live in them.
void building_entertainment::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();

    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT32, &d.latched_venue_main_grid_offset); // 2
    iob->bind(BIND_SIGNATURE_UINT32, &d.latched_venue_add_grid_offset);  // 6
    iob->bind(BIND_SIGNATURE_UINT32, &d.booth_corner_grid_offset);       // 10
    iob->bind(BIND_SIGNATURE_UINT8, &d.conservatory_help);               // 14
    iob->bind(BIND_SIGNATURE_UINT8, &d.consume_material_id);             // 15
    iob->bind(BIND_SIGNATURE_UINT8, &d.spawned_entertainer_days);        // 16
    iob->bind____skip(67);
    iob->bind(BIND_SIGNATURE_UINT8, &d.num_shows);        // 84
    iob->bind(BIND_SIGNATURE_UINT8, &d.juggler_visited);  // 85
    iob->bind(BIND_SIGNATURE_UINT8, &d.musician_visited); // 86
    iob->bind(BIND_SIGNATURE_UINT8, &d.dancer_visited);   // 87
    iob->bind(BIND_SIGNATURE_INT8, &d.play_index);        // 88
    iob->bind____skip(15);
}

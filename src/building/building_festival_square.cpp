#include "building_festival_square.h"

#include "grid/grid.h"
#include "grid/building_tiles.h"
#include "construction/build_planner.h"
#include "grid/building.h"
#include "js/js_game.h"

BUILDING_RUNTIME_DATA_IMPL(building_festival_square)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_festival_square);

void building_festival_square::preview::setup_preview_graphics(build_planner &planer) const {
    const int s = building_static_params::get(planer.build_type).building_size;
    planer.init_tiles(s, s);
}

bool building_festival_square::target_route_tile_blocked(int grid_offset) const {
    return false;
}

void building_festival_square::on_place_update_tiles(int orientation, int variant) {
    auto &d = runtime_data();

    d.booth_corner_grid_offset = tile().grid_offset();
    base.orientation = orientation;

    int size = current_params().building_size;
    if (!map_grid_is_inside(tile(), size)) {
        return;
    }

    map_add_venue_plaza_tiles(id(), size, tile(), first_img(animkeys().square), false);
}

void building_festival_square::update_day() {
    building_impl::update_day();

    auto &d = runtime_data();
    int shows = 0;
    auto update_shows = [&] (auto &days) { if (days > 0) { --days; ++shows; } };
    update_shows(d.juggler_visited);
    update_shows(d.musician_visited);
    update_shows(d.dancer_visited);

    d.num_shows = shows;
}

void building_festival_square::on_undo() {
    auto &d = runtime_data();
    const int s = size();

    for (int dy = 0; dy < s; dy++) {
        for (int dx = 0; dx < s; dx++) {
            if (map_building_at(d.booth_corner_grid_offset + GRID_OFFSET(dx, dy)) == 0)
                map_building_set(d.booth_corner_grid_offset + GRID_OFFSET(dx, dy), id());
        }
    }
}

void building_festival_square::update_map_orientation(int map_orientation) {
    if (!is_main()) {
        return;
    }

    int plaza_image_id = anim("square").first_img();
    tile2i btile(runtime_data().booth_corner_grid_offset);
    map_add_venue_plaza_tiles(id(), size(), btile, plaza_image_id, true);
}


void building_festival_square::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();

    iob->bind(BIND_SIGNATURE_UINT8, &d.num_shows);
    iob->bind(BIND_SIGNATURE_UINT8, &d.juggler_visited);
    iob->bind(BIND_SIGNATURE_UINT8, &d.musician_visited);
    iob->bind(BIND_SIGNATURE_UINT8, &d.dancer_visited);
    iob->bind(BIND_SIGNATURE_UINT32, &d.booth_corner_grid_offset);
}

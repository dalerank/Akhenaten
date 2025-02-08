#include "building_festival_square.h"

#include "city/buildings.h"
#include "city/city.h"
#include "grid/grid.h"
#include "grid/building_tiles.h"
#include "grid/image.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/ui.h"
#include "construction/build_planner.h"
#include "building/count.h"
#include "grid/building.h"
#include "grid/orientation.h"
#include "city/labor.h"

building_festival_square::static_params festival_square_m;

void building_festival_square::static_params::load(archive arch) {
    square = anim[animkeys().square].first_img();
}

void building_festival_square::static_params::planer_setup_preview_graphics(build_planner &planer) const {
    planer.init_tiles(5, 5); // TODO
}

void building_festival_square::static_params::planer_ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const {
    int orientation = 0;

    bool can_build = map_orientation_for_venue_with_map_orientation(end, e_venue_mode_festival_square, &orientation);
    // TODO: proper correct for map orientation (for now, just use a different orientation)
    orientation = abs(orientation + (8 - city_view_orientation())) % 8;

    if (can_build != 1) { // no can place
        for (int i = 0; i < building_size * building_size; i++) {
            planer.draw_flat_tile(ctx, pixel + VIEW_OFFSETS[i], COLOR_MASK_RED);
        }
    } else { // can place (theoretically)
        int square_id = current_params().anim[animkeys().square].first_img();
        bool is_exist = building_count_total(BUILDING_FESTIVAL_SQUARE);
        int color_mask = is_exist ? COLOR_MASK_RED : COLOR_MASK_GREEN;
        for (int i = 0; i < building_size * building_size; i++) {
            ImageDraw::isometric(ctx, square_id + i, pixel + vec2i{ ((i % building_size) - (i / building_size)) * 30, ((i % building_size) + (i / building_size)) * 15 }, color_mask);
        }
    }
}

void building_festival_square::on_place(int orientation, int variant) {
    building_impl::on_place(orientation, variant);

    g_city.buildings.festival_square = tile();
}

void building_festival_square::on_place_update_tiles(int orientation, int variant) {
    data.entertainment.booth_corner_grid_offset = tile().grid_offset();
    data.entertainment.orientation = orientation;

    int size = params().building_size;
    if (!map_grid_is_inside(tile(), size)) {
        return;
    }

    map_add_venue_plaza_tiles(id(), size, tile(), festival_square_m.square, false);
    g_city.buildings.festival_square = this->tile();
}

void building_festival_square::on_destroy() {
    g_city.buildings.festival_square = tile2i::invalid;
}

void building_festival_square::update_day() {
    building_impl::update_day();

    int shows = 0;
    auto update_shows = [&] (auto &days) { if (days > 0) { --days; ++shows; } };
    update_shows(data.entertainment.juggler_visited);
    update_shows(data.entertainment.musician_visited);
    update_shows(data.entertainment.dancer_visited);

    data.entertainment.num_shows = shows;
}

void building_festival_square::on_undo() {
    for (int dy = 0; dy < 5; dy++) {
        for (int dx = 0; dx < 5; dx++) {
            if (map_building_at(data.entertainment.booth_corner_grid_offset + GRID_OFFSET(dx, dy)) == 0)
                map_building_set(data.entertainment.booth_corner_grid_offset + GRID_OFFSET(dx, dy), id());
        }
    }
}

void building_festival_square::on_post_load() {
    g_city.buildings.festival_square = this->tile();
}

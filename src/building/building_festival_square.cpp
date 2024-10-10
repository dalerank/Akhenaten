#include "building_festival_square.h"

#include "city/buildings.h"
#include "city/object_info.h"
#include "js/js_game.h"
#include "grid/grid.h"
#include "grid/building_tiles.h"
#include "grid/image.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/ui.h"
#include "building/count.h"
#include "grid/building.h"
#include "city/labor.h"

struct festival_square_model : public buildings::model_t<building_festival_square> {
    int square;
} festival_square_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_festival_square);
void config_load_building_festival_square() {
    festival_square_m.load();
    festival_square_m.square = festival_square_m.anim["square"].first_img();
}

void building_festival_square::on_place(int orientation, int variant) {
    building_impl::on_place(orientation, variant);

    city_buildings_add_festival_square(&base);
}

void building_festival_square::on_place_update_tiles(int orientation, int variant) {
    data.entertainment.booth_corner_grid_offset = tile().grid_offset();
    data.entertainment.orientation = orientation;

    int size = params().building_size;

    if (!map_grid_is_inside(tile(), size)) {
        return;
    }

    map_add_venue_plaza_tiles(id(), size, tile(), festival_square_m.square, false);
    city_buildings_add_festival_square(&base);
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
    city_buildings_add_festival_square(&base);
}

void building_festival_square::ghost_preview(painter &ctx, tile2i tile, vec2i pixel, int orientation) {
    int square_id = festival_square_m.anim["square"].first_img();
    int size = festival_square_m.building_size;
    bool is_exist = building_count_total(BUILDING_FESTIVAL_SQUARE);
    int color_mask = is_exist ? COLOR_MASK_RED : COLOR_MASK_GREEN;
    for (int i = 0; i < size * size; i++) {
        ImageDraw::isometric(ctx, square_id + i, pixel + vec2i{((i % size) - (i / size)) * 30, ((i % size) + (i / size)) * 15}, color_mask);
    }
}

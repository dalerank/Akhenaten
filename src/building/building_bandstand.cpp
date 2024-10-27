#include "building_bandstand.h"

#include "building/building.h"
#include "building/count.h"
#include "city/object_info.h"
#include "city/warnings.h"
#include "construction/build_planner.h"
#include "city/labor.h"
#include "game/resource.h"
#include "grid/property.h"
#include "grid/image.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "widget/city/ornaments.h"
#include "widget/city/building_ghost.h"
#include "sound/sound_building.h"
#include "figure/figure.h"
#include "js/js_game.h"

struct bandstand_model : public buildings::model_t<building_bandstand> {
    int stand_sn_n = 0;
    int stand_sn_s = 0;
    int stand_we_w = 0;
    int stand_we_e = 0;
    int booth = 0;
};

bandstand_model bandstand_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_bandstand_config);
void config_load_building_bandstand_config() {
    bandstand_m.load();
    bandstand_m.stand_sn_n = bandstand_m.anim["stand_sn_n"].first_img();
    bandstand_m.stand_sn_s = bandstand_m.anim["stand_sn_s"].first_img();
    bandstand_m.stand_we_w = bandstand_m.anim["stand_we_w"].first_img();
    bandstand_m.stand_we_e = bandstand_m.anim["stand_we_e"].first_img();
    bandstand_m.booth = bandstand_m.anim["booth"].first_img();
}

void building_bandstand::on_create(int orientation) {
}

void building_bandstand::update_day() {
    building_impl::update_day();

    int shows = 0;
    auto update_shows = [&] (auto &days) { if (days > 0) { --days; ++shows; } };
    update_shows(data.entertainment.juggler_visited);
    update_shows(data.entertainment.musician_visited);

    data.entertainment.num_shows = shows;
}

void building_bandstand::on_place(int orientation, int variant) {
    data.entertainment.booth_corner_grid_offset = tile().grid_offset();
    data.entertainment.orientation = orientation;

    building_impl::on_place(orientation, variant);
}

void building_bandstand::on_place_checks() {
    if (building_construction_has_warning()) {
        return;
    }

    if (building_count_active(BUILDING_CONSERVATORY) <= 0) {
        building_construction_warning_show(WARNING_BUILD_GLADIATOR_SCHOOL);
    }
}

void building_bandstand::on_place_update_tiles(int orientation, int variant) {
    int size = params().building_size;
    int image_id = anim(animkeys().square).first_img();

    // add underlying plaza first
    map_add_venue_plaza_tiles(id(), size, tile(), image_id, false);
    int absolute_orientation = (abs(orientation * 2 + (8 - city_view_orientation())) % 8) / 2;
    // add additional building parts, update graphics accordingly
    switch (absolute_orientation) {
    case 0:
        build_planner_latch_on_venue(BUILDING_GARDENS, &base, 2, 1, 0);
        build_planner_latch_on_venue(BUILDING_BOOTH, &base, 2, 0, 0);
        build_planner_latch_on_venue(BUILDING_BANDSTAND, &base, 0, 0, 0, true);
        build_planner_latch_on_venue(BUILDING_BANDSTAND, &base, 0, 1, 0, false);
        break;

    case 1:
        build_planner_latch_on_venue(BUILDING_GARDENS, &base, 1, 2, 0);
        build_planner_latch_on_venue(BUILDING_BOOTH, &base, 2, 2, 0);
        build_planner_latch_on_venue(BUILDING_BANDSTAND, &base, 1, 0, 1, true);
        build_planner_latch_on_venue(BUILDING_BANDSTAND, &base, 2, 0, 1, false);
        break;

    case 2:
        build_planner_latch_on_venue(BUILDING_GARDENS, &base, 2, 1, 0);
        build_planner_latch_on_venue(BUILDING_BOOTH, &base, 2, 2, 0);
        build_planner_latch_on_venue(BUILDING_BANDSTAND, &base, 0, 1, 2, true);
        build_planner_latch_on_venue(BUILDING_BANDSTAND, &base, 0, 2, 2, false);
        break;

    case 3:
        build_planner_latch_on_venue(BUILDING_GARDENS, &base, 1, 2, 0);
        build_planner_latch_on_venue(BUILDING_BOOTH, &base, 0, 2, 0);
        build_planner_latch_on_venue(BUILDING_BANDSTAND, &base, 1, 0, 3, true);
        build_planner_latch_on_venue(BUILDING_BANDSTAND, &base, 0, 0, 3, false);
        break;
    }
}

void building_bandstand::update_map_orientation(int map_orientation) {
    int plaza_image_id = anim(animkeys().square).first_img();
    tile2i btile(data.entertainment.booth_corner_grid_offset);
    map_add_venue_plaza_tiles(id(), base.size, btile, plaza_image_id, true);
    map_add_bandstand_tiles(&base);
}

void building_bandstand::spawn_figure() {
    if (!is_main()) {
        return;
    }

    if (!common_spawn_figure_trigger(100)) {
        return;
    }

    if (data.entertainment.juggler_visited > 0) {
        create_roaming_figure(FIGURE_JUGGLER, FIGURE_ACTION_94_ENTERTAINER_ROAMING, BUILDING_SLOT_SERVICE);
    }

    if (data.entertainment.musician_visited > 0) {
        create_roaming_figure(FIGURE_MUSICIAN, FIGURE_ACTION_94_ENTERTAINER_ROAMING, BUILDING_SLOT_SERVICE);
    }
}

bool building_bandstand::force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) {
    int imgs[] = {bandstand_m.booth, bandstand_m.stand_sn_n, bandstand_m.stand_sn_s, bandstand_m.stand_we_e, bandstand_m.stand_we_w};
    int image_id = map_image_at(tile);
    const auto it = std::find(std::begin(imgs), std::end(imgs), image_id);
    return (it == std::end(imgs));
}

bool building_bandstand::force_draw_height_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) {
    int imgs[] = {bandstand_m.booth, bandstand_m.stand_sn_n, bandstand_m.stand_sn_s, bandstand_m.stand_we_e, bandstand_m.stand_we_w};
    int image_id = map_image_at(tile);
    const auto it = std::find(std::begin(imgs), std::end(imgs), image_id);
    if (it != std::end(imgs)) {
       ImageDraw::isometric_from_drawtile(ctx, image_id, pixel, mask);
       ImageDraw::isometric_from_drawtile_top(ctx, image_id, pixel, mask);
    }
    return false;
}

void building_bandstand::on_undo() {
    for (int dy = 0; dy < 3; dy++) {
        for (int dx = 0; dx < 3; dx++) {
            if (map_building_at(data.entertainment.booth_corner_grid_offset + GRID_OFFSET(dx, dy)) == 0)
                map_building_set(data.entertainment.booth_corner_grid_offset + GRID_OFFSET(dx, dy), id());
        }
    }
}

void building_bandstand::draw_shows_musicians(painter &ctx, vec2i pixel, int direction, color color_mask) {
    building* main = base.main();
    if (!main->data.entertainment.musician_visited) {
        return;
    }

    building* next_tile = base.next();
    switch (direction) {
    case 0:
    {
        const animation_t &ranim = anim("musician_sn");
        building_draw_normal_anim(ctx, pixel, &base, tile(), ranim, color_mask);
    }
    break;

    case 1:
    {
        const animation_t &ranim = anim("musician_we");
        building_draw_normal_anim(ctx, pixel, &base, tile(), ranim, color_mask);
    }
    break;
    }
}

void building_bandstand::update_count() const {
    building_increase_type_count(BUILDING_BOOTH, num_workers() > 0);
}

bool building_bandstand::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) {
    int color_mask = 0;
    if (drawing_building_as_deleted(&base) || map_property_is_deleted(tile)) {
        color_mask = COLOR_MASK_RED;
    }

    int grid_offset = tile.grid_offset();
    if (map_image_at(grid_offset) == bandstand_m.stand_sn_n) {
        draw_shows_musicians(ctx, point, 1, color_mask);
    } else if (map_image_at(grid_offset) == bandstand_m.stand_we_w) {
        draw_shows_musicians(ctx, point, 0, color_mask);
    }

    if (map_image_at(grid_offset) == bandstand_m.booth) {
        const animation_t &anim = bandstand_m.anim["juggler"];
        building* main = base.main();
        if (main->data.entertainment.juggler_visited) {
            building_draw_normal_anim(ctx, point, &base, tile, anim, mask);
        }
    }

    return false;
}

void building_bandstand::ghost_preview(painter &ctx, tile2i tile, vec2i pixel, int orientation) {
    int size = bandstand_m.building_size;
    int square_id = bandstand_m.anim["square"].first_img();
    for (int i = 0; i < size * size; i++) {
        ImageDraw::isometric(ctx, square_id + i, pixel + vec2i{((i % size) - (i / size)) * 30, ((i % size) + (i / size)) * 15}, COLOR_MASK_GREEN);
    }

    switch (orientation / 2) {
    case 0:
        draw_building_ghost(ctx, bandstand_m.stand_sn_n, pixel, COLOR_MASK_GREEN);
        draw_building_ghost(ctx, bandstand_m.stand_sn_s, pixel + vec2i{-30, 15}, COLOR_MASK_GREEN);
        draw_building_ghost(ctx, bandstand_m.booth, pixel + vec2i{60, 30}, COLOR_MASK_GREEN);
        break;
    case 1:
        draw_building_ghost(ctx, bandstand_m.stand_we_w, pixel + vec2i{30, 15}, COLOR_MASK_GREEN);
        draw_building_ghost(ctx, bandstand_m.stand_we_e, pixel + vec2i{60, 30}, COLOR_MASK_GREEN);
        draw_building_ghost(ctx, bandstand_m.booth, pixel + vec2i{0, 60}, COLOR_MASK_GREEN);
        break;
    case 2:
        draw_building_ghost(ctx, bandstand_m.stand_sn_n, pixel + vec2i{-30, 15}, COLOR_MASK_GREEN);
        draw_building_ghost(ctx, bandstand_m.stand_sn_s, pixel + vec2i{-60, 30}, COLOR_MASK_GREEN);
        draw_building_ghost(ctx, bandstand_m.booth, pixel + vec2i{0, 60}, COLOR_MASK_GREEN);
        break;
    case 3:
        draw_building_ghost(ctx, bandstand_m.stand_we_w, pixel, COLOR_MASK_GREEN);
        draw_building_ghost(ctx, bandstand_m.stand_we_e, pixel + vec2i{30, 15}, COLOR_MASK_GREEN);
        draw_building_ghost(ctx, bandstand_m.booth, pixel + vec2i{-60, 30}, COLOR_MASK_GREEN);
        break;
    }
}

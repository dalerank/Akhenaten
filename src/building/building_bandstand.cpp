#include "building_bandstand.h"

#include "building/building.h"
#include "city/object_info.h"
#include "city/city_warnings.h"
#include "construction/build_planner.h"
#include "city/city_labor.h"
#include "game/resource.h"
#include "grid/property.h"
#include "grid/image.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "grid/orientation.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "game/game_config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "widget/city/ornaments.h"
#include "widget/city/building_ghost.h"
#include "sound/sound_building.h"
#include "figure/figure.h"

namespace parts {
    xstring stand_sn_n("stand_sn_n");
    xstring stand_sn_s("stand_sn_s");
    xstring stand_we_w("stand_we_w");
    xstring stand_we_e("stand_we_e");
    xstring musician_sn("musician_sn");
    xstring musician_we("musician_we");
    xstring booth("booth");
}

building_bandstand::static_params bandstand_m;

bool building_bandstand::static_params::plane_ghost_allow_tile(build_planner& p, tile2i tile) const {
    const bool is_road = map_terrain_is(tile, TERRAIN_ROAD);
    const bool has_figure = map_has_figure_at(tile);
    return (is_road || !has_figure);
}

void building_bandstand::static_params::planer_setup_preview_graphics(build_planner &planer) const {
    planer.init_tiles(3, 3);
}

void building_bandstand::static_params::planer_ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const {
    int orientation = 0;

    int can_build = map_orientation_for_venue_with_map_orientation(end, e_venue_mode_bandstand, &orientation);
    // TODO: proper correct for map orientation (for now, just use a different orientation)
    orientation = abs(orientation + (8 - city_view_orientation())) % 8;

    if (can_build != 1) { // no can place
        for (int i = 0; i < building_size * building_size; i++) {
            planer.draw_flat_tile(ctx, pixel + VIEW_OFFSETS[i], COLOR_MASK_RED);
        }
    } else { // can place (theoretically)
        int square_id = animations[animkeys().square].first_img();
        for (int i = 0; i < building_size * building_size; i++) {
            ImageDraw::isometric(ctx, square_id + i, pixel + vec2i{ ((i % building_size) - (i / building_size)) * 30, ((i % building_size) + (i / building_size)) * 15 }, COLOR_MASK_GREEN);
        }

        switch (orientation / 2) {
        case 0:
            planer.draw_building_ghost(ctx, animations[parts::stand_sn_n].first_img(), pixel, COLOR_MASK_GREEN);
            planer.draw_building_ghost(ctx, animations[parts::stand_sn_s].first_img(), pixel + vec2i{ -30, 15 }, COLOR_MASK_GREEN);
            planer.draw_building_ghost(ctx, animations[parts::booth].first_img(), pixel + vec2i{ 60, 30 }, COLOR_MASK_GREEN);
            break;
        case 1:
            planer.draw_building_ghost(ctx, animations[parts::stand_we_w].first_img(), pixel + vec2i{ 30, 15 }, COLOR_MASK_GREEN);
            planer.draw_building_ghost(ctx, animations[parts::stand_we_e].first_img(), pixel + vec2i{ 60, 30 }, COLOR_MASK_GREEN);
            planer.draw_building_ghost(ctx, animations[parts::booth].first_img(), pixel + vec2i{ 0, 60 }, COLOR_MASK_GREEN);
            break;
        case 2:
            planer.draw_building_ghost(ctx, animations[parts::stand_sn_n].first_img(), pixel + vec2i{ -30, 15 }, COLOR_MASK_GREEN);
            planer.draw_building_ghost(ctx, animations[parts::stand_sn_s].first_img(), pixel + vec2i{ -60, 30 }, COLOR_MASK_GREEN);
            planer.draw_building_ghost(ctx, animations[parts::booth].first_img(), pixel + vec2i{ 0, 60 }, COLOR_MASK_GREEN);
            break;
        case 3:
            planer.draw_building_ghost(ctx, animations[parts::stand_we_w].first_img(), pixel, COLOR_MASK_GREEN);
            planer.draw_building_ghost(ctx, animations[parts::stand_we_e].first_img(), pixel + vec2i{ 30, 15 }, COLOR_MASK_GREEN);
            planer.draw_building_ghost(ctx, animations[parts::booth].first_img(), pixel + vec2i{ -60, 30 }, COLOR_MASK_GREEN);
            break;
        }
    }
}

void building_bandstand::on_create(int orientation) {
}

void building_bandstand::update_day() {
    building_impl::update_day();

    int shows = 0;
    auto update_shows = [&] (auto &days) { if (days > 0) { --days; ++shows; } };

    auto &d = runtime_data();
    update_shows(d.juggler_visited);
    update_shows(d.musician_visited);

    d.num_shows = shows;
}

void building_bandstand::on_place(int orientation, int variant) {
    auto &d = runtime_data();
    d.booth_corner_grid_offset = tile().grid_offset();
    base.orientation = orientation;

    building_impl::on_place(orientation, variant);
}

void building_bandstand::on_place_checks() {
    construction_warnings warnings;
    const bool has_conservatory = g_city.buildings.count_active(BUILDING_CONSERVATORY) > 0;
    const bool has_jungles = g_city.buildings.count_active(BUILDING_JUGGLER_SCHOOL) > 0;
    warnings.add_if(!has_conservatory, "#build_conservatory");
    warnings.add_if(!has_jungles, "#build_juggling_school");
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
        place_latch_on_venue(BUILDING_GARDENS, 2, 1, 0);
        place_latch_on_venue(BUILDING_BOOTH, 2, 0, 0);
        place_latch_on_venue(BUILDING_BANDSTAND, 0, 0, 0, true);
        place_latch_on_venue(BUILDING_BANDSTAND, 0, 1, 0, false);
        break;

    case 1:
        place_latch_on_venue(BUILDING_GARDENS, 1, 2, 0);
        place_latch_on_venue(BUILDING_BOOTH, 2, 2, 0);
        place_latch_on_venue(BUILDING_BANDSTAND, 1, 0, 1, true);
        place_latch_on_venue(BUILDING_BANDSTAND, 2, 0, 1, false);
        break;

    case 2:
        place_latch_on_venue(BUILDING_GARDENS, 2, 1, 0);
        place_latch_on_venue(BUILDING_BOOTH, 2, 2, 0);
        place_latch_on_venue(BUILDING_BANDSTAND, 0, 1, 2, true);
        place_latch_on_venue(BUILDING_BANDSTAND, 0, 2, 2, false);
        break;

    case 3:
        place_latch_on_venue(BUILDING_GARDENS, 1, 2, 0);
        place_latch_on_venue(BUILDING_BOOTH, 0, 2, 0);
        place_latch_on_venue(BUILDING_BANDSTAND, 1, 0, 3, true);
        place_latch_on_venue(BUILDING_BANDSTAND, 0, 0, 3, false);
        break;
    }
}

void building_bandstand::map_add_bandstand_tiles() {
    int offset = bandstand_main_img_offset(base.orientation);
    int offset_add = bandstand_add_img_offset(base.orientation);

    int stand_sn_s = first_img("stand_sn_s");
    auto &d = runtime_data();
    map_image_set(d.latched_venue_main_grid_offset, stand_sn_s + offset);
    map_image_set(d.latched_venue_add_grid_offset, stand_sn_s + offset_add);
}


void building_bandstand::update_map_orientation(int map_orientation) {
    int plaza_image_id = anim(animkeys().square).first_img();
    auto &d = runtime_data();

    tile2i btile(d.booth_corner_grid_offset);
    map_add_venue_plaza_tiles(id(), base.size, btile, plaza_image_id, true);
    map_add_bandstand_tiles();
}

void building_bandstand::spawn_figure() {
    if (!is_main()) {
        return;
    }

    auto &d = runtime_data();
    if (common_spawn_figure_trigger(100, BUILDING_SLOT_JUGGLER)) {
        if (d.juggler_visited > 0) {
            create_roaming_figure(FIGURE_JUGGLER, FIGURE_ACTION_94_ENTERTAINER_ROAMING, BUILDING_SLOT_JUGGLER);
            return;
        }
    }

    if (common_spawn_figure_trigger(100, BUILDING_SLOT_MUSICIAN)) {
        if (d.musician_visited > 0) {
            create_roaming_figure(FIGURE_MUSICIAN, FIGURE_ACTION_94_ENTERTAINER_ROAMING, BUILDING_SLOT_MUSICIAN);
            return;
        }
    }
}

bool building_bandstand::force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) {
    xstring imgs[] = { parts::booth, parts::stand_sn_n, parts::stand_sn_s, parts::stand_we_e, parts::stand_we_w };
    int image_id = map_image_at(tile);
    const auto it = std::find_if(std::begin(imgs), std::end(imgs), [&] (auto &p) { return first_img(p) == image_id; });
    return (it == std::end(imgs));
}

bool building_bandstand::force_draw_height_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) {
    xstring imgs[] = {parts::booth, parts::stand_sn_n, parts::stand_sn_s, parts::stand_we_e, parts::stand_we_w};
    int image_id = map_image_at(tile);
    const auto it = std::find_if(std::begin(imgs), std::end(imgs), [&] (auto &p) { return first_img(p) == image_id; });
    if (it != std::end(imgs)) {
        auto& command = ImageDraw::create_subcommand(render_command_t::ert_drawtile_full);
        command.image_id = image_id;
        command.pixel = pixel;
        command.mask = mask;
    }
    return false;
}

void building_bandstand::on_undo() {
    auto &d = runtime_data();
    for (int dy = 0; dy < 3; dy++) {
        for (int dx = 0; dx < 3; dx++) {
            if (map_building_at(d.booth_corner_grid_offset + GRID_OFFSET(dx, dy)) == 0)
                map_building_set(d.booth_corner_grid_offset + GRID_OFFSET(dx, dy), id());
        }
    }
}

void building_bandstand::draw_shows_musicians(painter &ctx, vec2i pixel, tile2i tile, int direction, color color_mask) {
    if (direction < 0) {
        return;
    }

    auto &d = runtime_data();
    if (!d.musician_visited) {
        return;
    }

    building* next_tile = base.next();
    const xstring& anim_key = (direction == 0) ? parts::musician_sn : parts::musician_we;
    d.musician_ctx = anim(anim_key);

    draw_normal_anim(ctx, d.musician_ctx, pixel, tile, color_mask);
}

void building_bandstand::on_tick(bool refresh_only) {
    inherited::on_tick(refresh_only);

    auto &d = runtime_data();
    d.musician_ctx.update(refresh_only);
    d.juggler_ctx.update(refresh_only);
}

void building_bandstand::draw_shows_juggler(painter &ctx, vec2i pixel, tile2i tile, int direction, color color_mask) {
    auto &d = runtime_data();
    if (!d.juggler_visited) {
        return;
    }

    if (map_image_at(tile) != first_img(parts::booth)) {
        return;
    }
    
    d.juggler_ctx = anim("juggler");
    draw_normal_anim(ctx, d.juggler_ctx, pixel, tile, color_mask);
}

bool building_bandstand::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) {
    const bool is_deleted = drawing_building_as_deleted(&base) || map_property_is_deleted(tile);
    int color_mask = is_deleted ? COLOR_MASK_RED : COLOR_MASK_NONE;

    const int direction = (map_image_at(tile) == first_img(parts::stand_sn_n)) ? 1 :
                          (map_image_at(tile) == first_img(parts::stand_we_e)) ? 0 : -1;

    draw_shows_juggler(ctx, point, tile, direction, color_mask);
    draw_shows_musicians(ctx, point, tile, direction, color_mask);

    return false;
}

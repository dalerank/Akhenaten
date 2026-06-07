#include "building_booth.h"

#include "building/building.h"
#include "construction/build_planner.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "game/game_config.h"
#include "grid/building_tiles.h"
#include "grid/property.h"
#include "grid/building.h"
#include "grid/figure.h"
#include "grid/image.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "widget/city/ornaments.h"
#include "sound/sound_building.h"
#include "figuretype/figure_entertainer.h"
#include "city/city_labor.h"
#include "figure/figure.h"
#include "grid/routing/routing_grids.h"
#include "js/js_game.h"
#include "core/profiler.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_booth);

bool building_booth::preview::ghost_allow_tile(build_planner &p, tile2i tile) const {
    const bool is_road = map_terrain_is(tile, TERRAIN_ROAD);
    const bool has_figure = map_has_figure_at(tile);
    return (is_road || !has_figure);
}

bool building_booth::get_route_citizen_land_type(int grid_offset, int &land_result) const {
    if (map_terrain_is(grid_offset, TERRAIN_ROAD)) {
        land_result = CITIZEN_0_ROAD;
        return true;
    }

    land_result = CITIZEN_N1_BLOCKED;
    return true;
}

bool building_booth::target_route_tile_blocked(int grid_offset) const {
    return false;
}

void building_booth::preview::setup_preview_graphics(build_planner &planer) const {
    planer.init_tiles(2, 2);
}

void building_booth::update_day() {
    building_impl::update_day();

    auto &d = runtime_data();
    d.num_shows = 0;
    if (d.juggler_visited > 0) {
        --d.juggler_visited;
        ++d.num_shows;
    }
}

void building_booth::update_month() {
    auto &d = runtime_data();
    d.play_index = std::rand() % 10;
}

void building_booth::on_place(int orientation, int variant) {
    base.orientation = orientation;

    auto &d = runtime_data();
    d.booth_corner_grid_offset = tile().grid_offset();

    building_impl::on_place(orientation, variant);
}

void building_booth::on_place_update_tiles(int orientation, int variant) {
    int image_id = anim(animkeys().square).first_img();

    // add underlying plaza first
    map_add_venue_plaza_tiles(id(), current_params().building_size, tile(), image_id, false);
    int absolute_orientation = (abs(orientation * 2 + (8 - g_camera.orientation)) % 8) / 2;

    // add additional building parts, update graphics accordingly
    switch (absolute_orientation) {
    case 0: place_latch_on_venue(BUILDING_BOOTH, 0, 0, orientation, true); break;
    case 1: place_latch_on_venue(BUILDING_BOOTH, 1, 0, orientation, true); break;
    case 2: place_latch_on_venue(BUILDING_BOOTH, 1, 1, orientation, true); break;
    case 3: place_latch_on_venue(BUILDING_BOOTH, 0, 1, orientation, true); break;
    }
}

void building_booth::spawn_figure() {
    if (!is_main()) {
        return;
    }

    if (!common_spawn_figure_trigger(current_params().min_houses_coverage, BUILDING_SLOT_JUGGLER)) {
        return;
    }

    auto &d = runtime_data();
    if (d.juggler_visited > 0) {
        create_roaming_figure(FIGURE_JUGGLER, (e_figure_action)ACTION_94_ENTERTAINER_ROAMING, BUILDING_SLOT_JUGGLER);
    }
}

bool building_booth::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) {
    int color_mask = 0;
    if (drawing_building_as_deleted(&base) || map_property_is_deleted(tile)) {
        color_mask = COLOR_MASK_RED;
    }

    int grid_offset = tile.grid_offset();
    auto &d = runtime_data();
    if (d.juggler_visited && map_image_at(grid_offset) == first_img(animkeys().booth)) {
        const animation_t &anim = this->anim(animkeys().juggler);
        building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);
    }
    return true;
}

bool building_booth::force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) {
    OZZY_PROFILER_FUNCTION()
    int image_id = map_image_at(tile);
    return (first_img(animkeys().booth)!= image_id);
}

bool building_booth::force_draw_height_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) {
    OZZY_PROFILER_FUNCTION()

    int image_id = map_image_at(tile);
    if (first_img(animkeys().booth) == image_id) {
        auto& command = ImageDraw::create_subcommand(ctx, render_command_t::ert_drawtile_full);
        command.image_id = image_id;
        command.pixel = pixel;
        command.mask = mask;
    }

    return false;
}

void building_booth::update_map_orientation(int map_orientation) {
    int plaza_image_id = anim(animkeys().square).first_img();
    auto &d = runtime_data();
    tile2i btile(d.booth_corner_grid_offset);
    map_add_venue_plaza_tiles(id(), base.size, btile, plaza_image_id, true);
}

void building_booth::on_undo() {
    auto &d = runtime_data();
    for (int dy = 0; dy < 2; dy++) {
        for (int dx = 0; dx < 2; dx++) {
            if (map_building_at(d.booth_corner_grid_offset + GRID_OFFSET(dx, dy)) == 0) {
                map_building_set(d.booth_corner_grid_offset + GRID_OFFSET(dx, dy), id());
            }
        }
    }
}
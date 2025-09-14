#include "building/building_fort.h"

#include "building/rotation.h"
#include "figure/formation.h"
#include "figure/formation_legion.h"
#include "widget/city/building_ghost.h"
#include "widget/city/ornaments.h"
#include "window/building/common.h"
#include "construction/build_planner.h"
#include "city/city.h"
#include "city/city_warnings.h"
#include "graphics/view/view.h"
#include "graphics/view/lookup.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/ui.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "grid/property.h"
#include "grid/building_tiles.h"
#include "grid/building.h"

#include "graphics/animation.h"
#include "city/city_labor.h"
#include "game/undo.h"

building_fort_charioteers::static_params fort_charioteers_m;
building_fort_archers::static_params fort_archers_m;
building_fort_infantry::static_params fort_infantry_m;
building_fort_ground::static_params fort_ground_m;

template<typename T>
void building_fort::static_params_t<T>::planer_ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const {
    bool fully_blocked = false;
    bool blocked = false;
    if (formation_get_num_forts_cached() >= formation_get_max_forts() || g_city.finance.is_out_of_money()) {
        fully_blocked = true;
        blocked = true;
    }

    const auto &ground_params = building_impl::params(BUILDING_FORT_GROUND);
    int fort_size = this->building_size;
    int ground_size = ground_params.building_size;
    int global_rotation = building_rotation_global_rotation();

    vec2i tile_ground_offset = this->ghost.ground_check_offset[global_rotation * 4 + (city_view_orientation() / 2)];
    tile2i tile_ground = end.shifted(tile_ground_offset.x, tile_ground_offset.y);

    blocked_tile_vec blocked_tiles_fort;
    blocked_tile_vec blocked_tiles_ground;

    blocked |= !!planer.is_blocked_for_building(end, fort_size, blocked_tiles_fort);
    blocked |= !!planer.is_blocked_for_building(tile_ground, ground_size, blocked_tiles_ground);

    int orientation_index = building_rotation_get_storage_fort_orientation(global_rotation) / 2;
    vec2i main_pixel = pixel + this->ghost.main_view_offset[orientation_index];
    vec2i ground_pixel = pixel + this->ghost.ground_view_offset[orientation_index];

    if (blocked) {
        planer.draw_partially_blocked(ctx, fully_blocked, blocked_tiles_fort);
        planer.draw_partially_blocked(ctx, fully_blocked, blocked_tiles_ground);
    } else {
        int image_id = this->anim[animkeys().base].first_img();
        if (orientation_index == 0 || orientation_index == 3) {
            // draw fort first, then ground
            planer.draw_building_ghost(ctx, image_id, main_pixel);
            planer.draw_building_ghost(ctx, image_id + 1, ground_pixel);
        } else {
            // draw ground first, then fort
            planer.draw_building_ghost(ctx, image_id + 1, ground_pixel);
            planer.draw_building_ghost(ctx, image_id, main_pixel);
        }
    }
}

template<typename T>
void building_fort::static_params_t<T>::planer_ghost_blocked(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel, bool fully_blocked) const {
    planer_ghost_preview(planer, ctx, start, end, pixel);
}

void building_fort::on_place_update_tiles(int orientation, int variant) {
    base.prev_part_building_id = 0;
    int image_id = params().anim[animkeys().base].first_img();
    map_building_tiles_add(id(), tile(), base.size, image_id, TERRAIN_BUILDING);

    auto &d = runtime_data();
    if (type() == BUILDING_FORT_CHARIOTEERS) {
        d.figure_type = FIGURE_FCHARIOTEER;
    } else if (type() == BUILDING_FORT_ARCHERS) {
        d.figure_type = FIGURE_ARCHER;
    } else if (type() == BUILDING_FORT_INFANTRY) {
        d.figure_type = FIGURE_INFANTRY;
    }

    // create parade ground
    const int offsets_x[] = {3, -1, -4, 0};
    const int offsets_y[] = {-1, -4, 0, 3};
    int global_rotation = building_rotation_global_rotation();
    building* ground = building_create(BUILDING_FORT_GROUND, tile().shifted(offsets_x[global_rotation], offsets_y[global_rotation]), 0);
    game_undo_add_building(ground);
    ground->prev_part_building_id = id();
    base.next_part_building_id = ground->id;
    ground->next_part_building_id = 0;
    tile2i fort_tile_add = tile().shifted(offsets_x[global_rotation], offsets_y[global_rotation]);

    int ground_id = params().anim[animkeys().ground].first_img();
    map_building_tiles_add(ground->id, fort_tile_add, 4, ground_id, TERRAIN_BUILDING);

    base.formation_id = formation_legion_create_for_fort(&base);
    ground->formation_id = base.formation_id;
}

void building_fort::on_place_checks() {
    construction_warnings warnings;

    const bool has_barracks = g_city.buildings.count_active(BUILDING_RECRUITER) > 0;
    warnings.add_if(!has_barracks, "#needs_recruiter_to_conscript");
}

bool building_fort::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (map_property_is_draw_tile(tile.grid_offset())) {
        int mask = drawing_building_as_deleted(&base) ? COLOR_MASK_RED : 0;
        const auto &anim = params().anim[animkeys().picture];

        auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
        command.image_id = anim.first_img();
        command.pixel = point + anim.pos;
        command.mask = color_mask;
    }

    return true;
}

void building_fort::bind_dynamic(io_buffer *iob, size_t verrsion) {
    auto &d = runtime_data();
    iob->bind(BIND_SIGNATURE_UINT16, &d.figure_type);
}

void building_fort::highlight_waypoints() {
    map_clear_highlights();
}

void building_fort::spawn_figure() {
    formation_legion_update_recruit_status(&base);
}
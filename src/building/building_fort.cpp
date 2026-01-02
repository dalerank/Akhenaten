#include "building/building_fort.h"

#include "building/rotation.h"
#include "figure/formation.h"
#include "figure/formation_batalion.h"
#include "widget/city/building_ghost.h"
#include "widget/city/ornaments.h"
#include "window/building/common.h"
#include "construction/build_planner.h"
#include "city/city.h"
#include "city/city_buildings.h"
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

#include "js/js_game.h"
#include "dev/debug.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_fort_charioteers);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_fort_archers);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_fort_infantry);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_fort_ground);

declare_console_command_p(force_fill_fort) {
    hvector<building_fort *, 4> forts;
    for (auto &bldg : city_buildings()) {
        building_fort *fort = bldg.dcast_fort();
        if (fort) {
            forts.push_back(fort);
        }
    }
}

template<typename T>
const building_fort::base_params &fort_static_params(const building_static_params &params) {
    using static_params = typename T::static_params;
    const auto &bparams = (const static_params &)params;
    return (const building_fort::base_params &)bparams;
}

const building_fort::base_params &get_fort_params(e_building_type type) {
    const auto &params = building_static_params::get(type);

    switch (params.type) {
    case BUILDING_FORT_CHARIOTEERS: return fort_static_params<building_fort_charioteers>(params);
    case BUILDING_FORT_ARCHERS: return fort_static_params<building_fort_archers>(params);
    case BUILDING_FORT_INFANTRY: return fort_static_params<building_fort_infantry>(params);
    default:
        break;
    }

    static building_fort::base_params dummy;
    return dummy;
};

void building_fort::preview::ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const {
    bool fully_blocked = false;
    bool blocked = false;
    if (g_formations.num_batalions >= formation_get_max_forts() || g_city.finance.is_out_of_money()) {
        fully_blocked = true;
        blocked = true;
    }

    const auto &ground_params = building_static_params::get(BUILDING_FORT_GROUND);
    const auto &params = building_static_params::get(planer.build_type);
    int fort_size = params.building_size;
    int ground_size = ground_params.building_size;
    int global_rotation = building_rotation_global_rotation();

    const auto &base_params = get_fort_params(planer.build_type);
    vec2i tile_ground_offset = base_params.ghost.ground_check_offset[global_rotation * 4 + (city_view_orientation() / 2)];
    tile2i tile_ground = end.shifted(tile_ground_offset.x, tile_ground_offset.y);

    blocked_tile_vec blocked_tiles_fort;
    blocked_tile_vec blocked_tiles_ground;

    blocked |= !!planer.is_blocked_for_building(end, fort_size, blocked_tiles_fort);
    blocked |= !!planer.is_blocked_for_building(tile_ground, ground_size, blocked_tiles_ground);

    int orientation_index = building_rotation_get_storage_fort_orientation(global_rotation) / 2;
    vec2i main_pixel = pixel + base_params.ghost.main_view_offset[orientation_index];
    vec2i ground_pixel = pixel + base_params.ghost.ground_view_offset[orientation_index];

    if (blocked) {
        planer.draw_partially_blocked(ctx, fully_blocked, blocked_tiles_fort);
        planer.draw_partially_blocked(ctx, fully_blocked, blocked_tiles_ground);
    } else {
        int image_id = params.base_img();
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

formation_id building_fort::create_batalion() {
    g_formations.calculate_batalion_totals();

    formation *m = formation_get_free(1);
    if (!m->id) {
        return 0;
    }

    m->faction_id = 1;
    m->in_use = 1;
    m->own_batalion = true;
    m->figure_type = runtime_data().figure_type;
    m->building_id = id();
    m->layout = FORMATION_DOUBLE_LINE_1;
    m->morale = 50;
    m->is_at_fort = 1;
    m->batalion_id = m->id - 1;
    m->max_figures = 16;
    verify_no_crash(m->batalion_id <= 9);

    building_fort_ground *fort_ground = ground();
    m->home = fort_ground->tile();
    m->tile = fort_ground->tile();
    m->standard_tile = fort_ground->tile();

    figure *standard = figure_create(FIGURE_STANDARD_BEARER, tile2i(0, 0), DIR_0_TOP_RIGHT);
    m->standard_figure_id = standard->id;
    standard->formation_id = m->id;
    standard->set_home(id());

    return m->id;
}

const building_fort::base_params &building_fort::base_params_ref() const {
    return get_fort_params(type());
}

void building_fort::preview::ghost_blocked(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel, bool fully_blocked) const {
    ghost_preview(planer, ctx, start, end, pixel);
}

void building_fort::on_place_update_tiles(int orientation, int variant) {
    base.prev_part_building_id = 0;
    int image_id = base_img();
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
    runtime_data().ground = ground->id;
    tile2i fort_tile_add = tile().shifted(offsets_x[global_rotation], offsets_y[global_rotation]);

    int ground_id = current_params().first_img(animkeys().ground);
    map_building_tiles_add(ground->id, fort_tile_add, 4, ground_id, TERRAIN_BUILDING);

    base.formation_id = create_batalion();
    ground->formation_id = base.formation_id;
}

void building_fort::on_place_checks() {
    construction_warnings warnings;

    const bool has_barracks = g_city.buildings.count_active(BUILDING_RECRUITER) > 0;
    warnings.add_if(!has_barracks, "#needs_recruiter_to_conscript");
}

void building_fort::remove_batalion() {
    if (base.formation_id <= 0) {
        return;
    }

    formation *m = formation_get(base.formation_id);
    if (!m->in_use) {
        return;
    }

    if (m->standard_figure_id) {
        figure_get(m->standard_figure_id)->poof();
    }

    g_formations.clear(base.formation_id);
    g_formations.calculate_batalion_totals();
}

void building_fort::on_destroy() {
    remove_batalion();
}

bool building_fort::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (map_property_is_draw_tile(tile.grid_offset())) {
        int mask = drawing_building_as_deleted(&base) ? COLOR_MASK_RED : 0;
        const auto &ranim = anim(animkeys().picture);

        auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
        command.image_id = ranim.first_img();
        command.pixel = point + ranim.pos;
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
    formation_batalion_update_recruit_status(&base);
}
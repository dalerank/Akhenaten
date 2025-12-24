#include "building_planer_renderer.h"

#include "building_static_params.h"
#include "building/construction/build_planner.h"
#include "city/city_buildings.h"
#include "building/building.h"
#include "game/undo.h"
#include "grid/figure.h"

static std::array<const building_planer_renderer *, BUILDING_MAX> *building_planer_rends = nullptr;

bool building_planer_renderer::is_need_flag(build_planner &planer, e_building_flags flag) const {
    const auto &params = building_static_params::get(planer.build_type);
    const auto &needs = params.needs;
    switch (flag) {
    case e_building_flag::Meadow: return needs.meadow;
    case e_building_flag::Rock: return needs.rock;
    case e_building_flag::Ore: return needs.ore;
    case e_building_flag::TempleUpgradeAltar: return needs.altar;
    case e_building_flag::TempleUpgradeOracle: return needs.oracle;
    case e_building_flag::NearbyWater: return needs.nearby_water;
    case e_building_flag::Groundwater: return needs.groundwater;
    case e_building_flag::ShoreLine: return needs.shoreline;
    case e_building_flag::Canals: return needs.canals;
    case e_building_flag::FloodplainShore: return needs.floodplain_shoreline;
    }

    return false;
}

bool building_planer_renderer::ghost_allow_tile(build_planner &p, tile2i tile) const {
    return (map_has_figure_at(tile) == false);
};
const building_planer_renderer building_planer_renderer::dummy;

void building_planer_renderer::register_model(e_building_type e, const building_planer_renderer &p) {
    if (!building_planer_rends) {
        building_planer_rends = new std::array<const building_planer_renderer *, BUILDING_MAX>();
        std::fill(building_planer_rends->begin(), building_planer_rends->end(), nullptr);
    }
    (*building_planer_rends)[e] = &p;
}

void building_planer_renderer::ghost_blocked(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel, bool fully_blocked) const {
    for (int row = 0; row < planer.size.y; row++) {
        for (int column = 0; column < planer.size.x; column++) {
            vec2i current_coord = planer.pixel_coord_offset(row, column);
            color color_mask = (planer.is_blocked_tile(row, column) || fully_blocked) ? COLOR_MASK_RED_30 : COLOR_MASK_GREEN_30;
            planer.draw_flat_tile(current_coord, color_mask, ctx);
        }
    }
}

void building_planer_renderer::ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const {
    planer.draw_tile_graphics_array(ctx, start, end, pixel);
}

int building_planer_renderer::construction_place(build_planner &planer, tile2i start, tile2i end, int orientation, int variant) const {
    // by default, get size from building's properties
    const auto &params = building_static_params::get(planer.build_type);
    verify_no_crash(params.building_size > 0);

    // correct building placement for city orientations
    switch (city_view_orientation()) {
    case DIR_2_BOTTOM_RIGHT:
        end = end.shifted(-params.building_size + 1, 0);
        break;

    case DIR_4_BOTTOM_LEFT:
        end = end.shifted(-params.building_size + 1, -params.building_size + 1);
        break;

    case DIR_6_TOP_LEFT:
        end = end.shifted(0, -params.building_size + 1);
        break;
    }

    // create building
    planer.last_created_building = nullptr;
    building *b = building_create(planer.build_type, end, orientation);
    game_undo_add_building(b);
    if (b->id <= 0) { // building creation failed????
        return 0;
    }

    add_building(b, orientation, variant);
    planer.last_created_building = b;

    return 1;
}

int building_planer_renderer::update_building_variant(build_planner &planer) const {
    return planer.building_variant;
}

int building_planer_renderer::construction_update(build_planner &planer, tile2i start, tile2i end) const {
    int special_flags = planer.special_flags;
    if ((special_flags & e_building_flag::Meadow) || (special_flags & e_building_flag::Rock)
        || (special_flags & e_building_flag::Trees) || (special_flags & e_building_flag::NearbyWater)
        || (special_flags & e_building_flag::Walls) || (special_flags & e_building_flag::Groundwater)
        || (special_flags & e_building_flag::Water) || (special_flags & e_building_flag::ShoreLine)
        || (special_flags & e_building_flag::Road) || (special_flags & e_building_flag::Intersection)) {
        return 0;
    }

    int real_orientation = (city_view_orientation() / 2) % 2;
    if (real_orientation == 0) {
        planer.mark_construction(planer.north_tile, planer.size, TERRAIN_ALL, true);
    } else {
        planer.mark_construction(planer.north_tile, planer.size, TERRAIN_ALL, true);
    }

    return 0;
}


void building_planer_renderer::setup_preview_graphics(build_planner &planer) const {
    const auto &params = building_static_params::get(planer.build_type);
    int img_id = params.base_img();
    if (!img_id) {
        img_id = params.first_img(animkeys().preview);
    }
    img_id += params.planner_update_rule.relative_orientation * planer.relative_orientation;
    planer.set_tiles_building(img_id, params.building_size);
}

const building_planer_renderer &building_planer_renderer::get(e_building_type e) {
    auto p = building_planer_rends->at(e);
    return (p == nullptr) ? building_planer_renderer::dummy : *p;
}
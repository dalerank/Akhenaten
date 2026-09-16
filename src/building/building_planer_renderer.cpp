#include "building_planer_renderer.h"

#include "building_static_params.h"
#include "building/construction/build_planner.h"
#include "grid/water.h"
#include "city/city_buildings.h"
#include "building/building.h"
#include "game/undo.h"
#include "grid/figure.h"
#include "graphics/graphics.h"
#include "js/js_game.h"
#include "js/js_struct.h"

struct ghost_preview_ev {
    tile2i start;
    tile2i end;
    vec2i pixel;
    bool in_progress;
};
ANK_REGISTER_STRUCT_WRITER(ghost_preview_ev, start, end, pixel, in_progress)

struct construction_update_ev {
    int start_x, start_y, end_x, end_y;
};
ANK_REGISTER_STRUCT_WRITER(construction_update_ev, start_x, start_y, end_x, end_y)

struct finalize_check_ev {
    tile2i start;
    tile2i end;
    int state;
};
ANK_REGISTER_STRUCT_WRITER(finalize_check_ev, start, end, state)

struct building_variant_ev {
    int type;
    tile2i tile;
    int variant;
    int global_orientation;
};
ANK_REGISTER_STRUCT_WRITER(building_variant_ev, type, tile, variant, global_orientation)

struct need_flag_ev {
    int flag;
    bool result;
};
ANK_REGISTER_STRUCT_WRITER(need_flag_ev, flag, result)

struct construction_start_ev {
    tile2i start;
};
ANK_REGISTER_STRUCT_WRITER(construction_start_ev, start)

struct ghost_allow_tile_ev {
    tile2i tile;
    bool in_progress;
};
ANK_REGISTER_STRUCT_WRITER(ghost_allow_tile_ev, tile, in_progress)

static std::array<const building_planer_renderer *, BUILDING_MAX> *building_planer_rends = nullptr;

bool building_planer_renderer::is_need_flag(build_planner &planer, e_building_need_rules flag) const {
    const auto &params = building_static_params::get(planer.build_type);
    const auto &needs = params.needs;
    bool result = false;
    switch (flag) {
    case PLANNER_RULE_MEADOW: result = needs.meadow; break;
    case PLANNER_RULE_ROCK: result = needs.rock; break;
    case PLANNER_RULE_ORE: result = needs.ore; break;
    case PLANNER_RULE_TEMPLE_UPGRADE_ALTAR: result = needs.altar; break;
    case PLANNER_RULE_TEMPLE_UPGRADE_ORACLE: result = needs.oracle; break;
    case PLANNER_RULE_NEARBY_WATER: result = needs.nearby_water; break;
    case PLANNER_RULE_GROUNDWATER: result = needs.groundwater; break;
    case PLANNER_RULE_SHORELINE: result = needs.shoreline; break;
    case PLANNER_RULE_CANALS: result = needs.canals; break;
    case PLANNER_RULE_FLOODPLAIN_SHORE: result = needs.floodplain_shoreline; break;
    }

    const xstring event_name = js_helpers::es_hash_str(params.name, __func__).c_str();
    if (js_has_event_handlers(event_name)) {
        planer.need_flag_result = result;
        es_t(need_flag_ev{ (int)flag, result }, params.name, __func__);
        return planer.need_flag_result != 0;
    }

    return result;
}

bool building_planer_renderer::ghost_allow_tile(build_planner &p, tile2i tile) const {
    bool result = !map_has_figure_at(tile);
    const auto &params = building_static_params::get(p.build_type);
    const xstring event_name = js_helpers::es_hash_str(params.name, __func__).c_str();
    if (js_has_event_handlers(event_name)) {
        p.preview_allow_result = result ? 1 : 0;
        es_t(ghost_allow_tile_ev{ tile, p.in_progress }, params.name, __func__);
        return p.preview_allow_result != 0;
    }

    return result;
}

bool building_planer_renderer::can_construction_start(build_planner &p, tile2i start) const {
    const auto &params = building_static_params::get(p.build_type);
    const xstring event_name = js_helpers::es_hash_str(params.name, __func__).c_str();
    if (js_has_event_handlers(event_name)) {
        p.preview_allow_result = 1;
        es_t(construction_start_ev{ start }, params.name, __func__);
        return p.preview_allow_result != 0;
    }

    return true;
}

const building_planer_renderer building_planer_renderer::dummy;

void building_planer_renderer::register_model(e_building_type e, const building_planer_renderer &p) {
    if (!building_planer_rends) {
        building_planer_rends = new std::array<const building_planer_renderer *, BUILDING_MAX>();
        std::fill(building_planer_rends->begin(), building_planer_rends->end(), nullptr);
    }
    (*building_planer_rends)[e] = &p;
}

void building_planer_renderer::unregister_model(e_building_type e) {
    if (building_planer_rends && e > BUILDING_NONE && e < BUILDING_MAX) {
        (*building_planer_rends)[e] = nullptr;
    }
}

void building_planer_renderer::ghost_blocked(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel, bool fully_blocked) const {
    const auto &params = building_static_params::get(planer.build_type);
    const xstring event_name = js_helpers::es_hash_str(params.name, __func__).c_str();
    if (js_has_event_handlers(event_name)) {
        es_t(ghost_preview_ev{ start, end, pixel, planer.in_progress }, params.name, __func__);
        return;
    }

    for (int row = 0; row < planer.size.y; row++) {
        for (int column = 0; column < planer.size.x; column++) {
            vec2i current_coord = planer.pixel_coord_offset(row, column);
            color color_mask = (planer.is_blocked_tile(row, column) || fully_blocked) ? COLOR_MASK_RED_30 : COLOR_MASK_GREEN_30;
            planer.draw_flat_tile(current_coord, color_mask, ctx);
        }
    }
}

void building_planer_renderer::ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const {
    const auto &params = building_static_params::get(planer.build_type);
    const xstring event_name = js_helpers::es_hash_str(params.name, __func__).c_str();
    if (js_has_event_handlers(event_name)) {
        es_t(ghost_preview_ev{ start, end, pixel, planer.in_progress }, params.name, __func__);
        return;
    }

    planer.draw_tile_graphics_array(ctx, start, end, pixel);
}

int building_planer_renderer::can_place(build_planner &planer, tile2i start, tile2i end, int state) const {
    const auto &params = building_static_params::get(planer.build_type);
    const xstring event_name = js_helpers::es_hash_str(params.name, __func__).c_str();
    if (js_has_event_handlers(event_name)) {
        planer.finalize_check_result = state;
        es_t(finalize_check_ev{ start, end, state }, params.name, __func__);
        return planer.finalize_check_result;
    }

    return state;
}

int building_planer_renderer::finalize_check(build_planner &planer, tile2i start, tile2i end, int state) const {
    const auto &params = building_static_params::get(planer.build_type);
    const xstring event_name = js_helpers::es_hash_str(params.name, __func__).c_str();
    if (js_has_event_handlers(event_name)) {
        planer.finalize_check_result = state;
        es_t(finalize_check_ev{ start, end, state }, params.name, __func__);
        return planer.finalize_check_result;
    }

    return state;
}

int building_planer_renderer::construction_place(build_planner &planer, tile2i start, tile2i end, int orientation, int variant) const {
    const auto &params = building_static_params::get(planer.build_type);
    const xstring place_event = js_helpers::es_hash_str(params.name, __func__).c_str();
    if (js_has_event_handlers(place_event)) {
        planer.construction_update_items = 0;
        es_t(construction_update_ev{ start.x(), start.y(), end.x(), end.y() }, params.name, __func__);
        return planer.construction_update_items;
    }

    // by default, get size from building's properties
    verify_no_crash(params.building_size > 0);

    // correct building placement for city orientations
    switch (g_camera.orientation) {
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
    const auto &params = building_static_params::get(planer.build_type);

    es_t(building_variant_ev{ planer.build_type, planer.end, planer.custom_building_variant, planer.relative_orientation }, params.name, __func__);
    return planer.building_variant;
}

int building_planer_renderer::construction_update(build_planner &planer, tile2i start, tile2i end) const {
    const auto &params = building_static_params::get(planer.build_type);
    const xstring event_name = js_helpers::es_hash_str(params.name, __func__).c_str();
    if (js_has_event_handlers(event_name)) {
        planer.construction_update_items = 0;
        es_t(construction_update_ev{ start.x(), start.y(), end.x(), end.y() }, params.name, __func__);
        return planer.construction_update_items;
    }

    if (planer.needShoreLine()) {
        planer.draw_as_constructing = map_shore_determine_orientation(end, params.building_size, true).match;
        return 1;
    }

    if (planer.needMeadow() || planer.needRock()
        || planer.needTrees() || planer.needNearbyWater()
        || planer.needWalls() || planer.needGroundwater()
        || planer.needWater()
        || planer.needRoad() || planer.needIntersection()) {
        return 0;
    }

    int real_orientation = (g_camera.orientation / 2) % 2;
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

    es_t(ghost_preview_ev{ planer.start, planer.end, g_camera.lookup_tile_to_pixel(planer.end), planer.in_progress }, params.name, __func__);
}

int building_planer_renderer::setup_building_variant(e_building_type type, tile2i tile, int variant) const {
    const auto &params = building_static_params::get(type);

    g_city_planner.custom_building_variant = variant;
    es_t(building_variant_ev{ type, tile, variant, g_city_planner.relative_orientation }, params.name, __func__);
    return g_city_planner.custom_building_variant;
}

int building_planer_renderer::next_building_variant(e_building_type type, tile2i tile, int variant) const {
    const auto &params = building_static_params::get(type);

    g_city_planner.custom_building_variant = (variant + 1) % 4;
    es_t(building_variant_ev{ type, tile, variant, g_city_planner.relative_orientation }, params.name, __func__);
    return g_city_planner.custom_building_variant;
}

int building_planer_renderer::update_relative_orientation(build_planner &planer, tile2i tile, int global_orientation) const {
    const auto &params = building_static_params::get(planer.build_type);

    planer.relative_orientation = global_orientation;
    es_t(building_variant_ev{ planer.build_type, tile, planer.custom_building_variant, global_orientation }, params.name, __func__);
    return planer.relative_orientation;
}

const building_planer_renderer &building_planer_renderer::get(e_building_type e) {
    auto p = building_planer_rends->at(e);
    return (p == nullptr) ? building_planer_renderer::dummy : *p;
}

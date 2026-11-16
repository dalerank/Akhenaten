#include "monument_abu_simbel.h"

#include "building/monuments.h"
#include "building/rotation.h"
#include "city/city.h"
#include "city/city_message.h"
#include "city/city_warnings.h"
#include "construction/build_planner.h"
#include "core/direction.h"
#include "figure/figure.h"
#include "game/undo.h"
#include "graphics/color.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/view/lookup.h"
#include "graphics/view/view.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/image.h"
#include "grid/property.h"
#include "grid/road_access.h"
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "js/js_game.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_abu_simbel);

static monument g_monument_abu_simbel{BUILDING_ABU_SIMBEL};

static constexpr uint32_t k_cliff_terrain = TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP;

struct abu_part_def {
    building_abu_simbel::part_variant variant;
    int ox; // NW in rot0 footprint
    int oy;
    int size;
    bool needs_cliff;
};

// Rot0 / Heaven 9×21: façade along +Y; near-cliffs at X3 form the side-wall lips.
// Center column Y9–11: midcut_back (X0) + midcut_depth (X3) + midcut_front (X6).
static const abu_part_def k_parts[building_abu_simbel::PART_COUNT] = {
    {building_abu_simbel::PART_CLIFF_L_FAR, 0, 0, 3, true},
    {building_abu_simbel::PART_CLIFF_L_NEAR, 3, 0, 3, true},
    {building_abu_simbel::PART_STATUE_L, 0, 3, 6, true},
    {building_abu_simbel::PART_MIDCUT_BACK, 0, 9, 3, true},
    {building_abu_simbel::PART_MIDCUT_DEPTH, 3, 9, 3, true},
    {building_abu_simbel::PART_MIDCUT_FRONT, 6, 9, 3, false},
    {building_abu_simbel::PART_STATUE_R, 0, 12, 6, true},
    {building_abu_simbel::PART_CLIFF_R_FAR, 0, 18, 3, true},
    {building_abu_simbel::PART_CLIFF_R_NEAR, 3, 18, 3, true},
};

void building_abu_simbel::static_params::rebuild_construction() {
    monument &m = g_monument_abu_simbel;
    m.btype = BUILDING_ABU_SIMBEL;
    m.phases.clear();

    const int stages = art_stages > 0 ? art_stages : 10;
    for (int i = 0; i < stages; ++i) {
        const uint16_t timber = (i < (int)timber_loads.size()) ? timber_loads[i] : 0;
        if (timber > 0) {
            m.phases.push_back({(uint8_t)i, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, timber}});
        } else {
            m.phases.push_back({(uint8_t)i, monument_phase_resource{ARCHITECTS, 1}});
        }
    }
    m.phases.push_back({(uint8_t)stages, monument_phase_resource{RESOURCE_NONE, 0}});
}

void building_abu_simbel::static_params::archive_load(archive /*arch*/) {
    rebuild_construction();
}

const monument &building_abu_simbel::config() const {
    return g_monument_abu_simbel;
}

static vec2i abu_oriented_wh(vec2i size, int rotation) {
    if (size.x <= 0 || size.y <= 0) {
        size = {9, 21};
    }
    rotation %= 4;
    if (rotation == 1 || rotation == 3) {
        return {size.y, size.x};
    }
    return size;
}

static vec2i abu_rotate_part_nw(int ox, int oy, int part_size, int rotation, int w, int h) {
    rotation %= 4;
    if (rotation < 0) {
        rotation += 4;
    }
    switch (rotation) {
    case 1:
        return {h - oy - part_size, ox};
    case 2:
        return {w - ox - part_size, h - oy - part_size};
    case 3:
        return {oy, w - ox - part_size};
    default:
        return {ox, oy};
    }
}

static vec2i abu_footprint(int rotation) {
    const auto &bp = building_abu_simbel::current_params();
    vec2i init = bp.init_tiles;
    if (init.x <= 0 || init.y <= 0) {
        init = {9, 21};
    }
    return abu_oriented_wh(init, rotation);
}

static tile2i abu_part_tile(tile2i origin, const abu_part_def &def, int rotation) {
    const auto &bp = building_abu_simbel::current_params();
    vec2i init = bp.init_tiles.x > 0 ? bp.init_tiles : vec2i{9, 21};
    const vec2i nw = abu_rotate_part_nw(def.ox, def.oy, def.size, rotation, init.x, init.y);
    return origin.shifted(nw.x, nw.y);
}

static bool abu_tile_is_cliff(tile2i t) {
    return map_terrain_is(t, k_cliff_terrain);
}

static bool abu_area_ok(tile2i origin, const abu_part_def &def, int rotation, bool *missing_cliff, bool *bad_clear) {
    tile2i t0 = abu_part_tile(origin, def, rotation);
    for (int dy = 0; dy < def.size; dy++) {
        for (int dx = 0; dx < def.size; dx++) {
            tile2i t = t0.shifted(dx, dy);
            if (!map_grid_is_inside(t, 1)) {
                if (def.needs_cliff) {
                    *missing_cliff = true;
                } else {
                    *bad_clear = true;
                }
                continue;
            }
            if (def.needs_cliff) {
                if (!abu_tile_is_cliff(t) || map_terrain_is(t, TERRAIN_NOT_CLEAR & ~k_cliff_terrain)) {
                    *missing_cliff = true;
                }
            } else if (map_terrain_is(t, TERRAIN_NOT_CLEAR)) {
                *bad_clear = true;
            }
            if (map_has_figure_at(t)) {
                if (def.needs_cliff) {
                    *missing_cliff = true;
                } else {
                    *bad_clear = true;
                }
            }
        }
    }
    return !(*missing_cliff) && !(*bad_clear);
}

static int abu_validate_site(tile2i origin, int rotation, xstring *warning_out) {
    bool missing_cliff = false;
    bool bad_clear = false;
    for (const auto &def : k_parts) {
        abu_area_ok(origin, def, rotation, &missing_cliff, &bad_clear);
    }
    if (missing_cliff) {
        if (warning_out) {
            *warning_out = "#must_be_over_cliffs";
        }
        return CAN_NOT_PLACE;
    }
    if (bad_clear) {
        if (warning_out) {
            *warning_out = "#entrance_on_clear_land";
        }
        return CAN_NOT_PLACE;
    }
    return CAN_PLACE;
}

static const abu_part_def *abu_def_for(int variant) {
    for (const auto &def : k_parts) {
        if ((int)def.variant == variant) {
            return &def;
        }
    }
    return &k_parts[0];
}

static bool abu_local_in_part(int dx, int dy, const abu_part_def &def, int rotation, int w0, int h0) {
    const vec2i nw = abu_rotate_part_nw(def.ox, def.oy, def.size, rotation, w0, h0);
    return dx >= nw.x && dy >= nw.y && dx < nw.x + def.size && dy < nw.y + def.size;
}

static const abu_part_def *abu_part_at_local(int dx, int dy, int rotation) {
    const auto &bp = building_abu_simbel::current_params();
    const vec2i init = bp.init_tiles.x > 0 ? bp.init_tiles : vec2i{9, 21};
    for (const auto &def : k_parts) {
        if (abu_local_in_part(dx, dy, def, rotation, init.x, init.y)) {
            return &def;
        }
    }
    return nullptr;
}

bool building_abu_simbel::has_abu_simbel_on_map() {
    for (building *b = building_begin(); b != building_end(); ++b) {
        if (b && b->is_valid() && b->type == BUILDING_ABU_SIMBEL) {
            return true;
        }
    }
    return false;
}

vec2i building_abu_simbel::footprint_size() const {
    return abu_footprint(base.orientation % 4);
}

int building_abu_simbel::part_size() const {
    return abu_def_for(runtime_data().variant)->size;
}

bool building_abu_simbel::part_needs_cliff() const {
    return abu_def_for(runtime_data().variant)->needs_cliff;
}

int building_abu_simbel::art_stage() const {
    const auto &bp = current_params();
    const int max_stage = bp.art_stages > 0 ? bp.art_stages : 10;
    const int p = runtime_data().phase;
    if (p == MONUMENT_FINISHED || p >= max_stage) {
        return max_stage;
    }
    if (p < 1) {
        return 1;
    }
    return std::min(p + 1, max_stage);
}

int building_abu_simbel::art_orient_pair() const {
    return (g_camera.orientation / 2) % 2;
}

bool building_abu_simbel::needs_resources() const {
    if (is_finished()) {
        return false;
    }
    auto &d = runtime_data();
    for (e_resource r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
        if (needs_resource(r) <= 0) {
            continue;
        }
        if (d.resources_pct[r] < 100) {
            return true;
        }
    }
    return false;
}

bool building_abu_simbel::need_carpenter_phase() const {
    return !is_finished() && needs_resource(RESOURCE_TIMBER) > 0;
}

bool building_abu_simbel::has_stonemason_worker() const {
    for (auto wid : runtime_data().workers) {
        figure *f = wid > 0 ? figure_get(wid) : nullptr;
        if (f && f->is_alive() && f->type == FIGURE_STONEMASON) {
            return true;
        }
    }
    return false;
}

bool building_abu_simbel::has_carpenter_worker() const {
    for (auto wid : runtime_data().workers) {
        figure *f = wid > 0 ? figure_get(wid) : nullptr;
        if (f && f->is_alive() && f->type == FIGURE_CARPENTER) {
            return true;
        }
    }
    return false;
}

bool building_abu_simbel::need_stonemason() {
    if (!is_main() || is_finished() || need_carpenter_phase()) {
        return false;
    }
    if (!need_workers()) {
        return false;
    }
    return !has_stonemason_worker();
}

bool building_abu_simbel::need_workers() const {
    if (!is_main() || is_finished()) {
        return false;
    }
    for (auto wid : runtime_data().workers) {
        if (!wid) {
            return true;
        }
        figure *f = figure_get(wid);
        if (!f || !f->is_alive()) {
            return true;
        }
    }
    return false;
}

void building_abu_simbel::add_workers(figure_id fid) {
    if (!is_main()) {
        return;
    }
    auto &d = runtime_data();
    for (auto &wid : d.workers) {
        if (wid == 0) {
            wid = fid;
            return;
        }
        figure *f = figure_get(wid);
        if (!f || !f->is_alive()) {
            wid = fid;
            return;
        }
    }
}

void building_abu_simbel::remove_worker(figure_id fid) {
    auto &d = runtime_data();
    for (auto &wid : d.workers) {
        if (wid == fid) {
            wid = 0;
            return;
        }
    }
}

int building_abu_simbel::building_image_get() const {
    const auto &params = current_params();
    const int part = runtime_data().variant;
    const int stage = art_stage();
    const int cam = art_orient_pair();

    auto first = [&](const char *key) { return params.first_img(key); };

    switch (part) {
    case PART_CLIFF_L_FAR:
        return first("cliff_l_far");
    case PART_CLIFF_L_NEAR:
        return first("cliff_l_near");
    case PART_CLIFF_R_FAR:
        return first("cliff_r_far");
    case PART_CLIFF_R_NEAR:
        return first("cliff_r_near");
    case PART_MIDCUT_BACK:
    case PART_MIDCUT_DEPTH: {
        const int base_img = first("midcut_back");
        if (base_img <= 0) {
            return 0;
        }
        const int mid_progress = std::min(std::max(stage - 1, 0), 6);
        return base_img + mid_progress * 2 + cam;
    }
    case PART_MIDCUT_FRONT: {
        const int base_img = first("midcut_front");
        if (base_img <= 0) {
            return 0;
        }
        const int mid_progress = std::min(std::max(stage - 1, 0), 6);
        return base_img + mid_progress * 2 + cam;
    }
    case PART_STATUE_L:
    case PART_STATUE_R: {
        bstring32 key;
        if (is_finished()) {
            key.printf("finish%d", cam + 1);
        } else {
            key.printf("s%c%d", 'a' + (stage - 1), cam + 1);
        }
        int img = first(key.c_str());
        if (img > 0) {
            return img;
        }
        img = first("preview");
        return img > 0 ? img : first("sa1");
    }
    default:
        return first("preview");
    }
}

void building_abu_simbel::refresh_part_tiles() {
    const int size = part_size();
    const int img = building_image_get();
    if (size > 0 && img > 0) {
        map_building_tiles_add(id(), tile(), size, img, TERRAIN_BUILDING);
    }
}

bool building_abu_simbel::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    // Height pass uses the camera draw-tile, not necessarily NW.
    if (!map_property_is_draw_tile(tile.grid_offset())) {
        return false;
    }

    const int part = runtime_data().variant;
    const bool is_statue = (part == PART_STATUE_L || part == PART_STATUE_R);
    const bool is_front = (part == PART_MIDCUT_FRONT);
    if (!is_statue && !is_front) {
        return false;
    }

    const auto &params = current_params();
    const int stage = art_stage();

    auto draw_layer = [&](int image_id, vec2i pixel) {
        if (image_id <= 0) {
            return;
        }
        const image_t *img = image_get(image_id);
        if (!img) {
            return;
        }
        const auto rtype = (img->isometric_top_height > 0) ? render_command_t::ert_drawtile_full
                                                           : render_command_t::ert_drawtile;
        auto &command = ImageDraw::create_command(ctx, rtype);
        command.image_id = image_id;
        command.pixel = pixel;
        command.mask = color_mask;
    };

    if (is_statue && !is_finished() && stage >= 2 && stage <= 8) {
        const char *scaffold_keys[] = {"scaffold_a", "scaffold_b", "scaffold_c", "scaffold_d"};
        const int n_scaf = (stage <= 4) ? 2 : 4;
        for (int i = 0; i < n_scaf; ++i) {
            const int scaf = params.first_img(scaffold_keys[i]);
            if (scaf > 0) {
                draw_layer(scaf, point + vec2i{8 + i * 12, -48});
            }
        }
    }

    if (is_front) {
        const int stairs_base = params.first_img("stairs");
        if (stairs_base > 0) {
            const int stairs_off = is_finished() ? 5 : std::min(std::max(stage - 1, 0), 5);
            draw_layer(stairs_base + stairs_off, point);
        }
    }

    return true;
}

void building_abu_simbel::preview::setup_preview_graphics(build_planner &planer) const {
    const int rot = building_rotation_global_rotation() % 4;
    const vec2i ft = abu_footprint(rot);
    planer.init_tiles(ft.x, ft.y);
}

uint32_t building_abu_simbel::preview::ghost_ignore_terrain(build_planner &p, tile2i tile) const {
    const int rot = building_rotation_global_rotation() % 4;
    const vec2i ft = abu_footprint(rot);
    const int dx = tile.x() - p.end.x();
    const int dy = tile.y() - p.end.y();
    if (dx < 0 || dy < 0 || dx >= ft.x || dy >= ft.y) {
        return 0;
    }
    const abu_part_def *def = abu_part_at_local(dx, dy, rot);
    if (!def) {
        // Niche gap / unused AABB pads — ignore all so they do not block place.
        return TERRAIN_NOT_CLEAR;
    }
    if (def->needs_cliff) {
        return k_cliff_terrain;
    }
    return 0;
}

bool building_abu_simbel::preview::ghost_allow_tile(build_planner &p, tile2i tile) const {
    const int rot = building_rotation_global_rotation() % 4;
    const vec2i ft = abu_footprint(rot);
    const int dx = tile.x() - p.end.x();
    const int dy = tile.y() - p.end.y();
    if (dx >= 0 && dy >= 0 && dx < ft.x && dy < ft.y && !abu_part_at_local(dx, dy, rot)) {
        return true;
    }
    return building_planer_renderer::ghost_allow_tile(p, tile);
}

int building_abu_simbel::preview::construction_place(build_planner &planer, tile2i /*tile*/, tile2i end, int orientation,
                                                     int variant) const {
    // Default construction_place shifts by building_size (3); use full footprint AABB.
    const int rot = building_rotation_global_rotation() % 4;
    const vec2i ft = abu_footprint(rot);
    switch (g_camera.orientation) {
    case DIR_2_BOTTOM_RIGHT:
        end = end.shifted(-ft.x + 1, 0);
        break;
    case DIR_4_BOTTOM_LEFT:
        end = end.shifted(-ft.x + 1, -ft.y + 1);
        break;
    case DIR_6_TOP_LEFT:
        end = end.shifted(0, -ft.y + 1);
        break;
    default:
        break;
    }

    planer.last_created_building = nullptr;
    building *b = building_create(planer.build_type, end, orientation);
    game_undo_add_building(b);
    if (!b || b->id <= 0) {
        return 0;
    }

    add_building(b, orientation, variant);
    // Tear-down in on_place_update_tiles leaves DELETED — treat as failed place.
    if (b->state == BUILDING_STATE_DELETED_BY_GAME) {
        planer.last_created_building = nullptr;
        return 0;
    }

    planer.last_created_building = b;
    return 1;
}

int building_abu_simbel::preview::can_place(build_planner &p, tile2i /*tile*/, tile2i end, int state) const {
    if (state != CAN_PLACE && state != CAN_NOT_BUT_GREEN) {
        return state;
    }
    if (has_abu_simbel_on_map()) {
        p.set_warning("#only_one_building_of_this_type");
        return CAN_NOT_PLACE;
    }
    const int rot = building_rotation_global_rotation() % 4;
    xstring warn;
    const int cliff_state = abu_validate_site(end, rot, &warn);
    if (cliff_state != CAN_PLACE) {
        if (!warn.empty()) {
            p.set_warning(warn);
        }
        return CAN_NOT_PLACE;
    }
    if (state == CAN_NOT_BUT_GREEN) {
        return state;
    }
    return CAN_PLACE;
}

int building_abu_simbel::preview::finalize_check(build_planner &p, tile2i tile, tile2i end, int state) const {
    state = building_planer_renderer::finalize_check(p, tile, end, state);
    if (state != CAN_PLACE) {
        return state;
    }
    if (has_abu_simbel_on_map()) {
        p.set_warning("#only_one_building_of_this_type");
        g_warning_manager.show("#only_one_building_of_this_type");
        return CAN_NOT_PLACE;
    }
    const int rot = building_rotation_global_rotation() % 4;
    xstring warn;
    const int cliff_state = abu_validate_site(end, rot, &warn);
    if (cliff_state != CAN_PLACE) {
        if (!warn.empty()) {
            p.set_warning(warn);
            g_warning_manager.show(warn.c_str());
        }
        return CAN_NOT_PLACE;
    }
    return CAN_PLACE;
}

void building_abu_simbel::preview::ghost_preview(build_planner &planer, painter &ctx, tile2i /*start*/, tile2i end,
                                                 vec2i /*pixel*/) const {
    const auto &params = building_static_params::get(planer.build_type);
    const int rot = building_rotation_global_rotation() % 4;
    const vec2i ft = abu_footprint(rot);

    const bool force_red = has_abu_simbel_on_map();
    xstring warn;
    const bool site_bad = force_red || abu_validate_site(end, rot, &warn) != CAN_PLACE;

    if (site_bad) {
        for (int dy = 0; dy < ft.y; dy++) {
            for (int dx = 0; dx < ft.x; dx++) {
                if (!abu_part_at_local(dx, dy, rot)) {
                    continue;
                }
                tile2i t = end.shifted(dx, dy);
                vec2i px = g_camera.lookup_tile_to_pixel(t);
                build_planner::draw_flat_tile(ctx, px, COLOR_MASK_RED_30);
            }
        }
        return;
    }

    for (const auto &def : k_parts) {
        tile2i t0 = abu_part_tile(end, def, rot);
        int img = 0;
        switch (def.variant) {
        case PART_CLIFF_L_FAR:
            img = params.first_img("cliff_l_far");
            break;
        case PART_CLIFF_L_NEAR:
            img = params.first_img("cliff_l_near");
            break;
        case PART_CLIFF_R_FAR:
            img = params.first_img("cliff_r_far");
            break;
        case PART_CLIFF_R_NEAR:
            img = params.first_img("cliff_r_near");
            break;
        case PART_MIDCUT_BACK:
        case PART_MIDCUT_DEPTH:
            img = params.first_img("midcut_back");
            break;
        case PART_MIDCUT_FRONT:
            img = params.first_img("midcut_front");
            break;
        case PART_STATUE_L:
        case PART_STATUE_R:
            img = params.first_img("sa1");
            break;
        default:
            break;
        }
        if (img <= 0) {
            img = params.first_img("preview");
        }
        planer.draw_building_ghost(ctx, img, g_camera.lookup_tile_to_pixel(t0));
    }
}

void building_abu_simbel::on_place_update_tiles(int /*orientation*/, int /*variant*/) {
    // Linked parts are created with building_create (no add_building) — only the
    // planner main should spawn the chain.
    if (base.prev_part_building_id > 0 || runtime_data().variant != 0) {
        refresh_part_tiles();
        return;
    }

    base.prev_part_building_id = 0;
    runtime_data().variant = PART_CLIFF_L_FAR;
    const int rotation = building_rotation_global_rotation() % 4;
    base.orientation = (uint8_t)rotation;
    base.size = (uint8_t)k_parts[0].size;

    refresh_part_tiles();
    map_monuments_set_progress(tile(), 0);

    building *prev = &base;
    for (int i = 1; i < PART_COUNT; ++i) {
        const abu_part_def &def = k_parts[i];
        tile2i part_tile = abu_part_tile(tile(), def, rotation);
        building *part = building_create(BUILDING_ABU_SIMBEL, part_tile, 0);
        if (!part || part->id <= 0) {
            // Tear down everything claimed so far.
            for (building *p = &base; p;) {
                building *n = p->has_next() ? p->next() : nullptr;
                map_building_tiles_remove(p->id, p->tile);
                p->state = BUILDING_STATE_DELETED_BY_GAME;
                p = n;
            }
            return;
        }
        game_undo_add_building(part);

        auto *ap = part->dcast_abu_simbel();
        if (ap) {
            ap->runtime_data().variant = def.variant;
            ap->runtime_data().phase = runtime_data().phase;
            part->orientation = (uint8_t)rotation;
            part->size = (uint8_t)def.size;
            ap->refresh_part_tiles();
        }

        part->prev_part_building_id = prev->id;
        prev->next_part_building_id = part->id;
        part->next_part_building_id = 0;
        prev = part;

        for (int dy = 0; dy < def.size; dy++) {
            for (int dx = 0; dx < def.size; dx++) {
                map_monuments_set_progress(part_tile.shifted(dx, dy), 0);
            }
        }
    }
}

xstring building_abu_simbel::demolish_blocked_message() const {
    return "#abu_simbel_not_demolishable";
}

void building_abu_simbel::on_phase_changed(int /*old_phase*/, int current) {
    refresh_part_tiles();

    if (current != MONUMENT_FINISHED) {
        auto &d = runtime_data();
        for (e_resource resource = RESOURCE_NONE; resource < RESOURCES_MAX; ++resource) {
            d.resources_pct[resource] = 0;
        }
    }
}

void building_abu_simbel::update_day() {
    building_impl::update_day();
    if (!is_main() || is_finished()) {
        return;
    }
    for (auto &wid : runtime_data().workers) {
        if (!wid) {
            continue;
        }
        figure *f = figure_get(wid);
        if (!f || !f->is_alive()) {
            wid = 0;
        }
    }
    if (need_carpenter_phase()) {
        if (!has_carpenter_worker()) {
            return;
        }
    } else if (!has_stonemason_worker()) {
        return;
    }
    progress();
}

void building_abu_simbel::update_map_orientation(int /*map_orientation*/) {
    refresh_part_tiles();
}

tile2i building_abu_simbel::center_point() const {
    building *m = base.main();
    const vec2i ft = m->dcast_abu_simbel() ? m->dcast_abu_simbel()->footprint_size() : vec2i{9, 21};
    return m->tile.shifted(ft.x / 2, ft.y / 2);
}

tile2i building_abu_simbel::access_point() const {
    building *m = base.main();
    const int rot = m->orientation % 4;
    return abu_part_tile(m->tile, k_parts[PART_MIDCUT_FRONT], rot).shifted(1, 1);
}

grid_area building_abu_simbel::get_area() const {
    building *m = base.main();
    tile2i start = m->tile;
    tile2i end = start.shifted(m->size - 1, m->size - 1);
    for (building *p = m; p; p = p->has_next() ? p->next() : nullptr) {
        const int sz = p->size > 0 ? p->size : 3;
        tile2i pmin = p->tile;
        tile2i pmax = p->tile.shifted(sz - 1, sz - 1);
        if (pmin.x() < start.x()) {
            start = tile2i(pmin.x(), start.y());
        }
        if (pmin.y() < start.y()) {
            start = tile2i(start.x(), pmin.y());
        }
        if (pmax.x() > end.x()) {
            end = tile2i(pmax.x(), end.y());
        }
        if (pmax.y() > end.y()) {
            end = tile2i(end.x(), pmax.y());
        }
    }
    return {start, end};
}

void building_abu_simbel::bind_dynamic(io_buffer *iob, size_t /*version*/) {
    auto &monumentd = runtime_data();

    iob->bind____skip(38);
    iob->bind(BIND_SIGNATURE_UINT8, &base.orientation);
    for (int i = 0; i < 5; i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &monumentd.workers[i]);
    }
    iob->bind(BIND_SIGNATURE_UINT8, &monumentd.phase);
    iob->bind(BIND_SIGNATURE_UINT8, &monumentd.funeral_done);
    iob->bind(BIND_SIGNATURE_UINT8, &monumentd.preexisting);
    iob->bind(BIND_SIGNATURE_UINT8, &monumentd.variant);

    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &monumentd.resources_pct[i]);
    }
}

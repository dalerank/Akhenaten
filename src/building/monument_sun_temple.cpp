#include "monument_sun_temple.h"

#include "building/monuments.h"
#include "building/rotation.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "city/city_message.h"
#include "city/city_resource.h"
#include "city/city_warnings.h"
#include "construction/build_planner.h"
#include "figure/figure.h"
#include "game/game_events.h"
#include "game/resource.h"
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
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "js/js_game.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_sun_temple);

static monument g_monument_sun_temple{BUILDING_SUN_TEMPLE};

namespace {

const building_sun_temple::base_params &st_params() {
    return (const building_sun_temple::base_params &)building_sun_temple::current_params();
}

vec2i part_offset(const svector<vec2i, 4> &offsets, int rotation, vec2i fallback) {
    if (offsets.size() >= 4) {
        return offsets[rotation % 4];
    }
    return fallback;
}

vec2i oriented_wh(vec2i size, int rotation) {
    if (size.x <= 0 || size.y <= 0) {
        return size;
    }
    rotation %= 4;
    if (rotation == 1 || rotation == 3) {
        return {size.y, size.x};
    }
    return size;
}

void sun_temple_add_rect_tiles(int building_id, tile2i tile, int w, int h, int image_id) {
    if (w < 1 || h < 1) {
        return;
    }
    for (int dy = 0; dy < h; dy++) {
        for (int dx = 0; dx < w; dx++) {
            tile2i t = tile.shifted(dx, dy);
            if (!map_grid_is_inside(t, 1)) {
                continue;
            }
            const int grid_offset = t.grid_offset();
            map_terrain_remove(grid_offset, TERRAIN_CLEARABLE);
            map_terrain_add(grid_offset, TERRAIN_BUILDING);
            map_building_set(grid_offset, building_id);
            map_property_clear_constructing(grid_offset);
            map_property_set_multi_tile_size(grid_offset, 1);
            map_image_set(grid_offset, (dx == 0 && dy == 0) ? image_id : 0);
            map_property_set_multi_tile_xy(grid_offset, dx, dy, dx == 0 && dy == 0);
        }
    }
    map_property_mark_draw_tile(tile.grid_offset());
}

bool tile_not_clear(tile2i t) {
    return map_terrain_is(t, TERRAIN_NOT_CLEAR)
        || (map_terrain_count_directly_adjacent_with_type(t, TERRAIN_FLOODPLAIN) > 0)
        || (map_terrain_count_diagonally_adjacent_with_type(t, TERRAIN_FLOODPLAIN) > 0)
        || map_has_figure_at(t);
}

// blocked_tile_vec holds only 36 entries — never use is_blocked_for_building for size>6.
bool area_blocked(tile2i origin, int w, int h) {
    if (w < 1 || h < 1) {
        return true;
    }
    for (int dy = 0; dy < h; dy++) {
        for (int dx = 0; dx < w; dx++) {
            tile2i t = origin.shifted(dx, dy);
            if (!map_grid_is_inside(t, 1) || tile_not_clear(t)) {
                return true;
            }
        }
    }
    return false;
}

void draw_area_mask(build_planner &/*planer*/, painter &ctx, tile2i origin, int w, int h, bool force_red) {
    for (int dy = 0; dy < h; dy++) {
        for (int dx = 0; dx < w; dx++) {
            tile2i t = origin.shifted(dx, dy);
            vec2i pixel = g_camera.lookup_tile_to_pixel(t);
            const bool bad = force_red || !map_grid_is_inside(t, 1) || tile_not_clear(t);
            build_planner::draw_flat_tile(ctx, pixel, bad ? COLOR_MASK_RED_30 : COLOR_MASK_GREEN_30);
        }
    }
}

// Placement rotation 0..3 (same source as part offsets / path W×H). Art pack id
// follows the camera like sphinx — separate from stored placement orientation.
int placement_rotation(const building &b) {
    return b.orientation % 4;
}

int art_orient_idx() {
    return (g_camera.orientation / 2) % 2;
}

// Rotate a 1×1 overlay offset from placement rot0 relative to body NW.
// Same transform family as part_path_offset (W=H=body; o may lie outside).
vec2i rotate_footprint_offset(vec2i o, int rotation, int w, int h) {
    rotation %= 4;
    if (rotation < 0) {
        rotation += 4;
    }
    switch (rotation) {
    case 1:
        return {h - o.y - 1, o.x};
    case 2:
        return {w - o.x - 1, h - o.y - 1};
    case 3:
        return {o.y, w - o.x - 1};
    default:
        return o;
    }
}

// Phase gate for plaza_overlays: finished temple counts as phase 5+.
bool overlay_phase_visible(int8_t phase, bool finished, int8_t min_phase, int8_t max_phase) {
    if (max_phase <= 0) {
        max_phase = 99;
    }
    const int p = finished ? 5 : (int)phase;
    if (p < min_phase || p > max_phase) {
        return false;
    }
    return true;
}

void advance_phase_all_parts(building_sun_temple *main_st) {
    if (!main_st) {
        return;
    }
    const int next = main_st->runtime_data().phase + 1;
    for (building *p = main_st->base.main(); p; p = p->has_next() ? p->next() : nullptr) {
        auto *st = p->dcast_sun_temple();
        if (st) {
            st->set_phase(next);
        }
    }
}

} // namespace

void building_sun_temple::static_params::rebuild_construction() {
    monument &m = g_monument_sun_temple;
    m.btype = BUILDING_SUN_TEMPLE;
    m.phases.clear();

    m.phases.push_back({0, monument_phase_resource{ARCHITECTS, 1}});
    m.phases.push_back({1, monument_phase_resource{ARCHITECTS, 1}});

    const uint16_t timber = !timber_loads.empty() ? timber_loads[0] : 100;
    if (timber > 0) {
        m.phases.push_back({2, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, timber}});
    } else {
        m.phases.push_back({2, monument_phase_resource{ARCHITECTS, 1}});
    }

    m.phases.push_back({3, monument_phase_resource{ARCHITECTS, 1}});

    uint16_t sand = build_sandstone > 0 ? build_sandstone : 160;
    if (!sandstone_loads.empty() && sandstone_loads[0] > 0) {
        sand = sandstone_loads[0];
    }
    m.phases.push_back({4, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_SANDSTONE, sand}});

    m.phases.push_back({5, monument_phase_resource{RESOURCE_NONE, 0}});
}

void building_sun_temple::static_params::archive_load(archive /*arch*/) {
    rebuild_construction();
}

const monument &building_sun_temple::config() const {
    return g_monument_sun_temple;
}

int building_sun_temple::placement_amount(e_resource r) const {
    const auto &bp = current_params();
    for (const auto &pr : bp.placement_resources) {
        if (pr.resource == r) {
            return pr.count;
        }
    }
    return 0;
}

int building_sun_temple::yards_available(e_resource r) {
    return g_city.resource.yards_stored_staffed(r);
}

bool building_sun_temple::has_unfinished_sun_temple() {
    // Parts of a sun temple do not share a construction phase, so only the main one answers.
    return building_monument_has_unfinished({BUILDING_SUN_TEMPLE}, /*main_parts_only*/ true);
}

int building_sun_temple::art_stage() const {
    const auto &bp = current_params();
    const int max_stage = bp.art_stages > 0 ? bp.art_stages : 4;
    const int p = runtime_data().phase;
    if (p == MONUMENT_FINISHED || p >= max_stage) {
        return max_stage;
    }
    if (p <= 1) {
        return 1;
    }
    return std::min(p, max_stage);
}

xstring building_sun_temple::anim_key_for(int stage, int orient_idx) const {
    const auto &bp = current_params();
    const int max_stage = bp.art_stages > 0 ? bp.art_stages : 4;
    if (stage < 1) {
        stage = 1;
    }
    if (stage > max_stage) {
        stage = max_stage;
    }
    if (orient_idx < 0 || orient_idx > 1) {
        orient_idx = 0;
    }
    bstring32 key;
    key.printf("s%c%d", 'a' + (stage - 1), orient_idx + 1);
    return xstring(key.c_str());
}

bool building_sun_temple::needs_resources() const {
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

bool building_sun_temple::need_stonemason() {
    if (is_finished() || !is_main()) {
        return false;
    }
    const int p = runtime_data().phase;
    if (p < 3 || p > 4) {
        return false;
    }
    // Free worker slot — otherwise guilds keep spawning into a full roster.
    const auto &w = runtime_data().workers;
    return std::find(w.begin(), w.end(), 0) != w.end();
}

bool building_sun_temple::need_workers() const {
    if (is_finished() || !is_main()) {
        return false;
    }
    const int p = runtime_data().phase;
    // 0–1: work-camp laborers. 2: carpenters (need_carpenter → free slot). 3+: stonemasons.
    if (p >= 3) {
        return false;
    }
    if (p == 2 && needs_resource(RESOURCE_TIMBER) <= 0) {
        return false;
    }
    const auto &w = runtime_data().workers;
    return std::find(w.begin(), w.end(), 0) != w.end();
}

void building_sun_temple::add_workers(figure_id fid) {
    if (!is_main()) {
        main()->add_workers(fid);
        return;
    }
    auto &d = runtime_data();
    for (auto &wid : d.workers) {
        if (wid == 0) {
            wid = fid;
            return;
        }
    }
}

void building_sun_temple::remove_worker(figure_id fid) {
    if (!is_main()) {
        main()->remove_worker(fid);
        return;
    }
    auto &d = runtime_data();
    for (auto &wid : d.workers) {
        if (wid == fid) {
            wid = 0;
            return;
        }
    }
}

int building_sun_temple::building_image_get() const {
    const auto &params = current_params();
    const int orient = art_orient_idx();
    const int part = runtime_data().variant;

    if (part == PART_PATH) {
        bstring32 key;
        key.printf("path%d", orient + 1);
        int img = params.first_img(xstring(key.c_str()));
        if (img <= 0) {
            img = params.first_img("path1");
        }
        return img > 0 ? img : params.first_img("preview");
    }
    if (part == PART_HALL) {
        bstring32 key;
        key.printf("hall%d", orient + 1);
        int img = params.first_img(xstring(key.c_str()));
        if (img <= 0) {
            img = params.first_img("hall1");
        }
        return img > 0 ? img : params.first_img("preview");
    }

    const xstring key = anim_key_for(art_stage(), orient);
    int img = params.first_img(key);
    if (img > 0) {
        return img;
    }
    // Fallback legacy sa / preview
    img = params.first_img("sa1");
    if (img > 0) {
        return img;
    }
    return params.first_img("preview");
}

bool building_sun_temple::draw_ornaments_and_animations_height(painter &ctx, vec2i /*point*/, tile2i tile, color color_mask) {
    // Overlays only from the body NW tile — path/hall parts skip.
    if (!is_main() || runtime_data().variant != PART_BODY || tile != base.tile) {
        return false;
    }

    const auto &params = current_params();
    const auto &bp = params;
    if (bp.plaza_overlays.empty()) {
        return false;
    }

    // Offsets are always relative to body NW (may be outside the 10×10).
    // Must rotate with body×body — init_tiles W×H is wrong because body.tile is
    // not the AABB origin on rot 1/3 (path sticks out to −X / −Y).
    const int body = base.size > 0 ? base.size : 10;
    const int rotation = placement_rotation(base);
    const int8_t phase = runtime_data().phase;
    const bool finished = is_finished();

    auto draw_layer = [&](int image_id, vec2i pixel) {
        if (image_id <= 0) {
            return;
        }
        auto &command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile);
        command.image_id = image_id;
        command.pixel = pixel;
        command.mask = color_mask;
    };

    bool drew = false;
    for (const auto &ov : bp.plaza_overlays) {
        if (!overlay_phase_visible(phase, finished, ov.min_phase, ov.max_phase)) {
            continue;
        }
        if (ov.key.empty()) {
            continue;
        }
        const int img = params.first_img(ov.key);
        if (img <= 0) {
            continue;
        }
        const vec2i off = rotate_footprint_offset(ov.offset, rotation, body, body);
        const vec2i px = g_camera.lookup_tile_to_pixel(base.tile.shifted(off.x, off.y)) + ov.pixel;
        draw_layer(img, px);
        drew = true;
    }
    return drew;
}

void building_sun_temple::refresh_part_tiles() {
    const int part = runtime_data().variant;
    const int img = building_image_get();
    if (part == PART_PATH) {
        const auto &bp = current_params();
        // Must use placement rotation (0..3), not camera absolute orientation.
        const vec2i psz = oriented_wh(bp.path_size.x > 0 ? bp.path_size : vec2i{8, 2}, placement_rotation(base));
        sun_temple_add_rect_tiles(id(), tile(), psz.x, psz.y, img);
        return;
    }
    if (part == PART_HALL) {
        const int size = base.size > 0 ? base.size : 3;
        map_building_tiles_add(id(), tile(), size, img, TERRAIN_BUILDING);
        return;
    }
    const int size = base.size > 0 ? base.size : 10;
    map_building_tiles_add(id(), tile(), size, img, TERRAIN_BUILDING);
}

void building_sun_temple::preview::setup_preview_graphics(build_planner &planer) const {
    const auto &bp = st_params();
    vec2i init_tiles = bp.init_tiles;
    if (init_tiles.x <= 0 || init_tiles.y <= 0) {
        init_tiles = vec2i{10, 15};
    }
    switch (building_rotation_global_rotation() % 4) {
    case 0:
        planer.init_tiles(init_tiles.x, init_tiles.y);
        break;
    case 1:
        planer.init_tiles(init_tiles.y, init_tiles.x);
        break;
    case 2:
        planer.init_tiles(init_tiles.x, init_tiles.y);
        break;
    case 3:
        planer.init_tiles(init_tiles.y, init_tiles.x);
        break;
    }
}

int building_sun_temple::preview::can_place(build_planner &p, tile2i /*tile*/, tile2i end, int state) const {
    if (state != CAN_PLACE && state != CAN_NOT_BUT_GREEN) {
        return state;
    }
    if (has_unfinished_sun_temple()) {
        p.set_warning("#only_one_sun_temple_at_a_time");
        return CAN_NOT_PLACE;
    }
    int sandstone_need = 0;
    for (const auto &pr : building_sun_temple::current_params().placement_resources) {
        if (pr.resource == RESOURCE_SANDSTONE) {
            sandstone_need = pr.count;
            break;
        }
    }
    if (sandstone_need > 0 && yards_available(RESOURCE_SANDSTONE) < sandstone_need) {
        return CAN_NOT_PLACE;
    }

    const auto &bp = st_params();
    const int rotation = building_rotation_global_rotation() % 4;
    const int body = 10;
    const vec2i path_sz = oriented_wh(bp.path_size.x > 0 ? bp.path_size : vec2i{8, 2}, rotation);
    const vec2i hall_sz = bp.hall_size.x > 0 ? bp.hall_size : vec2i{3, 3};
    const vec2i off_path = part_offset(bp.part_path_offset, rotation, vec2i{1, 10});
    const vec2i off_hall = part_offset(bp.part_hall_offset, rotation, vec2i{4, 12});

    if (area_blocked(end, body, body)
        || area_blocked(end.shifted(off_path), path_sz.x, path_sz.y)
        || area_blocked(end.shifted(off_hall), hall_sz.x, hall_sz.y)) {
        return CAN_NOT_PLACE;
    }
    return CAN_PLACE;
}

int building_sun_temple::preview::finalize_check(build_planner &p, tile2i tile, tile2i end, int state) const {
    state = building_planer_renderer::finalize_check(p, tile, end, state);
    if (state != CAN_PLACE) {
        return state;
    }
    if (has_unfinished_sun_temple()) {
        p.set_warning("#only_one_sun_temple_at_a_time");
        return CAN_NOT_PLACE;
    }
    int sandstone_need = 0;
    for (const auto &pr : building_sun_temple::current_params().placement_resources) {
        if (pr.resource == RESOURCE_SANDSTONE) {
            sandstone_need = pr.count;
            break;
        }
    }
    if (sandstone_need > 0 && yards_available(RESOURCE_SANDSTONE) < sandstone_need) {
        p.set_warning("#need_220_blocks_of_sandstone_for_sun_temple");
        g_warning_manager.show("#need_220_blocks_of_sandstone_for_sun_temple");
        return CAN_NOT_PLACE;
    }
    // Full footprint check (body + path + hall).
    return can_place(p, tile, end, CAN_PLACE);
}

int building_sun_temple::preview::construction_place(build_planner &planer, tile2i tile, tile2i end, int orientation, int variant) const {
    const int placed = building_planer_renderer::construction_place(planer, tile, end, orientation, variant);
    if (placed && planer.last_created_building && !planer.last_created_building->is_valid()) {
        planer.last_created_building = nullptr;
        return 0;
    }
    return placed;
}

void building_sun_temple::preview::ghost_preview(build_planner &planer, painter &ctx, tile2i /*start*/, tile2i end, vec2i pixel) const {
    const auto &params = building_static_params::get(planer.build_type);
    const auto &bp = st_params();
    const int rotation = building_rotation_global_rotation() % 4;
    const int body = 10;
    const vec2i path_sz = oriented_wh(bp.path_size.x > 0 ? bp.path_size : vec2i{8, 2}, rotation);
    const vec2i hall_sz = bp.hall_size.x > 0 ? bp.hall_size : vec2i{3, 3};
    const vec2i off_path = part_offset(bp.part_path_offset, rotation, vec2i{1, 10});
    const vec2i off_hall = part_offset(bp.part_hall_offset, rotation, vec2i{4, 12});

    tile2i tile_path = end.shifted(off_path);
    tile2i tile_hall = end.shifted(off_hall);

    const bool blocked = area_blocked(end, body, body)
        || area_blocked(tile_path, path_sz.x, path_sz.y)
        || area_blocked(tile_hall, hall_sz.x, hall_sz.y);

    const int preview = params.first_img("preview");
    const int img_body = params.first_img("sa1");
    const int img_path = params.first_img("path1");
    const int img_hall = params.first_img("hall1");
    const int img_stake = params.first_img("stake");

    if (blocked) {
        draw_area_mask(planer, ctx, end, body, body, true);
        draw_area_mask(planer, ctx, tile_path, path_sz.x, path_sz.y, true);
        draw_area_mask(planer, ctx, tile_hall, hall_sz.x, hall_sz.y, true);
        return;
    }

    planer.draw_building_ghost(ctx, img_body > 0 ? img_body : preview, pixel);
    planer.draw_building_ghost(ctx, img_path > 0 ? img_path : preview, g_camera.lookup_tile_to_pixel(tile_path));
    planer.draw_building_ghost(ctx, img_hall > 0 ? img_hall : preview, g_camera.lookup_tile_to_pixel(tile_hall));

    // I6: stakes along full AABB corners (V0 place look).
    if (img_stake > 0) {
        vec2i init_tiles = bp.init_tiles.x > 0 ? bp.init_tiles : vec2i{10, 15};
        const vec2i ft = oriented_wh(init_tiles, rotation);
        const tile2i corners[] = {
            end,
            end.shifted(ft.x - 1, 0),
            end.shifted(0, ft.y - 1),
            end.shifted(ft.x - 1, ft.y - 1),
            end.shifted(ft.x / 2, 0),
            end.shifted(0, ft.y / 2),
            end.shifted(ft.x - 1, ft.y / 2),
            end.shifted(ft.x / 2, ft.y - 1),
        };
        for (const tile2i &c : corners) {
            planer.draw_building_ghost(ctx, img_stake, g_camera.lookup_tile_to_pixel(c));
        }
    }
}

void building_sun_temple::on_place(int orientation, int variant) {
    building_impl::on_place(orientation, variant);

    // Parts may have failed to spawn — do not charge sandstone for a half-built temple.
    if (!base.is_valid()) {
        return;
    }

    const int need = placement_amount(RESOURCE_SANDSTONE);
    if (need > 0) {
        events::emit(event_city_remove_resource{RESOURCE_SANDSTONE, need, /*staffed_only*/true});
    }
}

void building_sun_temple::on_place_update_tiles(int /*orientation*/, int /*variant*/) {
    base.prev_part_building_id = 0;
    runtime_data().variant = PART_BODY;
    // Persist placement rotation (0..3) — same index as part_*_offset / path W×H.
    // absolute_orientation from the planner can differ from global_rotation.
    const int rotation = building_rotation_global_rotation() % 4;
    base.orientation = (uint8_t)rotation;
    base.size = 10;

    refresh_part_tiles();

    const auto &bp = current_params();
    const vec2i off_path = part_offset(bp.part_path_offset, rotation, vec2i{1, 10});
    const vec2i off_hall = part_offset(bp.part_hall_offset, rotation, vec2i{4, 12});
    const vec2i hall_sz = bp.hall_size.x > 0 ? bp.hall_size : vec2i{3, 3};

    building *part_path = building_create(BUILDING_SUN_TEMPLE, tile().shifted(off_path), 0);
    building *part_hall = building_create(BUILDING_SUN_TEMPLE, tile().shifted(off_hall), 0);
    const bool path_ok = part_path && part_path->id > 0;
    const bool hall_ok = part_hall && part_hall->id > 0;
    if (!path_ok || !hall_ok) {
        // Tear down the whole place attempt: body alone would block "one unfinished".
        if (path_ok) {
            map_building_tiles_remove(part_path->id, part_path->tile);
            part_path->state = BUILDING_STATE_DELETED_BY_GAME;
        }
        if (hall_ok) {
            map_building_tiles_remove(part_hall->id, part_hall->tile);
            part_hall->state = BUILDING_STATE_DELETED_BY_GAME;
        }
        map_building_tiles_remove(id(), tile());
        base.state = BUILDING_STATE_DELETED_BY_GAME;
        return;
    }
    game_undo_add_building(part_path);
    game_undo_add_building(part_hall);

    auto *sp = part_path->dcast_sun_temple();
    auto *sh = part_hall->dcast_sun_temple();
    if (sp) {
        sp->runtime_data().variant = PART_PATH;
        sp->runtime_data().phase = runtime_data().phase;
        part_path->orientation = (uint8_t)rotation;
        part_path->size = 1; // rect tiles; never size² leveling
        sp->refresh_part_tiles();
    }
    if (sh) {
        sh->runtime_data().variant = PART_HALL;
        sh->runtime_data().phase = runtime_data().phase;
        part_hall->orientation = (uint8_t)rotation;
        part_hall->size = (uint8_t)std::max(hall_sz.x, 1);
        sh->refresh_part_tiles();
    }

    part_path->prev_part_building_id = id();
    base.next_part_building_id = part_path->id;
    part_path->next_part_building_id = part_hall->id;
    part_hall->prev_part_building_id = part_path->id;
    part_hall->next_part_building_id = 0;
}

void building_sun_temple::on_destroy() {
    building_monument_remove_all_deliveries(id());
}

void building_sun_temple::on_phase_changed(int old_phase, int current) {
    refresh_part_tiles();

    if (current != MONUMENT_FINISHED) {
        auto &d = runtime_data();
        for (e_resource resource = RESOURCE_NONE; resource < RESOURCES_MAX; ++resource) {
            d.resources_pct[resource] = 0;
        }
    }

    if (!is_main()) {
        return;
    }

    // Leave leveling once: poof laborers; do not wipe on later advances.
    if (old_phase < 2 && current >= 2) {
        auto &d = runtime_data();
        for (auto &wid : d.workers) {
            if (wid) {
                figure *f = figure_get(wid);
                if (f && f->is_alive()) {
                    f->poof();
                }
                wid = 0;
            }
        }
    }
}

void building_sun_temple::update_day() {
    building_impl::update_day();
    if (!is_main() || is_finished()) {
        return;
    }

    auto &d = runtime_data();
    if (d.phase < 2) {
        // Body-only leveling — never walk linked path/hall via map_grid_get_tiles(&base).
        const int body = base.size > 0 ? base.size : 10;
        grid_tiles tiles = map_grid_get_tiles(tile(), tile().shifted(body - 1, body - 1));
        tile2i tile2works = map_grid_area_first(tiles, [](tile2i t) {
            return map_monuments_get_progress(t) < 200;
        });
        const bool all_tiles_finished = (tile2works == tile2i{-1, -1});
        if (all_tiles_finished) {
            map_grid_area_foreach(tiles, [](tile2i t) { map_monuments_set_progress(t, 0); });
            // Mastaba-style: advance every linked part. progress() later does
            // phase+1 per part — a main-only bump here permanently desyncs path/hall.
            advance_phase_all_parts(this);
        }
        return;
    }

    const int phase_before = d.phase;
    progress();
    if (phase_before != MONUMENT_FINISHED && is_finished()) {
        city_message &message = city_message_post_with_popup_delay(
            MESSAGE_CAT_MONUMENTS, true, "sun_temple_congratulations", type(), tile().grid_offset());
        message.hide_img = true;
    }
}

void building_sun_temple::update_map_orientation(int /*map_orientation*/) {
    refresh_part_tiles();
}

tile2i building_sun_temple::center_point() const {
    building *m = base.main();
    const int s = m->size > 0 ? m->size : 10;
    return m->tile.shifted(s / 2, s / 2);
}

tile2i building_sun_temple::access_point() const {
    // Prefer hall (variant 2) when present.
    for (building *p = base.main(); p; p = p->has_next() ? p->next() : nullptr) {
        auto *st = p->dcast_sun_temple();
        if (st && st->runtime_data().variant == PART_HALL) {
            return p->tile;
        }
    }
    return main()->tile();
}

grid_area building_sun_temple::get_area() const {
    building *m = base.main();
    tile2i start = m->tile;
    tile2i end = start.shifted(std::max((int)m->size, 1) - 1, std::max((int)m->size, 1) - 1);

    const auto &bp = current_params();
    for (building *p = m; p; p = p->has_next() ? p->next() : nullptr) {
        auto *st = p->dcast_sun_temple();
        int w = p->size;
        int h = p->size;
        if (st && st->runtime_data().variant == PART_PATH) {
            const vec2i psz = oriented_wh(bp.path_size.x > 0 ? bp.path_size : vec2i{8, 2}, placement_rotation(*p));
            w = psz.x;
            h = psz.y;
        } else if (st && st->runtime_data().variant == PART_HALL) {
            w = bp.hall_size.x > 0 ? bp.hall_size.x : 3;
            h = bp.hall_size.y > 0 ? bp.hall_size.y : 3;
        }
        tile2i pmin = p->tile;
        tile2i pmax = p->tile.shifted(std::max(w, 1) - 1, std::max(h, 1) - 1);
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

void building_sun_temple::bind_dynamic(io_buffer *iob, size_t /*version*/) {
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

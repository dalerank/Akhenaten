#include "monument_mausoleum.h"

#include "building/monuments.h"
#include "building/rotation.h"
#include "city/city.h"
#include "city/city_figures.h"
#include "city/city_resource.h"
#include "city/city_warnings.h"
#include "construction/build_planner.h"
#include "figure/figure.h"
#include "game/resource.h"
#include "game/undo.h"
#include "graphics/color.h"
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

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_mausoleum);

static monument g_monument_mausoleum{BUILDING_MAUSOLEUM};

namespace {

const building_mausoleum::base_params &maus_params() {
    return (const building_mausoleum::base_params &)building_mausoleum::current_params();
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

bool tile_not_clear(tile2i t) {
    return map_terrain_is(t, TERRAIN_NOT_CLEAR)
        || (map_terrain_count_directly_adjacent_with_type(t, TERRAIN_FLOODPLAIN) > 0)
        || (map_terrain_count_diagonally_adjacent_with_type(t, TERRAIN_FLOODPLAIN) > 0)
        || map_has_figure_at(t);
}

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

void draw_area_mask(painter &ctx, tile2i origin, int w, int h, bool force_red) {
    for (int dy = 0; dy < h; dy++) {
        for (int dx = 0; dx < w; dx++) {
            tile2i t = origin.shifted(dx, dy);
            vec2i pixel = g_camera.lookup_tile_to_pixel(t);
            const bool bad = force_red || !map_grid_is_inside(t, 1) || tile_not_clear(t);
            build_planner::draw_flat_tile(ctx, pixel, bad ? COLOR_MASK_RED_30 : COLOR_MASK_GREEN_30);
        }
    }
}

void mausoleum_add_rect_tiles(int building_id, tile2i tile, int w, int h, int image_id) {
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

uint16_t load_at(const svector<uint16_t, 8> &loads, int index) {
    if (index >= 0 && index < (int)loads.size()) {
        return loads[index];
    }
    return 0;
}

bool worker_slot_occupied(uint16_t wid) {
    if (wid == 0) {
        return false;
    }
    figure *f = figure_get(wid);
    return f && f->is_alive();
}

void scrub_dead_workers(std::array<uint16_t, 5> &workers) {
    for (auto &wid : workers) {
        if (wid && !worker_slot_occupied(wid)) {
            wid = 0;
        }
    }
}

int art_orient_idx() {
    return (g_camera.orientation / 2) % 2;
}

} // namespace

void building_mausoleum::static_params::rebuild_construction() {
    monument &m = g_monument_mausoleum;
    m.btype = BUILDING_MAUSOLEUM;
    m.phases.clear();

    // 0–1: Work Camp clearing / foundation.
    m.phases.push_back({0, monument_phase_resource{ARCHITECTS, 1}});
    m.phases.push_back({1, monument_phase_resource{ARCHITECTS, 1}});

    const uint16_t story1 = load_at(sandstone_loads, 0);
    const uint16_t story2 = load_at(sandstone_loads, 1);
    const uint16_t timber = load_at(timber_loads, 0);

    // 2: first story — sandstone + stonemasons
    if (story1 > 0) {
        m.phases.push_back({2, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_SANDSTONE, story1}});
    } else {
        m.phases.push_back({2, monument_phase_resource{ARCHITECTS, 1}});
    }

    // 3: wooden ramps — timber + carpenters
    if (timber > 0) {
        m.phases.push_back({3, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, timber}});
    } else {
        m.phases.push_back({3, monument_phase_resource{ARCHITECTS, 1}});
    }

    // 4: second story — sandstone + stonemasons
    if (story2 > 0) {
        m.phases.push_back({4, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_SANDSTONE, story2}});
    } else {
        m.phases.push_back({4, monument_phase_resource{ARCHITECTS, 1}});
    }

    // 5: finish sentinel
    m.phases.push_back({5, monument_phase_resource{RESOURCE_NONE, 0}});
}

void building_mausoleum::static_params::archive_load(archive /*arch*/) {
    rebuild_construction();
}

const monument &building_mausoleum::config() const {
    return g_monument_mausoleum;
}

int building_mausoleum::placement_amount(e_resource r) const {
    const auto &bp = current_params();
    for (const auto &pr : bp.placement_resources) {
        if (pr.resource == r) {
            return pr.count;
        }
    }
    return 0;
}

int building_mausoleum::yards_available(e_resource r) {
    return g_city.resource.yards_stored_staffed(r);
}

bool building_mausoleum::has_unfinished_mausoleum() {
    // Include CREATED: VALID is applied on the next building_update_state tick
    // (or by test validate_last_created). Same-frame second place must still see it.
    return building_monument_has_unfinished({BUILDING_MAUSOLEUM}, /*main_parts_only*/ false,
      /*include_just_placed*/ true);
}

vec2i building_mausoleum::footprint_size() const {
    const auto &bp = current_params();
    vec2i ft = bp.init_tiles;
    if (ft.x <= 0 || ft.y <= 0) {
        ft = {8, 22};
    }
    return oriented_wh(ft, base.orientation % 4);
}

int building_mausoleum::art_stage() const {
    const auto &bp = current_params();
    const int max_stage = bp.art_stages > 0 ? bp.art_stages : 3;
    const int p = runtime_data().phase;
    if (p == MONUMENT_FINISHED) {
        return max_stage;
    }
    if (p <= 1) {
        return 1; // clear / early
    }
    if (p <= 3) {
        return std::min(2, max_stage); // story1 + ramp
    }
    return std::min(3, max_stage); // story2
}

xstring building_mausoleum::anim_key_for(int stage, int orient_idx) const {
    const auto &bp = current_params();
    const int max_stage = bp.art_stages > 0 ? bp.art_stages : 3;
    if (stage < 1) {
        stage = 1;
    }
    if (stage > max_stage) {
        stage = max_stage;
    }
    if (orient_idx < 0 || orient_idx > 1) {
        orient_idx = 0;
    }
    // Skin suffix from variant 0/1/2 (PACK_LIB_MAUSOLEUM_*).
    const int skin = runtime_data().variant % 3;
    bstring32 key;
    key.printf("s%c%d_v%d", 'a' + (stage - 1), orient_idx + 1, skin);
    return xstring(key.c_str());
}

bool building_mausoleum::needs_resources() const {
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

bool building_mausoleum::need_stonemason() {
    if (is_finished()) {
        return false;
    }
    scrub_dead_workers(runtime_data().workers);
    const int p = runtime_data().phase;
    // Stories 1 and 2 (phases 2 and 4). Do not call need_workers() — that is false here.
    if (p != 2 && p != 4) {
        return false;
    }
    // One mason is enough for update_day progress (same gate as Caesareum / Library).
    for (auto wid : runtime_data().workers) {
        figure *f = wid > 0 ? figure_get(wid) : nullptr;
        if (f && f->is_alive() && f->type == FIGURE_STONEMASON) {
            return false;
        }
    }
    const auto &w = runtime_data().workers;
    return std::find(w.begin(), w.end(), 0) != w.end();
}

bool building_mausoleum::need_carpenter() {
    if (is_finished()) {
        return false;
    }
    scrub_dead_workers(runtime_data().workers);
    const int p = runtime_data().phase;
    // Ramp phase only. Do not route through need_workers() — that flag also
    // summons Work Camp peasants, who can fill all slots and starve the guild.
    if (p != 3) {
        return false;
    }
    if (needs_resource(RESOURCE_TIMBER, p) <= 0) {
        return false;
    }
    for (auto wid : runtime_data().workers) {
        figure *f = wid > 0 ? figure_get(wid) : nullptr;
        if (f && f->is_alive() && f->type == FIGURE_CARPENTER) {
            return false;
        }
    }
    const auto &w = runtime_data().workers;
    return std::find(w.begin(), w.end(), 0) != w.end();
}

bool building_mausoleum::need_workers() const {
    if (is_finished()) {
        return false;
    }
    const int p = runtime_data().phase;
    // Work Camp only for clearing / foundation. Stories → need_stonemason;
    // ramps → need_carpenter (must not share this flag with peasants).
    if (p >= 2) {
        return false;
    }
    const auto &w = runtime_data().workers;
    return std::find(w.begin(), w.end(), 0) != w.end();
}

void building_mausoleum::add_workers(figure_id fid) {
    auto &d = runtime_data();
    scrub_dead_workers(d.workers);
    for (auto &wid : d.workers) {
        if (wid == 0) {
            wid = fid;
            return;
        }
    }
}

void building_mausoleum::remove_worker(figure_id fid) {
    auto &d = runtime_data();
    for (auto &wid : d.workers) {
        if (wid == fid) {
            wid = 0;
            return;
        }
    }
}

int building_mausoleum::building_image_get() const {
    const auto &params = current_params();
    const xstring key = anim_key_for(art_stage(), art_orient_idx());
    int img = params.first_img(key);
    if (img > 0) {
        return img;
    }
    // Fallbacks: stage without skin / camera, then preview.
    bstring32 fallback;
    fallback.printf("s%c1", 'a' + (art_stage() - 1));
    img = params.first_img(xstring(fallback.c_str()));
    if (img > 0) {
        return img;
    }
    img = params.first_img("sa1");
    if (img > 0) {
        return img;
    }
    return params.first_img("preview");
}

void building_mausoleum::preview::setup_preview_graphics(build_planner &planer) const {
    const auto &bp = maus_params();
    vec2i init_tiles = bp.init_tiles;
    if (init_tiles.x <= 0 || init_tiles.y <= 0) {
        init_tiles = vec2i{8, 22};
    }
    const vec2i ft = oriented_wh(init_tiles, building_rotation_global_rotation() % 4);
    planer.init_tiles(ft.x, ft.y);
}

int building_mausoleum::preview::construction_place(build_planner &planer, tile2i /*start*/, tile2i end, int orientation, int variant) const {
    // Default placer uses square building_size for camera origin adjust — wrong for 8×22.
    const auto &bp = maus_params();
    vec2i init_tiles = bp.init_tiles.x > 0 ? bp.init_tiles : vec2i{8, 22};
    const vec2i ft = oriented_wh(init_tiles, building_rotation_global_rotation() % 4);

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
    if (b->id <= 0) {
        return 0;
    }

    add_building(b, orientation, variant);
    planer.last_created_building = b;
    return 1;
}

int building_mausoleum::preview::can_place(build_planner &p, tile2i /*tile*/, tile2i end, int state) const {
    if (state != CAN_PLACE && state != CAN_NOT_BUT_GREEN) {
        return state;
    }
    if (has_unfinished_mausoleum()) {
        p.set_warning("#only_one_building_of_this_type");
        return CAN_NOT_PLACE;
    }
    int sandstone_need = 0;
    for (const auto &pr : building_mausoleum::current_params().placement_resources) {
        if (pr.resource == RESOURCE_SANDSTONE) {
            sandstone_need = pr.count;
            break;
        }
    }
    if (sandstone_need > 0 && yards_available(RESOURCE_SANDSTONE) < sandstone_need) {
        return CAN_NOT_PLACE;
    }

    const auto &bp = maus_params();
    vec2i init_tiles = bp.init_tiles.x > 0 ? bp.init_tiles : vec2i{8, 22};
    const vec2i ft = oriented_wh(init_tiles, building_rotation_global_rotation() % 4);
    if (area_blocked(end, ft.x, ft.y)) {
        return CAN_NOT_PLACE;
    }
    return CAN_PLACE;
}

int building_mausoleum::preview::finalize_check(build_planner &p, tile2i tile, tile2i end, int state) const {
    state = building_planer_renderer::finalize_check(p, tile, end, state);
    if (state != CAN_PLACE) {
        return state;
    }
    if (has_unfinished_mausoleum()) {
        p.set_warning("#only_one_building_of_this_type");
        g_warning_manager.show("#only_one_building_of_this_type");
        return CAN_NOT_PLACE;
    }
    int sandstone_need = 0;
    for (const auto &pr : building_mausoleum::current_params().placement_resources) {
        if (pr.resource == RESOURCE_SANDSTONE) {
            sandstone_need = pr.count;
            break;
        }
    }
    if (sandstone_need > 0 && yards_available(RESOURCE_SANDSTONE) < sandstone_need) {
        p.set_warning("#mausoleum_needs_sandstone");
        g_warning_manager.show("#mausoleum_needs_sandstone");
        return CAN_NOT_PLACE;
    }
    return can_place(p, tile, end, CAN_PLACE);
}

void building_mausoleum::preview::ghost_preview(build_planner &planer, painter &ctx, tile2i /*start*/, tile2i end, vec2i pixel) const {
    const auto &params = building_static_params::get(planer.build_type);
    const auto &bp = maus_params();
    vec2i init_tiles = bp.init_tiles.x > 0 ? bp.init_tiles : vec2i{8, 22};
    const vec2i ft = oriented_wh(init_tiles, building_rotation_global_rotation() % 4);
    const bool blocked = has_unfinished_mausoleum() || area_blocked(end, ft.x, ft.y);

    if (blocked) {
        draw_area_mask(ctx, end, ft.x, ft.y, true);
        return;
    }

    int sandstone_need = 0;
    for (const auto &pr : building_mausoleum::current_params().placement_resources) {
        if (pr.resource == RESOURCE_SANDSTONE) {
            sandstone_need = pr.count;
            break;
        }
    }
    if (sandstone_need > 0 && yards_available(RESOURCE_SANDSTONE) < sandstone_need) {
        draw_area_mask(ctx, end, ft.x, ft.y, true);
        return;
    }

    // Ghost shows selected art skin (Ctrl+R / custom_building_variant → building_variant).
    int skin = planer.building_variant % 3;
    if (skin < 0) {
        skin = 0;
    }
    bstring32 key;
    key.printf("sa1_v%d", skin);
    int img = params.first_img(xstring(key.c_str()));
    if (img <= 0) {
        img = params.first_img("sa1");
    }
    if (img <= 0) {
        img = params.first_img("preview");
    }
    planer.draw_building_ghost(ctx, img, pixel);
}

void building_mausoleum::on_place(int orientation, int variant) {
    building_impl::on_place(orientation, variant);
    // During place, state is still CREATED (VALID set later by planner validate /
    // undo_finish). Do not gate on is_valid() — that skips sandstone consume.
    if (base.state == BUILDING_STATE_DELETED_BY_GAME || base.type != BUILDING_MAUSOLEUM) {
        return;
    }
    int need = placement_amount(RESOURCE_SANDSTONE);
    if (need <= 0) {
        need = 240;
    }
    event_storageyards_remove_resource ev{RESOURCE_SANDSTONE, need, /*staffed_only*/true};
    city_storageyards_remove_resource(ev);
}

void building_mausoleum::on_place_update_tiles(int /*orientation*/, int variant) {
    const int rotation = building_rotation_global_rotation() % 4;
    base.orientation = (uint8_t)rotation;
    // Art skin 0/1/2 from planner (Ctrl+R). Persist for draw + save.
    runtime_data().variant = (uint8_t)((variant < 0 ? 0 : variant) % 3);
    const vec2i ft = footprint_size();
    base.size = (uint8_t)std::max({ft.x, ft.y, 1});
    mausoleum_add_rect_tiles(id(), tile(), ft.x, ft.y, building_image_get());
    for (int dy = 0; dy < ft.y; dy++) {
        for (int dx = 0; dx < ft.x; dx++) {
            map_monuments_set_progress(tile().shifted(dx, dy), 0);
        }
    }
}

void building_mausoleum::on_place_checks() {
    construction_warnings warnings;
    const vec2i ft = footprint_size();
    int min_value = 12;
    int min_go = tile().grid_offset();
    const bool has_road = map_road_find_minimum_tile_xy(tile(), ft.x, ft.y, &min_value, &min_go) && min_value < 12;
    warnings.add_if(!has_road, "#needs_road_access");
}

void building_mausoleum::on_destroy() {
    building_monument_remove_all_deliveries(id());
    const vec2i ft = footprint_size();
    for (int dy = 0; dy < ft.y; dy++) {
        for (int dx = 0; dx < ft.x; dx++) {
            tile2i t = tile().shifted(dx, dy);
            if (!map_grid_is_inside(t, 1)) {
                continue;
            }
            map_monuments_set_progress(t, 0);
            if (map_building_at(t) == id()) {
                map_building_tile_clear_at(t.grid_offset(), type());
            }
        }
    }
}

void building_mausoleum::on_phase_changed(int old_phase, int current) {
    const vec2i ft = footprint_size();
    mausoleum_add_rect_tiles(id(), tile(), ft.x, ft.y, building_image_get());

    if (current != MONUMENT_FINISHED) {
        auto &d = runtime_data();
        for (e_resource resource = RESOURCE_NONE; resource < RESOURCES_MAX; ++resource) {
            d.resources_pct[resource] = 0;
        }
    }

    // Leave leveling: poof WC laborers once.
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

void building_mausoleum::update_day() {
    building_impl::update_day();
    if (is_finished()) {
        return;
    }

    auto &d = runtime_data();
    scrub_dead_workers(d.workers);
    if (d.phase < 2) {
        const vec2i ft = footprint_size();
        grid_tiles tiles = map_grid_get_tiles(tile(), tile().shifted(ft.x - 1, ft.y - 1));
        tile2i tile2works = map_grid_area_first(tiles, [](tile2i t) {
            return map_monuments_get_progress(t) < 200;
        });
        const bool all_tiles_finished = (tile2works == tile2i{-1, -1});
        if (all_tiles_finished) {
            map_grid_area_foreach(tiles, [](tile2i t) { map_monuments_set_progress(t, 0); });
            set_phase(d.phase + 1);
        }
        return;
    }

    // Story phases need a living stonemason before progress ticks.
    if ((d.phase == 2 || d.phase == 4) && !needs_resources()) {
        bool has_mason = false;
        for (auto wid : d.workers) {
            figure *f = wid > 0 ? figure_get(wid) : nullptr;
            if (f && f->is_alive() && f->type == FIGURE_STONEMASON) {
                has_mason = true;
                break;
            }
        }
        if (!has_mason) {
            return;
        }
    }

    // Ramp phase: after timber is in, still require a carpenter on site (symmetric to mason).
    if (d.phase == 3 && !needs_resources()) {
        bool has_carpenter = false;
        for (auto wid : d.workers) {
            figure *f = wid > 0 ? figure_get(wid) : nullptr;
            if (f && f->is_alive() && f->type == FIGURE_CARPENTER) {
                has_carpenter = true;
                break;
            }
        }
        if (!has_carpenter) {
            return;
        }
    }

    progress();
}

void building_mausoleum::update_map_orientation(int /*map_orientation*/) {
    const vec2i ft = footprint_size();
    mausoleum_add_rect_tiles(id(), tile(), ft.x, ft.y, building_image_get());
}

tile2i building_mausoleum::center_point() const {
    const vec2i ft = footprint_size();
    return tile().shifted(ft.x / 2, ft.y / 2);
}

tile2i building_mausoleum::access_point() const {
    const vec2i ft = footprint_size();
    return tile().shifted(ft.x / 2, ft.y - 1);
}

grid_area building_mausoleum::get_area() const {
    const vec2i ft = footprint_size();
    tile2i start = tile();
    tile2i end = start.shifted(ft.x - 1, ft.y - 1);
    return {start, end};
}

void building_mausoleum::bind_dynamic(io_buffer *iob, size_t /*version*/) {
    auto &monumentd = runtime_data();

    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &monumentd.burial_stock[i]);
    }
    iob->bind____skip(2); // was skip(38); 36 = burial_stock
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

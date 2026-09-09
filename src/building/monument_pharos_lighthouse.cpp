#include "monument_pharos_lighthouse.h"

#include "building/monuments.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "city/city_warnings.h"
#include "construction/build_planner.h"
#include "figure/figure.h"
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

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_pharos_lighthouse);

static monument g_monument_pharos_lighthouse{BUILDING_PHAROS_LIGHTHOUSE};

namespace {

// Rock footprint: every tile must be rock; reject water / building / figures / elevation.
bool tile_not_rock(tile2i t) {
    if (!map_terrain_is(t, TERRAIN_ROCK)) {
        return true;
    }
    if (map_terrain_is(t, TERRAIN_WATER | TERRAIN_BUILDING | TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP
            | TERRAIN_TREE | TERRAIN_SHRUB | TERRAIN_GARDEN | TERRAIN_ROAD | TERRAIN_CANAL)) {
        return true;
    }
    if (map_has_figure_at(t)) {
        return true;
    }
    return false;
}

bool area_not_all_rock(tile2i origin, int w, int h) {
    if (w < 1 || h < 1) {
        return true;
    }
    for (int dy = 0; dy < h; dy++) {
        for (int dx = 0; dx < w; dx++) {
            tile2i t = origin.shifted(dx, dy);
            if (!map_grid_is_inside(t, 1) || tile_not_rock(t)) {
                return true;
            }
        }
    }
    return false;
}

void draw_rock_area_mask(painter &ctx, tile2i origin, int w, int h, bool force_red) {
    for (int dy = 0; dy < h; dy++) {
        for (int dx = 0; dx < w; dx++) {
            tile2i t = origin.shifted(dx, dy);
            vec2i pixel = g_camera.lookup_tile_to_pixel(t);
            const bool bad = force_red || !map_grid_is_inside(t, 1) || tile_not_rock(t);
            build_planner::draw_flat_tile(ctx, pixel, bad ? COLOR_MASK_RED_30 : COLOR_MASK_GREEN_30);
        }
    }
}

void pharos_add_rect_tiles(int building_id, tile2i tile, int w, int h, int image_id) {
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
            // Rock is not CLEARABLE — strip it explicitly so the footprint becomes BUILDING.
            map_terrain_remove(grid_offset, TERRAIN_CLEARABLE | TERRAIN_ROCK);
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

} // namespace

void building_pharos_lighthouse::static_params::rebuild_construction() {
    monument &m = g_monument_pharos_lighthouse;
    m.btype = BUILDING_PHAROS_LIGHTHOUSE;
    m.phases.clear();

    // 0–1: Work Camp clearing rock island pad (foreman 132).
    m.phases.push_back({0, monument_phase_resource{ARCHITECTS, 1}});
    m.phases.push_back({1, monument_phase_resource{ARCHITECTS, 1}});

    const uint16_t marble_a = load_at(marble_loads, 0);
    const uint16_t marble_b = load_at(marble_loads, 1);
    const uint16_t marble_c = load_at(marble_loads, 2);
    const uint16_t marble_d = load_at(marble_loads, 3);
    const uint16_t marble_e = load_at(marble_loads, 4);
    const uint16_t timber_foundation = load_at(timber_loads, 0);
    const uint16_t timber_tier1 = load_at(timber_loads, 1);
    const uint16_t timber_octagon = load_at(timber_loads, 2);

    // 2: foundation (133) — marble + early scaffold
    m.phases.push_back({2, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_MARBLE, marble_a}, {RESOURCE_TIMBER, timber_foundation}});
    // 3: parquet floor (134)
    m.phases.push_back({3, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_MARBLE, marble_b}});
    // 4: first (square) tier (135)
    m.phases.push_back({4, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_MARBLE, marble_c}, {RESOURCE_TIMBER, timber_tier1}});
    // 5: octagonal tier (136)
    m.phases.push_back({5, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_MARBLE, marble_d}, {RESOURCE_TIMBER, timber_octagon}});
    // 6: cupola (137)
    m.phases.push_back({6, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_MARBLE, marble_e}});
    // 7: scaffolding removed (138–139) — carpenters (no timber consume; need_carpenter override)
    m.phases.push_back({7, monument_phase_resource{ARCHITECTS, 1}});
    // 8: finish sentinel
    m.phases.push_back({8, monument_phase_resource{RESOURCE_NONE, 0}});
}

void building_pharos_lighthouse::static_params::archive_load(archive /*arch*/) {
    rebuild_construction();
}

const monument &building_pharos_lighthouse::config() const {
    return g_monument_pharos_lighthouse;
}

bool building_pharos_lighthouse::has_unfinished_pharos_lighthouse() {
    return building_monument_has_unfinished({BUILDING_PHAROS_LIGHTHOUSE});
}

vec2i building_pharos_lighthouse::footprint_size() const {
    const auto &bp = current_params();
    vec2i ft = bp.init_tiles;
    if (ft.x <= 0 || ft.y <= 0) {
        ft = {6, 6};
    }
    return ft;
}

int building_pharos_lighthouse::art_stage() const {
    const auto &bp = current_params();
    const int max_stage = bp.art_stages > 0 ? bp.art_stages : 9;
    const int p = runtime_data().phase;
    if (p == MONUMENT_FINISHED) {
        return max_stage; // LtHouse9
    }
    if (p <= 1) {
        return 1;
    }
    if (p >= 7) {
        return std::min(7, max_stage); // scaffold off → LtHouse7
    }
    // phases 2–6 → art 2–6
    return std::min(p, max_stage);
}

xstring building_pharos_lighthouse::anim_key_for(int stage) const {
    const auto &bp = current_params();
    const int max_stage = bp.art_stages > 0 ? bp.art_stages : 9;
    if (stage < 1) {
        stage = 1;
    }
    if (stage > max_stage) {
        stage = max_stage;
    }
    bstring32 key;
    key.printf("s%c", 'a' + (stage - 1));
    return xstring(key.c_str());
}

bool building_pharos_lighthouse::needs_resources() const {
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

bool building_pharos_lighthouse::need_stonemason() {
    if (is_finished()) {
        return false;
    }
    scrub_dead_workers(runtime_data().workers);
    const int p = runtime_data().phase;
    // Mason work: foundation through cupola (2–6). Phase 7 = carpenter scaffold teardown.
    if (p < 2 || p > 6) {
        return false;
    }
    if (!need_workers()) {
        return false;
    }
    for (auto wid : runtime_data().workers) {
        figure *f = wid > 0 ? figure_get(wid) : nullptr;
        if (f && f->is_alive() && f->type == FIGURE_STONEMASON) {
            return false;
        }
    }
    return true;
}

bool building_pharos_lighthouse::need_carpenter() {
    if (is_finished()) {
        return false;
    }
    scrub_dead_workers(runtime_data().workers);
    const int p = runtime_data().phase;
    // Timber phases use base logic; phase 7 teardown needs a carpenter with no timber consume.
    if (p == 7) {
        if (!need_workers()) {
            return false;
        }
        for (auto wid : runtime_data().workers) {
            figure *f = wid > 0 ? figure_get(wid) : nullptr;
            if (f && f->is_alive() && f->type == FIGURE_CARPENTER) {
                return false;
            }
        }
        return true;
    }
    return building_monument::need_carpenter();
}

bool building_pharos_lighthouse::need_workers() const {
    if (is_finished()) {
        return false;
    }
    for (auto wid : runtime_data().workers) {
        if (!worker_slot_occupied(wid)) {
            return true;
        }
    }
    return false;
}

void building_pharos_lighthouse::add_workers(figure_id fid) {
    auto &d = runtime_data();
    scrub_dead_workers(d.workers);
    for (auto &wid : d.workers) {
        if (wid == 0) {
            wid = fid;
            return;
        }
    }
}

void building_pharos_lighthouse::remove_worker(figure_id fid) {
    auto &d = runtime_data();
    for (auto &wid : d.workers) {
        if (wid == fid) {
            wid = 0;
            return;
        }
    }
}

int building_pharos_lighthouse::building_image_get() const {
    const xstring key = anim_key_for(art_stage());
    const auto &params = current_params();
    int img = params.first_img(key);
    if (img > 0) {
        return img;
    }
    return params.first_img("preview");
}

void building_pharos_lighthouse::preview::setup_preview_graphics(build_planner &planer) const {
    const auto &bp = building_pharos_lighthouse::current_params();
    const vec2i init_tiles = bp.init_tiles.x > 0 ? bp.init_tiles : vec2i{6, 6};
    planer.init_tiles(init_tiles.x, init_tiles.y);
}

uint32_t building_pharos_lighthouse::preview::ghost_ignore_terrain(build_planner & /*p*/, tile2i /*tile*/) const {
    return TERRAIN_ROCK;
}

int building_pharos_lighthouse::preview::can_place(build_planner &p, tile2i /*tile*/, tile2i end, int state) const {
    if (state != CAN_PLACE && state != CAN_NOT_BUT_GREEN) {
        return state;
    }
    if (has_unfinished_pharos_lighthouse()) {
        p.set_warning("#one_pharos_only");
        return CAN_NOT_PLACE;
    }
    const auto &bp = building_pharos_lighthouse::current_params();
    const vec2i ft = bp.init_tiles.x > 0 ? bp.init_tiles : vec2i{6, 6};
    if (area_not_all_rock(end, ft.x, ft.y)) {
        // CAN_NOT_BUT_GREEN → ghost_preview shows per-tile rock mask (help: all green).
        return CAN_NOT_BUT_GREEN;
    }
    return CAN_PLACE;
}

int building_pharos_lighthouse::preview::finalize_check(build_planner &p, tile2i tile, tile2i end, int state) const {
    state = building_planer_renderer::finalize_check(p, tile, end, state);
    if (state != CAN_PLACE) {
        return state;
    }
    if (has_unfinished_pharos_lighthouse()) {
        p.set_warning("#one_pharos_only");
        g_warning_manager.show("#one_pharos_only");
        return CAN_NOT_PLACE;
    }
    return can_place(p, tile, end, CAN_PLACE);
}

void building_pharos_lighthouse::preview::ghost_preview(build_planner &planer, painter &ctx, tile2i /*start*/, tile2i end, vec2i pixel) const {
    const auto &params = building_static_params::get(planer.build_type);
    const auto &bp = building_pharos_lighthouse::current_params();
    const vec2i ft = bp.init_tiles.x > 0 ? bp.init_tiles : vec2i{6, 6};

    if (has_unfinished_pharos_lighthouse()) {
        draw_rock_area_mask(ctx, end, ft.x, ft.y, true);
        return;
    }
    if (area_not_all_rock(end, ft.x, ft.y)) {
        draw_rock_area_mask(ctx, end, ft.x, ft.y, false);
        return;
    }

    const int preview = params.first_img("preview");
    const int img = params.first_img("sa");
    planer.draw_building_ghost(ctx, img > 0 ? img : preview, pixel);
}

void building_pharos_lighthouse::on_place_update_tiles(int orientation, int /*variant*/) {
    base.orientation = orientation;
    const vec2i ft = footprint_size();
    base.size = (uint8_t)std::max({ft.x, ft.y, 1});
    pharos_add_rect_tiles(id(), tile(), ft.x, ft.y, building_image_get());
    for (int dy = 0; dy < ft.y; dy++) {
        for (int dx = 0; dx < ft.x; dx++) {
            map_monuments_set_progress(tile().shifted(dx, dy), 0);
        }
    }
}

void building_pharos_lighthouse::on_place_checks() {
    construction_warnings warnings;
    const vec2i ft = footprint_size();
    int min_value = 12;
    int min_go = tile().grid_offset();
    const bool has_road = map_road_find_minimum_tile_xy(tile(), ft.x, ft.y, &min_value, &min_go) && min_value < 12;
    warnings.add_if(!has_road, "#needs_road_access");
}

xstring building_pharos_lighthouse::demolish_blocked_message() const {
    return "#pharos_not_demolishable";
}

void building_pharos_lighthouse::on_destroy() {
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

void building_pharos_lighthouse::on_phase_changed(int old_phase, int current) {
    const vec2i ft = footprint_size();
    pharos_add_rect_tiles(id(), tile(), ft.x, ft.y, building_image_get());

    if (current != MONUMENT_FINISHED) {
        auto &d = runtime_data();
        for (e_resource resource = RESOURCE_NONE; resource < RESOURCES_MAX; ++resource) {
            d.resources_pct[resource] = 0;
        }
    }

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

void building_pharos_lighthouse::update_day() {
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

    if (!needs_resources() && d.phase >= 2 && d.phase <= 6) {
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

    // Scaffold teardown (7): carpenters, not masons.
    if (!needs_resources() && d.phase == 7) {
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

void building_pharos_lighthouse::update_map_orientation(int /*map_orientation*/) {
    const vec2i ft = footprint_size();
    pharos_add_rect_tiles(id(), tile(), ft.x, ft.y, building_image_get());
}

tile2i building_pharos_lighthouse::center_point() const {
    const vec2i ft = footprint_size();
    return tile().shifted(ft.x / 2, ft.y / 2);
}

tile2i building_pharos_lighthouse::access_point() const {
    const vec2i ft = footprint_size();
    return tile().shifted(ft.x / 2, ft.y - 1);
}

grid_area building_pharos_lighthouse::get_area() const {
    const vec2i ft = footprint_size();
    tile2i start = tile();
    tile2i end = start.shifted(ft.x - 1, ft.y - 1);
    return {start, end};
}

void building_pharos_lighthouse::bind_dynamic(io_buffer *iob, size_t /*version*/) {
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

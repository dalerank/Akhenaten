#include "monument_royal_tomb.h"

#include "building/monuments.h"
#include "building/rotation.h"
#include "city/city.h"
#include "city/city_warnings.h"
#include "construction/build_planner.h"
#include "core/direction.h"
#include "figure/figure.h"
#include "figuretype/figure_stonemason.h"
#include "figuretype/figure_tomb_artisan.h"
#include "game/undo.h"
#include "graphics/color.h"
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

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_royal_tomb);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_medium_royal_tomb);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_large_royal_tomb);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_grand_royal_tomb);

static monument g_monument_small_royal_tomb{BUILDING_SMALL_ROYAL_TOMB};
static monument g_monument_medium_royal_tomb{BUILDING_MEDIUM_ROYAL_TOMB};
static monument g_monument_large_royal_tomb{BUILDING_LARGE_ROYAL_TOMB};
static monument g_monument_grand_royal_tomb{BUILDING_GRAND_ROYAL_TOMB};

static constexpr uint32_t k_cliff_terrain = TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP;

template <typename T>
static const building_royal_tomb::base_params &rt_base_params(const building_static_params &p) {
    return static_cast<const typename T::static_params &>(p);
}

const building_royal_tomb::base_params &building_royal_tomb::params_for(e_building_type type) {
    switch (type) {
    case BUILDING_SMALL_ROYAL_TOMB:
        return rt_base_params<building_small_royal_tomb>(building_static_params::get(type));
    case BUILDING_MEDIUM_ROYAL_TOMB:
        return rt_base_params<building_medium_royal_tomb>(building_static_params::get(type));
    case BUILDING_LARGE_ROYAL_TOMB:
        return rt_base_params<building_large_royal_tomb>(building_static_params::get(type));
    case BUILDING_GRAND_ROYAL_TOMB:
        return rt_base_params<building_grand_royal_tomb>(building_static_params::get(type));
    default:
        break;
    }
    static base_params dummy;
    return dummy;
}

const building_royal_tomb::base_params &building_royal_tomb::tomb_params() const {
    return params_for(type());
}

void building_royal_tomb::static_params::rebuild_construction(e_building_type type) {
    monument *m = nullptr;
    if (type == BUILDING_SMALL_ROYAL_TOMB) {
        m = &g_monument_small_royal_tomb;
    } else if (type == BUILDING_MEDIUM_ROYAL_TOMB) {
        m = &g_monument_medium_royal_tomb;
    } else if (type == BUILDING_LARGE_ROYAL_TOMB) {
        m = &g_monument_large_royal_tomb;
    } else if (type == BUILDING_GRAND_ROYAL_TOMB) {
        m = &g_monument_grand_royal_tomb;
    }
    if (!m) {
        return;
    }
    m->btype = type;
    m->phases.clear();

    const int stages = art_stages > 0 ? art_stages : 9;
    for (int i = 0; i < stages; ++i) {
        const uint16_t lamps = (i < (int)lamp_loads.size()) ? lamp_loads[i] : 0;
        const uint16_t clay = (i < (int)clay_loads.size()) ? clay_loads[i] : 0;
        const uint16_t paint = (i < (int)paint_loads.size()) ? paint_loads[i] : 0;

        monument_phase ph{};
        ph.id = (uint8_t)i;
        int ri = 0;
        ph.resources[ri++] = {ARCHITECTS, 1};
        if (lamps > 0 && ri < (int)ph.resources.size()) {
            ph.resources[ri++] = {RESOURCE_LAMPS, lamps};
        }
        if (clay > 0 && ri < (int)ph.resources.size()) {
            ph.resources[ri++] = {RESOURCE_CLAY, clay};
        }
        if (paint > 0 && ri < (int)ph.resources.size()) {
            ph.resources[ri++] = {RESOURCE_PAINT, paint};
        }
        m->phases.push_back(ph);
    }
    // Last art phase → set_phase(stages) == phases() → MONUMENT_FINISHED (no empty sentinel).
}

void building_small_royal_tomb::static_params::archive_load(archive /*arch*/) {
    rebuild_construction(BUILDING_SMALL_ROYAL_TOMB);
}

void building_medium_royal_tomb::static_params::archive_load(archive /*arch*/) {
    rebuild_construction(BUILDING_MEDIUM_ROYAL_TOMB);
}

void building_large_royal_tomb::static_params::archive_load(archive /*arch*/) {
    rebuild_construction(BUILDING_LARGE_ROYAL_TOMB);
}

void building_grand_royal_tomb::static_params::archive_load(archive /*arch*/) {
    rebuild_construction(BUILDING_GRAND_ROYAL_TOMB);
}

const monument &building_small_royal_tomb::config() const {
    return g_monument_small_royal_tomb;
}

const monument &building_medium_royal_tomb::config() const {
    return g_monument_medium_royal_tomb;
}

const monument &building_large_royal_tomb::config() const {
    return g_monument_large_royal_tomb;
}

const monument &building_grand_royal_tomb::config() const {
    return g_monument_grand_royal_tomb;
}

static vec2i rt_entrance_size(vec2i entrance) {
    if (entrance.x > 0 && entrance.y > 0) {
        return entrance;
    }
    return {1, 1};
}

static vec2i rt_oriented_bulk(vec2i init_tiles, int rotation) {
    if (init_tiles.x <= 0 || init_tiles.y <= 0) {
        init_tiles = {11, 20};
    }
    rotation %= 4;
    if (rotation == 1 || rotation == 3) {
        return {init_tiles.y, init_tiles.x};
    }
    return init_tiles;
}

static vec2i rt_total_size(vec2i bulk, vec2i entrance) {
    entrance = rt_entrance_size(entrance);
    return {bulk.x, bulk.y + entrance.y};
}

static tile2i rt_map_origin(tile2i end, vec2i total) {
    switch (g_camera.orientation) {
    case DIR_2_BOTTOM_RIGHT:
        return end.shifted(-total.x + 1, 0);
    case DIR_4_BOTTOM_LEFT:
        return end.shifted(-total.x + 1, -total.y + 1);
    case DIR_6_TOP_LEFT:
        return end.shifted(0, -total.y + 1);
    default:
        return end;
    }
}

static void rt_local_xy(tile2i tile, tile2i origin, int *dx, int *dy) {
    *dx = tile.x() - origin.x();
    *dy = tile.y() - origin.y();
}

static void rt_preview_geometry(e_building_type type, vec2i *bulk_out, vec2i *ent_out, vec2i *total_out) {
    const auto &bp = building_royal_tomb::params_for(type);
    const int rot = building_rotation_global_rotation() % 4;
    *bulk_out = rt_oriented_bulk(bp.init_tiles, rot);
    *ent_out = rt_entrance_size(bp.entrance_size);
    *total_out = rt_total_size(*bulk_out, *ent_out);
}

bool building_royal_tomb::is_bulk_local(int dx, int dy, vec2i bulk) {
    return dx >= 0 && dy >= 0 && dx < bulk.x && dy < bulk.y;
}

bool building_royal_tomb::is_entrance_local(int dx, int dy, vec2i bulk, vec2i entrance) {
    entrance = rt_entrance_size(entrance);
    if (entrance.x > bulk.x) {
        return false;
    }
    const int x0 = (bulk.x - entrance.x) / 2;
    const int y0 = bulk.y;
    return dx >= x0 && dx < x0 + entrance.x && dy >= y0 && dy < y0 + entrance.y;
}

bool building_royal_tomb::is_padding_local(int dx, int dy, vec2i bulk, vec2i entrance) {
    entrance = rt_entrance_size(entrance);
    if (dy < bulk.y || dy >= bulk.y + entrance.y) {
        return false;
    }
    return !is_entrance_local(dx, dy, bulk, entrance);
}

bool building_royal_tomb::has_unfinished_royal_tomb(e_building_type type) {
    return building_monument_has_unfinished({type});
}

vec2i building_royal_tomb::bulk_size() const {
    return rt_oriented_bulk(tomb_params().init_tiles, base.orientation);
}

vec2i building_royal_tomb::total_size() const {
    return rt_total_size(bulk_size(), tomb_params().entrance_size);
}

int building_royal_tomb::art_stage() const {
    const auto &bp = tomb_params();
    const int max_stage = bp.art_stages > 0 ? bp.art_stages : 9;
    const int p = runtime_data().phase;
    if (p == MONUMENT_FINISHED || p >= max_stage) {
        return max_stage;
    }
    if (p < 1) {
        return 1;
    }
    return std::min(p + 1, max_stage);
}

xstring building_royal_tomb::anim_key_for(int stage) const {
    const auto &bp = tomb_params();
    const int max_stage = bp.art_stages > 0 ? bp.art_stages : 9;
    if (stage < 1) {
        stage = 1;
    }
    if (stage > max_stage) {
        stage = max_stage;
    }
    bstring32 key;
    if (is_finished()) {
        return xstring("finish");
    }
    key.printf("s%c", 'a' + (stage - 1));
    return xstring(key.c_str());
}

bool building_royal_tomb::needs_resources() const {
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

int building_royal_tomb::lamp_stock_room() const {
    if (is_finished()) {
        return 0;
    }
    // Yards only top up stock once carving begins; phase-0 leftovers still accept via deliver_resource.
    if (runtime_data().phase < 1) {
        return 0;
    }
    return std::max(0, k_lamp_stock_max - (int)runtime_data().lamp_stock);
}

int building_royal_tomb::accept_lamp_stock(int amount) {
    if (amount <= 0 || is_finished()) {
        return 0;
    }
    // Stock top-up from yards starts at phase≥1 (lamp_stock_room); leftover from a
    // phase-0 sled that overshoots the 400 gate must still land in stock or lamps vanish.
    auto &d = runtime_data();
    const int room = k_lamp_stock_max - (int)d.lamp_stock;
    if (room <= 0) {
        return 0;
    }
    const int added = std::min(amount, room);
    d.lamp_stock = (uint16_t)(d.lamp_stock + added);
    return added;
}

bool building_royal_tomb::deliver_resource(e_resource resource, int amount) {
    if (resource != RESOURCE_LAMPS || amount <= 0) {
        return building_monument::deliver_resource(resource, amount);
    }

    // Phase need first (help 478 / lamp_loads), leftover maintains working stock ≤700.
    const int phase_need = building_monument::needs_resource(RESOURCE_LAMPS);
    auto &d = runtime_data();
    int accepted = 0;
    if (phase_need > 0 && d.resources_pct[RESOURCE_LAMPS] < 100) {
        const int on_site = phase_need * (int)d.resources_pct[RESOURCE_LAMPS] / 100;
        const int phase_remaining = std::max(0, phase_need - on_site);
        const int to_phase = std::min(amount, phase_remaining);
        if (to_phase > 0 && building_monument::deliver_resource(RESOURCE_LAMPS, to_phase)) {
            accepted += to_phase;
        }
        const int leftover = amount - to_phase;
        if (leftover > 0) {
            accepted += accept_lamp_stock(leftover);
        }
        return accepted > 0;
    }
    return accept_lamp_stock(amount) > 0;
}

bool building_royal_tomb::need_stonemason() {
    if (is_finished() || runtime_data().phase < 1) {
        return false;
    }
    // Free slot required — without it guilds spawn walkers that add_workers drops.
    if (!need_workers()) {
        return false;
    }
    const int max_masons = std::max(1, (int)tomb_params().max_masons);
    int masons = 0;
    for (auto wid : runtime_data().workers) {
        figure *f = wid > 0 ? figure_get(wid) : nullptr;
        if (f && f->is_alive() && f->type == FIGURE_STONEMASON) {
            masons++;
        }
    }
    return masons < max_masons;
}

bool building_royal_tomb::need_artisan() {
    // My Palace: Stairway onward needs artisans (after Help-478 lamp gate = phase 0).
    if (is_finished() || runtime_data().phase < 1) {
        return false;
    }
    if (!need_workers()) {
        return false;
    }
    const int max_artisans = std::max(1, (int)tomb_params().max_artisans);
    int artisans = 0;
    for (auto wid : runtime_data().workers) {
        figure *f = wid > 0 ? figure_get(wid) : nullptr;
        if (f && f->is_alive() && f->type == FIGURE_TOMB_ARTISAN) {
            artisans++;
        }
    }
    return artisans < max_artisans;
}

bool building_royal_tomb::need_workers() {
    return static_cast<const building_royal_tomb *>(this)->need_workers();
}

bool building_royal_tomb::need_workers() const {
    if (is_finished()) {
        return false;
    }
    // Match building_monument / mastaba: true iff a free worker slot exists.
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

void building_royal_tomb::add_workers(figure_id fid) {
    for (auto &wid : runtime_data().workers) {
        if (!wid) {
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

void building_royal_tomb::remove_worker(figure_id fid) {
    for (auto &wid : runtime_data().workers) {
        if (wid == fid) {
            wid = 0;
            return;
        }
    }
}

int building_royal_tomb::building_image_get() const {
    const auto &params = building_static_params::get(type());
    int img = params.first_img(anim_key_for(art_stage()));
    if (img > 0) {
        return img;
    }
    img = params.first_img("preview");
    if (img > 0) {
        return img;
    }
    return params.first_img("sa");
}

static void rt_add_tile(int building_id, tile2i origin, int dx, int dy, int image_id, bool is_main) {
    tile2i t = origin.shifted(dx, dy);
    if (!map_grid_is_inside(t, 1)) {
        return;
    }
    const int grid_offset = t.grid_offset();
    map_terrain_remove(grid_offset, TERRAIN_CLEARABLE);
    map_terrain_add(grid_offset, TERRAIN_BUILDING);
    map_building_set(grid_offset, building_id);
    map_property_clear_constructing(grid_offset);
    map_property_set_multi_tile_size(grid_offset, 1);
    map_image_set(grid_offset, image_id);
    map_property_set_multi_tile_xy(grid_offset, dx, dy, is_main);
}

static void rt_place_tiles(int building_id, tile2i origin, vec2i bulk, vec2i entrance, int image_id, int entrance_img) {
    entrance = rt_entrance_size(entrance);
    for (int dy = 0; dy < bulk.y; dy++) {
        for (int dx = 0; dx < bulk.x; dx++) {
            const bool is_main = dx == 0 && dy == 0;
            rt_add_tile(building_id, origin, dx, dy, is_main ? image_id : 0, is_main);
        }
    }
    const int x0 = (bulk.x - entrance.x) / 2;
    for (int dy = 0; dy < entrance.y; dy++) {
        for (int dx = 0; dx < entrance.x; dx++) {
            rt_add_tile(building_id, origin, x0 + dx, bulk.y + dy, entrance_img, false);
        }
    }
    map_property_mark_draw_tile(origin.grid_offset());
}

static int rt_entrance_img(e_building_type type) {
    return building_static_params::get(type).first_img("entrance");
}

static bool rt_tile_is_cliff(tile2i t) {
    return map_terrain_is(t, k_cliff_terrain);
}

static int rt_validate_cliff_entrance(tile2i origin, vec2i bulk, vec2i entrance, xstring *warning_out) {
    entrance = rt_entrance_size(entrance);
    const vec2i total = rt_total_size(bulk, entrance);
    bool missing_cliff = false;
    bool bad_entrance = false;
    for (int dy = 0; dy < total.y; dy++) {
        for (int dx = 0; dx < total.x; dx++) {
            if (building_royal_tomb::is_padding_local(dx, dy, bulk, entrance)) {
                continue;
            }
            tile2i t = origin.shifted(dx, dy);
            if (!map_grid_is_inside(t, 1)) {
                if (building_royal_tomb::is_entrance_local(dx, dy, bulk, entrance)) {
                    bad_entrance = true;
                } else {
                    missing_cliff = true;
                }
                continue;
            }
            if (building_royal_tomb::is_entrance_local(dx, dy, bulk, entrance)) {
                if (map_terrain_is(t, TERRAIN_NOT_CLEAR)) {
                    bad_entrance = true;
                }
            } else if (!rt_tile_is_cliff(t)) {
                missing_cliff = true;
            }
        }
    }
    if (missing_cliff) {
        if (warning_out) {
            *warning_out = "#must_be_over_cliffs";
        }
        return CAN_NOT_PLACE;
    }
    if (bad_entrance) {
        if (warning_out) {
            *warning_out = "#entrance_on_clear_land";
        }
        return CAN_NOT_PLACE;
    }
    return CAN_PLACE;
}

void building_royal_tomb::preview::setup_preview_graphics(build_planner &planer) const {
    vec2i bulk, ent, total;
    rt_preview_geometry(planer.build_type, &bulk, &ent, &total);
    const int cam = g_camera.orientation / 2;
    if (cam == 1 || cam == 3) {
        planer.init_tiles(total.y, total.x);
    } else {
        planer.init_tiles(total.x, total.y);
    }
}

uint32_t building_royal_tomb::preview::ghost_ignore_terrain(build_planner &p, tile2i tile) const {
    vec2i bulk, ent, total;
    rt_preview_geometry(p.build_type, &bulk, &ent, &total);
    const tile2i origin = rt_map_origin(p.end, total);
    int dx = 0, dy = 0;
    rt_local_xy(tile, origin, &dx, &dy);
    if (dx < 0 || dy < 0 || dx >= total.x || dy >= total.y) {
        return 0;
    }
    if (building_royal_tomb::is_padding_local(dx, dy, bulk, ent)) {
        return TERRAIN_NOT_CLEAR;
    }
    if (building_royal_tomb::is_entrance_local(dx, dy, bulk, ent)) {
        return 0;
    }
    return k_cliff_terrain;
}

bool building_royal_tomb::preview::ghost_allow_tile(build_planner &p, tile2i tile) const {
    vec2i bulk, ent, total;
    rt_preview_geometry(p.build_type, &bulk, &ent, &total);
    const tile2i origin = rt_map_origin(p.end, total);
    int dx = 0, dy = 0;
    rt_local_xy(tile, origin, &dx, &dy);
    if (dx >= 0 && dy >= 0 && dx < total.x && dy < total.y
        && building_royal_tomb::is_padding_local(dx, dy, bulk, ent)) {
        return true;
    }
    return building_planer_renderer::ghost_allow_tile(p, tile);
}

int building_royal_tomb::preview::construction_place(build_planner &planer, tile2i /*start*/, tile2i end, int orientation, int variant) const {
    vec2i bulk, ent, total;
    rt_preview_geometry(planer.build_type, &bulk, &ent, &total);
    end = rt_map_origin(end, total);

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

int building_royal_tomb::preview::can_place(build_planner &p, tile2i /*tile*/, tile2i end, int state) const {
    if (state != CAN_PLACE && state != CAN_NOT_BUT_GREEN) {
        return state;
    }
    if (has_unfinished_royal_tomb(p.build_type)) {
        p.set_warning("#only_one_building_of_this_type");
        return CAN_NOT_PLACE;
    }
    vec2i bulk, ent, total;
    rt_preview_geometry(p.build_type, &bulk, &ent, &total);
    const tile2i origin = rt_map_origin(end, total);
    xstring warn;
    const int cliff_state = rt_validate_cliff_entrance(origin, bulk, ent, &warn);
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

int building_royal_tomb::preview::finalize_check(build_planner &p, tile2i tile, tile2i end, int state) const {
    state = building_planer_renderer::finalize_check(p, tile, end, state);
    if (state != CAN_PLACE) {
        return state;
    }
    if (has_unfinished_royal_tomb(p.build_type)) {
        p.set_warning("#only_one_building_of_this_type");
        g_warning_manager.show("#only_one_building_of_this_type");
        return CAN_NOT_PLACE;
    }
    vec2i bulk, ent, total;
    rt_preview_geometry(p.build_type, &bulk, &ent, &total);
    const tile2i origin = rt_map_origin(end, total);
    xstring warn;
    const int cliff_state = rt_validate_cliff_entrance(origin, bulk, ent, &warn);
    if (cliff_state != CAN_PLACE) {
        if (!warn.empty()) {
            p.set_warning(warn);
            g_warning_manager.show(warn.c_str());
        }
        return CAN_NOT_PLACE;
    }
    return CAN_PLACE;
}

void building_royal_tomb::preview::ghost_preview(build_planner &planer, painter &ctx, tile2i /*start*/, tile2i end, vec2i /*pixel*/) const {
    const auto &params = building_static_params::get(planer.build_type);
    vec2i bulk, ent, total;
    rt_preview_geometry(planer.build_type, &bulk, &ent, &total);
    tile2i origin = rt_map_origin(end, total);

    const bool force_red = has_unfinished_royal_tomb(planer.build_type);
    bool any_blocked = force_red;
    for (int dy = 0; dy < total.y && !any_blocked; dy++) {
        for (int dx = 0; dx < total.x; dx++) {
            if (building_royal_tomb::is_padding_local(dx, dy, bulk, ent)) {
                continue;
            }
            tile2i t = origin.shifted(dx, dy);
            const bool is_ent = building_royal_tomb::is_entrance_local(dx, dy, bulk, ent);
            bool tile_blocked = !map_grid_is_inside(t, 1) || map_has_figure_at(t);
            if (is_ent) {
                tile_blocked = tile_blocked || map_terrain_is(t, TERRAIN_NOT_CLEAR);
            } else {
                const uint32_t mask = TERRAIN_NOT_CLEAR & ~k_cliff_terrain;
                tile_blocked = tile_blocked || map_terrain_is(t, mask) || !rt_tile_is_cliff(t);
            }
            if (tile_blocked) {
                any_blocked = true;
                break;
            }
        }
    }

    if (any_blocked) {
        for (int dy = 0; dy < total.y; dy++) {
            for (int dx = 0; dx < total.x; dx++) {
                if (building_royal_tomb::is_padding_local(dx, dy, bulk, ent)) {
                    continue;
                }
                tile2i t = origin.shifted(dx, dy);
                vec2i px = g_camera.lookup_tile_to_pixel(t);
                const bool is_ent = building_royal_tomb::is_entrance_local(dx, dy, bulk, ent);
                bool tile_blocked = force_red || !map_grid_is_inside(t, 1) || map_has_figure_at(t);
                if (!force_red) {
                    if (is_ent) {
                        tile_blocked = tile_blocked || map_terrain_is(t, TERRAIN_NOT_CLEAR);
                    } else {
                        const uint32_t mask = TERRAIN_NOT_CLEAR & ~k_cliff_terrain;
                        tile_blocked = tile_blocked || map_terrain_is(t, mask) || !rt_tile_is_cliff(t);
                    }
                }
                build_planner::draw_flat_tile(ctx, px, tile_blocked ? COLOR_MASK_RED_30 : COLOR_MASK_GREEN_30);
            }
        }
        return;
    }

    const int preview = params.first_img("preview");
    const int img = params.first_img("sa");
    const vec2i origin_pixel = g_camera.lookup_tile_to_pixel(origin);
    planer.draw_building_ghost(ctx, img > 0 ? img : preview, origin_pixel);
}

void building_royal_tomb::on_place_update_tiles(int orientation, int /*variant*/) {
    // Prefer explicit place/carry orientation; fall back to global rotation (ghost click).
    if (orientation < 0) {
        orientation = building_rotation_global_rotation();
    }
    base.orientation = (uint8_t)(orientation % 4);
    const vec2i total = total_size();
    base.size = (uint8_t)std::max({total.x, total.y, 1});
    const auto &bp = tomb_params();
    rt_place_tiles(id(), tile(), bulk_size(), bp.entrance_size, building_image_get(), rt_entrance_img(type()));
    const vec2i bulk = bulk_size();
    const vec2i ent = rt_entrance_size(bp.entrance_size);
    for (int dy = 0; dy < total.y; dy++) {
        for (int dx = 0; dx < total.x; dx++) {
            if (is_padding_local(dx, dy, bulk, ent)) {
                continue;
            }
            map_monuments_set_progress(tile().shifted(dx, dy), 0);
        }
    }
}

void building_royal_tomb::on_place_checks() {
    construction_warnings warnings;
    const vec2i total = total_size();
    int min_value = 12;
    int min_go = tile().grid_offset();
    const bool has_road = map_road_find_minimum_tile_xy(tile(), total.x, total.y, &min_value, &min_go) && min_value < 12;
    warnings.add_if(!has_road, "#needs_road_access");
}

void building_royal_tomb::on_destroy() {
    building_monument_remove_all_deliveries(id());
    const vec2i total = total_size();
    for (int dy = 0; dy < total.y; dy++) {
        for (int dx = 0; dx < total.x; dx++) {
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

void building_royal_tomb::on_phase_changed(int /*old_phase*/, int current) {
    const auto &bp = tomb_params();
    rt_place_tiles(id(), tile(), bulk_size(), bp.entrance_size, building_image_get(), rt_entrance_img(type()));
    if (current != MONUMENT_FINISHED) {
        auto &d = runtime_data();
        for (e_resource resource = RESOURCE_NONE; resource < RESOURCES_MAX; ++resource) {
            d.resources_pct[resource] = 0;
        }
    }
}

static bool rt_mason_onsite(figure *f) {
    if (!f || !f->is_alive() || f->type != FIGURE_STONEMASON) {
        return false;
    }
    // Mastaba tile-work OR sphinx/royal on-site linger (ACTION_17).
    const int a = f->action_state;
    return a == FIGURE_ACTION_14_MASON_WORK_GROUND
        || a == FIGURE_ACTION_17_MASON_LOOKING_FOR_WORK_TILE
        || a == FIGURE_ACTION_12_MASON_GOING_TO_PLACE
        || a == FIGURE_ACTION_15_MASON_WORK_WALL;
}

static bool rt_artisan_onsite(figure *f) {
    return f && f->is_alive() && f->type == FIGURE_TOMB_ARTISAN
        && f->action_state == ACTION_14_TOMB_ARTISAN_WORK;
}

void building_royal_tomb::update_day() {
    building_impl::update_day();
    if (is_finished()) {
        return;
    }
    auto &d = runtime_data();
    for (auto &wid : d.workers) {
        if (!wid) {
            continue;
        }
        figure *f = figure_get(wid);
        if (!f || !f->is_alive()) {
            wid = 0;
        }
    }
    if (needs_resources()) {
        return;
    }
    // Phase 0 = lamp delivery only. Later phases need living guild workers on site
    // (∥ Abu Simbel / mausoleum) — otherwise the tomb finishes with no guilds.
    if (d.phase >= 1) {
        bool has_mason = false;
        bool has_artisan = false;
        for (auto wid : d.workers) {
            figure *f = wid > 0 ? figure_get(wid) : nullptr;
            if (rt_mason_onsite(f)) {
                has_mason = true;
            }
            if (rt_artisan_onsite(f)) {
                has_artisan = true;
            }
        }
        if (!has_mason) {
            return;
        }
        if (!has_artisan) {
            return;
        }
        // My Palace: masons/artisans burn lamps from the tomb stock while carving.
        if (d.lamp_stock <= 0) {
            return;
        }
        d.lamp_stock--;
    }
    progress();
}

void building_royal_tomb::update_map_orientation(int /*map_orientation*/) {
    const auto &bp = tomb_params();
    rt_place_tiles(id(), tile(), bulk_size(), bp.entrance_size, building_image_get(), rt_entrance_img(type()));
}

tile2i building_royal_tomb::center_point() const {
    const vec2i bulk = bulk_size();
    return tile().shifted(bulk.x / 2, bulk.y / 2);
}

tile2i building_royal_tomb::access_point() const {
    const vec2i bulk = bulk_size();
    const vec2i ent = rt_entrance_size(tomb_params().entrance_size);
    const int x0 = (bulk.x - ent.x) / 2;
    return tile().shifted(x0 + ent.x / 2, bulk.y + ent.y / 2);
}

grid_area building_royal_tomb::get_area() const {
    const vec2i total = total_size();
    tile2i start = tile();
    tile2i end = start.shifted(total.x - 1, total.y - 1);
    return {start, end};
}

void building_royal_tomb::bind_dynamic(io_buffer *iob, size_t /*version*/) {
    auto &monumentd = runtime_data();

    iob->bind(BIND_SIGNATURE_UINT16, &monumentd.lamp_stock);
    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &monumentd.burial_stock[i]);
    }
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

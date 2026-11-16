#include "monument_caesareum.h"

#include "building/monuments.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_message.h"
#include "construction/build_planner.h"
#include "figure/figure.h"
#include "figuretype/figure_carpenter.h"
#include "figuretype/figure_stonemason.h"
#include "game/undo.h"
#include "graphics/color.h"
#include "graphics/view/lookup.h"
#include "graphics/view/view.h"
#include "grid/building_tiles.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "js/js_game.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_caesareum);
BUILDING_RUNTIME_DATA_IMPL(building_caesareum)

namespace {
    enum : uint32_t {
        SPOT_WORK_UNSET = 0xFFFF,
        // OG BUILDING_MAP_EDGE_MARGIN for site buildings.
        MAP_EDGE_MARGIN = 3,
        // OG TERRAIN_BLOCKS_MONUMENT: everything but shrub, groundwater, meadow and the well/irrigation ranges.
        TERRAIN_BLOCKS_MONUMENT = 0xFEFFD76F,
    };

    struct monument_caesareum_cfg : public monument {
        monument_caesareum_cfg() : monument{BUILDING_CAESAREUM} {
            for (uint8_t i = 0; i < building_caesareum::STAGE_COMPLETE; ++i) {
                phases.push_back({i, monument_phase_resource{ARCHITECTS, 1}});
            }
        }
    } g_monument_caesareum;

    const building_caesareum::base_params &caesareum_params() {
        return (const building_caesareum::base_params &)building_caesareum::current_params();
    }

    int camera_view() {
        return (g_camera.orientation / 2) & 3;
    }

    tile2i part_offset(int part) {
        return tile2i(building_caesareum::PART_SIZE * (part / 3), building_caesareum::PART_SIZE * (part % 3));
    }

    tile2i origin_from_center(tile2i center) {
        return center.shifted(-building_caesareum::SITE_HALF, -building_caesareum::SITE_HALF);
    }

    bool site_tile_blocked(tile2i tile) {
        const auto *map = scenario_map_data();
        if (tile.x() < MAP_EDGE_MARGIN || tile.y() < MAP_EDGE_MARGIN || tile.x() >= map->width - MAP_EDGE_MARGIN
            || tile.y() >= map->height - MAP_EDGE_MARGIN) {
            return true;
        }
        return map_terrain_is(tile, TERRAIN_BLOCKS_MONUMENT);
    }

    bool collect_site(tile2i origin, std::array<blocked_tile_vec, building_caesareum::PARTS> &parts) {
        bool blocked = false;
        for (int p = 0; p < building_caesareum::PARTS; ++p) {
            const tile2i off = part_offset(p);
            tile2i po = origin.shifted(off.x(), off.y());
            for (int dy = 0; dy < building_caesareum::PART_SIZE; ++dy) {
                for (int dx = 0; dx < building_caesareum::PART_SIZE; ++dx) {
                    const tile2i t = po.shifted(dx, dy);
                    const bool b = site_tile_blocked(t);
                    parts[p].push_back({t, b});
                    blocked |= b;
                }
            }
        }
        return blocked;
    }

    bool site_contains(tile2i origin, tile2i tile) {
        const int dx = tile.x() - origin.x();
        const int dy = tile.y() - origin.y();
        return dx >= 0 && dy >= 0 && dx < building_caesareum::SITE_SIZE && dy < building_caesareum::SITE_SIZE;
    }

    // OG monument_spot_animate detaches a spot once its figure changes action; only working figures hold one.
    bool figure_still_working(uint16_t fid) {
        if (!fid) {
            return false;
        }
        figure *f = figure_get(fid);
        if (!f || !f->is_alive()) {
            return false;
        }
        building *dest = f->destination();
        if (!dest || dest->type != BUILDING_CAESAREUM) {
            return false;
        }
        return (f->type == FIGURE_STONEMASON && f->action_state == ACTION_9_MASON_WORK_OBELISK)
               || (f->type == FIGURE_CARPENTER && f->action_state == ACTION_2_CARPENTER_WORK);
    }

    bool any_caesareum_placed() {
        return g_city.buildings.count_total(BUILDING_CAESAREUM) > 0;
    }
} // namespace

void building_caesareum::static_params::archive_load(archive /*arch*/) {
}

const monument &building_caesareum::config() const {
    return g_monument_caesareum;
}

// OG caesareum_get_image: the part images rotate with the camera view.
int building_caesareum::view_part(int part, int view) {
    static const int table[4][PARTS] = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8},
        {2, 5, 8, 1, 4, 7, 0, 3, 6},
        {8, 7, 6, 5, 4, 3, 2, 1, 0},
        {6, 3, 0, 7, 4, 1, 8, 5, 2},
    };
    return table[view & 3][std::clamp(part, 0, PARTS - 1)];
}

building_caesareum *building_caesareum::main_caesareum() {
    building_impl *m = main();
    auto *c = m ? m->dcast_caesareum() : nullptr;
    return c ? c : this;
}

const building_caesareum *building_caesareum::main_caesareum() const {
    return const_cast<building_caesareum *>(this)->main_caesareum();
}

building_caesareum *building_caesareum::part(int index) {
    building_caesareum *p = main_caesareum();
    for (int i = 0; p && i < index; ++i) {
        p = p->has_next() ? p->next()->dcast_caesareum() : nullptr;
    }
    return p;
}

const building_caesareum *building_caesareum::part(int index) const {
    return const_cast<building_caesareum *>(this)->part(index);
}

int building_caesareum::stage() const {
    const int p = main_caesareum()->runtime_data().phase;
    if (p == MONUMENT_FINISHED || p >= STAGE_COMPLETE) {
        return STAGE_COMPLETE;
    }
    return std::max(p, 0);
}

int building_caesareum::spot_attached(int spot) const {
    const building_caesareum *p = part(spot / SPOTS_PER_PART);
    return p ? p->runtime_data().spot_figure[spot % SPOTS_PER_PART] : 0;
}

int building_caesareum::spot_work_left(int spot) const {
    const building_caesareum *p = part(spot / SPOTS_PER_PART);
    return p ? p->runtime_data().spot_work[spot % SPOTS_PER_PART] : 0;
}

void building_caesareum::set_spot(int spot, uint16_t work, uint16_t fid) {
    building_caesareum *p = part(spot / SPOTS_PER_PART);
    if (!p) {
        return;
    }
    p->runtime_data().spot_work[spot % SPOTS_PER_PART] = work;
    p->runtime_data().spot_figure[spot % SPOTS_PER_PART] = fid;
}

void building_caesareum::reset_spots() {
    const auto &spots = caesareum_params().spots;
    for (int i = 0; i < PARTS * SPOTS_PER_PART; ++i) {
        const uint16_t work = i < (int)spots.size() ? spots[i].work : 0;
        set_spot(i, work, 0);
    }
}

int building_caesareum::find_free_spot(e_figure_type type) const {
    const auto &spots = caesareum_params().spots;
    const int s = stage();
    for (int i = 0; i < (int)spots.size(); ++i) {
        const auto &def = spots[i];
        if (def.stage != s || def.figure != type || spot_work_left(i) <= 0) {
            continue;
        }
        if (!figure_still_working(spot_attached(i))) {
            return i;
        }
    }
    return -1;
}

bool building_caesareum::has_free_spot(e_figure_type type) const {
    return !main_caesareum()->is_finished() && find_free_spot(type) >= 0;
}

figure_id building_caesareum::worker_figure_id() const {
    return main_caesareum()->runtime_data().workers[0];
}

// OG caesareum_part_has_active_worker: a stale slot is cleared as a side effect.
bool building_caesareum::part_has_active_worker() const {
    auto &workers = const_cast<building_caesareum *>(main_caesareum())->runtime_data().workers;
    const figure_id wid = workers[0];
    if (!wid) {
        return false;
    }
    figure *f = figure_get(wid);
    if (f && f->is_alive()) {
        const int action = f->action_state;
        switch (f->type) {
        case FIGURE_CARPENTER:
            if (action == ACTION_1_CARPENTER_GO_TO_SITE || action == ACTION_2_CARPENTER_WORK) {
                return true;
            }
            break;
        case FIGURE_STONEMASON:
            if (action == ACTION_0_MASON_CREATED || action == ACTION_1_MASON_GOING
                || action == ACTION_9_MASON_WORK_OBELISK || action == ACTION_19_MASON_WAIT_FOR_BLOCK) {
                return true;
            }
            break;
        default:
            break;
        }
    }
    workers[0] = 0;
    return false;
}

bool building_caesareum::claim_worker(figure &f) {
    building_caesareum *m = main_caesareum();
    if (m->is_finished()) {
        return false;
    }
    if (m->runtime_data().workers[0] == f.id) {
        return true;
    }
    if (part_has_active_worker() || !has_free_spot(f.type)) {
        return false;
    }
    m->runtime_data().workers[0] = f.id;
    f.roam_length = 0;
    f.wait_ticks = 0;
    return true;
}

bool building_caesareum::need_stonemason() {
    return is_main() && !is_finished() && !part_has_active_worker() && has_free_spot(FIGURE_STONEMASON);
}

bool building_caesareum::need_carpenter() {
    return is_main() && !is_finished() && !part_has_active_worker() && has_free_spot(FIGURE_CARPENTER);
}

bool building_caesareum::need_workers() const {
    return false;
}

bool building_caesareum::needs_resources() const {
    return false;
}

void building_caesareum::add_workers(figure_id fid) {
    figure *f = fid ? figure_get(fid) : nullptr;
    if (f) {
        claim_worker(*f);
    }
}

void building_caesareum::remove_worker(figure_id fid) {
    auto &workers = main_caesareum()->runtime_data().workers;
    if (workers[0] == fid) {
        workers[0] = 0;
    }
}

// OG caesareum_figure_work_tick_spot: one work unit per tick at the figure's spot of the current stage.
bool building_caesareum::work_tick(figure &f) {
    building_caesareum *m = main_caesareum();
    if (m != this) {
        return m->work_tick(f);
    }
    if (is_finished()) {
        return true;
    }

    const auto &spots = caesareum_params().spots;
    const int s = stage();
    const int count = (int)spots.size();
    int index = -1;
    // OG looks for the figure's own spot only from the index equal to the stage on.
    for (int i = s; i < count; ++i) {
        if (spot_attached(i) == f.id) {
            if (spots[i].stage != s) {
                return true;
            }
            index = i;
            break;
        }
    }
    if (index < 0) {
        index = find_free_spot(f.type);
        if (index < 0) {
            return true;
        }
    }

    const int left = std::max(0, spot_work_left(index) - 1);
    set_spot(index, (uint16_t)left, f.id);
    if (left > 0) {
        return false;
    }

    set_spot(index, 0, 0);
    bool stage_done = true;
    for (int i = 0; i < count; ++i) {
        if (spots[i].stage == s && spot_work_left(i) > 0) {
            stage_done = false;
            break;
        }
    }
    if (stage_done) {
        advance_stage();
    }
    runtime_data().workers[0] = 0;
    return true;
}

bool building_caesareum::sled_arrived() {
    auto &d = main_caesareum()->runtime_data();
    d.sleds++;
    if (d.sleds >= SLEDS_PER_STAGE) {
        d.sleds = 0;
        return true;
    }
    return false;
}

e_resource building_caesareum::block_resource() const {
    return stage() == STAGE_GRANITE ? RESOURCE_GRANITE : RESOURCE_MARBLE;
}

void building_caesareum::advance_stage() {
    const int s = stage();
    if (s >= STAGE_COMPLETE) {
        return;
    }
    const int next = s + 1;
    for (int i = 0; i < PARTS; ++i) {
        if (building_caesareum *p = part(i)) {
            p->set_phase(next >= STAGE_COMPLETE ? MONUMENT_FINISHED : next);
        }
    }
    refresh_part_images();
    if (next >= STAGE_COMPLETE) {
        messages::popup("caesareum_congratulations", 0, tile().grid_offset());
    }
}

void building_caesareum::set_stage(int target) {
    building_caesareum *m = main_caesareum();
    if (m != this) {
        m->set_stage(target);
        return;
    }
    target = std::clamp(target, 0, (int)STAGE_COMPLETE);
    for (int i = 0; i < PARTS; ++i) {
        if (building_caesareum *p = part(i)) {
            p->set_phase(target >= STAGE_COMPLETE ? MONUMENT_FINISHED : target);
        }
    }
    reset_spots();
    const auto &spots = caesareum_params().spots;
    for (int i = 0; i < (int)spots.size(); ++i) {
        if (spots[i].stage < target) {
            set_spot(i, 0, 0);
        }
    }
    runtime_data().sleds = 0;
    refresh_part_images();
}

// OG caesareum_get_progress.
int building_caesareum::get_progress(caesareum_progress *out) const {
    const building_caesareum *m = main_caesareum();
    const int s = stage();
    const int percent = (s >= STAGE_COMPLETE) ? 100 : (s * 5) + 5;
    caesareum_progress p;
    p.stage = s;
    p.percent = percent;
    if (m->part_has_active_worker()) {
        figure *f = figure_get(m->worker_figure_id());
        if (f->type == FIGURE_CARPENTER) {
            p.carpenters = 1;
        } else if (f->type == FIGURE_STONEMASON) {
            p.stonemasons = 1;
            p.stonemasons_waiting = f->action_state == ACTION_19_MASON_WAIT_FOR_BLOCK ? 1 : 0;
        }
    }
    p.material = std::max(0, (MATERIAL_LOADS - SLEDS_PER_STAGE * s) * MATERIAL_PER_LOAD);
    if (out) {
        *out = p;
    }
    return percent;
}

void building_caesareum::refresh_part_images() {
    for (int i = 0; i < PARTS; ++i) {
        if (building_caesareum *p = part(i)) {
            map_building_tiles_add(p->id(), p->tile(), PART_SIZE, p->building_image_get(), TERRAIN_BUILDING);
        }
    }
}

int building_caesareum::building_image_get() const {
    const auto &params = building_static_params::get(BUILDING_CAESAREUM);
    bstring32 key;
    key.printf("s%d", stage() + 1);
    const int img = params.first_img(xstring(key.c_str()));
    if (img <= 0) {
        return params.first_img("preview");
    }
    return img + view_part(part_index(), camera_view());
}

void building_caesareum::preview::setup_preview_graphics(build_planner &planer) const {
    planer.init_tiles(SITE_SIZE, SITE_SIZE);
    planer.pivot = {SITE_HALF, SITE_HALF};
}

int building_caesareum::preview::construction_place(build_planner &planer, tile2i /*start*/, tile2i end,
  int orientation, int variant) const {
    planer.last_created_building = nullptr;
    building *b = building_create(planer.build_type, origin_from_center(end), orientation);
    game_undo_add_building(b);
    if (b->id <= 0) {
        return 0;
    }
    add_building(b, orientation, variant);
    planer.last_created_building = b;
    return 1;
}

// OG caesareum_draw_placement: the bare footprint, each tile green or red.
void building_caesareum::preview::ghost_preview(build_planner &planer, painter &ctx, tile2i /*start*/, tile2i end,
  vec2i /*pixel*/) const {
    std::array<blocked_tile_vec, PARTS> parts;
    collect_site(origin_from_center(end), parts);
    for (const auto &p : parts) {
        planer.draw_partially_blocked(ctx, false, p);
    }
}

void building_caesareum::preview::ghost_blocked(build_planner &planer, painter &ctx, tile2i start, tile2i end,
  vec2i pixel, bool /*fully_blocked*/) const {
    ghost_preview(planer, ctx, start, end, pixel);
}

bool building_caesareum::preview::ghost_allow_tile(build_planner &planer, tile2i tile) const {
    if (!site_contains(origin_from_center(planer.end), tile)) {
        return true;
    }
    return !site_tile_blocked(tile);
}

uint32_t building_caesareum::preview::ghost_ignore_terrain(build_planner &planer, tile2i tile) const {
    return site_contains(origin_from_center(planer.end), tile) ? TERRAIN_NOT_CLEAR : 0;
}

int building_caesareum::preview::can_place(build_planner &planer, tile2i /*start*/, tile2i end, int state) const {
    if (state != CAN_PLACE && state != CAN_NOT_BUT_GREEN) {
        return state;
    }
    std::array<blocked_tile_vec, PARTS> parts;
    if (collect_site(origin_from_center(end), parts)) {
        planer.set_warning("#must_build_on_cleared_land");
        return CAN_NOT_PLACE;
    }
    if (any_caesareum_placed()) {
        planer.set_warning("#one_caesareum_only");
        return CAN_NOT_PLACE;
    }
    if (state == CAN_NOT_BUT_GREEN) {
        planer.set_warning("");
    }
    return CAN_PLACE;
}

void building_caesareum::create_parts(bool undo) {
    base.prev_part_building_id = 0;
    base.size = PART_SIZE;
    runtime_data().variant = 0;
    runtime_data().sleds = 0;

    building *prev = &base;
    for (int p = 1; p < PARTS; ++p) {
        const tile2i off = part_offset(p);
        building *b = building_create(BUILDING_CAESAREUM, tile().shifted(off.x(), off.y()), base.orientation);
        if (undo) {
            game_undo_add_building(b);
        }
        if (auto *c = b->dcast_caesareum()) {
            c->runtime_data().variant = (uint8_t)p;
            c->runtime_data().phase = runtime_data().phase;
        }
        b->prev_part_building_id = prev->id;
        b->next_part_building_id = 0;
        prev->next_part_building_id = b->id;
        prev = b;
    }
}

void building_caesareum::on_place_update_tiles(int orientation, int /*variant*/) {
    base.orientation = orientation;
    runtime_data().phase = 0;
    create_parts(true);
    reset_spots();
    refresh_part_images();
}

void building_caesareum::on_post_load() {
    building_monument::on_post_load();
    if (!is_main()) {
        return;
    }

    if (!has_next()) {
        // Saves before v201 kept the caesareum as one 15x15 record; split it and start over unless finished.
        if (!is_finished()) {
            runtime_data().phase = 0;
        }
        create_parts(false);
    }

    bool unset = false;
    for (int i = 0; i < PARTS * SPOTS_PER_PART; ++i) {
        unset |= spot_work_left(i) == SPOT_WORK_UNSET;
    }
    if (unset) {
        // Saves before v201 have no spot state: spots of past stages are done, the rest start over.
        set_stage(stage());
        return;
    }
    refresh_part_images();
}

void building_caesareum::on_phase_changed(int /*old_phase*/, int /*current*/) {
}

void building_caesareum::update_day() {
    building_impl::update_day();
}

// Rotation only reaches the main record (map_orientation_update_buildings), so it redraws all parts.
void building_caesareum::update_map_orientation(int /*map_orientation*/) {
    main_caesareum()->refresh_part_images();
}

grid_area building_caesareum::get_area() const {
    tile2i start = main_caesareum()->tile();
    return {start, start.shifted(SITE_SIZE - 1, SITE_SIZE - 1)};
}

tile2i building_caesareum::center_point() const {
    return main_caesareum()->tile().shifted(SITE_HALF, SITE_HALF);
}

// OG caesareum_get_work_tile: the entrance faces the camera, so the work tile turns with the view.
tile2i building_caesareum::access_point() const {
    tile2i t = main_caesareum()->tile();
    switch (camera_view()) {
    case 1:
        return t.shifted(-1, 8);
    case 2:
        return t.shifted(6, -1);
    case 3:
        return t.shifted(15, 6);
    default:
        return t.shifted(8, 15);
    }
}

void building_caesareum::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();

    // v201+: the 3 spots of this part (work, figure) and the sled count take 13 of the formerly skipped 38 bytes.
    if (version > 200) {
        for (int i = 0; i < SPOTS_PER_PART; i++) {
            iob->bind(BIND_SIGNATURE_UINT16, &d.spot_work[i]);
            iob->bind(BIND_SIGNATURE_UINT16, &d.spot_figure[i]);
        }
        iob->bind(BIND_SIGNATURE_UINT8, &d.sleds);
        iob->bind____skip(25);
    } else {
        iob->bind____skip(38);
        d.spot_work.fill(SPOT_WORK_UNSET);
        d.spot_figure.fill(0);
        d.sleds = 0;
    }
    iob->bind(BIND_SIGNATURE_UINT8, &base.orientation);
    for (int i = 0; i < 5; i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &d.workers[i]);
    }
    iob->bind(BIND_SIGNATURE_UINT8, &d.phase);
    iob->bind(BIND_SIGNATURE_UINT8, &d.funeral_done);
    iob->bind(BIND_SIGNATURE_UINT8, &d.preexisting);
    iob->bind(BIND_SIGNATURE_UINT8, &d.variant);

    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &d.resources_pct[i]);
    }
}

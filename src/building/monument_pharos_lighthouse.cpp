#include "monument_pharos_lighthouse.h"
#include "grid/orientation.h"

#include "building/monuments.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_message.h"
#include "city/city_warnings.h"
#include "construction/build_planner.h"
#include "figure/figure.h"
#include "figuretype/figure_carpenter.h"
#include "figuretype/figure_cartpusher.h"
#include "figuretype/figure_stonemason.h"
#include "figuretype/figure_worker.h"
#include "game/resource.h"
#include "game/undo.h"
#include "graphics/view/lookup.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "js/js_register.h"
#include "scenario/scenario.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_pharos_lighthouse);
BUILDING_RUNTIME_DATA_IMPL(building_pharos_lighthouse)

namespace {
    enum {
        MAP_EDGE_MARGIN = 3,
    };

    constexpr uint32_t k_blocks_monument = 0xFEFFD76Fu & ~(uint32_t)TERRAIN_PLANER_FUTURE;

    const vec2i k_land_part_offset = {2, 6};

    struct monument_pharos_lighthouse_cfg : public monument {
        monument_pharos_lighthouse_cfg() : monument{BUILDING_PHAROS_LIGHTHOUSE} {
            for (uint8_t i = 0; i < building_pharos_lighthouse::STAGE_COMPLETE; ++i) {
                phases.push_back({i, monument_phase_resource{ARCHITECTS, 1}});
            }
        }
    } g_monument_pharos_lighthouse;

    int camera_view() {
        return (map_view_orientation() / 2) & 3;
    }

    void collect_site(tile2i tower, blocked_tile_vec& tiles, blocked_tile& land) {
        for (int dy = 0; dy < building_pharos_lighthouse::TOWER_SIZE; ++dy) {
            for (int dx = 0; dx < building_pharos_lighthouse::TOWER_SIZE; ++dx) {
                const tile2i t = tower.shifted(dx, dy);
                tiles.push_back({t, !building_pharos_lighthouse::site_tile_free(t, true)});
            }
        }
        const tile2i land_tile = building_pharos_lighthouse::land_part_tile(tower);
        land = {land_tile, !building_pharos_lighthouse::site_tile_free(land_tile, false)};
    }

    void draw_site(painter& ctx, const build_planner& planer, bool fully_blocked) {
        for (const auto& part : planer.site_parts) {
            ghost_draw::draw_partially_blocked(ctx, fully_blocked, part);
        }
    }

    bool laborer_fetching_for(const figure* laborer, figure_id mason_id) {
        if (!laborer || !laborer->is_alive() || laborer->type != FIGURE_LABORER
            || laborer->leading_figure_id != mason_id) {
            return false;
        }
        switch (laborer->action_state) {
        case ACTION_6_CARTPUSHER_ON_FERRY:
        case ACTION_7_CARTPUSHER_WAIT_FOR_FERRY:
        case ACTION_15_LABORER_TO_STORAGE_YARD:
        case ACTION_16_LABORER_AT_STORAGE_YARD:
        case ACTION_35_LABORER_SLED_TO_LIGHTHOUSE:
            return true;
        default:
            return false;
        }
    }
} // namespace

void building_pharos_lighthouse::static_params::archive_load(archive /*arch*/) {
}

const building_pharos_lighthouse::base_params& building_pharos_lighthouse::lighthouse_params() {
    return (const base_params&)current_params();
}

const monument &building_pharos_lighthouse::config() const {
    return g_monument_pharos_lighthouse;
}

bool building_pharos_lighthouse::has_unfinished_pharos_lighthouse() {
    return building_monument_has_unfinished({BUILDING_PHAROS_LIGHTHOUSE}, true);
}

tile2i building_pharos_lighthouse::land_part_tile(tile2i tower) {
    return tower.shifted(k_land_part_offset.x, k_land_part_offset.y);
}

bool building_pharos_lighthouse::site_tile_free(tile2i tile, bool tower) {
    const auto* map = scenario_map_data();
    if (tile.x() < MAP_EDGE_MARGIN || tile.y() < MAP_EDGE_MARGIN || tile.x() >= map->width - MAP_EDGE_MARGIN
        || tile.y() >= map->height - MAP_EDGE_MARGIN) {
        return false;
    }
    if (map_building_at(tile)) {
        return false;
    }
    const uint32_t terrain = map_terrain_get(tile.grid_offset()) & k_blocks_monument;
    return tower ? terrain == TERRAIN_ROCK : terrain == 0;
}

bool building_pharos_lighthouse::site_fits(tile2i tower) {
    blocked_tile_vec tiles;
    blocked_tile land;
    collect_site(tower, tiles, land);
    return !land.blocked && std::none_of(tiles.begin(), tiles.end(), [](const auto& t) { return t.blocked; });
}

building_pharos_lighthouse* building_pharos_lighthouse::main_lighthouse() {
    building_impl* m = main();
    auto* l = m ? m->dcast_pharos_lighthouse() : nullptr;
    return l ? l : this;
}

const building_pharos_lighthouse* building_pharos_lighthouse::main_lighthouse() const {
    return const_cast<building_pharos_lighthouse*>(this)->main_lighthouse();
}

int building_pharos_lighthouse::stage() const {
    const int p = main_lighthouse()->runtime_data().phase;
    if (p == MONUMENT_FINISHED || p >= STAGE_COMPLETE) {
        return STAGE_COMPLETE;
    }
    return std::max(p, 0);
}

int building_pharos_lighthouse::spot_index(e_figure_type type) const {
    if (type == FIGURE_STONEMASON) {
        return SPOT_MASON;
    }
    if (type == FIGURE_CARPENTER) {
        return SPOT_CARPENTER;
    }
    return -1;
}

int building_pharos_lighthouse::spot_work_left(e_figure_type type) const {
    const int i = spot_index(type);
    return i < 0 ? 0 : main_lighthouse()->runtime_data().spot_work[i];
}

void building_pharos_lighthouse::reset_spots() {
    auto& d = main_lighthouse()->runtime_data();
    d.spot_work.fill(0);
    const auto& stages = lighthouse_params().stages;
    const int s = stage();
    if (s < (int)stages.size()) {
        d.spot_work[spot_index(FIGURE_STONEMASON)] = stages[s].stonemason;
        d.spot_work[spot_index(FIGURE_CARPENTER)] = stages[s].carpenter;
    }
}

figure_id building_pharos_lighthouse::worker_figure_id() const {
    return main_lighthouse()->runtime_data().worker_fid;
}

bool building_pharos_lighthouse::part_has_active_worker() const {
    auto& d = const_cast<building_pharos_lighthouse*>(main_lighthouse())->runtime_data();
    if (!d.worker_fid) {
        return false;
    }
    figure* f = figure_get(d.worker_fid);
    if (f && f->is_alive()) {
        const int action = f->action_state;
        if (f->type == FIGURE_STONEMASON
            && (action == ACTION_0_MASON_CREATED || action == ACTION_1_MASON_GOING
                || action == ACTION_9_MASON_WORK_OBELISK || action == ACTION_19_MASON_WAIT_FOR_BLOCK)) {
            return true;
        }
        if (f->type == FIGURE_CARPENTER
            && (action == ACTION_1_CARPENTER_GO_TO_SITE || action == ACTION_2_CARPENTER_WORK)) {
            return true;
        }
    }
    d.worker_fid = 0;
    return false;
}

bool building_pharos_lighthouse::has_free_spot(e_figure_type type) const {
    if (stage() >= STAGE_COMPLETE || spot_work_left(type) <= 0) {
        return false;
    }
    if (part_has_active_worker()) {
        const figure* f = figure_get(worker_figure_id());
        const bool working
          = f->action_state
            == (f->type == FIGURE_STONEMASON ? (int)ACTION_9_MASON_WORK_OBELISK : (int)ACTION_2_CARPENTER_WORK);
        return f->type != type || !working;
    }
    return true;
}

figure_id building_pharos_lighthouse::mason_waiting_for_block() const {
    if (!part_has_active_worker()) {
        return 0;
    }
    figure* mason = figure_get(worker_figure_id());
    if (mason->type != FIGURE_STONEMASON || mason->action_state != ACTION_19_MASON_WAIT_FOR_BLOCK) {
        return 0;
    }
    if (mason->leading_figure_id) {
        if (laborer_fetching_for(figure_get(mason->leading_figure_id), mason->id)) {
            return 0;
        }
        mason->leading_figure_id = 0;
    }
    return mason->id;
}

bool building_pharos_lighthouse::sled_arrived(figure& mason) {
    auto& d = main_lighthouse()->runtime_data();
    if (mason.type != FIGURE_STONEMASON || mason.action_state != ACTION_19_MASON_WAIT_FOR_BLOCK) {
        return false;
    }
    mason.leading_figure_id = 0;
    if (++d.sleds < SLEDS_PER_BLOCK) {
        return false;
    }
    d.sleds = 0;
    mason.action_state = ACTION_9_MASON_WORK_OBELISK;
    mason.wait_ticks = 0;
    return true;
}

bool building_pharos_lighthouse::work_tick(figure& f) {
    building_pharos_lighthouse* m = main_lighthouse();
    if (m != this) {
        return m->work_tick(f);
    }
    const int i = spot_index(f.type);
    auto& d = runtime_data();
    if (i < 0 || stage() >= STAGE_COMPLETE || d.spot_work[i] == 0) {
        return true;
    }
    if (--d.spot_work[i] > 0) {
        return false;
    }
    if (d.worker_fid == f.id) {
        d.worker_fid = 0;
    }
    if (d.spot_work[SPOT_MASON] == 0 && d.spot_work[SPOT_CARPENTER] == 0) {
        advance_stage();
    }
    return true;
}

void building_pharos_lighthouse::advance_stage() {
    const int next = stage() + 1;
    if (next > STAGE_COMPLETE) {
        return;
    }
    set_phase(next >= STAGE_COMPLETE ? MONUMENT_FINISHED : next);
    reset_spots();
    if (next >= STAGE_COMPLETE) {
        messages::popup("lighthouse_congratulations", 0, tile().grid_offset());
    }
}

void building_pharos_lighthouse::set_stage(int target) {
    building_pharos_lighthouse* m = main_lighthouse();
    if (m != this) {
        m->set_stage(target);
        return;
    }
    target = std::clamp(target, 0, (int)STAGE_COMPLETE);
    set_phase(target >= STAGE_COMPLETE ? MONUMENT_FINISHED : target);
    runtime_data().sleds = 0;
    reset_spots();
}

void building_pharos_lighthouse::set_phase(int phase) {
    building_monument::set_phase(phase);
    if (has_next()) {
        if (auto* land = next()->dcast_pharos_lighthouse()) {
            land->runtime_data().phase = runtime_data().phase;
        }
    }
}

void building_pharos_lighthouse::on_phase_changed(int /*old_phase*/, int current) {
    if (is_main()) {
        refresh_tower_tiles();
        update_animation();
    }
    if (current != MONUMENT_FINISHED) {
        auto& d = runtime_data();
        std::fill(std::begin(d.resources_pct), std::end(d.resources_pct), 0);
    }
}

int building_pharos_lighthouse::get_progress(progress_info* out) const {
    const int s = stage();
    progress_info info;
    info.stage = s;
    info.percent = (s >= STAGE_COMPLETE) ? 100 : (s + 1) * 10;
    if (part_has_active_worker()) {
        const figure* f = figure_get(worker_figure_id());
        if (f->type == FIGURE_CARPENTER) {
            info.carpenters = 1;
        } else if (f->type == FIGURE_STONEMASON) {
            info.stonemasons = 1;
            info.stonemasons_waiting = f->action_state == ACTION_19_MASON_WAIT_FOR_BLOCK ? 1 : 0;
        }
    }
    info.material = std::max(0, (STAGE_COMPLETE - s) * SLEDS_PER_BLOCK * MATERIAL_PER_LOAD);
    info.material_total = STAGE_COMPLETE * SLEDS_PER_BLOCK * MATERIAL_PER_LOAD;
    if (out) {
        *out = info;
    }
    return info.percent;
}

bool building_pharos_lighthouse::needs_resources() const {
    return false;
}

bool building_pharos_lighthouse::need_stonemason() {
    return is_main() && !is_finished() && !part_has_active_worker() && has_free_spot(FIGURE_STONEMASON);
}

bool building_pharos_lighthouse::need_carpenter() {
    return is_main() && !is_finished() && !part_has_active_worker() && has_free_spot(FIGURE_CARPENTER);
}

bool building_pharos_lighthouse::need_workers() const {
    return false;
}

void building_pharos_lighthouse::add_workers(figure_id fid) {
    building_pharos_lighthouse* m = main_lighthouse();
    figure* f = figure_get(fid);
    if (!f || (f->type != FIGURE_STONEMASON && f->type != FIGURE_CARPENTER)) {
        return;
    }
    if (m->part_has_active_worker() || m->spot_work_left(f->type) <= 0 || m->is_finished()) {
        return;
    }
    m->runtime_data().worker_fid = fid;
}

void building_pharos_lighthouse::remove_worker(figure_id fid) {
    auto& d = main_lighthouse()->runtime_data();
    if (d.worker_fid == fid) {
        d.worker_fid = 0;
    }
}

int building_pharos_lighthouse::building_image_get() const {
    if (is_land_part()) {
        return 0;
    }
    bstring32 key;
    key.printf("s%d", stage() + 1);
    const auto &params = current_params();
    const int img = params.first_img(xstring(key.c_str()));
    return img > 0 ? img : params.first_img("preview");
}

void building_pharos_lighthouse::refresh_tower_tiles() {
    map_building_tiles_add(id(), tile(), TOWER_SIZE, building_image_get(), TERRAIN_BUILDING);
    for (int dy = 0; dy < TOWER_SIZE; ++dy) {
        for (int dx = 0; dx < TOWER_SIZE; ++dx) {
            map_terrain_remove(tile().shifted(dx, dy).grid_offset(), TERRAIN_ROCK);
        }
    }
}

void building_pharos_lighthouse::preview::setup_preview_graphics(build_planner &planer) const {
    planer.init_tiles(1, 1);
}

uint32_t building_pharos_lighthouse::preview::ghost_ignore_terrain(build_planner & /*p*/, tile2i /*tile*/) const {
    return TERRAIN_NOT_CLEAR;
}

void building_pharos_lighthouse::preview::collect_site(build_planner& p, tile2i end) const {
    blocked_tile_vec tiles;
    blocked_tile land;
    ::collect_site(end, tiles, land);
    blocked_tile_vec land_only;
    land_only.push_back(land);
    p.add_site_part(tiles);
    p.add_site_part(land_only);
    p.site_blocked = land.blocked || std::any_of(tiles.begin(), tiles.end(), [](const auto& t) { return t.blocked; });
}

int building_pharos_lighthouse::preview::can_place(build_planner& p, tile2i /*tile*/, tile2i /*end*/, int state) const {
    if (state != CAN_PLACE && state != CAN_NOT_BUT_GREEN) {
        return state;
    }
    if (p.site_blocked || has_unfinished_pharos_lighthouse()) {
        return CAN_NOT_BUT_GREEN;
    }
    return CAN_PLACE;
}

int building_pharos_lighthouse::preview::finalize_check(build_planner& p, tile2i /*tile*/, tile2i end,
  int state) const {
    if (state != CAN_PLACE && state != CAN_NOT_BUT_GREEN) {
        return state;
    }
    if (!site_fits(end)) {
        g_warning_manager.show("#must_be_over_rocks");
        p.set_warning("#entrance_on_clear_land");
        return CAN_NOT_PLACE;
    }
    if (has_unfinished_pharos_lighthouse()) {
        p.set_warning("#one_pharos_only");
        return CAN_NOT_PLACE;
    }
    return CAN_PLACE;
}

int building_pharos_lighthouse::preview::construction_place(build_planner& planer, tile2i /*tile*/, tile2i end,
  int orientation, int variant) const {
    planer.last_created_building = nullptr;
    building* b = building_create(BUILDING_PHAROS_LIGHTHOUSE, end, orientation);
    game_undo_add_building(b);
    if (b->id <= 0) {
        return 0;
    }
    add_building(b, orientation, variant);
    planer.last_created_building = b;
    return 1;
}

void building_pharos_lighthouse::preview::ghost_preview(build_planner& planer, painter& ctx, tile2i /*start*/,
  tile2i /*end*/, vec2i /*pixel*/) const {
    draw_site(ctx, planer, false);
}

void building_pharos_lighthouse::preview::ghost_blocked(build_planner& planer, painter& ctx, tile2i /*start*/,
  tile2i /*end*/, vec2i /*pixel*/, bool fully_blocked) const {
    draw_site(ctx, planer, fully_blocked);
}

void building_pharos_lighthouse::on_place_update_tiles(int orientation, int /*variant*/) {
    base.orientation = orientation;
    base.size = TOWER_SIZE;
    base.prev_part_building_id = 0;
    auto& d = runtime_data();
    d.phase = 0;
    d.worker_fid = 0;
    d.sleds = 0;
    reset_spots();
    refresh_tower_tiles();

    const tile2i land_tile = land_part_tile(tile());
    building* land = building_create(BUILDING_PHAROS_LIGHTHOUSE, land_tile, orientation);
    if (!land || land->id <= 0) {
        base.next_part_building_id = 0;
        return;
    }
    game_undo_add_building(land);
    land->size = 1;
    land->prev_part_building_id = id();
    land->next_part_building_id = 0;
    base.next_part_building_id = land->id;
    if (auto* lp = land->dcast_pharos_lighthouse()) {
        auto& ld = lp->runtime_data();
        ld.phase = 0;
        ld.worker_fid = 0;
        ld.sleds = 0;
        ld.spot_work.fill(0);
    }
    map_building_set(land_tile.grid_offset(), land->id);
}

xstring building_pharos_lighthouse::demolish_blocked_message() const {
    return "#pharos_not_demolishable";
}

void building_pharos_lighthouse::on_post_load() {
    building_monument::on_post_load();
    if (is_land_part()) {
        return;
    }
    auto& d = runtime_data();
    if (d.phase != MONUMENT_FINISHED && d.spot_work[SPOT_MASON] == 0 && d.spot_work[SPOT_CARPENTER] == 0) {
        d.phase = (int8_t)std::clamp(d.phase - 1, 0, (int)STAGE_COMPLETE - 1);
        d.worker_fid = 0;
        d.sleds = 0;
        reset_spots();
        if (has_next()) {
            if (auto* land = next()->dcast_pharos_lighthouse()) {
                land->runtime_data().phase = d.phase;
                land->runtime_data().spot_work.fill(0);
            }
        }
    }
    refresh_tower_tiles();
    update_animation();
}

void building_pharos_lighthouse::on_destroy() {
    if (is_land_part()) {
        const tile2i t = tile();
        if (map_building_at(t) == id()) {
            map_building_set(t.grid_offset(), 0);
        }
        return;
    }
    for (int dy = 0; dy < TOWER_SIZE; ++dy) {
        for (int dx = 0; dx < TOWER_SIZE; ++dx) {
            const tile2i t = tile().shifted(dx, dy);
            if (map_grid_is_inside(t, 1) && map_building_at(t) == id()) {
                map_terrain_add(t.grid_offset(), TERRAIN_ROCK);
            }
        }
    }
}

void building_pharos_lighthouse::update_day() {
    building_impl::update_day();
    if (is_main() && !is_finished()) {
        part_has_active_worker();
    }
}

void building_pharos_lighthouse::update_animation() {
    base.play_animation = !is_land_part() && is_finished();
}

void building_pharos_lighthouse::update_map_orientation(int /*map_orientation*/) {
    if (is_main()) {
        refresh_tower_tiles();
    }
}

bool building_pharos_lighthouse::draw_ornaments_and_animations_height(painter& ctx, vec2i point, tile2i tile,
  color color_mask) {
    if (is_land_part()) {
        return false;
    }
    return building_monument::draw_ornaments_and_animations_height(ctx, point, tile, color_mask);
}

tile2i building_pharos_lighthouse::center_point() const {
    tile2i t = main_lighthouse()->tile();
    return t.shifted(TOWER_SIZE / 2, TOWER_SIZE / 2);
}

tile2i building_pharos_lighthouse::access_point() const {
    return land_part_tile(main_lighthouse()->tile());
}

grid_area building_pharos_lighthouse::get_area() const {
    tile2i start = main_lighthouse()->tile();
    return {start, start.shifted(TOWER_SIZE - 1, TOWER_SIZE - 1)};
}

void building_pharos_lighthouse::bind_dynamic(io_buffer* iob, size_t /*version*/) {
    auto& d = runtime_data();

    iob->bind(BIND_SIGNATURE_UINT16, &d.spot_work[SPOT_MASON]);
    iob->bind(BIND_SIGNATURE_UINT16, &d.spot_work[SPOT_CARPENTER]);
    iob->bind(BIND_SIGNATURE_UINT16, &d.worker_fid);
    iob->bind(BIND_SIGNATURE_UINT8, &d.sleds);
    iob->bind____skip(31);
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

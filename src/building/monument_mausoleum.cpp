#include "monument_mausoleum.h"

#include "building/monuments.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_message.h"
#include "city/city_resource.h"
#include "city/city_warnings.h"
#include "construction/build_planner.h"
#include "figure/figure.h"
#include "figuretype/figure_carpenter.h"
#include "figuretype/figure_stonemason.h"
#include "figuretype/figure_worker.h"
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
#include <utility>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_mausoleum);
BUILDING_RUNTIME_DATA_IMPL(building_mausoleum)

static monument g_monument_mausoleum{BUILDING_MAUSOLEUM};

namespace {

const building_mausoleum::base_params &maus_params() {
    return (const building_mausoleum::base_params &)building_mausoleum::current_params();
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

int block_index_of(uint32_t kind_word) {
    switch (kind_word & MAUSOLEUM_KIND_BLOCK_MASK) {
    case MAUSOLEUM_KIND_BLOCK_0: return 0;
    case MAUSOLEUM_KIND_BLOCK_1: return 1;
    case MAUSOLEUM_KIND_BLOCK_2: return 2;
    case MAUSOLEUM_KIND_BLOCK_3: return 3;
    default: return -1;
    }
}

int pair_index_of(uint32_t kind_word) {
    switch (kind_word & MAUSOLEUM_KIND_PAIR_MASK) {
    case MAUSOLEUM_KIND_PAIR_0: return 0;
    case MAUSOLEUM_KIND_PAIR_1: return 1;
    case MAUSOLEUM_KIND_PAIR_2: return 2;
    case MAUSOLEUM_KIND_PAIR_3: return 3;
    default: return -1;
    }
}

uint16_t next_subtile(uint32_t kind_word, uint16_t mask) {
    const int pair = pair_index_of(kind_word);
    if (pair < 0) {
        return 0;
    }
    const uint16_t first = (uint16_t)(1 << (pair * 2));
    const uint16_t order[4] = {first, (uint16_t)(first << 1), (uint16_t)(first << 8), (uint16_t)(first << 9)};
    for (uint16_t bit : order) {
        if (!(mask & bit)) {
            return bit;
        }
    }
    return 0;
}

int count_subtiles(uint16_t mask) {
    int n = 0;
    for (int i = 0; i < MAUSOLEUM_BLOCK_SUBTILES; ++i) {
        n += (mask >> i) & 1;
    }
    return n;
}

template<class F>
bool walk_parts(building_mausoleum *main, F &&fn) {
    for (building *p = &main->base; p; p = p->has_next() ? p->next() : nullptr) {
        if (auto *mp = p->dcast_mausoleum(); mp && fn(mp)) {
            return true;
        }
    }
    return false;
}

} // namespace

void mausoleum_part_desc::pack_kind() {
    static const uint32_t block_bit[4] = {
        MAUSOLEUM_KIND_BLOCK_0, MAUSOLEUM_KIND_BLOCK_1, MAUSOLEUM_KIND_BLOCK_2, MAUSOLEUM_KIND_BLOCK_3
    };
    static const uint32_t pair_bit[4] = {
        MAUSOLEUM_KIND_PAIR_0, MAUSOLEUM_KIND_PAIR_1, MAUSOLEUM_KIND_PAIR_2, MAUSOLEUM_KIND_PAIR_3
    };

    uint32_t word = kind & MAUSOLEUM_KIND_MASK;
    if (walkway) {
        word |= MAUSOLEUM_KIND_WALKWAY;
    }
    if (block >= 0 && block < MAUSOLEUM_BLOCKS) {
        word |= block_bit[block];
    }
    if (pair >= 0 && pair < MAUSOLEUM_BLOCKS) {
        word |= pair_bit[pair];
    }
    kind = word;
}

namespace {

void push_fence_part(svector<mausoleum_part_desc, MAUSOLEUM_PARTS> &parts, int x, int y, const mausoleum_fence_token &tok) {
    mausoleum_part_desc p;
    p.offset = {x, y};
    p.size = 1;
    p.kind = (uint32_t)tok.kind;
    p.walkway = tok.walkway;
    parts.push_back(p);
}

} // namespace

void building_mausoleum::static_params::archive_load(archive /*arch*/) {
    parts.clear();
    for (auto &p : blocks) {
        p.pack_kind();
        parts.push_back(p);
    }

    const mausoleum_fence_token *grid[MAUSOLEUM_BOX_DEPTH][MAUSOLEUM_BOX_WIDTH] = {};
    const int rows = std::min((int)fence_map.size(), (int)MAUSOLEUM_BOX_DEPTH);
    for (int y = 0; y < rows; ++y) {
        const char *s = fence_map[y].c_str();
        int x = 0;
        while (*s && x < MAUSOLEUM_BOX_WIDTH) {
            while (*s == ' ' || *s == '\t') {
                ++s;
            }
            if (!*s) {
                break;
            }
            const char *start = s;
            while (*s && *s != ' ' && *s != '\t') {
                ++s;
            }
            bstring32 key;
            key.ncat(start, (size_t)(s - start));
            const xstring glyph(key.c_str());
            for (const auto &tok : fence_tokens) {
                if (tok.token == glyph && tok.kind >= 0) {
                    grid[y][x] = &tok;
                    break;
                }
            }
            ++x;
        }
    }

    for (int y = 0; y < MAUSOLEUM_BOX_DEPTH; ++y) {
        for (int x = 0; x < MAUSOLEUM_BOX_WIDTH; ++x) {
            const mausoleum_fence_token *tok = grid[y][x];
            if (!tok) {
                continue;
            }
            if (tok->pair_dy != 0) {
                const int py = y + tok->pair_dy;
                if (py >= 0 && py < MAUSOLEUM_BOX_DEPTH && grid[py][x]) {
                    push_fence_part(parts, x, y, *tok);
                    push_fence_part(parts, x, py, *grid[py][x]);
                    grid[y][x] = nullptr;
                    grid[py][x] = nullptr;
                    continue;
                }
            }
            push_fence_part(parts, x, y, *tok);
            grid[y][x] = nullptr;
        }
    }

    for (const auto &link : fence_links) {
        for (auto &p : parts) {
            if (p.offset == link.offset) {
                p.block = link.block;
                p.pair = link.pair;
                break;
            }
        }
    }
    for (auto &p : parts) {
        if (p.size == 1) {
            p.pack_kind();
        }
    }

    g_monument_mausoleum.btype = BUILDING_MAUSOLEUM;
    g_monument_mausoleum.phases.clear();
    g_monument_mausoleum.phases.push_back({0, monument_phase_resource{RESOURCE_NONE, 0}});
}

const monument &building_mausoleum::config() const {
    return g_monument_mausoleum;
}

int building_mausoleum::placement_amount(e_resource r) const {
    for (const auto &pr : current_params().placement_resources) {
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
    for (building &b : city_buildings()) {
        const bool live = b.is_valid() || b.state == BUILDING_STATE_CREATED || b.state == BUILDING_STATE_MOTHBALLED;
        if (!live || b.type != BUILDING_MAUSOLEUM || !b.is_main()) {
            continue;
        }
        auto *m = b.dcast_mausoleum();
        if (m && (!m->is_finished() || m->get_progress(nullptr) < 100)) {
            return true;
        }
    }
    return false;
}

int building_mausoleum::parts_count() {
    return std::min((int)current_params().parts.size(), (int)MAUSOLEUM_PARTS);
}

const mausoleum_part_desc &building_mausoleum::part_desc(int index) {
    static const mausoleum_part_desc empty{};
    const auto &parts = current_params().parts;
    if (index < 0 || index >= (int)parts.size()) {
        return empty;
    }
    return parts[index];
}

vec2i building_mausoleum::box_extent(int orientation) {
    if (orientation == 2 || orientation == 6) {
        return {MAUSOLEUM_BOX_DEPTH, MAUSOLEUM_BOX_WIDTH};
    }
    return {MAUSOLEUM_BOX_WIDTH, MAUSOLEUM_BOX_DEPTH};
}

tile2i building_mausoleum::origin_from_cursor(tile2i cursor) {
    const vec2i e = box_extent(g_camera.orientation);
    switch (g_camera.orientation) {
    case DIR_2_BOTTOM_RIGHT:
        return cursor.shifted(-e.x + 1, 0);
    case DIR_4_BOTTOM_LEFT:
        return cursor.shifted(-e.x + 1, -e.y + 1);
    case DIR_6_TOP_LEFT:
        return cursor.shifted(0, -e.y + 1);
    default:
        return cursor;
    }
}

static vec2i oriented_offset(int dx, int dy, int size, int view, int orientation) {
    if (orientation == 0 || orientation == 4) {
        if (view == 2 || view == 4) {
            dx = MAUSOLEUM_BOX_WIDTH - dx - size;
            dy = MAUSOLEUM_BOX_DEPTH - dy - size;
        }
        return {dx, dy};
    }
    if (view == 4 || view == 6) {
        dx = MAUSOLEUM_BOX_WIDTH - dx - size;
        dy = MAUSOLEUM_BOX_DEPTH - dy - size;
    }
    return {dy, dx};
}

vec2i building_mausoleum::part_offset(int index, int view, int orientation) {
    const auto &d = part_desc(index);
    return oriented_offset(d.offset.x, d.offset.y, d.size, view, orientation);
}

vec2i building_mausoleum::entry_offset(int view, int orientation) {
    return oriented_offset(MAUSOLEUM_ENTRY_DX, MAUSOLEUM_ENTRY_DY, 1, view, orientation);
}

bool building_mausoleum::area_blocked_at(tile2i origin, vec2i extent) {
    return area_blocked(origin, extent.x, extent.y);
}

building_mausoleum *building_mausoleum::main_mausoleum() {
    return base.main()->dcast_mausoleum();
}

const building_mausoleum *building_mausoleum::main_mausoleum() const {
    return base.main()->dcast_mausoleum();
}

building_mausoleum *building_mausoleum::part(int index) {
    building_mausoleum *m = main_mausoleum();
    if (!m || index <= 0) {
        return m;
    }
    building *p = &m->base;
    for (int i = 0; i < index && p; ++i) {
        p = p->has_next() ? p->next() : nullptr;
    }
    return p ? p->dcast_mausoleum() : nullptr;
}

const building_mausoleum *building_mausoleum::part(int index) const {
    return const_cast<building_mausoleum *>(this)->part(index);
}

uint32_t building_mausoleum::part_kind_word() const {
    return part_desc(part_index()).kind;
}

uint8_t building_mausoleum::work_flags() const {
    return main_mausoleum()->runtime_data().work_flags;
}

int building_mausoleum::block_index() const {
    return block_index_of(part_kind_word());
}

int building_mausoleum::camera_view() const {
    return g_camera.orientation;
}

tile2i building_mausoleum::origin() const {
    const building_mausoleum *m = main_mausoleum();
    const vec2i o = part_offset(0, m->runtime_data().view, m->base.orientation);
    return m->tile().shifted(-o.x, -o.y);
}

vec2i building_mausoleum::current_offset() const {
    return part_offset(part_index(), runtime_data().view, base.orientation);
}

figure_id building_mausoleum::worker_figure_id() const {
    return runtime_data().og_part.worker_figure_id;
}

void building_mausoleum::set_worker_figure(figure_id fid) {
    runtime_data().og_part.worker_figure_id = fid;
}

void building_mausoleum::clear_worker_figure() {
    runtime_data().og_part.worker_figure_id = 0;
}

bool building_mausoleum::part_has_active_worker() const {
    const figure_id wid = worker_figure_id();
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
            if (action == ACTION_1_MASON_GOING || action == ACTION_9_MASON_WORK_OBELISK
                || action == ACTION_19_MASON_WAIT_FOR_BLOCK) {
                return true;
            }
            break;
        case FIGURE_LABORER:
            if (action == ACTION_15_LABORER_TO_STORAGE_YARD || action == ACTION_16_LABORER_AT_STORAGE_YARD
                || action == ACTION_26_LABORER_SLED_TO_MAUSOLEUM || action == ACTION_27_LABORER_TO_MAUSOLEUM
                || action == ACTION_28_LABORER_MAUSOLEUM_WORK) {
                return true;
            }
            break;
        default:
            break;
        }
    }
    const_cast<building_mausoleum *>(this)->clear_worker_figure();
    return false;
}

void building_mausoleum::send_to_part(figure &f) const {
    f.destination_tile = main_mausoleum()->access_point();
    f.destination_building_id = id();
    f.roam_length = 0;
}

bool building_mausoleum::check_work(e_figure_type type, figure *f, bool assign) {
    building_mausoleum *m = main_mausoleum();
    if (!m) {
        return false;
    }
    const uint8_t flags = m->runtime_data().work_flags;
    const bool is_laborer = type == FIGURE_LABORER;
    const bool is_mason = type == FIGURE_STONEMASON;
    const bool is_carpenter = type == FIGURE_CARPENTER;
    const bool low_done = flags & MAUSOLEUM_BLOCKS_LOW_DONE;
    const bool ground_started = flags & MAUSOLEUM_GROUND_STARTED;
    const bool full = flags & MAUSOLEUM_BLOCKS_FULL;
    const bool all_finished = (flags & MAUSOLEUM_BLOCKS_FINISHED) == MAUSOLEUM_BLOCKS_FINISHED;

    if (part_index() == 0 && full) {
        for (int i = 0; i < MAUSOLEUM_BLOCKS; ++i) {
            auto *blk = part(i);
            if (blk && blk->part_stage() < MAUSOLEUM_BLOCK_FULL) {
                blk->runtime_data().part_stage = MAUSOLEUM_BLOCK_FULL;
                blk->update_part_image();
            }
        }
    }
    if (is_carpenter && (all_finished || !low_done)) {
        return false;
    }

    const uint32_t kind_word = part_kind_word();
    const int kind = kind_word & MAUSOLEUM_KIND_MASK;
    if (kind < MAUSOLEUM_KIND_GROUND_FIRST || kind == 11 || kind == 13) {
        return false;
    }

    const uint16_t stage = part_stage();
    if ((kind_word & MAUSOLEUM_KIND_BLOCK_MASK) && stage >= MAUSOLEUM_GROUND_LEVELED && !full) {
        const int block = block_index();
        if (block < 0) {
            return false;
        }
        if (flags & (MAUSOLEUM_BLOCK_FINISHED_FIRST << block)) {
            if (is_carpenter) {
                return false;
            }
        } else if (is_mason && low_done) {
            return false;
        }

        if (is_laborer) {
            // Sandstone sleds are dispatched through figure_worker::assign_block_delivery.
            if (assign || !part_has_active_worker()) {
                return false;
            }
            figure *mason = figure_get(worker_figure_id());
            return mason && mason->type == FIGURE_STONEMASON && mason->action_state == ACTION_19_MASON_WAIT_FOR_BLOCK
                && mason->leading_figure_id == 0;
        }
        if (is_mason) {
            const auto *block_part = m->part(block);
            const uint16_t mask = block_part ? block_part->part_stage() : 0;
            const int pair = pair_index_of(kind_word);
            if (pair < 0) {
                return false;
            }
            const uint16_t low = (uint16_t)(MAUSOLEUM_PAIR_LOW_SUBTILES << (pair * 2));
            const uint16_t high = (uint16_t)(MAUSOLEUM_PAIR_HIGH_SUBTILES << (pair * 2));
            if ((mask & low) == low && ((mask & high) == high || !low_done)) {
                return false;
            }
            if (part_has_active_worker()) {
                return false;
            }
            if (assign && f) {
                f->action_state = ACTION_1_MASON_GOING;
                set_worker_figure(f->id);
                send_to_part(*f);
            }
            return true;
        }
        if (is_carpenter) {
            if (part_has_active_worker()) {
                return false;
            }
            if (assign && f) {
                set_worker_figure(f->id);
                send_to_part(*f);
            }
            return true;
        }
        return false;
    }

    if (!is_laborer) {
        return false;
    }
    if (stage == MAUSOLEUM_GROUND_FINISHED) {
        return false;
    }
    if (stage == MAUSOLEUM_GROUND_LEVELED && (!ground_started || !full)) {
        return false;
    }
    if (part_has_active_worker()) {
        return false;
    }
    if (assign && f) {
        f->action_state = ACTION_27_LABORER_TO_MAUSOLEUM;
        set_worker_figure(f->id);
        send_to_part(*f);
    }
    return true;
}

bool building_mausoleum::check_work_for_figure(figure_id fid, bool assign) {
    figure *f = figure_get(fid);
    if (!f || !f->id) {
        return false;
    }
    return check_work(f->type, f, assign);
}

bool building_mausoleum::has_work_for(e_figure_type type) const {
    building_mausoleum *m = const_cast<building_mausoleum *>(main_mausoleum());
    return m && walk_parts(m, [&](building_mausoleum *p) { return p->check_work(type, nullptr, false); });
}

int building_mausoleum::find_work_for_figure(figure_id fid) {
    figure *f = figure_get(fid);
    if (!f || !f->id) {
        return 0;
    }
    for (building &b : city_buildings()) {
        if (!b.is_valid() || b.type != BUILDING_MAUSOLEUM || !b.is_main()) {
            continue;
        }
        auto *m = b.dcast_mausoleum();
        if (!m || m->is_finished()) {
            continue;
        }
        int found = 0;
        walk_parts(m, [&](building_mausoleum *p) {
            if (p->check_work(f->type, f, true)) {
                found = p->id();
                return true;
            }
            return false;
        });
        if (found) {
            return found;
        }
    }
    return 0;
}

void building_mausoleum::update_ground_flags() {
    building_mausoleum *m = main_mausoleum();
    bool started = true;
    bool done = true;
    for (int i = 0; i < parts_count(); ++i) {
        if ((part_desc(i).kind & MAUSOLEUM_KIND_MASK) < MAUSOLEUM_KIND_GROUND_FIRST) {
            continue;
        }
        const auto *p = part(i);
        const uint16_t s = p ? p->part_stage() : 0;
        started &= s != MAUSOLEUM_GROUND_UNTOUCHED;
        done &= s >= MAUSOLEUM_GROUND_FINISHED;
    }
    if (started) {
        m->runtime_data().work_flags |= MAUSOLEUM_GROUND_STARTED;
    }
    if (done) {
        m->runtime_data().work_flags |= MAUSOLEUM_GROUND_DONE;
    }
}

void building_mausoleum::recompute_block_flags() {
    building_mausoleum *m = main_mausoleum();
    bool full = true;
    bool low_done = true;
    for (int i = 0; i < MAUSOLEUM_BLOCKS; ++i) {
        const auto *blk = part(i);
        const uint16_t s = blk ? blk->part_stage() : 0;
        full &= s >= MAUSOLEUM_BLOCK_FULL;
        low_done &= (s & MAUSOLEUM_BLOCK_LOW_DONE_MASK) == MAUSOLEUM_BLOCK_LOW_DONE_MASK;
    }
    if (full) {
        m->runtime_data().work_flags |= MAUSOLEUM_BLOCKS_FULL;
    }
    if (low_done) {
        m->runtime_data().work_flags |= MAUSOLEUM_BLOCKS_LOW_DONE;
    }
}

bool building_mausoleum::laborer_tick(figure &f) {
    auto &d = runtime_data();
    if (d.part_stage != MAUSOLEUM_GROUND_UNTOUCHED && d.part_stage != MAUSOLEUM_GROUND_LEVELED) {
        d.part_stage = std::min<uint16_t>(d.part_stage, MAUSOLEUM_GROUND_FINISHED);
        clear_worker_figure();
        return true;
    }
    f.wait_ticks++;
    if (f.wait_ticks < MAUSOLEUM_WORK_TICKS) {
        return false;
    }
    f.wait_ticks = 0;

    d.part_stage++;
    const int kind = part_kind();
    if (kind == 10 || kind == 12) {
        if (auto *pair = part(part_index() + 1)) {
            pair->runtime_data().part_stage = d.part_stage;
            pair->update_part_image();
        }
    }
    update_part_image();
    update_ground_flags();
    clear_worker_figure();
    return true;
}

bool building_mausoleum::block_tick(figure &f) {
    const bool is_carpenter = f.type == FIGURE_CARPENTER;
    const uint32_t kind_word = part_kind_word();
    const int block = block_index();
    if (block < 0) {
        clear_worker_figure();
        return true;
    }
    building_mausoleum *m = main_mausoleum();
    building_mausoleum *block_part = m->part(block);
    if (!block_part) {
        clear_worker_figure();
        return true;
    }
    const uint16_t mask = block_part->part_stage();
    uint16_t bit = next_subtile(kind_word, mask);
    if (is_carpenter) {
        bit = (uint16_t)(MAUSOLEUM_BLOCK_FINISHED_FIRST << block);
    }
    if (bit == 0) {
        clear_worker_figure();
        return true;
    }
    if (f.wait_ticks < 0) {
        f.wait_ticks = 0;
    }
    f.wait_ticks++;
    if (f.wait_ticks < MAUSOLEUM_WORK_TICKS) {
        return false;
    }
    f.wait_ticks = 0;

    if (is_carpenter) {
        clear_worker_figure();
        m->runtime_data().work_flags |= (uint8_t)bit;
        block_part->update_part_image();
        return true;
    }
    block_part->runtime_data().part_stage = mask | bit;
    block_part->update_part_image();
    recompute_block_flags();
    clear_worker_figure();
    return true;
}

bool building_mausoleum::work_tick(figure &f) {
    if (part_kind() < MAUSOLEUM_KIND_GROUND_FIRST) {
        return true;
    }
    if (f.type == FIGURE_LABORER) {
        return laborer_tick(f);
    }
    if (f.type == FIGURE_CARPENTER || f.type == FIGURE_STONEMASON) {
        return block_tick(f);
    }
    return true;
}

int building_mausoleum::get_progress(int *out) const {
    const building_mausoleum *m = main_mausoleum();
    if (!m) {
        return 0;
    }
    const uint8_t flags = m->runtime_data().work_flags;
    const bool low_done = flags & MAUSOLEUM_BLOCKS_LOW_DONE;
    const bool full = flags & MAUSOLEUM_BLOCKS_FULL;
    int status = MAUSOLEUM_STATUS_SITE;
    int blocks_left = 0;
    if (low_done) {
        for (int block = 0; block < MAUSOLEUM_BLOCKS; ++block) {
            if (!(flags & (MAUSOLEUM_BLOCK_FINISHED_FIRST << block))) {
                blocks_left++;
            }
        }
    }
    int stage0 = 0, below2 = 0, missing = 0, material = 0;
    int masons = 0, waiting = 0, laborers = 0, carpenters = 0;
    for (int i = 0; i < parts_count(); ++i) {
        const building_mausoleum *p = m->part(i);
        if (!p) {
            continue;
        }
        if (p->part_has_active_worker()) {
            figure *f = figure_get(p->worker_figure_id());
            if (f->type == FIGURE_CARPENTER) {
                carpenters++;
            } else if (f->type == FIGURE_STONEMASON) {
                waiting += f->action_state == ACTION_19_MASON_WAIT_FOR_BLOCK;
                masons++;
            } else if (f->type == FIGURE_LABORER) {
                laborers++;
            }
        }
        const int kind = part_desc(i).kind & MAUSOLEUM_KIND_MASK;
        if (kind < MAUSOLEUM_BLOCKS) {
            const int done = count_subtiles(p->part_stage());
            missing += MAUSOLEUM_BLOCK_SUBTILES - done;
            material += (MAUSOLEUM_BLOCK_SUBTILES - done) * MAUSOLEUM_MATERIAL_PER_LOAD;
            if (done) {
                status = MAUSOLEUM_STATUS_STARTED;
            }
        } else if (kind <= 12 && kind != 11) {
            if (p->part_stage() == MAUSOLEUM_GROUND_UNTOUCHED) {
                stage0++;
                below2++;
            } else if (p->part_stage() == MAUSOLEUM_GROUND_LEVELED) {
                below2++;
            }
        }
    }
    if (stage0 == 0 && status == MAUSOLEUM_STATUS_SITE) {
        status = MAUSOLEUM_STATUS_STARTED;
    }
    if (full || low_done) {
        status = MAUSOLEUM_STATUS_BLOCKS_RISING;
    }
    const int percent = ((MAUSOLEUM_WORK_UNITS - below2 - missing - stage0) * 100) / MAUSOLEUM_WORK_UNITS;
    if (out) {
        out[MAUSOLEUM_PROGRESS_STATUS] = status;
        out[MAUSOLEUM_PROGRESS_PERCENT] = percent;
        out[MAUSOLEUM_PROGRESS_BLOCKS_LEFT] = blocks_left;
        out[MAUSOLEUM_PROGRESS_STONEMASONS] = masons;
        out[MAUSOLEUM_PROGRESS_STONEMASONS_WAITING] = waiting;
        out[MAUSOLEUM_PROGRESS_LABORERS] = laborers;
        out[MAUSOLEUM_PROGRESS_CARPENTERS] = carpenters;
        out[MAUSOLEUM_PROGRESS_MATERIAL] = material;
        out[MAUSOLEUM_PROGRESS_MATERIAL_TOTAL] = MAUSOLEUM_BLOCKS * MAUSOLEUM_BLOCK_SUBTILES * MAUSOLEUM_MATERIAL_PER_LOAD;
        out[MAUSOLEUM_PROGRESS_PARTS_BELOW_2] = below2;
    }
    return percent;
}

void building_mausoleum::finish_all() {
    building_mausoleum *m = main_mausoleum();
    if (!m) {
        return;
    }
    walk_parts(m, [](building_mausoleum *p) {
        auto &d = p->runtime_data();
        d.phase = MONUMENT_FINISHED;
        d.part_stage = (p->part_kind() < MAUSOLEUM_KIND_GROUND_FIRST) ? MAUSOLEUM_BLOCK_FULL : MAUSOLEUM_GROUND_FINISHED;
        p->clear_worker_figure();
        return false;
    });
    m->runtime_data().work_flags = MAUSOLEUM_BLOCKS_LOW_DONE | MAUSOLEUM_BLOCKS_FULL | MAUSOLEUM_GROUND_STARTED
        | MAUSOLEUM_GROUND_DONE | MAUSOLEUM_BLOCKS_FINISHED;
    m->refresh_part_images();
}

void building_mausoleum::set_phase(int phase) {
    if (phase == 0) {
        return;
    }
    finish_all();
}

void building_mausoleum::on_phase_changed(int /*old_phase*/, int /*current*/) {
    update_part_image();
}

int building_mausoleum::building_image_get() const {
    const auto &params = current_params();
    const uint32_t kind_word = part_kind_word();
    const int kind = kind_word & MAUSOLEUM_KIND_MASK;
    if (kind < MAUSOLEUM_KIND_GROUND_FIRST) {
        // OG: pack maus{skin}_{stage}{a-d}, camera bit picks image 0/1 inside the pack.
        const building_mausoleum *m = main_mausoleum();
        const int skin = m ? (int)(m->runtime_data().variant % 3) : 0;
        const int bit = ((((int)base.orientation + camera_view()) / 2) & 1);
        const int view = bit ? 1 : 2;
        const uint16_t stage = part_stage();
        const uint8_t flags = m ? m->runtime_data().work_flags : 0;
        const bool finished_flag = flags & (MAUSOLEUM_BLOCK_FINISHED_FIRST << kind);
        int band = 1;
        if ((m && m->is_finished()) || stage >= MAUSOLEUM_BLOCK_FULL) {
            band = 3;
        } else if ((stage & MAUSOLEUM_BLOCK_LOW_DONE_MASK) == MAUSOLEUM_BLOCK_LOW_DONE_MASK && finished_flag) {
            band = 2;
        }
        static const char letters[] = "abcd";
        bstring32 key;
        key.printf("m%d_%d%c%d", skin, band, letters[kind], view);
        int img = params.first_img(xstring(key.c_str()));
        if (img <= 0) {
            img = params.first_img("preview");
        }
        return img > 0 ? img : 0;
    }

    auto ground_img = [&](int offset) {
        bstring32 key;
        key.printf("g%d", offset);
        const int img = params.first_img(xstring(key.c_str()));
        return img > 0 ? img : 0;
    };

    const bool finished = is_finished() || part_stage() >= MAUSOLEUM_GROUND_FINISHED;
    if (finished) {
        if (kind <= 7) {
            return ground_img(kind - MAUSOLEUM_KIND_GROUND_FIRST);
        }
        static const int rotation[16] = {0, 1, 0, 1, 3, 2, 3, 2, 0, 1, 0, 1, 3, 2, 3, 2};
        const int rot = rotation[(camera_view() / 2) + ((base.orientation / 2) * 4)];
        const int opposite = (rot - 2) & 3;
        switch (kind) {
        case 8: return ground_img(4 + rot);
        case 9: return ground_img(4 + opposite);
        case 10: return ground_img(8 + 1 + opposite * 2);
        case 11: return ground_img(8 + opposite * 2);
        case 12: return ground_img(8 + rot * 2);
        default: return ground_img(8 + 1 + rot * 2);
        }
    }
    if (part_stage() == MAUSOLEUM_GROUND_LEVELED) {
        const int img = params.first_img(params.leveled);
        return img > 0 ? img : 0;
    }
    if (kind_word & MAUSOLEUM_KIND_WALKWAY) {
        const int img = params.first_img(params.unbuilt);
        return img > 0 ? img : 0;
    }
    return 0;
}

void building_mausoleum::update_part_image() {
    const auto &desc = part_desc(part_index());
    map_building_tiles_add(id(), tile(), std::max<int>(desc.size, 1), building_image_get(), TERRAIN_BUILDING);
}

void building_mausoleum::refresh_part_images() {
    building_mausoleum *m = main_mausoleum();
    if (m) {
        walk_parts(m, [](building_mausoleum *p) {
            p->update_part_image();
            return false;
        });
    }
}

bool building_mausoleum::needs_resources() const {
    return false;
}

bool building_mausoleum::need_carpenter() {
    return !is_finished() && has_work_for(FIGURE_CARPENTER);
}

bool building_mausoleum::need_stonemason() {
    if (is_finished()) {
        return false;
    }
    building_mausoleum *m = main_mausoleum();
    scrub_dead_workers(m->runtime_data().workers);
    const auto &w = m->runtime_data().workers;
    if (std::find(w.begin(), w.end(), 0) == w.end()) {
        return false;
    }
    return has_work_for(FIGURE_STONEMASON);
}

bool building_mausoleum::need_workers() const {
    return !is_finished() && has_work_for(FIGURE_LABORER);
}

void building_mausoleum::add_workers(figure_id fid) {
    building_mausoleum *m = main_mausoleum();
    if (!m) {
        return;
    }
    auto &workers = m->runtime_data().workers;
    scrub_dead_workers(workers);
    for (auto &wid : workers) {
        if (wid == 0) {
            wid = fid;
            return;
        }
    }
}

void building_mausoleum::remove_worker(figure_id fid) {
    building_mausoleum *m = main_mausoleum();
    if (!m) {
        return;
    }
    for (auto &wid : m->runtime_data().workers) {
        if (wid == fid) {
            wid = 0;
        }
    }
    walk_parts(m, [fid](building_mausoleum *p) {
        if (p->worker_figure_id() == fid) {
            p->clear_worker_figure();
        }
        return false;
    });
}

void building_mausoleum::preview::setup_preview_graphics(build_planner &planer) const {
    const vec2i ext = box_extent(g_camera.orientation);
    planer.init_tiles(ext.x, ext.y);
}

int building_mausoleum::preview::construction_place(build_planner &planer, tile2i /*start*/, tile2i end, int orientation, int variant) const {
    planer.last_created_building = nullptr;
    building *b = building_create(planer.build_type, origin_from_cursor(end), orientation);
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
    for (const auto &pr : maus_params().placement_resources) {
        if (pr.resource == RESOURCE_SANDSTONE) {
            sandstone_need = pr.count;
            break;
        }
    }
    if (sandstone_need > 0 && yards_available(RESOURCE_SANDSTONE) < sandstone_need) {
        return CAN_NOT_PLACE;
    }
    if (area_blocked_at(origin_from_cursor(end), box_extent(g_camera.orientation))) {
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
    for (const auto &pr : maus_params().placement_resources) {
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

void building_mausoleum::preview::ghost_preview(build_planner &planer, painter &ctx, tile2i /*start*/, tile2i end, vec2i /*pixel*/) const {
    const vec2i ext = box_extent(g_camera.orientation);
    const tile2i org = origin_from_cursor(end);
    int sandstone_need = 0;
    for (const auto &pr : maus_params().placement_resources) {
        if (pr.resource == RESOURCE_SANDSTONE) {
            sandstone_need = pr.count;
            break;
        }
    }
    const bool short_of_sandstone = sandstone_need > 0 && yards_available(RESOURCE_SANDSTONE) < sandstone_need;
    const bool blocked = has_unfinished_mausoleum() || short_of_sandstone || area_blocked_at(org, ext);
    draw_area_mask(ctx, org, ext.x, ext.y, blocked);
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
    const int view = g_camera.orientation;
    const uint8_t skin = (uint8_t)((variant < 0 ? 0 : variant) % 3);
    tile2i org = tile();

    auto &d = runtime_data();
    d.variant = skin;
    d.part_index = 0;
    d.part_stage = 0;
    d.work_flags = 0;
    d.phase = 0;
    d.view = (uint8_t)view;
    base.orientation = (uint8_t)view;
    base.prev_part_building_id = 0;
    base.next_part_building_id = 0;
    base.size = part_desc(0).size;
    const vec2i o0 = part_offset(0, view, view);
    base.tile = org.shifted(o0.x, o0.y);
    update_part_image();

    building *prev = &base;
    for (int i = 1; i < parts_count(); ++i) {
        const vec2i o = part_offset(i, view, view);
        building *b = building_create(BUILDING_MAUSOLEUM, org.shifted(o.x, o.y), view);
        if (!b || b->id <= 0) {
            for (building *p = &base; p;) {
                building *next = p->has_next() ? p->next() : nullptr;
                map_building_tiles_remove(p->id, p->tile);
                p->state = BUILDING_STATE_DELETED_BY_GAME;
                p = next;
            }
            return;
        }
        game_undo_add_building(b);
        if (auto *mp = b->dcast_mausoleum()) {
            auto &pd = mp->runtime_data();
            pd.variant = skin;
            pd.part_index = (uint8_t)i;
            pd.part_stage = 0;
            pd.work_flags = 0;
            pd.phase = 0;
            pd.view = (uint8_t)view;
        }
        b->orientation = (uint8_t)view;
        b->size = part_desc(i).size;
        b->prev_part_building_id = prev->id;
        b->next_part_building_id = 0;
        prev->next_part_building_id = b->id;
        prev = b;
    }
    refresh_part_images();
}

void building_mausoleum::update_day() {
    building_impl::update_day();
    if (!is_main() || is_finished()) {
        return;
    }

    scrub_dead_workers(runtime_data().workers);
    if (get_progress(nullptr) >= 100) {
        finish_all();
        city_message &message = city_message_post_with_popup_delay(
            MESSAGE_CAT_MONUMENTS, true, "mausoleum_congratulations", type(), tile().grid_offset());
        message.hide_img = true;
    }
}

void building_mausoleum::update_map_orientation(int /*map_orientation*/) {
    building_mausoleum *m = main_mausoleum();
    if (!m || !is_main()) {
        return;
    }
    const int view = g_camera.orientation;
    if (m->runtime_data().view == view) {
        refresh_part_images();
        return;
    }
    tile2i org = origin();
    walk_parts(m, [](building_mausoleum *p) {
        map_building_tiles_remove(p->id(), p->tile());
        return false;
    });
    walk_parts(m, [&](building_mausoleum *p) {
        const vec2i o = part_offset(p->part_index(), view, p->base.orientation);
        p->base.tile = org.shifted(o.x, o.y);
        p->runtime_data().view = (uint8_t)view;
        return false;
    });
    refresh_part_images();
}

tile2i building_mausoleum::center_point() const {
    const building_mausoleum *m = main_mausoleum();
    const vec2i ext = box_extent(m->base.orientation);
    return origin().shifted(ext.x / 2, ext.y / 2);
}

tile2i building_mausoleum::access_point() const {
    const building_mausoleum *m = main_mausoleum();
    const vec2i o = entry_offset(m->runtime_data().view, m->base.orientation);
    return origin().shifted(o.x, o.y);
}

grid_area building_mausoleum::get_area() const {
    const building_mausoleum *m = main_mausoleum();
    const vec2i ext = box_extent(m->base.orientation);
    tile2i start = origin();
    return {start, start.shifted(ext.x - 1, ext.y - 1)};
}

void building_mausoleum::bind_dynamic(io_buffer *iob, size_t /*version*/) {
    auto &d = runtime_data();

    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &d.burial_stock[i]);
    }
    iob->bind(BIND_SIGNATURE_UINT8, &d.part_index);
    iob->bind(BIND_SIGNATURE_UINT8, &d.work_flags);
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
    iob->bind(BIND_SIGNATURE_UINT16, &d.part_stage);
    iob->bind(BIND_SIGNATURE_UINT16, &d.og_part.worker_figure_id);
    iob->bind(BIND_SIGNATURE_UINT8, &d.view);
}

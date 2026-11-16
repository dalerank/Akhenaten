#include "monument_pyramid_figure.h"

#include "building/monument_mastaba.h"
#include "building/monument_mastaba_engine.h"
#include "building/monument_pyramid.h"
#include "building/monument_pyramid_engine.h"
#include "building/monuments.h"
#include "city/city_figures.h"
#include "core/calc.h"
#include "figure/figure.h"
#include "figuretype/figure_bricklayer.h"
#include "figuretype/figure_carpenter.h"
#include "figuretype/figure_sled.h"
#include "figuretype/figure_stonemason.h"
#include "figuretype/figure_worker.h"
#include "graphics/view/view.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "grid/terrain.h"

#include <algorithm>
#include <cmath>

monument_pyramid_figure g_monument_pyramid_figure;

building *monument_pyramid_figure::chain_head_for(building *any) const {
    if (!any) {
        return nullptr;
    }
    if (g_monument_pyramid_engine.uses_block_engine(any)) {
        return g_monument_pyramid_engine.chain_head(any);
    }
    if (mastaba_engine_is(any)) {
        return mastaba_chain_head(any);
    }
    if (auto *mon = any->dcast_monument()) {
        return &mon->main()->base;
    }
    return any->main();
}

int monument_pyramid_figure::part_height_of(building_id part_id) const {
    auto *ps = pyramid_part_state_get(part_id);
    if (!ps) {
        return 0;
    }
    building *part = building_get(part_id);
    building *head = part ? chain_head_for(part) : nullptr;
    if (head && g_monument_pyramid_engine.uses_block_engine(head)) {
        return g_monument_pyramid_engine.part_height(*ps);
    }
    return ps->blocks + ps->layer * monument_engine_config.blocks_per_layer;
}

building_id monument_pyramid_figure::part_id_by_subtype(building *head, int subtype) const {
    if (!head || subtype < 0) {
        return 0;
    }
    if (g_monument_pyramid_engine.uses_block_engine(head) && !mastaba_engine_is(head)) {
        svector<building *, PYRAMID_PARTS_CAPACITY> parts;
        g_monument_pyramid_engine.collect_parts(head, parts);
        for (building *p : parts) {
            auto *ps = pyramid_part_state_get(p->id);
            if (ps && ps->subtype == (uint8_t)subtype) {
                return p->id;
            }
        }
        return 0;
    }
    if (mastaba_engine_is(head)) {
        svector<building *, MASTABA_PARTS_CAPACITY> parts;
        mastaba_collect_parts(head, parts);
        for (building *p : parts) {
            auto *ps = pyramid_part_state_get(p->id);
            if (ps && ps->subtype == (uint8_t)subtype) {
                return p->id;
            }
        }
    }
    return 0;
}

const pyramid_entry_point *monument_pyramid_figure::entry_points_for(building *head, int &count) const {
    if (!head) {
        count = 0;
        return nullptr;
    }
    if (head->dcast_pyramid()) {
        const auto &tbl = building_pyramid::params_for_type(head->type).entry_points;
        count = (int)tbl.size();
        return count > 0 ? tbl.data() : nullptr;
    }
    if (mastaba_engine_is(head)) {
        const auto &tbl = building_mastaba::get_params(head->type).entry_points;
        count = (int)tbl.size();
        return count > 0 ? tbl.data() : nullptr;
    }
    count = 0;
    return nullptr;
}

int monument_pyramid_figure::rotated_tile_kind(building *part) const {
    if (!part) {
        return PYRAMID_PART_INNER;
    }
    auto *ps = pyramid_part_state_get(part->id);
    building *head = chain_head_for(part);
    if (!ps || !head) {
        return PYRAMID_PART_INNER;
    }

    int kind = PYRAMID_PART_INNER;
    if (g_monument_pyramid_engine.uses_block_engine(head) && !mastaba_engine_is(head)) {
        const int size = g_monument_pyramid_engine.size_variant(head);
        const int idx = size * PYRAMID_PARTS_CAPACITY + ps->subtype;
        if (idx >= 0 && idx < (int)pyramid_engine_config.part_kinds.size()) {
            kind = pyramid_engine_config.part_kinds[idx];
        }
    }

    const int rotation = g_camera.orientation / 2;
    if (kind < PYRAMID_PART_EDGE_TOP_LEFT) {
        kind += rotation;
        if (kind >= PYRAMID_PART_EDGE_TOP_LEFT) {
            kind -= PYRAMID_VIEW_COUNT;
        }
    } else if (kind < PYRAMID_PART_INNER) {
        kind += rotation;
        if (kind >= PYRAMID_PART_INNER) {
            kind -= PYRAMID_VIEW_COUNT;
        }
    }
    return kind;
}

void monument_pyramid_figure::neighbour_part_tile(int grid_offset, int rotation, building *head, int *x, int *y) const {
    if (!head || !x || !y) {
        return;
    }
    const int base = ((rotation & 3) * 3);
    for (int i = 0; i < 3; ++i) {
        const int32_t delta = pyramid_engine_config.neighbour_offsets[base + i];
        const building_id id = map_building_at(grid_offset + delta);
        if (!id) {
            continue;
        }
        building *p = building_get(id);
        if (p && chain_head_for(p) == head) {
            *x = p->tile.x();
            *y = p->tile.y();
            return;
        }
    }
}

const pyramid_paired_parts *monument_pyramid_figure::pair_table_for(building *head, int &count) const {
    count = 0;
    if (!head) {
        return nullptr;
    }
    if (head->dcast_pyramid()) {
        const auto &tbl = building_pyramid::params_for_type(head->type).part_pairs;
        count = (int)tbl.size();
        return count > 0 ? tbl.data() : nullptr;
    }
    if (mastaba_engine_is(head)) {
        const auto &tbl = building_mastaba::get_params(head->type).part_pairs;
        count = (int)tbl.size();
        return count > 0 ? tbl.data() : nullptr;
    }
    return nullptr;
}

building_id monument_pyramid_figure::part_pair(building* head, building_id part_id) const {
    auto* ps = pyramid_part_state_get(part_id);
    int count = 0;
    const pyramid_paired_parts* table = pair_table_for(head, count);
    if (!ps || !table) {
        return 0;
    }
    for (int i = 0; i < count; ++i) {
        if (table[i].second == (int16_t)ps->subtype) {
            return part_id_by_subtype(head, table[i].first);
        }
        if (table[i].first == (int16_t)ps->subtype) {
            return part_id_by_subtype(head, table[i].second);
        }
    }
    return 0;
}

template <typename Compare>
static void og_qsort(building_id* base, int count, Compare compare) {
    enum { QSORT_STACK = 30, QSORT_CUTOFF = 8 };
    if (count < 2) {
        return;
    }
    building_id* stack_lo[QSORT_STACK];
    building_id* stack_hi[QSORT_STACK];
    int depth = 0;
    building_id* lo = base;
    building_id* hi = base + count - 1;
    for (;;) {
        const int num = (int)(hi - lo) + 1;
        if (num <= QSORT_CUTOFF) {
            while (hi > lo) {
                building_id* maxp = lo;
                for (building_id* p = lo + 1; p <= hi; ++p) {
                    if (compare(*p, *maxp) > 0) {
                        maxp = p;
                    }
                }
                std::swap(*maxp, *hi);
                --hi;
            }
        } else {
            std::swap(lo[num >> 1], *lo);
            building_id* loguy = lo;
            building_id* higuy = hi + 1;
            for (;;) {
                do {
                    ++loguy;
                } while (loguy <= hi && compare(*loguy, *lo) <= 0);
                do {
                    --higuy;
                } while (higuy > lo && compare(*higuy, *lo) >= 0);
                if (higuy < loguy) {
                    break;
                }
                std::swap(*loguy, *higuy);
            }
            std::swap(*lo, *higuy);
            if ((higuy - lo) - 1 < hi - loguy) {
                if (loguy < hi) {
                    stack_lo[depth] = loguy;
                    stack_hi[depth] = hi;
                    depth++;
                }
                if (lo + 1 < higuy) {
                    hi = higuy - 1;
                    continue;
                }
            } else {
                if (lo + 1 < higuy) {
                    stack_lo[depth] = lo;
                    stack_hi[depth] = higuy - 1;
                    depth++;
                }
                if (loguy < hi) {
                    lo = loguy;
                    continue;
                }
            }
        }
        if (--depth < 0) {
            return;
        }
        lo = stack_lo[depth];
        hi = stack_hi[depth];
    }
}

void monument_pyramid_figure::sort_frontier(building_id* parts, int count) const {
    if (count < 2) {
        return;
    }
    building* first = building_get(parts[0]);
    building* head = first ? chain_head_for(first) : nullptr;
    if (!head) {
        return;
    }
    const int height = part_height_of(parts[0]);
    int entry_count = 0;
    const pyramid_entry_point* entries = entry_points_for(head, entry_count);
    building_id origin_id = parts[0];
    for (int i = 0; entries && i < entry_count; ++i) {
        origin_id = part_id_by_subtype(head, entries[i].part);
        if (entries[i].height >= height) {
            break;
        }
    }
    building* origin = building_get(origin_id);
    if (!origin || !origin->id) {
        origin = first;
    }
    const int ox = origin->tile.x();
    const int oy = origin->tile.y();
    auto distance = [&](building_id id) {
        building* b = building_get(id);
        const int dx = ox - b->tile.x();
        const int dy = oy - b->tile.y();
        int d = dy * dy + dx * dx;
        if (building_id pair = part_pair(head, id)) {
            building* p = building_get(pair);
            const int pdx = ox - p->tile.x();
            const int pdy = oy - p->tile.y();
            d = std::max(d, pdy * pdy + pdx * pdx);
        }
        return d;
    };
    og_qsort(parts, count, [&](building_id a, building_id b) { return distance(b) - distance(a); });
}

building_id monument_pyramid_figure::frontier_pair_part(building_id part_id,
    const svector<building_id, PYRAMID_PARTS_CAPACITY> &frontier, uint8_t *is_first) const {
    if (is_first) {
        *is_first = 0;
    }
    building *part = building_get(part_id);
    auto *ps = pyramid_part_state_get(part_id);
    building *head = part ? chain_head_for(part) : nullptr;
    int count = 0;
    const pyramid_paired_parts *table = pair_table_for(head, count);
    if (!ps || !table || count <= 0) {
        return 0;
    }
    for (int i = 0; i < count; ++i) {
        if (table[i].second == (int16_t)ps->subtype) {
            for (building_id id : frontier) {
                auto *fps = pyramid_part_state_get(id);
                if (fps && fps->subtype == (uint8_t)table[i].first) {
                    if (is_first) {
                        *is_first = 1;
                    }
                    return id;
                }
            }
            return 0;
        }
        if (table[i].first == (int16_t)ps->subtype) {
            for (building_id id : frontier) {
                auto *fps = pyramid_part_state_get(id);
                if (fps && fps->subtype == (uint8_t)table[i].second) {
                    return id;
                }
            }
            return 0;
        }
    }
    return 0;
}

int monument_pyramid_figure::pair_waiting_mason(building_id part_id,
    const svector<building_id, PYRAMID_PARTS_CAPACITY> &frontier) const {
    uint8_t is_first = 0;
    building_id pair = frontier_pair_part(part_id, frontier, &is_first);
    if (!pair) {
        return -1;
    }
    auto *ps = pyramid_part_state_get(pair);
    if (!ps || !ps->worker_figure_id) {
        return 0;
    }
    figure *f = figure_get(ps->worker_figure_id);
    if (!f) {
        return 0;
    }
    if (mason_waits_for_block(f)) {
        return (int)ps->worker_figure_id;
    }
    return 0;
}

int monument_pyramid_figure::part_mason_is_working(building_id part_id) const {
    auto *ps = pyramid_part_state_get(part_id);
    if (!ps || !ps->worker_figure_id) {
        return 0;
    }
    figure *worker = figure_get(ps->worker_figure_id);
    if (!worker || !worker->is_alive()) {
        return 0;
    }
    if (worker->type == FIGURE_STONEMASON && worker->action_state == ACTION_21_MASON_PYRAMID_WORK) {
        return 1;
    }
    if (worker->type == FIGURE_BRICKLAYER && worker->action_state == ACTION_2_BRICKLAYER_WORK) {
        return 1;
    }
    return 0;
}

int monument_pyramid_figure::mason_waits_for_block(const figure *mason) const {
    if (!mason || !mason->is_alive()) {
        return 0;
    }
    if (mason->type == FIGURE_BRICKLAYER && mason->action_state == ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK) {
        return 1;
    }
    if (mason->type == FIGURE_STONEMASON && mason->action_state == ACTION_19_MASON_WAIT_FOR_BLOCK) {
        return 1;
    }
    return 0;
}

int monument_pyramid_figure::laborer_brings_block_to(figure_id laborer_id, figure_id mason_id) const {
    figure *f = figure_get(laborer_id);
    if (!f || !f->is_alive() || f->type != FIGURE_LABORER) {
        return 0;
    }
    auto *w = f->dcast_worker();
    if (!w) {
        return 0;
    }
    const auto &rd = w->runtime_data();
    if (!rd.delivering_block) {
        return 0;
    }
    return rd.mason_fid == mason_id || f->leading_figure_id == mason_id;
}

void monument_pyramid_figure::stop_walk(figure *f, int fail_action) const {
    if (!f) {
        return;
    }
    walk_mode(f) = PYRAMID_WALK_NONE;
    f->advance_action(fail_action);
}

void monument_pyramid_figure::begin_on_layer(figure *f, int next_action) const {
    if (!f) {
        return;
    }
    walk_mode(f) = PYRAMID_WALK_ON_LAYER;
    f->advance_action(next_action);
}

int monument_pyramid_figure::worker_has_ramp_part(figure_id fid, building *head, const pyramid_entry_point *entries, int count) const {
    if (!head || !entries || count <= 0) {
        return 0;
    }
    for (int i = 0; i < count; ++i) {
        building_id id = part_id_by_subtype(head, entries[i].part);
        auto *ps = pyramid_part_state_get(id);
        if (ps && ps->worker_figure_id == fid && pyramid_engine_part_needs_ramp(id) != 0) {
            return 1;
        }
    }
    return 0;
}

int monument_pyramid_figure::first_frontier_height(building *head) const {
    if (!head) {
        return 0;
    }
    if (g_monument_pyramid_engine.uses_block_engine(head)) {
        svector<building_id, PYRAMID_PARTS_CAPACITY> frontier;
        pyramid_engine_find_frontier(head, frontier);
        if (frontier.empty()) {
            return -1;
        }
        return part_height_of(frontier[0]);
    }
    if (mastaba_engine_is(head)) {
        svector<building_id, MASTABA_PARTS_CAPACITY> frontier;
        mastaba_engine_find_frontier(head, frontier);
        if (frontier.empty()) {
            return -1;
        }
        return part_height_of(frontier[0]);
    }
    return -1;
}

int monument_pyramid_figure::ramp_next_step(figure_id fid, building_id part_id, int mode, const pyramid_entry_point *entries, int count, int *index) {
    figure *f = figure_get(fid);
    auto *work = work_data(f);
    auto *ps = pyramid_part_state_get(part_id);
    building *part = building_get(part_id);
    if (!f || !work || !ps || !part) {
        return RAMP_FAIL;
    }
    building *head = chain_head_for(part);
    if (!head) {
        return RAMP_FAIL;
    }

    if (mode == 1) {
        if (ps->worker_figure_id == fid) {
            return pyramid_engine_part_needs_ramp(part_id) != 0 ? RAMP_ON_LAYER : RAMP_FAIL;
        }
        if (!worker_has_ramp_part(fid, head, entries, count)) {
            return RAMP_FAIL;
        }
    }

    uint8_t &walk = walk_mode(f);
    if (walk == PYRAMID_WALK_START) {
        const int fh = first_frontier_height(head);
        if (fh < 0) {
            return RAMP_FAIL;
        }
        if (work->height >= fh) {
            return RAMP_ON_LAYER;
        }
        *index = 0;
        return RAMP_WALK_TO_ENTRY;
    }

    if (mode == 0 || mode == 2) {
        const int fh = first_frontier_height(head);
        if (fh < 0) {
            return RAMP_FAIL;
        }
        if (work->height >= fh) {
            return RAMP_ON_LAYER;
        }
    }

    int i = 0;
    for (; i < count; ++i) {
        if (entries[i].part == ps->subtype && entries[i].height == work->height) {
            break;
        }
    }
    if (i >= count) {
        return RAMP_FAIL;
    }
    ++i;
    if (i < count) {
        *index = i;
        return RAMP_WALK_TO_ENTRY;
    }
    if (mode == 1) {
        return RAMP_FAIL;
    }
    // OG: stonemason at casing frontier → NEXT_CASING_PART via RAMP_HANDLED.
    if (mode == 0 && f->type == FIGURE_STONEMASON) {
        svector<building_id, PYRAMID_PARTS_CAPACITY> frontier;
        if (g_monument_pyramid_engine.uses_block_engine(head) && !mastaba_engine_is(head)) {
            pyramid_engine_find_frontier(head, frontier);
        }
        if (!frontier.empty()) {
            auto *fps = pyramid_part_state_get(frontier[0]);
            if (fps && fps->stage == PYRAMID_STAGE_CASING) {
                f->advance_action(ACTION_20_MASON_NEXT_CASING);
                set_walk_target(fid, next_on_ring(work->part), work->height, false);
                return RAMP_HANDLED;
            }
        }
    }
    return RAMP_ON_LAYER;
}

void monument_pyramid_figure::walk_to_entry(figure_id fid, building_id part_id, int mode, const pyramid_entry_point &entry) {
    figure *f = figure_get(fid);
    auto *work = work_data(f);
    auto *ps = pyramid_part_state_get(part_id);
    building *part = building_get(part_id);
    if (!f || !work || !ps || !part) {
        return;
    }
    building *head = chain_head_for(part);
    building_id next_id = part_id_by_subtype(head, entry.part);
    if (!next_id) {
        return;
    }
    if (mode == 2 && pyramid_engine_part_needs_ramp(next_id) != 0) {
        return;
    }
    const bool same_part = next_id == work->part;
    set_walk_target(fid, next_id, entry.height, true);
    if (same_part) {
        work->progress = work->total;
    }
}

pyramid_figure_work_t *monument_pyramid_figure::work_data(figure *f) const {
    if (!f) {
        return nullptr;
    }
    if (auto *bl = f->dcast_bricklayer()) {
        return &bl->runtime_data().climb;
    }
    if (auto *cp = f->dcast_carpenter()) {
        return &cp->runtime_data().climb;
    }
    if (auto *sm = f->dcast_stonemason()) {
        return &sm->runtime_data().climb;
    }
    if (auto *w = f->dcast_worker()) {
        return &w->runtime_data().climb;
    }
    if (auto *sl = smart_cast<figure_sled>(f)) {
        return &sl->runtime_data().climb;
    }
    if (auto *sp = smart_cast<figure_sled_puller>(f)) {
        return &sp->runtime_data().climb;
    }
    return nullptr;
}

uint8_t &monument_pyramid_figure::walk_mode(figure *f) const {
    static uint8_t dummy = PYRAMID_WALK_NONE;
    if (!f) {
        return dummy;
    }
    if (auto *bl = f->dcast_bricklayer()) {
        return bl->runtime_data().walk_mode;
    }
    if (auto *cp = f->dcast_carpenter()) {
        return cp->runtime_data().walk_mode;
    }
    if (auto *sm = f->dcast_stonemason()) {
        return sm->runtime_data().walk_mode;
    }
    if (auto *w = f->dcast_worker()) {
        return w->runtime_data().walk_mode;
    }
    if (auto *sl = smart_cast<figure_sled>(f)) {
        return sl->runtime_data().walk_mode;
    }
    if (auto *sp = smart_cast<figure_sled_puller>(f)) {
        return sp->runtime_data().walk_mode;
    }
    return dummy;
}

building_id monument_pyramid_figure::work_part_bid(figure *f) const {
    if (!f) {
        return 0;
    }
    if (auto *bl = f->dcast_bricklayer()) {
        return bl->runtime_data().part_bid;
    }
    if (auto *sm = f->dcast_stonemason()) {
        return sm->runtime_data().part_bid;
    }
    return 0;
}

void monument_pyramid_figure::set_work_part_bid(figure *f, building_id part_id) const {
    if (!f) {
        return;
    }
    if (auto *bl = f->dcast_bricklayer()) {
        bl->runtime_data().part_bid = part_id;
    }
    if (auto *sm = f->dcast_stonemason()) {
        sm->runtime_data().part_bid = part_id;
    }
}

void monument_pyramid_figure::start_climb(figure_id fid) {
    figure *f = figure_get(fid);
    auto *work = work_data(f);
    if (!f || !work) {
        return;
    }
    walk_mode(f) = PYRAMID_WALK_START;
    // access_point can sit just outside the footprint — fall back to destination head.
    building_id part_id = map_building_at(f->destination_tile);
    if (!part_id) {
        part_id = map_building_at(f->tile);
    }
    if (!part_id) {
        if (building *dest = f->destination()) {
            if (building *head = chain_head_for(dest)) {
                part_id = head->id;
            }
        }
    }
    if (!part_id) {
        part_id = work_part_bid(f);
    }
    work->previous_part = part_id;
    work->previous_height = 0;
    work->part = part_id;
    work->height = 0;
    work->progress = 1;
    work->total = PYRAMID_STEPS_PER_TILE;
}

void monument_pyramid_figure::set_walk_target(figure_id fid, building_id part_id, int height, bool set_walk_mode_flag) {
    figure *f = figure_get(fid);
    auto *work = work_data(f);
    building *part = building_get(part_id);
    if (!f || !work || !part) {
        return;
    }

    // OG uses previous_part (pre-update) for facing, then shifts previous ← current.
    building *from = building_get(work->previous_part);
    work->previous_part = work->part;
    work->previous_height = work->height;
    work->part = part_id;
    work->height = (int16_t)height;

    f->destination_tile = part->tile;
    const int dx = std::abs(part->tile.x() - f->tile.x());
    const int dy = std::abs(part->tile.y() - f->tile.y());
    work->progress = 0;
    work->total = (int16_t)(std::sqrt((double)(dx * dx + dy * dy)) * PYRAMID_STEPS_PER_TILE);
    if (from) {
        f->direction = (uint8_t)calc_missile_shooter_direction(from->tile, part->tile);
    }
    if (!set_walk_mode_flag) {
        return;
    }
    switch (rotated_tile_kind(part)) {
    case PYRAMID_PART_CORNER_TOP:
    case PYRAMID_PART_CORNER_LEFT:
    case PYRAMID_PART_EDGE_TOP_LEFT:
    case PYRAMID_PART_EDGE_TOP_RIGHT:
        walk_mode(f) = PYRAMID_WALK_ALONG_Y;
        break;
    default:
        walk_mode(f) = PYRAMID_WALK_ALONG_X;
        break;
    }
}

int monument_pyramid_figure::climb_step(figure_id fid, int step) {
    figure *f = figure_get(fid);
    auto *work = work_data(f);
    if (!f || !work) {
        return 1;
    }
    if (work->total < 1) {
        return 1;
    }

    work->progress = (int16_t)(work->progress + step);
    int reached = 0;
    if (work->progress >= work->total) {
        reached = 1;
        work->progress = work->total;
    }

    building *prev = building_get(work->previous_part);
    building *target = building_get(work->part);
    if (!target) {
        return reached;
    }

    if (prev) {
        f->direction = (uint8_t)calc_missile_shooter_direction(prev->tile, target->tile);
    } else {
        f->direction = 0;
    }

    const int rotation = g_camera.orientation / 2;
    int x = target->tile.x();
    int y = target->tile.y();
    const uint8_t walk = walk_mode(f);

    if (!prev) {
        // stay on target
    } else if (walk == PYRAMID_WALK_ON_LAYER) {
        building *head = chain_head_for(prev);
        const int progress = work->progress;
        const int total = work->total;
        const int tile_x = ((target->tile.x() - prev->tile.x()) * progress) / total + prev->tile.x();
        const int tile_y = ((target->tile.y() - prev->tile.y()) * progress) / total + prev->tile.y();
        tile2i mid(tile_x, tile_y);
        building_id mid_id = map_building_at(mid);
        building *b = mid_id ? building_get(mid_id) : nullptr;
        if (b) {
            x = b->tile.x();
            y = b->tile.y();
            if (head) {
                neighbour_part_tile(b->tile.grid_offset(), rotation, head, &x, &y);
            }
        } else {
            x = tile_x;
            y = tile_y;
        }
    } else {
        const int kind = rotated_tile_kind(prev);
        int corner = 0;
        int facing = (int)f->direction - g_camera.orientation + 1;
        if (facing < 0) {
            facing += 8;
        }
        const int facing_back = facing <= 1 || facing >= 6;
        building *at = prev;
        switch (kind) {
        case PYRAMID_PART_CORNER_TOP:
        case PYRAMID_PART_EDGE_TOP_RIGHT:
            corner = 1;
            at = prev;
            break;
        case PYRAMID_PART_CORNER_LEFT:
        case PYRAMID_PART_CORNER_RIGHT:
            at = target;
            break;
        case PYRAMID_PART_EDGE_BOTTOM_LEFT:
            at = facing_back ? prev : target;
            break;
        default:
            at = prev;
            break;
        }
        x = at->tile.x();
        y = at->tile.y();
        if (corner) {
            building *head = chain_head_for(prev);
            if (head) {
                neighbour_part_tile(prev->tile.grid_offset(), (rotation - 2) & 3, head, &x, &y);
            }
        }
    }

    tile2i next(x, y);
    if (f->tile != next) {
        f->map_figure_remove();
        f->tile = next;
        f->map_figure_add();
    }
    return reached;
}

void monument_pyramid_figure::snap_to_part(figure_id fid) {
    figure *f = figure_get(fid);
    auto *work = work_data(f);
    if (!f || !work) {
        return;
    }
    building *part = building_get(work->part);
    if (!part) {
        return;
    }
    f->map_figure_remove();
    f->tile = f->destination_tile.valid() ? f->destination_tile : part->tile;
    f->map_figure_add();
    work->height = (int16_t)part_height_of(work->part);
    f->wait_ticks = 0;
}

void monument_pyramid_figure::walk_on_ramp(figure_id fid, int mode, int fail_action, int next_action) {
    figure *f = figure_get(fid);
    auto *work = work_data(f);
    if (!f || !work) {
        return;
    }

    building_id part_id = map_building_at(f->destination_tile);
    if (!part_id) {
        part_id = work->part;
    }
    if (!part_id) {
        if (building *dest = f->destination()) {
            if (building *head = chain_head_for(dest)) {
                part_id = head->id;
            }
        }
    }
    building *part = building_get(part_id);
    building *head = part ? chain_head_for(part) : nullptr;
    const bool on_monument = head
        && (g_monument_pyramid_engine.uses_block_engine(head) || mastaba_engine_is(head)
            || head->dcast_pyramid() || head->dcast_monument());
    if (!part || !on_monument) {
        f->poof();
        return;
    }

    if (climb_step(fid, 1) != 1) {
        return;
    }

    int count = 0;
    const pyramid_entry_point *entries = entry_points_for(head, count);
    if (!entries || count <= 0) {
        stop_walk(f, fail_action);
        return;
    }

    f->map_figure_remove();
    f->tile = f->destination_tile;
    f->map_figure_add();

    int index = 0;
    switch (ramp_next_step(fid, part_id, mode, entries, count, &index)) {
    case RAMP_WALK_TO_ENTRY:
        walk_to_entry(fid, part_id, mode, entries[index]);
        break;
    case RAMP_ON_LAYER:
        begin_on_layer(f, next_action);
        break;
    case RAMP_FAIL:
        stop_walk(f, fail_action);
        break;
    default:
        break;
    }
}

int monument_pyramid_figure::claim_next_part(figure_id fid, int set_height, int done_action, int next_action) {
    figure *f = figure_get(fid);
    auto *work = work_data(f);
    if (!f || !work) {
        return 0;
    }

    building_id part_id = map_building_at(f->tile);
    if (!part_id) {
        part_id = work->part;
    }
    building *part = building_get(part_id);
    if (!part) {
        return 0;
    }
    building *head = chain_head_for(part);
    if (!head || (!g_monument_pyramid_engine.uses_block_engine(head) && !mastaba_engine_is(head))) {
        return 0;
    }

    svector<building_id, PYRAMID_PARTS_CAPACITY> frontier;
    if (g_monument_pyramid_engine.uses_block_engine(head) && !mastaba_engine_is(head)) {
        pyramid_engine_find_frontier(head, frontier);
    } else {
        svector<building_id, MASTABA_PARTS_CAPACITY> mastaba_frontier;
        mastaba_engine_find_frontier(head, mastaba_frontier);
        for (building_id id : mastaba_frontier) {
            frontier.push_back(id);
        }
    }
    if (frontier.empty()) {
        return 0;
    }

    building *first = building_get(frontier[0]);
    building *first_head = first ? chain_head_for(first) : head;
    const int height = part_height_of(frontier[0]);
    if (set_height) {
        work->height = (int16_t)height;
    }
    if (height != work->height) {
        return 0;
    }

    int count = 0;
    const pyramid_entry_point *entries = entry_points_for(head, count);
    building_id ref_id = 0;
    if (entries && count > 0 && first_head) {
        for (int i = 0; i < count; ++i) {
            ref_id = part_id_by_subtype(first_head, entries[i].part);
            if (entries[i].height >= height) {
                break;
            }
        }
    }
    building *ref = building_get(ref_id);
    if (!ref) {
        ref = first;
    }
    if (!ref) {
        return 0;
    }
    const int ref_x = ref->tile.x();
    const int ref_y = ref->tile.y();

    const e_pyramid_style style = g_monument_pyramid_engine.style_of(head);
    building_id best_id = 0;
    int best_distance = 0;
    int best_pair_waiting = 0;
    int best_has_pair = 0;

    for (building_id id : frontier) {
        auto *ps = pyramid_part_state_get(id);
        building *b = building_get(id);
        if (!ps || !b) {
            continue;
        }

        const bool needs_main = g_monument_pyramid_engine.uses_block_engine(head)
                                  ? g_monument_pyramid_engine.needs_main_material(*ps, style)
                                  : true;
        switch (style) {
        case PYRAMID_STYLE_MASTABA:
        case PYRAMID_STYLE_TRUE:
        case PYRAMID_STYLE_STEPPED:
        case PYRAMID_STYLE_BENT:
            break;
        case PYRAMID_STYLE_MUDBRICK:
            if (f->type == FIGURE_BRICKLAYER ? !needs_main : needs_main) {
                continue;
            }
            break;
        default:
            continue;
        }

        int dx = ref_x - b->tile.x();
        int dy = ref_y - b->tile.y();
        int distance = (dx * dx) + (dy * dy);
        uint8_t is_first = 0;
        building_id pair_id = frontier_pair_part(id, frontier, &is_first);
        int has_pair;
        if (pair_id) {
            building *pair = building_get(pair_id);
            int pdx = ref_x - pair->tile.x();
            int pdy = ref_y - pair->tile.y();
            int pair_distance = (pdx * pdx) + (pdy * pdy);
            if (distance > pair_distance) {
                pair_distance = distance;
            }
            distance = pair_distance * 2;
            has_pair = 1;
        } else {
            distance *= 2;
            has_pair = 0;
        }
        const int pair_waiting = pair_waiting_mason(id, frontier) > 0;
        if (best_id != 0) {
            auto *best_ps = pyramid_part_state_get(best_id);
            const int best_worker = best_ps ? best_ps->worker_figure_id : 0;
            const int worker = ps->worker_figure_id;
            const int best_taken = best_worker > 0 && best_worker != fid;
            const int free = worker == 0 || worker == fid;
            if (!best_taken || !free) {
                if (!best_taken && !free) {
                    continue;
                }
                if (distance < best_distance) {
                    continue;
                }
                if (distance == best_distance && !(pair_waiting && !best_pair_waiting) && !(has_pair && !best_has_pair)) {
                    continue;
                }
            }
        }
        best_pair_waiting = pair_waiting;
        best_id = id;
        best_distance = distance;
        best_has_pair = has_pair;
    }

    if (!best_id) {
        return 0;
    }

    auto *best_ps = pyramid_part_state_get(best_id);
    if (!best_ps) {
        return 0;
    }
    const bool active_elsewhere = best_ps->worker_figure_id != 0 && best_ps->worker_figure_id != fid
        && (pyramid_engine_part_has_active_worker(best_id) || mastaba_engine_part_has_active_worker(best_id));
    if (active_elsewhere) {
        return 0;
    }
    if (best_ps->stage == PYRAMID_STAGE_CASING) {
        best_ps->worker_figure_id = 0;
        f->advance_action(done_action);
        return 1;
    }

    building_id old_part = work_part_bid(f);
    if (old_part && old_part != best_id) {
        if (auto *old_ps = pyramid_part_state_get(old_part)) {
            if (old_ps->worker_figure_id == fid) {
                old_ps->worker_figure_id = 0;
            }
        }
    }

    best_ps->worker_figure_id = fid;
    set_work_part_bid(f, best_id);
    walk_mode(f) = PYRAMID_WALK_ON_LAYER;
    f->advance_action(next_action);
    set_walk_target(fid, best_id, work->previous_height, false);
    return 1;
}

void monument_pyramid_figure::find_next_part(figure_id fid, int set_height, int fail_action, int done_action, int next_action) {
    if (!claim_next_part(fid, set_height, done_action, next_action)) {
        stop_walk(figure_get(fid), fail_action);
    }
}

building_id monument_pyramid_figure::next_on_ring(building_id part_id) const {
    building *part = building_get(part_id);
    auto *ps = pyramid_part_state_get(part_id);
    building *head = part ? chain_head_for(part) : nullptr;
    const auto &rings = pyramid_engine_config.part_rings;
    if (!ps || !head || rings.empty()) {
        return part_id;
    }
    const int subtype = ps->subtype;
    int ring = 0;
    while (subtype < rings[ring].down_first || subtype > rings[ring].up_last) {
        ++ring;
        if (ring >= (int)rings.size()) {
            return part_id;
        }
    }
    const pyramid_part_ring &r = rings[ring];
    int next_subtype = subtype;
    if (subtype >= r.down_first && subtype <= r.down_last) {
        next_subtype = (subtype == r.down_first) ? (r.down_last + 1) : (subtype - 1);
    } else if (subtype >= r.up_first && subtype <= r.up_last) {
        next_subtype = (subtype == r.up_last) ? (r.up_first - 1) : (subtype + 1);
    } else {
        next_subtype = (subtype & 1) ? (subtype - 2) : (subtype + 2);
    }
    building_id next_id = part_id_by_subtype(head, next_subtype);
    return next_id ? next_id : part_id;
}

void monument_pyramid_figure::stonemason_arrive_part(figure_id fid) {
    figure *f = figure_get(fid);
    auto *work = work_data(f);
    if (!f || !work) {
        return;
    }
    if (walk_mode(f) < PYRAMID_WALK_START) {
        f->advance_action(ACTION_6_MASON_RETURN_HOME);
        return;
    }
    if (climb_step(fid, 1) != 1) {
        return;
    }
    snap_to_part(fid);
    building_id part_id = work->part;
    building *part = building_get(part_id);
    building *head = part ? chain_head_for(part) : nullptr;
    if (!head) {
        f->advance_action(ACTION_6_MASON_RETURN_HOME);
        walk_mode(f) = PYRAMID_WALK_NONE;
        return;
    }

    svector<building_id, PYRAMID_PARTS_CAPACITY> frontier;
    pyramid_engine_find_frontier(head, frontier);
    for (building_id id : frontier) {
        if (id == part_id && !part_mason_is_working(id)) {
            f->advance_action(ACTION_21_MASON_PYRAMID_WORK);
            f->wait_ticks = 0;
            if (auto *ps = pyramid_part_state_get(id)) {
                ps->worker_figure_id = fid;
            }
            set_work_part_bid(f, id);
            return;
        }
    }

    building_id search_id = part_id;
    for (;;) {
        for (building_id id : frontier) {
            if (id == search_id && !part_mason_is_working(id)) {
                if (auto *ps = pyramid_part_state_get(id)) {
                    ps->worker_figure_id = fid;
                }
                set_work_part_bid(f, id);
                set_walk_target(fid, next_on_ring(part_id), work->height, true);
                return;
            }
        }
        search_id = next_on_ring(search_id);
        if (search_id == part_id) {
            f->advance_action(ACTION_6_MASON_RETURN_HOME);
            walk_mode(f) = PYRAMID_WALK_NONE;
            return;
        }
    }
}

static void collect_frontier(building* head, svector<building_id, PYRAMID_PARTS_CAPACITY>& frontier) {
    if (g_monument_pyramid_engine.uses_block_engine(head) && !mastaba_engine_is(head)) {
        pyramid_engine_find_frontier(head, frontier);
    } else if (mastaba_engine_is(head)) {
        svector<building_id, MASTABA_PARTS_CAPACITY> mf;
        mastaba_engine_find_frontier(head, mf);
        for (building_id id : mf) {
            frontier.push_back(id);
        }
    }
}

void monument_pyramid_figure::wake_pair_mason(figure_id mason_fid) {
    figure* mason = figure_get(mason_fid);
    if (!mason) {
        return;
    }
    building_id part_id = work_part_bid(mason);
    if (!part_id) {
        part_id = map_building_at(mason->destination_tile);
    }
    building* part = building_get(part_id);
    building* head = (part && part->id) ? chain_head_for(part) : nullptr;
    if (!head) {
        return;
    }
    svector<building_id, PYRAMID_PARTS_CAPACITY> frontier;
    collect_frontier(head, frontier);
    const int pair_fid = pair_waiting_mason(part_id, frontier);
    figure* pair = pair_fid > 0 ? figure_get(pair_fid) : nullptr;
    if (!pair) {
        return;
    }
    if (pair->type == FIGURE_BRICKLAYER) {
        pair->advance_action(ACTION_2_BRICKLAYER_WORK);
    } else if (pair->type == FIGURE_STONEMASON) {
        pair->advance_action(ACTION_21_MASON_PYRAMID_WORK);
    }
    pair->wait_ticks = 0;
}

building_id monument_pyramid_figure::find_mason_waiting_for_block(building* main, int clear_partner) {
    building* head = chain_head_for(main);
    if (!head) {
        return 0;
    }
    svector<building_id, PYRAMID_PARTS_CAPACITY> frontier;
    collect_frontier(head, frontier);
    sort_frontier(frontier.data(), (int)frontier.size());
    for (building_id id : frontier) {
        uint8_t is_first = 0;
        if (frontier_pair_part(id, frontier, &is_first) && is_first) {
            // OG skips pair-second; is_first means this subtype is the table's second → skip.
            continue;
        }
        auto *ps = pyramid_part_state_get(id);
        if (!ps || !ps->worker_figure_id) {
            continue;
        }
        if (!pyramid_engine_part_has_active_worker(id) && !mastaba_engine_part_has_active_worker(id)) {
            if (ps->worker_figure_id) {
                ps->worker_figure_id = 0;
            }
            continue;
        }
        figure *mason = figure_get(ps->worker_figure_id);
        if (!mason_waits_for_block(mason)) {
            continue;
        }
        int has_laborer = 0;
        int laborer_on_way = 0;
        figure_id laborer_id = mason->leading_figure_id;
        if (laborer_id && laborer_brings_block_to(laborer_id, mason->id)) {
            has_laborer = 1;
            figure *lab = figure_get(laborer_id);
            if (lab) {
                const int st = lab->action_state;
                if (st == ACTION_18_LABORER_CLIMB_RAMP || st == ACTION_19_LABORER_TO_MASON
                    || st == ACTION_20_LABORER_WALK_TO_MASON || st == ACTION_17_LABORER_TO_PYRAMID
                    || st == ACTION_29_LABORER_DELIVERED || st == ACTION_30_LABORER_SLED_AT_RAMP) {
                    laborer_on_way = 1;
                }
            }
        }
        if (pair_waiting_mason(id, frontier) == 0) {
            continue;
        }
        if (!has_laborer) {
            return mason->id;
        }
        if (!laborer_on_way && clear_partner) {
            mason->leading_figure_id = 0;
            return mason->id;
        }
    }
    return 0;
}

int monument_pyramid_figure::laborer_can_enter_ramp(figure_id fid) const {
    const figure *f = figure_get(fid);
    if (!f) {
        return 1;
    }
    if (f->routing_path_id <= 0) {
        return 1;
    }
    building_id part_id = map_building_at(f->destination_tile);
    building *part = building_get(part_id);
    building *head = part ? chain_head_for(part) : nullptr;
    if (!part_id || !head || (!g_monument_pyramid_engine.uses_block_engine(head) && !mastaba_engine_is(head))) {
        return 1;
    }
    const int remaining = f->routing_path_length - f->routing_path_current_tile;
    svector<building *, PYRAMID_PARTS_CAPACITY> parts;
    if (g_monument_pyramid_engine.uses_block_engine(head) && !mastaba_engine_is(head)) {
        g_monument_pyramid_engine.collect_parts(head, parts);
    } else {
        svector<building *, MASTABA_PARTS_CAPACITY> mp;
        mastaba_collect_parts(head, mp);
        for (building *p : mp) {
            parts.push_back(p);
        }
    }
    for (building *p : parts) {
        auto *ps = pyramid_part_state_get(p->id);
        if (!ps || !ps->worker_figure_id) {
            continue;
        }
        const figure *mason = figure_get(ps->worker_figure_id);
        if (!mason_waits_for_block(mason)) {
            continue;
        }
        figure_id laborer_id = mason->leading_figure_id;
        if (!laborer_id) {
            continue;
        }
        const figure *laborer = figure_get(laborer_id);
        if (laborer && laborer->type == FIGURE_LABORER && laborer->action_state == ACTION_17_LABORER_TO_PYRAMID
            && laborer->routing_path_id > 0
            && std::abs(laborer->routing_path_length - laborer->routing_path_current_tile - remaining) < PYRAMID_LABORER_NEAR_TILES) {
            return 0;
        }
    }
    return 1;
}

void monument_pyramid_figure::laborer_pair_with_mason(figure_id fid) {
    figure *f = figure_get(fid);
    if (!f) {
        return;
    }
    building_id part_id = map_building_at(f->destination_tile);
    if (!part_id) {
        auto *work = work_data(f);
        part_id = work ? work->part : 0;
    }
    building *part = building_get(part_id);
    building *head = part ? chain_head_for(part) : nullptr;
    if (!part_id || !head || (!g_monument_pyramid_engine.uses_block_engine(head) && !mastaba_engine_is(head))) {
        return;
    }

    figure *mason = nullptr;
    if (f->leading_figure_id) {
        mason = figure_get(f->leading_figure_id);
        building_id mason_part = 0;
        if (mason) {
            mason_part = map_building_at(mason->destination_tile);
            if (!mason_part) {
                mason_part = work_part_bid(mason);
            }
        }
        if (!mason_part || (!pyramid_engine_part_has_active_worker(mason_part) && !mastaba_engine_part_has_active_worker(mason_part))) {
            mason = nullptr;
        }
    }
    if (!mason) {
        figure_id mason_id = find_mason_waiting_for_block(head, 1);
        if (!mason_id) {
            return;
        }
        f->leading_figure_id = (int16_t)mason_id;
        mason = figure_get(mason_id);
        if (mason) {
            mason->leading_figure_id = (int16_t)fid;
        }
        if (auto *w = f->dcast_worker()) {
            w->runtime_data().mason_fid = mason_id;
        }
    }
    if (!mason) {
        return;
    }

    building_id mason_part_id = map_building_at(mason->destination_tile);
    if (!mason_part_id) {
        mason_part_id = work_part_bid(mason);
    }
    svector<building_id, PYRAMID_PARTS_CAPACITY> frontier;
    if (g_monument_pyramid_engine.uses_block_engine(head) && !mastaba_engine_is(head)) {
        pyramid_engine_find_frontier(head, frontier);
    } else {
        svector<building_id, MASTABA_PARTS_CAPACITY> mf;
        mastaba_engine_find_frontier(head, mf);
        for (building_id id : mf) {
            frontier.push_back(id);
        }
    }
    sort_frontier(frontier.data(), (int)frontier.size());
    int mason_index = 0;
    for (; mason_index < (int)frontier.size(); ++mason_index) {
        if (frontier[mason_index] == mason_part_id) {
            break;
        }
    }
    if (mason_index >= (int)frontier.size() || mason_index == 0) {
        return;
    }

    int best_index = mason_index;
    figure_id best_mason_id = 0;
    figure_id best_laborer_id = 0;
    svector<building *, PYRAMID_PARTS_CAPACITY> parts;
    if (g_monument_pyramid_engine.uses_block_engine(head) && !mastaba_engine_is(head)) {
        g_monument_pyramid_engine.collect_parts(head, parts);
    } else {
        svector<building *, MASTABA_PARTS_CAPACITY> mp;
        mastaba_collect_parts(head, mp);
        for (building *p : mp) {
            parts.push_back(p);
        }
    }
    for (building *p : parts) {
        auto *ps = pyramid_part_state_get(p->id);
        if (!ps || !ps->worker_figure_id) {
            continue;
        }
        uint8_t is_first = 0;
        if (frontier_pair_part(p->id, frontier, &is_first) && is_first) {
            continue;
        }
        figure *other_mason = figure_get(ps->worker_figure_id);
        if (!mason_waits_for_block(other_mason)) {
            continue;
        }
        figure_id other_laborer_id = other_mason->leading_figure_id;
        if (other_laborer_id == fid) {
            continue;
        }
        figure *other_laborer = other_laborer_id ? figure_get(other_laborer_id) : nullptr;
        if (other_laborer_id) {
            if (!other_laborer || other_laborer->leading_figure_id != other_mason->id) {
                other_mason->leading_figure_id = 0;
                other_laborer_id = 0;
            } else if (other_laborer->type != FIGURE_LABORER) {
                continue;
            } else {
                const int st = other_laborer->action_state;
                if (st != ACTION_15_LABORER_TO_STORAGE_YARD && st != ACTION_17_LABORER_TO_PYRAMID) {
                    continue;
                }
            }
        }
        int index = PYRAMID_NO_FRONTIER_INDEX;
        for (int i = 0; i < (int)frontier.size(); ++i) {
            if (frontier[i] == p->id) {
                index = i;
                break;
            }
        }
        if (index < best_index && other_laborer_id && f->collecting_item_id == other_laborer->collecting_item_id) {
            best_index = index;
            best_mason_id = other_mason->id;
            best_laborer_id = other_laborer_id;
        }
    }
    if (best_index == mason_index || !best_mason_id) {
        return;
    }
    figure_id old_mason_id = f->leading_figure_id;
    figure_get(best_mason_id)->leading_figure_id = (int16_t)fid;
    f->leading_figure_id = (int16_t)best_mason_id;
    if (auto *w = f->dcast_worker()) {
        w->runtime_data().mason_fid = best_mason_id;
    }
    if (best_laborer_id) {
        figure_get(old_mason_id)->leading_figure_id = (int16_t)best_laborer_id;
        figure_get(best_laborer_id)->leading_figure_id = (int16_t)old_mason_id;
        if (auto *ol = figure_get(best_laborer_id)->dcast_worker()) {
            ol->runtime_data().mason_fid = old_mason_id;
        }
    }
}

void monument_pyramid_figure::follow_on_ground(figure_id fid, figure *f, const figure *leader, int distance) const {
    if (!f || !leader) {
        return;
    }
    int progress = leader->progress_on_tile - distance;
    if (progress < 0) {
        progress += PYRAMID_STEPS_PER_TILE;
    }
    f->progress_on_tile = (uint8_t)progress;
    if (f->progress_on_tile == PYRAMID_MOVEMENT_TILE_CHANGE_STEP) {
        const tile2i old = f->tile;
        if (f->tile != leader->tile) {
            f->map_figure_remove();
            f->tile = leader->tile;
            f->map_figure_add();
            f->previous_tile = old;
        }
    }
    if (f->progress_on_tile == 0) {
        f->previous_tile_direction = f->direction;
        f->direction = leader->direction;
    }
    f->advance_height();
}

int monument_pyramid_figure::follow_step_reaches_leader(figure_id fid, figure *f, const figure *leader, int climb_step_n, int distance) {
    auto *work = work_data(f);
    auto *lwork = work_data(const_cast<figure *>(leader));
    if (!work || !lwork) {
        return 0;
    }
    if (walk_mode(f) != PYRAMID_WALK_NONE) {
        if (work->part == lwork->part) {
            if ((work->progress + distance) < lwork->progress) {
                climb_step(fid, climb_step_n);
            }
            return 0;
        }
        return work->part != lwork->previous_part || climb_step(fid, climb_step_n);
    }
    if (walk_mode(const_cast<figure *>(leader)) != PYRAMID_WALK_NONE) {
        f->progress_on_tile++;
        if (f->progress_on_tile <= LABORER_TRAIN_CATCH_UP_TICKS) {
            return 0;
        }
        f->progress_on_tile = 0;
        return 1;
    }
    follow_on_ground(fid, f, leader, distance);
    return 0;
}

void monument_pyramid_figure::take_leader_walk(figure_id fid, figure *f, const figure *leader, int distance) {
    auto *work = work_data(f);
    auto *lwork = work_data(const_cast<figure *>(leader));
    if (!work || !lwork) {
        return;
    }
    int progress = lwork->progress - distance;
    walk_mode(f) = walk_mode(const_cast<figure *>(leader));
    work->total = lwork->total;
    work->progress = (int16_t)((progress < 0) ? 0 : progress);
    work->previous_part = lwork->previous_part;
    work->part = lwork->part;
    work->previous_height = lwork->previous_height;
    work->height = lwork->height;
    f->direction = leader->direction;
    climb_step(fid, 0);
}

void monument_pyramid_figure::follow_closely(figure_id fid, figure_id leader_id, int climb_step_n, int distance) {
    figure *f = figure_get(fid);
    figure *leader = figure_get(leader_id);
    if (!f || !leader || !leader->is_alive()) {
        return;
    }
    if (f->tile == f->source_tile) {
        f->set_flag(e_figure_flag_invisible, true);
    }
    if (walk_mode(f) != PYRAMID_WALK_NONE && walk_mode(leader) == PYRAMID_WALK_NONE) {
        walk_mode(f) = PYRAMID_WALK_NONE;
    }
    if (follow_step_reaches_leader(fid, f, leader, climb_step_n, distance)) {
        take_leader_walk(fid, f, leader, distance);
    }
    if (f->animctx.max_frames > 1) {
        f->animctx.frame = leader->animctx.frame;
    }
}

figure_id monument_pyramid_figure::find_train_leader(figure_id fid, int *position) const {
    figure *f = figure_get(fid);
    if (!f || !position) {
        return 0;
    }
    figure_id id = f->leading_figure_id;
    *position = 1;
    for (int i = 0; i < LABORER_TRAIN_MAX_LINKS; ++i) {
        figure *link = figure_get(id);
        if (!link || !link->is_alive()) {
            return 0;
        }
        if (link->type == FIGURE_LABORER) {
            return id;
        }
        (*position)++;
        id = link->leading_figure_id;
    }
    return 0;
}

namespace {
    bool laborer_pulls_train(const figure& laborer, bool with_tomb_sled) {
        const short action = laborer.action_state;
        if (action == laborer.dcast()->ferry_wait_action() || action == laborer.dcast()->ferry_ride_action()) {
            return true;
        }
        switch (action) {
        case ACTION_17_LABORER_TO_PYRAMID:
        case ACTION_30_LABORER_SLED_AT_RAMP:
        case ACTION_18_LABORER_CLIMB_RAMP:
        case ACTION_19_LABORER_TO_MASON:
        case ACTION_20_LABORER_WALK_TO_MASON:
        case ACTION_23_LABORER_SLED_TO_SUN_TEMPLE:
        case ACTION_34_LABORER_SLED_TO_CAESAREUM:
        case ACTION_35_LABORER_SLED_TO_LIGHTHOUSE:
        case ACTION_31_LABORER_SLED_TO_LIBRARY:
        case ACTION_26_LABORER_SLED_TO_MAUSOLEUM:
        case ACTION_37_LABORER_SLED_TO_MASTABA:
        case ACTION_29_LABORER_DELIVERED:
            return true;
        case ACTION_36_LABORER_SLED_TO_TOMB:
            return with_tomb_sled;
        default:
            return false;
        }
    }

    bool front_keeps_pulling(const figure* f, bool is_sled) {
        figure* front = figure_get(f->leading_figure_id);
        if (!front || !front->is_alive()) {
            return false;
        }
        if (front->type == FIGURE_LABORER) {
            return laborer_pulls_train(*front, is_sled);
        }
        return front->type == FIGURE_SLED_PULLER && front->action_state == ACTION_8_SLED_TRAIN_FOLLOW;
    }

    bool leader_on_ferry(const figure& leader) {
        return leader.action_state == leader.dcast()->ferry_ride_action();
    }
} // namespace

void monument_pyramid_figure::train_follow(figure_id fid, int is_sled) {
    figure *f = figure_get(fid);
    if (!f) {
        return;
    }
    int position = 0;
    figure_id leader_id = find_train_leader(fid, &position);
    figure *leader = figure_get(leader_id);
    if (!leader || !leader->is_alive() || f->action_state != ACTION_8_SLED_TRAIN_FOLLOW) {
        f->poof();
        return;
    }

    f->set_flag(e_figure_flag_invisible, false);
    f->use_cross_country = false;
    if (!front_keeps_pulling(f, is_sled)) {
        f->poof();
        return;
    }

    if (leader_on_ferry(*leader)) {
        f->set_flag(e_figure_flag_invisible, true);
        return;
    }

    int max_spacing = is_sled ? LABORER_SLED_SPACING : LABORER_PULLER_SPACING;
    int spacing = max_spacing;
    if (leader->action_state == ACTION_29_LABORER_DELIVERED) {
        const int sled_extra = is_sled ? (LABORER_SLED_SPACING - LABORER_PULLER_SPACING) : 0;
        spacing = (LABORER_PULLER_SPACING * position) - leader->wait_ticks + sled_extra;
        if (spacing < 1) {
            spacing = 1;
        } else if (spacing > max_spacing) {
            spacing = max_spacing;
        }
    }
    follow_closely(fid, f->leading_figure_id, 1, spacing);
}

void monument_pyramid_figure::spawn_sled_train(figure_id laborer_fid) {
    figure *laborer = figure_get(laborer_fid);
    if (!laborer) {
        return;
    }

    figure_id previous_id = laborer_fid;
    uint8_t side = 0;
    for (int i = 0; i < LABORER_SLED_PULLERS; ++i) {
        figure* puller = figure_create(FIGURE_SLED_PULLER, laborer->tile, 0);
        if (!puller || !puller->id) {
            return;
        }
        puller->action_state = ACTION_8_SLED_TRAIN_FOLLOW;
        puller->leading_figure_id = (int16_t)previous_id;
        puller->wait_ticks = 0;
        puller->roam_length = 0;
        if (auto *sp = smart_cast<figure_sled_puller>(puller)) {
            sp->runtime_data().walk_mode = PYRAMID_WALK_NONE;
            sp->runtime_data().side = side;
        }
        side = 1 - side;
        previous_id = puller->id;
    }

    create_sled(laborer, previous_id);
}

void monument_pyramid_figure::spawn_single_sled(figure_id laborer_fid) {
    figure *laborer = figure_get(laborer_fid);
    if (!laborer) {
        return;
    }
    if (figure* sled = create_sled(laborer, laborer_fid)) {
        // OG at_storage_yard_lamps: source (0,0), so the lone sled is never hidden on its spawn tile.
        sled->source_tile = tile2i::invalid;
    }
}

// Remake (gameplay_change_sled_pullers_flee): the pullers run off, the sled keeps the laborer's load
// where it stands and the laborer goes back to its camp empty-handed.
void monument_pyramid_figure::drop_train(figure_id member_fid) {
    int position = 0;
    const figure_id leader_id = find_train_leader(member_fid, &position);
    figure* laborer = figure_get(leader_id);
    if (!laborer || !laborer->is_alive()) {
        return;
    }

    svector<figure*, LABORER_TRAIN_MAX_LINKS> members;
    for (figure* f : map_figures()) {
        if (!f || !f->is_alive() || (f->type != FIGURE_SLED && f->type != FIGURE_SLED_PULLER) || members.full()) {
            continue;
        }
        if (find_train_leader(f->id, &position) == leader_id) {
            members.push_back(f);
        }
    }

    for (figure* m : members) {
        if (m->type == FIGURE_SLED) {
            m->action_state = ACTION_9_SLED_DROPPED;
            m->leading_figure_id = 0;
            m->resource_amount_full = laborer->resource_amount_full;
            m->set_flag(e_figure_flag_invisible, false);
        } else {
            m->dcast()->begin_runaway();
        }
    }

    if (auto* worker = laborer->dcast_worker()) {
        worker->drop_load();
    }
}

figure* monument_pyramid_figure::create_sled(figure* laborer, figure_id front_id) {
    figure* sled = figure_create(FIGURE_SLED, laborer->tile, 0);
    if (!sled || !sled->id) {
        return nullptr;
    }
    sled->action_state = ACTION_8_SLED_TRAIN_FOLLOW;
    sled->resource_id = (e_resource)laborer->collecting_item_id;
    sled->leading_figure_id = (int16_t)front_id;
    sled->wait_ticks = 0;
    sled->roam_length = 0;
    if (auto *sl = smart_cast<figure_sled>(sled)) {
        sl->runtime_data().walk_mode = PYRAMID_WALK_NONE;
    }
    return sled;
}

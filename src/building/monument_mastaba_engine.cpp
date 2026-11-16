#include "monument_mastaba_engine.h"

#include "building/monument_mastaba.h"
#include "building/monument_pyramid_engine.h"
#include "building/monument_pyramid_figure.h"
#include "building/monuments.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "figure/figure.h"
#include "figuretype/figure_bricklayer.h"
#include "figuretype/figure_worker.h"
#include "js/js_game.h"

#include <algorithm>

monument_engine_config_t ANK_VARIABLE(monument_engine_config)
monument_mastaba_engine g_monument_mastaba_engine;

int monument_mastaba_engine::part_height(const pyramid_part_state &p) const {
    return p.blocks + p.layer * monument_engine_config.blocks_per_layer;
}

int monument_mastaba_engine::layer_capacity(const pyramid_part_state & /*p*/, bool is_main) const {
    if (is_main) {
        return 1;
    }
    return monument_engine_config.blocks_per_layer;
}

void monument_mastaba_engine::add_block(pyramid_part_state &p, bool is_main) const {
    if (p.stage == PYRAMID_STAGE_MAIN_MATERIAL) {
        int blocks = ++p.blocks;
        int capacity = layer_capacity(p, is_main);
        if (blocks >= capacity) {
            if (p.layer < p.target_layers) {
                if (blocks > capacity) {
                    p.layer++;
                    p.blocks = 1;
                }
            } else {
                p.stage = PYRAMID_STAGE_CASING;
                p.blocks = (uint8_t)std::max(1, capacity);
            }
        }
    } else if (p.blocks > 0) {
        p.blocks--;
    }
}

int monument_mastaba_engine::frontier_order(const pyramid_part_state &part, const pyramid_part_state &best) const {
    if (part.stage != best.stage) {
        return (part.stage != 0) ? 1 : -1;
    }
    if (part.stage == 0) {
        if (part.layer != best.layer) {
            return (part.layer < best.layer) ? -1 : 1;
        }
        return (part.blocks < best.blocks) ? -1 : (part.blocks != best.blocks);
    }
    if (part.layer != best.layer) {
        return (part.layer > best.layer) ? -1 : 1;
    }
    return (part.blocks > best.blocks) ? -1 : (part.blocks != best.blocks);
}

bool monument_mastaba_engine::needs_main_material(const pyramid_part_state &p) const {
    if (p.layer >= p.target_layers) {
        return false;
    }
    int capacity = layer_capacity(p, p.subtype == 0);
    return p.blocks != capacity || p.layer + 1 != p.target_layers;
}

pyramid_main_state *monument_mastaba_engine::main_state(building_id main_id) {
    building *b = building_get(main_id);
    auto *mon = b ? b->dcast_monument() : nullptr;
    if (!mon || !b->is_main()) {
        return nullptr;
    }
    auto &st = mon->runtime_data().og_main;
    return st.style != PYRAMID_STYLE_NONE ? &st : nullptr;
}

pyramid_part_state *monument_mastaba_engine::part_state(building_id part_id) {
    building *b = building_get(part_id);
    auto *mon = b ? b->dcast_monument() : nullptr;
    if (!mon) {
        return nullptr;
    }
    auto &ps = mon->runtime_data().og_part;
    // Inited if target_layers>0 (mastaba / inner pyramid) OR subtype>0 (square outer
    // ring may legitimately have target_layers==0) OR any progress/worker fields set.
    const bool inited = ps.target_layers != 0 || ps.subtype != 0 || ps.blocks != 0
        || ps.layer != 0 || ps.worker_figure_id != 0 || ps.stage != PYRAMID_STAGE_MAIN_MATERIAL;
    return inited ? &ps : nullptr;
}

pyramid_main_state &monument_mastaba_engine::ensure_main(building_id main_id) {
    building *b = building_get(main_id);
    auto *mon = b->dcast_monument();
    return mon->runtime_data().og_main;
}

pyramid_part_state &monument_mastaba_engine::ensure_part(building_id part_id) {
    building *b = building_get(part_id);
    auto *mon = b->dcast_monument();
    return mon->runtime_data().og_part;
}

void monument_mastaba_engine::clear_building(building_id id) {
    building *b = building_get(id);
    auto *mon = b ? b->dcast_monument() : nullptr;
    if (!mon) {
        return;
    }
    mon->runtime_data().og_main = {};
    mon->runtime_data().og_part = {};
}

void monument_mastaba_engine::clear_all() {
    buildings_valid_do([](building &b) {
        auto *mon = b.dcast_monument();
        if (!mon || !mastaba_engine_is(&b)) {
            return;
        }
        mon->runtime_data().og_main = {};
        mon->runtime_data().og_part = {};
    });
}

// Production JS helpers used by work_camp / guild scripts.
static int __pyramid_find_mason_waiting(int bid) {
    building *b = building_get(bid);
    building *head = b ? b->main() : nullptr;
    if (!head) {
        return 0;
    }
    if (mastaba_engine_is(head)) {
        return mastaba_engine_find_mason_waiting_for_block(head);
    }
    return g_monument_pyramid_figure.find_mason_waiting_for_block(head, 0);
}
ANK_FUNCTION_1(__pyramid_find_mason_waiting)

static void __worker_assign_brick_delivery(int fid, int monument_bid, int mason_fid) {
    figure *f = figure_get(fid);
    auto *worker = f ? f->dcast_worker() : nullptr;
    building *mon = building_get(monument_bid);
    if (!worker || !mon) {
        return;
    }
    if (!worker->assign_block_delivery(mon->main() ? mon->main() : mon, (figure_id)mason_fid)) {
        f->poof();
    }
}
ANK_FUNCTION_3(__worker_assign_brick_delivery)

building *mastaba_chain_head(building *any_part) {
    if (!any_part || !any_part->id) {
        return nullptr;
    }
    building *head = any_part;
    while (head->prev_part_building_id) {
        building *prev = building_get(head->prev_part_building_id);
        if (!prev || !prev->id) {
            break;
        }
        head = prev;
    }
    return head;
}

void mastaba_collect_parts(building *any_part, svector<building *, MASTABA_PARTS_CAPACITY> &out) {
    out.clear();
    building *head = mastaba_chain_head(any_part);
    for (building *p = head; p && p->id; p = p->has_next() ? p->next() : nullptr) {
        out.push_back(p);
        if ((int)out.size() >= monument_engine_config.mastaba_max_parts || out.size() >= MASTABA_PARTS_CAPACITY) {
            break;
        }
    }
}

pyramid_main_state *pyramid_main_state_get(building_id main_id) {
    return g_monument_mastaba_engine.main_state(main_id);
}

pyramid_part_state *pyramid_part_state_get(building_id part_id) {
    return g_monument_mastaba_engine.part_state(part_id);
}

void mastaba_engine_clear_building(building_id id) {
    g_monument_mastaba_engine.clear_building(id);
}

void mastaba_engine_clear_all() {
    g_monument_mastaba_engine.clear_all();
}

bool mastaba_engine_is(building *b) {
    if (!b) {
        return false;
    }
    const auto &p = building_mastaba::get_params(b->type);
    return p.part_count > 0 && p.brick_layers > 0;
}

bool mastaba_engine_block_phase_active(building *main) {
    auto *st = pyramid_main_state_get(main ? main->id : 0);
    return st && st->block_phase_active && st->remaining_blocks > 0;
}

void mastaba_engine_init(building *main) {
    if (!main) {
        return;
    }
    building *head = mastaba_chain_head(main);
    if (!head || !mastaba_engine_is(head)) {
        return;
    }

    const auto &cfg = building_mastaba::get_params(head->type);
    svector<building *, MASTABA_PARTS_CAPACITY> parts;
    mastaba_collect_parts(head, parts);
    const int n_parts = std::min((int)parts.size(), (int)cfg.part_count);
    if (n_parts <= 0) {
        return;
    }

    pyramid_main_state &ms = g_monument_mastaba_engine.ensure_main(head->id);
    ms.style = PYRAMID_STYLE_MASTABA;
    ms.size_variant = 0;
    int total_blocks = 0;
    if (auto *mon = head->dcast_monument()) {
        total_blocks = mon->brick_blocks_total();
    }
    ms.remaining_blocks = (uint16_t)std::max(0, total_blocks);
    ms.block_phase_active = 0;

    for (int i = 0; i < n_parts; i++) {
        pyramid_part_state &ps = g_monument_mastaba_engine.ensure_part(parts[i]->id);
        ps = {};
        ps.size_variant = 0;
        ps.subtype = (uint8_t)i;
        ps.target_layers = cfg.brick_layers;
        ps.stage = PYRAMID_STAGE_MAIN_MATERIAL;
        ps.worker_figure_id = 0;
    }
}

void mastaba_engine_start_block_phase(building *main) {
    building *head = mastaba_chain_head(main);
    if (!head) {
        return;
    }
    if (!pyramid_main_state_get(head->id)) {
        mastaba_engine_init(head);
    }
    auto *ms = pyramid_main_state_get(head->id);
    if (!ms) {
        return;
    }

    svector<building *, MASTABA_PARTS_CAPACITY> parts;
    mastaba_collect_parts(head, parts);
    for (building *p : parts) {
        if (auto *ps = pyramid_part_state_get(p->id)) {
            ps->stage = PYRAMID_STAGE_MAIN_MATERIAL;
            ps->blocks = 0;
            ps->layer = 0;
            ps->worker_figure_id = 0;
        }
    }
    int total_blocks = 0;
    if (auto *mon = head->dcast_monument()) {
        total_blocks = mon->brick_blocks_total();
    }
    ms->remaining_blocks = (uint16_t)std::max(0, total_blocks);
    ms->block_phase_active = 1;
}

bool mastaba_engine_blocks_finished(building *main) {
    building *head = mastaba_chain_head(main);
    auto *ms = pyramid_main_state_get(head ? head->id : 0);
    if (!ms || !ms->block_phase_active) {
        return false;
    }
    return ms->remaining_blocks == 0;
}

void monument_mastaba_engine::find_frontier(building *main, svector<building_id, MASTABA_PARTS_CAPACITY> &frontier) {
    frontier.clear();
    building *head = mastaba_chain_head(main);
    if (!head) {
        return;
    }

    svector<building *, MASTABA_PARTS_CAPACITY> parts;
    mastaba_collect_parts(head, parts);

    building_id best = 0;
    for (building *p : parts) {
        auto *ps = part_state(p->id);
        if (!ps) {
            continue;
        }
        // Mastaba: skip finished casing parts (stage!=0 and blocks==0).
        if (ps->stage != 0 && ps->blocks == 0) {
            continue;
        }
        int order = best ? frontier_order(*ps, *part_state(best)) : -1;
        if (order > 0) {
            continue;
        }
        if (order < 0) {
            frontier.clear();
            best = p->id;
        }
        frontier.push_back(p->id);
    }
}

void mastaba_engine_find_frontier(building *main, svector<building_id, MASTABA_PARTS_CAPACITY> &frontier) {
    g_monument_mastaba_engine.find_frontier(main, frontier);
}

bool mastaba_engine_part_has_active_worker(building_id part_id) {
    auto *ps = pyramid_part_state_get(part_id);
    if (!ps || !ps->worker_figure_id) {
        return false;
    }
    figure *f = figure_get(ps->worker_figure_id);
    if (!f || !f->is_alive()) {
        ps->worker_figure_id = 0;
        return false;
    }
    if (f->type != FIGURE_BRICKLAYER) {
        return false;
    }
    switch (f->action_state) {
    case ACTION_1_BRICKLAYER_GO_TO_SITE:
    case ACTION_4_BRICKLAYER_CLIMB_RAMP:
    case ACTION_5_BRICKLAYER_FIND_PART:
    case ACTION_7_BRICKLAYER_WALK_TO_PART:
    case ACTION_2_BRICKLAYER_WORK:
    case ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK:
        return true;
    default:
        ps->worker_figure_id = 0;
        return false;
    }
}

int mastaba_engine_try_assign_bricklayer(building *main, figure_id fid) {
    figure *f = figure_get(fid);
    building *head = mastaba_chain_head(main);
    if (!f || !head || !mastaba_engine_is(head)) {
        return 0;
    }
    auto *mon = head->dcast_monument();
    if (!mon || !mon->is_unfinished() || mon->phase() < MASTABA_PHASE_BRICKS) {
        return 0;
    }
    if (auto* mastaba = mon->dcast_mastaba()) {
        if (!mastaba->clay_stock_ready()) {
            return 0;
        }
    }
    auto *ms = pyramid_main_state_get(head->id);
    if (!ms) {
        mastaba_engine_init(head);
        mastaba_engine_start_block_phase(head);
        ms = pyramid_main_state_get(head->id);
    }
    if (!ms || !ms->block_phase_active || ms->remaining_blocks == 0) {
        return 0;
    }

    svector<building_id, MASTABA_PARTS_CAPACITY> frontier;
    mastaba_engine_find_frontier(head, frontier);
    for (building_id part_id : frontier) {
        auto *ps = pyramid_part_state_get(part_id);
        if (!ps) {
            continue;
        }
        if (ps->worker_figure_id && mastaba_engine_part_has_active_worker(part_id)) {
            continue;
        }
        ps->worker_figure_id = fid;

        auto *bl = f->dcast_bricklayer();
        if (!bl) {
            ps->worker_figure_id = 0;
            return 0;
        }
        auto &rd = bl->runtime_data();
        rd.destination_bid = head->id;
        rd.part_bid = part_id;
        rd.serving_statue = 0;
        // Non-NONE so WAIT_FOR_BLOCK keeps the claim (same as mudbrick pyramid).
        rd.walk_mode = PYRAMID_WALK_ON_LAYER;

        f->set_destination(head);
        f->destination_tile = mon->access_point();
        return part_id;
    }
    return 0;
}

void monument_mastaba_engine::apply_block_placed(building *head, pyramid_main_state &ms, pyramid_part_state &ps) {
    ms.remaining_blocks--;
    add_block(ps, ps.subtype == 0);

    auto *mon = head ? head->dcast_monument() : nullptr;
    if (!mon) {
        return;
    }

    // Advance remake visual phase from per-phase block quotas in construction config.
    const int total = mon->brick_blocks_total();
    if (total <= 0) {
        return;
    }
    const int done = total - ms.remaining_blocks;
    const int want = (ms.remaining_blocks == 0)
        ? MASTABA_PHASE_COMPLETE
        : mon->phase_for_blocks_done(done);
    if (want > mon->phase()) {
        building_impl *part_it = mon;
        while (part_it) {
            if (auto *m = part_it->dcast_monument()) {
                m->set_phase(want);
            }
            part_it = part_it->has_next() ? part_it->next() : nullptr;
        }
        mon->sync_visuals();
    }
    if (ms.remaining_blocks == 0) {
        ms.block_phase_active = 0;
        mon->sync_visuals();
    }

    // Laborers bring blocks, not stock: the info windows read the phase's brick share from resources_pct.
    const int phase = mon->phase();
    const int quota = mon->phase_blocks(phase);
    if (quota > 0) {
        int before = 0;
        for (int ph = 0; ph < phase; ++ph) {
            before += mon->phase_blocks(ph);
        }
        mon->runtime_data().resources_pct[RESOURCE_BRICKS] = (uint8_t)std::clamp((done - before) * 100 / quota, 0, 100);
    }
}

void monument_mastaba_engine::place_block(building_id part_id, figure_id fid) {
    figure *f = figure_get(fid);
    auto *ps = part_state(part_id);
    if (!f || !ps) {
        return;
    }
    auto *bl = f->dcast_bricklayer();
    if (!bl) {
        return;
    }
    auto &rd = bl->runtime_data();

    building *part = building_get(part_id);
    building *head = mastaba_chain_head(part);
    auto *ms = main_state(head ? head->id : 0);
    if (!ms || ms->remaining_blocks < 1) {
        f->advance_action(ACTION_3_BRICKLAYER_RETURN_HOME);
        rd.walk_mode = PYRAMID_WALK_NONE;
        return;
    }

    if (ps->worker_figure_id != fid && mastaba_engine_part_has_active_worker(part_id)) {
        f->advance_action(ACTION_3_BRICKLAYER_RETURN_HOME);
        rd.walk_mode = PYRAMID_WALK_NONE;
        return;
    }

    int ticks = (ps->stage == 0) ? (monument_engine_config.block_ticks_a + monument_engine_config.block_ticks_b) : monument_engine_config.casing_ticks;
    if (++f->wait_ticks < ticks) {
        return;
    }

    ps->worker_figure_id = 0;
    f->wait_ticks = 0;
    apply_block_placed(head, *ms, *ps);

    f->advance_action(ACTION_3_BRICKLAYER_RETURN_HOME);
    rd.walk_mode = PYRAMID_WALK_NONE;
}

int monument_mastaba_engine::boost_blocks(building *main, int max_count) {
    building *head = mastaba_chain_head(main);
    if (!head || !mastaba_engine_is(head)) {
        return 0;
    }

    auto *mon = head->dcast_monument();
    if (!mon || mon->is_finished() || mon->phase() < MASTABA_PHASE_BRICKS) {
        return 0;
    }

    auto *ms = main_state(head->id);
    if (!ms) {
        mastaba_engine_init(head);
        ms = main_state(head->id);
    }
    if (!ms) {
        return 0;
    }
    if (!ms->block_phase_active) {
        mastaba_engine_start_block_phase(head);
        ms = main_state(head->id);
    }
    if (!ms || !ms->block_phase_active || ms->remaining_blocks == 0) {
        return 0;
    }

    const int limit = max_count > 0 ? max_count : (int)ms->remaining_blocks;
    int placed = 0;
    while (placed < limit && ms->remaining_blocks > 0) {
        svector<building_id, MASTABA_PARTS_CAPACITY> frontier;
        find_frontier(head, frontier);
        g_monument_pyramid_figure.sort_frontier(frontier.data(), (int)frontier.size());
        if (frontier.empty()) {
            break;
        }

        auto *ps = part_state(frontier[0]);
        if (!ps) {
            break;
        }
        ps->worker_figure_id = 0;
        apply_block_placed(head, *ms, *ps);
        placed++;
    }
    return placed;
}

void mastaba_engine_place_block(building_id part_id, figure_id fid) {
    g_monument_mastaba_engine.place_block(part_id, fid);
}

int mastaba_engine_boost_blocks(building *main, int max_count) {
    return g_monument_mastaba_engine.boost_blocks(main, max_count);
}

building_id mastaba_engine_find_mason_waiting_for_block(building *main) {
    building *head = mastaba_chain_head(main);
    if (!head) {
        return 0;
    }
    svector<building *, MASTABA_PARTS_CAPACITY> parts;
    mastaba_collect_parts(head, parts);
    for (building *p : parts) {
        auto *ps = pyramid_part_state_get(p->id);
        if (!ps || !ps->worker_figure_id) {
            continue;
        }
        figure *f = figure_get(ps->worker_figure_id);
        if (f && f->is_alive() && f->type == FIGURE_BRICKLAYER
            && f->action_state == ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK) {
            return ps->worker_figure_id;
        }
    }
    return 0;
}

void mastaba_engine_laborer_deliver_block(figure_id mason_fid) {
    figure *mason = figure_get(mason_fid);
    if (!mason || mason->type != FIGURE_BRICKLAYER) {
        return;
    }
    if (mason->action_state != ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK) {
        return;
    }
    mason->wait_ticks = 0;
    mason->advance_action(ACTION_2_BRICKLAYER_WORK);
}

tile2i mastaba_engine_entry_tile(building *main) {
    building *head = mastaba_chain_head(main);
    if (!head) {
        return tile2i::invalid;
    }
    const auto &cfg = building_mastaba::get_params(head->type);
    const int entry_idx = cfg.entry_part;

    svector<building *, MASTABA_PARTS_CAPACITY> parts;
    mastaba_collect_parts(head, parts);
    const int n_parts = std::min((int)parts.size(), (int)cfg.part_count);
    if (entry_idx >= 0 && entry_idx < n_parts) {
        tile2i t = parts[entry_idx]->tile;
        return t.shifted(0, 2);
    }
    if (auto *mon = head->dcast_monument()) {
        return mon->access_point();
    }
    return head->tile;
}

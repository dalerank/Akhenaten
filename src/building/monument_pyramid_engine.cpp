#include "monument_pyramid_engine.h"

#include "building/monument_mastaba_engine.h"
#include "building/monument_pyramid.h"
#include "building/monuments.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "figure/figure.h"
#include "figuretype/figure_bricklayer.h"
#include "js/js_game.h"

#include <algorithm>

pyramid_engine_config_t ANK_VARIABLE(pyramid_engine_config)
monument_pyramid_engine g_monument_pyramid_engine;

building *monument_pyramid_engine::chain_head(building *any_part) const {
    if (!any_part) {
        return nullptr;
    }
    return any_part->main();
}

void monument_pyramid_engine::collect_parts(building *any_part, svector<building *, PYRAMID_PARTS_CAPACITY> &out) const {
    out.clear();
    building *head = chain_head(any_part);
    building *p = head;
    while (p) {
        if ((int)out.size() >= PYRAMID_PARTS_CAPACITY) {
            break;
        }
        out.push_back(p);
        p = p->has_next() ? p->next() : nullptr;
    }
}

int monument_pyramid_engine::size_variant(building *main) const {
    building *head = chain_head(main);
    if (!head) {
        return 0;
    }
    if (auto *pyr = head->dcast_pyramid()) {
        // Complex reuses LARGE corner/wall types (16×16); use monument footprint.
        const vec2i tiles = pyr->footprint_params().init_tiles;
        const int parts_edge = std::max(tiles.x, tiles.y) / 2;
        // 4→0, 6→1, 8→2, 10→3, 12→4
        const int idx = parts_edge / 2 - 2;
        return std::clamp(idx, 0, PYRAMID_SIZE_COUNT - 1);
    }
    return 0;
}

int monument_pyramid_engine::block_total(int size_variant) const {
    size_variant = std::clamp(size_variant, 0, PYRAMID_SIZE_COUNT - 1);
    return k_pyramid_block_totals[size_variant];
}

bool monument_pyramid_engine::is_mudbrick_type(e_building_type t) const {
    return building_pyramid::params_for_type(t).pyramide_type == PYRAMID_STYLE_MUDBRICK;
}

bool monument_pyramid_engine::is_mudbrick(building *b) const {
    if (!b) {
        return false;
    }
    building *head = chain_head(b);
    return head && is_mudbrick_type(head->type);
}

bool monument_pyramid_engine::block_phase_active(building *main) const {
    auto *st = pyramid_main_state_get(main ? main->main()->id : 0);
    return st && st->style == PYRAMID_STYLE_MUDBRICK && st->block_phase_active && st->remaining_blocks > 0;
}

// Size-0 (4×4 parts): OG layout gives layers=1 to the NW 2×2, layers=0 to the outer ring.
static uint8_t mudbrick_target_layers_for_part(building *head, building *part, int size_variant) {
    if (!head || !part) {
        return 0;
    }
    // Linked-list head can be a corner/wall — measure from geometric footprint NW.
    tile2i nw = head->tile;
    if (auto *pyr = head->dcast_pyramid()) {
        nw = pyr->footprint_nw();
    }
    const int dx = (part->tile.x() - nw.x()) / 2;
    const int dy = (part->tile.y() - nw.y()) / 2;
    const int ring = std::max(dx, dy);
    // Size 0 OG layout: NW 2×2 parts layers=1, outer ring layers=0.
    if (size_variant == 0) {
        return (ring <= 1) ? 1 : 0;
    }
    // side in 2×2 parts: 6/8/10/12 for size 1..4 (not 2+2*sv — that under-counted).
    const int side_parts = 4 + size_variant * 2;
    const int max_ring = side_parts - 1;
    const int from_outside = max_ring - ring;
    return (uint8_t)std::max(0, from_outside - (side_parts / 2 - 1));
}

void pyramid_engine_clear_all() {
}

void pyramid_engine_init_mudbrick(building *main) {
    if (!main) {
        return;
    }
    building *head = g_monument_pyramid_engine.chain_head(main);
    auto &engine = g_monument_pyramid_engine;
    if (!head || !engine.is_mudbrick(head)) {
        return;
    }

    const int size_variant = engine.size_variant(head);
    svector<building *, PYRAMID_PARTS_CAPACITY> parts;
    engine.collect_parts(head, parts);
    const int expect = k_pyramid_part_counts[size_variant];
    const int n_parts = std::min((int)parts.size(), expect);
    if (n_parts <= 0) {
        return;
    }

    pyramid_main_state &ms = g_monument_mastaba_engine.ensure_main(head->id);
    ms.style = PYRAMID_STYLE_MUDBRICK;
    ms.size_variant = (uint8_t)size_variant;
    ms.remaining_blocks = (uint16_t)engine.block_total(size_variant);
    ms.block_phase_active = 0;

    for (int i = 0; i < n_parts; i++) {
        pyramid_part_state &ps = g_monument_mastaba_engine.ensure_part(parts[i]->id);
        ps = {};
        ps.size_variant = (uint8_t)size_variant;
        ps.subtype = (uint8_t)i;
        ps.target_layers = mudbrick_target_layers_for_part(head, parts[i], size_variant);
        ps.stage = PYRAMID_STAGE_MAIN_MATERIAL;
        ps.worker_figure_id = 0;
    }
}

void pyramid_engine_start_block_phase(building *main) {
    building *head = g_monument_pyramid_engine.chain_head(main);
    if (!head) {
        return;
    }
    if (!pyramid_main_state_get(head->id) || pyramid_main_state_get(head->id)->style != PYRAMID_STYLE_MUDBRICK) {
        pyramid_engine_init_mudbrick(head);
    }
    auto *ms = pyramid_main_state_get(head->id);
    if (!ms || ms->style != PYRAMID_STYLE_MUDBRICK) {
        return;
    }

    svector<building *, PYRAMID_PARTS_CAPACITY> parts;
    g_monument_pyramid_engine.collect_parts(head, parts);
    for (building *p : parts) {
        if (auto *ps = pyramid_part_state_get(p->id)) {
            ps->stage = PYRAMID_STAGE_MAIN_MATERIAL;
            ps->blocks = 0;
            ps->layer = 0;
            ps->worker_figure_id = 0;
        }
    }
    ms->remaining_blocks = (uint16_t)g_monument_pyramid_engine.block_total(ms->size_variant);
    ms->block_phase_active = 1;
}

bool pyramid_engine_blocks_finished(building *main) {
    building *head = g_monument_pyramid_engine.chain_head(main);
    auto *ms = pyramid_main_state_get(head ? head->id : 0);
    if (!ms || ms->style != PYRAMID_STYLE_MUDBRICK || !ms->block_phase_active) {
        return false;
    }
    return ms->remaining_blocks == 0;
}

int monument_pyramid_engine::part_height(const pyramid_part_state &p) const {
    return p.blocks + p.layer * pyramid_engine_config.blocks_per_layer;
}

int monument_pyramid_engine::layer_capacity() const {
    return pyramid_engine_config.blocks_per_layer;
}

void monument_pyramid_engine::add_block(pyramid_part_state &p) const {
    if (p.stage == PYRAMID_STAGE_MAIN_MATERIAL) {
        int blocks = ++p.blocks;
        int capacity = layer_capacity();
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

int monument_pyramid_engine::frontier_order(const pyramid_part_state &part, const pyramid_part_state &best) const {
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

bool monument_pyramid_engine::needs_main_material(const pyramid_part_state &p) const {
    // OG pyramid_part_needs_main_material: bricklayers only while layer < target.
    if (p.stage != PYRAMID_STAGE_MAIN_MATERIAL) {
        return false;
    }
    if (p.layer >= p.target_layers) {
        return false;
    }
    const int capacity = layer_capacity();
    return p.blocks != capacity || p.layer + 1 != p.target_layers;
}

void monument_pyramid_engine::find_frontier(building *main, svector<building_id, PYRAMID_PARTS_CAPACITY> &frontier) {
    frontier.clear();
    building *head = chain_head(main);
    if (!head) {
        return;
    }

    svector<building *, PYRAMID_PARTS_CAPACITY> parts;
    collect_parts(head, parts);

    building_id best = 0;
    for (building *p : parts) {
        auto *ps = pyramid_part_state_get(p->id);
        if (!ps) {
            continue;
        }
        if (ps->stage != 0 && ps->blocks == 0) {
            continue;
        }
        // Boost/assign only parts that still need main bricks — otherwise
        // target_layers==0 parts drain remaining into a fake casing stage.
        if (ps->stage == PYRAMID_STAGE_MAIN_MATERIAL && !needs_main_material(*ps)) {
            continue;
        }
        if (pyramid_engine_part_needs_ramp(p->id) != 0) {
            continue;
        }
        int order = best ? frontier_order(*ps, *pyramid_part_state_get(best)) : -1;
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

void pyramid_engine_find_frontier(building *main, svector<building_id, PYRAMID_PARTS_CAPACITY> &frontier) {
    g_monument_pyramid_engine.find_frontier(main, frontier);
}

int pyramid_engine_part_needs_ramp(building_id /*part_id*/) {
    // Carpenter ramp thresholds deferred; allow block assignment.
    return 0;
}

bool pyramid_engine_part_has_active_worker(building_id part_id) {
    auto *ps = pyramid_part_state_get(part_id);
    if (!ps || !ps->worker_figure_id) {
        return false;
    }
    figure *f = figure_get(ps->worker_figure_id);
    if (!f || !f->is_alive()) {
        ps->worker_figure_id = 0;
        return false;
    }
    if (f->type == FIGURE_BRICKLAYER) {
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
    // Stonemason casing workers accepted once wired.
    ps->worker_figure_id = 0;
    return false;
}

void monument_pyramid_engine::apply_block_placed(building *head, pyramid_main_state &ms, pyramid_part_state &ps) {
    ms.remaining_blocks--;
    add_block(ps);

    if (auto *mon = head ? head->dcast_monument() : nullptr) {
        mon->sync_visuals();
    }
    if (ms.remaining_blocks == 0) {
        ms.block_phase_active = 0;
    }
}

void monument_pyramid_engine::place_block(building_id part_id, figure_id fid) {
    figure *f = figure_get(fid);
    auto *ps = pyramid_part_state_get(part_id);
    if (!f || !ps) {
        return;
    }
    auto *bl = f->dcast_bricklayer();
    if (!bl) {
        return;
    }
    auto &rd = bl->runtime_data();

    building *part = building_get(part_id);
    building *head = chain_head(part);
    auto *ms = pyramid_main_state_get(head ? head->id : 0);
    if (!ms || ms->remaining_blocks < 1) {
        f->advance_action(ACTION_3_BRICKLAYER_RETURN_HOME);
        rd.walk_mode = PYRAMID_WALK_NONE;
        return;
    }

    if (ps->worker_figure_id != fid && pyramid_engine_part_has_active_worker(part_id)) {
        f->advance_action(ACTION_3_BRICKLAYER_RETURN_HOME);
        rd.walk_mode = PYRAMID_WALK_NONE;
        return;
    }

    const int ticks = (ps->stage == 0)
        ? (pyramid_engine_config.block_ticks_a + pyramid_engine_config.block_ticks_b)
        : pyramid_engine_config.casing_ticks;
    if (++f->wait_ticks < ticks) {
        return;
    }

    ps->worker_figure_id = 0;
    f->wait_ticks = 0;
    apply_block_placed(head, *ms, *ps);

    f->advance_action(ACTION_3_BRICKLAYER_RETURN_HOME);
    rd.walk_mode = PYRAMID_WALK_NONE;
}

void pyramid_engine_place_block(building_id part_id, figure_id fid) {
    g_monument_pyramid_engine.place_block(part_id, fid);
}

int monument_pyramid_engine::boost_blocks(building *main, int max_count) {
    building *head = chain_head(main);
    if (!head || !is_mudbrick(head)) {
        return 0;
    }

    auto *mon = head->dcast_monument();
    if (!mon || mon->is_finished() || mon->phase() < 2) {
        return 0;
    }

    auto *ms = pyramid_main_state_get(head->id);
    if (!ms || ms->style != PYRAMID_STYLE_MUDBRICK) {
        pyramid_engine_init_mudbrick(head);
        ms = pyramid_main_state_get(head->id);
    }
    if (!ms) {
        return 0;
    }
    if (!ms->block_phase_active) {
        pyramid_engine_start_block_phase(head);
        ms = pyramid_main_state_get(head->id);
    }
    if (!ms || !ms->block_phase_active || ms->remaining_blocks == 0) {
        return 0;
    }

    const int limit = max_count > 0 ? max_count : (int)ms->remaining_blocks;
    int placed = 0;
    while (placed < limit && ms->remaining_blocks > 0) {
        svector<building_id, PYRAMID_PARTS_CAPACITY> frontier;
        find_frontier(head, frontier);
        if (frontier.empty()) {
            // Remake part target_layers can saturate before OG block_total —
            // still burn remaining so sync_footprint_layers / finish can complete.
            ms->remaining_blocks--;
            placed++;
            if (auto *mon = head->dcast_monument()) {
                mon->sync_visuals();
            }
            if (ms->remaining_blocks == 0) {
                ms->block_phase_active = 0;
            }
            continue;
        }
        auto *ps = pyramid_part_state_get(frontier[0]);
        if (!ps) {
            break;
        }
        ps->worker_figure_id = 0;
        apply_block_placed(head, *ms, *ps);
        placed++;
    }
    return placed;
}

int pyramid_engine_boost_blocks(building *main, int max_count) {
    return g_monument_pyramid_engine.boost_blocks(main, max_count);
}

int pyramid_engine_try_assign_bricklayer(building *main, figure_id fid) {
    figure *f = figure_get(fid);
    building *head = g_monument_pyramid_engine.chain_head(main);
    if (!f || !head || !g_monument_pyramid_engine.is_mudbrick(head)) {
        return 0;
    }
    auto *mon = head->dcast_monument();
    if (!mon || !mon->is_unfinished() || mon->phase() < 2) {
        return 0;
    }
    auto *ms = pyramid_main_state_get(head->id);
    if (!ms || ms->style != PYRAMID_STYLE_MUDBRICK) {
        pyramid_engine_init_mudbrick(head);
        pyramid_engine_start_block_phase(head);
        ms = pyramid_main_state_get(head->id);
    }
    if (!ms || !ms->block_phase_active || ms->remaining_blocks == 0) {
        return 0;
    }

    svector<building_id, PYRAMID_PARTS_CAPACITY> frontier;
    pyramid_engine_find_frontier(head, frontier);
    for (building_id part_id : frontier) {
        auto *ps = pyramid_part_state_get(part_id);
        if (!ps) {
            continue;
        }
        if (!g_monument_pyramid_engine.needs_main_material(*ps)) {
            continue;
        }
        if (ps->worker_figure_id && pyramid_engine_part_has_active_worker(part_id)) {
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
        rd.walk_mode = PYRAMID_WALK_ACTIVE;

        f->set_destination(head);
        f->destination_tile = mon->access_point();
        return part_id;
    }
    return 0;
}

building_id pyramid_engine_find_mason_waiting_for_block(building *main) {
    building *head = g_monument_pyramid_engine.chain_head(main);
    if (!head) {
        return 0;
    }
    svector<building *, PYRAMID_PARTS_CAPACITY> parts;
    g_monument_pyramid_engine.collect_parts(head, parts);
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

void pyramid_engine_laborer_deliver_block(figure_id mason_fid) {
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

tile2i pyramid_engine_entry_tile(building *main) {
    building *head = g_monument_pyramid_engine.chain_head(main);
    if (!head) {
        return tile2i::invalid;
    }
    if (auto *mon = head->dcast_monument()) {
        return mon->access_point();
    }
    return head->tile;
}

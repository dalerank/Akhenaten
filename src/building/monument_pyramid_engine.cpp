#include "monument_pyramid_engine.h"

#include "building/monument_mastaba_engine.h"
#include "building/monument_pyramid.h"
#include "building/monument_pyramid_ramp.h"
#include "building/monuments.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "figure/figure.h"
#include "figuretype/figure_bricklayer.h"
#include "figuretype/figure_carpenter.h"
#include "figuretype/figure_stonemason.h"
#include "grid/grid.h"
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

int monument_pyramid_engine::part_count(building *main) const {
    building *head = chain_head(main);
    if (!head) {
        return 0;
    }
    if (auto *pyr = head->dcast_pyramid()) {
        return (int)pyr->pyramid_params().part_count;
    }
    return 0;
}

int monument_pyramid_engine::block_total(building *main) const {
    building *head = chain_head(main);
    if (!head) {
        return 0;
    }
    if (auto *pyr = head->dcast_pyramid()) {
        return (int)pyr->pyramid_params().block_total;
    }
    return 0;
}

const std::array<int32_t, PYRAMID_PARTS_CAPACITY> &monument_pyramid_engine::part_grid_offsets() const {
    return pyramid_engine_config.part_grid_offsets;
}

const vec2i &monument_pyramid_engine::ramp_offset_at(int kind, int row) const {
    row = std::clamp(row, 0, PYRAMID_RAMP_OFFSET_ROWS - 1);
    return pyramid_engine_config.ramp_offsets[kind][row];
}

const hvector<pyramid_ramp_spec_t, 48> &monument_pyramid_engine::ramp_specs_for(building *head) const {
    static const hvector<pyramid_ramp_spec_t, 48> k_empty;
    building_pyramid *pyr = head ? head->dcast_pyramid() : nullptr;
    return pyr ? pyr->pyramid_params().ramps : k_empty;
}

void monument_pyramid_engine::offset_to_xy(int off, int &dx, int &dy) const {
    // Match OG signed grid split for negative offsets.
    dy = off / GRID_LENGTH;
    dx = off - dy * GRID_LENGTH;
    if (dx < -GRID_LENGTH / 2) {
        dx += GRID_LENGTH;
        dy -= 1;
    } else if (dx > GRID_LENGTH / 2) {
        dx -= GRID_LENGTH;
        dy += 1;
    }
}

void monument_pyramid_engine::size_norm_origin(int part_count, int &min_dx, int &min_dy) const {
    const int n = std::clamp(part_count, 0, (int)PYRAMID_PARTS_CAPACITY);
    const auto &offsets = part_grid_offsets();
    min_dx = 0;
    min_dy = 0;
    for (int i = 0; i < n; ++i) {
        int dx = 0, dy = 0;
        offset_to_xy(offsets[i], dx, dy);
        min_dx = std::min(min_dx, dx);
        min_dy = std::min(min_dy, dy);
    }
}

int monument_pyramid_engine::rotated_kind(int kind, int view) const {
    view &= 3;
    if (kind < PYRAMID_PART_EDGE_TOP_LEFT) {
        kind += view;
        if (kind > PYRAMID_PART_CORNER_RIGHT) {
            kind -= 4;
        }
    } else if (kind < PYRAMID_PART_INNER) {
        kind += view;
        if (kind > PYRAMID_PART_EDGE_TOP_RIGHT) {
            kind -= 4;
        }
    }
    return kind;
}

int monument_pyramid_engine::geometric_kind(tile2i nw, vec2i footprint, tile2i part_tile) const {
    const int max_x = nw.x() + footprint.x - 2;
    const int max_y = nw.y() + footprint.y - 2;
    const bool at_min_x = part_tile.x() <= nw.x();
    const bool at_min_y = part_tile.y() <= nw.y();
    const bool at_max_x = part_tile.x() >= max_x;
    const bool at_max_y = part_tile.y() >= max_y;
    if (at_min_x && at_min_y) return PYRAMID_PART_CORNER_TOP;
    if (at_min_x && at_max_y) return PYRAMID_PART_CORNER_LEFT;
    if (at_max_x && at_max_y) return PYRAMID_PART_CORNER_BOTTOM;
    if (at_max_x && at_min_y) return PYRAMID_PART_CORNER_RIGHT;
    if (at_min_x) return PYRAMID_PART_EDGE_TOP_LEFT;
    if (at_max_y) return PYRAMID_PART_EDGE_BOTTOM_LEFT;
    if (at_max_x) return PYRAMID_PART_EDGE_BOTTOM_RIGHT;
    if (at_min_y) return PYRAMID_PART_EDGE_TOP_RIGHT;
    return PYRAMID_PART_INNER;
}

int monument_pyramid_engine::layout_kind(building *head, int subtype) const {
    const int size = std::clamp(size_variant(head), 0, PYRAMID_SIZE_COUNT - 1);
    const int n = std::clamp(part_count(head), 0, (int)PYRAMID_PARTS_CAPACITY);
    if (subtype < 0 || subtype >= n) {
        return PYRAMID_PART_INNER;
    }
    const int kind = pyramid_engine_config.part_kinds[size * PYRAMID_PARTS_CAPACITY + subtype];
    if (kind < 0 || kind >= PYRAMID_PART_KIND_MAX) {
        return PYRAMID_PART_INNER;
    }
    return kind;
}

int monument_pyramid_engine::ramp_base_image(building &part, int kind, e_pyramid_style style) const {
    building *head = part.main();
    e_building_type t = head ? head->type : part.type;
    const auto &params = building_static_params::get(t);
    // PYRAMID_IMAGE_RAMP_BOTTOM_LEFT = group+109 → pack file *_00110 (wooden ramp).
    // empty_land (*_00109) is gravel / TOP_INNER — not a ramp sprite.
    int base = params.first_img("ramps");
    if (base <= 0) {
        // Legacy: empty_land was mistakenly used as ramp base (off-by-one).
        const int empty = params.first_img("empty_land");
        base = empty > 0 ? empty + 1 : 0;
    }
    if (base <= 0) {
        return 0;
    }
    if (kind == PYRAMID_PART_EDGE_BOTTOM_LEFT) {
        return base;
    }
    if (kind == PYRAMID_PART_EDGE_BOTTOM_RIGHT) {
        return base + (style == PYRAMID_STYLE_STEPPED ? 3 : 1);
    }
    if (style == PYRAMID_STYLE_STEPPED) {
        if (kind == PYRAMID_PART_CORNER_LEFT) return base + 6;
        if (kind == PYRAMID_PART_CORNER_BOTTOM) return base + 10;
        if (kind == PYRAMID_PART_CORNER_RIGHT) return base + 14;
    }
    return 0;
}

void monument_pyramid_engine::set_ramp_offsets(pyramid_part_state &ps, int kind, e_pyramid_style style) const {
    const int layer = std::max(1, pyramid_engine_config.blocks_per_layer);
    auto apply = [&](uint8_t height, int16_t &ox, int16_t &oy) {
        if (!height) {
            ox = oy = 0;
            return;
        }
        if (style == PYRAMID_STYLE_STEPPED) {
            // OG: row = ((height-1)%6 >= 3 ? 3 : 0) + kind*6 — only low/high shelf.
            const int r = ((height - 1) % layer >= 3 ? 3 : 0);
            const int k = std::clamp(kind, 0, PYRAMID_PART_KIND_MAX - 1);
            const auto &off = pyramid_engine_config.stepped_ramp_offsets[k][r];
            ox = (int16_t)off.x;
            oy = (int16_t)off.y;
            return;
        }
        const int row = (height - 1) % layer;
        const int k = std::clamp(kind, 0, PYRAMID_RAMP_KIND_COUNT - 1);
        const auto &base = pyramid_engine_config.ramp_base[k];
        const auto &off = ramp_offset_at(k, row);
        ox = (int16_t)(base.x + off.x);
        oy = (int16_t)(base.y + off.y);
    };
    apply(ps.ramp1_height, ps.ramp_image_x1, ps.ramp_image_y1);
    apply(ps.ramp2_height, ps.ramp_image_x2, ps.ramp_image_y2);
}

bool monument_pyramid_engine::is_mudbrick_type(e_building_type t) const {
    return building_pyramid::params_for_type(t).pyramide_type == PYRAMID_STYLE_MUDBRICK;
}

bool monument_pyramid_engine::uses_block_engine_type(e_building_type t) const {
    return building_pyramid::params_for_type(t).pyramide_type != PYRAMID_STYLE_NONE;
}

bool monument_pyramid_engine::is_mudbrick(building *b) const {
    if (!b) {
        return false;
    }
    building *head = chain_head(b);
    return head && is_mudbrick_type(head->type);
}

bool monument_pyramid_engine::uses_block_engine(building *b) const {
    if (!b) {
        return false;
    }
    building *head = chain_head(b);
    return head && uses_block_engine_type(head->type);
}

e_pyramid_style monument_pyramid_engine::style_of(building *b) const {
    building *head = chain_head(b);
    if (!head) {
        return PYRAMID_STYLE_NONE;
    }
    return building_pyramid::params_for_type(head->type).pyramide_type;
}

bool monument_pyramid_engine::block_phase_active(building *main) const {
    building *head = chain_head(main);
    auto *st = pyramid_main_state_get(head ? head->id : 0);
    return st && uses_block_engine(head) && st->block_phase_active && st->remaining_blocks > 0;
}

// Size-0 (4×4 parts): OG layout gives layers=1 to the NW 2×2, layers=0 to the outer ring.
static uint8_t square_target_layers_for_part(building *head, building *part, int size_variant) {
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

void pyramid_engine_init(building *main) {
    if (!main) {
        return;
    }
    building *head = g_monument_pyramid_engine.chain_head(main);
    auto &engine = g_monument_pyramid_engine;
    if (!head || !engine.uses_block_engine(head)) {
        return;
    }

    const e_pyramid_style style = engine.style_of(head);
    const int size_variant = engine.size_variant(head);
    const int expect = engine.part_count(head);
    svector<building *, PYRAMID_PARTS_CAPACITY> parts;
    engine.collect_parts(head, parts);
    const int n_parts = std::min((int)parts.size(), expect > 0 ? expect : (int)parts.size());
    if (n_parts <= 0) {
        return;
    }

    pyramid_main_state &ms = g_monument_mastaba_engine.ensure_main(head->id);
    ms.style = style;
    ms.size_variant = (uint8_t)size_variant;
    ms.remaining_blocks = (uint16_t)engine.block_total(head);
    ms.block_phase_active = 0;

    tile2i nw = head->tile;
    if (auto *pyr = head->dcast_pyramid()) {
        nw = pyr->footprint_nw();
    }
    for (int i = 0; i < n_parts; i++) {
        pyramid_part_state &ps = g_monument_mastaba_engine.ensure_part(parts[i]->id);
        ps = {};
        ps.size_variant = (uint8_t)size_variant;
        const int og = pyramid_ramp_og_subtype(expect > 0 ? expect : n_parts, nw, parts[i]->tile);
        ps.subtype = (uint8_t)(og >= 0 ? og : i);
        ps.target_layers = square_target_layers_for_part(head, parts[i], size_variant);
        ps.stage = PYRAMID_STAGE_MAIN_MATERIAL;
        ps.worker_figure_id = 0;
    }
}

void pyramid_engine_init_mudbrick(building *main) {
    pyramid_engine_init(main);
}

void pyramid_engine_start_block_phase(building *main) {
    building *head = g_monument_pyramid_engine.chain_head(main);
    if (!head) {
        return;
    }
    if (!g_monument_pyramid_engine.uses_block_engine(head)) {
        return;
    }
    auto *existing = pyramid_main_state_get(head->id);
    if (!existing || existing->style == PYRAMID_STYLE_NONE) {
        pyramid_engine_init(head);
    }
    auto *ms = pyramid_main_state_get(head->id);
    if (!ms) {
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
        pyramid_engine_clear_part_ramps(p->id);
    }
    ms->remaining_blocks = (uint16_t)g_monument_pyramid_engine.block_total(head);
    ms->block_phase_active = 1;
}

bool pyramid_engine_blocks_finished(building *main) {
    building *head = g_monument_pyramid_engine.chain_head(main);
    auto *ms = pyramid_main_state_get(head ? head->id : 0);
    if (!ms || !g_monument_pyramid_engine.uses_block_engine(head) || !ms->block_phase_active) {
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
        // OG casing: drop ramp segments taller than remaining blocks.
        if (p.ramp1_height > p.blocks) {
            p.ramp1_height = 0;
        }
        if (p.ramp2_height > p.blocks) {
            p.ramp2_height = 0;
        }
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
    if (f->type == FIGURE_CARPENTER) {
        switch (f->action_state) {
        case ACTION_1_CARPENTER_GO_TO_SITE:
        case ACTION_4_CARPENTER_CLIMB_RAMP:
        case ACTION_2_CARPENTER_WORK:
            return true;
        default:
            ps->worker_figure_id = 0;
            return false;
        }
    }
    if (f->type == FIGURE_STONEMASON) {
        switch (f->action_state) {
        case ACTION_1_MASON_GOING:
        case ACTION_16_MASON_CLIMB_RAMP:
        case ACTION_17_MASON_FIND_PART:
        case ACTION_18_MASON_WALK_TO_PART:
        case ACTION_19_MASON_WAIT_FOR_BLOCK:
        case ACTION_20_MASON_NEXT_CASING:
        case ACTION_21_MASON_PYRAMID_WORK:
            return true;
        default:
            ps->worker_figure_id = 0;
            return false;
        }
    }
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
    auto *sm = f->dcast_stonemason();
    if (!bl && !sm) {
        return;
    }
    uint8_t &walk = bl ? bl->runtime_data().walk_mode : sm->runtime_data().walk_mode;
    const short return_home = bl ? (short)ACTION_3_BRICKLAYER_RETURN_HOME : (short)ACTION_6_MASON_RETURN_HOME;

    building *part = building_get(part_id);
    building *head = chain_head(part);
    auto *ms = pyramid_main_state_get(head ? head->id : 0);
    if (!ms || ms->remaining_blocks < 1) {
        f->advance_action(return_home);
        walk = PYRAMID_WALK_NONE;
        return;
    }

    if (ps->worker_figure_id != fid && pyramid_engine_part_has_active_worker(part_id)) {
        f->advance_action(return_home);
        walk = PYRAMID_WALK_NONE;
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

    f->advance_action(return_home);
    walk = PYRAMID_WALK_NONE;
}

void pyramid_engine_place_block(building_id part_id, figure_id fid) {
    g_monument_pyramid_engine.place_block(part_id, fid);
}

int monument_pyramid_engine::boost_blocks(building *main, int max_count) {
    building *head = chain_head(main);
    if (!head || !uses_block_engine(head)) {
        return 0;
    }

    auto *mon = head->dcast_monument();
    if (!mon || mon->is_finished() || mon->phase() < 2) {
        return 0;
    }

    auto *ms = pyramid_main_state_get(head->id);
    if (!ms || ms->style == PYRAMID_STYLE_NONE) {
        pyramid_engine_init(head);
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
        const building_id part_id = frontier[0];
        ps->worker_figure_id = 0;
        apply_block_placed(head, *ms, *ps);
        // OG god-speed: build ramp immediately when the frontier part crosses a threshold.
        if (pyramid_engine_part_needs_ramp(part_id) != PYRAMID_RAMP_NONE) {
            pyramid_engine_build_ramp(part_id);
        }
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
        pyramid_engine_init(head);
        pyramid_engine_start_block_phase(head);
        ms = pyramid_main_state_get(head->id);
    }
    if (!ms || ms->style != PYRAMID_STYLE_MUDBRICK || !ms->block_phase_active || ms->remaining_blocks == 0) {
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
        // Non-NONE so WAIT_FOR_BLOCK (and early-assign tests) keep the claim;
        // climb/find_next_part will set START / ON_LAYER as they run.
        rd.walk_mode = PYRAMID_WALK_ON_LAYER;

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
        if (!f || !f->is_alive()) {
            continue;
        }
        if (f->type == FIGURE_BRICKLAYER && f->action_state == ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK) {
            return ps->worker_figure_id;
        }
        if (f->type == FIGURE_STONEMASON && f->action_state == ACTION_19_MASON_WAIT_FOR_BLOCK) {
            return ps->worker_figure_id;
        }
    }
    return 0;
}

void pyramid_engine_laborer_deliver_block(figure_id mason_fid) {
    figure *mason = figure_get(mason_fid);
    if (!mason) {
        return;
    }
    if (mason->type == FIGURE_BRICKLAYER && mason->action_state == ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK) {
        mason->wait_ticks = 0;
        mason->advance_action(ACTION_2_BRICKLAYER_WORK);
        return;
    }
    if (mason->type == FIGURE_STONEMASON && mason->action_state == ACTION_19_MASON_WAIT_FOR_BLOCK) {
        mason->wait_ticks = 0;
        mason->advance_action(ACTION_21_MASON_PYRAMID_WORK);
    }
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

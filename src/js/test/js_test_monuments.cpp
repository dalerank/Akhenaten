#include "js/test/js_test_common.h"

#include "building/building.h"
#include "building/building_delivery_path.h"
#include "building/building_storage_yard.h"
#include "building/construction_blessing.h"
#include "building/monument_caesareum.h"
#include "building/monument_mastaba.h"
#include "building/monument_mastaba_engine.h"
#include "building/monument_mausoleum.h"
#include "building/monument_obelisk.h"
#include "building/monument_pharos_lighthouse.h"
#include "building/monument_pyramid.h"
#include "building/monument_pyramid_engine.h"
#include "building/monument_pyramid_figure.h"
#include "building/monument_pyramid_ramp.h"
#include "building/monument_royal_tomb.h"
#include "building/monument_abu_simbel.h"
#include "building/monument_sphinx.h"
#include "building/monument_sun_temple.h"
#include "building/monument_alexandria_library.h"
#include "building/monuments.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "city/object_info.h"
#include "core/bstring.h"
#include "core/xstring.h"
#include "empire/trader_handler.h"
#include "figure/figure.h"
#include "figure/figure_impl.h"
#include "figure/formation.h"
#include "figuretype/figure_bricklayer.h"
#include "figuretype/figure_sled.h"
#include "figuretype/figure_carpenter.h"
#include "figuretype/figure_docker.h"
#include "figuretype/figure_plagued_citizen.h"
#include "figuretype/figure_stonemason.h"
#include "figuretype/figure_tomb_artisan.h"
#include "figuretype/figure_tomb_robber.h"
#include "figuretype/figure_worker.h"
#include "game/resource.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "grid/routing/routing.h"
#include "grid/terrain.h"
#include "scenario/scenario.h"

#include <algorithm>
#include <cstring>

static void __test_burial_provisions_force_dispatched(int resource, int dispatched) {
    if (resource <= RESOURCE_NONE || resource >= RESOURCES_MAX) {
        return;
    }
    // Reset this resource on non-preexisting tombs, then deposit exactly `dispatched`.
    // Otherwise a prior steal leaves tomb stock > 0 and migrate skips — city/tomb desync.
    buildings_valid_do([&](building& b) {
        auto* m = b.dcast_monument();
        if (!m || !b.is_main() || m->is_preexisting()) {
            return;
        }
        auto& d = m->runtime_data();
        if (resource >= 0 && resource < RESOURCES_MAX) {
            d.burial_stock[resource] = 0;
        }
    });
    g_scenario.monuments.burial_provisions[resource].dispatched = std::max(0, dispatched);
    burial_provisions_migrate_city_pool_to_tombs();
}
ANK_FUNCTION_2(__test_burial_provisions_force_dispatched);

static int __test_tomb_robber_try_spawn(int force_gates) {
    return figure_tomb_robber::try_spawn(force_gates != 0);
}
ANK_FUNCTION_1(__test_tomb_robber_try_spawn);

static int __test_tomb_robber_spawn_wave(int count) {
    return figure_tomb_robber::spawn_wave(count);
}
ANK_FUNCTION_1(__test_tomb_robber_spawn_wave);

static int __test_tomb_robber_commit_plunder(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_TOMB_ROBER) {
        return 0;
    }
    return figure_tomb_robber(f).commit_plunder() ? 1 : 0;
}
ANK_FUNCTION_1(__test_tomb_robber_commit_plunder);

static int __test_tomb_robber_arrest(int fid, int force) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_TOMB_ROBER) {
        return 0;
    }
    return figure_tomb_robber(f).arrest(force != 0) ? 1 : 0;
}
ANK_FUNCTION_2(__test_tomb_robber_arrest);

static void __test_monument_set_preexisting(int bid, int preexisting) {
    building* b = building_get(bid);
    auto* m = b ? b->dcast_monument() : nullptr;
    if (m) {
        m->set_preexisting(preexisting != 0);
    }
}
ANK_FUNCTION_2(__test_monument_set_preexisting);

static int __test_monument_is_preexisting(int bid) {
    building* b = building_get(bid);
    auto* m = b ? b->dcast_monument() : nullptr;
    return (m && m->is_preexisting()) ? 1 : 0;
}
ANK_FUNCTION_1(__test_monument_is_preexisting);

static int __test_monument_funeral_done(int bid) {
    building* b = building_get(bid);
    auto* m = b ? b->dcast_monument() : nullptr;
    return (m && m->has_funeral_done()) ? 1 : 0;
}
ANK_FUNCTION_1(__test_monument_funeral_done);

static void __test_monument_set_funeral_done(int bid, int done) {
    building* b = building_get(bid);
    auto* m = b ? b->dcast_monument() : nullptr;
    if (m) {
        m->set_funeral_done(done != 0);
    }
}
ANK_FUNCTION_2(__test_monument_set_funeral_done);

static e_building_type test_mastaba_params_type(building* head) {
    switch (head->type) {
    case BUILDING_MEDIUM_MASTABA:
    case BUILDING_MEDIUM_MASTABA_SIDE:
    case BUILDING_MEDIUM_MASTABA_WALL:
    case BUILDING_MEDIUM_MASTABA_ENTRANCE:
    case BUILDING_MEDIUM_MASTABA_RESERVED:
        return BUILDING_MEDIUM_MASTABA;
    case BUILDING_LARGE_MASTABA:
    case BUILDING_LARGE_MASTABA_SIDE:
    case BUILDING_LARGE_MASTABA_WALL:
    case BUILDING_LARGE_MASTABA_ENTRANCE:
    case BUILDING_LARGE_MASTABA_RESERVED:
        return BUILDING_LARGE_MASTABA;
    default:
        return BUILDING_SMALL_MASTABA;
    }
}

static void test_monument_apply_phase(building* head, int phase) {
    auto mm = head->dcast_monument();
    if (!mm) {
        return;
    }
    mm->set_phase(phase);
    for (building* p = head->has_next() ? head->next() : nullptr; p; p = p->has_next() ? p->next() : nullptr) {
        if (auto pm = p->dcast_monument()) {
            pm->set_phase(phase);
        }
    }
}

// Force a monument to `phase`. When advancing forward, walks one phase at a time so
// per-phase hooks (pyramid setup_phase_6, layer type changes, …) all fire — a direct
// jump used to skip them and left the first brick ring with missing edge textures.
static void __test_monument_set_phase(int bid, int phase) {
    building* b = building_get(bid);
    building* head = b ? b->main() : nullptr;
    auto mm = head ? head->dcast_monument() : nullptr;
    if (!mm) {
        return;
    }

    const int cur = (int)mm->runtime_data().phase;
    if (cur >= 0 && phase > cur) {
        for (int p = cur + 1; p <= phase; ++p) {
            test_monument_apply_phase(head, p);
        }
    } else {
        test_monument_apply_phase(head, phase);
    }

    const bool is_mastaba = head->dcast_mastaba();
    const bool is_pyramid = head->dcast_pyramid();
    if (!is_mastaba && !is_pyramid) {
        return;
    }

    // Fill every part's tiles so height ornaments use the current layer (progress >= 200).
    for (building* p = head; p; p = p->has_next() ? p->next() : nullptr) {
        grid_tiles part_tiles = map_grid_get_tiles(p, 0);
        for (auto& t : part_tiles) {
            map_monuments_set_progress(t, 200);
        }
    }

    if (is_mastaba) {
        const vec2i tiles = building_mastaba::get_params(test_mastaba_params_type(head)).init_tiles;
        if (mm->is_finished() || mm->phase() >= 8 || phase >= 8) {
            building_mastaba::finalize(head, tiles);
        } else if (phase >= 2) {
            building_mastaba::update_images(head, phase, tiles);
        }
    }
}
ANK_FUNCTION_2(__test_monument_set_phase);

static int __test_monument_phase(int bid) {
    building* b = building_get(bid);
    building* head = b ? b->main() : nullptr;
    auto mm = head ? head->dcast_monument() : nullptr;
    // phase is int8_t (MONUMENT_FINISHED = -1); phase() returns uint8_t and would yield 255.
    return mm ? (int)mm->runtime_data().phase : -999;
}
ANK_FUNCTION_1(__test_monument_phase);

// Halt / unhalt monument construction (MOTHBALLED). Used by construction-blessing tests.
static void __test_monument_set_halted(int bid, int halted) {
    building* b = building_get(bid);
    building* head = b ? b->main() : nullptr;
    auto* mm = head ? head->dcast_monument() : nullptr;
    if (!mm) {
        return;
    }
    const bool want = halted != 0;
    if ((bool)mm->is_construction_halted() != want) {
        mm->toggle_construction_halted();
    }
}
ANK_FUNCTION_2(__test_monument_set_halted);

static int __test_construction_blessing_cap(int bid) {
    building* b = building_get(bid);
    building* head = b ? b->main() : nullptr;
    auto* mm = head ? head->dcast_monument() : nullptr;
    return mm ? construction_blessing_cap_phase(*mm) : -1;
}
ANK_FUNCTION_1(__test_construction_blessing_cap);

static int __test_monument_next_part(int bid) {
    building* b = building_get(bid);
    building* head = b ? b->main() : nullptr;
    if (!head || !head->has_next()) {
        return 0;
    }
    return head->next()->id;
}
ANK_FUNCTION_1(__test_monument_next_part);

// 1 if every part in the monument chain has the given building state (e.g. MOTHBALLED=7).
static int __test_monument_chain_all_state(int bid, int state) {
    building* b = building_get(bid);
    building* head = b ? b->main() : nullptr;
    if (!head) {
        return 0;
    }
    for (building* part = head; part; part = part->has_next() ? part->next() : nullptr) {
        if ((int)part->state != state) {
            return 0;
        }
    }
    return 1;
}
ANK_FUNCTION_2(__test_monument_chain_all_state);

// Deliver resource loads into a monument (updates resources_pct like cart delivery).
// amount is resource units (same as deliver_resource); returns false if full / not a monument.
static bool __test_monument_add_resource(int bid, int resource, int amount) {
    building* b = building_get(bid);
    building* head = b ? b->main() : nullptr;
    auto mm = head ? head->dcast_monument() : nullptr;
    if (!mm || resource <= RESOURCE_NONE || resource >= RESOURCES_MAX || amount <= 0) {
        return false;
    }
    return mm->deliver_resource(static_cast<e_resource>(resource), amount);
}
ANK_FUNCTION_3(__test_monument_add_resource);

static bool __test_obelisk_place_scaffold(int bid) {
    building* b = building_get(bid);
    building* head = b ? b->main() : nullptr;
    auto* ob = head ? head->dcast_obelisk() : nullptr;
    return ob && ob->place_scaffold();
}
ANK_FUNCTION_1(__test_obelisk_place_scaffold);

// Current delivery progress for a resource on the monument (0..100+).
static int __test_monument_resource_pct(int bid, int resource) {
    building* b = building_get(bid);
    building* head = b ? b->main() : nullptr;
    auto mm = head ? head->dcast_monument() : nullptr;
    if (!mm || resource <= RESOURCE_NONE || resource >= RESOURCES_MAX) {
        return -1;
    }
    return mm->runtime_data().resources_pct[resource];
}
ANK_FUNCTION_2(__test_monument_resource_pct);

static int __pyramid_remaining_blocks(int bid) {
    building* b = building_get(bid);
    building* head = b ? b->main() : nullptr;
    auto* ms = pyramid_main_state_get(head ? head->id : 0);
    return ms ? (int)ms->remaining_blocks : -1;
}
ANK_FUNCTION_1(__pyramid_remaining_blocks);

static int __pyramid_casing_total(int bid) {
    building* b = building_get(bid);
    return b ? g_monument_pyramid_engine.casing_total(b) : -1;
}
ANK_FUNCTION_1(__pyramid_casing_total);

static void __pyramid_start_block_phase(int bid) {
    building* b = building_get(bid);
    building* head = b ? b->main() : nullptr;
    if (!head) {
        return;
    }
    if (g_monument_pyramid_engine.uses_block_engine(head)) {
        pyramid_engine_init(head);
        pyramid_engine_start_block_phase(head);
        return;
    }
    mastaba_engine_init(head);
    mastaba_engine_start_block_phase(head);
}
ANK_FUNCTION_1(__pyramid_start_block_phase);

static void __pyramid_laborer_wake_mason(int mason_fid) {
    pyramid_engine_laborer_deliver_block((figure_id)mason_fid);
    mastaba_engine_laborer_deliver_block((figure_id)mason_fid);
}
ANK_FUNCTION_1(__pyramid_laborer_wake_mason);

static int __pyramid_claim_bricklayer_task(int fid) {
    return building_monument_find_bricklayer_task((figure_id)fid);
}
ANK_FUNCTION_1(__pyramid_claim_bricklayer_task);

static int __test_pyramid_park_waiting_mason(int bid, int fid) {
    building* b = building_get(bid);
    building* head = b ? b->main() : nullptr;
    figure* f = figure_get(fid);
    if (!head || !f || !f->is_alive()) {
        return 0;
    }
    svector<building_id, PYRAMID_PARTS_CAPACITY> frontier;
    pyramid_engine_find_frontier(head, frontier);
    if (frontier.empty()) {
        return 0;
    }
    for (building_id id : frontier) {
        if (auto* ps = pyramid_part_state_get(id)) {
            ps->worker_figure_id = (figure_id)fid;
        }
    }
    f->set_destination(head);
    f->terrain_usage = TERRAIN_USAGE_ANY;
    g_monument_pyramid_figure.set_work_part_bid(f, frontier[0]);
    g_monument_pyramid_figure.walk_mode(f) = PYRAMID_WALK_ON_LAYER;
    f->action_state
      = f->type == FIGURE_BRICKLAYER ? ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK : ACTION_19_MASON_WAIT_FOR_BLOCK;
    return frontier[0];
}
ANK_FUNCTION_2(__test_pyramid_park_waiting_mason);

static int __test_pyramid_park_pair_masons(int bid, int fid_a, int fid_b) {
    building* b = building_get(bid);
    building* head = b ? b->main() : nullptr;
    auto* pyr = head ? head->dcast_pyramid() : nullptr;
    figure* fa = figure_get(fid_a);
    figure* fb = figure_get(fid_b);
    if (!pyr || !fa || !fb) {
        return 0;
    }
    svector<building_id, PYRAMID_PARTS_CAPACITY> frontier;
    pyramid_engine_find_frontier(head, frontier);
    for (const auto& pair : pyr->pyramid_params().part_pairs) {
        building_id first = 0;
        building_id second = 0;
        for (building_id id : frontier) {
            auto* ps = pyramid_part_state_get(id);
            if (ps && ps->subtype == pair.first) {
                first = id;
            }
            if (ps && ps->subtype == pair.second) {
                second = id;
            }
        }
        if (!first || !second) {
            continue;
        }
        pyramid_part_state_get(first)->worker_figure_id = (figure_id)fid_a;
        pyramid_part_state_get(second)->worker_figure_id = (figure_id)fid_b;
        g_monument_pyramid_figure.set_work_part_bid(fa, first);
        g_monument_pyramid_figure.set_work_part_bid(fb, second);
        g_monument_pyramid_figure.walk_mode(fa) = PYRAMID_WALK_ON_LAYER;
        g_monument_pyramid_figure.walk_mode(fb) = PYRAMID_WALK_ON_LAYER;
        fa->action_state = ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK;
        fb->action_state = ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK;
        return first;
    }
    return 0;
}
ANK_FUNCTION_3(__test_pyramid_park_pair_masons);

static int __test_pyramid_casing_part(int bid, int fid) {
    building* b = building_get(bid);
    building* head = b ? b->main() : nullptr;
    figure* f = figure_get(fid);
    auto* ps = head ? pyramid_part_state_get(head->id) : nullptr;
    if (!ps || !f) {
        return 0;
    }
    ps->stage = PYRAMID_STAGE_CASING;
    ps->blocks = 6;
    ps->worker_figure_id = (figure_id)fid;
    f->set_destination(head);
    f->destination_tile = head->tile;
    f->terrain_usage = TERRAIN_USAGE_ANY;
    g_monument_pyramid_figure.set_work_part_bid(f, head->id);
    g_monument_pyramid_figure.walk_mode(f) = PYRAMID_WALK_ON_LAYER;
    return head->id;
}
ANK_FUNCTION_2(__test_pyramid_casing_part);

static int __test_pyramid_boost_until_ramp(int bid) {
    building* b = building_get(bid);
    building* head = b ? b->main() : nullptr;
    if (!head) {
        return 0;
    }
    svector<building*, PYRAMID_PARTS_CAPACITY> parts;
    g_monument_pyramid_engine.collect_parts(head, parts);
    for (int step = 0; step < 4000; ++step) {
        svector<uint8_t, PYRAMID_PARTS_CAPACITY> before;
        for (building* p : parts) {
            auto* ps = pyramid_part_state_get(p->id);
            before.push_back(ps ? (uint8_t)(ps->ramp1_height + ps->ramp2_height) : 0);
        }
        if (pyramid_engine_boost_blocks(head, 1) == 0) {
            return 0;
        }
        for (int i = 0; i < (int)parts.size(); ++i) {
            auto* ps = pyramid_part_state_get(parts[i]->id);
            if (!ps || (uint8_t)(ps->ramp1_height + ps->ramp2_height) == before[i]) {
                continue;
            }
            if (ps->ramp2_height) {
                ps->ramp2_height = 0;
            } else {
                ps->ramp1_height = 0;
            }
            pyramid_engine_update_part_ramp_image(parts[i]->id);
            return parts[i]->id;
        }
    }
    return 0;
}
ANK_FUNCTION_1(__test_pyramid_boost_until_ramp);

static int __test_pyramid_level_layer(int part_id) {
    auto* ref = pyramid_part_state_get(part_id);
    building* part = building_get(part_id);
    building* head = part ? part->main() : nullptr;
    if (!ref || !head) {
        return 0;
    }
    svector<building*, PYRAMID_PARTS_CAPACITY> parts;
    g_monument_pyramid_engine.collect_parts(head, parts);
    int changed = 0;
    for (building* p : parts) {
        auto* ps = pyramid_part_state_get(p->id);
        if (ps && ps->stage == ref->stage && ps->layer == ref->layer && ps->blocks < ref->blocks) {
            ps->blocks = ref->blocks;
            changed++;
        }
    }
    return changed;
}
ANK_FUNCTION_1(__test_pyramid_level_layer);

static int __test_pyramid_frontier_index(int bid, int part_id) {
    building* b = building_get(bid);
    building* head = b ? b->main() : nullptr;
    if (!head) {
        return -1;
    }
    svector<building_id, PYRAMID_PARTS_CAPACITY> frontier;
    pyramid_engine_find_frontier(head, frontier);
    for (int i = 0; i < (int)frontier.size(); ++i) {
        if (frontier[i] == part_id) {
            return i;
        }
    }
    return -1;
}
ANK_FUNCTION_2(__test_pyramid_frontier_index);

static int __test_pyramid_part_needs_ramp(int part_id) {
    return pyramid_engine_part_needs_ramp((building_id)part_id);
}
ANK_FUNCTION_1(__test_pyramid_part_needs_ramp);

// Saved block-engine state of one monument part:
// "subtype,stage,blocks,layer,target_layers,worker,ramp1,ramp2,size_variant,alt_image,phase,stair,workers0,
//  stone_pct,bricks_pct,pottery_stock,remaining_blocks" or "".
static pcstr __test_monument_part_state(int part_id) {
    static bstring256 out;
    out.clear();
    building* b = building_get(part_id);
    auto* mon = b ? b->dcast_monument() : nullptr;
    if (!mon) {
        return out.c_str();
    }
    const auto& d = mon->runtime_data();
    const auto& p = d.og_part;
    out.printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", p.subtype, p.stage, p.blocks, p.layer,
      p.target_layers, p.worker_figure_id, p.ramp1_height, p.ramp2_height, p.size_variant, d.alt_image, d.phase,
      d.stair_index, d.workers[0], d.resources_pct[RESOURCE_STONE], d.resources_pct[RESOURCE_BRICKS],
      d.burial_stock[RESOURCE_POTTERY], d.og_main.remaining_blocks);
    return out.c_str();
}
ANK_FUNCTION_1(__test_monument_part_state);

// Writes recognisable values into every saved block-engine field of a part, so a lost byte shows after load.
static void __test_monument_part_fill(int part_id, int seed) {
    building* b = building_get(part_id);
    auto* mon = b ? b->dcast_monument() : nullptr;
    if (!mon) {
        return;
    }
    auto& p = mon->runtime_data().og_part;
    p.subtype = (uint8_t)(seed % 40);
    p.blocks = (uint8_t)(seed % 7 + 1);
    p.layer = (uint8_t)(seed % 5);
    p.target_layers = (uint8_t)(seed % 5 + 1);
    p.worker_figure_id = (uint16_t)(300 + seed);
    p.ramp1_height = (uint8_t)(seed % 6 + 1);
    p.ramp2_height = (uint8_t)(seed % 4 + 2);
    mon->runtime_data().workers[0] = (uint16_t)(500 + seed);
    if (b->is_main()) {
        auto& d = mon->runtime_data();
        d.resources_pct[RESOURCE_STONE] = (uint8_t)(seed % 90 + 5);
        d.resources_pct[RESOURCE_BRICKS] = 100;
        d.burial_stock[RESOURCE_POTTERY] = (uint8_t)(seed % 50 + 3);
    }
}
ANK_FUNCTION_2(__test_monument_part_fill);

// Building ids of the whole part chain, head first, comma separated.
static pcstr __test_monument_parts(int bid) {
    static bstring1024 out;
    out.clear();
    building* b = building_get(bid);
    building* part = b ? b->main() : nullptr;
    for (int guard = 0; part && part->id && guard < 400; ++guard) {
        out.append_fmt(out.empty() ? "%d" : ",%d", part->id);
        part = part->has_next() ? part->next() : nullptr;
    }
    return out.c_str();
}
ANK_FUNCTION_1(__test_monument_parts);

static int __pyramid_spawn_sled_train(int laborer_fid, int monument_bid) {
    figure* laborer = figure_get(laborer_fid);
    building* mon = building_get(monument_bid);
    if (!laborer || !laborer->is_alive() || !mon) {
        return 0;
    }
    const int before = __test_count_figures(FIGURE_SLED) + __test_count_figures(FIGURE_SLED_PULLER);
    pyramid_figure_spawn_sled_train((figure_id)laborer_fid);
    return (__test_count_figures(FIGURE_SLED) + __test_count_figures(FIGURE_SLED_PULLER)) - before;
}
ANK_FUNCTION_2(__pyramid_spawn_sled_train);

static int __pyramid_count_sled_train_followers(int laborer_fid) {
    int n = 0;
    for (int id = 1; id < MAX_FIGURES; ++id) {
        figure* f = figure_get(id);
        if (!f || !f->is_alive()) {
            continue;
        }
        if (f->type != FIGURE_SLED && f->type != FIGURE_SLED_PULLER) {
            continue;
        }
        if (f->action_state != 8) {
            continue;
        }
        int pos = 0;
        if (pyramid_figure_find_train_leader((figure_id)id, &pos) == (figure_id)laborer_fid) {
            ++n;
        }
    }
    return n;
}
ANK_FUNCTION_1(__pyramid_count_sled_train_followers);

// Train member at position (1 = right behind the laborer) whose leader is laborer_fid, 0 when none.
static int __pyramid_train_member(int laborer_fid, int position) {
    for (int id = 1; id < MAX_FIGURES; ++id) {
        figure* f = figure_get(id);
        if (!f || !f->is_alive() || (f->type != FIGURE_SLED && f->type != FIGURE_SLED_PULLER)) {
            continue;
        }
        int pos = 0;
        if (pyramid_figure_find_train_leader((figure_id)id, &pos) == (figure_id)laborer_fid && pos == position) {
            return id;
        }
    }
    return 0;
}
ANK_FUNCTION_2(__pyramid_train_member);

// Puts a sled on a ramp walk (previous_height < height) or back on the ground.
static int __test_sled_set_on_ramp(int fid, int on_ramp) {
    figure* f = figure_get(fid);
    auto* sled = f ? smart_cast<figure_sled>(f) : nullptr;
    if (!sled) {
        return 0;
    }
    auto& rd = sled->runtime_data();
    rd.walk_mode = on_ramp ? PYRAMID_WALK_ALONG_X : PYRAMID_WALK_NONE;
    rd.climb.previous_height = 0;
    rd.climb.height = on_ramp ? 1 : 0;
    sled->update_animation();
    return 1;
}
ANK_FUNCTION_2(__test_sled_set_on_ramp);

// Snap bricklayer/carpenter to monument access_point, start_climb, enter CLIMB_RAMP.
static int __pyramid_figure_begin_climb(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return 0;
    }
    building* dest = f->destination();
    auto* mon = dest ? dest->dcast_monument() : nullptr;
    if (!mon) {
        return 0;
    }
    const tile2i at = mon->access_point();
    if (at.valid()) {
        f->map_figure_remove();
        f->tile = at;
        f->destination_tile = at;
        f->map_figure_add();
    }
    pyramid_figure_start_climb((figure_id)fid);
    if (f->type == FIGURE_BRICKLAYER) {
        f->advance_action(ACTION_4_BRICKLAYER_CLIMB_RAMP);
    } else if (f->type == FIGURE_CARPENTER) {
        f->advance_action(ACTION_4_CARPENTER_CLIMB_RAMP);
    } else if (f->type == FIGURE_STONEMASON) {
        f->advance_action(ACTION_16_MASON_CLIMB_RAMP);
    } else if (f->type == FIGURE_LABORER) {
        f->advance_action(ACTION_18_LABORER_CLIMB_RAMP);
    } else {
        return 0;
    }
    return 1;
}
ANK_FUNCTION_1(__pyramid_figure_begin_climb);

static building_royal_tomb* test_royal_tomb_main(int bid) {
    building* b = building_get(bid);
    building* head = b ? b->main() : nullptr;
    return head ? head->dcast_royal_tomb() : nullptr;
}

static building_royal_tomb* test_royal_tomb_part(int bid, int index) {
    auto* tomb = test_royal_tomb_main(bid);
    return tomb ? tomb->part(index) : nullptr;
}

static int __test_royal_tomb_lamp_stock(int bid) {
    auto* tomb = test_royal_tomb_main(bid);
    return tomb ? tomb->lamp_stock() : -1;
}
ANK_FUNCTION_1(__test_royal_tomb_lamp_stock);

static int __test_royal_tomb_set_lamp_stock(int bid, int amount) {
    auto* tomb = test_royal_tomb_main(bid);
    if (!tomb) {
        return 0;
    }
    tomb->runtime_data().lamp_stock = (uint16_t)std::max(0, amount);
    tomb->refresh_part_images();
    return 1;
}
ANK_FUNCTION_2(__test_royal_tomb_set_lamp_stock);

// OG Valley terrain for a tomb whose placement click is (x, y): rock + rock-near-monument under
// every part, clear land under the entrance and around it.
static int __test_royal_tomb_paint_site(int type, int x, int y) {
    if (!building_royal_tomb::is_royal_tomb_type((e_building_type)type)) {
        return 0;
    }
    const auto& l = building_royal_tomb::layout_of((e_building_type)type);
    tile2i origin(x, y);
    for (int i = 0; i < l.part_count; ++i) {
        const auto& p = l.parts[i];
        for (int dy = 0; dy < p.size; ++dy) {
            for (int dx = 0; dx < p.size; ++dx) {
                tile2i t = origin.shifted(p.dx + dx, p.dy + dy);
                map_terrain_set(t.grid_offset(), i == l.last_part ? 0 : (TERRAIN_ROCK | TERRAIN_ROCK_NEAR_MONUMENT));
            }
        }
    }
    const auto& e = l.parts[l.last_part];
    tile2i entrance = origin.shifted(e.dx, e.dy);
    for (vec2i n : {vec2i{0, -1}, vec2i{0, 1}, vec2i{-1, 0}, vec2i{1, 0}}) {
        tile2i t = entrance.shifted(n.x, n.y);
        if (!map_terrain_is(t, TERRAIN_ROCK_NEAR_MONUMENT)) {
            map_terrain_set(t.grid_offset(), 0);
        }
    }
    return 1;
}
ANK_FUNCTION_3(__test_royal_tomb_paint_site);

static int __test_royal_tomb_can_place(int type, int x, int y) {
    return building_royal_tomb::can_place_at((e_building_type)type, tile2i(x, y)) ? 1 : 0;
}
ANK_FUNCTION_3(__test_royal_tomb_can_place);

static int __test_royal_tomb_part_count(int bid) {
    auto* tomb = test_royal_tomb_main(bid);
    if (!tomb) {
        return 0;
    }
    int n = 0;
    for (building* b = &tomb->base; b; b = b->has_next() ? b->next() : nullptr) {
        n++;
    }
    return n;
}
ANK_FUNCTION_1(__test_royal_tomb_part_count);

static int __test_royal_tomb_chambers(int bid) {
    auto* tomb = test_royal_tomb_main(bid);
    return tomb ? tomb->layout().chambers : 0;
}
ANK_FUNCTION_1(__test_royal_tomb_chambers);

static int __test_royal_tomb_part_stage(int bid, int index) {
    auto* p = test_royal_tomb_part(bid, index);
    return p ? p->stage() : -1;
}
ANK_FUNCTION_2(__test_royal_tomb_part_stage);

static int __test_royal_tomb_part_can_take(int bid, int index) {
    auto* p = test_royal_tomb_part(bid, index);
    return p ? p->runtime_data().can_take_workers : -1;
}
ANK_FUNCTION_2(__test_royal_tomb_part_can_take);

// Work left in the part's current stage.
static int __test_royal_tomb_part_work(int bid, int index) {
    auto* p = test_royal_tomb_part(bid, index);
    if (!p) {
        return -1;
    }
    const int s = p->stage();
    return (s >= 1 && s <= 3) ? p->runtime_data().remaining_work[s - 1] : 0;
}
ANK_FUNCTION_2(__test_royal_tomb_part_work);

static int __test_royal_tomb_part_worker(int bid, int index) {
    auto* p = test_royal_tomb_part(bid, index);
    return p ? p->runtime_data().worker_figure_id : -1;
}
ANK_FUNCTION_2(__test_royal_tomb_part_worker);

static int __test_royal_tomb_part_tile_x(int bid, int index) {
    auto* p = test_royal_tomb_part(bid, index);
    return p ? p->tile().x() : -1;
}
ANK_FUNCTION_2(__test_royal_tomb_part_tile_x);

static int __test_royal_tomb_part_tile_y(int bid, int index) {
    auto* p = test_royal_tomb_part(bid, index);
    return p ? p->tile().y() : -1;
}
ANK_FUNCTION_2(__test_royal_tomb_part_tile_y);

static int __test_royal_tomb_progress(int bid) {
    auto* tomb = test_royal_tomb_main(bid);
    return tomb ? tomb->progress_percent() : -1;
}
ANK_FUNCTION_1(__test_royal_tomb_progress);

static int __test_royal_tomb_wants_lamps(int bid) {
    auto* tomb = test_royal_tomb_main(bid);
    return tomb && tomb->wants_lamps() ? 1 : 0;
}
ANK_FUNCTION_1(__test_royal_tomb_wants_lamps);

static int __test_royal_tomb_sealed(int bid) {
    auto* tomb = test_royal_tomb_main(bid);
    return tomb && tomb->is_sealed() ? 1 : 0;
}
ANK_FUNCTION_1(__test_royal_tomb_sealed);

static int __test_royal_tomb_idle(int bid) {
    auto* tomb = test_royal_tomb_main(bid);
    return tomb && tomb->is_idle() ? 1 : 0;
}
ANK_FUNCTION_1(__test_royal_tomb_idle);

static int __test_royal_tomb_part_image(int bid, int index) {
    auto* p = test_royal_tomb_part(bid, index);
    return p ? p->building_image_get() : -1;
}
ANK_FUNCTION_2(__test_royal_tomb_part_image);

// The part a guild worker of this type would be sent to (probe, nothing assigned), -1 if none.
static int __test_royal_tomb_find_work(int figure_type, int only_stage) {
    auto* p = (figure_type == FIGURE_TOMB_ARTISAN && only_stage >= 0)
                ? building_royal_tomb::find_artisan_work(only_stage)
                : building_royal_tomb::find_work((e_figure_type)figure_type, 0, false);
    return p ? p->part_index() : -1;
}
ANK_FUNCTION_2(__test_royal_tomb_find_work);

// Dispatch a guild worker the way the guild does (it costs the tomb 100 lamps) and put it straight
// into its work action at the tomb entrance. Returns the figure id, 0 if no part took it.
static int __test_royal_tomb_attach_worker(int bid, int figure_type) {
    auto* tomb = test_royal_tomb_main(bid);
    if (!tomb || figure_type <= 0) {
        return 0;
    }
    const tile2i at = tomb->access_point();
    figure* f = figure_create((e_figure_type)figure_type, at, DIR_0_TOP_RIGHT);
    if (!f || !f->id || !f->is_alive()) {
        return 0;
    }
    f->set_destination(&tomb->base);
    tomb->add_workers(f->id);
    building* part = building_get(f->destination_building_id);
    auto* pt = part ? part->dcast_royal_tomb() : nullptr;
    if (!pt || pt->runtime_data().worker_figure_id != f->id) {
        f->poof();
        return 0;
    }
    if (figure_type == FIGURE_STONEMASON) {
        f->action_state = ACTION_9_MASON_WORK_OBELISK;
        if (auto* mason = smart_cast<figure_stonemason>(f)) {
            mason->runtime_data().destination_bid = part->id;
        }
    } else if (figure_type == FIGURE_TOMB_ARTISAN) {
        f->action_state = ACTION_14_TOMB_ARTISAN_WORK;
        if (auto* impl = smart_cast<figure_tomb_artisan>(f)) {
            impl->runtime_data().destination_bid = part->id;
        }
    }
    f->destination_tile = at;
    return f->id;
}
ANK_FUNCTION_2(__test_royal_tomb_attach_worker);

// Run the figure's work ticks at its royal tomb part; returns the tick on which it was done (it is
// then sent home), or -1 when it still works after max_ticks.
static int __test_royal_tomb_work(int fid, int max_ticks) {
    figure* f = figure_get(fid);
    building* part = f ? building_get(f->destination_building_id) : nullptr;
    auto* tomb = part ? part->dcast_royal_tomb() : nullptr;
    if (!tomb) {
        return -2;
    }
    for (int i = 1; i <= max_ticks; ++i) {
        if (tomb->work_tick(*f)) {
            tomb->remove_worker(fid);
            f->action_state
              = (f->type == FIGURE_STONEMASON) ? ACTION_6_MASON_RETURN_HOME : ACTION_16_TOMB_ARTISAN_RETURN_HOME;
            return i;
        }
    }
    return -1;
}
ANK_FUNCTION_2(__test_royal_tomb_work);

// Minimum map_monuments progress across the monument chain (all parts).
static int __test_monument_min_progress(int bid) {
    building* b = building_get(bid);
    building* head = b ? b->main() : nullptr;
    if (!head || !head->dcast_monument()) {
        return -1;
    }
    // map_grid_get_tiles(head) already walks the whole part chain — do not
    // nest another per-part walk (that re-counts the same tiles).
    grid_tiles tiles = map_grid_get_tiles(head, 0);
    if (tiles.empty()) {
        return -1;
    }
    int min_p = 200;
    for (auto& t : tiles) {
        min_p = std::min(min_p, (int)map_monuments_get_progress(t));
    }
    return min_p;
}
ANK_FUNCTION_1(__test_monument_min_progress);

// Override tile progress after set_phase (which fills 200). Mid-progress keeps
// update_day from advancing the phase across save/load day ticks.
static void __test_monument_set_all_progress(int bid, int progress) {
    building* b = building_get(bid);
    building* head = b ? b->main() : nullptr;
    if (!head || !head->dcast_monument()) {
        return;
    }
    const uint32_t v = (uint32_t)std::clamp(progress, 0, 200);
    grid_tiles tiles = map_grid_get_tiles(head, 0);
    for (auto& t : tiles) {
        map_monuments_set_progress(t, v);
    }
}
ANK_FUNCTION_2(__test_monument_set_all_progress);

static void __test_burial_provisions_clear() {
    for (int r = 0; r < RESOURCES_MAX; r++) {
        g_scenario.monuments.burial_provisions[r].required = 0;
        g_scenario.monuments.burial_provisions[r].dispatched = 0;
    }
    buildings_valid_do([](building& b) {
        auto* m = b.dcast_monument();
        if (!m || !b.is_main()) {
            return;
        }
        auto& d = m->runtime_data();
        memset(d.burial_stock, 0, sizeof(d.burial_stock));
    });
}
ANK_FUNCTION(__test_burial_provisions_clear);

static bool __test_burial_provisions_set(int resource, int required) {
    if (resource <= RESOURCE_NONE || resource >= RESOURCES_MAX || required < 0) {
        return false;
    }
    g_scenario.monuments.burial_provisions[resource].required = required;
    g_scenario.monuments.burial_provisions[resource].dispatched = 0;
    return true;
}
ANK_FUNCTION_2(__test_burial_provisions_set);

static int __test_monument_burial_stock(int bid, int resource) {
    building* b = building_get(bid);
    building* head = b ? b->main() : nullptr;
    auto* m = head ? head->dcast_monument() : nullptr;
    if (!m || resource <= RESOURCE_NONE || resource >= RESOURCES_MAX) {
        return -1;
    }
    return m->burial_stock((e_resource)resource);
}
ANK_FUNCTION_2(__test_monument_burial_stock);

static int __test_monument_add_burial_stock(int bid, int resource, int amount) {
    building* b = building_get(bid);
    building* head = b ? b->main() : nullptr;
    auto* m = head ? head->dcast_monument() : nullptr;
    if (!m || resource <= RESOURCE_NONE || resource >= RESOURCES_MAX || amount <= 0) {
        return 0;
    }
    const int added = m->add_burial_stock((e_resource)resource, amount);
    g_scenario.monuments.burial_provisions[resource].dispatched += added;
    return added;
}
ANK_FUNCTION_3(__test_monument_add_burial_stock);

static building_sphinx *test_sphinx(int bid) {
    building *b = building_get(bid);
    auto *s = b ? b->dcast_sphinx() : nullptr;
    return s ? s->main_sphinx() : nullptr;
}

static int __test_sphinx_stage(int bid) {
    auto *s = test_sphinx(bid);
    return s ? s->stage() : -1;
}
ANK_FUNCTION_1(__test_sphinx_stage);

static void __test_sphinx_set_stage(int bid, int stage) {
    if (auto *s = test_sphinx(bid)) {
        s->set_stage(stage);
    }
}
ANK_FUNCTION_2(__test_sphinx_set_stage);

static int __test_sphinx_spot_work(int bid, int spot) {
    auto *s = test_sphinx(bid);
    return s ? s->spot_work_left(spot) : -1;
}
ANK_FUNCTION_2(__test_sphinx_spot_work);

static int __test_sphinx_has_spot(int bid, int figure_type) {
    auto *s = test_sphinx(bid);
    return (s && s->has_free_spot((e_figure_type)figure_type)) ? 1 : 0;
}
ANK_FUNCTION_2(__test_sphinx_has_spot);

// One OG work tick by figure fid; returns 1 when the figure would leave the site.
static int __test_sphinx_work(int bid, int fid) {
    auto *s = test_sphinx(bid);
    figure *f = fid > 0 ? figure_get(fid) : nullptr;
    if (!s || !f) {
        return -1;
    }
    return s->work_tick(*f) ? 1 : 0;
}
ANK_FUNCTION_2(__test_sphinx_work);

static building_caesareum *test_caesareum(int bid) {
    building *b = building_get(bid);
    auto *c = b ? b->dcast_caesareum() : nullptr;
    return c ? c->main_caesareum() : nullptr;
}

static int __test_caesareum_stage(int bid) {
    auto *c = test_caesareum(bid);
    return c ? c->stage() : -1;
}
ANK_FUNCTION_1(__test_caesareum_stage);

static void __test_caesareum_set_stage(int bid, int stage) {
    if (auto *c = test_caesareum(bid)) {
        c->set_stage(stage);
    }
}
ANK_FUNCTION_2(__test_caesareum_set_stage);

static int __test_caesareum_spot_work(int bid, int spot) {
    auto *c = test_caesareum(bid);
    return c ? c->spot_work_left(spot) : -1;
}
ANK_FUNCTION_2(__test_caesareum_spot_work);

static int __test_caesareum_has_spot(int bid, int figure_type) {
    auto *c = test_caesareum(bid);
    return (c && c->has_free_spot((e_figure_type)figure_type)) ? 1 : 0;
}
ANK_FUNCTION_2(__test_caesareum_has_spot);

// One OG work tick by figure fid; returns 1 when the figure would leave the site.
static int __test_caesareum_work(int bid, int fid) {
    auto *c = test_caesareum(bid);
    figure *f = fid > 0 ? figure_get(fid) : nullptr;
    if (!c || !f) {
        return -1;
    }
    return c->work_tick(*f) ? 1 : 0;
}
ANK_FUNCTION_2(__test_caesareum_work);

static int __test_caesareum_progress(int bid) {
    auto *c = test_caesareum(bid);
    return c ? c->get_progress(nullptr) : -1;
}
ANK_FUNCTION_1(__test_caesareum_progress);

static int __test_caesareum_material(int bid) {
    auto *c = test_caesareum(bid);
    if (!c) {
        return -1;
    }
    caesareum_progress p;
    c->get_progress(&p);
    return p.material;
}
ANK_FUNCTION_1(__test_caesareum_material);

static int __test_caesareum_block_resource(int bid) {
    auto *c = test_caesareum(bid);
    return c ? (int)c->block_resource() : -1;
}
ANK_FUNCTION_1(__test_caesareum_block_resource);

static int __test_caesareum_sled_arrived(int bid) {
    auto *c = test_caesareum(bid);
    return (c && c->sled_arrived()) ? 1 : 0;
}
ANK_FUNCTION_1(__test_caesareum_sled_arrived);

static int __test_caesareum_claim(int bid, int fid) {
    auto *c = test_caesareum(bid);
    figure *f = fid > 0 ? figure_get(fid) : nullptr;
    return (c && f && c->claim_worker(*f)) ? 1 : 0;
}
ANK_FUNCTION_2(__test_caesareum_claim);

static int __test_caesareum_worker(int bid) {
    auto *c = test_caesareum(bid);
    return c ? (int)c->worker_figure_id() : -1;
}
ANK_FUNCTION_1(__test_caesareum_worker);

static int __test_caesareum_access(int bid) {
    auto *c = test_caesareum(bid);
    return c ? c->access_point().grid_offset() : -1;
}
ANK_FUNCTION_1(__test_caesareum_access);

static building_abu_simbel* test_abu_simbel(int bid) {
    building* b = building_get(bid);
    auto* a = b ? b->dcast_abu_simbel() : nullptr;
    return a ? a->main_abu_simbel() : nullptr;
}

static int __test_abu_simbel_stage(int bid) {
    auto* a = test_abu_simbel(bid);
    return a ? a->stage() : -1;
}
ANK_FUNCTION_1(__test_abu_simbel_stage);

static void __test_abu_simbel_set_stage(int bid, int stage) {
    if (auto* a = test_abu_simbel(bid)) {
        a->set_stage(stage);
    }
}
ANK_FUNCTION_2(__test_abu_simbel_set_stage);

static int __test_abu_simbel_scaffolds_raised(int bid) {
    auto* a = test_abu_simbel(bid);
    return a ? a->scaffolds_raised() : -1;
}
ANK_FUNCTION_1(__test_abu_simbel_scaffolds_raised);

static int __test_abu_simbel_scaffold_draws(int bid) {
    auto* a = test_abu_simbel(bid);
    return a ? a->scaffold_draw_count() : -1;
}
ANK_FUNCTION_1(__test_abu_simbel_scaffold_draws);

static int __test_abu_simbel_spot_work(int bid) {
    auto* a = test_abu_simbel(bid);
    return a ? a->spot_work_left() : -1;
}
ANK_FUNCTION_1(__test_abu_simbel_spot_work);

static int __test_abu_simbel_has_spot(int bid, int figure_type) {
    auto* a = test_abu_simbel(bid);
    return (a && a->has_free_spot((e_figure_type)figure_type)) ? 1 : 0;
}
ANK_FUNCTION_2(__test_abu_simbel_has_spot);

static int __test_abu_simbel_needs(int bid, int figure_type) {
    auto* a = test_abu_simbel(bid);
    if (!a) {
        return -1;
    }
    return (figure_type == FIGURE_STONEMASON ? a->need_stonemason() : a->need_carpenter()) ? 1 : 0;
}
ANK_FUNCTION_2(__test_abu_simbel_needs);

static int __test_abu_simbel_progress(int bid) {
    auto* a = test_abu_simbel(bid);
    return a ? a->progress_percent() : -1;
}
ANK_FUNCTION_1(__test_abu_simbel_progress);

static int __test_abu_simbel_site_fits(int x, int y) {
    return building_abu_simbel::site_fits(tile2i(x, y)) ? 1 : 0;
}
ANK_FUNCTION_2(__test_abu_simbel_site_fits);

// One OG work tick by figure fid; returns 1 when the figure would leave the site.
static int __test_abu_simbel_work(int bid, int fid) {
    auto* a = test_abu_simbel(bid);
    figure* f = fid > 0 ? figure_get(fid) : nullptr;
    if (!a || !f) {
        return -1;
    }
    return a->work_tick(*f) ? 1 : 0;
}
ANK_FUNCTION_2(__test_abu_simbel_work);

static int __test_abu_simbel_access_x(int bid) {
    auto* a = test_abu_simbel(bid);
    return a ? a->access_point().x() : -1;
}
ANK_FUNCTION_1(__test_abu_simbel_access_x);

static int __test_abu_simbel_access_y(int bid) {
    auto* a = test_abu_simbel(bid);
    return a ? a->access_point().y() : -1;
}
ANK_FUNCTION_1(__test_abu_simbel_access_y);

static building_pharos_lighthouse* test_lighthouse(int bid) {
    building* b = building_get(bid);
    auto* l = b ? b->dcast_pharos_lighthouse() : nullptr;
    return l ? l->main_lighthouse() : nullptr;
}

static int __test_lighthouse_stage(int bid) {
    auto* l = test_lighthouse(bid);
    return l ? l->stage() : -1;
}
ANK_FUNCTION_1(__test_lighthouse_stage);

static void __test_lighthouse_set_stage(int bid, int stage) {
    if (auto* l = test_lighthouse(bid)) {
        l->set_stage(stage);
    }
}
ANK_FUNCTION_2(__test_lighthouse_set_stage);

static int __test_lighthouse_spot_work(int bid, int figure_type) {
    auto* l = test_lighthouse(bid);
    return l ? l->spot_work_left((e_figure_type)figure_type) : -1;
}
ANK_FUNCTION_2(__test_lighthouse_spot_work);

static int __test_lighthouse_worker(int bid) {
    auto* l = test_lighthouse(bid);
    return (l && l->part_has_active_worker()) ? l->worker_figure_id() : 0;
}
ANK_FUNCTION_1(__test_lighthouse_worker);

static int __test_lighthouse_percent(int bid) {
    auto* l = test_lighthouse(bid);
    return l ? l->get_progress(nullptr) : -1;
}
ANK_FUNCTION_1(__test_lighthouse_percent);

static int __test_lighthouse_site_fits(int x, int y) {
    return building_pharos_lighthouse::site_fits(tile2i(x, y)) ? 1 : 0;
}
ANK_FUNCTION_2(__test_lighthouse_site_fits);

static int __test_lighthouse_assign(int bid, int fid) {
    auto* l = test_lighthouse(bid);
    if (!l) {
        return 0;
    }
    l->add_workers(fid);
    return l->worker_figure_id() == fid ? 1 : 0;
}
ANK_FUNCTION_2(__test_lighthouse_assign);

static int __test_lighthouse_mason_waiting(int bid) {
    auto* l = test_lighthouse(bid);
    return l ? l->mason_waiting_for_block() : 0;
}
ANK_FUNCTION_1(__test_lighthouse_mason_waiting);

static int __test_lighthouse_sled(int bid, int mason_fid) {
    auto* l = test_lighthouse(bid);
    figure* f = mason_fid > 0 ? figure_get(mason_fid) : nullptr;
    return (l && f && l->sled_arrived(*f)) ? 1 : 0;
}
ANK_FUNCTION_2(__test_lighthouse_sled);

static int __test_lighthouse_work(int bid, int fid) {
    auto* l = test_lighthouse(bid);
    figure* f = fid > 0 ? figure_get(fid) : nullptr;
    if (!l || !f) {
        return -1;
    }
    return l->work_tick(*f) ? 1 : 0;
}
ANK_FUNCTION_2(__test_lighthouse_work);

static pcstr __test_lighthouse_spots(int bid) {
    static bstring1024 out;
    out.clear();
    if (!test_lighthouse(bid)) {
        return out.c_str();
    }
    for (const auto& s : building_pharos_lighthouse::lighthouse_params().stages) {
        out.append_fmt("%s%d:%d:%d", out.empty() ? "" : ";", s.stage, (int)FIGURE_STONEMASON, s.stonemason);
        if (s.carpenter > 0) {
            out.append_fmt(";%d:%d:%d", s.stage, (int)FIGURE_CARPENTER, s.carpenter);
        }
    }
    return out.c_str();
}
ANK_FUNCTION_1(__test_lighthouse_spots);

static int __test_lighthouse_stage_text(int bid) {
    auto* l = test_lighthouse(bid);
    if (!l) {
        return -1;
    }
    const auto& stages = building_pharos_lighthouse::lighthouse_params().stages;
    const int s = l->stage();
    return s < (int)stages.size() ? stages[s].text : -1;
}
ANK_FUNCTION_1(__test_lighthouse_stage_text);

static building_sun_temple *test_sun_temple(int bid) {
    building *b = building_get(bid);
    auto *s = b ? b->dcast_sun_temple() : nullptr;
    return s ? s->main_sun_temple() : nullptr;
}

static int __test_sun_temple_part_count(int bid) {
    auto *s = test_sun_temple(bid);
    if (!s) {
        return -1;
    }
    int n = 0;
    for (building *p = &s->base; p; p = p->has_next() ? p->next() : nullptr) {
        n++;
    }
    return n;
}
ANK_FUNCTION_1(__test_sun_temple_part_count);

static int __test_sun_temple_stage(int bid) {
    auto *s = test_sun_temple(bid);
    return s ? s->part_stage() : -1;
}
ANK_FUNCTION_1(__test_sun_temple_stage);

static int __test_sun_temple_progress(int bid) {
    auto *s = test_sun_temple(bid);
    return s ? s->get_progress(nullptr) : -1;
}
ANK_FUNCTION_1(__test_sun_temple_progress);

static int __test_sun_temple_has_spot(int bid, int figure_type) {
    auto *s = test_sun_temple(bid);
    return (s && s->has_free_spot((e_figure_type)figure_type)) ? 1 : 0;
}
ANK_FUNCTION_2(__test_sun_temple_has_spot);

static int __test_sun_temple_spot_work(int bid, int spot) {
    auto *s = test_sun_temple(bid);
    return s ? s->spot_work_left(spot) : -1;
}
ANK_FUNCTION_2(__test_sun_temple_spot_work);

static int __test_sun_temple_spot_figure(int bid, int spot) {
    auto *s = test_sun_temple(bid);
    return s ? s->spot_attached(spot) : -1;
}
ANK_FUNCTION_2(__test_sun_temple_spot_figure);

static int __test_sun_temple_work(int bid, int fid) {
    auto *s = test_sun_temple(bid);
    figure *f = fid > 0 ? figure_get(fid) : nullptr;
    if (!s || !f) {
        return -1;
    }
    return s->work_tick(*f) ? 1 : 0;
}
ANK_FUNCTION_2(__test_sun_temple_work);

static building_mausoleum *test_mausoleum(int bid) {
    building *b = building_get(bid);
    auto *m = b ? b->dcast_mausoleum() : nullptr;
    return m ? m->main_mausoleum() : nullptr;
}

static int __test_mausoleum_part_count(int bid) {
    auto *m = test_mausoleum(bid);
    if (!m) {
        return -1;
    }
    int n = 0;
    for (building *p = &m->base; p; p = p->has_next() ? p->next() : nullptr) {
        n++;
    }
    return n;
}
ANK_FUNCTION_1(__test_mausoleum_part_count);

static int __test_mausoleum_part_id(int bid, int index) {
    auto *m = test_mausoleum(bid);
    auto *p = m ? m->part(index) : nullptr;
    return p ? p->id() : 0;
}
ANK_FUNCTION_2(__test_mausoleum_part_id);

static int __test_mausoleum_part_kind(int part_bid) {
    building *b = building_get(part_bid);
    auto *p = b ? b->dcast_mausoleum() : nullptr;
    return p ? (int)p->part_kind_word() : -1;
}
ANK_FUNCTION_1(__test_mausoleum_part_kind);

static int __test_mausoleum_part_stage(int part_bid) {
    building *b = building_get(part_bid);
    auto *p = b ? b->dcast_mausoleum() : nullptr;
    return p ? (int)p->part_stage() : -1;
}
ANK_FUNCTION_1(__test_mausoleum_part_stage);

static int __test_mausoleum_part_worker(int part_bid) {
    building *b = building_get(part_bid);
    auto *p = b ? b->dcast_mausoleum() : nullptr;
    return p ? (int)p->runtime_data().og_part.worker_figure_id : -1;
}
ANK_FUNCTION_1(__test_mausoleum_part_worker);

static int __test_mausoleum_work_flags(int bid) {
    auto *m = test_mausoleum(bid);
    return m ? (int)m->work_flags() : -1;
}
ANK_FUNCTION_1(__test_mausoleum_work_flags);

static int __test_mausoleum_progress(int bid) {
    auto *m = test_mausoleum(bid);
    return m ? m->get_progress(nullptr) : -1;
}
ANK_FUNCTION_1(__test_mausoleum_progress);

static int __test_mausoleum_access_x(int bid) {
    auto *m = test_mausoleum(bid);
    return m ? m->access_point().x() : -1;
}
ANK_FUNCTION_1(__test_mausoleum_access_x);

static int __test_mausoleum_access_y(int bid) {
    auto *m = test_mausoleum(bid);
    return m ? m->access_point().y() : -1;
}
ANK_FUNCTION_1(__test_mausoleum_access_y);

static int __test_mausoleum_has_work(int bid, int figure_type) {
    auto *m = test_mausoleum(bid);
    return (m && m->has_work_for((e_figure_type)figure_type)) ? 1 : 0;
}
ANK_FUNCTION_2(__test_mausoleum_has_work);

static int __test_mausoleum_find_work(int fid) {
    return building_mausoleum::find_work_for_figure(fid);
}
ANK_FUNCTION_1(__test_mausoleum_find_work);

static int __test_mausoleum_work(int part_bid, int fid) {
    building *b = building_get(part_bid);
    auto *p = b ? b->dcast_mausoleum() : nullptr;
    figure *f = fid > 0 ? figure_get(fid) : nullptr;
    if (!p || !f) {
        return -1;
    }
    return p->work_tick(*f) ? 1 : 0;
}
ANK_FUNCTION_2(__test_mausoleum_work);

static building_alexandria_library *test_alexandria_library(int bid) {
    building *b = building_get(bid);
    auto *s = b ? b->dcast_alexandria_library() : nullptr;
    return s ? s->main_library() : nullptr;
}

static int __test_alexandria_library_part_count(int bid) {
    auto *s = test_alexandria_library(bid);
    if (!s) {
        return -1;
    }
    int n = 0;
    for (building *p = &s->base; p; p = p->has_next() ? p->next() : nullptr) {
        n++;
    }
    return n;
}
ANK_FUNCTION_1(__test_alexandria_library_part_count);

static int __test_alexandria_library_stage(int bid) {
    auto *s = test_alexandria_library(bid);
    return s ? s->part_stage() : -1;
}
ANK_FUNCTION_1(__test_alexandria_library_stage);

static int __test_alexandria_library_progress(int bid) {
    auto *s = test_alexandria_library(bid);
    return s ? s->get_progress(nullptr) : -1;
}
ANK_FUNCTION_1(__test_alexandria_library_progress);

static int __test_alexandria_library_work(int bid, int fid) {
    building *b = building_get(bid);
    auto *part = b ? b->dcast_alexandria_library() : nullptr;
    figure *f = fid > 0 ? figure_get(fid) : nullptr;
    if (!part || !f) {
        return -1;
    }
    f->destination_building_id = bid;
    return part->work_tick(*f) ? 1 : 0;
}
ANK_FUNCTION_2(__test_alexandria_library_work);

static void __test_alexandria_library_finish(int bid) {
    auto *s = test_alexandria_library(bid);
    if (!s) {
        return;
    }
    for (int i = 0; i < building_alexandria_library::parts_count(); ++i) {
        if (auto *p = s->part(i)) {
            p->set_phase(MONUMENT_FINISHED);
        }
    }
    s->refresh_part_images();
}
ANK_FUNCTION_1(__test_alexandria_library_finish);

static int __test_alexandria_library_part_stage(int bid, int part_index) {
    auto *s = test_alexandria_library(bid);
    if (!s) {
        return -1;
    }
    auto *p = s->part(part_index);
    return p ? p->part_stage() : -1;
}
ANK_FUNCTION_2(__test_alexandria_library_part_stage);

static int __test_alexandria_library_part_id(int bid, int part_index) {
    auto *s = test_alexandria_library(bid);
    if (!s) {
        return 0;
    }
    auto *p = s->part(part_index);
    return p ? p->id() : 0;
}
ANK_FUNCTION_2(__test_alexandria_library_part_id);

static void __test_alexandria_library_set_part_stage(int bid, int part_index, int stage) {
    auto *s = test_alexandria_library(bid);
    if (!s) {
        return;
    }
    if (auto *p = s->part(part_index)) {
        p->set_phase(stage);
        s->refresh_part_images();
    }
}
ANK_FUNCTION_3(__test_alexandria_library_set_part_stage);

static int __test_alexandria_library_check_work(int bid, int fid, int assign) {
    auto *s = test_alexandria_library(bid);
    figure *f = fid > 0 ? figure_get(fid) : nullptr;
    if (!s || !f) {
        return 0;
    }
    return s->main_library()->check_work_for_figure(fid, assign != 0) ? 1 : 0;
}
ANK_FUNCTION_3(__test_alexandria_library_check_work);

static void __test_alexandria_library_deliver_material(int bid) {
    auto *s = test_alexandria_library(bid);
    if (!s) {
        return;
    }
    s->main_library()->on_material_delivered();
}
ANK_FUNCTION_1(__test_alexandria_library_deliver_material);

static tile2i __test_building_access_tile(int bid) {
    building* b = building_get(bid);
    return b ? b->access_tile() : tile2i::invalid;
}
ANK_FUNCTION_1(__test_building_access_tile);

static tile2i __test_building_road_access(int bid) {
    building* b = building_get(bid);
    return b ? b->road_access : tile2i::invalid;
}
ANK_FUNCTION_1(__test_building_road_access);

static tile2i __test_building_main_tile(int bid) {
    building* b = building_get(bid);
    return b ? b->main()->tile : tile2i::invalid;
}
ANK_FUNCTION_1(__test_building_main_tile);

static tile2i __test_monument_access_point(int bid) {
    building* b = building_get(bid);
    auto* mm = b ? b->dcast_monument() : nullptr;
    return mm ? mm->access_point() : tile2i::invalid;
}
ANK_FUNCTION_1(__test_monument_access_point);

#include "monuments.h"

#include "building/building.h"
#include "building/monument_pyramid.h"
#include "building/monument_abu_simbel.h"
#include "building/monument_caesareum.h"
#include "building/monument_mausoleum.h"
#include "building/monument_royal_tomb.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/view/view.h"
#include "empire/empire.h"
#include "figure/figure.h"
#include "core/svector.h"
#include "city/city_resource.h"
#include "city/city_message.h"
#include "game/resource.h"
#include "grid/grid.h"
#include "grid/figure.h"
#include "grid/building_tiles.h"
#include "grid/terrain.h"
#include "core/calc.h"
#include "core/log.h"

#include <algorithm>
#include "city/city.h"
#include "city/city_buildings.h"
#include "io/io_buffer.h"
#include "scenario/scenario.h"

#include "js/js_game.h"

#include <algorithm>

using e_pyramid_style_tokens_t = token_holder<e_pyramid_style, PYRAMID_STYLE_NONE, PYRAMID_STYLE_COUNT>;
const e_pyramid_style_tokens_t ANK_CONFIG_ENUM(e_pyramid_style_tokens);

#define DELIVERY_ARRAY_SIZE_STEP 200
#define ORIGINAL_DELIVERY_BUFFER_SIZE 16
#define MODULES_PER_TEMPLE 2

#define BUILDING_MONUMENT_FIRST_ID BUILDING_SMALL_MASTABA

#define NOTHING 0
#define INFINITE 10000

grid_xx g_monuments_progress_grid(FS_UINT32);
BUILDING_RUNTIME_DATA_IMPL(building_monument)

io_buffer* iob_monuments_progress_grid = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_monuments_progress_grid);
});

bool building_monument::deliver_resource(e_resource resource, int amount) {
    // Always credit the chain head — yard/sled destination may be a corner/wall
    // part, while update_day / info UI read resources_pct only from main().
    auto bmain = main()->dcast_monument();
    verify_no_crash(bmain);
    auto &d = bmain->runtime_data();
    if (d.resources_pct[resource] >= 100) {
        return false;
    }

    int full_resources = bmain->needs_resource(resource);
    int amount_pct = calc_percentage(amount, full_resources);
    // Clamp to 100 — update_day does tiles.resize(n * pct / 100); pct>100
    // grew the vector with bogus tiles and wrote monument progress off-footprint.
    int sum = (int)d.resources_pct[resource] + amount_pct;
    d.resources_pct[resource] = (uint8_t)std::min(sum, 100);

    return true;
}

uint32_t map_monuments_get_progress(tile2i tile) {
    return map_grid_get(g_monuments_progress_grid, tile.grid_offset());
}

void map_monuments_set_progress(tile2i tile, uint32_t progress) {
    map_grid_set(g_monuments_progress_grid, tile.grid_offset(), progress);
}

void map_monuments_clear() {
    map_grid_fill(g_monuments_progress_grid, 0);
}

tile2i building_monument_mason_waiting_tile(building *b) {
    if (!b || !b->is_monument()) {
        return tile2i{ -1, -1 };
    }

    building *main = b->main();
    if (!main) {
        return tile2i{ -1, -1 };
    }

    // Work-site offsets are relative to footprint NW. For pyramids that is not
    // always main()->tile() (orientation can put a corner/wall first in the chain).
    tile2i origin = main->tile;
    if (auto *pyr = main->dcast_pyramid()) {
        origin = pyr->footprint_nw();
    }

    // Same 2×2 work-site pattern as mastaba bricklayers. Prefer idle sites so
    // multiple masons spread out; fall back to mid-progress for resume-after-poof.
    grid_tiles tiles = map_grid_get_tiles(main, 0);
    auto find_in_range = [&] (int lo, int hi) {
        return map_grid_area_first(tiles, [origin, lo, hi] (tile2i tile) {
            int progress = map_monuments_get_progress(tile);
            tile2i offset = tile.dist2i(origin).mod(4, 4);
            return progress >= lo && progress < hi
                && (offset.x() == 1 || offset.x() == 3)
                && (offset.y() == 1 || offset.y() == 3);
        });
    };

    tile2i idle = find_in_range(0, 1);
    if (idle.valid()) {
        return idle;
    }
    tile2i claimed = find_in_range(1, 3);
    if (claimed.valid()) {
        return claimed;
    }
    return find_in_range(3, 200);
}

grid_area building_monument::get_area() const {
    tile2i main = tile();
    verify_no_crash(false);
    return {main, main};
}

int building_monument_workers_onsite(building *b, e_figure_type figure_type) {
    auto tiles = map_grid_get_tiles(b, 0);

    int num_workers = 0;
    for (auto &tile : tiles) {
        figure *f = map_figure_get(tile);
        num_workers += (f->destination() == b) ? 1 : 0;
    }

    return num_workers;
}

int building_monument_get_monument(tile2i tile, e_resource resource, int road_network_id, tile2i &dst) {
    if (g_city.resource.is_stockpiled(resource)) {
        return 0;
    }

    //int min_dist = INFINITE;
    //building *min_building = 0;
    //for (e_building_type type = BUILDING_MONUMENT_FIRST_ID; type < BUILDING_TYPE_MAX; type++) {
    //    if (!g_monument_types[type]) {
    //        continue;
    //    }
    //
    //    for (building *b = building_first_of_type(type); b; b = b->next_of_type) {
    //        if (b->data.monuments.phase == MONUMENT_FINISHED ||
    //            b->data.monuments.phase < MONUMENT_START ||
    //            building_monument_is_construction_halted(b) ||
    //            (!resource && building_monument_needs_resources(b))) {
    //            continue;
    //        }
    //        short needed = b->resources[resource];
    //        if ((needed - building_monument_resource_in_delivery(b, resource)) <= 0) {
    //            continue;
    //        }
    //        if (!map_has_road_access(b->tile, b->size) ||
    //            b->distance_from_entry <= 0 || b->road_network_id != road_network_id) {
    //            continue;
    //        }
    //        int dist = calc_maximum_distance(b->tile, tile);
    //        if (dist < min_dist) {
    //            min_dist = dist;
    //            min_building = b;
    //        }
    //    }
    //}
    //
    //if (min_building && min_dist < INFINITE) {
    //    map_point_store_result(min_building->road_access, dst);
    //    return min_building->id;
    //}
    return 0;
}

bool building_monument_has_unfinished(std::initializer_list<e_building_type> types,
  bool main_parts_only, bool include_just_placed) {
    for (building *b = building_begin(); b != building_end(); ++b) {
        if (!b || !building_type_any_of(b->type, types)) {
            continue;
        }

        const bool live = b->is_valid()
          || (include_just_placed
            && (b->state == BUILDING_STATE_CREATED || b->state == BUILDING_STATE_MOTHBALLED));
        if (!live) {
            continue;
        }

        if (main_parts_only && !b->is_main()) {
            continue;
        }

        auto *m = b->dcast_monument();
        if (m && m->is_unfinished()) {
            return true;
        }
    }

    return false;
}

int building_monument::phases() const {
    return config().phases.size();
}

int building_monument::phase_blocks(int ph_id) const {
    const monument &cfg = config();
    if (ph_id < 0 || ph_id >= (int)cfg.phases.size()) {
        return 0;
    }
    return cfg.phases[ph_id].blocks;
}

int building_monument::brick_blocks_total() const {
    int sum = 0;
    for (const auto &ph : config().phases) {
        sum += ph.blocks;
    }
    return sum;
}

int building_monument::phase_worker_count(int ph_id, e_figure_type type) const {
    const monument &cfg = config();
    if (ph_id < 0 || ph_id >= (int)cfg.phases.size()) {
        return 0;
    }
    int total = 0;
    for (const auto &w : cfg.phases[ph_id].workers) {
        if (w.type == type) {
            total += w.count;
        }
    }
    return total;
}

int building_monument::phase_bricks_per_block(int ph_id) const {
    int blocks = phase_blocks(ph_id);
    int bricks = needs_resource(RESOURCE_BRICKS, ph_id);
    if (blocks > 0 && bricks > 0) {
        return std::max(1, bricks / blocks);
    }
    return bricks > 0 ? bricks : 100;
}

int building_monument::phase_for_blocks_done(int blocks_done) const {
    const monument &cfg = config();
    int cum = 0;
    int last_brick_phase = -1;
    for (int i = 0; i < (int)cfg.phases.size(); i++) {
        const int n = cfg.phases[i].blocks;
        if (n <= 0) {
            continue;
        }
        last_brick_phase = cfg.phases[i].id;
        cum += n;
        if (blocks_done < cum) {
            return cfg.phases[i].id;
        }
    }
    if (last_brick_phase >= 0) {
        const int next = last_brick_phase + 1;
        if (next < (int)cfg.phases.size()) {
            return cfg.phases[next].id;
        }
        return last_brick_phase;
    }
    return phase();
}

int building_monument::needs_bricklayers(int ph_id) const {
    const int from_workers = phase_worker_count(ph_id, FIGURE_BRICKLAYER);
    if (from_workers > 0) {
        return from_workers;
    }

    const monument &cfg = config();
    if (ph_id < 0 || ph_id >= (int)cfg.phases.size()) {
        return 0;
    }
    const monument_phase &ph = cfg.phases[ph_id];
    return ph.resources.size() > 0 ? ph.resources[0].count : 0;
}

int building_monument::needs_resource(e_resource resource) const {
    auto &d = runtime_data();
    return needs_resource(resource, d.phase);
}

int building_monument::needs_resource(e_resource resource, int phase) const {
    const monument &config = this->config();

    // phase is signed in runtime (FINISHED = -1). Never index phases[] with that.
    if (phase < 0 || phase >= (int)config.phases.size()) {
        return 0;
    }

    const monument_phase &ph = config.phases[phase];
    auto r_it = std::find_if(ph.resources.begin(), ph.resources.end(), [&] (auto &p) { return p.resource == resource; });
    return (r_it != ph.resources.end() ? r_it->count : 0);
}

int building_monument::remaining_resource_need(e_resource resource) const {
    const auto& d = runtime_data();
    if (d.phase < 0) {
        return 0;
    }

    int total = 0;
    for (int ph = d.phase, num = phases(); ph < num; ++ph) {
        int need = needs_resource(resource, ph);
        if (ph == d.phase) {
            need -= need * (int)d.resources_pct[resource] / 100;
        }
        total += need;
    }
    return total;
}

void building_monument::on_phase_changed(int old, int current) {
    if (current >= 2) {
        map_building_tiles_add(id(), tile(), size(), this->building_image_get(), TERRAIN_BUILDING);
    }

    if (current != MONUMENT_FINISHED) {
        auto &d = runtime_data();
        for (e_resource resource = RESOURCE_NONE; resource < RESOURCES_MAX; ++resource) {
            d.resources_pct[resource] = 0;
        }
    }
}

void building_monument::set_phase(int phase) {
    if (phase == phases()) {
        phase = MONUMENT_FINISHED;
    }

    auto &d = runtime_data();
    if (phase == d.phase) {
        return;
    }

    int old_phase = d.phase;
    d.phase = phase;
    on_phase_changed(old_phase, phase);
}

void building_monument_finish_monuments() {
    buildings_valid_do([&] (building &b) {
        auto monument = b.dcast_monument();
        auto &monumentd = monument->runtime_data();
        if (monumentd.phase != MONUMENT_FINISHED) {
            return;
        }

        monument->set_phase(MONUMENT_FINISHED);
        for (auto &r: monumentd.resources_pct) {
            r = 0;
        }
    });
}

bool building_monument::needs_resources() const {   
    auto &d = runtime_data();
    if (d.phase == MONUMENT_FINISHED) {
        return false;
    }

    for (auto &r: d.resources_pct) {
        if (r < 100) {
            return true;
        }
    }
    return false;
}

int building_monument::progress() {
    if (needs_resources()) {
        return 0;
    }

    auto &d = runtime_data();
    if (d.phase == MONUMENT_FINISHED) {
        return 0;
    }

    auto bmain = main()->dcast_monument();

    bmain->set_phase(d.phase + 1);

    // Use has_next() — building_impl::next() returns building_get(0)->dcast() when
    // next_part_building_id is 0 (always non-null), which then fails dcast_monument().
    for (building_impl *part = bmain->has_next() ? bmain->next() : nullptr; part;
         part = part->has_next() ? part->next() : nullptr) {
        auto *nextd = part->dcast_monument();
        if (!nextd) {
            break;
        }
        nextd->set_phase(nextd->phase() + 1);
    }

    if (d.phase == MONUMENT_FINISHED) {
        if (bmain->dcast_temple_complex()) {
            messages::popup("message_monument_complete", 0, bmain->tile().grid_offset());
        } else if (bmain->dcast_mastaba()) {
            messages::popup("message_monument_complete", 0, bmain->tile().grid_offset());
        } else if (bmain->dcast_pyramid()) {
            messages::popup("message_monument_complete", 0, bmain->tile().grid_offset());
        } else if (bmain->dcast_sphinx()) {
            messages::popup("message_monument_complete", 0, bmain->tile().grid_offset());
        } else if (bmain->dcast_obelisk()) {
            messages::popup("message_monument_complete", 0, bmain->tile().grid_offset());
        } else if (bmain->dcast_abu_simbel()) {
            messages::popup("abu_simbel_congratulations", 0, bmain->tile().grid_offset());
        } else if (bmain->dcast_caesareum()) {
            messages::popup("caesareum_congratulations", 0, bmain->tile().grid_offset());
        } else if (bmain->dcast_alexandria_library()) {
            messages::popup("alex_library_congratulations", 0, bmain->tile().grid_offset());
        } else if (bmain->dcast_mausoleum()) {
            messages::popup("mausoleum_congratulations", 0, bmain->tile().grid_offset());
        } else if (bmain->dcast_pharos_lighthouse()) {
            messages::popup("lighthouse_congratulations", 0, bmain->tile().grid_offset());
        } else if (bmain->dcast_royal_tomb()) {
            messages::popup("message_monument_complete", 0, bmain->tile().grid_offset());
        }
    }
    return 1;
}

int building_monument_get_id(e_building_type type) {
    building *b = building_first_of_type(type);
    if (!b->is_monument()) {
        return 0;
    }

    return b->id;
}

int building_monument_count_temple_complex(void) {
    auto temple_complex = {
        BUILDING_TEMPLE_COMPLEX_OSIRIS,
        BUILDING_TEMPLE_COMPLEX_RA,
        BUILDING_TEMPLE_COMPLEX_PTAH,
        BUILDING_TEMPLE_COMPLEX_SETH,
        BUILDING_TEMPLE_COMPLEX_BAST,
    };

    const int count = g_city.buildings.count_active(temple_complex);
    return count;
}

bool building_monument::has_labour_problems() const {
    return (base.num_workers < base.max_workers);
}

int building_monument::working() {
    auto &d = runtime_data();
    if (d.phase != MONUMENT_FINISHED || base.state != BUILDING_STATE_VALID) {
        return 0;
    }

    if (has_labour_problems()) {
        return 0;
    }

    return id();
}

bool building_monument::requires_resource(e_resource resource) const {
    int phases = this->phases();
    for (int phase = 1; phase < phases; phase++) {
        if (needs_resource(resource, phase) > 0) {
            return true;
        }
    }
    return false;
}

span_const<uint16_t> building_monument::active_workers() const {
    auto &d = runtime_data();
    return span_const<uint16_t>(d.workers);
}

int building_monument::workers_assigned() const {
    int workers_num = 0;
    for (auto wid : runtime_data().workers) {
        workers_num += wid > 0 ? 1 : 0;
    }
    return workers_num;
}

int building_monument::workers_slots() const {
    return (int)runtime_data().workers.size();
}

int building_monument::workers_onsite(e_figure_type figure_type) const {
    return building_monument_workers_onsite(&base, figure_type);
}

int building_monument::resource_pct(e_resource resource) const {
    if (resource < RESOURCES_MIN || resource >= RESOURCES_MAX) {
        return 0;
    }
    return (int)runtime_data().resources_pct[resource];
}

int building_monument::material_pct_min() const {
    if (runtime_data().phase == MONUMENT_FINISHED) {
        return 100;
    }

    const auto &d = runtime_data();
    int min_pct = 100;
    bool any = false;
    for (int ri = (int)RESOURCES_MIN; ri < (int)RESOURCES_MAX; ++ri) {
        const auto r = (e_resource)ri;
        if (needs_resource(r) <= 0) {
            continue;
        }
        any = true;
        const int pct = (int)d.resources_pct[r];
        if (pct < min_pct) {
            min_pct = pct;
        }
    }
    return any ? min_pct : 100;
}

void building_monument::set_tile_progress(tile2i tile, int v) {
    map_monuments_set_progress(tile, v);
}

bool building_monument::has_required_resources_to_build() const {
    int phases = this->phases();
    for (int phase = 1; phase < phases; phase++) {
        for (e_resource r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
            if (needs_resource(r, phase) > 0 &&
                !g_city.can_produce_resource(r)) {
                return false;
            }
        }
    }
    return true;
}

int building_monument::upgraded() {
    int monument_id = working();
    building *b = building_get(monument_id);
    if (!monument_id) {
        return 0;
    }
    auto &monumentd = b->dcast_monument()->runtime_data();
    if (!monumentd.upgrades) {
        return 0;
    }
    return monument_id;
}

int building_monument::module_type() {
    auto &d = runtime_data();
    return d.upgrades;
}

// Former storage-yard sled delivery table: no longer used, its slots are kept so saves keep their layout.
io_buffer* iob_city_building_monuments = new io_buffer([](io_buffer* iob, size_t version) {
    enum { UNUSED_DELIVERY_SLOTS = 32, UNUSED_DELIVERY_FIELDS = 4 };
    int unused = 0;
    iob->bind(BIND_SIGNATURE_INT32, &unused);
    for (int i = 0; i < UNUSED_DELIVERY_SLOTS * UNUSED_DELIVERY_FIELDS; ++i) {
        unused = 0;
        iob->bind(BIND_SIGNATURE_INT32, &unused);
    }
});

bool building_monument::need_workers() const {
    return has_free_worker_slot();
}

bool building_monument::has_free_worker_slot() const {
    if (!is_main()) {
        return false;
    }

    auto &d = runtime_data();
    for (auto w_id : d.workers) {
        if (!w_id) {
            return true;
        }
    }

    return false;
}

int building_monument::is_construction_halted() {
    return main()->state() == BUILDING_STATE_MOTHBALLED;
}

int building_monument::toggle_construction_halted() {
    building_impl *m = main();
    const bool halt = (m->state() != BUILDING_STATE_MOTHBALLED);
    for (building_impl *part = m; part; part = part->has_next() ? part->next() : nullptr) {
        part->base.state = halt ? BUILDING_STATE_MOTHBALLED : BUILDING_STATE_VALID;
    }
    return halt ? 1 : 0;
}

bool building_monument::need_stonemason() {
    return false;
}

bool building_monument::need_artisan() {
    return false;
}

bool building_monument::need_artisan_with(e_resource material) {
    return need_artisan() && needs_resource(material) > 0 && resource_pct(material) < 100;
}

bool building_monument::need_carpenter() {
    auto &d = runtime_data();
    if (d.phase == MONUMENT_FINISHED) {
        return false;
    }

    int phase = d.phase;

    // Check if monument needs TIMBER for current phase
    int needs_timber = needs_resource(RESOURCE_TIMBER, phase);
    if (needs_timber <= 0) {
        return false;
    }

    // Free worker slot required — without this, guilds keep spawning carpenters
    // that add_workers silently drops while need_carpenter stays true.
    if (!has_free_worker_slot()) {
        return false;
    }

    // Count existing carpenters
    int works_carpenters = 0;
    for (auto &id : d.workers) {
        figure *f = id > 0 ? figure_get(id) : nullptr;
        works_carpenters += (f && f->type == FIGURE_CARPENTER) ? 1 : 0;
    }

    // Carpenters are needed if monument needs TIMBER and we don't have enough carpenters
    // Typically need 1 carpenter for scaffolding construction
    return works_carpenters < 1;
}

int building_monument_find_bricklayer_task(figure_id fid) {
    int part = 0;
    buildings_valid_do([&](building &b) {
        if (part || !b.is_main()) {
            return;
        }
        if (auto *mon = b.dcast_monument()) {
            part = mon->try_assign_bricklayer(fid);
        }
    });
    return part;
}

bool building_monument::need_bricklayers() {
    auto &d = runtime_data();
    if (d.phase == MONUMENT_FINISHED) {
        return false;
    }

    int phase = d.phase;
    if (needs_resource(RESOURCE_BRICKS, phase) <= 0) {
        return false;
    }

    // Free worker slot required — same gate as need_carpenter. Without it, guilds
    // keep spawning bricklayers that add_workers silently drops (mudbrick pyramids
    // share the 5-slot list with masons/carpenters) while need_bricklayers stays true.
    if (!has_free_worker_slot()) {
        return false;
    }

    int works_bricklayers = 0;
    for (auto &id : d.workers) {
        figure *f = id > 0 ? figure_get(id) : nullptr;
        works_bricklayers += (f && f->type == FIGURE_BRICKLAYER) ? 1 : 0;
    }

    return works_bricklayers < needs_bricklayers(phase);
}

bool building_monument::is_unfinished() const {
    return runtime_data().phase != MONUMENT_FINISHED;
}

bool building_monument::is_finished() const {
    return runtime_data().phase == MONUMENT_FINISHED;
}

xstring building_monument::demolish_blocked_message() const {
    return "#monument_not_demolishable";
}

bool building_monument_is_non_tomb_type(e_building_type type) {
    switch (type) {
    case BUILDING_SPHINX:
    case BUILDING_SMALL_OBELISK:
    case BUILDING_LARGE_OBELISK:
    case BUILDING_SUN_TEMPLE:
    case BUILDING_ALEXANDRIA_LIBRARY:
    case BUILDING_CAESAREUM:
    case BUILDING_PHAROS_LIGHTHOUSE:
    case BUILDING_ABU_SIMBEL:
        return true;
    default:
        return false;
    }
}

bool building_monument_is_finished_burial_tomb(building &b) {
    if (!b.is_valid() || !b.is_main()) {
        return false;
    }
    if (!b.is_monument() || building_monument_is_non_tomb_type(b.type)) {
        return false;
    }
    auto *m = b.dcast_monument();
    return m && m->is_finished();
}

bool building_monument::has_funeral_done() const {
    const building *mb = base.main();
    if (!mb) {
        mb = &base;
    }
    const auto &d = *reinterpret_cast<const runtime_data_t *>(mb->runtime_data);
    return d.funeral_done != 0;
}

void building_monument::set_funeral_done(bool done) {
    building *mb = base.main();
    if (!mb) {
        mb = &base;
    }
    auto &d = *reinterpret_cast<runtime_data_t *>(mb->runtime_data);
    d.funeral_done = done ? 1 : 0;
}

bool building_monument::is_preexisting() const {
    const building *mb = base.main();
    if (!mb) {
        mb = &base;
    }
    const auto &d = *reinterpret_cast<const runtime_data_t *>(mb->runtime_data);
    return d.preexisting != 0;
}

void building_monument::set_preexisting(bool preexisting) {
    building *mb = base.main();
    if (!mb) {
        mb = &base;
    }
    auto &d = *reinterpret_cast<runtime_data_t *>(mb->runtime_data);
    d.preexisting = preexisting ? 1 : 0;
}

int building_monument::burial_stock(e_resource r) const {
    if (r <= RESOURCE_NONE || r >= RESOURCES_MAX) {
        return 0;
    }
    const building *mb = base.main();
    if (!mb) {
        mb = &base;
    }
    const auto &d = *reinterpret_cast<const runtime_data_t *>(mb->runtime_data);
    return d.burial_stock[r];
}

int building_monument::burial_stock_total() const {
    const building *mb = base.main();
    if (!mb) {
        mb = &base;
    }
    const auto &d = *reinterpret_cast<const runtime_data_t *>(mb->runtime_data);
    int total = 0;
    for (int r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
        total += d.burial_stock[r];
    }
    return total;
}

int building_monument::add_burial_stock(e_resource r, int n) {
    if (n <= 0 || r <= RESOURCE_NONE || r >= RESOURCES_MAX) {
        return 0;
    }
    building *mb = base.main();
    if (!mb) {
        mb = &base;
    }
    auto &d = *reinterpret_cast<runtime_data_t *>(mb->runtime_data);
    const int room = 255 - (int)d.burial_stock[r];
    const int added = std::min(n, room);
    d.burial_stock[r] = (uint8_t)(d.burial_stock[r] + added);
    return added;
}

bool building_monument::take_burial_stock(e_resource r, int n) {
    if (n <= 0 || r <= RESOURCE_NONE || r >= RESOURCES_MAX) {
        return false;
    }
    building *mb = base.main();
    if (!mb) {
        mb = &base;
    }
    auto &d = *reinterpret_cast<runtime_data_t *>(mb->runtime_data);
    if (d.burial_stock[r] < n) {
        return false;
    }
    d.burial_stock[r] = (uint8_t)(d.burial_stock[r] - n);
    return true;
}

// Mostly zero per-resource bytes: a presence bit per resource, then the present values only.
static void bind_sparse_resource_bytes(io_buffer* iob, uint8_t (&values)[RESOURCES_MAX]) {
    uint8_t present[(RESOURCES_MAX + 7) / 8] = {};
    if (!iob->is_read_access()) {
        for (int r = 0; r < RESOURCES_MAX; ++r) {
            if (values[r]) {
                present[r / 8] |= (uint8_t)(1 << (r % 8));
            }
        }
    }
    for (auto& bits : present) {
        iob->bind_u8(bits);
    }
    for (int r = 0; r < RESOURCES_MAX; ++r) {
        if (present[r / 8] & (1 << (r % 8))) {
            iob->bind_u8(values[r]);
        } else {
            values[r] = 0;
        }
    }
}

void building_monument::bind_block_engine_state(io_buffer* iob, int alt_image_base) {
    auto& d = runtime_data();

    iob->bind_u8(base.orientation);
    iob->bind_i8(d.phase);
    iob->bind_u8(d.layer);
    iob->bind_u8(d.stair_index);
    iob->bind_u8(d.variant);
    iob->bind_u8(d.funeral_done);
    iob->bind_u8(d.preexisting);
    iob->bind_u8(d.causeway_length);
    iob->bind_u8(d.causeway_dir);
    for (auto& w : d.workers) {
        iob->bind_u16(w);
    }

    // 0 = none, else 1 + offset from alt_image_base: the save does not depend on image pack ids.
    uint8_t alt_image_slot = 0;
    if (!iob->is_read_access() && d.alt_image > 0 && alt_image_base > 0) {
        const int offset = (int)d.alt_image - alt_image_base;
        alt_image_slot = (offset >= 0 && offset < 255) ? (uint8_t)(offset + 1) : 0;
    }
    iob->bind_u8(alt_image_slot);
    if (iob->is_read_access()) {
        d.alt_image = (alt_image_slot && alt_image_base > 0) ? (uint16_t)(alt_image_base + alt_image_slot - 1) : 0;
    }

    // Deliveries, burial goods and the block count live on the chain head only.
    if (base.is_main()) {
        bind_sparse_resource_bytes(iob, d.resources_pct);
        bind_sparse_resource_bytes(iob, d.burial_stock);

        auto& main = d.og_main;
        iob->bind_u8((uint8_t&)main.style);
        iob->bind_u8(main.size_variant);
        iob->bind_u16(main.remaining_blocks);
        iob->bind_u8(main.block_phase_active);
        iob->bind_u8(main.force_show_ramps);
    } else if (iob->is_read_access()) {
        std::fill(std::begin(d.resources_pct), std::end(d.resources_pct), 0);
        std::fill(std::begin(d.burial_stock), std::end(d.burial_stock), 0);
        d.og_main = {};
    }

    // The ramp sprite and its offsets are a draw cache (they follow the camera rotation), not saved.
    auto& part = d.og_part;
    iob->bind_u8(part.size_variant);
    iob->bind_u8(part.stage);
    iob->bind_u8(part.blocks);
    iob->bind_u8(part.layer);
    iob->bind_u8(part.target_layers);
    iob->bind_u8(part.subtype);
    iob->bind_u16(part.worker_figure_id);
    iob->bind_u8(part.ramp1_height);
    iob->bind_u8(part.ramp2_height);
    if (iob->is_read_access()) {
        part.ramp_image_id = 0;
        part.ramp_image_x1 = part.ramp_image_y1 = 0;
        part.ramp_image_x2 = part.ramp_image_y2 = 0;
    }
}

building *burial_provisions_pick_dispatch_tomb() {
    building *best = nullptr;
    int best_stock = 0x7fffffff;
    buildings_valid_do([&](building &b) {
        if (!building_monument_is_finished_burial_tomb(b)) {
            return;
        }
        auto *m = b.dcast_monument();
        if (!m || m->is_preexisting()) {
            return;
        }
        const int stock = m->burial_stock_total();
        if (stock < best_stock) {
            best_stock = stock;
            best = &b;
        }
    });
    return best;
}

int burial_provisions_tomb_stock_total(e_resource r) {
    if (r <= RESOURCE_NONE || r >= RESOURCES_MAX) {
        return 0;
    }
    int total = 0;
    buildings_valid_do([&](building &b) {
        if (!building_monument_is_finished_burial_tomb(b)) {
            return;
        }
        auto *m = b.dcast_monument();
        if (!m || m->is_preexisting()) {
            return;
        }
        total += m->burial_stock(r);
    });
    return total;
}

void burial_provisions_sync_city_dispatched() {
    for (int r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
        g_scenario.monuments.burial_provisions[r].dispatched = burial_provisions_tomb_stock_total((e_resource)r);
    }
}

void burial_provisions_migrate_city_pool_to_tombs() {
    bool needs = false;
    for (int r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
        const int city = g_scenario.monuments.burial_provisions[r].dispatched;
        if (city > 0 && burial_provisions_tomb_stock_total((e_resource)r) == 0) {
            needs = true;
            break;
        }
    }
    if (!needs) {
        return;
    }

    building *tomb = burial_provisions_pick_dispatch_tomb();
    if (!tomb) {
        return;
    }
    auto *m = tomb->dcast_monument();
    if (!m) {
        return;
    }
    for (int r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
        const int city = g_scenario.monuments.burial_provisions[r].dispatched;
        if (city <= 0 || burial_provisions_tomb_stock_total((e_resource)r) > 0) {
            continue;
        }
        m->add_burial_stock((e_resource)r, city);
    }
}



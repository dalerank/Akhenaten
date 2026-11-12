#include "monument_royal_tomb.h"

#include "building/monuments.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_message.h"
#include "city/city_warnings.h"
#include "construction/build_planner.h"
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
#include "grid/random.h"
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "js/js_game.h"
#include "scenario/scenario.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_royal_tomb);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_medium_royal_tomb);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_large_royal_tomb);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_grand_royal_tomb);
BUILDING_RUNTIME_DATA_IMPL(building_royal_tomb)

namespace {

    monument g_monument_royal_tombs[ROYAL_TOMB_SIZES] = {
      monument{BUILDING_SMALL_ROYAL_TOMB},
      monument{BUILDING_MEDIUM_ROYAL_TOMB},
      monument{BUILDING_LARGE_ROYAL_TOMB},
      monument{BUILDING_GRAND_ROYAL_TOMB},
    };

    // OG TERRAIN_BLOCKS_MONUMENT; 0x20000000 is OG TERRAIN_ROCK_NEAR_MONUMENT (the Valley cliffs).
    constexpr uint32_t k_blocks_monument = 0xFEFFD76F;
    constexpr uint32_t k_rock_near_monument = TERRAIN_UNK_08;
    constexpr uint32_t k_tomb_rock = TERRAIN_ROCK | k_rock_near_monument;

    constexpr int k_spots_per_table = 3;

    // OG monument spots are shared by every chamber of a kind, across all tombs: one figure per
    // (spot table, stage) works at a time. A spot frees once its figure leaves the work action.
    std::array<figure_id, ROYAL_TOMB_SPOT_TABLES * k_spots_per_table> g_spot_figure{};

    bool figure_is_working(figure* f) {
        if (!f || !f->is_alive()) {
            return false;
        }
        if (f->type == FIGURE_STONEMASON) {
            return f->action_state == ACTION_9_MASON_WORK_OBELISK;
        }
        if (f->type == FIGURE_TOMB_ARTISAN) {
            return f->action_state == ACTION_14_TOMB_ARTISAN_WORK;
        }
        return false;
    }

    bool spot_free(int slot, figure_id self) {
        figure_id& fid = g_spot_figure[slot];
        if (fid && !figure_is_working(figure_get(fid))) {
            fid = 0;
        }
        return fid == 0 || fid == self;
    }

    e_figure_type spot_figure_type(int stage) {
        return stage == ROYAL_TOMB_STAGE_STONEMASONS ? FIGURE_STONEMASON : FIGURE_TOMB_ARTISAN;
    }

    int camera_view() {
        return (g_camera.orientation / 2) & 3;
    }

    bool tile_outside_site(tile2i t) {
        const auto* map = scenario_map_data();
        const int m = building_royal_tomb::MAP_EDGE_MARGIN;
        return t.x() < m || t.y() < m || t.x() >= map->width - m || t.y() >= map->height - m;
    }

    bool entrance_tile_free(tile2i t) {
        return map_grid_is_inside(t, 1) && (map_terrain_get(t) & k_blocks_monument) == 0;
    }

    const vec2i k_entrance_neighbours[4] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    void set_tile_image(int building_id, tile2i t, int image_id) {
        const int grid_offset = t.grid_offset();
        // OG overwrites the cliff terrain of every tomb tile with plain building terrain.
        map_terrain_set(grid_offset, TERRAIN_BUILDING);
        map_building_set(grid_offset, building_id);
        map_property_clear_constructing(grid_offset);
        map_property_set_multi_tile_size(grid_offset, 1);
        map_property_set_multi_tile_xy(grid_offset, 0, 0, 1);
        map_image_set(grid_offset, image_id);
        map_property_mark_draw_tile(grid_offset);
    }

    int pack_image(e_building_type type, int group, int offset) {
        const auto& params = (const building_royal_tomb::static_params&)building_static_params::get(type);
        if (params.art_pack <= 0 || group <= 0) {
            return 0;
        }
        const int img = image_id_from_group(params.art_pack, group);
        return img > 0 ? img + offset : 0;
    }

} // namespace

int building_royal_tomb::size_index(e_building_type type) {
    switch (type) {
    case BUILDING_MEDIUM_ROYAL_TOMB:
        return 1;
    case BUILDING_LARGE_ROYAL_TOMB:
        return 2;
    case BUILDING_GRAND_ROYAL_TOMB:
        return 3;
    default:
        return 0;
    }
}

bool building_royal_tomb::is_royal_tomb_type(e_building_type type) {
    return type == BUILDING_SMALL_ROYAL_TOMB || type == BUILDING_MEDIUM_ROYAL_TOMB || type == BUILDING_LARGE_ROYAL_TOMB
           || type == BUILDING_GRAND_ROYAL_TOMB;
}

const royal_tomb_layout& building_royal_tomb::layout_of(e_building_type type) {
    return g_royal_tomb_layouts[size_index(type)];
}

void building_royal_tomb::static_params::rebuild_construction(e_building_type type) {
    monument& m = g_monument_royal_tombs[size_index(type)];
    m.btype = type;
    m.phases.clear();
    // One phase per chamber stage: the rating reads phase / phases as the OG percent.
    const int stages = layout_of(type).chambers * ROYAL_TOMB_STAGE_DONE;
    for (int i = 0; i < stages; ++i) {
        m.phases.push_back({(uint8_t)i, monument_phase_resource{RESOURCE_NONE, 0}});
    }
}

void building_small_royal_tomb::static_params::archive_load(archive) {
    rebuild_construction(BUILDING_SMALL_ROYAL_TOMB);
}

void building_medium_royal_tomb::static_params::archive_load(archive) {
    rebuild_construction(BUILDING_MEDIUM_ROYAL_TOMB);
}

void building_large_royal_tomb::static_params::archive_load(archive) {
    rebuild_construction(BUILDING_LARGE_ROYAL_TOMB);
}

void building_grand_royal_tomb::static_params::archive_load(archive) {
    rebuild_construction(BUILDING_GRAND_ROYAL_TOMB);
}

const monument &building_small_royal_tomb::config() const {
    return g_monument_royal_tombs[0];
}

const monument &building_medium_royal_tomb::config() const {
    return g_monument_royal_tombs[1];
}

const monument &building_large_royal_tomb::config() const {
    return g_monument_royal_tombs[2];
}

const monument &building_grand_royal_tomb::config() const {
    return g_monument_royal_tombs[3];
}

const royal_tomb_part_init& building_royal_tomb::part_init() const {
    const auto& l = layout();
    return l.parts[std::min<int>(part_index(), l.part_count - 1)];
}

building_royal_tomb* building_royal_tomb::main_tomb() {
    auto* m = base.main()->dcast_royal_tomb();
    return m ? m : this;
}

const building_royal_tomb* building_royal_tomb::main_tomb() const {
    return const_cast<building_royal_tomb*>(this)->main_tomb();
}

building_royal_tomb* building_royal_tomb::part(int index) {
    building* p = &main_tomb()->base;
    for (int i = 0; i < index && p; ++i) {
        p = p->has_next() ? p->next() : nullptr;
    }
    return p ? p->dcast_royal_tomb() : nullptr;
}

int building_royal_tomb::spot_table() const {
    const int kind = part_init().kind;
    if (kind < 0 || kind >= ROYAL_TOMB_CHAMBER_KINDS) {
        return -1;
    }
    return g_royal_tomb_spot_tables[kind];
}

bool building_royal_tomb::part_has_active_worker() const {
    auto& d = const_cast<building_royal_tomb*>(this)->runtime_data();
    if (!d.worker_figure_id) {
        return false;
    }
    figure* f = figure_get(d.worker_figure_id);
    if (f && f->is_alive()) {
        const int a = f->action_state;
        if (f->type == FIGURE_STONEMASON
            && (a == ACTION_0_MASON_CREATED || a == ACTION_1_MASON_GOING || a == ACTION_9_MASON_WORK_OBELISK)) {
            return true;
        }
        if (f->type == FIGURE_TOMB_ARTISAN
            && (a == ACTION_10_TOMB_ARTISAN_CREATED || a == ACTION_11_TOMB_ARTISAN_GOING
                || a == ACTION_14_TOMB_ARTISAN_WORK)) {
            return true;
        }
    }
    d.worker_figure_id = 0;
    return false;
}

bool building_royal_tomb::check_work_for_figure(e_figure_type type, figure_id fid, bool assign,
  building_royal_tomb* m) {
    if (part_has_active_worker()) {
        return false;
    }
    if (!m) {
        m = main_tomb();
    }
    if (m->runtime_data().lamp_stock < LAMPS_PER_WORKER) {
        return false;
    }
    auto& d = runtime_data();
    const int t = spot_table();
    const int s = d.stage;
    if (!d.can_take_workers || t < 0 || s < ROYAL_TOMB_STAGE_STONEMASONS || s > ROYAL_TOMB_STAGE_ARTISANS_LAST) {
        return false;
    }
    if (spot_figure_type(s) != type || d.remaining_work[s - 1] == 0 || !spot_free(t * k_spots_per_table + s - 1, 0)) {
        return false;
    }
    if (!assign) {
        return true;
    }
    m->runtime_data().lamp_stock -= LAMPS_PER_WORKER;
    d.worker_figure_id = fid;
    if (figure* f = figure_get(fid)) {
        f->destination_building_id = id();
        f->destination_tile = access_point();
        f->roam_length = 0;
        f->wait_ticks = 0;
    }
    return true;
}

building_royal_tomb* building_royal_tomb::find_work(e_figure_type type, figure_id fid, bool assign, int only_stage) {
    // OG searches the tomb types small, medium, large, grand in turn, every part in id order.
    static const e_building_type order[]
      = {BUILDING_SMALL_ROYAL_TOMB, BUILDING_MEDIUM_ROYAL_TOMB, BUILDING_LARGE_ROYAL_TOMB, BUILDING_GRAND_ROYAL_TOMB};
    for (e_building_type bt : order) {
        for (building& b : city_buildings()) {
            if (!b.is_valid() || b.type != bt || !b.is_main()) {
                continue;
            }
            auto* m = b.dcast_royal_tomb();
            if (!m || m->is_finished()) {
                continue;
            }
            for (building* pb = &m->base; pb; pb = pb->has_next() ? pb->next() : nullptr) {
                auto* tomb = pb->dcast_royal_tomb();
                if (!tomb || (only_stage >= 0 && tomb->stage() != only_stage)) {
                    continue;
                }
                if (bt == BUILDING_GRAND_ROYAL_TOMB && tomb->stage() >= ROYAL_TOMB_STAGE_DONE) {
                    continue;
                }
                if (tomb->check_work_for_figure(type, fid, assign, m)) {
                    return tomb;
                }
            }
        }
    }
    return nullptr;
}

bool building_royal_tomb::work_tick(figure& f) {
    building_royal_tomb* p = nullptr;
    if (building* dest = building_get(f.destination_building_id); dest && dest->main() == base.main()) {
        p = dest->dcast_royal_tomb();
    }
    if (!p) {
        for (building* b = &main_tomb()->base; b; b = b->has_next() ? b->next() : nullptr) {
            auto* t = b->dcast_royal_tomb();
            if (t && t->runtime_data().worker_figure_id == f.id) {
                p = t;
                break;
            }
        }
    }
    if (!p) {
        return true;
    }

    auto& d = p->runtime_data();
    const int t = p->spot_table();
    if (t < 0) {
        return true;
    }
    const int s = d.stage;
    int attached = -1;
    for (int k = 0; k < k_spots_per_table; ++k) {
        if (g_spot_figure[t * k_spots_per_table + k] == f.id) {
            attached = k;
            break;
        }
    }
    if (attached >= 0) {
        if (attached + 1 != s) {
            g_spot_figure[t * k_spots_per_table + attached] = 0;
            return true;
        }
    } else {
        if (s < ROYAL_TOMB_STAGE_STONEMASONS || s > ROYAL_TOMB_STAGE_ARTISANS_LAST || spot_figure_type(s) != f.type
            || d.remaining_work[s - 1] == 0 || !spot_free(t * k_spots_per_table + s - 1, f.id)) {
            return true;
        }
        g_spot_figure[t * k_spots_per_table + s - 1] = f.id;
    }

    if (d.remaining_work[s - 1] > 0) {
        d.remaining_work[s - 1]--;
    }
    if (d.remaining_work[s - 1] >= 1) {
        return false;
    }
    d.worker_figure_id = 0;
    g_spot_figure[t * k_spots_per_table + s - 1] = 0;
    p->advance_stage();
    return true;
}

void building_royal_tomb::advance_stage() {
    building_royal_tomb* m = main_tomb();
    auto& d = runtime_data();
    if (d.stage < ROYAL_TOMB_STAGE_DONE) {
        if (++d.stage == ROYAL_TOMB_STAGE_OPENS_NEIGHBOURS) {
            for (int8_t n : part_init().neighbours) {
                if (n < 0) {
                    continue;
                }
                if (auto* q = m->part(n)) {
                    q->runtime_data().stage++;
                    q->runtime_data().can_take_workers = 1;
                }
            }
        }
        if (d.stage == ROYAL_TOMB_STAGE_DONE) {
            d.can_take_workers = 0;
        }
        m->refresh_part_images();
    }
    if (d.can_take_workers != 0 || !goals_reached()) {
        return;
    }
    if (m->progress_percent() == 100) {
        m->runtime_data().sealed = 1;
        m->refresh_part_images();
    }
}

int building_royal_tomb::progress_percent() const {
    const building_royal_tomb* m = main_tomb();
    const int chambers = m->layout().chambers;
    int stages = 0;
    int i = 0;
    for (const building* b = &m->base; b && i < chambers; b = b->has_next() ? b->next() : nullptr, ++i) {
        if (auto* t = const_cast<building*>(b)->dcast_royal_tomb()) {
            stages += t->runtime_data().stage;
        }
    }
    const double percent = (100.0 / (chambers * (double)ROYAL_TOMB_STAGE_DONE)) * stages;
    return percent > 99.9 ? 100 : (int)percent;
}

building_royal_tomb::progress_report building_royal_tomb::get_progress() const {
    progress_report r;
    building_royal_tomb* m = const_cast<building_royal_tomb*>(main_tomb());
    r.percent = progress_percent();
    r.stock = m->runtime_data().lamp_stock;
    // OG counts chamber workers only while the main chamber has one, and stops at the first idle chamber.
    if (!m->part_has_active_worker()) {
        return r;
    }
    int i = 0;
    for (building* b = &m->base; b && i < m->layout().chambers; b = b->has_next() ? b->next() : nullptr, ++i) {
        auto* t = b->dcast_royal_tomb();
        const figure_id wid = t ? t->runtime_data().worker_figure_id : 0;
        if (!wid) {
            break;
        }
        figure* f = figure_get(wid);
        if (!f) {
            break;
        }
        if (f->type == FIGURE_STONEMASON) {
            r.stonemasons++;
        } else if (f->type == FIGURE_LABORER) {
            r.laborers++;
        } else if (f->type == FIGURE_TOMB_ARTISAN) {
            r.artisans++;
        }
    }
    return r;
}

bool building_royal_tomb::has_chamber_at(int first_stage, int last_stage) const {
    const building_royal_tomb* m = main_tomb();
    int i = 0;
    for (const building* b = &m->base; b && i < m->layout().chambers; b = b->has_next() ? b->next() : nullptr, ++i) {
        auto* t = const_cast<building*>(b)->dcast_royal_tomb();
        const int s = t ? t->stage() : 0;
        if (s >= first_stage && s <= last_stage) {
            return true;
        }
    }
    return false;
}

bool building_royal_tomb::is_idle() const {
    const building_royal_tomb* m = main_tomb();
    if (m->runtime_data().lamp_stock > 0) {
        return false;
    }
    int i = 0;
    for (const building* b = &m->base; b && i < m->layout().chambers; b = b->has_next() ? b->next() : nullptr, ++i) {
        auto* t = const_cast<building*>(b)->dcast_royal_tomb();
        if (t && t->part_has_active_worker()) {
            return false;
        }
    }
    return true;
}

bool building_royal_tomb::wants_lamps() const {
    return is_main() && runtime_data().lamp_stock < LAMP_REFILL_BELOW && !part_has_active_worker();
}

void building_royal_tomb::add_lamp_stock(int amount) {
    if (amount <= 0) {
        return;
    }
    auto& d = main_tomb()->runtime_data();
    d.lamp_stock = (uint16_t)std::min(0xffff, d.lamp_stock + amount);
    main_tomb()->refresh_part_images();
}

bool building_royal_tomb::deliver_resource(e_resource resource, int amount) {
    if (resource != RESOURCE_LAMPS || amount <= 0) {
        return false;
    }
    add_lamp_stock(amount);
    return true;
}

bool building_royal_tomb::goals_reached() {
    return g_city.victory.state == e_victory_state_won || g_city.victory.force_win;
}

void building_royal_tomb::seal_if_goals_reached() {
    building_royal_tomb* m = main_tomb();
    auto& d = m->runtime_data();
    if (d.sealed || !goals_reached() || m->progress_percent() != 100) {
        return;
    }
    d.sealed = 1;
    m->refresh_part_images();
}

void building_royal_tomb::seal_all_finished() {
    for (building& b : city_buildings()) {
        if (b.is_valid() && b.is_main()) {
            if (auto* t = b.dcast_royal_tomb()) {
                t->seal_if_goals_reached();
            }
        }
    }
}

void building_royal_tomb::set_completed() {
    building_royal_tomb* m = main_tomb();
    auto& md = m->runtime_data();
    md.lamp_stock = LAMP_STOCK_FULL;
    md.sealed = 1;
    md.completion_shown = 1;
    for (building* b = &m->base; b; b = b->has_next() ? b->next() : nullptr) {
        auto* t = b->dcast_royal_tomb();
        if (!t) {
            continue;
        }
        auto& d = t->runtime_data();
        if (t->part_init().kind != ROYAL_TOMB_KIND_SEALING) {
            d.stage = ROYAL_TOMB_STAGE_DONE;
        }
        d.can_take_workers = 0;
        d.phase = MONUMENT_FINISHED;
    }
    m->refresh_part_images();
}

int building_royal_tomb::part_image(bool& per_tile) const {
    const building_royal_tomb* m = main_tomb();
    const auto& l = layout();
    const auto& p = part_init();
    const auto& d = runtime_data();
    per_tile = false;
    const int kind = p.kind;
    const bool entrance
      = kind == ROYAL_TOMB_KIND_ENTRANCE_A || kind == ROYAL_TOMB_KIND_ENTRANCE_B || kind == ROYAL_TOMB_KIND_ENTRANCE_C;
    // OG takes every tomb's closed rock from the small tomb pack (group 805); ours is the same
    // tombground group inside each tomb's own pack.
    if (d.stage == ROYAL_TOMB_STAGE_CLOSED && !entrance) {
        per_tile = true;
        return pack_image(type(), l.sealing_group, d.closed_variant);
    }
    int rot = p.anim_key - camera_view();
    if (rot < 0) {
        rot += 4;
    }
    int add = 0;
    if (d.stage >= 3 && d.stage <= 5) {
        add = (d.stage - 2) * 4;
    }
    if (l.last_part_closed && part_index() == l.last_part) {
        add = 0;
    }
    if (p.completed_image && (m->is_preexisting() || (goals_reached() && m->progress_percent() == 100))) {
        add += 4;
    }
    if (kind == ROYAL_TOMB_KIND_SEALING) {
        return pack_image(type(), l.sealing_group, l.sealing_adds_stage ? add : 0);
    }
    if (kind == ROYAL_TOMB_KIND_ENTRANCE_A) {
        return pack_image(type(), l.entrance_groups[0], rot);
    }
    if (kind == ROYAL_TOMB_KIND_ENTRANCE_B) {
        return pack_image(type(), l.entrance_groups[1], rot);
    }
    if (kind == ROYAL_TOMB_KIND_ENTRANCE_C) {
        return pack_image(type(), l.entrance_groups[2], rot);
    }
    for (int i = 0; i < l.chamber_image_count; ++i) {
        if (l.chamber_images[i].kind == kind) {
            const int group = l.chamber_images[i].group;
            return m->is_idle() ? pack_image(type(), group + 1, rot) : pack_image(type(), group, add + rot);
        }
    }
    return 0;
}

int building_royal_tomb::building_image_get() const {
    bool per_tile = false;
    return part_image(per_tile);
}

void building_royal_tomb::update_part_image() {
    const int size = std::max<int>(1, part_init().size);
    base.size = (uint8_t)size;
    if (is_sealed()) {
        // OG turns a sealed tomb back into cliff (rock-monument ground) and the entrance into
        // leveled land; without that terrain set we keep the closed rock and clear the entrance art.
        const int img = (part_index() == layout().last_part)
                          ? 0
                          : pack_image(type(), layout().sealing_group, runtime_data().closed_variant);
        for (int dy = 0; dy < size; ++dy) {
            for (int dx = 0; dx < size; ++dx) {
                set_tile_image(id(), tile().shifted(dx, dy), img);
            }
        }
        return;
    }
    bool per_tile = false;
    const int img = part_image(per_tile);
    if (per_tile) {
        for (int dy = 0; dy < size; ++dy) {
            for (int dx = 0; dx < size; ++dx) {
                set_tile_image(id(), tile().shifted(dx, dy), img);
            }
        }
        return;
    }
    map_building_tiles_add(id(), tile(), size, img, TERRAIN_BUILDING);
    for (int dy = 0; dy < size; ++dy) {
        for (int dx = 0; dx < size; ++dx) {
            map_terrain_set(tile().shifted(dx, dy).grid_offset(), TERRAIN_BUILDING);
        }
    }
}

void building_royal_tomb::refresh_part_images() {
    building_royal_tomb* m = main_tomb();
    auto& md = m->runtime_data();
    if (md.phase != MONUMENT_FINISHED) {
        int stages = 0;
        int i = 0;
        for (building* b = &m->base; b && i < m->layout().chambers; b = b->has_next() ? b->next() : nullptr, ++i) {
            if (auto* t = b->dcast_royal_tomb()) {
                stages += t->stage();
            }
        }
        md.phase = (int8_t)std::min(stages, m->phases() - 1);
    }
    for (building* b = &m->base; b; b = b->has_next() ? b->next() : nullptr) {
        if (auto* t = b->dcast_royal_tomb()) {
            t->update_part_image();
        }
    }
}

void building_royal_tomb::init_part(int index) {
    const auto& l = layout();
    const auto& p = l.parts[index];
    auto& d = runtime_data();
    d.part = (uint16_t)index;
    d.stage = index == 0 ? ROYAL_TOMB_STAGE_STONEMASONS : ROYAL_TOMB_STAGE_CLOSED;
    d.can_take_workers = index == 0 ? 1 : 0;
    d.worker_figure_id = 0;
    d.remaining_work.fill((uint16_t)std::max<int>(0, p.work));
    d.closed_variant = p.closed_variant >= 0 ? (uint8_t)p.closed_variant
                                             : (uint8_t)(map_random_get(tile()) % ROYAL_TOMB_CLOSED_VARIANTS);
    d.sealed = 0;
    d.completion_shown = 0;
    d.legacy_layout = 0;
    d.lamp_stock = 0;
    d.phase = 0;
    d.variant = 0;
    base.orientation = 0;
    base.size = (uint8_t)std::max<int>(1, p.size);
}

void building_royal_tomb::place_parts() {
    const auto& l = layout();
    tile2i origin = tile();
    base.prev_part_building_id = 0;
    base.next_part_building_id = 0;
    base.tile = origin.shifted(l.parts[0].dx, l.parts[0].dy);
    init_part(0);

    building* prev = &base;
    for (int i = 1; i < l.part_count; ++i) {
        const auto& p = l.parts[i];
        building* b = building_create(type(), origin.shifted(p.dx, p.dy), 0);
        if (!b || b->id <= 0) {
            break;
        }
        game_undo_add_building(b);
        b->prev_part_building_id = prev->id;
        b->next_part_building_id = 0;
        prev->next_part_building_id = b->id;
        if (auto* t = b->dcast_royal_tomb()) {
            t->init_part(i);
        }
        prev = b;
    }
    refresh_part_images();
}

void building_royal_tomb::on_place_update_tiles(int /*orientation*/, int /*variant*/) {
    place_parts();
}

void building_royal_tomb::on_place_checks() {
}

void building_royal_tomb::on_phase_changed(int, int) {
}

void building_royal_tomb::set_phase(int phase) {
    if (phase != MONUMENT_FINISHED && phase < phases()) {
        runtime_data().phase = (int8_t)phase;
        return;
    }
    building_royal_tomb* m = main_tomb();
    for (building* b = &m->base; b; b = b->has_next() ? b->next() : nullptr) {
        auto* t = b->dcast_royal_tomb();
        if (!t) {
            continue;
        }
        auto& d = t->runtime_data();
        if (t->is_chamber()) {
            d.stage = ROYAL_TOMB_STAGE_DONE;
            d.can_take_workers = 0;
        }
        d.phase = MONUMENT_FINISHED;
    }
    m->refresh_part_images();
}

void building_royal_tomb::on_destroy() {
    if (auto& d = runtime_data(); d.worker_figure_id) {
        d.worker_figure_id = 0;
    }
}

void building_royal_tomb::update_day() {
    building_impl::update_day();
    if (!is_main()) {
        return;
    }
    auto& d = runtime_data();
    if (d.phase != MONUMENT_FINISHED && progress_percent() >= 100) {
        for (building* b = &base; b; b = b->has_next() ? b->next() : nullptr) {
            if (auto* t = b->dcast_royal_tomb()) {
                t->runtime_data().phase = MONUMENT_FINISHED;
            }
        }
        if (!d.completion_shown) {
            d.completion_shown = 1;
            messages::popup("message_monument_complete", 0, tile().grid_offset());
        }
        refresh_part_images();
    }
    if (d.phase == MONUMENT_FINISHED) {
        seal_if_goals_reached();
    }
}

void building_royal_tomb::update_map_orientation(int /*map_orientation*/) {
    if (is_main()) {
        refresh_part_images();
    }
}

bool building_royal_tomb::needs_resources() const {
    return false;
}

bool building_royal_tomb::need_stonemason() {
    if (!is_main() || is_finished()) {
        return false;
    }
    for (building* b = &base; b; b = b->has_next() ? b->next() : nullptr) {
        auto* t = b->dcast_royal_tomb();
        if (t && t->check_work_for_figure(FIGURE_STONEMASON, 0, false, this)) {
            return true;
        }
    }
    return false;
}

bool building_royal_tomb::need_artisan() {
    // Tomb artisans are dispatched by building_royal_tomb::find_work from the guild, per stage material.
    return false;
}

bool building_royal_tomb::need_workers() const {
    return false;
}

void building_royal_tomb::add_workers(figure_id fid) {
    figure* f = figure_get(fid);
    if (!f) {
        return;
    }
    building_royal_tomb* m = main_tomb();
    for (building* b = &m->base; b; b = b->has_next() ? b->next() : nullptr) {
        auto* t = b->dcast_royal_tomb();
        if (t && t->check_work_for_figure((e_figure_type)f->type, fid, true, m)) {
            return;
        }
    }
}

void building_royal_tomb::remove_worker(figure_id fid) {
    for (building* b = &main_tomb()->base; b; b = b->has_next() ? b->next() : nullptr) {
        auto* t = b->dcast_royal_tomb();
        if (t && t->runtime_data().worker_figure_id == fid) {
            t->runtime_data().worker_figure_id = 0;
        }
    }
    for (auto& slot : g_spot_figure) {
        if (slot == fid) {
            slot = 0;
        }
    }
}

tile2i building_royal_tomb::entrance_access_tile() const {
    const building_royal_tomb* m = main_tomb();
    const auto& l = m->layout();
    tile2i origin = m->tile().shifted(-l.parts[0].dx, -l.parts[0].dy);
    const auto& e = l.parts[l.last_part];
    tile2i entrance = origin.shifted(e.dx, e.dy);
    for (const vec2i& n : k_entrance_neighbours) {
        tile2i t = entrance.shifted(n.x, n.y);
        if (entrance_tile_free(t) && !map_building_at(t)) {
            return t;
        }
    }
    return entrance;
}

tile2i building_royal_tomb::center_point() const {
    grid_area area = get_area();
    return tile2i((area.tmin().x() + area.tmax().x()) / 2, (area.tmin().y() + area.tmax().y()) / 2);
}

tile2i building_royal_tomb::access_point() const {
    return entrance_access_tile();
}

grid_area building_royal_tomb::get_area() const {
    const building_royal_tomb* m = main_tomb();
    const auto& l = m->layout();
    tile2i origin = m->tile().shifted(-l.parts[0].dx, -l.parts[0].dy);
    int min_x = 0x7fff, min_y = 0x7fff, max_x = -0x7fff, max_y = -0x7fff;
    for (int i = 0; i < l.part_count; ++i) {
        const auto& p = l.parts[i];
        min_x = std::min<int>(min_x, p.dx);
        min_y = std::min<int>(min_y, p.dy);
        max_x = std::max<int>(max_x, p.dx + p.size - 1);
        max_y = std::max<int>(max_y, p.dy + p.size - 1);
    }
    return {origin.shifted(min_x, min_y), origin.shifted(max_x, max_y)};
}

bool building_royal_tomb::part_tile_allowed(const royal_tomb_layout& l, int part, tile2i t) {
    if (tile_outside_site(t)) {
        return false;
    }
    const uint32_t terrain = map_terrain_get(t) & k_blocks_monument;
    if (part == l.last_part) {
        return terrain == 0 && !map_building_at(t);
    }
    return terrain == k_tomb_rock && !map_building_at(t);
}

bool building_royal_tomb::can_place_at(e_building_type type, tile2i origin) {
    const auto& l = layout_of(type);
    for (int i = 0; i < l.part_count; ++i) {
        const auto& p = l.parts[i];
        tile2i pt = origin.shifted(p.dx, p.dy);
        if (i == l.last_part) {
            bool connected = false;
            for (const vec2i& n : k_entrance_neighbours) {
                connected |= entrance_tile_free(pt.shifted(n.x, n.y));
            }
            if (!connected) {
                return false;
            }
        }
        for (int dy = 0; dy < p.size; ++dy) {
            for (int dx = 0; dx < p.size; ++dx) {
                if (!part_tile_allowed(l, i, pt.shifted(dx, dy))) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool building_royal_tomb::has_unfinished_royal_tomb(e_building_type type) {
    return building_monument_has_unfinished({type}, /*main_parts_only*/ true);
}

void building_royal_tomb::preview::setup_preview_graphics(build_planner &planer) const {
    planer.init_tiles(1, 1);
}

uint32_t building_royal_tomb::preview::ghost_ignore_terrain(build_planner&, tile2i) const {
    return TERRAIN_ALL;
}

bool building_royal_tomb::preview::ghost_allow_tile(build_planner&, tile2i) const {
    return true;
}

int building_royal_tomb::preview::construction_place(build_planner& planer, tile2i /*start*/, tile2i end,
  int orientation, int variant) const {
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
    if (!can_place_at(p.build_type, end)) {
        p.set_warning("#must_be_over_cliffs");
        return CAN_NOT_PLACE;
    }
    if (has_unfinished_royal_tomb(p.build_type)) {
        p.set_warning("#only_one_building_of_this_type");
        return CAN_NOT_PLACE;
    }
    return state;
}

int building_royal_tomb::preview::finalize_check(build_planner &p, tile2i tile, tile2i end, int state) const {
    state = building_planer_renderer::finalize_check(p, tile, end, state);
    if (state != CAN_PLACE) {
        return state;
    }
    if (!can_place_at(p.build_type, end)) {
        p.set_warning("#entrance_on_clear_land");
        g_warning_manager.show("#must_be_over_cliffs");
        return CAN_NOT_PLACE;
    }
    if (has_unfinished_royal_tomb(p.build_type)) {
        p.set_warning("#only_one_building_of_this_type");
        g_warning_manager.show("#only_one_building_of_this_type");
        return CAN_NOT_PLACE;
    }
    return CAN_PLACE;
}

void building_royal_tomb::preview::ghost_preview(build_planner &planer, painter &ctx, tile2i /*start*/, tile2i end, vec2i /*pixel*/) const {
    const auto& l = layout_of(planer.build_type);
    for (int i = 0; i < l.part_count; ++i) {
        const auto& p = l.parts[i];
        tile2i pt = end.shifted(p.dx, p.dy);
        bool connected = true;
        if (i == l.last_part) {
            connected = false;
            for (const vec2i& n : k_entrance_neighbours) {
                connected |= entrance_tile_free(pt.shifted(n.x, n.y));
            }
        }
        for (int dy = 0; dy < p.size; ++dy) {
            for (int dx = 0; dx < p.size; ++dx) {
                tile2i t = pt.shifted(dx, dy);
                if (tile_outside_site(t)) {
                    continue;
                }
                const bool ok = connected && part_tile_allowed(l, i, t);
                build_planner::draw_flat_tile(ctx, g_camera.lookup_tile_to_pixel(t),
                  ok ? COLOR_MASK_GREEN_30 : COLOR_MASK_RED_30);
            }
        }
    }
}

void building_royal_tomb::on_post_load() {
    building_monument::on_post_load();
    if (!is_main()) {
        return;
    }
    if (runtime_data().legacy_layout) {
        convert_legacy_layout();
        return;
    }
    refresh_part_images();
}

// Pre-v201 royal tombs were one record over an 11x20-style cliff bulk with art phases. Rebuild them
// as the OG part chain on the same corner; a finished one comes back sealed, an unfinished one starts over.
void building_royal_tomb::convert_legacy_layout() {
    auto& d = runtime_data();
    const bool finished = d.phase == MONUMENT_FINISHED;
    const bool preexisting = d.preexisting != 0;
    const bool funeral = d.funeral_done != 0;
    tile2i corner = tile();
    for (int dy = -2; dy < 40; ++dy) {
        for (int dx = -2; dx < 40; ++dx) {
            tile2i t = corner.shifted(dx, dy);
            if (map_grid_is_inside(t, 1) && map_building_at(t) == id()) {
                map_building_tile_clear_at(t.grid_offset(), type());
            }
        }
    }
    const auto& l = layout();
    int min_x = 0x7fff, min_y = 0x7fff;
    for (int i = 0; i < l.part_count; ++i) {
        min_x = std::min<int>(min_x, l.parts[i].dx);
        min_y = std::min<int>(min_y, l.parts[i].dy);
    }
    base.tile = corner.shifted(-min_x, -min_y);
    place_parts();
    if (finished || preexisting) {
        set_completed();
    }
    set_funeral_done(funeral);
}

void building_royal_tomb::bind_dynamic(io_buffer* iob, size_t version) {
    auto &d = runtime_data();

    if (version < 202) {
        iob->bind(BIND_SIGNATURE_UINT16, &d.lamp_stock);
        for (int i = 0; i < RESOURCES_MAX; i++) {
            iob->bind(BIND_SIGNATURE_UINT8, &d.burial_stock[i]);
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
        d.legacy_layout = 1;
        return;
    }

    iob->bind(BIND_SIGNATURE_UINT16, &d.part);
    iob->bind(BIND_SIGNATURE_UINT8, &d.stage);
    iob->bind(BIND_SIGNATURE_UINT8, &d.can_take_workers);
    for (auto& w : d.remaining_work) {
        iob->bind(BIND_SIGNATURE_UINT16, &w);
    }
    iob->bind(BIND_SIGNATURE_UINT16, &d.worker_figure_id);
    iob->bind(BIND_SIGNATURE_UINT8, &d.closed_variant);
    iob->bind(BIND_SIGNATURE_UINT16, &d.lamp_stock);
    iob->bind(BIND_SIGNATURE_UINT8, &d.sealed);
    iob->bind(BIND_SIGNATURE_UINT8, &d.completion_shown);
    iob->bind(BIND_SIGNATURE_UINT8, &base.orientation);
    iob->bind(BIND_SIGNATURE_UINT8, &d.phase);
    iob->bind(BIND_SIGNATURE_UINT8, &d.funeral_done);
    iob->bind(BIND_SIGNATURE_UINT8, &d.preexisting);
    iob->bind(BIND_SIGNATURE_UINT8, &d.variant);
    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &d.burial_stock[i]);
    }
    d.legacy_layout = 0;
}

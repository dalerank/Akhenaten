#include "monument_abu_simbel.h"

#include "building/monuments.h"
#include "city/city.h"
#include "city/city_message.h"
#include "construction/build_planner.h"
#include "figure/figure.h"
#include "figuretype/figure_carpenter.h"
#include "figuretype/figure_stonemason.h"
#include "game/game_config.h"
#include "game/undo.h"
#include "graphics/color.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/view/lookup.h"
#include "graphics/view/view.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "js/js_register.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_abu_simbel);
BUILDING_RUNTIME_DATA_IMPL(building_abu_simbel)

namespace {
    enum {
        // OG map_grid_is_inside_size(..., 3) in monument_object_can_place.
        MAP_EDGE_MARGIN = 3,
    };

    constexpr uint32_t k_monument_rock = TERRAIN_ROCK | TERRAIN_ROCK_NEAR_MONUMENT;
    // OG TERRAIN_BLOCKS_MONUMENT (0xFEFFD76F) without the planner bit Akhenaten keeps in OG's TERRAIN_MONUMENT.
    constexpr uint32_t k_blocks_monument = 0xFEFFD76Fu & ~(uint32_t)TERRAIN_PLANER_FUTURE;

    struct monument_abu_simbel_cfg : public monument {
        monument_abu_simbel_cfg() : monument{BUILDING_ABU_SIMBEL} {
            for (uint8_t i = 0; i < building_abu_simbel::STAGE_COMPLETE; ++i) {
                phases.push_back({i, monument_phase_resource{ARCHITECTS, 1}});
            }
        }
    } g_monument_abu_simbel;

    enum {
        VIEWS = 4,
    };

    const building_abu_simbel::static_params& abu_params() {
        return building_abu_simbel::current_params();
    }

    const abu_simbel_part_cfg* part_row(int part) {
        const auto& parts = abu_params().parts;
        return (part >= 0 && part < (int)parts.size()) ? &parts[part] : nullptr;
    }

    const abu_simbel_part_kind* kind_row(const xstring& name) {
        for (const auto& k : abu_params().part_kinds) {
            if (k.name == name) {
                return &k;
            }
        }
        return nullptr;
    }

    const abu_simbel_part_kind* part_kind_row(int part) {
        const abu_simbel_part_cfg* p = part_row(part);
        return p ? kind_row(p->kind) : nullptr;
    }

    int part_size(int part) {
        const abu_simbel_part_kind* k = part_kind_row(part);
        return k ? k->size : 0;
    }

    const abu_simbel_stage_cfg* stage_row(int stage) {
        const auto& stages = abu_params().stages;
        return (stage >= 0 && stage < (int)stages.size()) ? &stages[stage] : nullptr;
    }

    e_figure_type stage_figure(int stage) {
        const abu_simbel_stage_cfg* s = stage_row(stage);
        if (!s || s->scaffold.empty() == s->art.empty()) {
            return FIGURE_NONE;
        }
        return s->scaffold.empty() ? FIGURE_STONEMASON : FIGURE_CARPENTER;
    }

    uint16_t stage_work(int stage) {
        const abu_simbel_stage_cfg* s = stage_row(stage);
        return s ? s->work : 0;
    }

    // The art stage a part has reached once `stage` stages are done: how many of them carved it.
    int part_art_stage(int part, int stage) {
        const abu_simbel_part_cfg* p = part_row(part);
        if (!p) {
            return 0;
        }
        const auto& stages = abu_params().stages;
        int art = 0;
        for (int i = 0; i < stage && i < (int)stages.size(); ++i) {
            art += (stages[i].scaffold.empty() && stages[i].art == p->id) ? 1 : 0;
        }
        return art;
    }

    // OG built_parts: raised by the first stage that names the scaffold, lowered by the second.
    bool scaffold_raised(const xstring& name, int stage) {
        const auto& stages = abu_params().stages;
        int seen = 0;
        for (int i = 0; i < stage && i < (int)stages.size(); ++i) {
            seen += stages[i].scaffold == name ? 1 : 0;
        }
        return seen == 1;
    }

    // The cliff kinds take image family + "_" + (view + rotate) % 4, the others name the image per view.
    abu_simbel_view_art kind_view_art(const abu_simbel_part_kind& k, int view) {
        if (k.family.empty()) {
            return view < (int)k.views.size() ? k.views[view] : abu_simbel_view_art{};
        }
        abu_simbel_view_art art;
        art.image.printf("%s_%d", k.family.c_str(), (view + k.rotate) % VIEWS);
        return art;
    }

    int camera_view() {
        return (g_camera.orientation / 2) & 3;
    }

    bool tile_fits(tile2i t, bool on_rock) {
        const auto* map = scenario_map_data();
        if (t.x() < MAP_EDGE_MARGIN || t.y() < MAP_EDGE_MARGIN || t.x() >= map->width - MAP_EDGE_MARGIN
            || t.y() >= map->height - MAP_EDGE_MARGIN) {
            return false;
        }
        const uint32_t terrain = (uint32_t)map_terrain_get(t) & k_blocks_monument;
        return terrain == (on_rock ? k_monument_rock : 0);
    }

    bool tile_near_edge(tile2i t) {
        const auto* map = scenario_map_data();
        return t.x() < MAP_EDGE_MARGIN || t.y() < MAP_EDGE_MARGIN || t.x() >= map->width - MAP_EDGE_MARGIN
               || t.y() >= map->height - MAP_EDGE_MARGIN;
    }

    template <typename F>
    void for_each_site_tile(tile2i origin, F f) {
        for (const auto& p : abu_params().parts) {
            const abu_simbel_part_kind* k = kind_row(p.kind);
            if (!k) {
                continue;
            }
            tile2i po = origin.shifted(p.dx, p.dy);
            for (int dy = 0; dy < k->size; ++dy) {
                for (int dx = 0; dx < k->size; ++dx) {
                    f(po.shifted(dx, dy), k->on_rock);
                }
            }
        }
    }

    void draw_placement(painter& ctx, tile2i origin) {
        for_each_site_tile(origin, [&](tile2i t, bool on_rock) {
            if (tile_near_edge(t)) {
                return;
            }
            const color mask = tile_fits(t, on_rock) ? COLOR_MASK_GREEN_30 : COLOR_MASK_RED_30;
            build_planner::draw_flat_tile(ctx, g_camera.lookup_tile_to_pixel(t), mask);
        });
    }

    bool is_working_action(const figure& f) {
        if (f.type == FIGURE_STONEMASON) {
            return f.action_state == ACTION_9_MASON_WORK_OBELISK;
        }
        if (f.type == FIGURE_CARPENTER) {
            return f.action_state == ACTION_2_CARPENTER_WORK;
        }
        return false;
    }

    bool is_heading_or_working(const figure& f) {
        if (f.type == FIGURE_STONEMASON) {
            return f.action_state == ACTION_0_MASON_CREATED || f.action_state == ACTION_1_MASON_GOING
                   || f.action_state == ACTION_9_MASON_WORK_OBELISK;
        }
        if (f.type == FIGURE_CARPENTER) {
            return f.action_state == ACTION_1_CARPENTER_GO_TO_SITE || f.action_state == ACTION_2_CARPENTER_WORK;
        }
        return false;
    }

    figure* abu_simbel_figure(uint16_t fid) {
        figure* f = fid ? figure_get(fid) : nullptr;
        if (!f || !f->is_alive()) {
            return nullptr;
        }
        building* dest = f->destination();
        return (dest && dest->type == BUILDING_ABU_SIMBEL) ? f : nullptr;
    }

    // OG monument_spot_animate: a spot lets go of its figure once the figure stops working.
    bool spot_still_held(uint16_t fid) {
        figure* f = abu_simbel_figure(fid);
        return f && is_working_action(*f);
    }
} // namespace

const monument& building_abu_simbel::config() const {
    return g_monument_abu_simbel;
}

building_abu_simbel* building_abu_simbel::main_abu_simbel() {
    building_impl* m = main();
    auto* a = m ? m->dcast_abu_simbel() : nullptr;
    return a ? a : this;
}

const building_abu_simbel* building_abu_simbel::main_abu_simbel() const {
    return const_cast<building_abu_simbel*>(this)->main_abu_simbel();
}

const abu_simbel_part_kind* building_abu_simbel::part_kind() const {
    return part_kind_row(part_index());
}

int building_abu_simbel::stage() const {
    const int p = main_abu_simbel()->runtime_data().phase;
    if (p == MONUMENT_FINISHED || p >= STAGE_COMPLETE) {
        return STAGE_COMPLETE;
    }
    return std::max(p, 0);
}

int building_abu_simbel::progress_percent() const {
    const int s = stage();
    return s >= STAGE_COMPLETE ? 100 : s * 100 / STAGE_COMPLETE;
}

bool building_abu_simbel::site_fits(tile2i origin) {
    bool fits = !abu_params().parts.empty();
    for_each_site_tile(origin, [&](tile2i t, bool on_rock) { fits = fits && tile_fits(t, on_rock); });
    return fits;
}

bool building_abu_simbel::spot_free() const {
    const auto& d = main_abu_simbel()->runtime_data();
    return stage() < STAGE_COMPLETE && d.spot_work > 0 && !spot_still_held(d.spot_figure);
}

bool building_abu_simbel::has_free_spot(e_figure_type type) const {
    const e_figure_type figure = stage_figure(stage());
    return figure != FIGURE_NONE && figure == type && spot_free();
}

// OG abu_simbel_part_has_active_worker: one worker at a time, from dispatch until he leaves the site.
bool building_abu_simbel::has_active_worker() const {
    figure* f = abu_simbel_figure(main_abu_simbel()->runtime_data().workers[0]);
    return f && is_heading_or_working(*f);
}

bool building_abu_simbel::need_stonemason() {
    return is_main() && !is_finished() && !has_active_worker() && has_free_spot(FIGURE_STONEMASON);
}

bool building_abu_simbel::need_carpenter() {
    return is_main() && !is_finished() && !has_active_worker() && has_free_spot(FIGURE_CARPENTER);
}

bool building_abu_simbel::need_workers() const {
    return false;
}

bool building_abu_simbel::needs_resources() const {
    return false;
}

void building_abu_simbel::add_workers(figure_id fid) {
    main_abu_simbel()->runtime_data().workers[0] = fid;
}

void building_abu_simbel::remove_worker(figure_id fid) {
    auto& workers = main_abu_simbel()->runtime_data().workers;
    if (workers[0] == fid) {
        workers[0] = 0;
    }
}

// OG abu_simbel_figure_work_tick_spot: one work per tick at the single spot of the current stage.
bool building_abu_simbel::work_tick(figure& f) {
    building_abu_simbel* m = main_abu_simbel();
    if (m != this) {
        return m->work_tick(f);
    }
    if (is_finished()) {
        return true;
    }

    auto& d = runtime_data();
    const bool attached = d.spot_figure == f.id && d.spot_work > 0;
    if (!attached) {
        if (!has_free_spot(f.type)) {
            return true;
        }
        d.spot_figure = f.id;
    }

    d.spot_work--;
    if (d.spot_work > 0) {
        return false;
    }
    advance_stage();
    return true;
}

// OG abu_simbel_advance_stage.
void building_abu_simbel::advance_stage() {
    const int s = stage();
    if (s >= STAGE_COMPLETE) {
        return;
    }
    set_stage(s + 1);
    if (is_finished()) {
        messages::popup("abu_simbel_congratulations", 0, tile().grid_offset());
    }
}

void building_abu_simbel::set_stage(int target) {
    building_abu_simbel* m = main_abu_simbel();
    if (m != this) {
        m->set_stage(target);
        return;
    }
    target = std::clamp(target, 0, (int)STAGE_COMPLETE);
    for (building* p = &base; p; p = p->has_next() ? p->next() : nullptr) {
        if (auto* part = p->dcast_abu_simbel()) {
            part->set_phase(target);
        }
    }
    auto& d = runtime_data();
    d.spot_work = stage_work(target);
    d.spot_figure = 0;
    refresh_part_images();
}

void building_abu_simbel::refresh_part_images() {
    for (building* p = &main_abu_simbel()->base; p; p = p->has_next() ? p->next() : nullptr) {
        if (auto* part = p->dcast_abu_simbel()) {
            map_building_tiles_add(p->id, p->tile, p->size, part->building_image_get(), TERRAIN_BUILDING);
        }
    }
}

// OG abu_simbel_part_image: the art of a record by its kind and the camera view (part_kinds in abu_simbel.js).
int building_abu_simbel::building_image_get() const {
    const abu_simbel_part_kind* kind = part_kind();
    if (!kind) {
        return 0;
    }
    const abu_simbel_view_art art = kind_view_art(*kind, camera_view());
    const int first = current_params().first_img(art.image);
    if (first <= 0) {
        return 0;
    }
    return first + art.offset + (art.two_per_art_stage ? part_art_stage(part_index(), stage()) * 2 : 0);
}

int building_abu_simbel::scaffolds_raised() const {
    int count = 0;
    for (const auto& sc : abu_params().scaffolds) {
        count += scaffold_raised(sc.name, stage()) ? 1 : 0;
    }
    return count;
}

int building_abu_simbel::scaffold_draw_count() const {
    const int view = camera_view();
    // OG draw_abu_simbel_top: the front record anchors the scaffolds in N/S, the back record in E/W; only
    // views 0 and 3 have offsets, so the south and east views draw none.
    const int anchor = view == 0 ? 0 : (view == 3 ? 1 : -1);
    if (part_index() != anchor || !game_features::gameplay_change_abu_simbel_draw_scaffolds) {
        return 0;
    }
    int count = 0;
    for (const auto& sc : abu_params().scaffolds) {
        count += (scaffold_raised(sc.name, stage()) && current_params().first_img(sc.image) > 0) ? 1 : 0;
    }
    return count;
}

// OG abu_simbel_draw_built_parts.
bool building_abu_simbel::draw_ornaments_and_animations_height(painter& ctx, vec2i point, tile2i tile, color mask) {
    const bool drew = building_monument::draw_ornaments_and_animations_height(ctx, point, tile, mask);
    if (scaffold_draw_count() == 0) {
        return drew;
    }
    const int view = camera_view();
    for (const auto& sc : abu_params().scaffolds) {
        const int first = current_params().first_img(sc.image);
        if (!scaffold_raised(sc.name, stage()) || first <= 0) {
            continue;
        }
        auto& command = ImageDraw::create_subcommand(ctx, render_command_t::ert_drawtile);
        command.image_id = first + (view & 1);
        command.pixel = point + (view == 0 ? sc.view0 : sc.view3);
        command.mask = mask;
    }
    return true;
}

void building_abu_simbel::preview::setup_preview_graphics(build_planner& planer) const {
    planer.init_tiles(1, 1);
}

uint32_t building_abu_simbel::preview::ghost_ignore_terrain(build_planner& /*p*/, tile2i /*tile*/) const {
    return TERRAIN_ALL;
}

bool building_abu_simbel::preview::ghost_allow_tile(build_planner& /*p*/, tile2i /*tile*/) const {
    return true;
}

int building_abu_simbel::preview::can_place(build_planner &p, tile2i /*tile*/, tile2i end, int state) const {
    if (state != CAN_PLACE && state != CAN_NOT_BUT_GREEN) {
        return state;
    }
    // OG check_monument_object_site: both warnings when the site does not fit.
    if (!site_fits(end)) {
        p.set_warning("#must_be_over_cliffs");
        p.set_extra_warning("#entrance_on_clear_land");
        return CAN_NOT_PLACE;
    }
    if (building_monument_has_unfinished({BUILDING_ABU_SIMBEL}, true, true)) {
        p.set_warning("#only_one_building_of_this_type");
        return CAN_NOT_PLACE;
    }
    if (state == CAN_NOT_BUT_GREEN) {
        p.set_warning("");
    }
    return CAN_PLACE;
}

void building_abu_simbel::preview::ghost_preview(build_planner& /*planer*/, painter& ctx, tile2i /*start*/, tile2i end,
  vec2i /*pixel*/) const {
    draw_placement(ctx, end);
}

void building_abu_simbel::preview::ghost_blocked(build_planner& /*planer*/, painter& ctx, tile2i /*start*/, tile2i end,
  vec2i /*pixel*/, bool /*fully_blocked*/) const {
    draw_placement(ctx, end);
}

// OG building property size 1: the clicked tile is the layout origin in every view.
int building_abu_simbel::preview::construction_place(build_planner& planer, tile2i /*tile*/, tile2i end,
  int /*orientation*/, int variant) const {
    const abu_simbel_part_cfg* p0 = part_row(0);
    planer.last_created_building = nullptr;
    if (!p0) {
        return 0;
    }
    building* b = building_create(planer.build_type, end.shifted(p0->dx, p0->dy), 0);
    game_undo_add_building(b);
    if (!b || b->id <= 0) {
        return 0;
    }
    add_building(b, 0, variant);
    planer.last_created_building = b;
    return 1;
}

void building_abu_simbel::on_place_update_tiles(int /*orientation*/, int /*variant*/) {
    const auto& params = current_params();
    const abu_simbel_part_cfg* p0 = part_row(0);
    if (!p0) {
        return;
    }
    tile2i origin = tile().shifted(-p0->dx, -p0->dy);

    base.prev_part_building_id = 0;
    base.orientation = 0;
    base.size = part_size(0);
    runtime_data().variant = 0;
    runtime_data().phase = 0;

    building *prev = &base;
    for (int i = 1; i < (int)params.parts.size(); ++i) {
        const abu_simbel_part_cfg& def = params.parts[i];
        building* b = building_create(BUILDING_ABU_SIMBEL, origin.shifted(def.dx, def.dy), 0);
        game_undo_add_building(b);
        b->size = part_size(i);
        b->fire_proof = params.fire_proof;
        b->damage_proof = params.damage_proof;
        if (auto* part = b->dcast_abu_simbel()) {
            part->runtime_data().variant = (uint8_t)i;
            part->runtime_data().phase = 0;
        }
        b->prev_part_building_id = prev->id;
        b->next_part_building_id = 0;
        prev->next_part_building_id = b->id;
        prev = b;
    }

    // OG map_building_tiles_add keeps no rock bits under a building.
    for_each_site_tile(origin, [](tile2i t, bool) { map_terrain_remove(t.grid_offset(), k_monument_rock); });

    auto& d = runtime_data();
    d.workers.fill(0);
    d.spot_work = stage_work(0);
    d.spot_figure = 0;
    refresh_part_images();
}

void building_abu_simbel::on_post_load() {
    building_monument::on_post_load();
    if (!is_main()) {
        return;
    }
    auto& d = runtime_data();
    // Every stage has work at its spot, so none left on an unfinished main record means a save that kept no
    // spot state: the current stage starts over.
    if (d.phase != MONUMENT_FINISHED && d.spot_work == 0) {
        d.phase = (int8_t)std::clamp((int)d.phase, 0, STAGE_COMPLETE - 1);
        d.spot_work = stage_work(stage());
        d.spot_figure = 0;
    }
    refresh_part_images();
}

xstring building_abu_simbel::demolish_blocked_message() const {
    return "#abu_simbel_not_demolishable";
}

// OG remove_tiles_singly: the cliff comes back under every part but the entrance.
void building_abu_simbel::on_destroy() {
    const abu_simbel_part_kind* kind = part_kind();
    const bool rock = !kind || kind->on_rock;
    for (int dy = 0; dy < base.size; ++dy) {
        for (int dx = 0; dx < base.size; ++dx) {
            const tile2i t = tile().shifted(dx, dy);
            if (map_building_at(t) == id()) {
                map_building_tile_clear_at(t.grid_offset(), 0);
            }
            if (rock) {
                map_terrain_add(t.grid_offset(), k_monument_rock);
            }
        }
    }
}

void building_abu_simbel::update_day() {
    building_impl::update_day();
    if (!is_main() || is_finished()) {
        return;
    }
    auto& d = runtime_data();
    if (d.spot_figure && !spot_still_held(d.spot_figure)) {
        d.spot_figure = 0;
    }
    if (!has_active_worker()) {
        d.workers[0] = 0;
    }
}

// Rotation only reaches the main record, so it redraws all parts.
void building_abu_simbel::update_map_orientation(int /*map_orientation*/) {
    main_abu_simbel()->refresh_part_images();
}

grid_area building_abu_simbel::get_area() const {
    const abu_simbel_part_cfg* p0 = part_row(0);
    tile2i main_tile = main_abu_simbel()->tile();
    if (!p0) {
        return {main_tile, main_tile};
    }
    tile2i origin = main_tile.shifted(-p0->dx, -p0->dy);
    int x0 = 0, y0 = 0, x1 = 0, y1 = 0;
    bool first = true;
    for (const auto& p : abu_params().parts) {
        const abu_simbel_part_kind* k = kind_row(p.kind);
        if (!k) {
            continue;
        }
        const int px1 = p.dx + k->size - 1;
        const int py1 = p.dy + k->size - 1;
        x0 = first ? p.dx : std::min(x0, p.dx);
        y0 = first ? p.dy : std::min(y0, p.dy);
        x1 = first ? px1 : std::max(x1, px1);
        y1 = first ? py1 : std::max(y1, py1);
        first = false;
    }
    return {origin.shifted(x0, y0), origin.shifted(x1, y1)};
}

tile2i building_abu_simbel::center_point() const {
    grid_area area = get_area();
    return area.tmin().add(area.tmax()).div(2);
}

// OG abu_simbel_get_work_tile: the staging tile in front of the entrance, also every part's road access.
tile2i building_abu_simbel::access_point() const {
    const vec2i w = abu_params().work_tile;
    return main_abu_simbel()->tile().shifted(w.x, w.y);
}

void building_abu_simbel::bind_dynamic(io_buffer *iob, size_t /*version*/) {
    auto& d = runtime_data();

    // The current stage's spot (work, figure) takes 4 of the 38 bytes older saves wrote as zero.
    iob->bind(BIND_SIGNATURE_UINT16, &d.spot_work);
    iob->bind(BIND_SIGNATURE_UINT16, &d.spot_figure);
    iob->bind____skip(34);
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

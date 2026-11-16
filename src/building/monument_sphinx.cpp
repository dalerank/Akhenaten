#include "monument_sphinx.h"

#include "building/monuments.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_message.h"
#include "construction/build_planner.h"
#include "core/profiler.h"
#include "figure/figure.h"
#include "game/game.h"
#include "game/game_config.h"
#include "game/resource.h"
#include "game/undo.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/view/lookup.h"
#include "graphics/view/view.h"
#include "grid/building_tiles.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "js/js_game.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_sphinx);
BUILDING_RUNTIME_DATA_IMPL(building_sphinx)

namespace {
    enum {
        SPOT_WORK_UNSET = 0xFFFF,
        // OG BUILDING_MAP_EDGE_MARGIN for site buildings.
        MAP_EDGE_MARGIN = 3,
    };

    // Phases 0..15 carve (no deliveries); 16 is the Enhanced painting stage.
    struct monument_sphinx_cfg : public monument {
        monument_sphinx_cfg() : monument{BUILDING_SPHINX} {
            for (uint8_t i = 0; i < building_sphinx::STAGE_PAINTING; ++i) {
                phases.push_back({i, monument_phase_resource{ARCHITECTS, 1}});
            }
            phases.push_back({building_sphinx::STAGE_PAINTING, monument_phase_resource{ARCHITECTS, 1},
              {RESOURCE_PAINT, 400}, {RESOURCE_CLAY, 400}});
        }
    } g_monument_sphinx;

    const building_sphinx::base_params& sphinx_params() {
        return (const building_sphinx::base_params&)building_sphinx::current_params();
    }

    bool artisans_paint_sphinx() {
        return !!game_features::gameplay_sphinx_artisans;
    }

    int camera_view() {
        return (g_camera.orientation / 2) & 3;
    }

    // OG turn_origin_to_view: the clicked tile is the view anchor of the first 6x6 part.
    tile2i origin_from_anchor(tile2i anchor, int view) {
        const int d = building_sphinx::PART_SIZE - 1;
        switch (view) {
        case 1:
            return anchor.shifted(-d, 0);
        case 2:
            return anchor.shifted(-d, -d);
        case 3:
            return anchor.shifted(0, -d);
        default:
            return anchor;
        }
    }

    tile2i anchor_from_origin(tile2i origin, int view) {
        const int d = building_sphinx::PART_SIZE - 1;
        switch (view) {
        case 1:
            return origin.shifted(d, 0);
        case 2:
            return origin.shifted(d, d);
        case 3:
            return origin.shifted(0, d);
        default:
            return origin;
        }
    }

    tile2i part_origin(tile2i origin, int part) {
        return origin.shifted(part * building_sphinx::PART_SIZE, 0);
    }

    int sphinx_part_image(int part, int stage) {
        const int view = camera_view();
        const int letter = building_sphinx::view_part_letter(part, view);
        const int img_index = (view == 0 || view == 2) ? 2 : 1;
        static const char letters[] = {'a', 'b', 'c'};
        bstring32 key;
        key.printf("s%d%c%d", building_sphinx::pack_stage(letter, stage), letters[letter], img_index);
        const auto& params = building_static_params::get(BUILDING_SPHINX);
        const int img = params.first_img(xstring(key.c_str()));
        return img > 0 ? img : params.first_img("preview");
    }

    bool site_tile_blocked(tile2i tile) {
        const auto* map = scenario_map_data();
        if (tile.x() < MAP_EDGE_MARGIN || tile.y() < MAP_EDGE_MARGIN || tile.x() >= map->width - MAP_EDGE_MARGIN
            || tile.y() >= map->height - MAP_EDGE_MARGIN) {
            return true;
        }
        return map_terrain_is(tile, TERRAIN_NOT_CLEAR | TERRAIN_FLOODPLAIN) || map_has_figure_at(tile);
    }

    bool collect_site(tile2i origin, std::array<blocked_tile_vec, building_sphinx::PARTS>& parts) {
        bool blocked = false;
        for (int p = 0; p < building_sphinx::PARTS; ++p) {
            tile2i po = part_origin(origin, p);
            for (int dy = 0; dy < building_sphinx::PART_SIZE; ++dy) {
                for (int dx = 0; dx < building_sphinx::PART_SIZE; ++dx) {
                    const tile2i t = po.shifted(dx, dy);
                    const bool b = site_tile_blocked(t);
                    parts[p].push_back({t, b});
                    blocked |= b;
                }
            }
        }
        return blocked;
    }

    bool site_contains(tile2i origin, tile2i tile) {
        const int dx = tile.x() - origin.x();
        const int dy = tile.y() - origin.y();
        return dx >= 0 && dy >= 0 && dx < building_sphinx::PARTS * building_sphinx::PART_SIZE
               && dy < building_sphinx::PART_SIZE;
    }

    bool figure_still_working(uint16_t fid) {
        if (!fid) {
            return false;
        }
        figure* f = figure_get(fid);
        if (!f || !f->is_alive()) {
            return false;
        }
        building* dest = f->destination();
        return dest && dest->type == BUILDING_SPHINX;
    }

    // Visual-only state of the work-spot animations (one sphinx per city); rebuilt from the attached workers.
    struct spot_anim {
        int8_t sequence = -1;
        int8_t reverse = 0;
        int16_t frame = 0;
        bool active = false;
        uint16_t figure = 0;
    };
    std::array<spot_anim, building_sphinx::PARTS * building_sphinx::SPOTS_PER_PART> g_spot_anims;
    int g_spot_anim_tick = -1;

    const sphinx_anim_script* anim_script(const xstring& name) {
        const auto& scripts = sphinx_params().anim_scripts;
        auto it = scripts.find(name);
        return it != scripts.end() ? &it->second : nullptr;
    }

    bool pick_choice(const sphinx_anim_script& sc, const svector<vec2i, 4>& choices, spot_anim& a) {
        if (choices.empty()) {
            return false;
        }
        const vec2i c = choices[rand() % choices.size()];
        if (c.x < 0 || c.x >= (int)sc.sequences.size()) {
            return false;
        }
        a.sequence = (int8_t)c.x;
        a.reverse = (int8_t)c.y;
        a.frame = c.y ? sc.sequences[c.x].frames : 0;
        return true;
    }

    void start_spot_anim(const xstring& script, spot_anim& a) {
        a.sequence = -1;
        a.active = false;
        const sphinx_anim_script* sc = anim_script(script);
        if (!sc) {
            return;
        }
        static const svector<vec2i, 4> first = {vec2i{0, 0}};
        a.active = pick_choice(*sc, sc->entry.empty() ? first : sc->entry, a);
    }

    void step_spot_anim(const xstring& script, spot_anim& a) {
        const sphinx_anim_script* sc = anim_script(script);
        if (!a.active || !sc) {
            return;
        }
        if (a.sequence < 0 || a.sequence >= (int)sc->sequences.size()) {
            a.active = false;
            return;
        }
        const auto& seq = sc->sequences[a.sequence];
        a.frame += a.reverse ? -1 : 1;
        if (a.frame >= 0 && a.frame <= seq.frames) {
            return;
        }
        if (a.reverse) {
            a.active = pick_choice(*sc, seq.back, a);
        } else if (seq.stop) {
            a.active = false;
        } else if (seq.next.empty()) {
            const svector<vec2i, 4> following = {vec2i{(a.sequence + 1) % (int)sc->sequences.size(), 0}};
            a.active = pick_choice(*sc, following, a);
        } else {
            a.active = pick_choice(*sc, seq.next, a);
        }
    }
} // namespace

void building_sphinx::static_params::archive_load(archive /*arch*/) {
}

const monument& building_sphinx::config() const {
    return g_monument_sphinx;
}

int building_sphinx::pack_stage(int part_letter, int stage) {
    const int s = std::clamp(stage, STAGE_FIRST, STAGE_COMPLETE);
    int pack = 1;
    switch (part_letter) {
    case 0:
        pack = 1 + (s + 1) / 3;
        break;
    case 1:
        pack = 1 + s / 3;
        break;
    default:
        pack = 1 + (s - 1) / 3;
        break;
    }
    return std::clamp(pack, 1, 6);
}

// sphinx_image: in E/S views the end parts swap packs so the paws (C) face the camera.
int building_sphinx::view_part_letter(int part, int view) {
    part = std::clamp(part, 0, PARTS - 1);
    return (view == 1 || view == 2) ? (PARTS - 1 - part) : part;
}

building_sphinx* building_sphinx::main_sphinx() {
    building_impl* m = main();
    auto* s = m ? m->dcast_sphinx() : nullptr;
    return s ? s : this;
}

const building_sphinx* building_sphinx::main_sphinx() const {
    return const_cast<building_sphinx*>(this)->main_sphinx();
}

building_sphinx* building_sphinx::part(int index) {
    building_sphinx* p = main_sphinx();
    for (int i = 0; p && i < index; ++i) {
        p = p->has_next() ? p->next()->dcast_sphinx() : nullptr;
    }
    return p;
}

const building_sphinx* building_sphinx::part(int index) const {
    return const_cast<building_sphinx*>(this)->part(index);
}

int building_sphinx::stage() const {
    const int p = main_sphinx()->runtime_data().phase;
    if (p == MONUMENT_FINISHED || p >= STAGE_COMPLETE) {
        return STAGE_COMPLETE;
    }
    return std::max(p, STAGE_FIRST);
}

int building_sphinx::spot_attached(int spot) const {
    const building_sphinx* p = part(spot / SPOTS_PER_PART);
    return p ? p->runtime_data().spot_figure[spot % SPOTS_PER_PART] : 0;
}

int building_sphinx::spot_work_left(int spot) const {
    const building_sphinx* p = part(spot / SPOTS_PER_PART);
    return p ? p->runtime_data().spot_work[spot % SPOTS_PER_PART] : 0;
}

void building_sphinx::set_spot(int spot, uint16_t work, uint16_t fid) {
    building_sphinx* p = part(spot / SPOTS_PER_PART);
    if (!p) {
        return;
    }
    p->runtime_data().spot_work[spot % SPOTS_PER_PART] = work;
    p->runtime_data().spot_figure[spot % SPOTS_PER_PART] = fid;
}

void building_sphinx::reset_spots() {
    const auto& spots = sphinx_params().spots;
    for (int i = 0; i < PARTS * SPOTS_PER_PART; ++i) {
        const uint16_t work = i < (int)spots.size() ? spots[i].work : 0;
        set_spot(i, work, 0);
    }
}

void building_sphinx::scrub_spots() {
    const auto& spots = sphinx_params().spots;
    for (int i = 0; i < (int)spots.size(); ++i) {
        const int fid = spot_attached(i);
        if (fid && !figure_still_working(fid)) {
            set_spot(i, spot_work_left(i), 0);
        }
    }
}

int building_sphinx::find_free_spot(e_figure_type type) const {
    const auto& spots = sphinx_params().spots;
    const int s = stage();
    for (int i = 0; i < (int)spots.size(); ++i) {
        const auto& def = spots[i];
        if (def.stage != s || def.figure != type || spot_work_left(i) <= 0) {
            continue;
        }
        if (!figure_still_working(spot_attached(i))) {
            return i;
        }
    }
    return -1;
}

bool building_sphinx::has_free_spot(e_figure_type type) const {
    return find_free_spot(type) >= 0;
}

bool building_sphinx::work_tick(figure& f) {
    building_sphinx* m = main_sphinx();
    if (m != this) {
        return m->work_tick(f);
    }
    if (is_carving_done()) {
        return true;
    }

    const auto& spots = sphinx_params().spots;
    const int s = stage();
    int spot = -1;
    for (int i = 0; i < (int)spots.size(); ++i) {
        if (spot_attached(i) == f.id) {
            spot = i;
            break;
        }
    }
    if (spot >= 0 && spots[spot].stage != s) {
        set_spot(spot, spot_work_left(spot), 0);
        return true;
    }
    if (spot < 0) {
        spot = find_free_spot(f.type);
        if (spot < 0) {
            return true;
        }
    }

    const int left = std::max(0, spot_work_left(spot) - 1);
    set_spot(spot, (uint16_t)left, left > 0 ? f.id : 0);
    if (left > 0) {
        return false;
    }

    for (int i = 0; i < (int)spots.size(); ++i) {
        if (spots[i].stage == s && spot_work_left(i) > 0) {
            return true;
        }
    }
    advance_stage();
    return true;
}

void building_sphinx::advance_stage() {
    const int s = stage();
    if (s >= STAGE_COMPLETE) {
        return;
    }

    int next = s + 1;
    if (next >= STAGE_COMPLETE) {
        next = artisans_paint_sphinx() ? STAGE_PAINTING : MONUMENT_FINISHED;
    }
    for (int i = 0; i < PARTS; ++i) {
        if (building_sphinx* p = part(i)) {
            p->set_phase(next);
        }
    }
    refresh_part_images();

    if (next == MONUMENT_FINISHED) {
        messages::popup("sphinx_congratulations", 0, tile().grid_offset());
    }
}

void building_sphinx::set_stage(int target) {
    building_sphinx* m = main_sphinx();
    if (m != this) {
        m->set_stage(target);
        return;
    }
    target = std::clamp(target, STAGE_FIRST, STAGE_COMPLETE);
    int phase = target;
    if (target >= STAGE_COMPLETE) {
        phase = artisans_paint_sphinx() ? STAGE_PAINTING : MONUMENT_FINISHED;
    }
    for (int i = 0; i < PARTS; ++i) {
        if (building_sphinx* p = part(i)) {
            p->set_phase(phase);
        }
    }
    reset_spots();
    const auto& spots = sphinx_params().spots;
    for (int i = 0; i < (int)spots.size(); ++i) {
        if (spots[i].stage < target) {
            set_spot(i, 0, 0);
        }
    }
    refresh_part_images();
}

void building_sphinx::refresh_part_images() {
    for (int i = 0; i < PARTS; ++i) {
        if (building_sphinx* p = part(i)) {
            map_building_tiles_add(p->id(), p->tile(), PART_SIZE, p->building_image_get(), TERRAIN_BUILDING);
        }
    }
}

void building_sphinx::work_percentages(int& carpenter_pct, int& mason_pct) const {
    const auto& spots = sphinx_params().spots;
    const int s = stage();
    int carpenters = 0, carpenters_done = 0, masons = 0, masons_done = 0;
    for (const auto& def : spots) {
        const bool done = def.stage < s;
        if (def.figure == FIGURE_CARPENTER) {
            carpenters++;
            carpenters_done += done ? 1 : 0;
        } else {
            masons++;
            masons_done += done ? 1 : 0;
        }
    }
    carpenter_pct = carpenters ? carpenters_done * 100 / carpenters : 100;
    mason_pct = masons ? masons_done * 100 / masons : 100;
}

bool building_sphinx::needs_resources() const {
    const building_sphinx* m = main_sphinx();
    if (m->runtime_data().phase != STAGE_PAINTING) {
        return false;
    }
    return m->resource_pct(RESOURCE_PAINT) < 100 || m->resource_pct(RESOURCE_CLAY) < 100;
}

bool building_sphinx::need_carpenter() {
    return is_main() && !is_finished() && has_free_spot(FIGURE_CARPENTER);
}

bool building_sphinx::need_stonemason() {
    return is_main() && !is_finished() && has_free_spot(FIGURE_STONEMASON);
}

bool building_sphinx::need_artisan() {
    if (!is_main() || !artisans_paint_sphinx() || runtime_data().phase != STAGE_PAINTING) {
        return false;
    }
    return needs_resources() && has_free_worker_slot();
}

bool building_sphinx::need_workers() const {
    return false;
}

void building_sphinx::add_workers(figure_id fid) {
    building_sphinx* m = main_sphinx();
    auto& workers = m->runtime_data().workers;
    if (std::find(workers.begin(), workers.end(), fid) != workers.end()) {
        return;
    }
    for (auto& wid : workers) {
        if (wid == 0) {
            wid = fid;
            return;
        }
    }
}

void building_sphinx::remove_worker(figure_id fid) {
    for (auto& wid : main_sphinx()->runtime_data().workers) {
        if (wid == fid) {
            wid = 0;
        }
    }
}

int building_sphinx::building_image_get() const {
    return sphinx_part_image(part_index(), stage());
}

void building_sphinx::preview::setup_preview_graphics(build_planner& planer) const {
    // Footprint is 18 tiles along map x; planner columns follow the camera.
    const int along = PARTS * PART_SIZE;
    if (camera_view() % 2 == 0) {
        planer.init_tiles(along, PART_SIZE);
    } else {
        planer.init_tiles(PART_SIZE, along);
    }
}

void building_sphinx::preview::ghost_preview(build_planner& planer, painter& ctx, tile2i /*start*/, tile2i end,
  vec2i pixel) const {
    const int view = camera_view();
    const tile2i origin = origin_from_anchor(end, view);

    std::array<blocked_tile_vec, PARTS> parts;
    const bool blocked = collect_site(origin, parts) || g_city.buildings.count_total(BUILDING_SPHINX) > 0;
    if (blocked) {
        const bool all_red = g_city.buildings.count_total(BUILDING_SPHINX) > 0;
        for (const auto& p : parts) {
            planer.draw_partially_blocked(ctx, all_red, p);
        }
        return;
    }

    for (int p = 0; p < PARTS; ++p) {
        const tile2i anchor = anchor_from_origin(part_origin(origin, p), view);
        const vec2i px = (p == 0) ? pixel : g_camera.lookup_tile_to_pixel(anchor);
        planer.draw_building_ghost(ctx, sphinx_part_image(p, STAGE_FIRST), px);
    }
}

void building_sphinx::preview::ghost_blocked(build_planner& planer, painter& ctx, tile2i /*start*/, tile2i end,
  vec2i /*pixel*/, bool fully_blocked) const {
    std::array<blocked_tile_vec, PARTS> parts;
    collect_site(origin_from_anchor(end, camera_view()), parts);
    for (const auto& p : parts) {
        planer.draw_partially_blocked(ctx, fully_blocked, p);
    }
}

bool building_sphinx::preview::ghost_allow_tile(build_planner& planer, tile2i tile) const {
    if (!site_contains(origin_from_anchor(planer.end, camera_view()), tile)) {
        return true;
    }
    return !site_tile_blocked(tile);
}

uint32_t building_sphinx::preview::ghost_ignore_terrain(build_planner& planer, tile2i tile) const {
    if (!site_contains(origin_from_anchor(planer.end, camera_view()), tile)) {
        return TERRAIN_NOT_CLEAR;
    }
    return 0;
}

int building_sphinx::preview::can_place(build_planner& planer, tile2i /*start*/, tile2i end, int state) const {
    if (state != CAN_PLACE && state != CAN_NOT_BUT_GREEN) {
        return state;
    }
    if (g_city.buildings.count_total(BUILDING_SPHINX) > 0) {
        planer.set_warning("#only_one_building_of_this_type");
        return CAN_NOT_PLACE;
    }
    std::array<blocked_tile_vec, PARTS> parts;
    if (collect_site(origin_from_anchor(end, camera_view()), parts)) {
        planer.set_warning("#must_build_on_cleared_land");
        return CAN_NOT_PLACE;
    }
    if (state == CAN_NOT_BUT_GREEN) {
        planer.set_warning("");
    }
    return CAN_PLACE;
}

void building_sphinx::on_place_update_tiles(int orientation, int /*variant*/) {
    base.prev_part_building_id = 0;
    base.orientation = orientation;
    runtime_data().variant = 0;
    runtime_data().phase = STAGE_FIRST;

    building* prev = &base;
    for (int p = 1; p < PARTS; ++p) {
        building* b = building_create(BUILDING_SPHINX, part_origin(tile(), p), 0);
        game_undo_add_building(b);
        if (auto* sp = b->dcast_sphinx()) {
            sp->runtime_data().variant = (uint8_t)p;
            sp->runtime_data().phase = STAGE_FIRST;
        }
        b->prev_part_building_id = prev->id;
        b->next_part_building_id = 0;
        prev->next_part_building_id = b->id;
        prev = b;
    }

    reset_spots();
    refresh_part_images();
}

void building_sphinx::on_post_load() {
    building_monument::on_post_load();
    if (!is_main()) {
        return;
    }

    bool unset = false;
    for (int i = 0; i < PARTS * SPOTS_PER_PART; ++i) {
        unset |= spot_work_left(i) == SPOT_WORK_UNSET;
    }
    if (unset) {
        // Saves before v193 have no spot state: spots of past stages are done, the rest start over.
        auto& d = runtime_data();
        if (d.phase != MONUMENT_FINISHED) {
            d.phase = (int8_t)std::clamp((int)d.phase, STAGE_FIRST, STAGE_COMPLETE - 1);
        }
        reset_spots();
        const auto& spots = sphinx_params().spots;
        for (int i = 0; i < (int)spots.size(); ++i) {
            if (spots[i].stage < stage()) {
                set_spot(i, 0, 0);
            }
        }
    }
    refresh_part_images();
}

void building_sphinx::update_day() {
    building_impl::update_day();
    if (!is_main() || is_finished()) {
        return;
    }
    scrub_spots();

    if (runtime_data().phase == STAGE_PAINTING && !needs_resources()) {
        for (int i = 0; i < PARTS; ++i) {
            if (building_sphinx* p = part(i)) {
                p->set_phase(MONUMENT_FINISHED);
            }
        }
        refresh_part_images();
        messages::popup("sphinx_congratulations", 0, tile().grid_offset());
    }
}

// Rotation only reaches the main record (map_orientation_update_buildings), so it redraws all parts.
void building_sphinx::update_map_orientation(int /*map_orientation*/) {
    main_sphinx()->refresh_part_images();
}

void building_sphinx::animate_spots() {
    const int now = game.simtime.absolute_tick();
    int steps = (g_spot_anim_tick < 0) ? 1 : std::clamp(now - g_spot_anim_tick, 0, 64);
    g_spot_anim_tick = now;

    const auto& spots = sphinx_params().spots;
    for (int i = 0; i < (int)spots.size() && i < (int)g_spot_anims.size(); ++i) {
        auto& a = g_spot_anims[i];
        const int fid = spot_attached(i);
        if (!fid) {
            a.active = false;
            a.figure = 0;
            continue;
        }
        if (a.figure != fid) {
            a.figure = (uint16_t)fid;
            start_spot_anim(spots[i].script, a);
        }
        for (int k = 0; k < steps; ++k) {
            step_spot_anim(spots[i].script, a);
        }
    }
}

// OG sphinx_draw_spots: drawn once, from the part that shows the paws (pack C) to the camera.
bool building_sphinx::draw_ornaments_and_animations_height(painter& ctx, vec2i point, tile2i, color color_mask) {
    if (is_finished() || view_part_letter(part_index(), camera_view()) != 2) {
        return false;
    }
    building_sphinx* m = main_sphinx();
    m->animate_spots();

    const int view = camera_view();
    const auto& spots = sphinx_params().spots;
    bool drew = false;

    // Workers stand over all three parts, so sort after the screen-lowest corner of the whole
    // 18x6 footprint (OG drew them right after the parts, before anything in front).
    {
        tile2i origin = m->tile();
        int max_y = point.y;
        for (const vec2i corner : {vec2i{0, 0}, vec2i{PARTS * PART_SIZE - 1, 0}, vec2i{0, PART_SIZE - 1},
               vec2i{PARTS * PART_SIZE - 1, PART_SIZE - 1}}) {
            max_y = std::max(max_y, g_camera.lookup_tile_to_pixel(origin.shifted(corner.x, corner.y)).y);
        }
        auto& anchor = ImageDraw::create_command(ctx, render_command_t::ert_none);
        anchor.pixel = point;
        anchor.use_sort_pixel = true;
        anchor.sort_pixel = vec2i{point.x, max_y};
    }
    for (int i = 0; i < (int)spots.size() && i < (int)g_spot_anims.size(); ++i) {
        const auto& a = g_spot_anims[i];
        const sphinx_anim_script* sc = anim_script(spots[i].script);
        if (!a.active || !sc || a.sequence < 0 || a.sequence >= (int)sc->sequences.size()) {
            continue;
        }
        const auto& seq = sc->sequences[a.sequence];
        const auto& images = sphinx_params().worker_images;
        auto img_it = images.find(seq.anim);
        if (img_it == images.end() || seq.frames <= 0) {
            continue;
        }
        const auto& img = img_it->second;
        const int base_img = image_id_from_group(img.pack, img.id);
        if (base_img <= 0) {
            continue;
        }
        const bool mirror = (view == 1 || view == 3) && !sc->unmirrored;
        const auto view_point = [mirror](vec2i p) { return mirror ? vec2i{-p.x, p.y} : p; };
        const vec2i from = view_point(seq.from);
        const vec2i to = view_point(seq.to);
        const vec2i offset = sphinx_params().anim_offset;
        const int x = (to.x - from.x) * a.frame / seq.frames + offset.x + from.x;
        const int y = (to.y - from.y) * a.frame / seq.frames + offset.y + from.y;

        const int image_id = base_img + img.offset + (a.frame % std::max<int>(1, img.frames)) * img.step;
        const image_t* image = image_get(image_id);
        if (!image) {
            continue;
        }
        auto& command = ImageDraw::create_subcommand(ctx, render_command_t::ert_generic);
        command.image_id = image_id;
        command.pixel = point + vec2i{x, y} - image->animation.sprite_offset;
        command.mask = color_mask;
        drew = true;
    }
    return drew;
}

grid_area building_sphinx::get_area() const {
    tile2i start = main_sphinx()->tile();
    return {start, start.shifted(PARTS * PART_SIZE - 1, PART_SIZE - 1)};
}

tile2i building_sphinx::center_point() const {
    grid_area area = get_area();
    return area.tmin().add(area.tmax()).div(2);
}

// OG road access of the sphinx: the tile just below the middle part.
tile2i building_sphinx::access_point() const {
    tile2i t = main_sphinx()->tile();
    return t.shifted(PART_SIZE + 3, PART_SIZE);
}

void building_sphinx::bind_dynamic(io_buffer* iob, size_t version) {
    auto& d = runtime_data();

    // v193+: the 8 spots of this part (work, figure) take 32 of the formerly skipped 38 bytes.
    if (version > 192) {
        for (int i = 0; i < SPOTS_PER_PART; i++) {
            iob->bind(BIND_SIGNATURE_UINT16, &d.spot_work[i]);
            iob->bind(BIND_SIGNATURE_UINT16, &d.spot_figure[i]);
        }
        iob->bind____skip(6);
    } else {
        iob->bind____skip(38);
        d.spot_work.fill(SPOT_WORK_UNSET);
        d.spot_figure.fill(0);
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
}

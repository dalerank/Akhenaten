#include "monument_sun_temple.h"

#include "building/monuments.h"
#include "building/rotation.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_message.h"
#include "city/city_resource.h"
#include "city/city_warnings.h"
#include "construction/build_planner.h"
#include "figure/figure.h"
#include "figuretype/figure_stonemason.h"
#include "figuretype/figure_carpenter.h"
#include "figuretype/figure_worker.h"
#include "game/game.h"
#include "game/game_events.h"
#include "game/resource.h"
#include "game/undo.h"
#include "graphics/color.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
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

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_sun_temple);
BUILDING_RUNTIME_DATA_IMPL(building_sun_temple)

const e_sun_temple_part_kind_tokens_t ANK_CONFIG_ENUM(e_sun_temple_part_kind_tokens);

static monument g_monument_sun_temple{BUILDING_SUN_TEMPLE};

namespace {

const building_sun_temple::base_params &st_params() {
    return (const building_sun_temple::base_params &)building_sun_temple::current_params();
}

// OG keeps one sun-temple work-spot table for the city (runtime_data is too small for 13×2).
class sun_temple_spots {
public:
    int attached(int spot) const {
        return valid(spot) ? figure_[spot] : 0;
    }

    int work_left(int spot) const {
        return valid(spot) ? work_[spot] : 0;
    }

    void set(int spot, uint16_t work, uint16_t fid) {
        if (!valid(spot)) {
            return;
        }
        work_[spot] = work;
        figure_[spot] = fid;
    }

    void reset(const svector<sun_temple_spot_def, SUN_TEMPLE_WORK_SPOTS> &defs) {
        for (int i = 0; i < SUN_TEMPLE_WORK_SPOTS; ++i) {
            work_[i] = i < (int)defs.size() ? defs[i].work : 0;
            figure_[i] = 0;
        }
    }

    void mark_unset() {
        work_.fill(SUN_TEMPLE_SPOT_WORK_UNSET);
        figure_.fill(0);
    }

    void clear_figures() {
        figure_.fill(0);
    }

    bool any_unset() const {
        for (uint16_t w : work_) {
            if (w == SUN_TEMPLE_SPOT_WORK_UNSET) {
                return true;
            }
        }
        return false;
    }

    void bind(io_buffer *iob, bool with_figures) {
        for (int i = 0; i < SUN_TEMPLE_WORK_SPOTS; i++) {
            iob->bind(BIND_SIGNATURE_UINT16, &work_[i]);
        }
        if (with_figures) {
            for (int i = 0; i < SUN_TEMPLE_WORK_SPOTS; i++) {
                iob->bind(BIND_SIGNATURE_UINT16, &figure_[i]);
            }
        }
    }

private:
    static bool valid(int spot) {
        return spot >= 0 && spot < SUN_TEMPLE_WORK_SPOTS;
    }

    std::array<uint16_t, SUN_TEMPLE_WORK_SPOTS> work_{};
    std::array<uint16_t, SUN_TEMPLE_WORK_SPOTS> figure_{};
};

sun_temple_spots &work_spots() {
    static sun_temple_spots state;
    return state;
}

struct spot_anim {
    int8_t sequence = -1;
    int8_t reverse = 0;
    int16_t frame = 0;
    bool active = false;
    uint16_t figure = 0;
};

std::array<spot_anim, SUN_TEMPLE_WORK_SPOTS> g_spot_anims{};
int g_spot_anim_tick = -1;

const sun_temple_anim_script *anim_script(const xstring &name) {
    const auto &scripts = st_params().anim_scripts;
    auto it = scripts.find(name);
    return it != scripts.end() ? &it->second : nullptr;
}

// OG transitions are 4 view slots (N/E/S/W). x=-1 means no choice for that view.
bool pick_choice(const sun_temple_anim_script &sc, const svector<vec2i, 4> &choices, int view, spot_anim &a) {
    if (choices.empty()) {
        return false;
    }
    const int idx = std::clamp(view, 0, (int)choices.size() - 1);
    vec2i c = choices[idx];
    if (c.x < 0) {
        for (const vec2i &alt : choices) {
            if (alt.x >= 0) {
                c = alt;
                break;
            }
        }
    }
    if (c.x < 0 || c.x >= (int)sc.sequences.size()) {
        return false;
    }
    a.sequence = (int8_t)c.x;
    a.reverse = (int8_t)c.y;
    a.frame = c.y ? sc.sequences[c.x].frames : 0;
    return true;
}

void start_spot_anim(const xstring &script, int view, spot_anim &a) {
    a.sequence = -1;
    a.active = false;
    const sun_temple_anim_script *sc = anim_script(script);
    if (!sc) {
        return;
    }
    static const svector<vec2i, 4> first = {vec2i{0, 0}, vec2i{-1, 0}, vec2i{-1, 0}, vec2i{-1, 0}};
    a.active = pick_choice(*sc, sc->entry.empty() ? first : sc->entry, view, a);
}

void step_spot_anim(const xstring &script, int view, spot_anim &a) {
    const sun_temple_anim_script *sc = anim_script(script);
    if (!a.active || !sc) {
        return;
    }
    if (a.sequence < 0 || a.sequence >= (int)sc->sequences.size()) {
        a.active = false;
        return;
    }
    const auto &seq = sc->sequences[a.sequence];
    a.frame += a.reverse ? -1 : 1;
    if (a.frame >= 0 && a.frame <= seq.frames) {
        return;
    }
    if (a.reverse) {
        a.active = pick_choice(*sc, seq.back, view, a);
    } else if (seq.stop) {
        a.active = false;
    } else if (seq.next.empty()) {
        const svector<vec2i, 4> following
          = {vec2i{(a.sequence + 1) % (int)sc->sequences.size(), 0}, vec2i{-1, 0}, vec2i{-1, 0}, vec2i{-1, 0}};
        a.active = pick_choice(*sc, following, view, a);
    } else {
        a.active = pick_choice(*sc, seq.next, view, a);
    }
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

bool figure_still_working(int fid) {
    figure *f = figure_get(fid);
    return f && f->is_alive();
}

// Bounding box of all part offsets relative to placement origin.
void footprint_bounds(int &min_x, int &min_y, int &max_x, int &max_y) {
    min_x = min_y = 0x7fffffff;
    max_x = max_y = -0x7fffffff;
    const int n = building_sun_temple::parts_count();
    for (int i = 0; i < n; ++i) {
        const auto &d = building_sun_temple::part_desc(i);
        min_x = std::min(min_x, d.offset.x);
        min_y = std::min(min_y, d.offset.y);
        max_x = std::max(max_x, d.offset.x + d.size - 1);
        max_y = std::max(max_y, d.offset.y + d.size - 1);
    }
}

} // namespace

void building_sun_temple::static_params::archive_load(archive /*arch*/) {
    // Guild demand is driven by spots / part kinds. Keep 0..13 so set_phase(n)
    // for main-temple stages is not collapsed to MONUMENT_FINISHED (phases()==n).
    g_monument_sun_temple.btype = BUILDING_SUN_TEMPLE;
    g_monument_sun_temple.phases.clear();
    for (uint8_t i = 0; i <= SUN_TEMPLE_STAGE_COMPLETE; ++i) {
        g_monument_sun_temple.phases.push_back({i, monument_phase_resource{RESOURCE_NONE, 0}});
    }
}

const monument &building_sun_temple::config() const {
    return g_monument_sun_temple;
}

int building_sun_temple::placement_amount(e_resource r) const {
    for (const auto &pr : current_params().placement_resources) {
        if (pr.resource == r) {
            return pr.count;
        }
    }
    return 0;
}

int building_sun_temple::yards_available(e_resource r) {
    return g_city.resource.yards_stored_staffed(r);
}

bool building_sun_temple::has_completed_sun_temple() {
    // OG sun_temple_any_completed: percent == 100 blocks a new one.
    for (building &b : city_buildings()) {
        if (!b.is_valid() || b.type != BUILDING_SUN_TEMPLE || !b.is_main()) {
            continue;
        }
        auto *st = b.dcast_sun_temple();
        if (st && (st->is_finished() || st->get_progress(nullptr) >= 100)) {
            return true;
        }
    }
    return false;
}

bool building_sun_temple::area_for_part_free(tile2i origin, const sun_temple_part_desc &desc) {
    return !area_blocked(origin.shifted(desc.offset.x, desc.offset.y), desc.size, desc.size);
}

int building_sun_temple::parts_count() {
    const int n = (int)current_params().parts.size();
    return n > 0 ? n : 0;
}

const sun_temple_part_desc &building_sun_temple::part_desc(int index) {
    const auto &parts = current_params().parts;
    static const sun_temple_part_desc empty{};
    if (index < 0 || index >= (int)parts.size()) {
        return empty;
    }
    return parts[index];
}

building_sun_temple *building_sun_temple::main_sun_temple() {
    return base.main()->dcast_sun_temple();
}

const building_sun_temple *building_sun_temple::main_sun_temple() const {
    return base.main()->dcast_sun_temple();
}

building_sun_temple *building_sun_temple::part(int index) {
    building_sun_temple *m = main_sun_temple();
    if (!m) {
        return nullptr;
    }
    if (index <= 0) {
        return m;
    }
    building *p = &m->base;
    for (int i = 0; i < index && p; ++i) {
        p = p->has_next() ? p->next() : nullptr;
    }
    return p ? p->dcast_sun_temple() : nullptr;
}

const building_sun_temple *building_sun_temple::part(int index) const {
    return const_cast<building_sun_temple *>(this)->part(index);
}

e_sun_temple_part_kind building_sun_temple::part_kind() const {
    return part_desc(part_index()).kind;
}

int building_sun_temple::part_stage() const {
    const int p = runtime_data().phase;
    if (p == MONUMENT_FINISHED) {
        return SUN_TEMPLE_STAGE_COMPLETE;
    }
    return std::max(0, (int)p);
}

uint8_t building_sun_temple::work_flags() const {
    return main_sun_temple()->runtime_data().work_flags;
}

figure_id building_sun_temple::worker_figure_id() const {
    return runtime_data().og_part.worker_figure_id;
}

void building_sun_temple::set_worker_figure(figure_id fid) {
    runtime_data().og_part.worker_figure_id = fid;
}

void building_sun_temple::clear_worker_figure() {
    runtime_data().og_part.worker_figure_id = 0;
}

bool building_sun_temple::part_has_active_worker() const {
    const figure_id wid = worker_figure_id();
    if (!wid) {
        return false;
    }
    figure *f = figure_get(wid);
    if (!f || !f->is_alive()) {
        const_cast<building_sun_temple *>(this)->clear_worker_figure();
        return false;
    }

    const int action = f->action_state;
    switch (f->type) {
    case FIGURE_CARPENTER:
        return action == ACTION_1_CARPENTER_GO_TO_SITE || action == ACTION_2_CARPENTER_WORK;
    case FIGURE_STONEMASON:
        return action == ACTION_1_MASON_GOING || action == ACTION_9_MASON_WORK_OBELISK
            || action == ACTION_19_MASON_WAIT_FOR_BLOCK;
    case FIGURE_LABORER:
        return action == ACTION_15_LABORER_TO_STORAGE_YARD || action == ACTION_16_LABORER_AT_STORAGE_YARD
            || action == ACTION_23_LABORER_SLED_TO_SUN_TEMPLE || action == ACTION_24_LABORER_TO_SUN_TEMPLE
            || action == ACTION_25_LABORER_SUN_TEMPLE_WORK;
    default:
        break;
    }
    const_cast<building_sun_temple *>(this)->clear_worker_figure();
    return false;
}

void building_sun_temple::send_to_part(figure &f) const {
    tile2i road = base.road_access;
    if (!road.valid()) {
        road = tile();
    }
    f.destination_tile = road;
    f.destination_building_id = id();
    f.roam_length = 0;
}

int building_sun_temple::spot_attached(int spot) const {
    return work_spots().attached(spot);
}

int building_sun_temple::spot_work_left(int spot) const {
    return work_spots().work_left(spot);
}

void building_sun_temple::set_spot(int spot, uint16_t work, uint16_t fid) {
    work_spots().set(spot, work, fid);
}

void building_sun_temple::reset_spots() {
    work_spots().reset(st_params().spots);
    g_spot_anims = {};
    g_spot_anim_tick = -1;
}

void building_sun_temple::scrub_spots() {
    const auto &spots = st_params().spots;
    for (int i = 0; i < (int)spots.size() && i < SUN_TEMPLE_WORK_SPOTS; ++i) {
        const int fid = spot_attached(i);
        if (fid && !figure_still_working(fid)) {
            set_spot(i, (uint16_t)spot_work_left(i), 0);
        }
    }
}

int building_sun_temple::find_free_spot(e_figure_type type) const {
    const auto &spots = st_params().spots;
    const int s = main_sun_temple()->part_stage();
    for (int i = 0; i < (int)spots.size() && i < SUN_TEMPLE_WORK_SPOTS; ++i) {
        const auto &def = spots[i];
        if (def.stage != s || def.figure != type || spot_work_left(i) <= 0) {
            continue;
        }
        if (!figure_still_working(spot_attached(i))) {
            return i;
        }
    }
    return -1;
}

bool building_sun_temple::has_free_spot(e_figure_type type) const {
    return find_free_spot(type) >= 0;
}

void building_sun_temple::advance_main_stage() {
    building_sun_temple *m = main_sun_temple();
    if (!m || m->is_finished()) {
        return;
    }
    int stage = m->part_stage();
    if (stage < SUN_TEMPLE_STAGE_COMPLETE) {
        stage++;
        m->set_phase(stage);
        if (stage == SUN_TEMPLE_STAGE_COMPLETE) {
            m->runtime_data().work_flags |= SUN_TEMPLE_TEMPLE_DONE;
        }
        m->update_part_image();
    }
}

bool building_sun_temple::work_tick(figure &f) {
    const int kind = part_kind();
    if (kind == SUN_TEMPLE_PART_TEMPLE) {
        building_sun_temple *m = main_sun_temple();
        if (m != this) {
            return m->work_tick(f);
        }
        if (is_finished() || part_stage() >= SUN_TEMPLE_STAGE_COMPLETE) {
            return true;
        }
        const auto &spots = st_params().spots;
        const int s = part_stage();
        int spot = -1;
        for (int i = 0; i < (int)spots.size() && i < SUN_TEMPLE_WORK_SPOTS; ++i) {
            if (spot_attached(i) == f.id) {
                spot = i;
                break;
            }
        }
        if (spot >= 0 && spots[spot].stage != s) {
            set_spot(spot, (uint16_t)spot_work_left(spot), 0);
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
        for (int i = 0; i < (int)spots.size() && i < SUN_TEMPLE_WORK_SPOTS; ++i) {
            if (spots[i].stage == s && spot_work_left(i) > 0) {
                return true;
            }
        }
        advance_main_stage();
        return true;
    }

    // Side parts: 50-tick laborer/mason work advances the part stage.
    if (kind >= SUN_TEMPLE_PART_KIND_MAX) {
        return true;
    }
    if (kind == SUN_TEMPLE_PART_FORECOURT && f.wait_ticks < 0) {
        f.wait_ticks = 0;
    }
    f.wait_ticks++;
    if (f.wait_ticks < SUN_TEMPLE_LABORER_WORK_TICKS) {
        return false;
    }

    set_phase(part_stage() + 1);
    update_part_image();
    apply_part_flags_after_work();
    clear_worker_figure();
    return true;
}

void building_sun_temple::apply_part_flags_after_work() {
    building_sun_temple *main = main_sun_temple();
    if (!main) {
        return;
    }
    const int kind = part_kind();
    const int stage = part_stage();
    auto &flags = main->runtime_data().work_flags;

    if (kind == SUN_TEMPLE_PART_FORECOURT) {
        if (stage == SUN_TEMPLE_PART_DONE) {
            flags |= SUN_TEMPLE_FORECOURT_DONE;
        }
    } else if (kind >= SUN_TEMPLE_PART_ENCLOSURE_CORNER_SW && kind <= SUN_TEMPLE_PART_ENCLOSURE_EDGE) {
        if (stage == SUN_TEMPLE_PART_DONE) {
            bool all = true;
            for (int i = 0; i < parts_count(); ++i) {
                const int k = part_desc(i).kind;
                if (k >= SUN_TEMPLE_PART_ENCLOSURE_CORNER_SW && k <= SUN_TEMPLE_PART_ENCLOSURE_EDGE) {
                    auto *p = part(i);
                    if (!p || p->part_stage() < SUN_TEMPLE_PART_DONE) {
                        all = false;
                        break;
                    }
                }
            }
            if (all) {
                flags |= SUN_TEMPLE_ENCLOSURE_DONE;
            }
        }
    } else if (kind >= SUN_TEMPLE_PART_COURTYARD && kind <= SUN_TEMPLE_PART_COURTYARD_COLUMN) {
        bool all_started = true;
        bool all_done = true;
        for (int i = 0; i < parts_count(); ++i) {
            const int k = part_desc(i).kind;
            if (k < SUN_TEMPLE_PART_COURTYARD || k > SUN_TEMPLE_PART_COURTYARD_COLUMN) {
                continue;
            }
            auto *p = part(i);
            const int st = p ? p->part_stage() : 0;
            if (st == 0) {
                all_started = false;
            }
            if (st < SUN_TEMPLE_PART_DONE) {
                all_done = false;
            }
        }
        if (all_started) {
            flags |= SUN_TEMPLE_COURTYARD_STARTED;
        }
        if (all_done) {
            flags |= SUN_TEMPLE_COURTYARD_DONE;
        }
    } else if (kind == SUN_TEMPLE_PART_HALL && stage == SUN_TEMPLE_LAST_PART_DONE) {
        flags |= SUN_TEMPLE_HALL_DONE;
    }
}

int building_sun_temple::assign_laborer(figure_id fid, bool assign) {
    figure *f = figure_get(fid);
    if (!f || part_stage() != 0 || f->type != FIGURE_LABORER || part_has_active_worker()) {
        return 0;
    }
    if (assign) {
        f->action_state = ACTION_24_LABORER_TO_SUN_TEMPLE;
        set_worker_figure(fid);
        send_to_part(*f);
        f->destination_building_id = id();
    }
    return 1;
}

int building_sun_temple::assign_material(figure_id fid, bool assign, e_terrain_usage terrain) {
    figure *f = figure_get(fid);
    if (!f) {
        return 0;
    }

    if (f->type != FIGURE_LABORER) {
        if (part_has_active_worker() || f->type != FIGURE_STONEMASON) {
            return 0;
        }
        if (assign) {
            f->action_state = ACTION_1_MASON_GOING;
            set_worker_figure(fid);
            send_to_part(*f);
            f->destination_building_id = id();
        }
        return 1;
    }

    if (!part_has_active_worker()) {
        return 0;
    }
    const figure_id mason_id = worker_figure_id();
    figure *mason = figure_get(mason_id);
    if (!mason) {
        return 0;
    }

    const figure_id partner_id = mason->leading_figure_id;
    if (partner_id) {
        figure *partner = figure_get(partner_id);
        if (partner && partner->is_alive() && partner->type == FIGURE_LABORER) {
            const int action = partner->action_state;
            if ((action == ACTION_15_LABORER_TO_STORAGE_YARD || action == ACTION_16_LABORER_AT_STORAGE_YARD
                    || action == ACTION_23_LABORER_SLED_TO_SUN_TEMPLE)
                && partner->leading_figure_id == mason_id) {
                return 0;
            }
        }
        mason->leading_figure_id = 0;
    }
    if (!assign) {
        return 1;
    }

    tile2i yard_tile;
    building_id storage_id = 0;
    // Prefer staffed yards with sandstone; kill the laborer if none (OG).
    for (building &b : city_buildings()) {
        if (!b.is_valid() || b.type != BUILDING_STORAGE_YARD) {
            continue;
        }
        if (b.stored_amount(RESOURCE_SANDSTONE) < 1) {
            continue;
        }
        storage_id = b.id;
        yard_tile = b.road_access.valid() ? b.road_access : b.tile;
        break;
    }
    if (!storage_id) {
        f->poof();
        return 1;
    }

    f->collecting_item_id = RESOURCE_SANDSTONE;
    f->resource_amount_full = 0;
    f->destination_building_id = storage_id;
    f->leading_figure_id = mason_id;
    f->action_state = ACTION_15_LABORER_TO_STORAGE_YARD;
    f->wait_ticks = 0;
    f->destination_tile = yard_tile;
    if (terrain != TERRAIN_USAGE_ROADS) {
        f->terrain_usage = (uint8_t)terrain;
    }
    if (auto *worker = f->dcast_worker()) {
        worker->runtime_data().mason_fid = mason_id;
        worker->runtime_data().yard_bid = storage_id;
    }
    mason->leading_figure_id = fid;
    return 1;
}

bool building_sun_temple::check_work_for_figure(figure_id fid, bool assign) {
    figure *f = figure_get(fid);
    if (!f) {
        return false;
    }
    const uint32_t flags = work_flags();
    const bool is_laborer = f->type == FIGURE_LABORER;
    const int stage = part_stage();
    const int kind = part_kind();

    switch (kind) {
    case SUN_TEMPLE_PART_TEMPLE:
        if (part_has_active_worker() || !has_free_spot(f->type)) {
            return false;
        }
        if (assign) {
            if (f->type == FIGURE_CARPENTER) {
                f->action_state = ACTION_2_CARPENTER_WORK;
            } else if (f->type == FIGURE_STONEMASON) {
                f->action_state = ACTION_9_MASON_WORK_OBELISK;
            } else {
                return false;
            }
            set_worker_figure(fid);
            send_to_part(*f);
            f->destination_building_id = id();
            f->wait_ticks = 0;
        }
        return true;
    case SUN_TEMPLE_PART_FORECOURT:
    case SUN_TEMPLE_PART_ENCLOSURE_CORNER_SW:
    case SUN_TEMPLE_PART_ENCLOSURE_CORNER_SE:
    case SUN_TEMPLE_PART_ENCLOSURE_CORNER_NE:
    case SUN_TEMPLE_PART_ENCLOSURE_CORNER_NW:
    case SUN_TEMPLE_PART_ENCLOSURE_SIDE:
    case SUN_TEMPLE_PART_ENCLOSURE_EDGE: {
        const uint32_t unlock = (kind == SUN_TEMPLE_PART_FORECOURT) ? SUN_TEMPLE_TEMPLE_DONE : SUN_TEMPLE_FORECOURT_DONE;
        if (!(flags & unlock) || stage == 0) {
            return is_laborer ? assign_laborer(fid, assign) != 0 : false;
        }
        if (stage != SUN_TEMPLE_PART_STARTED) {
            return false;
        }
        return assign_material(fid, assign, TERRAIN_USAGE_ANY) != 0;
    }
    case SUN_TEMPLE_PART_COURTYARD:
    case SUN_TEMPLE_PART_PATH:
    case SUN_TEMPLE_PART_COURTYARD_PILLAR:
    case SUN_TEMPLE_PART_COURTYARD_COLUMN:
        if (!is_laborer || part_has_active_worker()) {
            return false;
        }
        if (!(flags & SUN_TEMPLE_COURTYARD_STARTED)) {
            if (stage != 0) {
                return false;
            }
        } else if (!(flags & SUN_TEMPLE_TEMPLE_DONE) || stage != 1) {
            return false;
        }
        if (assign) {
            f->action_state = ACTION_24_LABORER_TO_SUN_TEMPLE;
            set_worker_figure(fid);
            send_to_part(*f);
            f->destination_building_id = id();
        }
        return true;
    case SUN_TEMPLE_PART_HALL:
        if (!(flags & SUN_TEMPLE_COURTYARD_DONE) || !(flags & SUN_TEMPLE_ENCLOSURE_DONE) || stage == 0) {
            return is_laborer ? assign_laborer(fid, assign) != 0 : false;
        }
        if (stage < 1 || stage > 3) {
            return false;
        }
        return assign_material(fid, assign, TERRAIN_USAGE_PREFER_ROADS) != 0;
    default:
        return false;
    }
}

int building_sun_temple::find_work_for_figure(figure_id fid) {
    for (building &b : city_buildings()) {
        if (!b.is_valid() || b.type != BUILDING_SUN_TEMPLE) {
            continue;
        }
        auto *st = b.dcast_sun_temple();
        if (st && st->check_work_for_figure(fid, true)) {
            return b.id;
        }
    }
    return 0;
}

int building_sun_temple::get_progress(int *out) const {
    const building_sun_temple *main = main_sun_temple();
    if (!main) {
        return 0;
    }
    const auto &params = st_params();
    const int material_total = params.material_total;
    const int material_per_load = params.material_per_load;
    const int work_units = std::max(1, (int)params.work_units);
    if (main->is_finished()) {
        if (out) {
            for (int i = 0; i < SUN_TEMPLE_PROGRESS_SLOTS; ++i) {
                out[i] = 0;
            }
            out[SUN_TEMPLE_PROGRESS_PERCENT] = 100;
            out[SUN_TEMPLE_PROGRESS_MATERIAL_TOTAL] = material_total;
            out[SUN_TEMPLE_PROGRESS_STATUS] = 4;
        }
        return 100;
    }

    const uint32_t flags = main->work_flags();
    int status = 1, at_stage0 = 0, temple_left = 0;
    int forecourt_left = 0, enclosure_left = 0, courtyard_left = 0, hall_left = 0;
    int masons = 0, masons_waiting = 0, laborers = 0, carpenters = 0, material = 0;

    for (int i = 0; i < parts_count(); ++i) {
        auto *p = main->part(i);
        if (!p) {
            continue;
        }
        if (p->part_has_active_worker()) {
            figure *f = figure_get(p->worker_figure_id());
            if (f) {
                if (f->type == FIGURE_CARPENTER) {
                    carpenters++;
                } else if (f->type == FIGURE_STONEMASON) {
                    if (f->action_state == ACTION_19_MASON_WAIT_FOR_BLOCK) {
                        masons_waiting++;
                    }
                    masons++;
                } else if (f->type == FIGURE_LABORER) {
                    laborers++;
                }
            }
        }

        const int stage = p->part_stage();
        switch (part_desc(i).kind) {
        case SUN_TEMPLE_PART_TEMPLE:
            temple_left += SUN_TEMPLE_STAGE_COMPLETE - stage;
            if (stage == 0) {
                status = (flags & SUN_TEMPLE_COURTYARD_STARTED) ? 2 : 1;
            } else if (stage >= 1 && stage <= 3) {
                status = 2;
            } else if (stage >= 4 && stage < SUN_TEMPLE_STAGE_COMPLETE) {
                status = 3;
            } else if (stage == SUN_TEMPLE_STAGE_COMPLETE) {
                status = 4;
            }
            break;
        case SUN_TEMPLE_PART_FORECOURT:
            if (stage == 0 || stage == 1) {
                at_stage0 += stage == 0;
                forecourt_left++;
                material += material_per_load;
            }
            break;
        case SUN_TEMPLE_PART_ENCLOSURE_CORNER_SW:
        case SUN_TEMPLE_PART_ENCLOSURE_CORNER_SE:
        case SUN_TEMPLE_PART_ENCLOSURE_CORNER_NE:
        case SUN_TEMPLE_PART_ENCLOSURE_CORNER_NW:
        case SUN_TEMPLE_PART_ENCLOSURE_SIDE:
        case SUN_TEMPLE_PART_ENCLOSURE_EDGE:
            if (stage == 0 || stage == 1) {
                at_stage0 += stage == 0;
                enclosure_left++;
                material += material_per_load;
            }
            break;
        case SUN_TEMPLE_PART_COURTYARD:
        case SUN_TEMPLE_PART_PATH:
        case SUN_TEMPLE_PART_COURTYARD_PILLAR:
        case SUN_TEMPLE_PART_COURTYARD_COLUMN:
            if (stage == 0 || stage == 1) {
                at_stage0 += stage == 0;
                courtyard_left++;
            }
            break;
        case SUN_TEMPLE_PART_HALL:
            if (stage >= 0 && stage < SUN_TEMPLE_LAST_PART_DONE) {
                at_stage0 += stage == 0;
                const int left = (stage == 0) ? (SUN_TEMPLE_LAST_PART_DONE - 1) : (SUN_TEMPLE_LAST_PART_DONE - stage);
                hall_left += left;
                material += left * material_per_load;
            }
            break;
        }
    }

    int spot_carpenters = 0, spot_masons = 0;
    for (int i = 0; i < SUN_TEMPLE_WORK_SPOTS; ++i) {
        const int fid = main->spot_attached(i);
        if (!fid) {
            continue;
        }
        figure *f = figure_get(fid);
        if (!f) {
            continue;
        }
        if (f->type == FIGURE_CARPENTER) {
            spot_carpenters++;
        } else if (f->type == FIGURE_STONEMASON) {
            spot_masons++;
        }
    }

    const int remaining = hall_left + courtyard_left + enclosure_left + temple_left + at_stage0;
    const int percent = ((work_units - remaining) * 100) / work_units;
    if (out) {
        out[SUN_TEMPLE_PROGRESS_AT_STAGE_0] = at_stage0;
        out[SUN_TEMPLE_PROGRESS_STATUS] = status;
        out[SUN_TEMPLE_PROGRESS_TEMPLE_LEFT] = temple_left;
        out[SUN_TEMPLE_PROGRESS_COURTYARD_LEFT] = courtyard_left;
        out[SUN_TEMPLE_PROGRESS_FORECOURT_LEFT] = forecourt_left;
        out[SUN_TEMPLE_PROGRESS_ENCLOSURE_LEFT] = enclosure_left;
        out[SUN_TEMPLE_PROGRESS_STONEMASONS] = spot_masons + masons;
        out[SUN_TEMPLE_PROGRESS_STONEMASONS_WAITING] = masons_waiting;
        out[SUN_TEMPLE_PROGRESS_LABORERS] = laborers;
        out[SUN_TEMPLE_PROGRESS_HALL_LEFT] = hall_left;
        out[SUN_TEMPLE_PROGRESS_CARPENTERS] = spot_carpenters + carpenters;
        out[SUN_TEMPLE_PROGRESS_MATERIAL] = material;
        out[SUN_TEMPLE_PROGRESS_PERCENT] = percent;
        out[SUN_TEMPLE_PROGRESS_MATERIAL_TOTAL] = material_total;
    }
    return percent;
}

void building_sun_temple::update_part_image() {
    const auto &desc = part_desc(part_index());
    const int img = building_image_get();
    map_building_tiles_add(id(), tile(), desc.size, img, TERRAIN_BUILDING);
}

void building_sun_temple::refresh_part_images() {
    building_sun_temple *m = main_sun_temple();
    if (!m) {
        return;
    }
    for (int i = 0; i < parts_count(); ++i) {
        if (auto *p = m->part(i)) {
            p->update_part_image();
        }
    }
}

int building_sun_temple::map_view() {
    return g_camera.orientation;
}

int building_sun_temple::art_orient_idx() {
    return (g_camera.orientation / 2) % 2;
}

int building_sun_temple::camera_view() {
    return (g_camera.orientation / 2) & 3;
}

int building_sun_temple::temple_image_band(const base_params &params, int stage) {
    int band = 0;
    for (int i = 0; i < (int)params.temple_image_stages.size(); ++i) {
        if (stage >= params.temple_image_stages[i]) {
            band = i + 1;
        }
    }
    const int n = (int)params.temple_images.size();
    if (n <= 0) {
        return 0;
    }
    return std::min(band, n - 1);
}

int building_sun_temple::extra_img(const static_params &params, int offset) {
    if (offset < 0 || offset >= (int)params.extra_images.size()) {
        return 0;
    }
    const int img = params.first_img(params.extra_images[offset]);
    return img > 0 ? img : 0;
}

int building_sun_temple::img_or_fallback(const static_params &params, xstring key) {
    if (key.empty()) {
        return 0;
    }
    const int img = params.first_img(key);
    return img > 0 ? img : 0;
}

int building_sun_temple::finished_extra_offset(e_sun_temple_part_kind kind, int view) {
    switch (kind) {
    case SUN_TEMPLE_PART_FORECOURT:
        return (view / 2) & 1;
    case SUN_TEMPLE_PART_ENCLOSURE_CORNER_SW:
        return (((8 - view) / 2) & 3) + 2;
    case SUN_TEMPLE_PART_ENCLOSURE_CORNER_SE:
        return (((8 - view) / 2 + 1) & 3) + 2;
    case SUN_TEMPLE_PART_ENCLOSURE_CORNER_NE:
        return (((8 - view) / 2 - 2) & 3) + 2;
    case SUN_TEMPLE_PART_ENCLOSURE_CORNER_NW:
        return (((8 - view) / 2 - 1) & 3) + 2;
    case SUN_TEMPLE_PART_ENCLOSURE_SIDE:
        return ((view / 2) & 1) + 6;
    case SUN_TEMPLE_PART_ENCLOSURE_EDGE:
        return ((view / 2 - 1) & 1) + 6;
    case SUN_TEMPLE_PART_COURTYARD:
        return 8;
    case SUN_TEMPLE_PART_PATH:
        return 9;
    case SUN_TEMPLE_PART_COURTYARD_PILLAR:
        return 10;
    case SUN_TEMPLE_PART_COURTYARD_COLUMN:
        return 11;
    case SUN_TEMPLE_PART_HALL:
        return 12;
    default:
        return -1;
    }
}

int building_sun_temple::building_image_get() const {
    const auto &params = current_params();
    const e_sun_temple_part_kind kind = part_kind();
    const int stage = part_stage();
    const int view = map_view();
    const int orient = art_orient_idx();

    if (kind == SUN_TEMPLE_PART_TEMPLE) {
        // OG: stage < 9 → pack 0, < 13 → pack 1, else pack 2; id = (view/2)&1.
        int use_stage = stage;
        if (runtime_data().phase == MONUMENT_FINISHED) {
            use_stage = SUN_TEMPLE_STAGE_COMPLETE;
        }
        const int band = temple_image_band(params, use_stage);
        bstring32 key;
        if (band < (int)params.temple_images.size() && !params.temple_images[band].empty()) {
            key.printf("%s%d", params.temple_images[band].c_str(), orient + 1);
        } else {
            key.printf("s%c%d", 'a' + band, orient + 1);
        }
        int img = params.first_img(xstring(key.c_str()));
        if (img <= 0) {
            img = params.first_img("sa1");
        }
        return img > 0 ? img : params.first_img("preview");
    }

    // OG hall finishes at stage 4; other side parts at stage 2.
    const int done_stage = (kind == SUN_TEMPLE_PART_HALL) ? SUN_TEMPLE_LAST_PART_DONE : SUN_TEMPLE_PART_DONE;
    if (stage >= done_stage) {
        const int offset = finished_extra_offset(kind, view);
        const int img = extra_img(params, offset);
        return img > 0 ? img : params.first_img("preview");
    }

    if (stage == 1) {
        const int img = img_or_fallback(params, params.leveled);
        return img > 0 ? img : 0;
    }

    // OG: unleveled plaza / walkway outline (kinds 1–5 and hall before stage 1).
    if (kind >= SUN_TEMPLE_PART_FORECOURT && kind <= SUN_TEMPLE_PART_ENCLOSURE_EDGE) {
        return img_or_fallback(params, params.unbuilt);
    }
    if (kind == SUN_TEMPLE_PART_HALL && stage < 1) {
        return img_or_fallback(params, params.unbuilt);
    }
    return 0;
}

void building_sun_temple::animate_spots() {
    const int now = game.simtime.absolute_tick();
    int steps = (g_spot_anim_tick < 0) ? 1 : std::clamp(now - g_spot_anim_tick, 0, 64);
    g_spot_anim_tick = now;
    const int view = camera_view();

    const auto &spots = st_params().spots;
    for (int i = 0; i < (int)spots.size() && i < SUN_TEMPLE_WORK_SPOTS; ++i) {
        auto &a = g_spot_anims[i];
        const int fid = spot_attached(i);
        if (!fid) {
            a.active = false;
            a.figure = 0;
            continue;
        }
        if (a.figure != fid) {
            a.figure = (uint16_t)fid;
            start_spot_anim(spots[i].script, view, a);
        }
        for (int k = 0; k < steps; ++k) {
            step_spot_anim(spots[i].script, view, a);
        }
    }
}

// OG sun temple worker scripts: drawn once from the main (temple) part.
bool building_sun_temple::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (!is_main() || is_finished() || tile != base.tile) {
        return false;
    }
    animate_spots();

    const int view = camera_view();
    const auto &params = st_params();
    const auto &spots = params.spots;
    bool drew = false;

    // Sort workers after the screen-lowest corner of the whole footprint.
    {
        grid_area area = get_area();
        int max_y = point.y;
        for (const tile2i corner : {area.tmin(), tile2i(area.tmax().x(), area.tmin().y()),
               tile2i(area.tmin().x(), area.tmax().y()), area.tmax()}) {
            max_y = std::max(max_y, g_camera.lookup_tile_to_pixel(corner).y);
        }
        auto &anchor = ImageDraw::create_command(ctx, render_command_t::ert_none);
        anchor.pixel = point;
        anchor.use_sort_pixel = true;
        anchor.sort_pixel = vec2i{point.x, max_y};
    }

    for (int i = 0; i < (int)spots.size() && i < SUN_TEMPLE_WORK_SPOTS; ++i) {
        const auto &a = g_spot_anims[i];
        const sun_temple_anim_script *sc = anim_script(spots[i].script);
        if (!a.active || !sc || a.sequence < 0 || a.sequence >= (int)sc->sequences.size()) {
            continue;
        }
        const auto &seq = sc->sequences[a.sequence];
        auto img_it = params.worker_images.find(seq.anim);
        if (img_it == params.worker_images.end() || seq.frames <= 0) {
            continue;
        }
        const auto &img = img_it->second;
        const int base_img = image_id_from_group(img.pack, img.id);
        if (base_img <= 0) {
            continue;
        }
        const bool mirror = (view == 1 || view == 3) && !sc->unmirrored;
        const auto view_point = [mirror](vec2i p) { return mirror ? vec2i{-p.x, p.y} : p; };
        const vec2i from = view_point(seq.from);
        const vec2i to = view_point(seq.to);
        const vec2i offset = params.anim_offset;
        const int x = (to.x - from.x) * a.frame / seq.frames + offset.x + from.x;
        const int y = (to.y - from.y) * a.frame / seq.frames + offset.y + from.y;

        const int image_id = base_img + img.offset + (a.frame % std::max<int>(1, img.frames)) * img.step;
        const image_t *image = image_get(image_id);
        if (!image) {
            continue;
        }
        auto &command = ImageDraw::create_subcommand(ctx, render_command_t::ert_generic);
        command.image_id = image_id;
        command.pixel = point + vec2i{x, y} - image->animation.sprite_offset;
        command.mask = color_mask;
        drew = true;
    }
    return drew;
}

bool building_sun_temple::needs_resources() const {
    return false;
}

bool building_sun_temple::need_carpenter() {
    return is_main() && !is_finished() && has_free_spot(FIGURE_CARPENTER);
}

bool building_sun_temple::need_stonemason() {
    if (is_finished()) {
        return false;
    }
    // Kind 0 spots, or any side part that can take a mason for sandstone stage.
    if (is_main() && has_free_spot(FIGURE_STONEMASON)) {
        return true;
    }
    for (int i = 0; i < parts_count(); ++i) {
        auto *p = part(i);
        if (!p || p->part_has_active_worker()) {
            continue;
        }
        const int kind = p->part_kind();
        const int stage = p->part_stage();
        const uint32_t flags = work_flags();
        if (kind >= SUN_TEMPLE_PART_FORECOURT && kind <= SUN_TEMPLE_PART_ENCLOSURE_EDGE) {
            const uint32_t unlock = (kind == SUN_TEMPLE_PART_FORECOURT) ? SUN_TEMPLE_TEMPLE_DONE : SUN_TEMPLE_FORECOURT_DONE;
            if ((flags & unlock) && stage == SUN_TEMPLE_PART_STARTED) {
                return true;
            }
        } else if (kind == SUN_TEMPLE_PART_HALL) {
            if ((flags & SUN_TEMPLE_COURTYARD_DONE) && (flags & SUN_TEMPLE_ENCLOSURE_DONE) && stage >= 1 && stage <= 3) {
                return true;
            }
        }
    }
    return false;
}

bool building_sun_temple::need_workers() const {
    if (is_finished() || !is_main()) {
        return false;
    }
    // Any part that would accept a laborer (leveling or material partner).
    for (int i = 0; i < parts_count(); ++i) {
        auto *p = const_cast<building_sun_temple *>(this)->part(i);
        if (!p) {
            continue;
        }
        // Probe with a synthetic check: laborer type without assign.
        // Use check path by temporarily requiring laborer gates.
        const int kind = p->part_kind();
        const int stage = p->part_stage();
        const uint32_t flags = work_flags();
        if (p->part_has_active_worker()) {
            // Material partner for waiting mason.
            if (p->worker_figure_id()) {
                figure *w = figure_get(p->worker_figure_id());
                if (w && w->type == FIGURE_STONEMASON && w->action_state == ACTION_19_MASON_WAIT_FOR_BLOCK
                    && w->leading_figure_id == 0) {
                    return true;
                }
            }
            continue;
        }
        if (kind >= SUN_TEMPLE_PART_FORECOURT && kind <= SUN_TEMPLE_PART_ENCLOSURE_EDGE) {
            const uint32_t unlock = (kind == SUN_TEMPLE_PART_FORECOURT) ? SUN_TEMPLE_TEMPLE_DONE : SUN_TEMPLE_FORECOURT_DONE;
            if (!(flags & unlock) || stage == 0) {
                if (stage == 0) {
                    return true;
                }
            } else if (stage == SUN_TEMPLE_PART_STARTED) {
                return true;
            }
        } else if (kind >= SUN_TEMPLE_PART_COURTYARD && kind <= SUN_TEMPLE_PART_COURTYARD_COLUMN) {
            if (!(flags & SUN_TEMPLE_COURTYARD_STARTED)) {
                if (stage == 0) {
                    return true;
                }
            } else if ((flags & SUN_TEMPLE_TEMPLE_DONE) && stage == 1) {
                return true;
            }
        } else if (kind == SUN_TEMPLE_PART_HALL) {
            if (!(flags & SUN_TEMPLE_COURTYARD_DONE) || !(flags & SUN_TEMPLE_ENCLOSURE_DONE) || stage == 0) {
                if (stage == 0) {
                    return true;
                }
            } else if (stage >= 1 && stage <= 3) {
                return true;
            }
        }
    }
    return false;
}

void building_sun_temple::add_workers(figure_id fid) {
    if (!is_main()) {
        main()->add_workers(fid);
        return;
    }
    auto &d = runtime_data();
    for (auto &wid : d.workers) {
        if (wid == 0) {
            wid = fid;
            return;
        }
    }
}

void building_sun_temple::remove_worker(figure_id fid) {
    if (!is_main()) {
        main()->remove_worker(fid);
        return;
    }
    auto &d = runtime_data();
    for (auto &wid : d.workers) {
        if (wid == fid) {
            wid = 0;
            return;
        }
    }
    // Also clear part worker slots.
    for (int i = 0; i < parts_count(); ++i) {
        if (auto *p = part(i); p && p->worker_figure_id() == fid) {
            p->clear_worker_figure();
        }
    }
    for (int i = 0; i < SUN_TEMPLE_WORK_SPOTS; ++i) {
        if (spot_attached(i) == fid) {
            set_spot(i, (uint16_t)spot_work_left(i), 0);
        }
    }
}

void building_sun_temple::preview::setup_preview_graphics(build_planner &planer) const {
    int min_x, min_y, max_x, max_y;
    footprint_bounds(min_x, min_y, max_x, max_y);
    planer.init_tiles(max_x - min_x + 1, max_y - min_y + 1);
}

int building_sun_temple::preview::can_place(build_planner &p, tile2i /*tile*/, tile2i end, int state) const {
    if (state != CAN_PLACE && state != CAN_NOT_BUT_GREEN) {
        return state;
    }
    if (has_completed_sun_temple()) {
        p.set_warning("#only_one_sun_temple_at_a_time");
        return CAN_NOT_PLACE;
    }
    int sandstone_need = 0;
    for (const auto &pr : building_sun_temple::current_params().placement_resources) {
        if (pr.resource == RESOURCE_SANDSTONE) {
            sandstone_need = pr.count;
            break;
        }
    }
    if (sandstone_need > 0 && yards_available(RESOURCE_SANDSTONE) < sandstone_need) {
        return CAN_NOT_PLACE;
    }
    for (int i = 0; i < parts_count(); ++i) {
        if (!area_for_part_free(end, part_desc(i))) {
            return CAN_NOT_PLACE;
        }
    }
    return CAN_PLACE;
}

int building_sun_temple::preview::finalize_check(build_planner &p, tile2i tile, tile2i end, int state) const {
    state = building_planer_renderer::finalize_check(p, tile, end, state);
    if (state != CAN_PLACE) {
        return state;
    }
    if (has_completed_sun_temple()) {
        p.set_warning("#only_one_sun_temple_at_a_time");
        return CAN_NOT_PLACE;
    }
    int sandstone_need = 0;
    for (const auto &pr : building_sun_temple::current_params().placement_resources) {
        if (pr.resource == RESOURCE_SANDSTONE) {
            sandstone_need = pr.count;
            break;
        }
    }
    if (sandstone_need > 0 && yards_available(RESOURCE_SANDSTONE) < sandstone_need) {
        p.set_warning("#need_220_blocks_of_sandstone_for_sun_temple");
        g_warning_manager.show("#need_220_blocks_of_sandstone_for_sun_temple");
        return CAN_NOT_PLACE;
    }
    return can_place(p, tile, end, CAN_PLACE);
}

int building_sun_temple::preview::construction_place(build_planner &planer, tile2i tile, tile2i end, int orientation,
  int variant) const {
    const int placed = building_planer_renderer::construction_place(planer, tile, end, orientation, variant);
    if (placed && planer.last_created_building && !planer.last_created_building->is_valid()) {
        planer.last_created_building = nullptr;
        return 0;
    }
    return placed;
}

void building_sun_temple::preview::ghost_preview(build_planner &planer, painter &ctx, tile2i /*start*/, tile2i end,
  vec2i /*pixel*/) const {
    const auto &params = building_static_params::get(planer.build_type);
    const int preview = params.first_img("preview");
    const int img_body = params.first_img("sa1");
    bool blocked = false;
    for (int i = 0; i < parts_count(); ++i) {
        if (!area_for_part_free(end, part_desc(i))) {
            blocked = true;
            break;
        }
    }
    for (int i = 0; i < parts_count(); ++i) {
        const auto &d = part_desc(i);
        tile2i t = end.shifted(d.offset.x, d.offset.y);
        if (blocked) {
            draw_area_mask(ctx, t, d.size, d.size, true);
        } else if (d.kind == SUN_TEMPLE_PART_TEMPLE) {
            planer.draw_building_ghost(ctx, img_body > 0 ? img_body : preview, g_camera.lookup_tile_to_pixel(t));
        } else {
            draw_area_mask(ctx, t, d.size, d.size, false);
        }
    }
}

void building_sun_temple::on_place(int orientation, int variant) {
    building_impl::on_place(orientation, variant);
    if (!base.is_valid()) {
        return;
    }
    const int need = placement_amount(RESOURCE_SANDSTONE);
    if (need > 0) {
        events::emit(event_city_remove_resource{RESOURCE_SANDSTONE, need, /*staffed_only*/ true});
    }
}

void building_sun_temple::on_place_update_tiles(int /*orientation*/, int /*variant*/) {
    base.prev_part_building_id = 0;
    runtime_data().variant = 0;
    runtime_data().phase = 0;
    runtime_data().work_flags = 0;
    base.orientation = 0;
    base.size = part_desc(0).size;

    // Shift placement so part 0 (main) sits at its OG relative offset from the cursor.
    // Planner end tile is the origin used by part_descs (same as OG sun_temple_place).
    const auto &d0 = part_desc(0);
    // Body already created at end; move it to end+d0 if needed.
    if (d0.offset.x != 0 || d0.offset.y != 0) {
        // building_create already put us at end; OG rewrites main to end+d0.
        tile2i desired = tile().shifted(d0.offset.x, d0.offset.y);
        // Clear current tiles then re-add at desired — planner placed at end.
        map_building_tiles_remove(id(), tile());
        base.tile = desired;
        base.size = d0.size;
    }
    update_part_image();

    building *prev = &base;
    bool ok = true;
    for (int part_i = 1; part_i < parts_count(); ++part_i) {
        const auto &d = part_desc(part_i);
        // Origin is main tile - d0 offset.
        tile2i origin = tile().shifted(-d0.offset.x, -d0.offset.y);
        tile2i part_tile = origin.shifted(d.offset.x, d.offset.y);
        building *b = building_create(BUILDING_SUN_TEMPLE, part_tile, 0);
        if (!b || b->id <= 0) {
            ok = false;
            break;
        }
        game_undo_add_building(b);
        auto *sp = b->dcast_sun_temple();
        if (sp) {
            sp->runtime_data().variant = (uint8_t)part_i;
            sp->runtime_data().phase = 0;
            sp->runtime_data().work_flags = 0;
        }
        b->orientation = 0;
        b->size = d.size;
        b->prev_part_building_id = prev->id;
        b->next_part_building_id = 0;
        prev->next_part_building_id = b->id;
        if (sp) {
            sp->update_part_image();
        }
        prev = b;
    }

    if (!ok) {
        // Tear down the chain.
        for (building *p = &base; p;) {
            building *next = p->has_next() ? p->next() : nullptr;
            map_building_tiles_remove(p->id, p->tile);
            p->state = BUILDING_STATE_DELETED_BY_GAME;
            p = next;
        }
        return;
    }

    reset_spots();
    refresh_part_images();
}

void building_sun_temple::on_post_load() {
    building_monument::on_post_load();
    if (!is_main()) {
        return;
    }
    if (work_spots().any_unset()) {
        reset_spots();
        const auto &defs = st_params().spots;
        const int s = part_stage();
        for (int i = 0; i < (int)defs.size() && i < SUN_TEMPLE_WORK_SPOTS; ++i) {
            if (defs[i].stage < s) {
                set_spot(i, 0, 0);
            }
        }
    }
    refresh_part_images();
}

void building_sun_temple::on_destroy() {
    if (is_main()) {
        work_spots().mark_unset();
    }
}

void building_sun_temple::update_day() {
    building_impl::update_day();
    if (!is_main() || is_finished()) {
        return;
    }
    scrub_spots();

    if (get_progress(nullptr) >= 100) {
        for (int i = 0; i < parts_count(); ++i) {
            if (auto *p = part(i)) {
                p->set_phase(MONUMENT_FINISHED);
            }
        }
        refresh_part_images();
        city_message &message = city_message_post_with_popup_delay(
            MESSAGE_CAT_MONUMENTS, true, "sun_temple_congratulations", type(), tile().grid_offset());
        message.hide_img = true;
    }
}

void building_sun_temple::update_map_orientation(int /*map_orientation*/) {
    main_sun_temple()->refresh_part_images();
}

tile2i building_sun_temple::center_point() const {
    grid_area area = get_area();
    return tile2i((area.tmin().x() + area.tmax().x()) / 2, (area.tmin().y() + area.tmax().y()) / 2);
}

tile2i building_sun_temple::access_point() const {
    // OG hall is kind 12 (last part).
    if (auto *hall = part(parts_count() - 1)) {
        return hall->tile();
    }
    return main()->tile();
}

grid_area building_sun_temple::get_area() const {
    const building_sun_temple *m = main_sun_temple();
    tile2i start = m->tile();
    tile2i end = start;
    for (int i = 0; i < parts_count(); ++i) {
        auto *p = const_cast<building_sun_temple *>(m)->part(i);
        if (!p) {
            continue;
        }
        const int sz = std::max(1, (int)part_desc(i).size);
        tile2i pmin = p->tile();
        tile2i pmax = pmin.shifted(sz - 1, sz - 1);
        start = tile2i(std::min(start.x(), pmin.x()), std::min(start.y(), pmin.y()));
        end = tile2i(std::max(end.x(), pmax.x()), std::max(end.y(), pmax.y()));
    }
    return {start, end};
}

void building_sun_temple::bind_dynamic(io_buffer *iob, size_t /*version*/) {
    auto &d = runtime_data();

    if (is_main()) {
        iob->bind(BIND_SIGNATURE_UINT8, &d.work_flags);
        work_spots().bind(iob, /*with_figures*/ true);
    } else {
        iob->bind____skip(38);
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

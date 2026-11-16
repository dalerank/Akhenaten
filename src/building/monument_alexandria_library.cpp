#include "monument_alexandria_library.h"

#include "building/monuments.h"
#include "building/rotation.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_message.h"
#include "city/city_resource.h"
#include "city/city_warnings.h"
#include "construction/build_planner.h"
#include "figure/figure.h"
#include "figuretype/figure_carpenter.h"
#include "figuretype/figure_stonemason.h"
#include "figuretype/figure_worker.h"
#include "game/game.h"
#include "game/resource.h"
#include "game/undo.h"
#include "graphics/color.h"
#include "graphics/view/lookup.h"
#include "graphics/view/view.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/image.h"
#include "grid/property.h"
#include "grid/random.h"
#include "grid/road_access.h"
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "js/js_game.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_alexandria_library);
BUILDING_RUNTIME_DATA_IMPL(building_alexandria_library)

static monument g_monument_alexandria_library{BUILDING_ALEXANDRIA_LIBRARY};

namespace {

const building_alexandria_library::base_params &lib_params() {
    return (const building_alexandria_library::base_params &)building_alexandria_library::current_params();
}

class library_spots {
public:
    int attached(int spot) const { return valid(spot) ? figure_[spot] : 0; }
    int work_left(int spot) const { return valid(spot) ? work_[spot] : 0; }

    void set(int spot, uint16_t work, uint16_t fid) {
        if (!valid(spot)) {
            return;
        }
        work_[spot] = work;
        figure_[spot] = fid;
    }

    void reset(const svector<library_spot_def, LIBRARY_WORK_SPOTS> &defs) {
        for (int i = 0; i < LIBRARY_WORK_SPOTS; ++i) {
            work_[i] = i < (int)defs.size() ? defs[i].work : 0;
            figure_[i] = 0;
        }
    }

    void mark_unset() {
        work_.fill(LIBRARY_SPOT_WORK_UNSET);
        figure_.fill(0);
    }

    bool any_unset() const {
        for (uint16_t w : work_) {
            if (w == LIBRARY_SPOT_WORK_UNSET) {
                return true;
            }
        }
        return false;
    }

    void bind(io_buffer *iob, bool with_figures) {
        for (int i = 0; i < LIBRARY_WORK_SPOTS; i++) {
            iob->bind(BIND_SIGNATURE_UINT16, &work_[i]);
        }
        if (with_figures) {
            for (int i = 0; i < LIBRARY_WORK_SPOTS; i++) {
                iob->bind(BIND_SIGNATURE_UINT16, &figure_[i]);
            }
        }
    }

private:
    static bool valid(int spot) { return spot >= 0 && spot < LIBRARY_WORK_SPOTS; }
    std::array<uint16_t, LIBRARY_WORK_SPOTS> work_{};
    std::array<uint16_t, LIBRARY_WORK_SPOTS> figure_{};
};

library_spots &work_spots() {
    static library_spots state;
    return state;
}

struct spot_anim {
    int8_t sequence = -1;
    int8_t reverse = 0;
    int16_t frame = 0;
    bool active = false;
    uint16_t figure = 0;
};

std::array<spot_anim, LIBRARY_WORK_SPOTS> g_spot_anims{};
int g_spot_anim_tick = -1;

int camera_view() {
    return g_camera.orientation / 2;
}

const library_anim_script *anim_script(const xstring &name) {
    const auto &scripts = lib_params().anim_scripts;
    auto it = scripts.find(name);
    return it != scripts.end() ? &it->second : nullptr;
}

bool pick_choice(const library_anim_script &sc, const svector<vec2i, 4> &choices, int view, spot_anim &a) {
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
    const library_anim_script *sc = anim_script(script);
    if (!sc) {
        return;
    }
    static const svector<vec2i, 4> first = {vec2i{0, 0}, vec2i{-1, 0}, vec2i{-1, 0}, vec2i{-1, 0}};
    a.active = pick_choice(*sc, sc->entry.empty() ? first : sc->entry, view, a);
}

void step_spot_anim(const xstring &script, int view, spot_anim &a) {
    const library_anim_script *sc = anim_script(script);
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
        a.active = false;
    } else if (seq.next.empty()) {
        const svector<vec2i, 4> following
          = {vec2i{(a.sequence + 1) % (int)sc->sequences.size(), 0}, vec2i{-1, 0}, vec2i{-1, 0}, vec2i{-1, 0}};
        a.active = pick_choice(*sc, following, view, a);
    } else {
        a.active = pick_choice(*sc, seq.next, view, a);
    }
}

vec2i view_point(const svector<vec2i, 4> &views, int view) {
    if (views.empty()) {
        return {};
    }
    return views[std::clamp(view, 0, (int)views.size() - 1)];
}

bool tile_not_clear(tile2i t) {
    return map_terrain_is(t, TERRAIN_NOT_CLEAR)
        || (map_terrain_count_directly_adjacent_with_type(t, TERRAIN_FLOODPLAIN) > 0)
        || (map_terrain_count_diagonally_adjacent_with_type(t, TERRAIN_FLOODPLAIN) > 0)
        || map_has_figure_at(t);
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

constexpr int LIBRARY_VIEW_SOUTH_FIRST = 2;

// OG loads LibExtra / LibExtra2 into one IMAGE_GROUP slot via anim_load_script.
// Parts with script NONE keep whatever pack the last scripted Extra part loaded.
int g_library_extra_pack = 0; // 0 = LibExtra, 1 = LibExtra2

bool is_lib_extra_key(const xstring &key) {
    return key == "front" || key == "c4" || key == "cc" || key == "dc" || key == "e4" || key == "ec"
        || key == "f4" || key == "fc" || key == "i04" || key == "i0c" || key == "i14" || key == "i1c"
        || key == "i24" || key == "i2c" || key == "i34" || key == "i3c";
}

xstring lib_extra_anim_key(const xstring &key, bool use_extra2) {
    if (!use_extra2) {
        return key;
    }
    bstring32 k;
    k.printf("%s_2", key.c_str());
    return xstring(k.c_str());
}

const library_image_step *find_image_step(int kind, int stage) {
    const library_image_step *found = nullptr;
    for (const auto &step : lib_params().image_steps) {
        if (step.kind != kind) {
            continue;
        }
        found = &step;
        if (stage < step.until) {
            break;
        }
    }
    return found;
}

int resolve_step_image(const building_static_params &params, const xstring &key, const xstring &script) {
    if (key.empty() || key == "blank") {
        return 0;
    }

    xstring anim_key = key;
    if (key == "main_a" || key == "main_b" || key == "main_c") {
        // Script is already the animation key (main_a1 / main_b3 / …).
        if (script.empty()) {
            return 0;
        }
        anim_key = script;
    } else if (key == "leveled") {
        const auto &lp = lib_params();
        anim_key = lp.leveled.empty() ? key : lp.leveled;
    } else if (script == "extra2") {
        g_library_extra_pack = 1;
        anim_key = lib_extra_anim_key(key, true);
    } else if (script == "extra") {
        g_library_extra_pack = 0;
        anim_key = key;
    } else if (is_lib_extra_key(key)) {
        anim_key = lib_extra_anim_key(key, g_library_extra_pack != 0);
    }

    return std::max(0, params.first_img(anim_key));
}

// OG keeps_tile_image: tiles of 3x3 part indices 13..16 that FRONT must not overwrite.
bool keeps_front_tile_image(int part, int row, int col) {
    switch (part) {
    case 13: return col > 0 || row < 2;
    case 14: return col < 2 || row < 2;
    case 15: return col > 0 || row > 0;
    case 16: return col < 2 || row > 0;
    default: return false;
    }
}

} // namespace

void building_alexandria_library::static_params::archive_load(archive /*arch*/) {
    g_monument_alexandria_library.btype = BUILDING_ALEXANDRIA_LIBRARY;
    g_monument_alexandria_library.phases.clear();
    // Keep 0..COMPLETE so set_phase(n) is not collapsed to FINISHED.
    for (uint8_t i = 0; i <= LIBRARY_STAGE_COMPLETE; ++i) {
        g_monument_alexandria_library.phases.push_back({i, monument_phase_resource{RESOURCE_NONE, 0}});
    }
}

const monument &building_alexandria_library::config() const {
    return g_monument_alexandria_library;
}

int building_alexandria_library::parts_count() {
    return std::min((int)lib_params().parts.size(), (int)LIBRARY_PARTS);
}

const library_part_desc &building_alexandria_library::part_desc(int index) {
    static library_part_desc empty;
    const auto &parts = lib_params().parts;
    if (index < 0 || index >= (int)parts.size()) {
        return empty;
    }
    return parts[index];
}

bool building_alexandria_library::has_unfinished_alexandria_library() {
    return building_monument_has_unfinished({BUILDING_ALEXANDRIA_LIBRARY});
}

e_resource building_alexandria_library::material_for_stage(int stage) {
    if (stage >= LIBRARY_STAGE_COPPER_FIRST && stage < LIBRARY_STAGE_COPPER_END) {
        return RESOURCE_COPPER;
    }
    return RESOURCE_MARBLE;
}

vec2i building_alexandria_library::box_extent() {
    int minx = 0, miny = 0, maxx = 0, maxy = 0;
    const int n = parts_count();
    for (int i = 0; i < n; ++i) {
        const auto &d = part_desc(i);
        minx = std::min(minx, d.offset.x);
        miny = std::min(miny, d.offset.y);
        maxx = std::max(maxx, d.offset.x + d.size);
        maxy = std::max(maxy, d.offset.y + d.size);
    }
    return {maxx - minx, maxy - miny};
}

bool building_alexandria_library::area_for_part_free(tile2i origin, const library_part_desc &desc) {
    for (int dy = 0; dy < desc.size; ++dy) {
        for (int dx = 0; dx < desc.size; ++dx) {
            tile2i t = origin.shifted(desc.offset.x + dx, desc.offset.y + dy);
            if (!map_grid_is_inside(t, 1) || tile_not_clear(t)) {
                return false;
            }
        }
    }
    return true;
}

building_alexandria_library *building_alexandria_library::main_library() {
    return base.main()->dcast_alexandria_library();
}

const building_alexandria_library *building_alexandria_library::main_library() const {
    return const_cast<building_alexandria_library *>(this)->main_library();
}

building_alexandria_library *building_alexandria_library::part(int index) {
    building *b = &main_library()->base;
    for (int i = 0; b && i < index; ++i) {
        b = b->has_next() ? b->next() : nullptr;
    }
    return b ? b->dcast_alexandria_library() : nullptr;
}

const building_alexandria_library *building_alexandria_library::part(int index) const {
    return const_cast<building_alexandria_library *>(this)->part(index);
}

int building_alexandria_library::part_kind() const {
    return part_desc(part_index()).kind;
}

int building_alexandria_library::part_stage() const {
    const int p = runtime_data().phase;
    if (p == MONUMENT_FINISHED) {
        return LIBRARY_STAGE_COMPLETE;
    }
    return p;
}

int building_alexandria_library::spot_attached(int spot) const {
    return work_spots().attached(spot);
}

int building_alexandria_library::spot_work_left(int spot) const {
    return work_spots().work_left(spot);
}

void building_alexandria_library::set_spot(int spot, uint16_t work, uint16_t fid) {
    work_spots().set(spot, work, fid);
}

void building_alexandria_library::reset_spots() {
    work_spots().reset(lib_params().spots);
}

void building_alexandria_library::scrub_spots() {
    const auto &spots = lib_params().spots;
    for (int i = 0; i < (int)spots.size() && i < LIBRARY_WORK_SPOTS; ++i) {
        const int fid = spot_attached(i);
        if (!fid) {
            continue;
        }
        figure *f = figure_get(fid);
        if (!f || !f->is_alive()) {
            set_spot(i, (uint16_t)spot_work_left(i), 0);
        }
    }
}

int building_alexandria_library::find_free_spot(e_figure_type type) const {
    const auto &spots = lib_params().spots;
    const int s = main_library()->part_stage();
    for (int i = 0; i < (int)spots.size() && i < LIBRARY_WORK_SPOTS; ++i) {
        const auto &def = spots[i];
        if (def.stage == s && def.figure == type && spot_attached(i) == 0 && spot_work_left(i) > 0) {
            return i;
        }
    }
    return -1;
}

bool building_alexandria_library::has_free_spot(e_figure_type type) const {
    return find_free_spot(type) >= 0;
}

figure_id building_alexandria_library::worker_figure_id() const {
    return runtime_data().og_part.worker_figure_id;
}

void building_alexandria_library::set_worker_figure(figure_id fid) {
    runtime_data().og_part.worker_figure_id = fid;
}

void building_alexandria_library::clear_worker_figure() {
    runtime_data().og_part.worker_figure_id = 0;
}

bool building_alexandria_library::part_has_active_worker() const {
    const building_alexandria_library *target = this;
    if (part_stage() >= LIBRARY_STAGE_BUILDING) {
        target = main_library();
    }
    const figure_id wid = target->worker_figure_id();
    if (!wid) {
        return false;
    }
    figure *f = figure_get(wid);
    if (!f || !f->is_alive()) {
        const_cast<building_alexandria_library *>(target)->clear_worker_figure();
        return false;
    }
    const int action = f->action_state;
    switch (f->type) {
    case FIGURE_LABORER:
        return action == ACTION_15_LABORER_TO_STORAGE_YARD || action == ACTION_16_LABORER_AT_STORAGE_YARD
            || action == ACTION_31_LABORER_SLED_TO_LIBRARY || action == ACTION_32_LABORER_TO_LIBRARY
            || action == ACTION_33_LABORER_LIBRARY_WORK;
    case FIGURE_STONEMASON:
        return action == ACTION_1_MASON_GOING || action == ACTION_9_MASON_WORK_OBELISK
            || action == ACTION_19_MASON_WAIT_FOR_BLOCK;
    case FIGURE_CARPENTER:
        return action == ACTION_1_CARPENTER_GO_TO_SITE || action == ACTION_2_CARPENTER_WORK;
    default:
        const_cast<building_alexandria_library *>(target)->clear_worker_figure();
        return false;
    }
}

tile2i building_alexandria_library::work_tile() const {
    if (part_stage() < LIBRARY_STAGE_BUILDING) {
        const int half = std::max(0, (int)part_desc(part_index()).size / 2);
        return tile().shifted(half, half);
    }
    const building_alexandria_library *m = main_library();
    return m->tile().shifted(LIBRARY_WORK_TILE_DX, LIBRARY_WORK_TILE_DY);
}

void building_alexandria_library::send_to_part(figure &f) const {
    f.destination_tile = work_tile();
    f.destination_building_id = id();
    f.wait_ticks = 0;
    f.roam_length = 0;
}

bool building_alexandria_library::all_parts_prepared() const {
    const building_alexandria_library *m = main_library();
    for (int i = 0; i < parts_count(); ++i) {
        const auto *p = m->part(i);
        if (!p || p->part_stage() < LIBRARY_STAGE_PREPARED) {
            return false;
        }
    }
    return true;
}

void building_alexandria_library::advance_all_parts() {
    building_alexandria_library *m = main_library();
    if (!m || m->is_finished()) {
        return;
    }
    int stage = m->part_stage();
    if (stage >= LIBRARY_STAGE_COMPLETE) {
        return;
    }
    stage++;
    m->runtime_data().material_frame = 0;
    m->reset_spots();
    for (int i = 0; i < parts_count(); ++i) {
        if (auto *p = m->part(i)) {
            p->set_phase(stage);
            p->update_part_image();
            p->base.road_access = p->work_tile();
        }
    }
    if (stage == LIBRARY_STAGE_COMPLETE) {
        m->finish_all();
    }
}

void building_alexandria_library::finish_all() {
    for (int i = 0; i < parts_count(); ++i) {
        if (auto *p = part(i)) {
            p->set_phase(MONUMENT_FINISHED);
            p->update_part_image();
        }
    }
    refresh_part_images();
    city_message &message = city_message_post_with_popup_delay(
        MESSAGE_CAT_MONUMENTS, true, "alex_library_congratulations", type(), tile().grid_offset());
    message.hide_img = true;
}

void building_alexandria_library::on_material_delivered() {
    building_alexandria_library *m = main_library();
    if (!m) {
        return;
    }
    auto &d = m->runtime_data();
    d.material_frame++;
    if (d.material_frame < LIBRARY_FRAME_COUNT) {
        return;
    }
    d.material_frame = 0;
    figure_id mason_id = m->worker_figure_id();
    figure *mason = mason_id ? figure_get(mason_id) : nullptr;
    if (mason && mason->is_alive() && mason->type == FIGURE_STONEMASON
        && mason->action_state == ACTION_19_MASON_WAIT_FOR_BLOCK) {
        mason->action_state = ACTION_9_MASON_WORK_OBELISK;
        mason->wait_ticks = 0;
    }
}

bool building_alexandria_library::work_tick(figure &f) {
    building_alexandria_library *m = main_library();
    if (!m) {
        return true;
    }

    if (all_parts_prepared()) {
        // Spot work on main.
        if (m != this) {
            return m->work_tick(f);
        }
        if (is_finished() || part_stage() >= LIBRARY_STAGE_COMPLETE) {
            return true;
        }
        if (part_stage() < LIBRARY_STAGE_BUILDING) {
            return true;
        }

        const auto &spots = lib_params().spots;
        const int s = part_stage();
        int spot = -1;
        for (int i = 0; i < (int)spots.size() && i < LIBRARY_WORK_SPOTS; ++i) {
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

        // OG: mason WAIT_FOR_BLOCK until FRAME_COUNT sleds arrive (on_material_delivered wakes to WORK).
        if (f.type == FIGURE_STONEMASON && f.action_state == ACTION_19_MASON_WAIT_FOR_BLOCK) {
            if (spot_attached(spot) != f.id) {
                set_spot(spot, (uint16_t)spot_work_left(spot), f.id);
            }
            return false;
        }

        const int left = std::max(0, spot_work_left(spot) - 1);
        set_spot(spot, (uint16_t)left, left > 0 ? f.id : 0);
        if (left > 0) {
            return false;
        }
        for (int i = 0; i < (int)spots.size() && i < LIBRARY_WORK_SPOTS; ++i) {
            if (spots[i].stage == s && spot_work_left(i) > 0) {
                clear_worker_figure();
                return true;
            }
        }
        clear_worker_figure();
        advance_all_parts();
        return true;
    }

    // Prep: laborer levels this part.
    if (f.type != FIGURE_LABORER || part_stage() >= LIBRARY_STAGE_PREPARED) {
        clear_worker_figure();
        return true;
    }
    f.wait_ticks++;
    if (f.wait_ticks <= LIBRARY_LABORER_WORK_TICKS) {
        return false;
    }
    f.wait_ticks = 0;
    set_phase(LIBRARY_STAGE_PREPARED);
    update_part_image();
    clear_worker_figure();

    if (all_parts_prepared()) {
        // Jump shared stage to BUILDING (3).
        for (int i = 0; i < parts_count(); ++i) {
            if (auto *p = m->part(i)) {
                p->set_phase(LIBRARY_STAGE_BUILDING);
                p->update_part_image();
                p->base.road_access = p->work_tile();
            }
        }
        m->reset_spots();
        m->refresh_part_images();
    }
    return true;
}

bool building_alexandria_library::check_work_for_figure(figure_id fid, bool assign) {
    figure *f = figure_get(fid);
    if (!f) {
        return false;
    }

    building_alexandria_library *target = this;
    if (part_stage() >= LIBRARY_STAGE_BUILDING) {
        target = main_library();
    }
    if (!target) {
        return false;
    }

    if (f->type == FIGURE_LABORER) {
        const int stage = target->part_stage();
        if (stage < LIBRARY_STAGE_PREPARED) {
            if (target->part_has_active_worker()) {
                return false;
            }
            // Assign on this part (may be a side part still at STARTED).
            if (part_stage() >= LIBRARY_STAGE_PREPARED || part_has_active_worker()) {
                return false;
            }
            if (assign) {
                f->action_state = ACTION_32_LABORER_TO_LIBRARY;
                set_worker_figure(fid);
                send_to_part(*f);
            }
            return true;
        }
        if (stage < LIBRARY_STAGE_BUILDING) {
            return false;
        }
        if (!target->part_has_active_worker()) {
            return false;
        }
        figure *worker = figure_get(target->worker_figure_id());
        if (!worker || worker->type != FIGURE_STONEMASON
            || worker->action_state != ACTION_19_MASON_WAIT_FOR_BLOCK) {
            return false;
        }
        // Material sled partner (OG: only while mason WAIT_FOR_BLOCK).
        if (worker->leading_figure_id) {
            figure *partner = figure_get(worker->leading_figure_id);
            if (partner && partner->is_alive() && partner->type == FIGURE_LABORER) {
                return false;
            }
            worker->leading_figure_id = 0;
        }
        if (!assign) {
            return true;
        }
        const e_resource res = material_for_stage(stage);
        tile2i yard_tile;
        building_id storage_id = 0;
        for (building &b : city_buildings()) {
            if (!b.is_valid() || b.type != BUILDING_STORAGE_YARD) {
                continue;
            }
            if (b.stored_amount(res) < 1) {
                continue;
            }
            storage_id = b.id;
            yard_tile = b.road_access.valid() ? b.road_access : b.tile;
            break;
        }
        if (!storage_id) {
            f->poof();
            return true;
        }
        f->collecting_item_id = res;
        f->resource_amount_full = 0;
        f->destination_building_id = storage_id;
        f->leading_figure_id = worker->id;
        f->action_state = ACTION_15_LABORER_TO_STORAGE_YARD;
        f->wait_ticks = 0;
        f->destination_tile = yard_tile;
        if (auto *w = f->dcast_worker()) {
            w->runtime_data().mason_fid = worker->id;
            w->runtime_data().yard_bid = storage_id;
        }
        worker->leading_figure_id = fid;
        return true;
    }

    if (target->part_has_active_worker()) {
        return false;
    }
    if (target->part_stage() < LIBRARY_STAGE_BUILDING) {
        return false;
    }
    if (!target->has_free_spot(f->type)) {
        return false;
    }
    if (assign) {
        if (f->type == FIGURE_CARPENTER) {
            f->action_state = ACTION_2_CARPENTER_WORK;
        } else if (f->type == FIGURE_STONEMASON) {
            f->action_state = ACTION_1_MASON_GOING;
        } else {
            return false;
        }
        target->set_worker_figure(fid);
        f->destination_tile = target->work_tile();
        // OG routes guild workers via main_id + 15.
        building_alexandria_library *dest_part = target->part(LIBRARY_SPOT_DESTINATION_OFFSET);
        f->destination_building_id = dest_part ? dest_part->id() : target->id();
        f->wait_ticks = 0;
        f->roam_length = 0;
    }
    return true;
}

int building_alexandria_library::find_work_for_figure(figure_id fid) {
    for (building &b : city_buildings()) {
        if (!b.is_valid() || b.type != BUILDING_ALEXANDRIA_LIBRARY) {
            continue;
        }
        auto *lib = b.dcast_alexandria_library();
        if (lib && lib->check_work_for_figure(fid, true)) {
            return b.id;
        }
    }
    return 0;
}

int building_alexandria_library::get_progress(int *out) const {
    const building_alexandria_library *m = main_library();
    const int stage = m->part_stage();
    int percent = 100;
    if (stage < LIBRARY_STAGE_COMPLETE && stage != MONUMENT_FINISHED) {
        percent = (int)((double)stage * (1.0 / LIBRARY_STAGE_COMPLETE) * 100.0);
    }
    int masons = 0, waiting = 0, laborers = 0, carpenters = 0;
    if (m->part_has_active_worker()) {
        figure *f = figure_get(m->worker_figure_id());
        if (!f) {
            return 0;
        }
        if (f->type == FIGURE_CARPENTER) {
            carpenters = 1;
        } else if (f->type == FIGURE_STONEMASON) {
            masons = 1;
            if (f->action_state == ACTION_19_MASON_WAIT_FOR_BLOCK) {
                waiting = 1;
            }
        } else if (f->type == FIGURE_LABORER) {
            laborers = 1;
        }
    }
    int material = LIBRARY_MATERIAL_LOADS * LIBRARY_MATERIAL_PER_LOAD;
    if (stage > LIBRARY_STAGE_BUILDING) {
        material = (LIBRARY_MATERIAL_LOADS - ((stage - LIBRARY_STAGE_BUILDING) * LIBRARY_FRAME_COUNT)) * LIBRARY_MATERIAL_PER_LOAD;
        if (material < 0) {
            material = 0;
        }
    }
    if (out) {
        out[LIBRARY_PROGRESS_STATUS] = stage >= LIBRARY_STAGE_COMPLETE ? 3 : (stage >= LIBRARY_STAGE_BUILDING ? 2 : 1);
        out[LIBRARY_PROGRESS_PERCENT] = percent;
        out[LIBRARY_PROGRESS_STONEMASONS] = masons;
        out[LIBRARY_PROGRESS_STONEMASONS_WAITING] = waiting;
        out[LIBRARY_PROGRESS_LABORERS] = laborers;
        out[LIBRARY_PROGRESS_CARPENTERS] = carpenters;
        out[LIBRARY_PROGRESS_MATERIAL] = material;
        out[LIBRARY_PROGRESS_MATERIAL_TOTAL] = LIBRARY_MATERIAL_LOADS * LIBRARY_MATERIAL_PER_LOAD;
    }
    return percent;
}

void building_alexandria_library::update_part_image() {
    bool is_front = false;
    const int img = resolve_image(&is_front);
    const int sz = std::max(1, (int)part_desc(part_index()).size);
    const int leveled_base = std::max(0, current_params().first_img(lib_params().leveled));
    const bool is_leveled = img > 0 && leveled_base > 0 && img == leveled_base;
    // OG library_image_flags: only blank / leveled / FRONT are PER_TILE.
    const bool per_tile = img <= 0 || is_leveled || is_front;

    if (!per_tile) {
        map_building_tiles_add(id(), tile(), sz, img, TERRAIN_BUILDING);
        return;
    }

    // OG library_update_image PER_TILE: no map_building_tiles_add — every tile draws
    // on its own (size 1, DRAW_TILE), FRONT may keep prior images on edge tiles.
    std::array<int, 64> ground{};
    if (is_front || img <= 0) {
        for (int dy = 0; dy < sz; ++dy) {
            for (int dx = 0; dx < sz; ++dx) {
                ground[dy * sz + dx] = map_image_at(tile().shifted(dx, dy));
            }
        }
    }

            const int part = part_index();
    for (int dy = 0; dy < sz; ++dy) {
        for (int dx = 0; dx < sz; ++dx) {
            tile2i t = tile().shifted(dx, dy);
            const int go = t.grid_offset();
            map_terrain_remove(go, TERRAIN_CLEARABLE);
            map_terrain_add(go, TERRAIN_BUILDING);
            map_building_set(go, id());
            map_property_clear_constructing(go);
            map_property_set_multi_tile_size(go, 1);
            map_property_clear_multi_tile_xy(go);
            map_property_mark_draw_tile(go);

            if (is_front && keeps_front_tile_image(part, dy, dx)) {
                map_image_set(t, ground[dy * sz + dx]);
                continue;
            }
            if (img <= 0) {
                map_image_set(t, ground[dy * sz + dx]);
            } else if (is_leveled) {
                map_image_set(t, leveled_base + (map_random_get(t) % 8));
            } else {
                map_image_set(t, img);
            }
        }
    }
}

void building_alexandria_library::refresh_part_images() {
    // Match OG: scripted Extra/Extra2 loads first in part order; NONE piggybacks.
    g_library_extra_pack = 0;
    for (int i = 0; i < parts_count(); ++i) {
        if (auto *p = part(i)) {
            p->update_part_image();
        }
    }
}

void building_alexandria_library::animate_spots() {
    const int now = game.simtime.absolute_tick();
    int steps = (g_spot_anim_tick < 0) ? 1 : std::clamp(now - g_spot_anim_tick, 0, 64);
    g_spot_anim_tick = now;
    const int view = camera_view();
    const auto &spots = lib_params().spots;
    for (int i = 0; i < (int)spots.size() && i < LIBRARY_WORK_SPOTS; ++i) {
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

bool building_alexandria_library::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile,
  color color_mask) {
    if (!is_main() || is_finished() || tile != base.tile) {
        return false;
    }
    animate_spots();

    const int view = camera_view();
    const auto &params = lib_params();
    const auto &spots = params.spots;
    bool drew = false;

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

    for (int i = 0; i < (int)spots.size() && i < LIBRARY_WORK_SPOTS; ++i) {
        const auto &a = g_spot_anims[i];
        const library_anim_script *sc = anim_script(spots[i].script);
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
        const vec2i from = view_point(seq.from_views, view);
        const vec2i to = view_point(seq.to_views, view);
        const vec2i offset = params.anim_offset;
        const int x = (to.x - from.x) * a.frame / seq.frames + offset.x + from.x;
        const int y = (to.y - from.y) * a.frame / seq.frames + offset.y + from.y;
        const int add = (view < (int)seq.add.size()) ? seq.add[view] : 0;
        const int image_id = base_img + img.offset + add + (a.frame % std::max<int>(1, img.frames)) * img.step;
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

int building_alexandria_library::building_image_get() const {
    return resolve_image(nullptr);
}

int building_alexandria_library::resolve_image(bool *is_front) const {
    if (is_front) {
        *is_front = false;
    }

    int stage = part_stage();
    if (stage > LIBRARY_STAGE_PREPARED) {
        stage = main_library()->part_stage();
    }

    const auto *step = find_image_step(part_desc(part_index()).kind, stage);
    if (!step) {
        return 0;
    }

    const int view = g_camera.orientation / 2;
    const bool south = view >= LIBRARY_VIEW_SOUTH_FIRST;
    const xstring &key = south ? step->south : step->north;
    const xstring &script = south ? step->south_script : step->north_script;
    const bool odd = south ? step->south_odd : step->north_odd;

    if (is_front) {
        *is_front = key == "front";
    }

    int image = resolve_step_image(current_params(), key, script);
    if (image > 0 && odd) {
        image += view & 1;
    }
    return image;
}

bool building_alexandria_library::needs_resources() const {
    if (is_finished()) {
        return false;
    }
    const int stage = main_library()->part_stage();
    return stage >= LIBRARY_STAGE_BUILDING && stage < LIBRARY_STAGE_COMPLETE;
}

bool building_alexandria_library::need_stonemason() {
    if (is_finished()) {
        return false;
    }
    building_alexandria_library *m = main_library();
    if (!m->all_parts_prepared()) {
        return false;
    }
    return m->has_free_spot(FIGURE_STONEMASON) && !m->part_has_active_worker();
}

bool building_alexandria_library::need_carpenter() {
    if (is_finished()) {
        return false;
    }
    building_alexandria_library *m = main_library();
    if (!m->all_parts_prepared()) {
        return false;
    }
    return m->has_free_spot(FIGURE_CARPENTER) && !m->part_has_active_worker();
}

bool building_alexandria_library::need_workers() const {
    if (is_finished()) {
        return false;
    }
    const building_alexandria_library *m = main_library();
    if (!m->all_parts_prepared()) {
        for (int i = 0; i < parts_count(); ++i) {
            const auto *p = m->part(i);
            if (p && p->part_stage() < LIBRARY_STAGE_PREPARED && !p->part_has_active_worker()) {
                return true;
            }
        }
        return false;
    }
    return m->has_free_spot(FIGURE_STONEMASON) || m->has_free_spot(FIGURE_CARPENTER)
        || (m->part_has_active_worker() && material_for_stage(m->part_stage()) != RESOURCE_NONE);
}

void building_alexandria_library::add_workers(figure_id fid) {
    if (!worker_figure_id()) {
        set_worker_figure(fid);
    }
}

void building_alexandria_library::remove_worker(figure_id fid) {
    if (worker_figure_id() == fid) {
        clear_worker_figure();
    }
    for (int i = 0; i < LIBRARY_WORK_SPOTS; ++i) {
        if (spot_attached(i) == fid) {
            set_spot(i, (uint16_t)spot_work_left(i), 0);
        }
    }
}

void building_alexandria_library::preview::setup_preview_graphics(build_planner &planer) const {
    const vec2i ext = box_extent();
    planer.init_tiles(std::max(1, ext.x), std::max(1, ext.y));
}

int building_alexandria_library::preview::can_place(build_planner &p, tile2i /*tile*/, tile2i end, int state) const {
    if (state != CAN_PLACE && state != CAN_NOT_BUT_GREEN) {
        return state;
    }
    if (has_unfinished_alexandria_library()) {
        p.set_warning("#one_library_only");
        return CAN_NOT_PLACE;
    }
    for (int i = 0; i < parts_count(); ++i) {
        if (!area_for_part_free(end, part_desc(i))) {
            return CAN_NOT_PLACE;
        }
    }
    return CAN_PLACE;
}

int building_alexandria_library::preview::finalize_check(build_planner &p, tile2i tile, tile2i end, int state) const {
    state = building_planer_renderer::finalize_check(p, tile, end, state);
    if (state != CAN_PLACE) {
        return state;
    }
    if (has_unfinished_alexandria_library()) {
        p.set_warning("#one_library_only");
        g_warning_manager.show("#one_library_only");
        return CAN_NOT_PLACE;
    }
    return can_place(p, tile, end, CAN_PLACE);
}

int building_alexandria_library::preview::construction_place(build_planner &planer, tile2i tile, tile2i end, int orientation,
  int variant) const {
    const int placed = building_planer_renderer::construction_place(planer, tile, end, orientation, variant);
    if (placed && planer.last_created_building && !planer.last_created_building->is_valid()) {
        planer.last_created_building = nullptr;
        return 0;
    }
    return placed;
}

void building_alexandria_library::preview::ghost_preview(build_planner &planer, painter &ctx, tile2i /*start*/, tile2i end,
  vec2i /*pixel*/) const {
    const auto &params = building_static_params::get(planer.build_type);
    const int preview = params.first_img("preview");
    const int img_body = params.first_img("main_a5");
    bool blocked = has_unfinished_alexandria_library();
    if (!blocked) {
        for (int i = 0; i < parts_count(); ++i) {
            if (!area_for_part_free(end, part_desc(i))) {
                blocked = true;
                break;
            }
        }
    }
    for (int i = 0; i < parts_count(); ++i) {
        const auto &d = part_desc(i);
        tile2i t = end.shifted(d.offset.x, d.offset.y);
        if (blocked) {
            draw_area_mask(ctx, t, d.size, d.size, true);
        } else if (d.kind == 0) {
            planer.draw_building_ghost(ctx, img_body > 0 ? img_body : preview, g_camera.lookup_tile_to_pixel(t));
        } else {
            draw_area_mask(ctx, t, d.size, d.size, false);
        }
    }
}

void building_alexandria_library::on_place(int orientation, int variant) {
    building_impl::on_place(orientation, variant);
}

void building_alexandria_library::on_place_update_tiles(int /*orientation*/, int /*variant*/) {
    base.prev_part_building_id = 0;
    runtime_data().variant = 0;
    runtime_data().phase = LIBRARY_STAGE_STARTED;
    runtime_data().material_frame = 0;
    base.orientation = 0;
    base.size = part_desc(0).size;

    const auto &d0 = part_desc(0);
    if (d0.offset.x != 0 || d0.offset.y != 0) {
        tile2i desired = tile().shifted(d0.offset.x, d0.offset.y);
        map_building_tiles_remove(id(), tile());
        base.tile = desired;
        base.size = d0.size;
    }
    base.road_access = work_tile();
    update_part_image();

    building *prev = &base;
    bool ok = true;
    for (int part_i = 1; part_i < parts_count(); ++part_i) {
        const auto &d = part_desc(part_i);
        tile2i origin = tile().shifted(-d0.offset.x, -d0.offset.y);
        tile2i part_tile = origin.shifted(d.offset.x, d.offset.y);
        building *b = building_create(BUILDING_ALEXANDRIA_LIBRARY, part_tile, 0);
        if (!b || b->id <= 0) {
            ok = false;
            break;
        }
        game_undo_add_building(b);
        auto *lp = b->dcast_alexandria_library();
        if (lp) {
            lp->runtime_data().variant = (uint8_t)part_i;
            lp->runtime_data().phase = LIBRARY_STAGE_STARTED;
            lp->runtime_data().material_frame = 0;
            lp->base.road_access = lp->work_tile();
            lp->update_part_image();
        }
        b->orientation = 0;
        b->size = d.size;
        b->prev_part_building_id = prev->id;
        b->next_part_building_id = 0;
        prev->next_part_building_id = b->id;
        prev = b;
    }

    if (!ok) {
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

void building_alexandria_library::on_post_load() {
    building_monument::on_post_load();
    if (!is_main()) {
        return;
    }
    if (work_spots().any_unset()) {
        reset_spots();
        const auto &defs = lib_params().spots;
        const int s = part_stage();
        for (int i = 0; i < (int)defs.size() && i < LIBRARY_WORK_SPOTS; ++i) {
            if (defs[i].stage < s) {
                set_spot(i, 0, 0);
            }
        }
    }
    refresh_part_images();
}

void building_alexandria_library::on_destroy() {
    if (is_main()) {
        work_spots().mark_unset();
    }
}

void building_alexandria_library::update_day() {
    building_impl::update_day();
    if (!is_main() || is_finished()) {
        return;
    }
    scrub_spots();
    if (part_stage() >= LIBRARY_STAGE_COMPLETE) {
        finish_all();
    }
}

void building_alexandria_library::update_map_orientation(int /*map_orientation*/) {
    main_library()->refresh_part_images();
}

tile2i building_alexandria_library::center_point() const {
    grid_area area = get_area();
    return tile2i((area.tmin().x() + area.tmax().x()) / 2, (area.tmin().y() + area.tmax().y()) / 2);
}

tile2i building_alexandria_library::access_point() const {
    return main_library()->work_tile();
}

grid_area building_alexandria_library::get_area() const {
    const building_alexandria_library *m = main_library();
    tile2i start = m->tile();
    tile2i end = start;
    for (int i = 0; i < parts_count(); ++i) {
        auto *p = const_cast<building_alexandria_library *>(m)->part(i);
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

void building_alexandria_library::bind_dynamic(io_buffer *iob, size_t /*version*/) {
    auto &d = runtime_data();
    // Building record budget: header (~82) + bind_dynamic <= 186 → max ~104 for dynamic.
    // Sun temple fits 13 spots (1+52+51=104). Library's 24 spots (1+96+51=148) overflow and
    // zero phase on load. Keep the legacy 38-byte hole; rebuild spots from stage on post_load.
    if (is_main()) {
        iob->bind(BIND_SIGNATURE_UINT8, &d.material_frame);
        iob->bind____skip(37);
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

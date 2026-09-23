#include "monument_obelisk.h"

#include "building/monuments.h"
#include "city/city.h"
#include "city/city_resource.h"
#include "city/city_warnings.h"
#include "construction/build_planner.h"
#include "core/archive.h"
#include "figure/figure.h"
#include "figure/figure_type.h"
#include "game/game_events.h"
#include "game/resource.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "grid/building_tiles.h"
#include "grid/road_access.h"
#include "grid/terrain.h"
#include "io/gamefiles/lang.h"
#include "io/io_buffer.h"
#include "js/js_game.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_obelisk);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_large_obelisk);

static monument g_monument_small_obelisk{BUILDING_SMALL_OBELISK};
static monument g_monument_large_obelisk{BUILDING_LARGE_OBELISK};

void building_obelisk::static_params::rebuild_construction(e_building_type type) {
    monument &m = (type == BUILDING_LARGE_OBELISK) ? g_monument_large_obelisk : g_monument_small_obelisk;
    m.btype = type;
    m.phases.clear();

    for (int i = 0; i < (int)stages.size(); ++i) {
        const auto &st = stages[i];
        if (st.timber > 0) {
            m.phases.push_back({(uint8_t)i, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, st.timber}});
        } else {
            m.phases.push_back({(uint8_t)i, monument_phase_resource{ARCHITECTS, 1}});
        }
    }
    m.phases.push_back({(uint8_t)stages.size(), monument_phase_resource{RESOURCE_NONE, 0}});
}

void building_small_obelisk::static_params::archive_load(archive /*arch*/) {
    rebuild_construction(BUILDING_SMALL_OBELISK);
}

void building_large_obelisk::static_params::archive_load(archive /*arch*/) {
    rebuild_construction(BUILDING_LARGE_OBELISK);
}

const monument &building_small_obelisk::config() const {
    return g_monument_small_obelisk;
}

const monument &building_large_obelisk::config() const {
    return g_monument_large_obelisk;
}

static const building_obelisk::base_params &obelisk_params_for(e_building_type t) {
    if (t == BUILDING_LARGE_OBELISK) {
        return (const building_obelisk::base_params &)building_large_obelisk::current_params();
    }
    return (const building_obelisk::base_params &)building_small_obelisk::current_params();
}

void building_obelisk::scrub_dead_workers() {
    for (auto &wid : runtime_data().workers) {
        if (!wid) {
            continue;
        }
        figure *f = figure_get(wid);
        if (!f || !f->is_alive()) {
            wid = 0;
        }
    }
}

bool building_obelisk::has_live_worker(e_figure_type type) const {
    for (auto wid : runtime_data().workers) {
        figure *f = wid > 0 ? figure_get(wid) : nullptr;
        if (f && f->is_alive() && f->type == type) {
            return true;
        }
    }
    return false;
}

const obelisk_stage *building_obelisk::stage_at(int phase) const {
    const auto &bp = obelisk_params_for(base.type);
    if (phase < 0 || phase >= (int)bp.stages.size()) {
        return nullptr;
    }
    return &bp.stages[phase];
}

const obelisk_stage *building_obelisk::current_stage() const {
    if (is_finished()) {
        return nullptr;
    }
    return stage_at(runtime_data().phase);
}

vec2i building_obelisk::carpenter_work_pixel() const {
    const auto *st = current_stage();
    return st ? st->carpenter_point : vec2i{};
}

vec2i building_obelisk::stonemasons_work_pixel() const {
    const auto *st = current_stage();
    return st ? st->stonemasons_point : vec2i{};
}

void building_obelisk::set_carpenter_works(figure_id fid) {
    runtime_data().carpenter_works = fid;
}

void building_obelisk::set_stonemason_works(figure_id fid) {
    runtime_data().stonemason_works = fid;
}

figure_id building_obelisk::carpenter_works() const {
    return runtime_data().carpenter_works;
}

figure_id building_obelisk::stonemason_works() const {
    return runtime_data().stonemason_works;
}

static int placement_amount_for(e_building_type t, e_resource r) {
    const auto &bp = obelisk_params_for(t);
    for (const auto &pr : bp.placement_resources) {
        if (pr.resource == r) {
            return pr.count;
        }
    }
    return 0;
}

int building_obelisk::placement_amount(e_resource r) const {
    return placement_amount_for(base.type, r);
}

int building_obelisk::yards_available(e_resource r) {
    return g_city.resource.yards_stored_staffed(r);
}

bool building_obelisk::has_unfinished_obelisk() {
    return building_monument_has_unfinished({BUILDING_SMALL_OBELISK, BUILDING_LARGE_OBELISK});
}

int building_obelisk::art_stage() const {
    const auto &bp = obelisk_params_for(base.type);
    const int max_stage = bp.art_stages > 0 ? bp.art_stages : 4;
    const int p = runtime_data().phase;
    if (p == MONUMENT_FINISHED || p >= max_stage) {
        return max_stage;
    }
    if (p <= 1) {
        return 1;
    }
    return std::min(p, max_stage);
}

xstring building_obelisk::anim_key_for(int stage) const {
    const auto &bp = obelisk_params_for(base.type);
    const int max_stage = bp.art_stages > 0 ? bp.art_stages : 4;
    if (stage < 1) {
        stage = 1;
    }
    if (stage > max_stage) {
        stage = max_stage;
    }
    bstring32 key;
    key.printf("s%c", 'a' + (stage - 1));
    return xstring(key.c_str());
}

bool building_obelisk::needs_resources() const {
    if (is_finished()) {
        return false;
    }
    auto &d = runtime_data();
    for (e_resource r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
        if (needs_resource(r) <= 0) {
            continue;
        }
        if (d.resources_pct[r] < 100) {
            return true;
        }
    }
    return false;
}

bool building_obelisk::need_stonemason() {
    if (is_finished()) {
        return false;
    }
    const auto *st = current_stage();
    return st && st->stonemasons_need;
}

bool building_obelisk::need_carpenter() {
    if (is_finished()) {
        return false;
    }
    scrub_dead_workers();
    const auto *st = current_stage();
    if (!st || !st->carpenter_need) {
        return false;
    }
    const int need = needs_resource(RESOURCE_TIMBER);
    if (need <= 0) {
        return false;
    }
    if (resource_pct(RESOURCE_TIMBER) >= 100) {
        return false;
    }
    if (yards_available(RESOURCE_TIMBER) < need) {
        return false;
    }
    if (has_live_worker(FIGURE_CARPENTER)) {
        return false;
    }
    return has_free_worker_slot();
}

bool building_obelisk::accepts_yard_delivery(e_resource resource) const {
    return resource != RESOURCE_TIMBER;
}

void building_obelisk::add_workers(figure_id fid) {
    scrub_dead_workers();
    auto &d = runtime_data();
    for (auto &wid : d.workers) {
        if (wid == 0) {
            wid = fid;
            return;
        }
    }
}

void building_obelisk::remove_worker(figure_id fid) {
    auto &d = runtime_data();
    for (auto &wid : d.workers) {
        if (wid == fid) {
            wid = 0;
            return;
        }
    }
}

bool building_obelisk::place_scaffold() {
    if (is_finished()) {
        return false;
    }
    const auto *st = current_stage();
    if (!st || !st->carpenter_need) {
        return false;
    }
    const int need = needs_resource(RESOURCE_TIMBER);
    if (need <= 0) {
        return false;
    }
    if (resource_pct(RESOURCE_TIMBER) >= 100) {
        return false;
    }
    if (yards_available(RESOURCE_TIMBER) < need) {
        return false;
    }
    events::emit(event_city_remove_resource{RESOURCE_TIMBER, need, /*staffed_only*/true});
    return deliver_resource(RESOURCE_TIMBER, need);
}

void building_obelisk::on_phase_changed(int /*old_phase*/, int current) {
    const int size = base.size > 0 ? base.size : 3;
    map_building_tiles_add(id(), tile(), size, building_image_get(), TERRAIN_BUILDING);

    if (current != MONUMENT_FINISHED) {
        auto &d = runtime_data();
        for (e_resource resource = RESOURCE_NONE; resource < RESOURCES_MAX; ++resource) {
            d.resources_pct[resource] = 0;
        }
    }
}

bool building_obelisk::need_workers() const {
    return false;
}

int building_obelisk::building_image_get() const {
    const auto &bp = obelisk_params_for(base.type);
    int phase = runtime_data().phase;
    if (is_finished() || phase < 0 || phase >= (int)bp.stages.size()) {
        phase = std::max(0, (int)bp.stages.size() - 1);
    }
    if (const auto *st = stage_at(phase)) {
        if (st->obelisk_tx.valid()) {
            image_desc desc = st->obelisk_tx;
            const int img = desc.tid();
            if (img > 0) {
                return img;
            }
        }
    }

    const xstring key = anim_key_for(art_stage());
    const auto &params = building_static_params::get(base.type);
    int img = params.first_img(key);
    if (img > 0) {
        return img;
    }
    return params.first_img("preview");
}

static xstring granite_need_warning(e_building_type t, int need) {
    const int lang_id = (t == BUILDING_LARGE_OBELISK) ? 84 : 83;
    pcstr tmpl = lang_get_string(19, lang_id);
    bstring256 msg;
    if (tmpl && tmpl[0]) {
        msg.printf(tmpl, need);
    } else {
        msg.printf("You need %d blocks of granite to build an obelisk", need);
    }
    return xstring(msg.c_str());
}

int building_obelisk::preview::finalize_check(build_planner &p, tile2i tile, tile2i end, int state) const {
    state = building_planer_renderer::finalize_check(p, tile, end, state);
    if (state != CAN_PLACE) {
        return state;
    }
    if (has_unfinished_obelisk()) {
        p.set_warning("#only_one_obelisk_at_a_time");
        return CAN_NOT_PLACE;
    }
    const int need = placement_amount_for(p.build_type, RESOURCE_GRANITE);
    if (need > 0 && yards_available(RESOURCE_GRANITE) < need) {
        const xstring msg = granite_need_warning(p.build_type, need);
        p.set_warning(msg);
        g_warning_manager.show_custom(msg.c_str());
        return CAN_NOT_PLACE;
    }
    return CAN_PLACE;
}

void building_obelisk::preview::ghost_preview(build_planner &planer, painter &ctx, tile2i /*start*/, tile2i /*end*/, vec2i pixel) const {
    const auto &params = building_static_params::get(planer.build_type);
    int img = 0;
    const auto &bp = (planer.build_type == BUILDING_LARGE_OBELISK)
        ? (const building_obelisk::base_params &)building_large_obelisk::current_params()
        : (const building_obelisk::base_params &)building_small_obelisk::current_params();
    if (!bp.stages.empty() && bp.stages[0].obelisk_tx.valid()) {
        image_desc desc = bp.stages[0].obelisk_tx;
        img = desc.tid();
    }
    if (img <= 0) {
        img = params.first_img("preview");
    }
    planer.draw_building_ghost(ctx, img, pixel);
}

void building_obelisk::on_place_update_tiles(int /*orientation*/, int /*variant*/) {
    const int size = base.size > 0 ? base.size : 3;
    map_building_tiles_add(id(), tile(), size, building_image_get(), TERRAIN_BUILDING);
}

void building_obelisk::on_destroy() {
    building_monument_remove_all_deliveries(id());
}

void building_obelisk::update_day() {
    building_impl::update_day();
    runtime_data().carpenter_works = 0;
    runtime_data().stonemason_works = 0;
    if (is_finished()) {
        return;
    }
    scrub_dead_workers();
    const auto *st = current_stage();

    if (st && st->stonemasons_need && !st->carpenter_need) {
        return;
    }
    progress();
}

void building_obelisk::stonemason_complete_work() {
    if (is_finished()) {
        return;
    }
    const auto *st = current_stage();
    if (!st || !st->stonemasons_need) {
        return;
    }
    progress();
}

void building_obelisk::update_map_orientation(int /*map_orientation*/) {
    const int size = base.size > 0 ? base.size : 3;
    map_building_tiles_add(id(), tile(), size, building_image_get(), TERRAIN_BUILDING);
}

bool building_obelisk::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i /*tile*/, color color_mask) {
    if (is_finished()) {
        return false;
    }

    bool drew = false;
    const int phase = runtime_data().phase;
    const auto *st = stage_at(phase);
    // Draw current-phase ladders (no previous-stage fallback) so --mixed edits are visible.
    const auto *ladder_st = st;

    const int ladder_img = building_static_params::get(base.type).first_img("ladder");

    if (ladder_st && !ladder_st->ladders.empty()) {
        if (ladder_img > 0) {
            for (const auto &off : ladder_st->ladders) {
                auto &command = ImageDraw::create_subcommand(ctx, render_command_t::ert_drawtile);
                command.image_id = ladder_img;
                command.pixel = point + off;
                command.mask = color_mask;
            }
            drew = true;
        }
    }

    if (!st) {
        return drew;
    }

    const auto draw_worker = [&](figure_id fid, vec2i work_off) {
        figure *f = fid > 0 ? figure_get(fid) : nullptr;
        if (!f || !f->is_alive() || f->main_image_id <= 0) {
            return;
        }
        auto &command = ImageDraw::create_subcommand(ctx, render_command_t::ert_sprite);
        command.image_id = f->main_image_id;
        command.pixel = point + work_off;
        command.mask = color_mask;
        drew = true;
    };

    if (st->carpenter_need) {
        draw_worker(carpenter_works(), st->carpenter_point);
    }
    if (st->stonemasons_need) {
        draw_worker(stonemason_works(), st->stonemasons_point);
    }

    return drew;
}

tile2i building_obelisk::center_point() const {
    const int s = base.size > 0 ? base.size : 3;
    return tile().shifted(s / 2, s / 2);
}

tile2i building_obelisk::access_point() const {
    if (base.road_access.valid()) {
        return base.road_access;
    }
    const int s = base.size > 0 ? base.size : 3;
    tile2i road = map_get_road_access_tile(tile(), s);
    if (road.valid()) {
        return road;
    }
    int x = 0, y = 0;
    if (map_terrain_get_adjacent_road_or_clear_land(tile().x(), tile().y(), s, &x, &y)) {
        return tile2i(x, y);
    }
    return tile2i::invalid;
}

void building_obelisk::bind_dynamic(io_buffer *iob, size_t /*version*/) {
    auto &monumentd = runtime_data();

    iob->bind____skip(38);
    iob->bind(BIND_SIGNATURE_UINT8, &base.orientation);
    for (int i = 0; i < 5; i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &monumentd.workers[i]);
    }
    iob->bind(BIND_SIGNATURE_UINT8, &monumentd.phase);
    iob->bind(BIND_SIGNATURE_UINT8, &monumentd.funeral_done);
    iob->bind(BIND_SIGNATURE_UINT8, &monumentd.preexisting);
    iob->bind(BIND_SIGNATURE_UINT8, &monumentd.variant);

    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &monumentd.resources_pct[i]);
    }
}

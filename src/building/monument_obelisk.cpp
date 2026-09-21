#include "monument_obelisk.h"

#include "building/monuments.h"
#include "city/city.h"
#include "city/city_resource.h"
#include "city/city_warnings.h"
#include "construction/build_planner.h"
#include "figure/figure.h"
#include "figure/figure_type.h"
#include "game/game_events.h"
#include "game/resource.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "grid/building_tiles.h"
#include "io/gamefiles/lang.h"
#include "io/io_buffer.h"
#include "js/js_game.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_obelisk);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_large_obelisk);

// Filled from JS timber_loads (+ art_stages) on config load / --mixed reload.
static monument g_monument_small_obelisk{BUILDING_SMALL_OBELISK};
static monument g_monument_large_obelisk{BUILDING_LARGE_OBELISK};

void building_obelisk::static_params::rebuild_construction(e_building_type type) {
    monument &m = (type == BUILDING_LARGE_OBELISK) ? g_monument_large_obelisk : g_monument_small_obelisk;
    m.btype = type;
    m.phases.clear();

    const int stages = art_stages > 0 ? art_stages : 4;
    for (int i = 0; i < stages; ++i) {
        const uint16_t timber = (i < (int)timber_loads.size()) ? timber_loads[i] : 0;
        if (timber > 0) {
            m.phases.push_back({(uint8_t)i, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, timber}});
        } else {
            m.phases.push_back({(uint8_t)i, monument_phase_resource{ARCHITECTS, 1}});
        }
    }
    m.phases.push_back({(uint8_t)stages, monument_phase_resource{RESOURCE_NONE, 0}});
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

int building_obelisk::max_scaffolds() const {
    const auto &bp = obelisk_params_for(base.type);
    if (!bp.scaffold_offsets.empty()) {
        return (int)bp.scaffold_offsets.size();
    }
    int n = 0;
    for (uint16_t load : bp.timber_loads) {
        n += (load > 0) ? 1 : 0;
    }
    return std::max(1, n);
}

vec2i building_obelisk::scaffold_pixel_offset(int i) const {
    const auto &bp = obelisk_params_for(base.type);
    if (i >= 0 && i < (int)bp.scaffold_offsets.size()) {
        return bp.scaffold_offsets[i];
    }
    return vec2i{20 + i * 16, -40};
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
    if (needs_resource(RESOURCE_TIMBER) > 0) {
        return false;
    }
    const auto &bp = obelisk_params_for(base.type);
    const int max_stage = bp.art_stages > 0 ? bp.art_stages : 4;
    return runtime_data().phase < max_stage;
}

bool building_obelisk::need_carpenter() {
    if (is_finished()) {
        return false;
    }
    scrub_dead_workers();
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

int building_obelisk::scaffold_count() const {
    if (is_finished()) {
        return 0;
    }
    const int placed = (int)runtime_data().phase;
    const int extra = (needs_resource(RESOURCE_TIMBER) > 0 && resource_pct(RESOURCE_TIMBER) >= 100) ? 1 : 0;
    return std::min(placed + extra, max_scaffolds());
}

bool building_obelisk::place_scaffold() {
    if (is_finished()) {
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
    const int preview = params.first_img("preview");
    const int img = params.first_img("sa");
    planer.draw_building_ghost(ctx, img > 0 ? img : preview, pixel);
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
    if (is_finished()) {
        return;
    }
    scrub_dead_workers();
    if (needs_resource(RESOURCE_TIMBER) <= 0 && need_stonemason() && !has_live_worker(FIGURE_STONEMASON)) {
        return;
    }
    progress();
}

void building_obelisk::update_map_orientation(int /*map_orientation*/) {
    const int size = base.size > 0 ? base.size : 3;
    map_building_tiles_add(id(), tile(), size, building_image_get(), TERRAIN_BUILDING);
}

bool building_obelisk::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i /*tile*/, color color_mask) {
    const int n = scaffold_count();
    if (n <= 0) {
        return false;
    }
    const int ladder = building_static_params::get(base.type).first_img("ladder");
    if (ladder <= 0) {
        return false;
    }
    for (int i = 0; i < n; ++i) {
        auto &command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile);
        command.image_id = ladder;
        command.pixel = point + scaffold_pixel_offset(i);
        command.mask = color_mask;
    }
    return true;
}

tile2i building_obelisk::center_point() const {
    const int s = base.size > 0 ? base.size : 3;
    return tile().shifted(s / 2, s / 2);
}

tile2i building_obelisk::access_point() const {
    return tile();
}

void building_obelisk::bind_dynamic(io_buffer *iob, size_t /*version*/) {
    auto &monumentd = runtime_data();

    iob->bind____skip(38);
    iob->bind(BIND_SIGNATURE_UINT8, &base.orientation);
    for (int i = 0; i < 5; i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &monumentd.workers[i]);
    }
    iob->bind(BIND_SIGNATURE_UINT8, &monumentd.phase);
    iob->bind(BIND_SIGNATURE_UINT8, &monumentd.funeral_done); // was skip(1)
    iob->bind(BIND_SIGNATURE_UINT8, &monumentd.preexisting);  // was skip(1)
    iob->bind(BIND_SIGNATURE_UINT8, &monumentd.variant);

    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &monumentd.resources_pct[i]);
    }
}

#include "monument_obelisk.h"

#include "building/monuments.h"
#include "city/city.h"
#include "city/city_resource.h"
#include "city/city_warnings.h"
#include "construction/build_planner.h"
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
    const auto &bp = obelisk_params_for(base.type);
    const int max_stage = bp.art_stages > 0 ? bp.art_stages : 4;
    const int p = runtime_data().phase;
    return p >= 2 && p < max_stage;
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

int building_obelisk::preview::can_place(build_planner &p, tile2i /*tile*/, tile2i /*end*/, int state) const {
    if (state != CAN_PLACE) {
        return state;
    }
    if (has_unfinished_obelisk()) {
        p.set_warning("#only_one_obelisk_at_a_time");
        return CAN_NOT_PLACE;
    }
    const int need = placement_amount_for(p.build_type, RESOURCE_GRANITE);
    if (need > 0 && yards_available(RESOURCE_GRANITE) < need) {
        return CAN_NOT_PLACE;
    }
    return CAN_PLACE;
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
        const int lang_id = (p.build_type == BUILDING_LARGE_OBELISK) ? 84 : 83;
        pcstr tmpl = lang_get_string(19, lang_id);
        bstring256 msg;
        if (tmpl && tmpl[0]) {
            msg.printf(tmpl, need);
        } else {
            msg.printf("You need %d blocks of granite to build an obelisk", need);
        }
        g_warning_manager.show_custom(msg.c_str());
        return CAN_NOT_PLACE;
    }
    return CAN_PLACE;
}

void building_obelisk::preview::ghost_preview(build_planner &planer, painter &ctx, tile2i /*start*/, tile2i end, vec2i pixel) const {
    const auto &params = building_static_params::get(planer.build_type);
    const int size = params.building_size > 0 ? params.building_size : 3;
    blocked_tile_vec blocked;
    const bool is_blocked = !!planer.is_blocked_for_building(end, size, blocked);
    const int preview = params.first_img("preview");
    const int img = params.first_img("sa");
    if (is_blocked) {
        planer.draw_partially_blocked(ctx, false, blocked);
        return;
    }
    planer.draw_building_ghost(ctx, img > 0 ? img : preview, pixel);
}

void building_obelisk::on_place(int orientation, int variant) {
    building_impl::on_place(orientation, variant);

    const int need = placement_amount(RESOURCE_GRANITE);
    if (need > 0) {
        events::emit(event_city_remove_resource{RESOURCE_GRANITE, need, /*staffed_only*/true});
    }
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
    if (runtime_data().phase < 2) {
        return false;
    }
    const int ladder = building_static_params::get(base.type).first_img("ladder");
    if (ladder <= 0) {
        return false;
    }
    auto &command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile);
    command.image_id = ladder;
    command.pixel = point + vec2i{20, -40};
    command.mask = color_mask;
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

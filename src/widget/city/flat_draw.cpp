#include "widget/city/flat_draw.h"
#include "overlays/city_overlay.h"

#include "building/building.h"
#include "building/monuments.h"
#include "city/city.h"
#include "game/game.h"
#include "game/game_config.h"
#include "game/game_events.h"
#include "graphics/animkeys.h"
#include "graphics/animation.h"
#include "js/js_game.h"
#include "widget/widget_city.h"

#include <unordered_set>

namespace {

std::unordered_set<int> g_raised_while_flat;
// Draw workers read g_raised_draw_snapshot only.
// Main thread updates live set anytime; prepare_draw copies to snapshot;
// clear/erase also drop ids from the snapshot (no stale raise after delete).
std::unordered_set<int> g_raised_draw_snapshot;

void ensure_mission_reset_hook() {
    static bool hooked = false;
    if (hooked) {
        return;
    }
    hooked = true;
    events::subscribe_permanent([](event_game_mission_pre_load) {
        city_flat_view_reset();
    });
}

} // namespace

bool city_flat_feature_enabled() {
    return !!game_features::gameui_flat_buildings;
}

bool city_flat_view_active() {
    city_flat_view_sync_feature();
    return g_screen_city.buildings_flat_view;
}

void city_flat_clear_raised() {
    g_raised_while_flat.clear();
    g_raised_draw_snapshot.clear();
}

void city_flat_erase_raised(int main_building_id) {
    if (main_building_id <= 0) {
        return;
    }
    g_raised_while_flat.erase(main_building_id);
    g_raised_draw_snapshot.erase(main_building_id);
}

void city_flat_view_set(bool on) {
    ensure_mission_reset_hook();
    if (!city_flat_feature_enabled()) {
        g_screen_city.buildings_flat_view = false;
        city_flat_clear_raised();
        return;
    }
    if (!on) {
        city_flat_clear_raised();
    }
    g_screen_city.buildings_flat_view = on;
}

void city_flat_view_toggle() {
    city_flat_view_sync_feature();
    if (!city_flat_feature_enabled()) {
        return;
    }
    city_flat_view_set(!g_screen_city.buildings_flat_view);
}

void city_flat_view_reset() {
    g_screen_city.buildings_flat_view = false;
    city_flat_clear_raised();
}

void city_flat_view_sync_feature() {
    if (!city_flat_feature_enabled() && g_screen_city.buildings_flat_view) {
        city_flat_view_reset();
    }
}

void city_flat_prepare_draw() {
    ensure_mission_reset_hook();
    city_flat_view_sync_feature();
    g_raised_draw_snapshot = g_raised_while_flat;
}

bool city_flat_is_raised(int main_building_id) {
    if (main_building_id <= 0) {
        return false;
    }
    // Parallel draw reads the snapshot from prepare_draw (main thread).
    return g_raised_draw_snapshot.find(main_building_id) != g_raised_draw_snapshot.end();
}

void city_flat_toggle_raised(int main_building_id) {
    if (main_building_id <= 0 || !city_flat_view_active()) {
        return;
    }
    auto it = g_raised_while_flat.find(main_building_id);
    if (it != g_raised_while_flat.end()) {
        g_raised_while_flat.erase(it);
    } else {
        g_raised_while_flat.insert(main_building_id);
    }
}

bool city_flat_building_alive(const building &b) {
    if (b.type == BUILDING_NONE) {
        return false;
    }
    return b.state == BUILDING_STATE_VALID || b.state == BUILDING_STATE_MOTHBALLED;
}

int city_flat_flatten_id(const building &b) {
    const building *main_b = b.main();
    if (!main_b || main_b->id <= 0 || !city_flat_building_alive(*main_b)) {
        return 0;
    }
    return main_b->id;
}

int city_flat_building_texture_id(const building &b) {
    // Always resolve from main type — parts share the complex flat sprite.
    const building *main_b = b.main();
    if (!main_b || !city_flat_building_alive(*main_b)) {
        return 0;
    }

    // Unfinished monuments keep construction feet / force_draw partials.
    if (building_monument *mon = const_cast<building *>(main_b)->dcast_monument()) {
        if (mon->is_unfinished()) {
            return 0;
        }
    }

    const animation_t &anim = main_b->params().animations[animkeys().flat];
    // Unset / dummy: no pack, id, or path → keep map_image_at foot path.
    if (anim.path.empty() && anim.pack == 0 && anim.id == 0) {
        return 0;
    }

    const int img = anim.first_img();
    return (img > 0 && img < 0xFFFF) ? img : 0;
}

bool city_flat_should_flatten_building(const building &b) {
    // Read-only: no sync_feature (called from parallel city draw workers).
    if (!city_flat_feature_enabled() || !g_screen_city.buildings_flat_view) {
        return false;
    }
    if (g_city_overlay.current != OVERLAY_NONE) {
        return false;
    }
    if (!city_flat_building_alive(b)) {
        return false;
    }
    const int fid = city_flat_flatten_id(b);
    if (fid == 0) {
        return false;
    }
    if (city_flat_is_raised(fid)) {
        return false;
    }
    return true;
}

bool city_flat_should_skip_tall_ornaments(const building &b) {
    if (!city_flat_should_flatten_building(b)) {
        return false;
    }
    // Height-pass only. Parts/cones follow main().
    // Unfinished monuments: do not skip the pass (phase-6 alt / ladder).
    // Tall height_impl is omitted inside pyramid/mastaba draw under flatten.
    const building *main_b = b.main();
    if (!main_b) {
        return false;
    }
    if (building_monument *mon = const_cast<building *>(main_b)->dcast_monument()) {
        if (mon->is_unfinished()) {
            return false;
        }
    }
    // Finished tall volume: building_monument defaults suppress=true;
    // is_monument() covers Cleopatra types without METAINFO.
    building_impl *impl = const_cast<building *>(main_b)->dcast();
    if (impl && impl->suppress_ornaments_in_flat_view()) {
        return true;
    }
    return main_b->is_monument();
}

static void __city_flat_buildings_toggle() {
    city_flat_view_toggle();
}
ANK_FUNCTION(__city_flat_buildings_toggle)

static void __city_flat_buildings_sync() {
    city_flat_view_sync_feature();
}
ANK_FUNCTION(__city_flat_buildings_sync)

static int __city_flat_buildings_active() {
    return city_flat_view_active() ? 1 : 0;
}
ANK_FUNCTION(__city_flat_buildings_active)

static void __city_flat_buildings_set(int on) {
    city_flat_view_set(!!on);
    city_flat_prepare_draw();
}
ANK_FUNCTION_1(__city_flat_buildings_set)

static int __city_flat_should_flatten(int bid) {
    building *b = building_get(bid);
    if (!b) {
        return 0;
    }
    return city_flat_should_flatten_building(*b) ? 1 : 0;
}
ANK_FUNCTION_1(__city_flat_should_flatten)

static void __city_flat_toggle_raised(int bid) {
    building *b = building_get(bid);
    if (!b || !city_flat_building_alive(*b)) {
        return;
    }
    building *main_b = b->main();
    if (!main_b || !city_flat_building_alive(*main_b)) {
        return;
    }
    city_flat_toggle_raised(main_b->id);
    city_flat_prepare_draw();
}
ANK_FUNCTION_1(__city_flat_toggle_raised)

static int __city_flat_is_raised(int bid) {
    building *b = building_get(bid);
    if (!b || !city_flat_building_alive(*b)) {
        return 0;
    }
    const int fid = city_flat_flatten_id(*b);
    return (fid > 0 && city_flat_is_raised(fid)) ? 1 : 0;
}
ANK_FUNCTION_1(__city_flat_is_raised)

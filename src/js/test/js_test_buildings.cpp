#include "js/test/js_test_common.h"

#include "building/building.h"
#include "building/building_delivery_path.h"
#include "building/building_house.h"
#include "building/building_mansion.h"
#include "building/building_static_params.h"
#include "building/building_temple_complex.h"
#include "building/monument_obelisk.h"
#include "building/monument_pyramid.h"
#include "building/monument_royal_tomb.h"
#include "building/monuments.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_recorded_paths.h"
#include "city/city_warnings.h"
#include "city/object_info.h"
#include "core/bstring.h"
#include "core/xstring.h"
#include "empire/trader_handler.h"
#include "figure/figure.h"
#include "figure/figure_impl.h"
#include "figure/formation.h"
#include "figuretype/figure_cartpusher.h"
#include "figuretype/figure_plagued_citizen.h"
#include "game/game_events.h"
#include "game/resource.h"
#include "graphics/image.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "grid/routing/routing.h"
#include "scenario/scenario.h"
#include "sound/sound_city.h"

#include <algorithm>
#include <vector>

int __building_static_building_size(int type) {
    if (type <= BUILDING_NONE || type >= BUILDING_MAX) {
        return 0;
    }
    return std::max(1, (int)building_static_params::get((e_building_type)type).building_size);
}
ANK_FUNCTION_1(__building_static_building_size);

int __building_static_base_img(int type) {
    if (type <= BUILDING_NONE || type >= BUILDING_MAX) {
        return 0;
    }
    return building_static_params::get((e_building_type)type).base_img();
}
ANK_FUNCTION_1(__building_static_base_img);

int __building_static_labor_category(int type) {
    if (type <= BUILDING_NONE || type >= BUILDING_MAX) {
        return LABOR_CATEGORY_INVALID;
    }
    return building_static_params::get((e_building_type)type).labor_category;
}
ANK_FUNCTION_1(__building_static_labor_category);

int __building_static_guild_worker_terrain(int type) {
    if (type <= BUILDING_NONE || type >= BUILDING_MAX) {
        return -1;
    }
    return building_static_params::get((e_building_type)type).guild_worker_terrain;
}
ANK_FUNCTION_1(__building_static_guild_worker_terrain);

int __test_sound_city_mark_building(int bid, int views) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    for (int i = 0; i < views; ++i) {
        sound_city_mark_building_view(b, SOUND_DIRECTION_CENTER);
    }
    return b->dcast()->sound_channel();
}
ANK_FUNCTION_2(__test_sound_city_mark_building);

int __test_sound_city_channel_views(int channel) {
    const auto& channels = sound_city_channels().channels;
    const int slot = channel - SOUND_CHANNEL_CITY_START;
    if (slot < 0 || slot >= (int)channels.size()) {
        return -1;
    }
    return channels[slot].total_views;
}
ANK_FUNCTION_1(__test_sound_city_channel_views);

void __test_sound_city_decay_views() {
    sound_city_decay_views();
}
ANK_FUNCTION(__test_sound_city_decay_views);

static int __test_building_create(int type, int x, int y) {
    if (type <= BUILDING_NONE || type >= BUILDING_MAX) {
        return 0;
    }

    tile2i place = (x < 0 || y < 0) ? tile2i::invalid : tile2i(x, y);
    // Reuse only for unspecified tile; explicit coords create a second instance when needed.
    if (!place.valid()) {
        if (building* existing = building_first((e_building_type)type)) {
            return existing->id;
        }
        place.set(g_scenario.map.width / 2, g_scenario.map.height / 2);
    }

    building* b = building_create((e_building_type)type, place, 0);
    if (!b || b->id <= 0) {
        return 0;
    }

    add_building(b, 0, 0);
    for (building* part = b->main(); part;) {
        part->state = BUILDING_STATE_VALID;
        if (!part->has_next()) {
            break;
        }
        part = part->next();
    }
    return b->id;
}
ANK_FUNCTION_3(__test_building_create);

static int __test_building_destroy_by_enemy(int bid) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    g_city.maintenance.destroy_by_enemy(b);
    return 1;
}
ANK_FUNCTION_1(__test_building_destroy_by_enemy);

// Free a slot the way the game does: 0 = destroy_by_poof (slot just marked unused),
// 1 = deleted by the player and removed by building_update_state.
static int __test_building_release_slot(int bid, int via_delete) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    if (via_delete) {
        b->state = BUILDING_STATE_DELETED_BY_PLAYER;
        building_update_state();
    } else {
        b->dcast()->destroy_by_poof(false);
    }
    return b->state == BUILDING_STATE_UNUSED ? 1 : 0;
}
ANK_FUNCTION_2(__test_building_release_slot);

static int __test_destroy_buildings_of_type(int type) {
    if (type <= BUILDING_NONE || type >= BUILDING_MAX) {
        return 0;
    }
    svector<int, 64> ids;
    buildings_valid_do([&](building& b) {
        if ((int)b.type == type) {
            ids.push_back(b.id);
        }
    });
    for (int id : ids) {
        building* b = building_get(id);
        if (b && b->is_valid()) {
            g_city.maintenance.destroy_by_enemy(b);
        }
    }
    return (int)ids.size();
}
ANK_FUNCTION_1(__test_destroy_buildings_of_type);

static void __test_mansion_update_money_values() {
    building_mansion::update_money_values();
}
ANK_FUNCTION(__test_mansion_update_money_values);

static int __test_mansion_spawn_figure(int bid) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    auto* m = b->dcast_mansion();
    if (!m) {
        return 0;
    }
    m->spawn_figure();
    return b->has_figure_of_type(BUILDING_SLOT_GOVERNOR, FIGURE_GOVERNOR) ? 1 : 0;
}
ANK_FUNCTION_1(__test_mansion_spawn_figure);

static int __test_building_map_random_7bit(int bid) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return -1;
    }
    return b->map_random_7bit;
}
ANK_FUNCTION_1(__test_building_map_random_7bit);

static int __test_building_create_cartpusher_wait_ticks(int bid) {
    building* b = building_get(bid);
    if (!b) {
        return -1;
    }
    figure* f = b->dcast()->create_cartpusher(RESOURCE_GRAIN, 100, (e_figure_action)ACTION_20_CARTPUSHER_INITIAL,
      BUILDING_SLOT_CARTPUSHER);
    return f ? f->wait_ticks : -1;
}
ANK_FUNCTION_1(__test_building_create_cartpusher_wait_ticks);

static void __test_building_force_road_access(int bid) {
    building* b = building_get(bid);
    if (!b) {
        return;
    }
    b->has_road_access = true;
    if (!b->road_access.valid()) {
        b->road_access = b->tile;
    }
    if (b->road_network_id <= 0) {
        b->road_network_id = 1;
    }
}
ANK_FUNCTION_1(__test_building_force_road_access);

static void __test_building_set_native_meeting(int hut_id, int meeting_id) {
    building* b = building_get(hut_id);
    if (!b) {
        return;
    }
    b->native_meeting_center_id = (int16_t)meeting_id;
}
ANK_FUNCTION_2(__test_building_set_native_meeting);

static void __test_building_set_road_access(int bid, int x, int y) {
    building* b = building_get(bid);
    if (!b) {
        return;
    }
    b->has_road_access = true;
    b->road_access = tile2i(x, y);
    if (b->road_network_id <= 0) {
        b->road_network_id = 1;
    }
}
ANK_FUNCTION_3(__test_building_set_road_access);

static int __test_building_curse_days(int bid) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return -1;
    }
    return b->curse_days_left;
}
ANK_FUNCTION_1(__test_building_curse_days);

static int __test_house_set_population(int bid, int pop) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    auto* house = b->dcast_house();
    if (!house) {
        return 0;
    }
    house->runtime_data().population = (uint16_t)std::max(0, pop);
    return house->house_population();
}
ANK_FUNCTION_2(__test_house_set_population);

static int __test_house_add_population(int bid, int num_people) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return -1;
    }
    auto* house = b->dcast_house();
    if (!house) {
        return -1;
    }
    house->add_population(num_people);
    return house->house_population();
}
ANK_FUNCTION_2(__test_house_add_population);

static int __test_house_mark_plague(int bid, int days) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    building* main = b->main();
    if (!main) {
        return 0;
    }
    main->mark_plague(days);
    return main->has_plague ? 1 : 0;
}
ANK_FUNCTION_2(__test_house_mark_plague);

static int __test_building_has_plague(int bid) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    return b->main()->has_plague ? 1 : 0;
}
ANK_FUNCTION_1(__test_building_has_plague);

static int __test_building_figure_spawn_delay(int bid) {
    building* b = building_get(bid);
    return b ? b->figure_spawn_delay : -1;
}
ANK_FUNCTION_1(__test_building_figure_spawn_delay);

static int __test_building_figure_spawn_timer(int bid) {
    building* b = building_get(bid);
    return b ? b->dcast()->figure_spawn_timer() : -2;
}
ANK_FUNCTION_1(__test_building_figure_spawn_timer);

static void __test_building_set_figure_spawn_delay(int bid, int delay) {
    building* b = building_get(bid);
    if (!b) {
        return;
    }
    b->figure_spawn_delay = (short)delay;
}
ANK_FUNCTION_2(__test_building_set_figure_spawn_delay);

static void __test_building_set_houses_covered(int bid, int covered) {
    building* b = building_get(bid);
    if (b) {
        b->houses_covered = (short)std::max(0, covered);
    }
}
ANK_FUNCTION_2(__test_building_set_houses_covered);

static void __test_building_set_open_water_access(int bid, int value) {
    building* b = building_get(bid);
    if (b) {
        b->has_open_water_access = value != 0;
    }
}
ANK_FUNCTION_2(__test_building_set_open_water_access);

static void __test_building_set_figure_slot(int bid, int slot, int fid) {
    building* b = building_get(bid);
    if (!b) {
        return;
    }
    b->set_figure(slot, fid);
}
ANK_FUNCTION_3(__test_building_set_figure_slot);

static xstring __test_building_slot_anim_key(int bid, int slot) {
    building* b = building_get(bid);
    if (!b || !b->is_valid() || slot < 0 || slot >= (int)b->anims.size()) {
        return {};
    }
    return b->anims[slot].key;
}
ANK_FUNCTION_2(__test_building_slot_anim_key);

static xstring __test_building_anim_key(int bid) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return {};
    }
    return b->anim.key;
}
ANK_FUNCTION_1(__test_building_anim_key);

// Call building_impl::update_day() (e.g. pyramid phase advance / congrats).
static void __test_building_update_day(int bid) {
    building* b = building_get(bid);
    auto* impl = b ? b->dcast() : nullptr;
    if (!impl) {
        return;
    }
    impl->update_day();
}
ANK_FUNCTION_1(__test_building_update_day);

static int __test_building_current_image(int bid) {
    building* b = building_get(bid);
    auto m = b ? b->dcast_monument() : nullptr;
    if (!m) {
        return 0;
    }
    const int id = m->building_image_get();
    return (id > 0 && image_get(id)) ? id : 0;
}
ANK_FUNCTION_1(__test_building_current_image);

static int __test_building_figure_id(int bid, int slot) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    return b->get_figure_id(slot);
}
ANK_FUNCTION_2(__test_building_figure_id);

static int __test_building_is_fancy(int bid) {
    building* b = building_get(bid);
    return (b && b->is_valid() && b->get_flag(e_building_fancy)) ? 1 : 0;
}
ANK_FUNCTION_1(__test_building_is_fancy);

static int __test_building_road_access_tile(int bid) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return -1;
    }
    building* m = b->main();
    if (!m || !m->road_access.valid()) {
        return -1;
    }
    return m->road_access.grid_offset();
}
ANK_FUNCTION_1(__test_building_road_access_tile);

static void __test_building_road_access_set_stale(int bid) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return;
    }
    building* m = b->main();
    if (!m) {
        return;
    }
    m->has_road_access = true;
    m->road_network_id = 1;
    m->distance_from_entry = 1;
    m->road_access = m->tile;
}
ANK_FUNCTION_1(__test_building_road_access_set_stale);

static int __test_building_road_access_fields_cleared(int bid) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    building* m = b->main();
    if (!m) {
        return 0;
    }
    return (!m->has_road_access && m->road_network_id == 0 && m->distance_from_entry == 0 && !m->road_access.valid())
             ? 1
             : 0;
}
ANK_FUNCTION_1(__test_building_road_access_fields_cleared);

static int __test_building_road_access_match_preview(int bid) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    building* m = b->main();
    if (!m) {
        return 0;
    }
    int variant = 0;
    if (building_static_params::get(m->type).flags.is_temple_complex) {
        auto complex = m->dcast_temple_complex();
        variant = complex ? complex->runtime_data().variant : 0;
    }
    const bool assume = building_type_ghost_assume_occupied(m->type);
    building_road_ports stored = building_road_ports_stored(*m);
    building_road_ports preview
      = building_road_ports_preview(m->tile, m->type, m->size, m->orientation, variant, assume);
    if (!stored.valid || !preview.valid) {
        return 0;
    }
    return (stored.tile == preview.tile) ? 1 : 0;
}
ANK_FUNCTION_1(__test_building_road_access_match_preview);

static int __test_building_type_ghost_road_access(int type) {
    return building_type_ghost_road_access((e_building_type)type) ? 1 : 0;
}
ANK_FUNCTION_1(__test_building_type_ghost_road_access);

static int __test_building_type_ghost_assume_occupied(int type) {
    return building_type_ghost_assume_occupied((e_building_type)type) ? 1 : 0;
}
ANK_FUNCTION_1(__test_building_type_ghost_assume_occupied);

static int __test_building_type_hover_road_access(int type) {
    return building_type_hover_road_access((e_building_type)type) ? 1 : 0;
}
ANK_FUNCTION_1(__test_building_type_hover_road_access);

// Construction warnings captured since the last __test_construction_warnings_reset().
static std::vector<xstring> g_test_construction_warnings;
static bool g_test_construction_warnings_subscribed = false;

static void __test_construction_warnings_reset() {
    if (!g_test_construction_warnings_subscribed) {
        g_test_construction_warnings_subscribed = true;
        events::subscribe_permanent(
          [](event_construction_warning ev) { g_test_construction_warnings.push_back(ev.id); });
    }
    g_test_construction_warnings.clear();
}
ANK_FUNCTION(__test_construction_warnings_reset);

static int __test_construction_warning_count(pcstr id) {
    int count = 0;
    for (const xstring& w : g_test_construction_warnings) {
        if (w == id) {
            ++count;
        }
    }
    return count;
}
ANK_FUNCTION_1(__test_construction_warning_count);

static void __test_building_set_workers(int bid, int workers) {
    building* b = building_get(bid);
    if (!b) {
        return;
    }
    building* m = b->main();
    if (!m) {
        return;
    }
    m->num_workers = std::max(0, workers);
    for (building* part = m; part;) {
        part->num_workers = m->num_workers;
        if (!part->has_next()) {
            break;
        }
        part = part->next();
    }
}
ANK_FUNCTION_2(__test_building_set_workers);

static void __test_building_spawn_figure(int bid) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return;
    }
    b->has_road_access = true;
    if (auto* impl = b->dcast()) {
        impl->spawn_figure();
    }
}
ANK_FUNCTION_1(__test_building_spawn_figure);

static void __test_city_buildings_update_tick() {
    g_city.buildings.update_tick(/*refresh_only*/ true);
}
ANK_FUNCTION(__test_city_buildings_update_tick);

static int __test_building_shows_delivery_paths(int bid) {
    building* b = building_get(bid);
    if (!b) {
        return 0;
    }
    return building_shows_delivery_paths(*b) ? 1 : 0;
}
ANK_FUNCTION_1(__test_building_shows_delivery_paths);

static void __test_building_push_recorded_path(int bid, int path_id) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return;
    }
    building* main = b->main();
    g_recorded_paths.building_push(main ? main->id : bid, path_id);
}
ANK_FUNCTION_2(__test_building_push_recorded_path);

static int __test_building_recorded_path_at(int bid, int index) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    building* main = b->main();
    return g_recorded_paths.building_path_at(main ? main->id : bid, index);
}
ANK_FUNCTION_2(__test_building_recorded_path_at);

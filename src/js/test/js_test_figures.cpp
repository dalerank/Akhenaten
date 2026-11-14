#include "js/test/js_test_common.h"

#include "building/building.h"
#include "building/building_delivery_path.h"
#include "city/city.h"
#include "city/city_figures.h"
#include "city/object_info.h"
#include "core/xstring.h"
#include "empire/trader_handler.h"
#include "figure/figure.h"
#include "figure/figure_impl.h"
#include "figure/formation.h"
#include "figuretype/figure_funeral_walker.h"
#include "figuretype/figure_immigrant.h"
#include "figuretype/figure_mummy.h"
#include "figuretype/figure_plagued_citizen.h"
#include "game/game_events.h"
#include "game/resource.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "grid/routing/routing.h"
#include "grid/terrain.h"
#include "scenario/scenario.h"

#include <algorithm>

// Force figures.reset()+action_perform. Needed when --integraltests pumps
// frames faster than tick_timer_ms (get_elapsed_ticks ? 0).
static void __test_figures_update() {
    g_city.figures.update();
}
ANK_FUNCTION(__test_figures_update);

static int __test_figure_create(int type, int x, int y) {
    if (type <= FIGURE_NONE || type >= FIGURE_MAX) {
        return 0;
    }

    tile2i place = (x < 0 || y < 0) ? tile2i::invalid : tile2i(x, y);
    if (!place.valid()) {
        place.set(g_scenario.map.width / 2, g_scenario.map.height / 2);
    }

    figure* f = figure_create((e_figure_type)type, place, DIR_0_TOP_RIGHT);
    if (!f || f->id <= 0 || !f->is_alive()) {
        return 0;
    }

    return f->id;
}
ANK_FUNCTION_3(__test_figure_create);

static int __test_figure_draw_mode(int fid) {
    figure* f = figure_get(fid);
    return (f && f->id > 0) ? (int)f->draw_mode : -1;
}
ANK_FUNCTION_1(__test_figure_draw_mode);

static void __test_figure_set_draw_mode(int fid, int mode) {
    figure* f = figure_get(fid);
    if (f && f->id > 0) {
        f->draw_mode = (uint8_t)mode;
    }
}
ANK_FUNCTION_2(__test_figure_set_draw_mode);

static void __test_figure_set_home(int fid, int bid) {
    figure* f = figure_get(fid);
    building* b = building_get(bid);
    if (!f || !f->is_alive() || !b || !b->is_valid()) {
        return;
    }
    f->set_home(bid);
}
ANK_FUNCTION_2(__test_figure_set_home);

static void __test_figure_set_home_slot(int fid, int bid) {
    figure* f = figure_get(fid);
    building* b = building_get(bid);
    if (!f || !f->is_alive() || !b || !b->is_valid()) {
        return;
    }
    f->set_home(bid);
    b->set_figure(0, f);
}
ANK_FUNCTION_2(__test_figure_set_home_slot);

static void __test_figure_set_leading(int fid, int leader_id) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return;
    }
    f->leading_figure_id = (short)std::max(0, leader_id);
}
ANK_FUNCTION_2(__test_figure_set_leading);

static void __test_figure_set_collecting_item(int fid, int item) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return;
    }
    f->collecting_item_id = (uint8_t)std::clamp(item, 0, INVENTORY_MAX - 1);
}
ANK_FUNCTION_2(__test_figure_set_collecting_item);

static void __test_figure_set_speed(int fid, int speed) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return;
    }
    f->speed_multiplier = (uint8_t)std::clamp(speed, 0, 255);
}
ANK_FUNCTION_2(__test_figure_set_speed);

static int __test_figure_get_speed(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return -1;
    }
    return f->speed_multiplier;
}
ANK_FUNCTION_1(__test_figure_get_speed);

static int __test_figure_apply_params_speed(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return -1;
    }
    f->apply_params_speed_multiplier();
    return f->speed_multiplier;
}
ANK_FUNCTION_1(__test_figure_apply_params_speed);

static int __test_figure_get_wait_ticks(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return -1;
    }
    return f->wait_ticks;
}
ANK_FUNCTION_1(__test_figure_get_wait_ticks);

static void __test_figure_set_wait_ticks(int fid, int ticks) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return;
    }
    f->wait_ticks = (int16_t)ticks;
}
ANK_FUNCTION_2(__test_figure_set_wait_ticks);

static int __test_figure_get_action(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return -1;
    }
    return f->action_state;
}
ANK_FUNCTION_1(__test_figure_get_action);

static int __test_figure_is_visible(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return -1;
    }
    return f->is_visible() ? 1 : 0;
}
ANK_FUNCTION_1(__test_figure_is_visible);

static void __test_figure_set_visible(int fid, int visible) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return;
    }
    f->set_flag(e_figure_flag_invisible, visible == 0);
}
ANK_FUNCTION_2(__test_figure_set_visible);

static int __test_figure_cart_image_id(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return -1;
    }
    return f->cart_image_id;
}
ANK_FUNCTION_1(__test_figure_cart_image_id);

static int __test_figure_main_image_id(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return -1;
    }
    return f->main_image_id;
}
ANK_FUNCTION_1(__test_figure_main_image_id);

// Ferry action id a landing assigns to this figure: 0 wait, 1 ride, 2 reroute. -1 when missing.
static int __test_figure_ferry_action(int fid, int which) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return -1;
    }
    switch (which) {
    case 0:
        return f->dcast()->ferry_wait_action();
    case 1:
        return f->dcast()->ferry_ride_action();
    case 2:
        return f->dcast()->ferry_reroute_action();
    }
    return -1;
}
ANK_FUNCTION_2(__test_figure_ferry_action);

// OG immigrant create path (event_create_immigrant): entry point, wait from house map_random_7bit.
static int __test_create_immigrant(int bid, int num_people) {
    building* b = building_get(bid);
    if (!b || !b->is_valid() || !b->is_house() || num_people <= 0) {
        return 0;
    }
    events::emit(event_create_immigrant{(building_id)bid, num_people, SOURCE_LOCATION});
    events::process();
    figure* f = b->get_figure(BUILDING_SLOT_IMMIGRANT);
    if (!f || !f->is_alive() || f->type != FIGURE_IMMIGRANT) {
        return 0;
    }
    return f->id;
}
ANK_FUNCTION_2(__test_create_immigrant);

static void __test_figure_set_force_valid_animation(int fid, int enabled) {
    figure* f = figure_get(fid);
    if (!f || !f->is_valid()) {
        return;
    }
    f->set_force_valid_animation(enabled != 0);
}
ANK_FUNCTION_2(__test_figure_set_force_valid_animation);

static int __test_figure_get_damage(int fid) {
    figure* f = figure_get(fid);
    if (!f) {
        return -1;
    }
    return f->damage;
}
ANK_FUNCTION_1(__test_figure_get_damage);

static void __test_figure_set_damage(int fid, int damage) {
    figure* f = figure_get(fid);
    if (!f) {
        return;
    }
    f->damage = (uint16_t)std::max(0, damage);
}
ANK_FUNCTION_2(__test_figure_set_damage);

static void __test_figure_apply_damage(int fid, int damage) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return;
    }
    f->apply_damage(damage, 0);
}
ANK_FUNCTION_2(__test_figure_apply_damage);

static tile2i __figure_get_destination_tile(int fid) {
    figure* f = figure_get(fid);
    return (f && f->is_valid()) ? f->destination_tile : tile2i::invalid;
}
ANK_FUNCTION_1(__figure_get_destination_tile);

static int __test_figure_is_alive(int fid) {
    figure* f = figure_get(fid);
    return (f && f->is_alive()) ? 1 : 0;
}
ANK_FUNCTION_1(__test_figure_is_alive);

static void __test_figure_set_faction(int fid, int faction) {
    figure* f = figure_get(fid);
    if (!f) {
        return;
    }
    f->faction_id = (uint8_t)faction;
}
ANK_FUNCTION_2(__test_figure_set_faction);

int __test_count_figures(int type) {
    int count = 0;
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure* f = figure_get(i);
        if (f && f->is_alive() && f->type == (e_figure_type)type) {
            count++;
        }
    }
    return count;
}
ANK_FUNCTION_1(__test_count_figures);

static int __test_figure_missile_defense(int type) {
    return figure_static_params::get((e_figure_type)type).missile_defense_value;
}
ANK_FUNCTION_1(__test_figure_missile_defense);

static int __test_figure_get_formation_id(int fid) {
    figure* f = figure_get(fid);
    return f ? f->formation_id : 0;
}
ANK_FUNCTION_1(__test_figure_get_formation_id);

static void __test_buildings_generate_figures() {
    g_city.buildings_generate_figure();
}
ANK_FUNCTION(__test_buildings_generate_figures);

static int __test_figure_type_max_roam(int type) {
    if (type <= FIGURE_NONE || type >= FIGURE_MAX) {
        return -1;
    }
    return figure_static_params::get((e_figure_type)type).max_roam_length;
}
ANK_FUNCTION_1(__test_figure_type_max_roam);

static int __test_figure_type_category(int type) {
    if (type <= FIGURE_NONE || type >= FIGURE_MAX) {
        return -1;
    }
    return (int)figure_static_params::get((e_figure_type)type).category;
}
ANK_FUNCTION_1(__test_figure_type_category);

static int __test_figure_type_missile_attack(int type) {
    if (type <= FIGURE_NONE || type >= FIGURE_MAX) {
        return -1;
    }
    return figure_static_params::get((e_figure_type)type).missile_attack_value;
}
ANK_FUNCTION_1(__test_figure_type_missile_attack);

static int __test_figure_type_missile_delay(int type) {
    if (type <= FIGURE_NONE || type >= FIGURE_MAX) {
        return -1;
    }
    return figure_static_params::get((e_figure_type)type).missile_delay;
}
ANK_FUNCTION_1(__test_figure_type_missile_delay);

static int __test_figure_type_missile_range(int type) {
    if (type <= FIGURE_NONE || type >= FIGURE_MAX) {
        return -1;
    }
    return figure_static_params::get((e_figure_type)type).missile_range;
}
ANK_FUNCTION_1(__test_figure_type_missile_range);

static void __test_figure_set_wait_ticks_missile(int fid, int ticks) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return;
    }
    f->wait_ticks_missile = (uint8_t)ticks;
}
ANK_FUNCTION_2(__test_figure_set_wait_ticks_missile);

static int __test_mummy_spawn_wave(int count) {
    return figure_mummy::spawn_wave(count);
}
ANK_FUNCTION_1(__test_mummy_spawn_wave);

static void __test_figure_action_perform(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return;
    }
    f->action_perform();
}
ANK_FUNCTION_1(__test_figure_action_perform);

static int __test_figure_combat_attack_at(int fid, int x, int y) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return 0;
    }
    f->figure_combat_attack_figure_at(tile2i(x, y).grid_offset());
    return f->in_attack() ? 1 : 0;
}
ANK_FUNCTION_3(__test_figure_combat_attack_at);

static int __test_figure_in_attack(int fid) {
    figure* f = figure_get(fid);
    return (f && f->is_alive() && f->in_attack()) ? 1 : 0;
}
ANK_FUNCTION_1(__test_figure_in_attack);

static int __test_figure_get_opponent_id(int fid) {
    figure* f = figure_get(fid);
    return f ? (int)f->opponent_id : 0;
}
ANK_FUNCTION_1(__test_figure_get_opponent_id);

static int __test_funeral_try_spawn(int force_ignore_road) {
    return figure_funeral_walker::try_spawn_all(force_ignore_road != 0);
}
ANK_FUNCTION_1(__test_funeral_try_spawn);

static int __test_funeral_target_tomb(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_valid() || f->type != FIGURE_FUNERAL_WALKER) {
        return 0;
    }
    return figure_funeral_walker(f).runtime_data().target_tomb_id;
}
ANK_FUNCTION_1(__test_funeral_target_tomb);

static int __test_funeral_dest_is_road(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_valid() || f->type != FIGURE_FUNERAL_WALKER) {
        return 0;
    }
    if (!f->destination_tile.valid()) {
        return 0;
    }
    return map_terrain_is(f->destination_tile, TERRAIN_ROAD | TERRAIN_FERRY_ROUTE) ? 1 : 0;
}
ANK_FUNCTION_1(__test_funeral_dest_is_road);

static int __test_funeral_tomb_dest_is_road(int bid) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    tile2i dest = figure_funeral_walker::tomb_destination_tile(*b);
    if (!dest.valid()) {
        return 0;
    }
    return map_terrain_is(dest, TERRAIN_ROAD | TERRAIN_FERRY_ROUTE) ? 1 : 0;
}
ANK_FUNCTION_1(__test_funeral_tomb_dest_is_road);

static int __test_figure_current_height(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return -1;
    }
    return f->current_height;
}
ANK_FUNCTION_1(__test_figure_current_height);

static int __test_plagued_spawn_from_house(int bid) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    return figure_plagued_citizen::spawn_from_house(*b);
}
ANK_FUNCTION_1(__test_plagued_spawn_from_house);

static int __test_plagued_cure_nearby(int x, int y) {
    return figure_plagued_citizen::cure_nearby(tile2i(x, y), 1);
}
ANK_FUNCTION_2(__test_plagued_cure_nearby);

static int __test_figure_provide_service(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return 0;
    }
    auto* impl = f->dcast();
    if (!impl) {
        return 0;
    }
    return impl->provide_service();
}
ANK_FUNCTION_1(__test_figure_provide_service);

static int __test_figure_is_enemy(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_valid()) {
        return 0;
    }
    return f->is_enemy() ? 1 : 0;
}
ANK_FUNCTION_1(__test_figure_is_enemy);

static void __test_figure_kill(int fid) {
    figure* f = figure_get(fid);
    if (f && f->is_alive()) {
        f->wait_ticks = 0; // corpse timer must not inherit roam lifetime
        // Prefer type override (e.g. transport drown + shipwreck) over figure::kill.
        if (figure_impl* impl = f->dcast()) {
            impl->kill();
        } else {
            f->kill();
        }
    }
}
ANK_FUNCTION_1(__test_figure_kill);

static void __test_figure_update_day(int fid) {
    figure* f = figure_get(fid);
    auto* impl = f ? f->dcast() : nullptr;
    if (!impl) {
        return;
    }
    impl->update_day();
}
ANK_FUNCTION_1(__test_figure_update_day);

static void __test_figure_set_action(int fid, int action) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return;
    }
    f->advance_action((short)action);
}
ANK_FUNCTION_2(__test_figure_set_action);

static int __test_figure_is_dying(int fid) {
    figure* f = figure_get(fid);
    return (f && f->state == FIGURE_STATE_DYING) ? 1 : 0;
}
ANK_FUNCTION_1(__test_figure_is_dying);

static void __test_figure_action_perform_dying(int fid) {
    figure* f = figure_get(fid);
    if (!f || (f->state != FIGURE_STATE_ALIVE && f->state != FIGURE_STATE_DYING)) {
        return;
    }
    f->action_perform();
}
ANK_FUNCTION_1(__test_figure_action_perform_dying);

static void __test_figure_update_animation(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return;
    }
    figure_impl* impl = f->dcast();
    if (impl) {
        impl->update_animation();
    }
}
ANK_FUNCTION_1(__test_figure_update_animation);

static void __test_figure_refresh_image(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return;
    }
    f->figure_image_update(true);
}
ANK_FUNCTION_1(__test_figure_refresh_image);

static int __test_figure_carrying_amount(int fid) {
    figure* f = figure_get(fid);
    return f ? f->get_carrying_amount() : -1;
}
ANK_FUNCTION_1(__test_figure_carrying_amount);

static int __test_figure_resource(int fid) {
    figure* f = figure_get(fid);
    return f ? (int)f->get_resource() : -1;
}
ANK_FUNCTION_1(__test_figure_resource);

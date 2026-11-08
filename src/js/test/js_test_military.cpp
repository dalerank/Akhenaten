#include "js/test/js_test_common.h"

#include "building/building.h"
#include "building/building_barracks.h"
#include "building/building_delivery_path.h"
#include "building/building_fort.h"
#include "building/building_gatehouse.h"
#include "building/building_transport_wharf.h"
#include "building/building_warship_wharf.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "city/city_religion_seth.h"
#include "city/legion_requests.h"
#include "city/object_info.h"
#include "core/log.h"
#include "core/xstring.h"
#include "empire/trader_handler.h"
#include "figure/combat.h"
#include "figure/enemy_army.h"
#include "figure/figure.h"
#include "figure/figure_impl.h"
#include "figure/formation.h"
#include "figure/formation_batalion.h"
#include "figuretype/figure_constable.h"
#include "figuretype/figure_enemy_archer.h"
#include "figuretype/figure_enemy_elephant.h"
#include "figuretype/figure_enemy_spearman.h"
#include "figuretype/figure_enemy_transport.h"
#include "figuretype/figure_enemy_warship.h"
#include "figuretype/figure_javelin.h"
#include "figuretype/figure_missile.h"
#include "figuretype/figure_plagued_citizen.h"
#include "figuretype/figure_soldier.h"
#include "figuretype/figure_transport_ship.h"
#include "figuretype/figure_war_ship.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "grid/routing/routing.h"
#include "grid/terrain.h"
#include "grid/water.h"
#include "scenario/distant_battle.h"
#include "scenario/scenario.h"
#include "scenario/scenario_invasion.h"

#include <algorithm>

void __test_distant_battle_set_egyptian_strength(int strength) {
    if (strength <= 0) {
        g_distant_battle.battle.egyptian_strength = 0;
        g_distant_battle.battle.egyptian_months_to_travel_forth = 0;
    } else {
        g_distant_battle.battle.egyptian_strength = (uint8_t)std::min(255, strength);
        g_distant_battle.battle.egyptian_months_to_travel_forth = 1;
    }
}
ANK_FUNCTION_1(__test_distant_battle_set_egyptian_strength);

void __test_process_distant_battle_month() {
    g_distant_battle.process_distant_battle_impl();
}
ANK_FUNCTION(__test_process_distant_battle_month);

int __test_distant_battle_egyptian_strength() {
    return (int)g_distant_battle.battle.egyptian_strength;
}
ANK_FUNCTION(__test_distant_battle_egyptian_strength);

int __test_distant_battle_enemy_strength() {
    return (int)g_distant_battle.battle.enemy_strength;
}
ANK_FUNCTION(__test_distant_battle_enemy_strength);

void __test_process_invasion_binds() {
    g_invasions.process_bind_resolutions();
}
ANK_FUNCTION(__test_process_invasion_binds);

// B3: seed / inspect a single invasion_warning slot for saveload.
void __test_invasion_warning_force(int idx, int months_to_go, int warning_years, int handled) {
    if (idx < 0 || idx >= (int)g_invasions.warnings.size()) {
        return;
    }
    auto& w = g_invasions.warnings[idx];
    w = {};
    w.in_use = true;
    w.handled = handled != 0;
    w.months_to_go = months_to_go;
    w.warning_years = warning_years;
    w.invasion_path_id = 3;
    w.invasion_id = 5;
    w.empire_object_id = 42;
    w.image_id = 7;
    w.pos = {11, 22};
    w.year_notified = 1400;
    w.month_notified = 4;
}
ANK_FUNCTION_4(__test_invasion_warning_force);

int __test_invasion_warning_months_to_go(int idx) {
    if (idx < 0 || idx >= (int)g_invasions.warnings.size()) {
        return -1;
    }
    const auto& w = g_invasions.warnings[idx];
    return w.in_use ? w.months_to_go : -1;
}
ANK_FUNCTION_1(__test_invasion_warning_months_to_go);

int __test_invasion_warning_handled(int idx) {
    if (idx < 0 || idx >= (int)g_invasions.warnings.size()) {
        return -1;
    }
    const auto& w = g_invasions.warnings[idx];
    return w.in_use ? (w.handled ? 1 : 0) : -1;
}
ANK_FUNCTION_1(__test_invasion_warning_handled);

int __test_invasion_warning_pos_x(int idx) {
    if (idx < 0 || idx >= (int)g_invasions.warnings.size()) {
        return -999;
    }
    return g_invasions.warnings[idx].pos.x;
}
ANK_FUNCTION_1(__test_invasion_warning_pos_x);

void __test_clear_enemy_formations() {
    for (int fi = 1; fi < MAX_FORMATIONS; ++fi) {
        formation* m = formation_get(fi);
        if (!m || !m->in_use || m->is_herd || m->own_batalion) {
            continue;
        }
        for (int fig = 0; fig < m->num_figures; ++fig) {
            if (m->figures[fig] > 0) {
                figure* f = figure_get(m->figures[fig]);
                if (f) {
                    f->poof();
                }
            }
        }
        g_formations.clear(fi);
    }
    // Also poof enemy figures that still reference a formation (pre-calculate state).
    for (int i = 1; i < MAX_FIGURES; ++i) {
        figure* f = figure_get(i);
        if (!f || !f->is_alive() || f->formation_id <= 0) {
            continue;
        }
        formation* m = formation_get(f->formation_id);
        if (m && !m->own_batalion && !m->is_herd) {
            f->poof();
        }
    }
    g_formations.calculate_figures();
}
ANK_FUNCTION(__test_clear_enemy_formations);

static void __test_poof_kingdome_figures() {
    for (int i = 1; i < MAX_FIGURES; ++i) {
        figure* f = figure_get(i);
        if (!f || !f->is_valid()) {
            continue;
        }
        if (figure_is_kingdome_army(f->type)) {
            f->poof();
        }
    }
}
ANK_FUNCTION(__test_poof_kingdome_figures);

int __test_count_enemy_figures() {
    g_formations.calculate_figures();
    int n = 0;
    for (int i = 1; i < MAX_FIGURES; ++i) {
        figure* f = figure_get(i);
        if (!f || !f->is_alive() || f->formation_id <= 0) {
            continue;
        }
        formation* m = formation_get(f->formation_id);
        if (m && m->in_use && !m->own_batalion && !m->is_herd) {
            ++n;
        }
    }
    return n;
}
ANK_FUNCTION(__test_count_enemy_figures);

void __test_set_scenario_enemy_id(int enemy_id) {
    g_scenario.enemy_id = (e_enemy_type)enemy_id;
}
ANK_FUNCTION_1(__test_set_scenario_enemy_id);

void __test_set_army_buildings_destroyed(int invasion_id, int count) {
    if (invasion_id <= 0 || invasion_id >= enemy_armies_t::MAX_ENEMY_ARMIES) {
        return;
    }
    enemy_army* army = enemy_army_get_editable((uint8_t)invasion_id);
    army->buildings_destroyed = (uint8_t)std::clamp(count, 0, 255);
}
ANK_FUNCTION_2(__test_set_army_buildings_destroyed);

// Place a gatehouse road-pair at (x,y)/(x+1,y) with flanking walls, claim the OG 2x2 footprint.
// Returns the number of TERRAIN_GATEHOUSE tiles in the 2x2 (expect 4).
static int __test_gatehouse_place_2x2(int type, int x, int y) {
    if (x < 1 || y < 1) {
        return 0;
    }

    const e_building_type gate_type = (e_building_type)type;
    const tile2i road_a(x, y);
    const tile2i road_b(x + 1, y);
    const tile2i side_a(x, y - 1);
    const tile2i side_b(x + 1, y - 1);

    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = 0; dx <= 1; dx++) {
            const tile2i t(x + dx, y + dy);
            map_terrain_remove(t, TERRAIN_CLEARABLE);
            map_building_set(t.grid_offset(), 0);
        }
    }
    map_terrain_add(side_a, TERRAIN_WALL);
    map_terrain_add(side_b, TERRAIN_WALL);
    map_terrain_add(road_a, TERRAIN_ROAD);
    map_terrain_add(road_b, TERRAIN_ROAD);

    building* part_a = building_create(gate_type, road_a, 0);
    building* part_b = building_create(gate_type, road_b, 0);
    if (!part_a || !part_b || part_a->id <= 0 || part_b->id <= 0) {
        return 0;
    }

    add_building(part_a, 0, 0);
    add_building(part_b, 0, 0);
    part_a->state = BUILDING_STATE_VALID;
    part_b->state = BUILDING_STATE_VALID;
    part_a->prev_part_building_id = 0;
    part_a->next_part_building_id = part_b->id;
    part_b->prev_part_building_id = part_a->id;
    part_b->next_part_building_id = 0;
    part_a->orientation = 1;

    building_gatehouse::claim_2x2_footprint(*part_a, *part_b);

    tile2i origin(x, y - 1);
    int count = 0;
    for (int dy = 0; dy < 2; dy++) {
        for (int dx = 0; dx < 2; dx++) {
            if (map_terrain_is(origin.shifted(dx, dy), TERRAIN_GATEHOUSE)) {
                count++;
            }
        }
    }
    return count;
}
ANK_FUNCTION_3(__test_gatehouse_place_2x2);

static int __test_mud_gatehouse_place_2x2(int x, int y) {
    return __test_gatehouse_place_2x2(BUILDING_MUD_GATEHOUSE, x, y);
}
ANK_FUNCTION_2(__test_mud_gatehouse_place_2x2);

extern int g_tower_sentry_request;

static void __test_tower_sentry_request_clear() {
    g_tower_sentry_request = 0;
}
ANK_FUNCTION(__test_tower_sentry_request_clear);

static int __test_tower_sentry_request_get() {
    return building_barracks_has_tower_sentry_request();
}
ANK_FUNCTION(__test_tower_sentry_request_get);

static void __test_warship_set_order(int fid, int order) {
    figure* f = figure_get(fid);
    auto* warship = f ? smart_cast<figure_warship>(f) : nullptr;
    if (warship) {
        warship->set_order(order);
    }
}
ANK_FUNCTION_2(__test_warship_set_order);

static int __test_warship_get_secondary_action(int fid) {
    figure* f = figure_get(fid);
    auto* warship = f ? smart_cast<figure_warship>(f) : nullptr;
    return warship ? warship->runtime_data().secondary_action : 0;
}
ANK_FUNCTION_1(__test_warship_get_secondary_action);

static void __test_warship_force_low_hull(int fid) {
    figure* f = figure_get(fid);
    auto* warship = f ? smart_cast<figure_warship>(f) : nullptr;
    if (warship) {
        const int max_damage = warship->base.max_damage();
        warship->base.damage = (uint16_t)(max_damage - (max_damage * 15 / 100));
    }
}
ANK_FUNCTION_1(__test_warship_force_low_hull);

static int __test_enemy_chariot_refresh_cart(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive() || !f->dcast()) {
        return 0;
    }
    // Chariot update_animation sets OG cart trailer (pulls_cart).
    f->dcast()->update_animation();
    return (f->use_cart && f->cart_image_id > 0) ? 1 : 0;
}
ANK_FUNCTION_1(__test_enemy_chariot_refresh_cart);

static int __test_enemy_speed_multiplier(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return -1;
    }
    auto* en = smart_cast<figure_enemy>(f);
    if (!en) {
        return -1;
    }
    return en->enemy_speed_multiplier();
}
ANK_FUNCTION_1(__test_enemy_speed_multiplier);

static int __test_elephant_trample(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_ENEMY_EGYPTIAN_ELEPHANT) {
        return 0;
    }
    // Type check above: leaf is figure_egyptian_elephant ? figure_enemy_elephant.
    auto* el = static_cast<figure_enemy_elephant*>(f->dcast());
    if (!el) {
        return 0;
    }
    el->trample_adjacent(true);
    return 1;
}
ANK_FUNCTION_1(__test_elephant_trample);

// Verify Julius-parity missile spawn args: create(shooter_id, shooter_tile, dst).
// Returns 1 if a FIGURE_SPEAR/ARROW exists with shooter_id == fid on the spearman's tile.
static int __test_spearman_fire_initial_missile(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return 0;
    }
    auto* sp = smart_cast<figure_enemy_spearman>(f);
    if (!sp) {
        return 0;
    }

    const e_figure_type want = sp->missile_type();
    auto target = figure_combat_get_missile_target_for_enemy(f, 10, g_city.figures.soldiers < 4);
    if (!target.fid || !target.tile.valid()) {
        return 0;
    }

    // Same create args as fixed figure_enemy_spearman::enemy_initial.
    auto* missile = figure_missile::create(fid, f->tile, target.tile, want);
    if (!missile) {
        return 0;
    }
    if (missile->runtime_data().shooter_id != fid) {
        return 0;
    }
    if (missile->base.tile != f->tile) {
        return 0;
    }
    return 1;
}
ANK_FUNCTION_1(__test_spearman_fire_initial_missile);

// Drive OG archer INITIAL shoot path: wait_ticks_missile past delay ? FIGURE_SPEAR + missile_fired.
static int __test_enemy_archer_fire_initial_missile(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return 0;
    }
    auto* ar = smart_cast<figure_enemy_archer>(f);
    if (!ar) {
        return 0;
    }
    if (ar->missile_type() != FIGURE_SPEAR) {
        return 0;
    }

    formation* m = formation_get(f->formation_id > 0 ? f->formation_id : 1);
    f->action_state = ACTION_0_ENEMY_ARCHER_INITIAL;
    f->wait_ticks = 50;
    f->wait_ticks_missile = (uint8_t)ar->missile_delay();
    f->attack_image_offset = 0;

    const int spears_before = __test_count_figures(FIGURE_SPEAR);
    const int missile_fired_before = m->missile_fired;
    ar->enemy_initial(m);
    if (__test_count_figures(FIGURE_SPEAR) != spears_before + 1) {
        return 0;
    }
    if (m->missile_fired <= missile_fired_before) {
        return 0;
    }

    // ACTION_3 is melee chase ? must not spawn another spear.
    f->action_state = ACTION_3_ENEMY_ARCHER_ATTACKING;
    m->recent_fight = 1;
    const int spears_mid = __test_count_figures(FIGURE_SPEAR);
    ar->enemy_fighting(m);
    if (__test_count_figures(FIGURE_SPEAR) != spears_mid) {
        return 0;
    }
    return 1;
}
ANK_FUNCTION_1(__test_enemy_archer_fire_initial_missile);

// Spawn a missile on dst (same tile as target) so the next action tick can hit.
static int __test_missile_create(int shooter_fid, int type, int dst_x, int dst_y) {
    figure* shooter = figure_get(shooter_fid);
    if (!shooter || !shooter->is_alive()) {
        return 0;
    }
    tile2i dst(dst_x, dst_y);
    auto* missile = figure_missile::create(shooter_fid, dst, dst, (e_figure_type)type);
    return missile ? missile->id() : 0;
}
ANK_FUNCTION_4(__test_missile_create);

// Returns figure type of OG javelin attack target on tile, or 0.
static int __test_javelin_target_type_at(int x, int y) {
    figure_id tid = javelin_find_attack_target(tile2i(x, y));
    figure* f = tid ? figure_get(tid) : nullptr;
    return f ? (int)f->type : 0;
}
ANK_FUNCTION_2(__test_javelin_target_type_at);

static int __test_formation_get_experience(int formation_id) {
    formation* m = formation_get(formation_id);
    return m ? m->experience : -1;
}
ANK_FUNCTION_1(__test_formation_get_experience);

static void __test_barracks_request_tower_sentry() {
    building_barracks_request_tower_sentry();
}
ANK_FUNCTION(__test_barracks_request_tower_sentry);

static int __test_constable_try_arrest(int constable_id, int max_distance, int force) {
    figure* f = figure_get(constable_id);
    if (!f || !f->is_alive() || f->type != FIGURE_CONSTABLE) {
        return 0;
    }
    return figure_constable(f).try_arrest_criminal(max_distance, force != 0) ? 1 : 0;
}
ANK_FUNCTION_3(__test_constable_try_arrest);

static int __test_soldier_combat_target(int x, int y, int max_distance) {
    tile2i tile(x, y);
    if (!tile.valid()) {
        tile.set(g_scenario.map.width / 2, g_scenario.map.height / 2);
    }
    return figure_combat_get_target_for_soldier(tile, max_distance > 0 ? max_distance : 8);
}
ANK_FUNCTION_3(__test_soldier_combat_target);

static int __test_city_kingdome_soldiers() {
    return g_city.figures.kingdome_soldiers;
}
ANK_FUNCTION(__test_city_kingdome_soldiers);

static int __test_kingdome_invasion_favour_only() {
    return g_city.kingdome.invasion.favour_only;
}
ANK_FUNCTION(__test_kingdome_invasion_favour_only);

static int __test_kingdome_invasion_size() {
    return g_city.kingdome.invasion.size;
}
ANK_FUNCTION(__test_kingdome_invasion_size);

static int __test_kingdome_invasion_days_until() {
    return g_city.kingdome.invasion.days_until_invasion;
}
ANK_FUNCTION(__test_kingdome_invasion_days_until);

// Tests share one city session, so a run that spawned a kingdome invasion leaves its
// bookkeeping behind for whoever comes next.
static void __test_kingdome_invasion_reset() {
    g_city.kingdome.invasion = {};
}
ANK_FUNCTION(__test_kingdome_invasion_reset);

static void __test_process_kingdome_invasion() {
    g_city.kingdome.process_invasion();
}
ANK_FUNCTION(__test_process_kingdome_invasion);

static void __test_kingdome_set_kills_to_size() {
    auto& inv = g_city.kingdome.invasion;
    if (inv.size > 0) {
        inv.soldiers_killed = inv.size;
    }
}
ANK_FUNCTION(__test_kingdome_set_kills_to_size);

static void __test_transport_wharf_spawn_figure(int bid) {
    building* b = building_get(bid);
    auto* wharf = (b && b->is_valid()) ? b->dcast_transport_wharf() : nullptr;
    if (!wharf) {
        return;
    }
    b->has_road_access = true;
    if (!b->road_access.valid()) {
        b->road_access = b->tile;
    }
    if (b->road_network_id <= 0) {
        b->road_network_id = 1;
    }
    if (b->distance_from_entry <= 0) {
        b->distance_from_entry = 1;
    }
    wharf->spawn_figure();
}
ANK_FUNCTION_1(__test_transport_wharf_spawn_figure);

static void __test_transport_wharf_update_month(int bid) {
    building* b = building_get(bid);
    auto* wharf = (b && b->is_valid()) ? b->dcast_transport_wharf() : nullptr;
    if (!wharf) {
        return;
    }
    wharf->update_month();
}
ANK_FUNCTION_1(__test_transport_wharf_update_month);

static int __test_transport_ships_requested() {
    return g_city.buildings.transport_ships_requested;
}
ANK_FUNCTION(__test_transport_ships_requested);

static void __test_transport_ships_requested_set(int value) {
    g_city.buildings.transport_ships_requested = (int8_t)value;
}
ANK_FUNCTION_1(__test_transport_ships_requested_set);

static void __test_warship_wharf_spawn_figure(int bid) {
    building* b = building_get(bid);
    auto* wharf = (b && b->is_valid()) ? b->dcast_warship_wharf() : nullptr;
    if (!wharf) {
        return;
    }
    b->has_road_access = true;
    if (!b->road_access.valid()) {
        b->road_access = b->tile;
    }
    if (b->road_network_id <= 0) {
        b->road_network_id = 1;
    }
    if (b->distance_from_entry <= 0) {
        b->distance_from_entry = 1;
    }
    wharf->spawn_figure();
}
ANK_FUNCTION_1(__test_warship_wharf_spawn_figure);

static void __test_warship_wharf_update_month(int bid) {
    building* b = building_get(bid);
    auto* wharf = (b && b->is_valid()) ? b->dcast_warship_wharf() : nullptr;
    if (!wharf) {
        return;
    }
    wharf->update_month();
}
ANK_FUNCTION_1(__test_warship_wharf_update_month);

static int __test_warships_requested() {
    return g_city.buildings.warships_requested;
}
ANK_FUNCTION(__test_warships_requested);

static void __test_warships_requested_set(int value) {
    g_city.buildings.warships_requested = (int8_t)value;
}
ANK_FUNCTION_1(__test_warships_requested_set);

static building_recruiter* __test_recruiter(int bid) {
    building* b = building_get(bid);
    return (b && b->is_valid()) ? b->dcast_recruiter() : nullptr;
}

static int __test_recruiter_pick_batalion(int bid) {
    building_recruiter* r = __test_recruiter(bid);
    return r ? r->get_closest_batalion_needing_soldiers() : -1;
}
ANK_FUNCTION_1(__test_recruiter_pick_batalion);

static int __test_recruiter_create_soldier(int bid) {
    building_recruiter* r = __test_recruiter(bid);
    return (r && r->create_soldier()) ? 1 : 0;
}
ANK_FUNCTION_1(__test_recruiter_create_soldier);

static int __test_recruiter_create_tower_sentry(int bid) {
    building_recruiter* r = __test_recruiter(bid);
    return (r && r->create_tower_sentry()) ? 1 : 0;
}
ANK_FUNCTION_1(__test_recruiter_create_tower_sentry);

static void __test_fort_update_recruit_status(int bid) {
    building* b = building_get(bid);
    if (b && b->is_valid() && b->dcast_fort()) {
        formation_batalion_update_recruit_status(b);
    }
}
ANK_FUNCTION_1(__test_fort_update_recruit_status);

static void __test_formation_set_experience(int formation_id, int experience) {
    formation* m = formation_get(formation_id);
    if (!m || !m->in_use) {
        return;
    }
    m->experience = (uint16_t)std::max(0, experience);
}
ANK_FUNCTION_2(__test_formation_set_experience);

static void __test_formation_set_ship_figure(int formation_id, int ship_figure_id) {
    formation* m = formation_get(formation_id);
    if (!m || !m->in_use) {
        return;
    }
    m->ship_figure_id = (int16_t)ship_figure_id;
}
ANK_FUNCTION_2(__test_formation_set_ship_figure);

static void __test_formation_set_in_distant_battle(int formation_id, int value) {
    formation* m = formation_get(formation_id);
    if (!m || !m->in_use) {
        return;
    }
    m->in_distant_battle = value ? 1 : 0;
}
ANK_FUNCTION_2(__test_formation_set_in_distant_battle);

bool __test_enemy_figure_registered(int type) {
    tile2i tile(g_scenario.map.width / 2, g_scenario.map.height / 2);
    figure* f = figure_create((e_figure_type)type, tile, 0);
    if (!f) {
        return false;
    }

    figure_impl* impl = f->dcast();
    bool is_enemy = impl && impl->dcast_enemy();
    f->poof();
    return is_enemy;
}
ANK_FUNCTION_1(__test_enemy_figure_registered);

namespace {

    tile2i test_find_or_make_water_strip(int* out_cx, int* out_cy) {
        const int cx = g_scenario.map.width / 2;
        const int cy = g_scenario.map.height / 2;
        const int x0 = cx - 2;
        for (int dy = 0; dy < 2; dy++) {
            for (int dx = 0; dx < 6; dx++) {
                tile2i t(x0 + dx, cy + dy);
                map_terrain_add(t, TERRAIN_WATER);
            }
        }
        // Land strip above water for disembark.
        for (int dx = 0; dx < 6; dx++) {
            tile2i land(x0 + dx, cy - 1);
            map_terrain_remove(land, TERRAIN_WATER);
        }
        map_water_rebuild_shores();
        if (out_cx) {
            *out_cx = cx;
        }
        if (out_cy) {
            *out_cy = cy;
        }
        return tile2i(cx, cy);
    }

} // namespace

int __test_spawn_warship_on_water() {
    tile2i water = test_find_or_make_water_strip(nullptr, nullptr);
    figure* f = figure_create(FIGURE_WARSHIP, water, DIR_0_TOP_RIGHT);
    return f && f->is_valid() ? f->id : 0;
}
ANK_FUNCTION(__test_spawn_warship_on_water);

// Spawn enemy transport with N soldiers loaded and sailing to a nearby shore.
// Returns transport figure id, or 0 on failure.
int __test_enemy_transport_spawn_loaded(int enemy_type, int soldier_count) {
    int cx = 0;
    int cy = 0;
    tile2i water = test_find_or_make_water_strip(&cx, &cy);
    tile2i landing = tile2i(cx, cy);
    tile2i shore(cx, cy - 1);

    e_enemy_type enemy = (e_enemy_type)enemy_type;
    e_figure_type ship_type = enemy_transport_type_for(enemy);
    e_figure_type soldier_type = FIGURE_ENEMY_HITTITE_SPEARMAN;
    const enemy_properties_t& props = g_invasions.get_prop(enemy);
    if (props.figure_types[0] != FIGURE_NONE) {
        soldier_type = props.figure_types[0];
    }

    if (soldier_count < 1) {
        soldier_count = 1;
    }
    if (soldier_count > 8) {
        soldier_count = 8;
    }

    int formation_id = formation_create_enemy(soldier_type, shore, FORMATION_ENEMY_MOB, DIR_0_TOP_RIGHT, enemy,
      FORMATION_ATTACK_RANDOM, 23, 1);
    if (formation_id <= 0) {
        return 0;
    }

    for (int i = 0; i < soldier_count; i++) {
        figure* s = figure_create(soldier_type, water, DIR_0_TOP_RIGHT);
        if (!s || !s->is_valid()) {
            continue;
        }
        s->faction_id = 0;
        s->formation_id = formation_id;
        s->index_in_formation = (uint8_t)i;
        s->action_state = ACTION_152_ENEMY_WAITING;
        s->wait_ticks = 30000;
        s->formation_at_rest = 1;
        s->allow_move_type = EMOVE_AMPHIBIAN;
        s->set_flag(e_figure_flag_invisible);
    }

    auto abort_test_formation = [formation_id]() {
        for (figure* f : map_figures()) {
            if (f && f->is_alive() && f->formation_id == formation_id) {
                f->set_flag(e_figure_flag_invisible, false);
                f->kill();
            }
        }
        formation* m = formation_get(formation_id);
        if (m && m->in_use) {
            m->num_figures = 0;
            for (int fi = 0; fi < formation::max_figures_count; fi++) {
                m->figures[fi] = 0;
            }
            m->in_use = false;
        }
    };

    figure* ship = figure_create(ship_type, water, DIR_0_TOP_RIGHT);
    if (!ship || !ship->is_valid()) {
        abort_test_formation();
        return 0;
    }

    auto* transport = smart_cast<figure_enemy_transport>(ship);
    if (!transport) {
        ship->kill();
        abort_test_formation();
        return 0;
    }
    if (!transport->load_formation(formation_id)) {
        ship->kill();
        abort_test_formation();
        return 0;
    }
    if (!transport->sail_to_landing(landing)) {
        ship->kill();
        abort_test_formation();
        return 0;
    }
    return ship->id;
}
ANK_FUNCTION_2(__test_enemy_transport_spawn_loaded);

int __test_enemy_transport_has_troops(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return 0;
    }
    auto* t = smart_cast<figure_enemy_transport>(f);
    return t && t->has_troops() ? 1 : 0;
}
ANK_FUNCTION_1(__test_enemy_transport_has_troops);

static int g_test_player_transport_company_id = 0;
static int g_test_player_transport_water_x = 0;
static int g_test_player_transport_water_y = 0;

// Spawn a moored player transport + own infantry company on adjacent shore.
// Returns transport figure id (0 on failure). Company id via __test_player_transport_company_id().
int __test_player_transport_spawn_for_embark(int soldier_count) {
    g_test_player_transport_company_id = 0;

    int cx = 0;
    int cy = 0;
    tile2i water = test_find_or_make_water_strip(&cx, &cy);
    g_test_player_transport_water_x = cx;
    g_test_player_transport_water_y = cy;

    if (soldier_count < 1) {
        soldier_count = 1;
    }
    if (soldier_count > 8) {
        soldier_count = 8;
    }

    // Prefer a clear shore tile adjacent to embark water (Chebyshev distance 1).
    tile2i shore = tile2i::invalid;
    for (int dx = -1; dx <= 1; dx++) {
        tile2i cand(cx + dx, cy - 1);
        if (!cand.valid()) {
            continue;
        }
        if (map_terrain_is(cand, TERRAIN_WATER | TERRAIN_DEEPWATER)) {
            continue;
        }
        if (map_building_at(cand) > 0) {
            continue;
        }
        shore = cand;
        break;
    }
    if (!shore.valid()) {
        shore = tile2i(cx, cy - 1);
        int bid = map_building_at(shore);
        if (bid > 0) {
            building* old = building_get(bid);
            if (old && old->id) {
                old->state = BUILDING_STATE_UNUSED;
            }
            map_building_tiles_remove(bid, shore);
        }
    }

    // Minimal home wharf so figure_action can run LEAVING/ANCHORED.
    building* wharf_b = building_create(BUILDING_TRANSPORT_WHARF, shore, 0);
    if (!wharf_b || !wharf_b->id) {
        logs::info("[test:103] spawn fail: wharf create");
        return 0;
    }
    add_building(wharf_b, 0, 0);
    wharf_b->state = BUILDING_STATE_VALID;
    wharf_b->num_workers = 10;
    wharf_b->max_workers = 10;
    if (auto* wharf = wharf_b->dcast_transport_wharf()) {
        wharf->set_water_access_tiles({water, water});
    }

    formation* m = formation_get_free(1);
    if (!m || !m->id) {
        logs::info("[test:103] spawn fail: formation");
        return 0;
    }
    g_formations.clear(m->id);
    m->faction_id = 1;
    m->in_use = 1;
    m->own_batalion = true;
    m->figure_type = FIGURE_INFANTRY;
    m->layout = FORMATION_DOUBLE_LINE_1;
    m->morale = 50;
    m->is_at_fort = 0;
    m->batalion_id = m->id;
    m->max_figures = 16;
    m->tile = shore;
    m->standard_tile = shore;
    m->home = shore;
    g_test_player_transport_company_id = m->id;

    int spawned_soldiers = 0;
    for (int i = 0; i < soldier_count; i++) {
        figure* s = figure_create(FIGURE_INFANTRY, shore, DIR_0_TOP_RIGHT);
        if (!s) {
            continue;
        }
        s->faction_id = 1;
        s->formation_id = m->id;
        s->index_in_formation = (uint8_t)formation_add_figure(m->id, s->id, 1, 0, s->max_damage());
        s->action_state = ACTION_4_SOLDIER_AT_STANDARD;
        s->formation_at_rest = 1;
        spawned_soldiers++;
    }
    if (spawned_soldiers <= 0) {
        logs::info("[test:103] spawn fail: soldiers");
        return 0;
    }

    figure* ship_f = figure_create(FIGURE_TRANSPORT_SHIP, water, DIR_0_TOP_RIGHT);
    if (!ship_f || !ship_f->is_valid()) {
        logs::info("[test:103] spawn fail: ship create");
        return 0;
    }

    auto* ship = smart_cast<figure_transport_ship>(ship_f);
    if (!ship) {
        logs::info("[test:103] spawn fail: ship cast");
        return 0;
    }

    ship_f->set_home(wharf_b->id);
    wharf_b->set_figure(BUILDING_SLOT_BOAT, ship_f);
    ship_f->source_tile = water;
    ship_f->advance_action(ACTION_213_TRANSPORT_SHIP_MOORED);
    return ship_f->id;
}
ANK_FUNCTION_1(__test_player_transport_spawn_for_embark);

int __test_player_transport_company_id() {
    return g_test_player_transport_company_id;
}
ANK_FUNCTION(__test_player_transport_company_id);

int __test_player_transport_water_x() {
    return g_test_player_transport_water_x;
}
ANK_FUNCTION(__test_player_transport_water_x);

int __test_player_transport_water_y() {
    return g_test_player_transport_water_y;
}
ANK_FUNCTION(__test_player_transport_water_y);

// Snap player transport to its sail destination. Keep GOING_TO_LANDING so the next
// action tick lands troops immediately (OG: disembark on arrival, no timer).
void __test_transport_ship_snap_to_destination(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return;
    }
    auto* ship = smart_cast<figure_transport_ship>(f);
    if (!ship) {
        return;
    }
    if (f->destination_tile.valid()) {
        f->tile = f->destination_tile;
        f->previous_tile = f->destination_tile;
    }
    if (ship->has_troops()) {
        const int state = f->action_state;
        // Keep kingdom-request / return states; only force landing for ordinary sail-home snaps.
        if (state != ACTION_221_TRANSPORT_SHIP_GOING_TO_REQUEST && state != ACTION_222_TRANSPORT_SHIP_AWAY_ON_REQUEST
            && state != ACTION_223_TRANSPORT_SHIP_RETURNING_FROM_REQUEST
            && state != ACTION_220_TRANSPORT_SHIP_RETURNING_TO_LANDING) {
            f->advance_action(ACTION_219_TRANSPORT_SHIP_GOING_TO_LANDING);
        }
    }
    f->direction = DIR_FIGURE_NONE;
    f->route_remove();
}
ANK_FUNCTION_1(__test_transport_ship_snap_to_destination);

void __test_formation_set_empire_service(int formation_id, int value) {
    formation* m = formation_get(formation_id);
    if (!m || !m->in_use) {
        return;
    }
    m->empire_service = value ? 1 : 0;
}
ANK_FUNCTION_2(__test_formation_set_empire_service);

int __test_formation_request_event_id(int formation_id) {
    formation* m = formation_get(formation_id);
    if (!m || !m->in_use) {
        return -1;
    }
    return m->request_event_id;
}
ANK_FUNCTION_1(__test_formation_request_event_id);

int __test_transport_ship_request_event_id(int ship_id) {
    figure* f = figure_get(ship_id);
    auto* ship = f ? smart_cast<figure_transport_ship>(f) : nullptr;
    if (!ship) {
        return -1;
    }
    return ship->runtime_data().request_event_id;
}
ANK_FUNCTION_1(__test_transport_ship_request_event_id);

void __test_legion_dispatch_to_request(int event_id) {
    formation_legions_dispatch_to_request(event_id);
}
ANK_FUNCTION_1(__test_legion_dispatch_to_request);

void __test_legion_return_from_request(int event_id) {
    formation_legions_return_from_request(event_id);
}
ANK_FUNCTION_1(__test_legion_return_from_request);

int __test_formation_request_strength(int event_id) {
    return formation_request_strength(event_id, nullptr, nullptr);
}
ANK_FUNCTION_1(__test_formation_request_strength);

void __transport_ship_set_evade(int ship_id) {
    figure* f = figure_get(ship_id);
    if (!f) {
        return;
    }
    if (auto* ship = smart_cast<figure_transport_ship>(f)) {
        ship->set_evade_order();
    }
}
ANK_FUNCTION_1(__transport_ship_set_evade)

void __transport_ship_move_to(int ship_id, int x, int y) {
    figure* f = figure_get(ship_id);
    if (!f) {
        return;
    }
    if (auto* ship = smart_cast<figure_transport_ship>(f)) {
        ship->move_to_tile(tile2i(x, y));
    }
}
ANK_FUNCTION_3(__transport_ship_move_to)

void __transport_ship_set_repair(int ship_id) {
    figure* f = figure_get(ship_id);
    if (!f) {
        return;
    }
    if (auto* ship = smart_cast<figure_transport_ship>(f)) {
        ship->set_repair_order();
    }
}
ANK_FUNCTION_1(__transport_ship_set_repair)

int __test_formation_alive_count(int formation_id) {
    formation* m = formation_get(formation_id);
    if (!m || !m->in_use) {
        return 0;
    }
    int alive = 0;
    for (int i = 0; i < formation::max_figures_count && m->figures[i]; i++) {
        figure* f = figure_get(m->figures[i]);
        if (f && f->is_alive()) {
            alive++;
        }
    }
    return alive;
}
ANK_FUNCTION_1(__test_formation_alive_count)

int __test_count_visible_enemy_soldiers() {
    int count = 0;
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure* f = figure_get(i);
        if (!f || !f->is_alive()) {
            continue;
        }
        if (!f->is_visible()) {
            continue;
        }
        if (f->is_boat() || f->allow_move_type == EMOVE_WATER || f->allow_move_type == EMOVE_DEEPWATER) {
            continue;
        }
        if (smart_cast<figure_enemy_transport>(f) || smart_cast<figure_enemy_warship>(f)) {
            continue;
        }
        // Prefer flag, fall back to static params (fresh spawn / flag edge cases).
        if (!f->is_enemy() && !f->params().is_enemy) {
            continue;
        }
        count++;
    }
    return count;
}
ANK_FUNCTION(__test_count_visible_enemy_soldiers);

int __test_start_sea_invasion(int enemy_type, int size) {
    int cx = 0;
    int cy = 0;
    tile2i water = test_find_or_make_water_strip(&cx, &cy);
    g_scenario.invasion_points_sea.clear();
    g_scenario.invasion_points_sea.push_back(water);
    g_scenario.disembark_points.clear();
    g_scenario.disembark_points.push_back(tile2i(cx, cy - 1));

    invasion_opts_t opts;
    opts.mode = ATTACK_TYPE_ENEMIES;
    opts.enemy_type = (e_enemy_type)enemy_type;
    opts.size = size > 0 ? size : 8;
    opts.via_sea = true;
    opts.invasion_id = 23;
    opts.attack_type = FORMATION_ATTACK_RANDOM;
    opts.kind = INVASION_KIND_FOREIGN;
    tile2i tile = scenario_start_invasion_impl(opts);
    return tile.valid() ? 1 : 0;
}
ANK_FUNCTION_2(__test_start_sea_invasion);

int __test_count_enemy_transports() {
    int count = 0;
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure* f = figure_get(i);
        if (f && f->is_alive() && smart_cast<figure_enemy_transport>(f)) {
            count++;
        }
    }
    return count;
}
ANK_FUNCTION(__test_count_enemy_transports);

int __test_count_enemy_warships() {
    int count = 0;
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure* f = figure_get(i);
        if (f && f->is_alive() && smart_cast<figure_enemy_warship>(f)) {
            count++;
        }
    }
    return count;
}
ANK_FUNCTION(__test_count_enemy_warships);

int __test_spawn_enemy_warship_on_water(int enemy_type) {
    int cx = 0;
    int cy = 0;
    tile2i water = test_find_or_make_water_strip(&cx, &cy);
    e_figure_type ftype = enemy_warship_type_for((e_enemy_type)enemy_type);
    figure* f = figure_create(ftype, water, DIR_0_TOP_RIGHT);
    return f && f->is_valid() ? f->id : 0;
}
ANK_FUNCTION_1(__test_spawn_enemy_warship_on_water);

void __test_seth_sink_all_ships() {
    god_seth.sink_all_ships();
}
ANK_FUNCTION(__test_seth_sink_all_ships);

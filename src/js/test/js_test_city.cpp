#include "js/test/js_test_common.h"

#include "building/building_barracks.h"
#include "building/building_bazaar.h"
#include "building/building_fishing_wharf.h"
#include "building/building_food_mill.h"
#include "building/building_fort.h"
#include "building/building_gatehouse.h"
#include "building/building_granary.h"
#include "building/building_house.h"
#include "building/building_shipyard.h"
#include "building/building_storage_yard.h"
#include "building/building_temple_complex.h"
#include "building/monument_mastaba.h"
#include "building/monument_obelisk.h"
#include "building/monument_pyramid.h"
#include "building/monument_royal_tomb.h"
#include "city/city.h"
#include "city/city_message.h"
#include "core/random.h"
#include "core/xstring.h"
#include "game/game.h"
#include "figure/figure_impl.h"
#include "figuretype/animal_asp.h"
#include "figuretype/animal_lion.h"
#include "figuretype/animal_scorpion.h"
#include "figuretype/figure_bricklayer.h"
#include "figuretype/figure_carpenter.h"
#include "figuretype/figure_cartpusher.h"
#include "figuretype/figure_docker.h"
#include "figuretype/figure_enemy_archer.h"
#include "figuretype/figure_enemy_elephant.h"
#include "figuretype/figure_enemy_spearman.h"
#include "figuretype/figure_enemy_transport.h"
#include "figuretype/figure_enemy_warship.h"
#include "figuretype/figure_ferry_boat.h"
#include "figuretype/figure_flotsam.h"
#include "figuretype/figure_frog.h"
#include "figuretype/figure_hunter.h"
#include "figuretype/figure_kingdome_trader.h"
#include "figuretype/figure_locust.h"
#include "figuretype/figure_trader_ship.h"
#include "figuretype/figure_transport_ship.h"
#include "figuretype/figure_war_ship.h"
#include "figuretype/figure_worker.h"
#include "scenario/request.h"
#include "scenario/scenario.h"
#include "scenario/scenario_event_manager.h"
#include "scenario/earthquake.h"
#include "grid/grid.h"
#include "grid/image.h"
#include "grid/terrain.h"


#include <algorithm>

void __test_set_treasury(int amount) {
    g_city.finance.treasury = amount;
}
ANK_FUNCTION_1(__test_set_treasury);

void __test_set_city_population(int amount) {
    g_city.population.current = amount;
}
ANK_FUNCTION_1(__test_set_city_population);

void __test_set_city_enemies(int count) {
    g_city.figures.enemies = (int16_t)count;
}
ANK_FUNCTION_1(__test_set_city_enemies);

int __test_request_cleared_seq() {
    return scenario_request_last_cleared().seq;
}
ANK_FUNCTION(__test_request_cleared_seq);

int __test_request_cleared_tag_id() {
    return scenario_request_last_cleared().tag_id;
}
ANK_FUNCTION(__test_request_cleared_tag_id);

int __test_request_cleared_resource() {
    return scenario_request_last_cleared().resource;
}
ANK_FUNCTION(__test_request_cleared_resource);

int __test_request_cleared_fulfilled() {
    return scenario_request_last_cleared().fulfilled;
}
ANK_FUNCTION(__test_request_cleared_fulfilled);

int __test_request_cleared_was_overdue() {
    return scenario_request_last_cleared().was_overdue;
}
ANK_FUNCTION(__test_request_cleared_was_overdue);

static event_ph_t* __test_find_request_by_tag(int tag) {
    for (int i = 0; i < g_scenario.events.events_count(); ++i) {
        event_ph_t* e = g_scenario.events.at(i);
        if (e && e->type == EVENT_TYPE_REQUEST && e->tag_id == tag) {
            return e;
        }
    }
    return nullptr;
}

int __test_request_exists(int tag) {
    return __test_find_request_by_tag(tag) ? 1 : 0;
}
ANK_FUNCTION_1(__test_request_exists);

int __test_request_is_active(int tag) {
    event_ph_t* e = __test_find_request_by_tag(tag);
    return (e && e->is_active) ? 1 : 0;
}
ANK_FUNCTION_1(__test_request_is_active);

int __test_request_months_left(int tag) {
    event_ph_t* e = __test_find_request_by_tag(tag);
    return e ? (int)e->quest_months_left : -1;
}
ANK_FUNCTION_1(__test_request_months_left);

int __test_request_state(int tag) {
    event_ph_t* e = __test_find_request_by_tag(tag);
    return e ? (int)e->event_state : -1;
}
ANK_FUNCTION_1(__test_request_state);

int __test_request_resource(int tag) {
    event_ph_t* e = __test_find_request_by_tag(tag);
    return e ? (int)e->item.value : -1;
}
ANK_FUNCTION_1(__test_request_resource);

int __test_request_amount(int tag) {
    event_ph_t* e = __test_find_request_by_tag(tag);
    return e ? (int)e->amount.value : -1;
}
ANK_FUNCTION_1(__test_request_amount);

int __test_request_sender_faction(int tag) {
    event_ph_t* e = __test_find_request_by_tag(tag);
    return e ? (int)e->sender_faction : -1;
}
ANK_FUNCTION_1(__test_request_sender_faction);

// Force overdue grace with months_left months remaining (for late-fulfill tests).
void __test_request_force_overdue(int tag, int months_left) {
    event_ph_t* e = __test_find_request_by_tag(tag);
    if (!e || !e->is_active) {
        return;
    }
    e->event_state = e_event_state_overdue;
    e->is_overdue = true;
    e->quest_months_left = (uint8_t)std::max(0, months_left);
}
ANK_FUNCTION_2(__test_request_force_overdue);

// Expire grace immediately ? refuse path on next process_active_request.
void __test_request_force_refuse_now(int tag) {
    event_ph_t* e = __test_find_request_by_tag(tag);
    if (!e || !e->is_active) {
        return;
    }
    e->event_state = e_event_state_overdue;
    e->is_overdue = true;
    e->quest_months_left = 0;
    g_scenario.events.process_active_request(e->event_id);
}
ANK_FUNCTION_1(__test_request_force_refuse_now);

// Tag-targeted fulfill (visible-index dispatch is ambiguous when a mission has many requests):
// the dispatched goods arrive at once.
void __test_request_force_fulfill(int tag, int as_late) {
    event_ph_t* e = __test_find_request_by_tag(tag);
    if (!e || !e->is_active) {
        return;
    }
    e->is_overdue = as_late != 0;
    e->event_state = as_late ? e_event_state_dispatched_late : e_event_state_dispatched;
    e->quest_months_left = 1;
    g_scenario.events.process_active_request(e->event_id);
}
ANK_FUNCTION_2(__test_request_force_fulfill);

// Advisor-style dispatch (RESOURCE_TROOPS + defeat ? distant battle; B8).
void __test_request_dispatch_by_tag(int tag) {
    event_ph_t* e = __test_find_request_by_tag(tag);
    if (!e || !e->is_active) {
        return;
    }
    scenario_request_dispatch_event(e->event_id);
}
ANK_FUNCTION_1(__test_request_dispatch_by_tag);

int __test_last_message_eventmsg_phrase_id() {
    const int n = city_message_count();
    if (n <= 0) {
        return -1;
    }
    return city_message_get(n - 1).eventmsg_phrase_id;
}
ANK_FUNCTION(__test_last_message_eventmsg_phrase_id);

static void __test_sentiment_set(int value) {
    g_city.sentiment.value = value;
}
ANK_FUNCTION_1(__test_sentiment_set);

static int __test_kingdom_rating() {
    return g_city.kingdome.rating;
}
ANK_FUNCTION(__test_kingdom_rating);

static void __test_kingdom_set_rating(int value) {
    g_city.kingdome.rating = (uint8_t)std::clamp(value, 0, 100);
}
ANK_FUNCTION_1(__test_kingdom_set_rating);

// Draws one crt rand() and returns the low 31 bits of the new state: output bits 16..30, peek gives bits 0..15.
// Bit 31 never reaches a later output, so JS can predict every following roll from this.
static int __test_crt_sync_state31() {
    const int high = anti_scum_random_15bit();
    const int low = anti_scum_random_15bit(false);
    return (high << 16) | low;
}
ANK_FUNCTION(__test_crt_sync_state31);

static void __test_crt_srand(int seed) {
    anti_scum_srand((uint32_t)seed);
}
ANK_FUNCTION_1(__test_crt_srand);

static int __test_ra_harsh_trade_months() {
    return g_city.religion.ra_harshly_reduced_trading_months_left;
}
ANK_FUNCTION(__test_ra_harsh_trade_months);

static int __test_ra_no_traders_months() {
    return g_city.religion.ra_no_traders_months_left;
}
ANK_FUNCTION(__test_ra_no_traders_months);

static void __test_ra_clear_curse_months() {
    g_city.religion.ra_harshly_reduced_trading_months_left = 0;
    g_city.religion.ra_no_traders_months_left = 0;
}
ANK_FUNCTION(__test_ra_clear_curse_months);

static void __test_house_calculate_culture_aggregates() {
    g_city.house_service_calculate_culture_aggregates();
}
ANK_FUNCTION(__test_house_calculate_culture_aggregates);

static void __test_update_religion_supply_houses() {
    g_city.buildings.update_religion_supply_houses();
}
ANK_FUNCTION(__test_update_religion_supply_houses);

static void __test_health_update_coverage() {
    g_city.health.update_coverage();
}
ANK_FUNCTION(__test_health_update_coverage);

static void __test_government_distribute_treasury() {
    g_city.government_distribute_treasury();
}
ANK_FUNCTION(__test_government_distribute_treasury);

static int __test_city_has_palace() {
    return g_city.buildings.has_palace() ? 1 : 0;
}
ANK_FUNCTION(__test_city_has_palace);

static void __test_set_god_status(int god, int status) {
    if (god < 0 || god >= MAX_GODS) {
        return;
    }
    g_city.religion.set_god_known((e_god)god, (e_god_status)status);
}
ANK_FUNCTION_2(__test_set_god_status);

static int __test_god_coverage_total(int god) {
    if (god < 0 || god >= MAX_GODS) {
        return -1;
    }
    g_city.buildings.update_counters();
    const auto& p = g_city.religion.gods[god].static_params();
    return g_city.religion.god_coverage_total((e_god)god, p.shrine_type, p.temple_type, p.complex_type);
}
ANK_FUNCTION_1(__test_god_coverage_total);

static void __test_scenario_var_set_string(pcstr name, pcstr value) {
    g_scenario.vars.set_string(name, value);
}
ANK_FUNCTION_2(__test_scenario_var_set_string);

static void __test_city_update_month() {
    g_city.update_month(game.simtime);
}
ANK_FUNCTION(__test_city_update_month);

static int __test_event_id_by_tag(int tag) {
    for (int i = 0; i < g_scenario.events.events_count(); i++) {
        if (g_scenario.events.at(i)->tag_id == tag) {
            return i;
        }
    }
    return -1;
}
ANK_FUNCTION_1(__test_event_id_by_tag);

static int __test_event_sweep_countdown(int event_id) {
    const event_ph_t* e = g_scenario.events.at(event_id);
    return e ? e->data.sweep.countdown : -1;
}
ANK_FUNCTION_1(__test_event_sweep_countdown);

static void __test_scenario_events_tick(int n) {
    for (int i = 0; i < n; i++) {
        g_scenario.events.update_tick();
    }
}
ANK_FUNCTION_1(__test_scenario_events_tick);

static int __test_blood_river_sweep_active() {
    return g_scenario.events.blood_river_sweep_active() ? 1 : 0;
}
ANK_FUNCTION(__test_blood_river_sweep_active);

static building_house* test_house(int bid) {
    building* b = building_get(bid);
    return (b && b->is_valid()) ? b->dcast_house() : nullptr;
}

static int __test_house_water_supply(int bid) {
    building_house* h = test_house(bid);
    return h ? h->runtime_data().water_supply : -1;
}
ANK_FUNCTION_1(__test_house_water_supply);

static void __test_house_set_water_supply(int bid, int v) {
    if (building_house* h = test_house(bid)) {
        h->runtime_data().water_supply = (uint8_t)v;
    }
}
ANK_FUNCTION_2(__test_house_set_water_supply);

static int __test_house_happiness(int bid) {
    building_house* h = test_house(bid);
    return h ? h->runtime_data().house_happiness : -1;
}
ANK_FUNCTION_1(__test_house_happiness);

static void __test_house_set_happiness(int bid, int v) {
    if (building_house* h = test_house(bid)) {
        h->runtime_data().house_happiness = (uint8_t)v;
    }
}
ANK_FUNCTION_2(__test_house_set_happiness);

static int __test_building_malaria_risk(int bid) {
    building* b = building_get(bid);
    return b ? b->malaria_risk : -1;
}
ANK_FUNCTION_1(__test_building_malaria_risk);

static void __test_set_earthquake_point(int x, int y) {
    g_scenario.earthquake_point = (x < 0 || y < 0) ? tile2i::invalid : tile2i(x, y);
}
ANK_FUNCTION_2(__test_set_earthquake_point);

static void __test_earthquake_tick(int n) {
    for (int i = 0; i < n; i++) {
        scenario_earthquake_process();
    }
}
ANK_FUNCTION_1(__test_earthquake_tick);

static int __test_event_state(int event_id) {
    const event_ph_t* e = g_scenario.events.at(event_id);
    return e ? (int)e->event_state : -1;
}
ANK_FUNCTION_1(__test_event_state);

// Front i of an earthquake event as x * 1000 + y.
static int __test_earthquake_front(int event_id, int i) {
    const event_ph_t* e = g_scenario.events.at(event_id);
    if (!e || i < 0 || i > 3) {
        return -1;
    }
    return e->data.earthquake.locations[2 * i] * 1000 + e->data.earthquake.locations[2 * i + 1];
}
ANK_FUNCTION_2(__test_earthquake_front);

static int __test_earthquake_duration(int event_id) {
    const event_ph_t* e = g_scenario.events.at(event_id);
    return e ? e->data.earthquake.duration : -1;
}
ANK_FUNCTION_1(__test_earthquake_duration);

static int __test_earthquake_tile_free(int x, int y) {
    return map_terrain_is(MAP_OFFSET(x, y), TERRAIN_ELEVATION | TERRAIN_ROCK | TERRAIN_WATER) ? 0 : 1;
}
ANK_FUNCTION_2(__test_earthquake_tile_free);

// Makes a tile meadow with a stale image id, to see whether a refresh redraws it.
static void __test_map_set_meadow(int x, int y, int image_id) {
    map_terrain_add(MAP_OFFSET(x, y), TERRAIN_MEADOW);
    map_image_set(MAP_OFFSET(x, y), image_id);
}
ANK_FUNCTION_3(__test_map_set_meadow);

static int __test_map_image(int x, int y) {
    return map_image_at(MAP_OFFSET(x, y));
}
ANK_FUNCTION_2(__test_map_image);

static int __test_gift_reply(int event_id, int button) {
    return g_scenario.events.gift_reply(event_id, (e_gift_button)button) ? 1 : 0;
}
ANK_FUNCTION_2(__test_gift_reply);

static int __test_treasury() {
    return g_city.finance.treasury.value;
}
ANK_FUNCTION(__test_treasury);

static int __test_house_tax_units(int bid) {
    auto* house = building_get(bid)->dcast_house();
    return house ? g_city.finance.house_monthly_tax_units(house) : -1;
}
ANK_FUNCTION_1(__test_house_tax_units);

// The house model of the current difficulty.
static int __test_house_model_value(int bid, pcstr field) {
    auto* house = building_get(bid)->dcast_house();
    if (!house) {
        return -1;
    }
    const xstring name(field);
    if (name == "prosperity")
        return house->model().prosperity;
    if (name == "tax_multiplier")
        return house->model().tax_multiplier;
    logs::error("[test] __test_house_model_value: unknown field %s", field);
    return -1;
}
ANK_FUNCTION_2(__test_house_model_value);

// Sets a per-difficulty scenario meta table to five copies of value; a negative value clears it.
static void __test_scenario_meta_tax(pcstr field, int value) {
    const xstring name(field);
    int_dcy* table = nullptr;
    if (name == "tax_percentage")
        table = &g_scenario.meta.tax_percentage;
    else if (name == "house_tax_multipliers")
        table = &g_scenario.meta.house_tax_multipliers;
    if (!table) {
        logs::error("[test] __test_scenario_meta_tax: unknown field %s", field);
        return;
    }
    table->value.clear();
    for (int i = 0; value >= 0 && i < 5; ++i) {
        table->value.push_back(value);
    }
}
ANK_FUNCTION_2(__test_scenario_meta_tax);

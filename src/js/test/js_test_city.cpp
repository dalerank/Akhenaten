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
#include "core/xstring.h"
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

#include <algorithm>

void __test_set_treasury(int amount) {
    g_city.finance.treasury = amount;
}
ANK_FUNCTION_1(__test_set_treasury);

void __test_set_city_population(int amount) {
    g_city.population.current = amount;
}
ANK_FUNCTION_1(__test_set_city_population);

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

// Tag-targeted fulfill (visible-index dispatch is ambiguous when a mission has many requests).
void __test_request_force_fulfill(int tag, int as_late) {
    event_ph_t* e = __test_find_request_by_tag(tag);
    if (!e || !e->is_active) {
        return;
    }
    if (as_late) {
        e->is_overdue = true;
        e->event_state = e_event_state_finished_late;
    } else {
        e->is_overdue = false;
        e->event_state = e_event_state_finished;
    }
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

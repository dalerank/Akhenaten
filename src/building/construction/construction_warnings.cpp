#include "construction_warnings.h"
#include "city/buildings.h"
#include "city/city_resource.h"
#include "city/city_food_supply.h"
#include "city/city_labor.h"

#include "building/building.h"
#include "city/city.h"
#include "city/city_population.h"
#include "city/city_message.h"
#include "city/city_warnings.h"
#include "city/constants.h"
#include "core/calc.h"
#include "game/game_events.h"
#include "empire/empire.h"
#include "grid/road_access.h"
#include "grid/terrain.h"
#include "scenario/scenario.h"
#include "scenario/scenario_invasion.h"

#include <algorithm>

construction_warnings_t::static_params ANK_VARIABLE(construction_warning_rules);

const construction_warnings_t::static_params& construction_warnings_t::params() {
    return construction_warning_rules;
}

template <typename List>
bool construction_warnings_t::listed(const List& list, e_building_type type) {
    return std::find(list.begin(), list.end(), type) != list.end();
}

void construction_warnings_t::warn(const xstring& id) {
    if (id.empty()) {
        return;
    }
    shown = true;
    events::emit(event_construction_warning{id});
}

int construction_warnings_t::active(e_resource r) const {
    return r == RESOURCE_NONE ? 0 : city_building_stats().count_industry_active(r);
}

int construction_warnings_t::total(e_resource r) const {
    return r == RESOURCE_NONE ? 0 : city_building_stats().count_industry_total(r);
}

int construction_warnings_t::stored(e_resource r) const {
    return r == RESOURCE_NONE ? 0 : city_resource().yards_stored(r);
}

bool construction_warnings_t::can_produce(e_resource r) const {
    return r != RESOURCE_NONE && g_empire.can_produce_resource(r);
}

bool construction_warnings_t::can_import(e_resource r) const {
    return g_empire.can_import_resource(r, true);
}

bool construction_warnings_t::could_import(e_resource r) const {
    return g_empire.can_import_resource(r, false);
}

bool construction_warnings_t::imported(e_resource r) const {
    const e_trade_status status = city_resource().trade_status[r];
    return status == TRADE_STATUS_IMPORT || status == TRADE_STATUS_IMPORT_AS_NEEDED;
}

bool construction_warnings_t::has(e_resource industry, e_resource stock) const {
    return active(industry) > 0 || stored(stock) > 0;
}

void construction_warnings_t::hint_import(e_resource r, const xstring& no_route, const xstring& not_imported) {
    if (!can_import(r)) {
        warn(no_route);
    } else if (!imported(r)) {
        warn(not_imported);
    }
}

void construction_warnings_t::hint_raw_material(e_resource produce, const xstring& build, e_resource import_res,
  const xstring& no_route, const xstring& not_imported) {
    if (can_produce(produce)) {
        warn(build);
        return;
    }
    hint_import(import_res, no_route, not_imported);
}

void construction_warnings_t::hint_input(const construction_warning_input& in, bool both) {
    hint_raw_material(in.produce, in.build, in.import_res, both ? in.both_no_route : in.no_route,
      both ? in.both_not_imported : in.not_imported);
}

void construction_warnings_t::check_raw_material(const construction_warning_material& m) {
    if (active(m.industry) > 0 || stored(m.stock) > 0 || stored(m.product) > 0) {
        return;
    }
    warn(m.warning);
    hint_raw_material(m.produce, m.build, m.import_res, m.no_route, m.not_imported);
}

void construction_warnings_t::check_two_inputs(const construction_warning_two_inputs& t) {
    const auto& a = t.first;
    const auto& b = t.second;
    if (active(a.industry) > 0 && active(b.industry) > 0) {
        return;
    }
    if (stored(t.product) > 0) {
        return;
    }
    if (stored(a.stock) > 0 && stored(b.stock) > 0) {
        return;
    }
    if (!has(a.industry, a.stock)) {
        if (!has(b.industry, b.stock)) {
            warn(t.warning);
            hint_input(a, true);
            hint_input(b, true);
            return;
        }
        warn(a.warning);
        hint_input(a, false);
        return;
    }
    if (has(b.industry, b.stock)) {
        return;
    }
    warn(b.warning);
    hint_input(b, false);
}

void construction_warnings_t::check_finished_good(const construction_warning_finished_good& g) {
    if (stored(g.product) > 0) {
        return;
    }
    warn(g.warning);
    if (total(g.raw) > 0) {
        return;
    }
    const bool raw_can_be_had = can_produce(g.raw) || could_import(g.raw);
    if (raw_can_be_had && total(g.product) == 0) {
        if (!could_import(g.product)) {
            warn(g.build);
        } else if (!can_import(g.product)) {
            warn(g.no_route);
        } else if (
          g.import_only ? city_resource().trade_status[g.product] != TRADE_STATUS_IMPORT : !imported(g.product)) {
            warn(g.not_imported);
        }
        return;
    }
    if (could_import(g.raw) && total(g.product) != 0) {
        hint_import(g.raw, g.raw_no_route, g.raw_not_imported);
        return;
    }
    if (could_import(g.product)) {
        hint_import(g.product, g.product_no_route, g.product_not_imported);
    }
}

void construction_warnings_t::check_workers(building& b) {
    const auto& rules = params();
    if (shown || listed(rules.workers_exempt, b.type) || b.max_workers <= 0) {
        return;
    }
    if (city_labor().workers_needed >= rules.min_workers_needed) {
        warn(rules.workers);
    }
}

void construction_warnings_t::check_requirements(e_building_type type) {
    for (const auto& r : params().requires_building) {
        if (r.building == type && !shown && city_building_stats().count_active(r.needs) < 1) {
            warn(r.warning);
        }
    }
}

void construction_warnings_t::check_military(e_building_type type) {
    const auto& rules = params();
    if (listed(rules.defense, type) && scenario_invasion_city_undefended()) {
        warn(rules.no_troops);
    }
}

void construction_warnings_t::check_stock(e_building_type type) {
    for (const auto& s : params().requires_stock) {
        if (s.building == type && !shown && stored(s.resource) < 1) {
            warn(s.warning);
        }
    }
}

void construction_warnings_t::check_wall_patrol(building& b) {
    const auto& rules = params();
    if (!shown && listed(rules.wall_patrol_types, b.type)
        && !map_terrain_is_adjacent_to_wall(b.tile.x(), b.tile.y(), b.size)) {
        warn(rules.wall_patrol);
    }
}

void construction_warnings_t::check_materials(e_building_type type) {
    const auto& rules = params();
    for (const auto& m : rules.raw_materials) {
        if (listed(m.buildings, type)) {
            check_raw_material(m);
        }
    }
    for (const auto& t : rules.two_inputs) {
        if (listed(t.buildings, type)) {
            check_two_inputs(t);
        }
    }
    for (const auto& g : rules.finished_goods) {
        if (listed(g.buildings, type)) {
            check_finished_good(g);
        }
    }
}

bool construction_warnings_t::is_venue(e_building_type type) const {
    const auto& schools = params().venue_schools;
    return std::any_of(schools.begin(), schools.end(), [type](const auto& s) { return s.building == type; });
}

void construction_warnings_t::check_venue_schools(e_building_type type) {
    for (const auto& s : params().venue_schools) {
        if (s.building == type && city_building_stats().count_total(s.school) < 1) {
            warn(s.warning);
        }
    }
}

bool construction_warnings_t::has_road_access(building& b) const {
    if (map_has_road_access(b.tile, b.size)) {
        return true;
    }
    for (const auto& area : params().road_access_area) {
        if (area.building == b.type && map_has_road_access(b.tile, area.size)) {
            return true;
        }
    }
    return false;
}

void construction_warnings_t::check_site(building& b) {
    const e_building_type type = b.type;
    if (is_venue(type)) {
        check_venue_schools(type);
        return;
    }
    check_workers(b);
    check_requirements(type);
    check_military(type);
    check_stock(type);
    check_wall_patrol(b);
    check_materials(type);
}

void construction_warnings_t::check_road_access(building& b) {
    const auto& rules = params();
    if (is_venue(b.type) || listed(rules.road_access_exempt, b.type) || has_road_access(b)) {
        return;
    }
    const bool shrine = listed(rules.shrines, b.type);
    if (shrine && map_has_road_access_nearby(b.tile, b.params().road_access_distance)) {
        return;
    }
    if (message_manager().problem_area_count() >= rules.max_problem_messages) {
        return;
    }
    warn(shrine ? rules.shrine_road_access : rules.road_access);
}

void construction_warnings_t::check_house_plots() {
    const auto& rules = params();
    const int population = city_population().current;
    if (population < rules.min_population) {
        return;
    }
    const int produced
      = calc_percentage<int>(city_food_supply().percentage(), city_resource().food_consumed_last_month());
    if (!g_scenario.kingdom_supplies_grain && produced < rules.min_food_produced_percent) {
        warn(rules.eating_more_than_produced);
    }
    const bool first_mission = g_scenario.mode() == e_scenario_normal && g_scenario.campaign_scenario_id == 0;
    if (!first_mission && city_labor().unemployment_percentage > rules.max_unemployment_percent) {
        warn(rules.too_few_jobs);
    }
    if ((int)city_resource().granary_total_stored <= city_resource().food_needed_per_month / 2) {
        warn(rules.low_food);
    }
}

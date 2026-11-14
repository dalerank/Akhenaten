#include "construction_warnings.h"

#include "building/building.h"
#include "city/city.h"
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

construction_warning_rules_t ANK_VARIABLE(construction_warning_rules);

namespace {

    template <typename List>
    bool listed(const List& list, e_building_type type) {
        return std::find(list.begin(), list.end(), type) != list.end();
    }

    struct warnings_pass {
        const construction_warning_rules_t& rules = construction_warning_rules;
        bool shown = false;

        void warn(const xstring& id) {
            if (id.empty()) {
                return;
            }
            shown = true;
            events::emit(event_construction_warning{id});
        }

        int active(e_resource r) const { return r == RESOURCE_NONE ? 0 : g_city.buildings.count_industry_active(r); }
        int total(e_resource r) const { return r == RESOURCE_NONE ? 0 : g_city.buildings.count_industry_total(r); }
        int stored(e_resource r) const { return r == RESOURCE_NONE ? 0 : g_city.resource.yards_stored(r); }
        bool can_produce(e_resource r) const { return r != RESOURCE_NONE && g_city.can_produce_resource(r); }
        bool can_import(e_resource r) const { return g_empire.can_import_resource(r, true); }
        bool could_import(e_resource r) const { return g_empire.can_import_resource(r, false); }

        bool imported(e_resource r) const {
            const e_trade_status status = g_city.resource.trade_status[r];
            return status == TRADE_STATUS_IMPORT || status == TRADE_STATUS_IMPORT_AS_NEEDED;
        }

        void hint_import(e_resource r, const xstring& no_route, const xstring& not_imported) {
            if (!can_import(r)) {
                warn(no_route);
            } else if (!imported(r)) {
                warn(not_imported);
            }
        }

        void hint_raw_material(e_resource produce, const xstring& build, e_resource import_res, const xstring& no_route,
          const xstring& not_imported) {
            if (can_produce(produce)) {
                warn(build);
                return;
            }
            hint_import(import_res, no_route, not_imported);
        }

        bool has(e_resource industry, e_resource stock) const { return active(industry) > 0 || stored(stock) > 0; }

        void check_raw_material(const construction_warning_material& m) {
            if (active(m.industry) > 0 || stored(m.stock) > 0 || stored(m.product) > 0) {
                return;
            }
            warn(m.warning);
            hint_raw_material(m.produce, m.build, m.import_res, m.no_route, m.not_imported);
        }

        void hint_input(const construction_warning_input& in, bool both) {
            hint_raw_material(in.produce, in.build, in.import_res, both ? in.both_no_route : in.no_route,
              both ? in.both_not_imported : in.not_imported);
        }

        void check_two_inputs(const construction_warning_two_inputs& t) {
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

        void check_finished_good(const construction_warning_finished_good& g) {
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
                } else if (g.import_only ? g_city.resource.trade_status[g.product] != TRADE_STATUS_IMPORT
                                         : !imported(g.product)) {
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

        void check_workers(building& b) {
            if (shown || listed(rules.workers_exempt, b.type) || b.max_workers <= 0) {
                return;
            }
            if (g_city.labor.workers_needed >= rules.min_workers_needed) {
                warn(rules.workers);
            }
        }

        void check_requirements(e_building_type type) {
            for (const auto& r : rules.requires_building) {
                if (r.building == type && !shown && g_city.buildings.count_active(r.needs) < 1) {
                    warn(r.warning);
                }
            }
        }

        void check_military(e_building_type type) {
            if (listed(rules.defense, type) && scenario_invasion_city_undefended()) {
                warn(rules.no_troops);
            }
        }

        void check_stock(e_building_type type) {
            for (const auto& s : rules.requires_stock) {
                if (s.building == type && !shown && stored(s.resource) < 1) {
                    warn(s.warning);
                }
            }
        }

        void check_wall_patrol(building& b) {
            if (!shown && listed(rules.wall_patrol_types, b.type)
                && !map_terrain_is_adjacent_to_wall(b.tile.x(), b.tile.y(), b.size)) {
                warn(rules.wall_patrol);
            }
        }

        void check_materials(e_building_type type) {
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

        bool is_venue(e_building_type type) const {
            return std::any_of(rules.venue_schools.begin(), rules.venue_schools.end(),
              [type](const auto& s) { return s.building == type; });
        }

        void check_venue_schools(e_building_type type) {
            for (const auto& s : rules.venue_schools) {
                if (s.building == type && g_city.buildings.count_total(s.school) < 1) {
                    warn(s.warning);
                }
            }
        }

        // OG map_has_road_access_nearby: the 4 neighbours and the 4 tiles two steps away.
        bool shrine_has_road_nearby(tile2i tile) const {
            static const vec2i offsets[] = {{0, -1}, {1, 0}, {-1, 0}, {0, 1}, {0, -2}, {2, 0}, {-2, 0}, {0, 2}};
            return std::any_of(std::begin(offsets), std::end(offsets),
              [tile](vec2i d) { return map_terrain_is(tile2i(tile).shifted(d.x, d.y), TERRAIN_ROAD); });
        }

        bool has_road_access(building& b) const {
            if (map_has_road_access(b.tile, b.size)) {
                return true;
            }
            for (const auto& area : rules.road_access_area) {
                if (area.building == b.type && map_has_road_access(b.tile, area.size)) {
                    return true;
                }
            }
            return false;
        }

        void check_road_access(building& b) {
            if (is_venue(b.type) || listed(rules.road_access_exempt, b.type) || has_road_access(b)) {
                return;
            }
            const bool shrine = listed(rules.shrines, b.type);
            if (shrine && shrine_has_road_nearby(b.tile)) {
                return;
            }
            if (city_message_problem_area_count() >= rules.max_problem_messages) {
                return;
            }
            warn(shrine ? rules.shrine_road_access : rules.road_access);
        }
    };

} // namespace

void construction_warnings_check_site(building& b) {
    warnings_pass pass;
    const e_building_type type = b.type;
    if (pass.is_venue(type)) {
        pass.check_venue_schools(type);
        return;
    }
    pass.check_workers(b);
    pass.check_requirements(type);
    pass.check_military(type);
    pass.check_stock(type);
    pass.check_wall_patrol(b);
    pass.check_materials(type);
}

void construction_warnings_check_road_access(building& b) {
    warnings_pass pass;
    pass.check_road_access(b);
}

void construction_warnings_check_house_plots() {
    warnings_pass pass;
    const auto& rules = pass.rules;
    const int population = g_city.population.current;
    if (population < rules.min_population) {
        return;
    }
    const int produced
      = calc_percentage<int>(g_city.food_supply.percentage(), g_city.resource.food_consumed_last_month());
    if (!g_scenario.kingdom_supplies_grain && produced < rules.min_food_produced_percent) {
        pass.warn(rules.eating_more_than_produced);
    }
    const bool first_mission = g_scenario.mode() == e_scenario_normal && g_scenario.campaign_scenario_id == 0;
    if (!first_mission && g_city.labor.unemployment_percentage > rules.max_unemployment_percent) {
        pass.warn(rules.too_few_jobs);
    }
    if ((int)g_city.resource.granary_total_stored <= g_city.resource.food_needed_per_month / 2) {
        pass.warn(rules.low_food);
    }
}

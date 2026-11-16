#include "io/og_save/og_load.h"

#include "building/building.h"
#include "building/building_bazaar.h"
#include "building/building_entertainment.h"
#include "building/building_farm.h"
#include "building/building_granary.h"
#include "building/building_guild.h"
#include "building/building_house.h"
#include "building/building_static_params.h"
#include "building/building_industry.h"
#include "building/building_temple_complex.h"
#include "building/building_type.h"
#include "city/city.h"
#include "core/log.h"
#include "grid/building.h"
#include "game/resource.h"

#include <algorithm>
#include <map>

// Buildings from OG records (tutankhamun building_types.h). Common fields go to ::building, the per-type union to
// the matching runtime class. Types whose OG data has no mapping yet start with fresh runtime data and are logged.
namespace og {

    namespace {

        enum e_og_building_type {
            OG_TYPE_WATER_LIFT = 90,
            OG_TYPE_TEMPLE_COMPLEX_ALTAR = 211,
            OG_TYPE_TEMPLE_COMPLEX_ORACLE = 212,
        };

        enum e_og_building_offset {
            OG_ORIENTATION_OFFSET = 170,
        };

        // OG house inventory slots (house_evolve.h): 0..7 foods by resource, then beer, pottery, linen, jewelry.
        enum e_og_inventory {
            OG_INVENTORY_BEER = 8,
            OG_INVENTORY_POTTERY = 9,
            OG_INVENTORY_LINEN = 10,
            OG_INVENTORY_JEWELRY = 11,
        };

        // OG market good_demands order.
        enum e_og_demand {
            OG_DEMAND_POTTERY = 0,
            OG_DEMAND_JEWELRY = 1,
            OG_DEMAND_LINEN = 2,
            OG_DEMAND_BEER = 3,
        };

        bool is_dropped(int og_type) {
            return og_type == OG_TYPE_TEMPLE_COMPLEX_ALTAR || og_type == OG_TYPE_TEMPLE_COMPLEX_ORACLE;
        }

        e_building_type our_type(int og_type) {
            return og_type == OG_TYPE_WATER_LIFT ? BUILDING_WATER_LIFT : (e_building_type)og_type;
        }

        // Orientation sits at union byte 86 for every OG variant that has one (oriented, industry, dock, temple
        // complex, shipyard); the other variants keep reserved zeros there.
        uint8_t og_orientation(const building& og) {
            return reinterpret_cast<const uint8_t*>(&og)[OG_ORIENTATION_OFFSET];
        }

        void load_common(::building& b, const building& og, int id) {
            // The slot may already hold the impl of its previous (empty) type; the impl follows the OG type.
            b.clear_impl();
            b.id = id;
            b.state = (e_building_state)og.state;
            b.type = our_type(og.type);
            b.size = og.size;
            b.tile = tile2i(og.x, og.y);
            b.orientation = og_orientation(og);
            b.road_network_id = og.road_network_id;
            b.houses_covered = og.houses_covered;
            b.percentage_houses_covered = og.percentage_houses_covered;
            b.distance_from_entry = og.distance_from_entry;
            b.road_access = tile2i(og.road_access_x, og.road_access_y);
            b.figure_spawn_delay = og.figure_spawn_delay;
            b.figure_roam_direction = og.figure_roam_direction;
            b.has_water_access = og.has_water_access;
            b.prev_part_building_id = og.prev_part_building_id;
            b.next_part_building_id = og.next_part_building_id;
            b.has_well_access = og.has_well_access;
            b.num_workers = og.num_workers;
            b.labor_category = (e_labor_category)og.labor_category;
            b.output.resource = (e_resource)og.output_resource;
            b.has_road_access = og.has_road_access;
            b.collapse_risk = og.damage_risk;
            b.fire_risk = og.fire_risk;
            b.fire_duration = og.fire_duration;
            b.fire_proof = og.fire_proof;
            b.formation_id = og.formation_id;
            b.has_plague = og.ruin_has_plague;
            b.current_desirability = og.desirability;
            b.is_deleted = og.is_deleted;
            b.is_adjacent_to_water = og.is_adjacent_to_water;
            b.storage_id = og.storage_id;
            b.show_on_problem_overlay = og.show_on_problem_overlay;
            b.common_health = 100;

            const auto& params = building_static_params::get(b.type);
            b.des_influence = params.desirability.to_influence();
            b.crime_influence = params.crime.to_influence();
            b.fire_risk_increase = params.fire_risk;
            b.collapse_risk_increase = params.damage_risk;
            b.max_workers = params.laborers;
        }

        void load_house(::building_house& house, const building& og) {
            const building_house& h = og.data.house;
            auto& d = house.runtime_data();
            d.inventory[INVENTORY_GOOD1] = h.inventory[OG_INVENTORY_POTTERY];
            d.inventory[INVENTORY_GOOD2] = h.inventory[OG_INVENTORY_JEWELRY];
            d.inventory[INVENTORY_GOOD3] = h.inventory[OG_INVENTORY_LINEN];
            d.inventory[INVENTORY_GOOD4] = h.inventory[OG_INVENTORY_BEER];
            d.booth_juggler = h.juggler;
            d.bandstand_musician = h.musician;
            d.pavillion_dancer = h.dancer;
            d.senet_player = h.senet;
            d.magistrate = h.courthouse;
            d.school = h.school;
            d.library = h.library;
            d.apothecary = h.apothecary;
            d.dentist = h.dentist;
            d.mortuary = h.mortuary;
            d.physician = h.physician;
            d.water_supply = h.water_supply;
            d.zookeeper = h.zoo;
            d.temple_osiris = h.temple[0];
            d.temple_ra = h.temple[1];
            d.temple_ptah = h.temple[2];
            d.temple_seth = h.temple[3];
            d.temple_bast = h.temple[4];
            d.no_space_to_expand = h.no_space_to_expand;
            d.num_foods = h.food_types;
            d.entertainment = h.entertainment;
            d.education = h.education;
            d.health = h.health;
            d.num_gods = h.num_gods;
            d.devolve_delay = h.devolve_delay;
            d.tax_bonus = h.tax_bonus;
            d.house_happiness = og.sentiment.house;
            d.is_merged = og.house_is_merged;
            d.hsize = og.house_size;
            d.population = og.house_population;
            d.highest_population = og.house_highest_population;
            d.unreachable_ticks = og.unreachable_ticks;
            d.tax_coverage = og.house_tax_coverage;
            d.days_without_food = og.house_months_without_food;
            house.base.tax_income_or_storage = (int16_t)std::min<int32_t>(h.tax_income, INT16_MAX);
        }

        void load_bazaar(::building_bazaar& bazaar, const building& og) {
            const building_market& m = og.data.market;
            auto& d = bazaar.runtime_data();
            d.pottery_demand = m.good_demands[OG_DEMAND_POTTERY];
            d.luxurygoods_demand = m.good_demands[OG_DEMAND_JEWELRY];
            d.linen_demand = m.good_demands[OG_DEMAND_LINEN];
            d.beer_demand = m.good_demands[OG_DEMAND_BEER];
            d.inventory[INVENTORY_GOOD1].value = m.inventory[OG_INVENTORY_POTTERY];
            d.inventory[INVENTORY_GOOD2].value = m.inventory[OG_INVENTORY_JEWELRY];
            d.inventory[INVENTORY_GOOD3].value = m.inventory[OG_INVENTORY_LINEN];
            d.inventory[INVENTORY_GOOD4].value = m.inventory[OG_INVENTORY_BEER];
        }

        // Returns false when the OG per-type data was not carried over.
        bool load_runtime(::building& b, const building& og) {
            if (auto* house = b.dcast_house()) {
                load_house(*house, og);
                return true;
            }
            if (auto* granary = b.dcast<::building_granary>()) {
                auto& d = granary->runtime_data();
                for (int i = 0; i < RESOURCES_FOODS_MAX; ++i) {
                    d.resource_stored[i] = og.data.granary.resource_stored[i];
                }
                return true;
            }
            if (auto* bazaar = b.dcast<::building_bazaar>()) {
                load_bazaar(*bazaar, og);
                return true;
            }
            if (b.dcast<::building_industry>()) {
                b.progress = og.data.industry.progress;
                // Same default a .svx load gives a record without a cycle length.
                b.progress_max = 400;
                return true;
            }
            if (b.dcast<::building_guild>()) {
                b.progress = og.data.industry.progress;
                return true;
            }
            if (auto* farm = b.dcast<::building_farm>()) {
                b.progress = og.data.industry.progress;
                farm->runtime_data().labor_days_left = og.data.industry.labor_days_left[0];
                return true;
            }
            if (auto* venue = b.dcast<::building_entertainment>()) {
                auto& d = venue->runtime_data();
                d.num_shows = og.data.entertainment.num_shows;
                d.juggler_visited = og.data.entertainment.show_days_left[0];
                d.musician_visited = og.data.entertainment.show_days_left[1];
                d.dancer_visited = og.data.entertainment.show_days_left[2];
                return true;
            }
            if (auto* complex = b.dcast<::building_temple_complex>()) {
                complex->runtime_data().temple_complex_upgrades = og.data.temple_complex.upgrades;
                return true;
            }
            return b.type == BUILDING_WATER_LIFT || b.type == BUILDING_FERRY;
        }

    } // namespace

    void load_buildings(const savegame& s, load_report& report) {
        std::map<int, int> unmapped;
        for (size_t id = 1; id < s.buildings.size(); ++id) {
            const building& og = s.buildings[id];
            if (og.state == BUILDING_STATE_UNUSED) {
                continue;
            }
            if (is_dropped(og.type)) {
                logs::info(
                  "[og-save] unmapped building %u: temple complex altar/oracle (type %d), the god is not in the "
                  "record",
                  (uint32_t)id, og.type);
                for (int i = 0; i < GRID_CELLS; ++i) {
                    if (map_building_at(i) == (int)id) {
                        map_building_set(i, 0);
                    }
                }
                report.buildings_dropped++;
                continue;
            }

            ::building& b = *building_get(building_id(id));
            load_common(b, og, (int)id);
            report.buildings++;
            if (!load_runtime(b, og) && og.state == BUILDING_STATE_VALID) {
                unmapped[og.type]++;
                report.buildings_runtime_unmapped++;
            }
        }
        for (const auto& kv : unmapped) {
            logs::info("[og-save] unmapped building runtime data: type %d x%d", kv.first, kv.second);
        }
    }

    void load_after_post_load(const savegame& s) {
        for (size_t id = 1; id < s.buildings.size(); ++id) {
            const building& og = s.buildings[id];
            if (og.state == BUILDING_STATE_UNUSED || is_dropped(og.type)) {
                continue;
            }
            ::building* b = building_get(building_id(id));
            for (int slot = INVENTORY_MIN_FOOD; slot < INVENTORY_MAX_FOOD; ++slot) {
                const int food = g_city.allowed_foods(slot) - RESOURCE_GRAIN;
                if (food < 0 || food >= 8) {
                    continue;
                }
                if (auto* house = b->dcast_house()) {
                    house->runtime_data().foods[slot] = og.data.house.inventory[food];
                } else if (auto* bazaar = b->dcast<::building_bazaar>()) {
                    bazaar->runtime_data().inventory[slot].value = og.data.market.inventory[food];
                }
            }
        }
    }

} // namespace og

#include "city/city_food_supply.h"
#include "city/buildings.h"
#include "game/simulation.h"
#include "core/app_module.h"
#include "game/sim_schedule.h"
#include "city/city_food_supply_chunks.h"
#include "core/xvalue.h"
#include "io/chunk_serializer.h"

#include "building/building.h"
#include "building/building_static_params.h"
#include "building/building_temple_complex.h"
#include "city/city.h"
#include "city/city_temple_complexes.h"
#include "city/city_buildings.h"
#include "city/city_resource.h"
#include "empire/empire.h"
#include "empire/empire_city.h"
#include "grid/floodplain.h"
#include "js/js_game.h"

#include <algorithm>

city_food_supply_rules_t ANK_VARIABLE(city_food_supply_rules);

int food_supply_farm_expected_produce(int fertility, int laborers, bool blessed,
  const city_food_supply_rules_t& rules) {
    const double per_worker
      = (rules.farm_produce_per_worker_pct / 100.0) * (1.0 / std::max(1, rules.farm_fertility_max));
    double value = (double)fertility * per_worker;
    value *= (double)laborers;
    value *= (double)rules.farm_produce_scale;
    if (blessed) {
        value += value;
    }
    return std::max(1, (int)value);
}

int food_supply_percentage(const food_supply_sources& s, const city_food_supply_rules_t& rules) {
    const int harvests
      = s.floodplain_produce * rules.floodplain_farm_food_factor + s.meadow_produce * rules.meadow_farm_food_factor;
    const int ranches = (int)(((uint32_t)s.ranch_food * (uint32_t)rules.ranch_food_percentage) / 100);
    const double divisor = (double)std::max(1, rules.harvest_food_divisor);
    const int supply
      = (int)((double)harvests / divisor + (double)(s.import_food + ranches + s.fishing_food + s.hunting_food));
    return (supply * 100) / std::max(1, s.consumption_percentage);
}

// OG temple_complex.c city_food_consumption_percentage.
int city_food_consumption_percentage() {
    const auto& rules = city_food_supply_rules;
    building* complex = building_get(city_temple_complexes().any_id());
    if (!complex || !complex->is_valid()) {
        return rules.consumption_percentage;
    }

    if (complex->type == BUILDING_TEMPLE_COMPLEX_BAST) {
        return rules.blessed_consumption_percentage;
    }

    auto* osiris = complex->dcast_temple_complex();
    if (complex->type == BUILDING_TEMPLE_COMPLEX_OSIRIS && osiris && osiris->has_upgrade(etc_upgrade_altar)) {
        return rules.blessed_consumption_percentage;
    }
    return rules.consumption_percentage;
}

static bool food_supply_is_food_farm(e_building_type type) {
    const auto& farms = city_food_supply_rules.food_farms;
    return std::find(farms.begin(), farms.end(), type) != farms.end();
}

static int food_supply_imports() {
    const auto& rules = city_food_supply_rules;
    int imports = 0;
    for (const auto& c : g_empire.get_cities()) {
        const bool trading = (c.type == EMPIRE_CITY_PHARAOH_TRADING || c.type == EMPIRE_CITY_EGYPTIAN_TRADING
                              || c.type == EMPIRE_CITY_FOREIGN_TRADING);
        if (!c.in_use || !trading || !c.is_open) {
            continue;
        }

        const trade_route& route = c.get_route();
        for (e_resource r = RESOURCES_FOOD_MIN; r < RESOURCES_FOODS_MAX; ++r) {
            const e_trade_status status = city_resource().trade_status[r];
            if ((status != TRADE_STATUS_IMPORT && status != TRADE_STATUS_IMPORT_AS_NEEDED) || !c.sells_resource[r]) {
                continue;
            }
            const int loads = route.resources[r].limit / 100;
            imports += (loads * rules.import_amount_per_load) / std::max(1, rules.months_per_year);
        }
    }
    return imports;
}

city_food_supply_t& city_food_supply() {
    return xvalue<city_food_supply_t>::ref();
}

void city_food_supply_t::reset() {
    *this = {};
}

void city_food_supply_t::subscribe_events() {
    events::subscribe([](event_produced_resources ev) {
        auto& food_supply = city_food_supply();
        if (ev.resource == RESOURCE_GAMEMEAT) {
            food_supply.game_meat_this_month += city_food_supply_rules.food_per_cart;
        } else if (ev.resource == RESOURCE_FISH) {
            food_supply.fish_this_month += city_food_supply_rules.food_per_cart;
        }
    });
}

void city_food_supply_t::advance_month() {
    hunting_lodges_working = city_building_stats().count_industry_active(RESOURCE_GAMEMEAT);
    game_meat_last_month = game_meat_this_month;
    game_meat_this_month = 0;
    fishing_wharfs_working = city_building_stats().count_industry_active(RESOURCE_FISH);
    fish_last_month = fish_this_month;
    fish_this_month = 0;
}

food_supply_sources city_food_supply_t::gather() const {
    const auto& rules = city_food_supply_rules;
    food_supply_sources s;

    if (hunting_lodges_working != 0) {
        s.hunting_food = (game_meat_last_month / hunting_lodges_working)
                         * city_building_stats().count_industry_active(RESOURCE_GAMEMEAT);
    }
    if (fishing_wharfs_working != 0) {
        s.fishing_food
          = (fish_last_month / fishing_wharfs_working) * city_building_stats().count_industry_active(RESOURCE_FISH);
    }

    buildings_valid_do([&](building& b) {
        if (b.is_farm()) {
            if (!food_supply_is_food_farm(b.type)) {
                return;
            }
            const int laborers = building_static_params::get(b.type).laborers;
            const bool blessed
              = b.blessing_days_left > 0 && (b.type == BUILDING_GRAIN_FARM || b.type == BUILDING_GRAIN_MEADOW_FARM);
            const int produce
              = food_supply_farm_expected_produce(map_get_fertility_for_farm(b.tile), laborers, blessed, rules);
            if (b.is_floodplain_farm()) {
                s.floodplain_produce += produce;
            } else {
                s.meadow_produce += produce;
            }
            return;
        }

        if (b.type == BUILDING_CATTLE_RANCH && b.num_workers > 0 && b.progress > 0) {
            const int laborers = building_static_params::get(b.type).laborers;
            s.ranch_food += (laborers * rules.ranch_food_factor) / std::max(1, rules.ranch_food_divisor);
        }
    });

    s.import_food = food_supply_imports();
    s.consumption_percentage = city_food_consumption_percentage();
    return s;
}

int city_food_supply_t::percentage() const {
    return food_supply_percentage(gather(), city_food_supply_rules);
}

int __city_food_supply_percentage() {
    return city_food_supply().percentage();
}
ANK_FUNCTION(__city_food_supply_percentage)

class food_supply_system : public sim_system {
public:
    const char* name() const override { return "food_supply"; }
    void on_reset() override { city_food_supply().reset(); }
    void push_save_sections() override {
        g_chunk_io.push_chunk<city_food_supply_chunk>(city_food_supply_chunk::size, false);
    }
    void register_steps(sim_schedule_t& schedule) override {
        schedule.add(
          {sim_step_food_supply_month, SIM_PHASE_MONTH_CITY, [](int) { city_food_supply().advance_month(); }});
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_food_supply_system) {
    static food_supply_system system;
    g_simulation.register_system(&system);
}

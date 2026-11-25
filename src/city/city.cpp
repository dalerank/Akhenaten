#include "city.h"
#include "city/city_food_supply.h"
#include "city/city_maintenance.h"
#include "city/city_kingdome_relations.h"
#include "city/city_religion.h"
#include "city/city_finance.h"
#include "city/city_trade.h"
#include "city/ratings.h"
#include "city/city_sentiment.h"
#include "city/city_health.h"
#include "city/city_labor.h"
#include "game/simulation.h"
#include "core/app_module.h"
#include "city/city.h"
#include "game/sim_schedule.h"

#include "city/constants.h"
#include "city/buildings.h"
#include "city/city_population.h"
#include "city/city_desirability.h"
#include "city/city_malaria_risk.h"
#include "grid/malaria_risk.h"
#include "grid/irrigation_value.h"
#include "grid/crime.h"
#include "core/object_property.h"
#include "grid/water.h"
#include "grid/natives.h"
#include "grid/vegetation.h"
#include "grid/trees.h"
#include "grid/canals.h"
#include "core/profiler.h"
#include "core/calc.h"
#include "game/difficulty.h"
#include "game/game.h"
#include "game/game_config.h"
#include "scenario/scenario.h"
#include "empire/empire_city.h"
#include "empire/empire.h"
#include "empire/trade_route.h"
#include "building/building_granary.h"
#include "building/building_house.h"
#include "city/city_industry.h"
#include "city/city_animals.h"
#include "city/city_bookmarks.h"
#include "city/city_festival.h"
#include "city/entertainment.h"
#include "city/city_plagues.h"
#include "city/city_taxes.h"
#include "city/city_victory.h"
#include "city/sound.h"
#include "city/city_local_cults.h"
#include "city/city_temple_complexes.h"
#include "building/building_barracks.h"
#include "building/building_temple_complex.h"
#include "building/building_burning_ruin.h"
#include "figure/figure.h"
#include "figuretype/figure_native.h"
#include "figuretype/figure_fishing_point.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "grid/image.h"
#include "grid/random.h"
#include "grid/terrain.h"
#include "figuretype/figure_kingdome_trader.h"
#include "figuretype/figure_trader_ship.h"
#include "figuretype/figure_tomb_robber.h"
#include "figuretype/figure_flotsam.h"
#include "figuretype/figure_funeral_walker.h"
#include "city_warnings.h"
#include "game/game_events.h"
#include "empire/empire_object.h"
#include "grid/building.h"
#include "building/construction/build_planner.h"
#include "empire/empire_traders.h"
#include "scenario/criteria.h"
#include "city/city_religion_osiris.h"
#include "scenario/distant_battle.h"

#include <core/string.h>
#include <string.h>
#include <time.h>
#include "scenario/map.h"

city_t g_city;
events::typed_queue g_city_events;

static void city_subscribe_events() {
    city_maintenance_t::subscribe_events();
    g_city.resource.subscribe_events();
    city_food_supply_t::subscribe_events();
    city_finance_t::subscribe_events();
}
static events::session_subscriber g_city_session(&city_subscribe_events);

template <typename T>
static void zero_fill(T& part) {
    memset((void*)&part, 0, sizeof(T));
}

void city_t::init() {
    buildings.shutdown();

    zero_fill(buildings);
    zero_fill(figures);
    zero_fill(houses);
    zero_fill(military);
    zero_fill(resource);
    zero_fill(map);

    g_simulation.reset_systems();
    g_distant_battle.clear();
    buildings.init();
    figure_clear_all();
    city_sentiment().init();
    city_finance().init();
}

void city_t::reload_objects() {
    buildings.reload_objects();
    figures.reload_objects();
}

void city_t::update_month(simulation_time_t simtime) {
    g_simulation.schedule.run(SIM_PHASE_MONTH_CITY, g_simulation.simtime.tick);
}

void city_t::init_custom_map() {
    city_finance().treasury = g_scenario.startup_funds();
    city_finance().last_year.balance = city_finance().treasury;
}

void city_t::init_campaign_mission() {
    city_finance().treasury = g_scenario.startup_funds();
    city_finance().last_year.income.gold_delivered = 0;
    city_finance().this_year.income.gold_delivered = 0;
}

void city_t::init_mission_resources(const resource_allow_vec& resources) {
    auto fobj = const_cast<full_empire_object*>(ourcity().get_full_empire_object());
    for (const auto &r: resources) {
        fobj->add_sell_resource(r.type);
    }
}

e_resource city_t::allowed_foods(int i) {
    return resource.food_types_allowed[i];
}

void city_t::set_max_happiness(int max) {
    buildings_house_do([max] (auto house) {
        if (house->hsize()) {
            auto &housed = house->runtime_data();
            housed.house_happiness = std::min<int>(housed.house_happiness, max);
            housed.house_happiness = calc_bound(housed.house_happiness, 0, 100);
        }
    });
}

void city_t::change_happiness(int amount) {
    buildings_house_do([amount] (auto house) {
        if (house->hsize()) {
            auto &housed = house->runtime_data();
            housed.house_happiness = calc_bound(housed.house_happiness + amount, 0, 100);
        }
    });
}

void city_t::update_tick(int simtick) {
    g_simulation.schedule.run(SIM_PHASE_TICK, simtick);
    g_simulation.schedule.run(SIM_PHASE_TICK_CITY_END, simtick);
}

bool city_t::generate_trader_from(empire_city &city) {
    if (city_gods().ra_no_traders_months_left > 0) {
        return false;
    }

    if (city.free_trader_slot() < 0) {
        return false;
    }

    if (city.trader_entry_delay > 0) {
        city.trader_entry_delay--;
        return false;
    }

    constexpr int sea_default_entry_delay = 30;  // 2 in-game months at 16 days/month
    constexpr int land_default_entry_delay = 4;
    const int default_entry_delay = city.is_sea_trade ? sea_default_entry_delay : land_default_entry_delay;
    city.trader_entry_delay = city.trader_entry_delay_override != 0
                                ? city.trader_entry_delay_override
                                : default_entry_delay;

    if (city.is_sea_trade) {
        // generate ship
        const bool has_doks = g_city.buildings.has_working_dock();
        const bool has_river_entry = scenario_map_has_river_entry();
        const bool can_sea_trade = !city_trade().has_sea_problems();
        if (has_doks && has_river_entry && can_sea_trade) {
            g_empire_traders.create_trader(city.route_id, -1);
            return true;
        }
    } else {
        // generate caravan and donkeys
        if (!city_trade().has_land_problems()) {
            // caravan head
            g_empire_traders.create_trader(city.route_id, -1);
            return true;
        }
    }
    return false;
}

bool city_t::is_food_allowed(e_resource resource) {
    bool result = false;
    for (int i = 0; i < 4; i++) {
        if (g_city.allowed_foods(i) == resource) {
            result = true;
        }
    }
    // for etc etc todo: other resources?
    return result;
}

void city_t::set_allowed_food(int i, e_resource r) {
    resource.food_types_allowed[i] = r;
}

int stack_units_by_resource(int resource) {
    switch (resource) {
    default:
        return RESOURCE_UNIT_PILE;

    case RESOURCE_GOLD:
    case RESOURCE_STONE:
    case RESOURCE_LIMESTONE:
    case RESOURCE_GRANITE:
    case RESOURCE_SANDSTONE:
    case RESOURCE_MARBLE:
        return RESOURCE_UNIT_BLOCK;

    case RESOURCE_WEAPONS:
        return RESOURCE_UNIT_WEAPON;

    case RESOURCE_CHARIOTS:
        return RESOURCE_UNIT_CHARIOT;
    }
}

empire_city &city_t::ourcity() {
    auto const &cities = g_empire.get_cities();
    auto it = std::find_if(cities.begin(), cities.end(), [] (auto &city) { return (city.in_use && (city.type == EMPIRE_CITY_OURS)); });

    verify_no_crash(it != cities.end());
    return *it;
}

bool city_t::can_produce_resource(e_resource resource) {
    auto &c = ourcity();
    return c.sells_resource[resource];
}

void city_t::set_produce_resource(e_resource resource, bool v) {
    auto &c = ourcity();
    c.sells_resource[resource] = v;
}

void city_t::update_allowed_foods() {
    int food_index = 0;

    std::fill_n(std::begin(resource.food_types_allowed), RESOURCES_FOODS_MAX, RESOURCE_NONE);

    for (e_resource resource = RESOURCES_MIN; resource < RESOURCES_FOODS_MAX; ++resource) {
        bool can_import_food = g_empire.can_import_resource(resource, false);
        bool can_produce_food = can_produce_resource(resource);
        if (can_import_food || can_produce_food) {
            set_allowed_food(food_index, resource);
            food_index++;
        }
    }
}

void city_t::house_decay_tax_coverage() {
    OZZY_PROFILER_FUNCTION();
    buildings_house_do([&] (building_house *house) {
        house->decay_tax_coverage();
    });
}

void city_t::house_decay_services() {
    OZZY_PROFILER_FUNCTION();
    buildings_house_do([] (auto house) {
        house->decay_services();
    });
}

bool city_t::available_resource(e_resource resource) {
    e_resource raw_resource = get_raw_resource(resource);
    // finished goods: check imports of raw materials
    if (raw_resource != resource && g_empire.can_import_resource(raw_resource, false)) {
        return true;
    }

    // check if we can produce the raw materials
    return can_produce_resource(raw_resource);
}

void city_t::buildings_generate_figure() {
    OZZY_PROFILER_FUNCTION();
    figures.house_noble_spawned_this_tick = false;
    figures.bazaar_figure_pass_index = 0;
    buildings_valid_do([] (building &b) {
        switch (b.type) {
        case BUILDING_UNUSED_NATIVE_HUT_88: {
            // OG spawn_native_hut: hut image from random bit; native every 5 days when a meeting
            // is linked and there is road/clear land next to the hut.
            int native_image = image_id_from_group(GROUP_BUILDING_NATIVE);
            map_image_set(b.tile, native_image + (map_random_get(b.tile.grid_offset()) & 1));
            if (b.has_figure_of_type(-1, FIGURE_INDIGENOUS_NATIVE)) {
                break;
            }
            int x_out = 0;
            int y_out = 0;
            if (b.native_meeting_center_id > 0
                && map_terrain_get_adjacent_road_or_clear_land(b.tile.x(), b.tile.y(), b.size, &x_out, &y_out)) {
                b.figure_spawn_delay++;
                if (b.figure_spawn_delay > 4) {
                    b.figure_spawn_delay = 0;
                    figure *f = figure_create(FIGURE_INDIGENOUS_NATIVE, tile2i(x_out, y_out), DIR_0_TOP_RIGHT);
                    f->action_state = ACTION_10_NATIVE_CREATED;
                    f->set_home(b.id);
                    b.set_figure(BUILDING_SLOT_SERVICE, f);
                }
            }
            break;
        }

        case BUILDING_UNUSED_NATIVE_MEETING_89:
            //    map_building_tiles_add(id, x, y, 2,
            //                           image_id_from_group(GROUP_BUILDING_NATIVE) + 2, TERRAIN_BUILDING);
            //    if (city_buildings_is_mission_post_operational() && !has_figure_of_type(FIGURE_NATIVE_TRADER)) {
            //        int x_out, y_out;
            //        if (map_terrain_get_adjacent_road_or_clear_land(tile.x(), tile.y(), size, &x_out, &y_out)) {
            //            figure_spawn_delay++;
            //            if (figure_spawn_delay > 8) {
            //                figure_spawn_delay = 0;
            //                figure *f = figure_create(FIGURE_NATIVE_TRADER, x_out, y_out, DIR_0_TOP_RIGHT);
            //                f->action_state = FIGURE_ACTION_162_NATIVE_TRADER_CREATED;
            //                f->home() = b;
            //                figure_id = f->id;
            //            }
            //        }
            //    }

            break;
        case BUILDING_UNUSED_NATIVE_CROPS_93:
            // todo
            //data.industry.progress++;
            //if (data.industry.progress >= 5) {
            //    data.industry.progress = 0;
            //}
            //
            //int img_id = building_impl::params(BUILDING_BARLEY_FARM).anim["farmland"].first_img();
            //map_image_set(tile.grid_offset(), img_id + data.industry.progress);
            break;

        default:
            b.dcast()->spawn_figure();
            break;
        }
    });

    if (city_gods().osiris_double_farm_yield_used) {
        city_gods().osiris_double_farm_yield_days = 0;
        city_gods().osiris_double_farm_yield_used = false;
    }
}

void city_t::plague_update_day() {
    buildings_house_do([] (auto house) {
        if (!house->hsize()) {
            return;
        }

        if (house->base.has_plague && house->base.disease_days > 0) {
            house->base.disease_days--;
            house->base.has_plague = (house->base.disease_days > 0);
        }

        auto &housed = house->runtime_data();
        if (housed.frog_infest_days > 0) {
            housed.frog_infest_days--;
        }
    });
}

void city_t::criminals_update_day() {
    buildings_house_do([] (auto house) {
        if (!house->hsize()) {
            return;
        }

        int delta;
        auto &housed = house->runtime_data();
        if (housed.house_happiness >= 50) {
            delta = (housed.house_happiness - 50) / 30;
        } else if (housed.house_happiness < 50) {
            delta = -std::max<int>((50 - housed.house_happiness) / 10, 0);
        }

        housed.criminal_active += delta;
        housed.criminal_active = std::clamp<int>(housed.criminal_active, 0, 100);
    });
}

void city_t::before_start_simulation() {
    events::emit(event_population_changed{city_population().current});
    events::emit(event_finance_changed{city_finance().treasury});
}

void city_t::houses_reset_demands() {
    houses.missing.fountain = 0;
    houses.missing.well = 0;
    houses.missing.entertainment = 0;
    houses.missing.more_entertainment = 0;
    houses.missing.education = 0;
    houses.missing.more_education = 0;
    houses.missing.religion = 0;
    houses.missing.second_religion = 0;
    houses.missing.third_religion = 0;
    houses.missing.dentist = 0;
    houses.missing.courthouse = 0;
    houses.missing.any_courthouse = 0;
    houses.missing.health = 0;
    houses.missing.more_health = 0;
    houses.missing.food = 0;
    // OG city_houses_reset_demands leaves houses_missing_second_luxury alone too.

    houses.requiring.school = 0;
    houses.requiring.library = 0;
    houses.requiring.dentist = 0;
    houses.requiring.courthouse = 0;
    houses.requiring.more_courthouse = 0;
    houses.requiring.health = 0;
    houses.requiring.religion = 0;
}

pcstr city_player_name() {
    return city_kingdome().player_name.c_str();
}

void city_set_player_name(xstring name) {
    city_kingdome().player_name = name;
}

void city_restore_campaign_player_name() {
    city_kingdome().player_name = city_kingdome().campaign_player_name;
}

mission_result_t city_make_mission_result(int scenario_id) {
    mission_result_t result;

    result.scenario_id = scenario_id;
    result.rating_culture = city_ratings().culture;
    result.rating_prosperity = city_ratings().prosperity;
    result.rating_kingdom = city_kingdome().rating;
    result.final_population = city_population().current;
    result.final_funds = city_finance().treasury;
    result.completion_months = (uint32_t)(g_simulation.simtime.years_since_start() * simulation_time_t::months_in_year
                                          + g_simulation.simtime.month + 1);
    result.difficulty = game_difficulty();
    result.player_name = city_kingdome().player_name;

    return result;
}

struct cproperty {
    xstring domain;
    xstring name;

    std::function<bvariant(const xstring &)> handler;
};

bvariant city_get_property(xstring domain, xstring name) {
    static cproperty cproperties[] = {
      {tags().city, "population", [](const xstring&) { return bvariant(city_population().current); }},
      {tags().city, "population_kids", [](const xstring&) { return bvariant(city_population().school_age); }},
      {tags().city, "population_youngs", [](const xstring&) { return bvariant(city_population().academy_age); }},
      {tags().city, "treasury", [](const xstring&) { return bvariant(city_finance().treasury); }},
      {tags().rating, tags().culture, [](const xstring&) { return bvariant(city_ratings().culture); }},
      {tags().rating, tags().prosperity, [](const xstring&) { return bvariant(city_ratings().prosperity); }},
      {tags().rating, tags().monument, [](const xstring&) { return bvariant(city_ratings().monument); }},
      {tags().rating, tags().kingdom, [](const xstring&) { return bvariant(city_kingdome().rating); }},
      {tags().city, "months_since_festival",
        [](const xstring&) { return bvariant(city_festival().months_since_festival); }},
      {tags().city, "workers_needed", [](const xstring&) { return bvariant(city_labor().workers_needed); }},
      {tags().city, "workers_diff",
        [](const xstring&) { return bvariant(city_labor().workers_unemployed - city_labor().workers_needed); }},
    };

    for (const auto &prop : cproperties) {
        if (prop.domain != domain) {
            continue;
        }

        if (prop.name == name) {
            return prop.handler(name);
        }
    }

    return bvariant();
}

bvariant city_t::get_property(xstring domain, xstring name) const {
    return city_get_property(domain, name);
}

void city_t::on_post_load() {
    buildings.on_post_load();
    figures.on_post_load();
    city_kingdome().on_post_load();
    city_trade().update_export_keep();
}

void city_t::figures_update_day() {
    figure_valid_do([] (figure &f) {
        f.dcast()->update_day();
    });
}

bool city_t::determine_granary_get_foods(resource_list &foods, int road_network) {
    if (g_scenario.kingdom_supplies_grain) {
        return false;
    }

    foods.clear();
    buildings_valid_do([&] (building &b) {
        building_granary *granary = b.dcast_granary();
        verify_no_crash(granary);
        if (!granary->has_road_access()) {
            return;
        }

        if (!building_granary_touches_network(b, road_network)) {
            return;
        }

        const int pct_workers = granary->worker_percentage();
        if (pct_workers < 100 || granary->amount(RESOURCE_NONE) < 100) {
            return;
        }

        if (!granary->is_empty_all()) {
            return;
        }

        for (const auto &r: resource_list::foods) {
            if (granary->is_getting(r.type)) {
                foods[r.type] = 1;
            }
        }
    }, BUILDING_GRANARY);

    return foods.any();
}

class city_system : public sim_system {
public:
    const char* name() const override { return "city"; }
    void register_steps(sim_schedule_t& schedule) override {
        schedule.add({sim_step_generate_figures, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 31) {
                              return;
                          }
                          g_city.buildings_generate_figure();
                      }});
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_city_system) {
    static city_system system;
    g_simulation.register_system(&system);
}

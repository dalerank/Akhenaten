#include "city_health.h"
#include "city/city_religion.h"
#include "io/gamestate/save_versions.h"
#include "io/chunk_serializer.h"
#include "core/xvalue.h"
#include "city/city_temple_complexes.h"
#include "city/city_health_chunks.h"
#include "core/app_module.h"
#include "game/sim_schedule.h"

#include "core/profiler.h"
#include "core/calc.h"
#include "building/building_house.h"
#include "building/building_temple_complex.h"
#include "building/destruction.h"
#include "city/buildings.h"
#include "city/city.h"
#include "city/city_population.h"
#include "city/city_figures.h"
#include "game/game_config.h"
#include "game/game_events.h"
#include "city/coverage.h"
#include "city/city_message.h"
#include "core/random.h"
#include "figuretype/figure_plagued_citizen.h"
#include "scenario/scenario.h"
#include "game/simulation.h"
#include "js/js_register.h"

city_health_rules_t ANK_VARIABLE(city_health_rules);

void city_health_t::change(int amount) {
    value = calc_bound(value + amount, 0, 100);
}

void city_health_t::infect_house(building& main) {
    main.mark_plague(city_health_rules.plague_house_days);
}

void city_health_t::start_disease(int total_people, bool force, int plague_people) {
    if (!force && value >= 40) {
        // Natural check blocked by good health — drop a leftover Bast force flag.
        city_gods().bast_curse_active = false;
        return;
    }

    int chance_value = random_byte() & 0x3f;
    const bool bast_forced = city_gods().bast_curse_active;
    if (bast_forced) {
        // Force the roll; clear flag only after an outbreak outcome below.
        chance_value = 0;
    }

    if (!force && (chance_value > 40 - value)) {
        return;
    }

    int sick_people = calc_adjust_with_percentage(total_people, 7 + (random_byte() & 3));
    if (plague_people > 0) {
        sick_people = plague_people;
    }

    if (sick_people <= 0) {
        if (bast_forced) {
            city_gods().bast_curse_active = false;
        }
        return;
    }

    int people_to_plague = sick_people - num_mortuary_workers;
    if (people_to_plague <= 0) {
        if (bast_forced) {
            city_gods().bast_curse_active = false;
        }
        change(10);
        message_manager().post_with_popup_delay(MESSAGE_CAT_HEALTH_PROBLEM, false, "message_malaria", 0, 0);
        return;
    }

    building *warn_building = nullptr;
    auto infect_house = [&](building_house *house) {
        auto main = house->main();
        if (main->base.has_plague) {
            return; // already counted / spawned this outbreak
        }
        warn_building = &main->base;
        people_to_plague -= house->house_population();
        city_health_t::infect_house(main->base);
        if (!!game_features::gameplay_change_plagued_citizen_remake) {
            figure_plagued_citizen::create_at_house(main->base);
        }
    };

    // kill people where has little common_health
    buildings_house_do([&] (building_house *house) {
        if (people_to_plague <= 0 || !house || !house->base.is_main() || house->house_population() <= 0) {
            return;
        }

        if (house->main()->base.common_health < 10) {
            infect_house(house);
        }
    });

    // kill people who don't have access to apothecary/physician
    buildings_house_do([&] (building_house *house) {
        if (people_to_plague <= 0 || !house->base.is_main() || house->house_population() <= 0) {
            return;
        }

        auto &housed = house->runtime_data();
        if (!(housed.apothecary || housed.physician)) {
            infect_house(house);
        }
    });

    // kill people in tents
    buildings_house_do([&] (building_house *house) {
        if (people_to_plague <= 0 || !house->base.is_main() || house->house_population() <= 0) {
            return;
        }

        if (house->house_level() <= HOUSE_STURDY_HUT) {
            infect_house(house);
        }
    });

    // kill anyone
    buildings_house_do([&] (building_house *house) {
        if (people_to_plague <= 0 || !house->base.is_main() || house->house_population() <= 0) {
            return;
        }

        infect_house(house);
    });

    // Nothing newly infected (all candidates already had plague) — no cooldown bump / spam.
    if (!warn_building) {
        if (bast_forced) {
            city_gods().bast_curse_active = false;
        }
        return;
    }

    if (bast_forced) {
        city_gods().bast_curse_active = false;
    }

    // OG city_health_start_plague_at_house: one carrier from the outbreak's house.
    if (!game_features::gameplay_change_plagued_citizen_remake.to_bool()) {
        figure_plagued_citizen::create_at_house(*warn_building);
    }

    change(10);
    events::emit(event_city_disease{g_simulation.simtime.absolute_day(true)});

    e_building_type btype = warn_building->type;
    int grid_offset = warn_building->tile.grid_offset();
    if (num_mortuary_workers > 0) {
        message_manager().post_with_popup_delay(MESSAGE_CAT_HEALTH_PROBLEM, force, "message_disease", btype,
          grid_offset);
    } else {
        message_manager().post_with_popup_delay(MESSAGE_CAT_HEALTH_PROBLEM, force, "message_disease_strikes", btype,
          grid_offset);
    }
}

void city_health_t::update_coverage() {
    OZZY_PROFILER_FUNCTION();
    // OG culture_update_health_coverage: share of people in houses still visited by each service.
    int population = 0;
    int with_apothecary = 0;
    int with_mortuary = 0;
    int with_physician = 0;
    int with_dentist = 0;
    buildings_house_do([&] (building_house *house) {
        const int people = house->house_population();
        if (people <= 0) {
            return;
        }
        population += people;
        auto &housed = house->runtime_data();
        if (housed.apothecary) {
            with_apothecary += people;
        }
        if (housed.mortuary) {
            with_mortuary += people;
        }
        if (housed.physician) {
            with_physician += people;
        }
        if (housed.dentist) {
            with_dentist += people;
        }
    });

    auto& coverage = g_city.coverage;
    coverage.apothecary = (uint8_t)calc_percentage(with_apothecary, population);
    coverage.mortuary = (uint8_t)calc_percentage(with_mortuary, population);
    coverage.physician = (uint8_t)calc_percentage(with_physician, population);
    coverage.dentist = (uint8_t)calc_percentage(with_dentist, population);
}

void city_health_t::update_month() {
    if (city_population().current < 200 || g_scenario.is_scenario_id(1, 2)) {
        value = 50;
        target_value = 50;
        return;
    }

    // OG city_health_update: mortuary / physician / food types (apothecary does not count).
    const auto &rules = city_health_rules;

    int total_population = 0;
    int healthy_population = 0;
    buildings_house_do([&] (building_house* house) {
        const short hpop = house->house_population();
        if (hpop <= 0) {
            return;
        }

        total_population += hpop;
        auto &housed = house->runtime_data();
        int coverage_pts = 0;
        if (housed.mortuary) {
            coverage_pts = rules.mortuary_points;
        }
        if (housed.physician) {
            coverage_pts += rules.physician_points;
        }
        const int food = housed.num_foods;
        if (food) {
            coverage_pts += rules.food_points;
        }
        if (food > 1) {
            coverage_pts += rules.second_food_points;
        }
        if (food > 2) {
            coverage_pts += rules.third_food_points;
        }
        if (food && housed.physician) {
            coverage_pts += rules.physician_and_food_points;
        }
        healthy_population += (int)(coverage_pts * rules.coverage_factor * hpop);
    });

    target_value = calc_percentage(healthy_population, total_population);
    const int pop = city_population().current;
    for (const auto &entry : rules.population_bonus) {
        if (pop < entry.pop) {
            target_value += entry.bonus;
            break;
        }
    }

    // OG Isis altar on Bast complex: improve overall city health.
    if (city_temple_complexes().has_upgrade(BUILDING_TEMPLE_COMPLEX_BAST, etc_upgrade_altar)) {
        target_value += building_temple_complex_bast::current_params().isis_health_bonus;
    }

    const int step = rules.monthly_step;
    if (value < target_value) {
        value += step;
        if (value > target_value) {
            value = target_value;
        }

    } else if (value > target_value) {
        value -= step;
        if (value < target_value) {
            value = target_value;
        }
    }
    value = calc_bound(value, 0, 100);

    start_disease(total_population, false, 0);
}

void city_health_t::reset_mortuary_workers() {
    num_mortuary_workers = 0;
}

void city_health_t::add_mortuary_workers(int amount) {
    num_mortuary_workers += amount;
}

city_health_t& city_health() {
    return xvalue<city_health_t>::ref();
}

void city_health_t::reset() {
    *this = {};
}

class health_sim_system : public sim_system {
public:
    const char* name() const override { return "health"; }
    void on_reset() override { city_health().reset(); }
    void push_save_sections(int file_version) override {
        if (file_version >= save_version_city_sections) {
            g_chunk_io.push_chunk<city_health_chunk>(city_health_chunk::size, false);
        }
    }
    void register_steps(sim_schedule_t& schedule) override {
        schedule.add({sim_step_health_coverage, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 33) {
                              return;
                          }
                          city_health().update_coverage();
                      }});
        schedule.add({sim_step_plague_day, SIM_PHASE_DAY, [](int) { g_city.plague_update_day(); }});
        schedule.add({sim_step_health_month, SIM_PHASE_MONTH_CITY, [](int) { city_health().update_month(); }});
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_health_system) {
    static health_sim_system system;
    g_simulation.register_system(&system);
}

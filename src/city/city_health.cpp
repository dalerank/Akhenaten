#include "city_health.h"
#include "core/app_module.h"
#include "game/sim_schedule.h"

#include "core/profiler.h"
#include "core/calc.h"
#include "building/building_house.h"
#include "building/building_temple_complex.h"
#include "building/destruction.h"
#include "city/buildings.h"
#include "city/city.h"
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

void health_system::change(int amount) {
    _state.value = calc_bound(_state.value + amount, 0, 100);
}

void health_system::infect_house(building& main) {
    main.mark_plague(city_health_rules.plague_house_days);
}

void health_system::start_disease(int total_people, bool force, int plague_people) {
    if (!force && _state.value >= 40) {
        // Natural check blocked by good health — drop a leftover Bast force flag.
        _ctx.gods.bast_curse_active = false;
        return;
    }

    int chance_value = random_byte() & 0x3f;
    const bool bast_forced = _ctx.gods.bast_curse_active;
    if (bast_forced) {
        // Force the roll; clear flag only after an outbreak outcome below.
        chance_value = 0;
    }

    if (!force && (chance_value > 40 - _state.value)) {
        return;
    }

    int sick_people = calc_adjust_with_percentage(total_people, 7 + (random_byte() & 3));
    if (plague_people > 0) {
        sick_people = plague_people;
    }

    if (sick_people <= 0) {
        if (bast_forced) {
            _ctx.gods.bast_curse_active = false;
        }
        return;
    }

    int people_to_plague = sick_people - _state.num_mortuary_workers;
    if (people_to_plague <= 0) {
        if (bast_forced) {
            _ctx.gods.bast_curse_active = false;
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
        health_system::infect_house(main->base);
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
            _ctx.gods.bast_curse_active = false;
        }
        return;
    }

    if (bast_forced) {
        _ctx.gods.bast_curse_active = false;
    }

    // OG city_health_start_plague_at_house: one carrier from the outbreak's house.
    if (!game_features::gameplay_change_plagued_citizen_remake.to_bool()) {
        figure_plagued_citizen::create_at_house(*warn_building);
    }

    change(10);
    events::emit(event_city_disease{_ctx.absolute_day});

    e_building_type btype = warn_building->type;
    int grid_offset = warn_building->tile.grid_offset();
    if (_state.num_mortuary_workers > 0) {
        message_manager().post_with_popup_delay(MESSAGE_CAT_HEALTH_PROBLEM, force, "message_disease", btype,
          grid_offset);
    } else {
        message_manager().post_with_popup_delay(MESSAGE_CAT_HEALTH_PROBLEM, force, "message_disease_strikes", btype,
          grid_offset);
    }
}

void health_system::update_coverage() {
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

    auto& coverage = _ctx.coverage;
    coverage.apothecary = (uint8_t)calc_percentage(with_apothecary, population);
    coverage.mortuary = (uint8_t)calc_percentage(with_mortuary, population);
    coverage.physician = (uint8_t)calc_percentage(with_physician, population);
    coverage.dentist = (uint8_t)calc_percentage(with_dentist, population);
}

void health_system::update_month() {
    if (_ctx.population.current < 200 || _ctx.fixed_health_mission) {
        _state.value = 50;
        _state.target_value = 50;
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

    _state.target_value = calc_percentage(healthy_population, total_population);
    const int pop = _ctx.population.current;
    for (const auto &entry : rules.population_bonus) {
        if (pop < entry.pop) {
            _state.target_value += entry.bonus;
            break;
        }
    }

    // OG Isis altar on Bast complex: improve overall city health.
    if (_ctx.bast_complex_has_altar) {
        _state.target_value += building_temple_complex_bast::current_params().isis_health_bonus;
    }

    const int step = rules.monthly_step;
    if (_state.value < _state.target_value) {
        _state.value += step;
        if (_state.value > _state.target_value) {
            _state.value = _state.target_value;
        }

    } else if (_state.value > _state.target_value) {
        _state.value -= step;
        if (_state.value < _state.target_value) {
            _state.value = _state.target_value;
        }
    }
    _state.value = calc_bound(_state.value, 0, 100);

    start_disease(total_population, false, 0);
}

void health_system::reset_mortuary_workers() {
    _state.num_mortuary_workers = 0;
}

void health_system::add_mortuary_workers(int amount) {
    _state.num_mortuary_workers += amount;
}

class health_sim_system : public sim_system {
public:
    const char* name() const override { return "health"; }
    void register_steps() override {
        sim_schedule_add({SIM_PHASE_TICK_SLOT, 33, 350, "health_coverage", SIM_AREA_COVERAGE | SIM_AREA_HEALTH,
          [] { g_city.health_sys().update_coverage(); }});
        sim_schedule_add(
          {SIM_PHASE_DAY, -1, 60, "plague_day", SIM_AREA_HEALTH | SIM_AREA_HOUSES, [] { g_city.plague_update_day(); }});
        sim_schedule_add(
          {SIM_PHASE_MONTH_CITY, -1, 20, "health_month", SIM_AREA_HEALTH, [] { g_city.health_sys().update_month(); }});
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_health_system) {
    static health_sim_system system;
    g_simulation.register_system(&system);
}

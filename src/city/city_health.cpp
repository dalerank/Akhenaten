#include "city_health.h"

#include "core/profiler.h"
#include "core/calc.h"
#include "building/building_health.h"
#include "building/building_house.h"
#include "building/destruction.h"
#include "city/city.h"
#include "game/game_events.h"
#include "city/coverage.h"
#include "city/city_message.h"
#include "core/calc.h"
#include "core/random.h"
#include "game/tutorial.h"
#include "scenario/scenario.h"
#include "game/game.h"
#include "dev/debug.h"

declare_console_command_p(plague_start) {
    std::string args; is >> args;
    int plague_people = atoi(args.empty() ? "100" : args.c_str());

    int total_population = 0;
    buildings_house_do([&] (building_house *house) {
        if (house->house_population() <= 0) {
            return;
        }
        total_population += house->house_population();
    });
    g_city.health.start_disease(total_population, true, plague_people);
}

declare_console_command_p(plague_no) {
    buildings_house_do([&] (building_house *house) {
        if (house->house_population() <= 0) {
            return;
        }

        house->base.disease_days = 0;
        house->base.has_plague = false;
        house->base.common_health = 100;
    });
}


void city_health_t::change(int amount) {
    value = calc_bound(value + amount, 0, 100);
}

void city_health_t::start_disease(int total_people, bool force, int plague_people) {
    if (!force && value >= 40) {
        return;
    }

    int chance_value = random_byte() & 0x3f;
    if (g_city.religion.bast_curse_active) {
        // force plague
        chance_value = 0;
        g_city.religion.bast_curse_active = false;
    }

    if (!force && (chance_value > 40 - value)) {
        return;
    }

    int sick_people = calc_adjust_with_percentage(total_people, 7 + (random_byte() & 3));
    if (plague_people > 0) {
        sick_people = plague_people;
    }

    if (sick_people <= 0) {
        return;
    }

    change(10);
    int people_to_plague = sick_people - num_mortuary_workers;
    if (people_to_plague <= 0) {
        city_message_post_with_popup_delay(MESSAGE_CAT_HEALTH_PROBLEM, false, "malaria_problem", 0, 0);
        return;
    }

    events::emit(event_city_disease{game.simtime.absolute_day(true)});

    // kill people where has little common_health
    building *warn_building = nullptr;
    buildings_house_do([&] (building_house *house) {
        if (people_to_plague <= 0 || !house || house->house_population() <= 0) {
            return;
        }

        if (house->base.common_health < 10) {
            warn_building = &house->base;
            people_to_plague -= house->house_population();
            auto main = house->main();
            main->base.mark_plague(30);
        }
    });

    // kill people who don't have access to apothecary/physician
    buildings_house_do([&] (building_house *house) {
        if (people_to_plague <= 0 || house->house_population() <= 0) {
            return;
        }

        auto &housed = house->runtime_data();
        if (!(housed.apothecary || housed.physician)) {
            warn_building = &house->base;
            people_to_plague -= house->house_population();
            auto main = house->main();
            main->base.mark_plague(30);
        }
    });

    // kill people in tents
    buildings_house_do([&] (building_house *house) {
        if (people_to_plague <= 0 || house->house_population() <= 0) {
            return;
        }

        if (house->house_level() <= HOUSE_STURDY_HUT) {
            warn_building = &house->base;
            people_to_plague -= house->house_population();
            auto main = house->main();
            main->base.mark_plague(30);
        }
    });

    // kill anyone
    buildings_house_do([&] (building_house *house) {
        if (people_to_plague <= 0 || house->house_population() <= 0) {
            return;
        }

        warn_building = &house->base;
        people_to_plague -= house->house_population();
        auto main = house->main();
        main->base.mark_plague(30);
    });

    e_building_type btype = (warn_building ? warn_building->type : BUILDING_NONE);
    int grid_offset = (warn_building ? warn_building->tile.grid_offset() : 0);
    if (num_mortuary_workers > 0) {
        city_message_post_with_popup_delay(MESSAGE_CAT_HEALTH_PROBLEM, false, "message_health_disease", btype, grid_offset);
    } else {
        city_message_post_with_popup_delay(MESSAGE_CAT_HEALTH_PROBLEM, false, "message_health_plague", btype, grid_offset);
    }
}

void city_health_t::update_coverage() {
    OZZY_PROFILER_SECTION("Game/Update/Health Coverage");
    int population = g_city.population.current;

    const auto &mortuary_params = building_mortuary::current_params();
    auto &coverage = g_city.coverage;
    coverage.mortuary = std::min<int>(calc_percentage(mortuary_params.max_serve_clients * g_city.buildings.count_active(BUILDING_MORTUARY), population), 100);

    coverage.physician = std::min<int>(calc_percentage(1000 * g_city.buildings.count_active(BUILDING_PHYSICIAN), population), 100);
    coverage.dentist = std::min<int>(calc_percentage(1000 * g_city.buildings.count_active(BUILDING_DENTIST), population), 100);

    const auto &apothecary_params = building_apothecary::current_params();
    coverage.apothecary = std::min<int>(calc_percentage(apothecary_params.max_serve_clients * g_city.buildings.count_active(BUILDING_APOTHECARY), population), 100);
}


void city_health_t::update() {
    if (g_city.population.current < 200 || g_scenario.is_scenario_id(1, 2)) {
        value = 50;
        target_value = 50;
        return;
    }

    int total_population = 0;
    int healthy_population = 0;
    buildings_house_do([&] (building_house* house) {
        const short hpop = house->house_population();
        if (hpop <= 0) {
            return;
        }

        total_population += hpop;
        auto &housed = house->runtime_data();
        if (house->house_level() <= HOUSE_STURDY_HUT) {
            if (housed.apothecary) {
                healthy_population += hpop;
            } else {
                healthy_population += hpop / 4;
            }
        } else if (housed.physician) {
            if (housed.days_without_food == 0) {
                healthy_population += hpop;
            } else {
                healthy_population += hpop / 4;
            }
        } else if (housed.days_without_food == 0) {
            healthy_population += hpop / 4;
        }
    });

    target_value = calc_percentage(healthy_population, total_population);
    if (value < target_value) {
        value += 2;
        if (value > target_value) {
            value = target_value;
        }

    } else if (value > target_value) {
        value -= 2;
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

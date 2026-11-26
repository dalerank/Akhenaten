#include "coverage.h"
#include "city/buildings.h"
#include "game/simulation.h"
#include "core/app_module.h"
#include "game/sim_schedule.h"
#include "city/coverage_chunks.h"
#include "core/xvalue.h"
#include "io/chunk_serializer.h"
#include "io/gamestate/save_versions.h"

#include "building/building_house.h"
#include "city/constants.h"
#include "city/city.h"
#include "city/entertainment.h"
#include "city/constants.h"
#include "city/city_population.h"
#include "core/calc.h"
#include "core/profiler.h"

city_average_coverage_t& city_avg_coverage() {
    return xvalue<city_average_coverage_t>::ref();
}

void city_average_coverage_t::reset() {
    *this = {};
}

void city_average_coverage_t::update() {
    OZZY_PROFILER_FUNCTION();
    average_entertainment = 0;
    average_religion = 0;
    average_education = 0;
    average_health = 0;

    int num_houses = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        auto house = building_get(i)->dcast_house();

        if (house && house->state() == BUILDING_STATE_VALID && house->hsize() > 0) {
            num_houses++;
            auto &housed = house->runtime_data();
            average_entertainment += housed.entertainment;
            average_religion += housed.num_gods;
            average_education += housed.education;
            average_health += housed.health;
        }
    }

    if (num_houses) {
        average_entertainment /= num_houses;
        average_religion /= num_houses;
        average_education /= num_houses;
        average_health /= num_houses;
    }

    city_entertainment().calculate_shows();
}

city_coverage_t& city_coverage() {
    return xvalue<city_coverage_t>::ref();
}

void city_coverage_t::reset() {
    *this = {};
}

void city_coverage_t::update() {
    OZZY_PROFILER_FUNCTION();
    auto& population = city_population();
    const int pop = population.current;

    // entertainment
    const int active_booth = city_building_stats().count_active(BUILDING_BOOTH);
    booth = std::min(calc_percentage(400 * active_booth, pop), 100);

    bandstand = std::min(calc_percentage(700 * city_building_stats().count_active(BUILDING_BANDSTAND), pop), 100);
    pavilion = std::min(calc_percentage(1200 * city_building_stats().count_active(BUILDING_PAVILLION), pop), 100);
    senet_house = city_building_stats().count_active(BUILDING_SENET_HOUSE) <= 0 ? 0 : 100;
    zoo = std::min(calc_percentage(7500 * city_building_stats().count_active(BUILDING_ZOO), pop), 100);

    // education
    city_population().calculate_educational_age();

    int active_schools = city_building_stats().count_active(BUILDING_SCRIBAL_SCHOOL);
    const auto &school_config = building_static_params::get(BUILDING_SCRIBAL_SCHOOL);
    school = std::min(calc_percentage(school_config.max_service * active_schools, city_population().school_age), 100);

    int active_libraries = city_building_stats().count_active(BUILDING_LIBRARY);
    const auto &lib_config = building_static_params::get(BUILDING_LIBRARY);
    library = std::min(calc_percentage(lib_config.max_service * active_libraries, pop), 100);

    int active_academy = city_building_stats().count_active(BUILDING_ACADEMY);
    const auto &academy_config = building_static_params::get(BUILDING_ACADEMY);
    academy
      = std::min(calc_percentage(academy_config.max_service * active_academy, city_population().academy_age), 100);
}

int city_average_coverage_t::calc_average_entertainment() {
    const auto& coverage = city_coverage();
    return (coverage.senet_house + coverage.pavilion + coverage.bandstand + coverage.booth + coverage.zoo) / 5;
}

class coverage_system : public sim_system {
public:
    const char* name() const override { return "coverage"; }
    void on_reset() override { city_coverage().reset(); }
    void register_steps(sim_schedule_t& schedule) override {
        schedule.add({sim_step_coverage, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 33) {
                              return;
                          }
                          city_coverage().update();
                      }});
    }
};

class avg_coverage_sim_system : public sim_system {
public:
    const char* name() const override { return "avg_coverage"; }
    void on_reset() override { city_avg_coverage().reset(); }
    void push_save_sections(int file_version) override {
        if (file_version >= save_version_city_sections) {
            g_chunk_io.push_chunk<city_avg_coverage_chunk>(city_avg_coverage_chunk::size, false);
        }
    }
    void register_steps(sim_schedule_t& schedule) override {
        schedule.add({sim_step_avg_coverage_33, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 33) {
                              return;
                          }
                          city_avg_coverage().update();
                      }});
        schedule.add({sim_step_avg_coverage_49, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 49) {
                              return;
                          }
                          city_avg_coverage().update();
                      }});
        schedule.add({sim_step_avg_coverage_day, SIM_PHASE_DAY, [](int) { city_avg_coverage().update(); }});
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_coverage_system) {
    static coverage_system system;
    g_simulation.register_system(&system);
}

void ANK_REGISTER_APPLICATION_MODULE(register_avg_coverage_system) {
    static avg_coverage_sim_system system;
    g_simulation.register_system(&system);
}

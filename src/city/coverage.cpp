#include "coverage.h"

#include "building/building_house.h"
#include "city/constants.h"
#include "city/city.h"
#include "city/entertainment.h"
#include "city/constants.h"
#include "city/city_population.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "core/buffer.h"

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

    g_city.entertainment.calculate_shows();
}

void city_coverage_t::save(buffer *buf) {
    buf->write_u8(booth);
    buf->write_u8(0);
    buf->write_u16(0);
    buf->write_i32(bandstand);
    buf->write_i32(pavilion);
    buf->write_u8(physician);
    buf->write_u8(dentist);
    buf->write_u8(apothecary);
    buf->write_u8(0);
    buf->write_i32(senet_house);

    buf->write_i32(0);
    buf->write_i32(0);
    buf->write_i32(0);
    buf->write_i32(0);
    buf->write_i32(0);

    buf->write_i32(oracle);
    buf->write_i32(school);
    buf->write_i32(library);
    buf->write_i32(academy);
    buf->write_i32(mortuary);
}

void city_coverage_t::load(buffer *buf) {
    booth = buf->read_u8();
    buf->read_u8();
    buf->read_u16();
    bandstand = buf->read_i32();
    pavilion = buf->read_i32();
    physician = buf->read_u8();
    dentist = buf->read_u8();
    apothecary = buf->read_u8();
    int tmp = buf->read_u8();
    senet_house = buf->read_i32();

    buf->skip(5);

    oracle = buf->read_i32();
    school = buf->read_i32();
    library = buf->read_i32();
    academy = buf->read_i32();
    mortuary = buf->read_i32();
}

void city_coverage_t::update() {
    OZZY_PROFILER_FUNCTION();
    auto &population = g_city.population;
    const int pop = population.current;

    // entertainment
    const int active_booth = g_city.buildings.count_active(BUILDING_BOOTH);
    booth = std::min(calc_percentage(400 * active_booth, pop), 100);

    bandstand = std::min(calc_percentage(700 * g_city.buildings.count_active(BUILDING_BANDSTAND), pop), 100);
    pavilion = std::min(calc_percentage(1200 * g_city.buildings.count_active(BUILDING_PAVILLION), pop), 100);
    senet_house = g_city.buildings.count_active(BUILDING_SENET_HOUSE) <= 0 ? 0 : 100;

    // education
    population.calculate_educational_age();

    int active_schools = g_city.buildings.count_active(BUILDING_SCRIBAL_SCHOOL);
    const auto &school_config = building_static_params::get(BUILDING_SCRIBAL_SCHOOL);
    school = std::min(calc_percentage(school_config.max_service * active_schools, g_city.population.school_age), 100);

    int active_libraries = g_city.buildings.count_active(BUILDING_LIBRARY);
    const auto &lib_config = building_static_params::get(BUILDING_LIBRARY);
    library = std::min(calc_percentage(lib_config.max_service * active_libraries, pop), 100);

    int active_academy = g_city.buildings.count_active(BUILDING_ACADEMY);
    const auto &academy_config = building_static_params::get(BUILDING_ACADEMY);
    academy = std::min(calc_percentage(academy_config.max_service * active_academy, g_city.population.academy_age), 100);
}

int city_average_coverage_t::calc_average_entertainment() {
    const auto &coverage = g_city.coverage;
    return (coverage.senet_house + coverage.pavilion + coverage.bandstand + coverage.booth) / 4;
}

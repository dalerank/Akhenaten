#include "city/city.h"

#include "core/profiler.h"
#include "coverage.h"
#include "building/count.h"
#include "city/population.h"
#include "core/calc.h"

void city_t::coverage_update() {
    OZZY_PROFILER_SECTION("Game/Update/Avg Coverage Update");
    auto& coverage = g_coverage;
    int pop = population.population;

    // entertainment
    coverage.booth = std::min(calc_percentage(400 * building_count_active(BUILDING_BOOTH), pop), 100);
    coverage.bandstand = std::min(calc_percentage(700 * building_count_active(BUILDING_BANDSTAND), pop), 100);
    coverage.pavilion = std::min(calc_percentage(1200 * building_count_active(BUILDING_PAVILLION), pop), 100);
    coverage.senet_house = building_count_active(BUILDING_SENET_HOUSE) <= 0 ? 0 : 100;

    // education
    city_population_calculate_educational_age();

    coverage.school = std::min(calc_percentage(75 * building_count_active(BUILDING_SCRIBAL_SCHOOL), city_population_school_age()), 100);
    coverage.library = std::min(calc_percentage(800 * building_count_active(BUILDING_LIBRARY), pop), 100);
    coverage.academy = std::min(calc_percentage(100 * building_count_active(BUILDING_ACADEMY), city_population_academy_age()), 100);
}

int city_t::average_coverage_t::calc_average_entertainment() {
    return (g_coverage.senet_house + g_coverage.pavilion + g_coverage.bandstand + g_coverage.booth) / 4;
}
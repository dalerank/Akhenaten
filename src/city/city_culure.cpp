#include "city/city.h"

#include "core/profiler.h"
#include "coverage.h"
#include "building/count.h"
#include "city/population.h"
#include "city/gods.h"
#include "core/calc.h"

int city_god_coverage_total(e_god god, e_building_type temple, e_building_type shrine, e_building_type complex) {
    switch (city_gods_is_known(god)) {
    default:
    return 0;

    case GOD_STATUS_PATRON:
    return 150 * building_count_total(shrine) + 375 * building_count_active(temple) + 8000 * building_count_active(complex);
    break;

    case GOD_STATUS_KNOWN:
    return 300 * building_count_total(shrine) + 750 * building_count_active(temple) + 8000 * building_count_active(complex);
    break;
    }
}

void city_t::coverage_update() {
    OZZY_PROFILER_SECTION("Game/Update/Avg Coverage Update");
    auto& coverage = g_coverage;
    int population = g_city.population.population;

    // entertainment
    coverage.booth = std::min(calc_percentage(400 * building_count_active(BUILDING_BOOTH), population), 100);
    coverage.bandstand = std::min(calc_percentage(700 * building_count_active(BUILDING_BANDSTAND), population), 100);
    coverage.pavilion = std::min(calc_percentage(1200 * building_count_active(BUILDING_PAVILLION), population), 100);
    coverage.senet_house = building_count_active(BUILDING_SENET_HOUSE) <= 0 ? 0 : 100;

    // religion
    //    int oracles = building_count_total(BUILDING_ORACLE);
    //    coverage.oracle = top(calc_percentage(500 * oracles, population));
    coverage.religion[GOD_OSIRIS] = std::min(calc_percentage(population, city_god_coverage_total(GOD_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_OSIRIS, BUILDING_TEMPLE_COMPLEX_OSIRIS)), 100);
    coverage.religion[GOD_RA] = std::min(calc_percentage(population, city_god_coverage_total(GOD_RA, BUILDING_SHRINE_RA, BUILDING_TEMPLE_RA, BUILDING_TEMPLE_COMPLEX_RA)), 100);
    coverage.religion[GOD_PTAH] = std::min(calc_percentage(population, city_god_coverage_total(GOD_PTAH, BUILDING_SHRINE_PTAH, BUILDING_TEMPLE_PTAH, BUILDING_TEMPLE_COMPLEX_PTAH)), 100);
    coverage.religion[GOD_SETH] = std::min(calc_percentage(population, city_god_coverage_total(GOD_SETH, BUILDING_SHRINE_SETH, BUILDING_TEMPLE_SETH, BUILDING_TEMPLE_COMPLEX_SETH)), 100);
    coverage.religion[GOD_BAST] = std::min(calc_percentage(population, city_god_coverage_total(GOD_BAST, BUILDING_SHRINE_BAST, BUILDING_TEMPLE_BAST, BUILDING_TEMPLE_COMPLEX_BAST)), 100);

    g_city.avg_coverage.common_religion = coverage.religion[GOD_OSIRIS] + coverage.religion[GOD_RA]
        + coverage.religion[GOD_PTAH] + coverage.religion[GOD_SETH]
        + coverage.religion[GOD_BAST];
    g_city.avg_coverage.common_religion /= 5;

    // education
    city_population_calculate_educational_age();

    coverage.school = std::min(calc_percentage(75 * building_count_active(BUILDING_SCRIBAL_SCHOOL), city_population_school_age()), 100);
    coverage.library = std::min(calc_percentage(800 * building_count_active(BUILDING_LIBRARY), population), 100);
    coverage.academy = std::min(calc_percentage(100 * building_count_active(BUILDING_ACADEMY), city_population_academy_age()), 100);
}

int city_t::average_coverage_t::calc_average_entertainment() {
    return (g_coverage.senet_house + g_coverage.pavilion + g_coverage.bandstand + g_coverage.booth) / 4;
}
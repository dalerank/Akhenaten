#include "culture.h"

#include "building/building.h"
#include "building/count.h"
#include "city/constants.h"
#include "city/data_private.h"
#include "city/entertainment.h"
#include "city/festival.h"
#include "city/population.h"
#include "core/calc.h"
#include "gods.h"

struct coverage_data_t {
    int theater;
    int amphitheater;
    int colosseum;
    int hippodrome;
    int hospital;
    int school;
    int academy;
    int library;
    int religion[5];
    int oracle;
};

coverage_data_t g_coverage;

int city_culture_coverage_theater(void) {
    return g_coverage.theater;
}

int city_culture_coverage_amphitheater(void) {
    return g_coverage.amphitheater;
}

int city_culture_coverage_colosseum(void) {
    return g_coverage.colosseum;
}

int city_culture_coverage_hippodrome(void) {
    return g_coverage.hippodrome;
}

int city_culture_coverage_average_entertainment(void) {
    return (g_coverage.hippodrome + g_coverage.colosseum + g_coverage.amphitheater + g_coverage.theater) / 4;
}

int city_culture_coverage_religion(int god) {
    return g_coverage.religion[god];
}

int city_culture_coverage_school(void) {
    return g_coverage.school;
}

int city_culture_coverage_library(void) {
    return g_coverage.library;
}

int city_culture_coverage_academy(void) {
    return g_coverage.academy;
}

int city_culture_coverage_hospital(void) {
    return g_coverage.hospital;
}

int city_culture_average_education(void) {
    return city_data.culture.average_education;
}

int city_culture_average_entertainment(void) {
    return city_data.culture.average_entertainment;
}

int city_culture_average_health(void) {
    return city_data.culture.average_health;
}

static int top(int input) {
    return input > 100 ? 100 : input;
}

static int god_coverage_total(int god, int temple, int shrine, int complex) {
    switch (god_known_status(god)) {
    default:
        return 0;
    case GOD_STATUS_PATRON:
        return 150 * building_count_total(shrine) + 375 * building_count_active(temple)
               + 8000 * building_count_active(complex);
        break;
    case GOD_STATUS_KNOWN:
        return 300 * building_count_total(shrine) + 750 * building_count_active(temple)
               + 8000 * building_count_active(complex);
        break;
    }
}
void city_culture_update_coverage(void) {
    auto& coverage = g_coverage;
    int population = city_data.population.population;

    // entertainment
    coverage.theater = top(calc_percentage(400 * building_count_active(BUILDING_BOOTH), population));
    coverage.amphitheater = top(calc_percentage(700 * building_count_active(BUILDING_BANDSTAND), population));
    coverage.colosseum = top(calc_percentage(1200 * building_count_active(BUILDING_PAVILLION), population));
    if (building_count_active(BUILDING_SENET_HOUSE) <= 0)
        coverage.hippodrome = 0;
    else
        coverage.hippodrome = 100;

    // religion
    //    int oracles = building_count_total(BUILDING_ORACLE);
    //    coverage.oracle = top(calc_percentage(500 * oracles, population));
    coverage.religion[GOD_OSIRIS] = top(calc_percentage(
      population,
      god_coverage_total(GOD_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_OSIRIS, BUILDING_TEMPLE_COMPLEX_OSIRIS)));
    coverage.religion[GOD_RA] = top(
      calc_percentage(population,
                      god_coverage_total(GOD_RA, BUILDING_SHRINE_RA, BUILDING_TEMPLE_RA, BUILDING_TEMPLE_COMPLEX_RA)));
    coverage.religion[GOD_PTAH] = top(calc_percentage(
      population,
      god_coverage_total(GOD_PTAH, BUILDING_SHRINE_PTAH, BUILDING_TEMPLE_PTAH, BUILDING_TEMPLE_COMPLEX_PTAH)));
    coverage.religion[GOD_SETH] = top(calc_percentage(
      population,
      god_coverage_total(GOD_SETH, BUILDING_SHRINE_SETH, BUILDING_TEMPLE_SETH, BUILDING_TEMPLE_COMPLEX_SETH)));
    coverage.religion[GOD_BAST] = top(calc_percentage(
      population,
      god_coverage_total(GOD_BAST, BUILDING_SHRINE_BAST, BUILDING_TEMPLE_BAST, BUILDING_TEMPLE_COMPLEX_BAST)));

    city_data.culture.religion_coverage = coverage.religion[GOD_OSIRIS] + coverage.religion[GOD_RA]
                                          + coverage.religion[GOD_PTAH] + coverage.religion[GOD_SETH]
                                          + coverage.religion[GOD_BAST];
    city_data.culture.religion_coverage /= 5;

    // education
    city_population_calculate_educational_age();

    coverage.school = top(calc_percentage(75 * building_count_active(BUILDING_SCHOOL), city_population_school_age()));
    coverage.library = top(calc_percentage(800 * building_count_active(BUILDING_LIBRARY), population));
    coverage.academy
      = top(calc_percentage(100 * building_count_active(BUILDING_MENU_WATER_CROSSINGS), city_population_academy_age()));

    // health
    coverage.hospital = top(calc_percentage(1000 * building_count_active(BUILDING_MORTUARY), population));
}

void city_culture_calculate(void) {
    city_data.culture.average_entertainment = 0;
    city_data.culture.average_religion = 0;
    city_data.culture.average_education = 0;
    city_data.culture.average_health = 0;

    int num_houses = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->house_size) {
            num_houses++;
            city_data.culture.average_entertainment += b->data.house.entertainment;
            city_data.culture.average_religion += b->data.house.num_gods;
            city_data.culture.average_education += b->data.house.education;
            city_data.culture.average_health += b->data.house.health;
        }
    }
    if (num_houses) {
        city_data.culture.average_entertainment /= num_houses;
        city_data.culture.average_religion /= num_houses;
        city_data.culture.average_education /= num_houses;
        city_data.culture.average_health /= num_houses;
    }

    city_entertainment_calculate_shows();
    city_festival_calculate_costs();
}

void city_culture_save_state(buffer* buf) {
    auto& coverage = g_coverage;

    // Yes, hospital is saved twice
    buf->write_i32(coverage.theater);
    buf->write_i32(coverage.amphitheater);
    buf->write_i32(coverage.colosseum);
    buf->write_i32(coverage.hospital);
    buf->write_i32(coverage.hippodrome);
    for (int i = GOD_OSIRIS; i <= GOD_BAST; i++) {
        buf->write_i32(coverage.religion[i]);
    }
    buf->write_i32(coverage.oracle);
    buf->write_i32(coverage.school);
    buf->write_i32(coverage.library);
    buf->write_i32(coverage.academy);
    buf->write_i32(coverage.hospital);
}

void city_culture_load_state(buffer* buf) {
    auto& coverage = g_coverage;

    // Yes, hospital is saved twice
    coverage.theater = buf->read_i32();
    coverage.amphitheater = buf->read_i32();
    coverage.colosseum = buf->read_i32();
    coverage.hospital = buf->read_i32();
    coverage.hippodrome = buf->read_i32();
    for (int i = GOD_OSIRIS; i <= GOD_BAST; i++) {
        coverage.religion[i] = buf->read_i32();
    }
    coverage.oracle = buf->read_i32();
    coverage.school = buf->read_i32();
    coverage.library = buf->read_i32();
    coverage.academy = buf->read_i32();
    coverage.hospital = buf->read_i32();
}

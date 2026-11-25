#pragma once

#include "core/archive.h"
#include "city/coverage.h"

struct city_coverage_t {
    int booth;
    int bandstand;
    int pavilion;
    int senet_house;
    int zoo;
    uint8_t physician;
    uint8_t dentist;
    uint8_t apothecary;
    uint8_t mortuary;
    int school;
    int academy;
    int library;
    int oracle;

    void reset();
    void update();
};

ANK_CONFIG_PROPERTY(city_coverage_t,
    booth, bandstand, pavilion, senet_house, zoo, physician, dentist, apothecary, mortuary, school, academy, library, oracle)

city_coverage_t& city_coverage();

struct city_average_coverage_t {
    int32_t average_entertainment;
    int32_t average_religion;
    int32_t average_education;
    int32_t average_health;

    void reset();
    void update();
    int calc_average_entertainment();
};

ANK_CONFIG_PROPERTY(city_average_coverage_t, average_entertainment, average_religion, average_education, average_health)

city_average_coverage_t& city_avg_coverage();

#pragma once

#include <cstdint>

class buffer;

struct city_coverage_t {
    int booth;
    int bandstand;
    int pavilion;
    int senet_house;
    uint8_t physician;
    uint8_t dentist;
    uint8_t apothecary;
    uint8_t mortuary;
    int school;
    int academy;
    int library;
    int oracle;

    void save(buffer *buf);
    void load(buffer *buf);
    void update();
};

struct city_average_coverage_t {
    int32_t average_entertainment;
    int32_t average_religion;
    int32_t average_education;
    int32_t average_health;

    void update();
    int calc_average_entertainment();
};

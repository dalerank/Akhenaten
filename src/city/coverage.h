#pragma once

#include <cstdint>

class buffer;

struct coverage_data_t {
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
};

extern coverage_data_t g_coverage;

void city_coverage_save_state(buffer* buf);
void city_coverage_load_state(buffer* buf);

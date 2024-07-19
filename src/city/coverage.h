#pragma once

#include "city/gods.h"

class buffer;

struct coverage_data_t {
    int booth;
    int bandstand;
    int pavilion;
    int senet_house;
    int physician;
    int mortuary;
    int school;
    int academy;
    int library;
    int religion[5];
    int oracle;
};

extern coverage_data_t g_coverage;

int city_avg_coverage_religion(e_god god);

void city_coverage_save_state(buffer* buf);
void city_coverage_load_state(buffer* buf);

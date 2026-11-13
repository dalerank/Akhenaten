#pragma once

#include <cstdint>

#include "core/archive.h"

inline void decay_service(unsigned char& value) {
    if (value > 0) {
        --value;
    } else {
        value = 0;
    }
}

struct house_demands_missing {
    int well;
    int fountain;
    int entertainment;
    int more_entertainment;
    int education;
    int more_education;
    int religion;
    int second_religion;
    int third_religion;
    int dentist;
    int courthouse;
    int any_courthouse;
    int health;
    int more_health;
    int food;
    int second_luxury;
};

struct house_demands_requiring {
    int school;
    int library;
    int dentist;
    int courthouse;
    int more_courthouse;
    int health;
    int religion;
};

struct house_demands {
    house_demands_missing missing;
    house_demands_requiring requiring;
    uint8_t health;
    int religion;
    int education;
    int entertainment;
};

ANK_CONFIG_PROPERTY(house_demands_requiring, school, library, dentist, courthouse, more_courthouse, health, religion)
ANK_CONFIG_PROPERTY(house_demands_missing, entertainment, more_entertainment, dentist, courthouse, any_courthouse,
  health, more_health, second_luxury)
ANK_CONFIG_PROPERTY(house_demands, health, religion, education, entertainment)


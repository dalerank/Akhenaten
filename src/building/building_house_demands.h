#pragma once

inline void decay_service(unsigned char& value) {
    if (value > 0) {
        --value;
    } else {
        value = 0;
    }
}

struct house_demands {
    struct {
        int well;
        int fountain;
        int entertainment;
        int more_entertainment;
        int education;
        int more_education;
        int religion;
        int second_religion;
        int third_religion;
        int apothecary;
        int dentist;
        int mortuary;
        int physician;
        int water_supply;
        int magistrate;
        int food;
        int second_wine;
    } missing;

    struct {
        int school;
        int library;
        int dentist;
        int physician;
        int water_supply;
        int magistrate;
        int religion;
    } requiring;
    int health;
    int religion;
    int education;
    int entertainment;
};


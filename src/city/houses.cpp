#include "houses.h"

#include "city/city.h"

void city_t::houses_reset_demands() {
    houses.missing.fountain = 0;
    houses.missing.well = 0;
    houses.missing.entertainment = 0;
    houses.missing.more_entertainment = 0;
    houses.missing.education = 0;
    houses.missing.more_education = 0;
    houses.missing.religion = 0;
    houses.missing.second_religion = 0;
    houses.missing.third_religion = 0;
    houses.missing.apothecary = 0;
    houses.missing.dentist = 0;
    houses.missing.mortuary = 0;
    houses.missing.physician = 0;
    houses.missing.food = 0;
    // NB: second_wine purposely not cleared

    houses.requiring.school = 0;
    houses.requiring.library = 0;
    houses.requiring.dentist = 0;
    houses.requiring.physician = 0;
    houses.requiring.water_supply = 0;
    houses.requiring.religion = 0;
}


void city_t::houses_calculate_culture_demands(void) {
    // health
    houses.health = 0;
    int max = 0;
    if (houses.missing.water_supply > max) {
        houses.health = 1;
        max = houses.missing.water_supply;
    }

    if (houses.missing.apothecary > max) {
        houses.health = 2;
        max = houses.missing.apothecary;
    }

    if (houses.missing.dentist > max) {
        houses.health = 3;
        max = houses.missing.dentist;
    }

    if (houses.missing.physician > max) {
        houses.health = 4;
    }

    // education
    houses.education = 0;
    if (houses.missing.more_education > houses.missing.education)
        houses.education = 1; // schools(academies?)
    else if (houses.missing.more_education < houses.missing.education)
        houses.education = 2; // libraries
    else if (houses.missing.more_education || houses.missing.education)
        houses.education = 3; // more education

    // entertainment
    houses.entertainment = 0;
    if (houses.missing.entertainment > houses.missing.more_entertainment)
        houses.entertainment = 1;
    else if (houses.missing.more_entertainment)
        houses.entertainment = 2;

    // religion
    houses.religion = 0;
    max = 0;
    if (houses.missing.religion > max) {
        houses.religion = 1;
        max = houses.missing.religion;
    }
    if (houses.missing.second_religion > max) {
        houses.religion = 2;
        max = houses.missing.second_religion;
    }
    if (houses.missing.third_religion > max)
        houses.religion = 3;
}

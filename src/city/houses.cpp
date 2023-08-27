#include "houses.h"

#include "city/data_private.h"

void city_houses_reset_demands(void) {
    city_data.houses.missing.fountain = 0;
    city_data.houses.missing.well = 0;
    city_data.houses.missing.entertainment = 0;
    city_data.houses.missing.more_entertainment = 0;
    city_data.houses.missing.education = 0;
    city_data.houses.missing.more_education = 0;
    city_data.houses.missing.religion = 0;
    city_data.houses.missing.second_religion = 0;
    city_data.houses.missing.third_religion = 0;
    city_data.houses.missing.apothecary = 0;
    city_data.houses.missing.dentist = 0;
    city_data.houses.missing.mortuary = 0;
    city_data.houses.missing.physician = 0;
    city_data.houses.missing.food = 0;
    // NB: second_wine purposely not cleared

    city_data.houses.requiring.school = 0;
    city_data.houses.requiring.library = 0;
    city_data.houses.requiring.dentist = 0;
    city_data.houses.requiring.physician = 0;
    city_data.houses.requiring.water_supply = 0;
    city_data.houses.requiring.religion = 0;
}

house_demands* city_houses_demands(void) {
    return &city_data.houses;
}

void city_houses_calculate_culture_demands(void) {
    // health
    city_data.houses.health = 0;
    int max = 0;
    if (city_data.houses.missing.water_supply > max) {
        city_data.houses.health = 1;
        max = city_data.houses.missing.water_supply;
    }

    if (city_data.houses.missing.apothecary > max) {
        city_data.houses.health = 2;
        max = city_data.houses.missing.apothecary;
    }

    if (city_data.houses.missing.dentist > max) {
        city_data.houses.health = 3;
        max = city_data.houses.missing.dentist;
    }

    if (city_data.houses.missing.physician > max) {
        city_data.houses.health = 4;
    }

    // education
    city_data.houses.education = 0;
    if (city_data.houses.missing.more_education > city_data.houses.missing.education)
        city_data.houses.education = 1; // schools(academies?)
    else if (city_data.houses.missing.more_education < city_data.houses.missing.education)
        city_data.houses.education = 2; // libraries
    else if (city_data.houses.missing.more_education || city_data.houses.missing.education)
        city_data.houses.education = 3; // more education

    // entertainment
    city_data.houses.entertainment = 0;
    if (city_data.houses.missing.entertainment > city_data.houses.missing.more_entertainment)
        city_data.houses.entertainment = 1;
    else if (city_data.houses.missing.more_entertainment)
        city_data.houses.entertainment = 2;

    // religion
    city_data.houses.religion = 0;
    max = 0;
    if (city_data.houses.missing.religion > max) {
        city_data.houses.religion = 1;
        max = city_data.houses.missing.religion;
    }
    if (city_data.houses.missing.second_religion > max) {
        city_data.houses.religion = 2;
        max = city_data.houses.missing.second_religion;
    }
    if (city_data.houses.missing.third_religion > max)
        city_data.houses.religion = 3;
}

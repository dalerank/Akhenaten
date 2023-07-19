#ifndef CITY_HOUSES_H
#define CITY_HOUSES_H

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
        int barber;
        int bathhouse;
        int magistrate;
        int clinic;
        int hospital;
        int food;
        int second_wine;
    } missing;
    struct {
        int school;
        int library;
        int barber;
        int bathhouse;
        int magistrate;
        int clinic;
        int religion;
    } requiring;
    int health;
    int religion;
    int education;
    int entertainment;
} ;

void city_houses_reset_demands(void);

house_demands *city_houses_demands(void);

void city_houses_calculate_culture_demands(void);

#endif // CITY_HOUSES_H

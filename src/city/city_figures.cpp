#include "city/city.h"

void city_t::figures_reset() {
    figures.enemies = 0;
    figures.rioters = 0;
    figures.attacking_natives = 0;
    figures.animals_number = 0;
    figures.kingdome_soldiers = 0;
    figures.soldiers = 0;
    if (figures.security_breach_duration > 0)
        figures.security_breach_duration--;
}

void city_t::figures_add_animal() {
    figures.animals_number++;
}

void city_t::figures_add_attacking_native() {
    figures.security_breach_duration = 10;
    figures.attacking_natives++;
}

void city_t::figures_add_enemy() {
    figures.enemies++;
}

void city_t::figures_add_kingdome_soldier() {
    figures.kingdome_soldiers++;
}

void city_t::figures_add_rioter(int is_attacking) {
    figures.rioters++;
    if (is_attacking)
        figures.security_breach_duration = 10;
}

void city_t::figures_add_soldier() {
    figures.soldiers++;
}

//void city_figures_set_gladiator_revolt(void) {
//    figure.attacking_natives = 10;
//}

int city_t::figures_total_invading_enemies() {
    return figures.kingdome_soldiers + figures.enemies;
}

bool city_t::figures_has_security_breach() {
    return figures.security_breach_duration > 0;
}

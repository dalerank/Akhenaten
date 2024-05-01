#include "city/city.h"

void city_t::figures_reset() {
    figure.enemies = 0;
    figure.rioters = 0;
    figure.attacking_natives = 0;
    figure.animals_number = 0;
    figure.kingdome_soldiers = 0;
    figure.soldiers = 0;
    if (figure.security_breach_duration > 0)
        figure.security_breach_duration--;
}

void city_t::figures_add_animal() {
    figure.animals_number++;
}

void city_t::figures_add_attacking_native() {
    figure.security_breach_duration = 10;
    figure.attacking_natives++;
}

void city_t::figures_add_enemy() {
    figure.enemies++;
}

void city_t::figures_add_kingdome_soldier() {
    figure.kingdome_soldiers++;
}

void city_t::figures_add_rioter(int is_attacking) {
    figure.rioters++;
    if (is_attacking)
        figure.security_breach_duration = 10;
}

void city_t::figures_add_soldier() {
    figure.soldiers++;
}

//void city_figures_set_gladiator_revolt(void) {
//    figure.attacking_natives = 10;
//}

int city_t::figures_total_invading_enemies() {
    return figure.kingdome_soldiers + figure.enemies;
}

bool city_t::figures_has_security_breach() {
    return figure.security_breach_duration > 0;
}

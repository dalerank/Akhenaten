#include "city_figures.h"

#include "core/profiler.h"
#include "city/city.h"
#include "city/city_figures.h"
#include "figure/figure.h"

void city_figures_t::reset() {
    enemies = 0;
    rioters = 0;
    attacking_natives = 0;
    animals_number = 0;
    kingdome_soldiers = 0;
    soldiers = 0;
    if (security_breach_duration > 0) {
        security_breach_duration--;
    }
}

void city_figures_t::on_post_load() {
    for (auto &figure: map_figures()) {
        if (figure->type == FIGURE_NONE) {
            continue;
        }

        figure->dcast()->on_post_load();
    }
}

void city_figures_t::update() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure Action");
    reset();
    //g_city.entertainment.hippodrome_has_race = false;

    for (auto &figure: map_figures()) {
        figure->action_perform();
    }
}

void city_figures_t::add_animal() {
    animals_number++;
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

#include "military.h"
#include "game/simulation.h"
#include "core/app_module.h"
#include "game/sim_schedule.h"

#include "city/buildings.h"
#include "city/city.h"
#include "game/game_events.h"
#include "city/city_message.h"
#include "city/ratings.h"
#include "core/calc.h"
#include "empire/empire.h"
#include "figure/formation.h"
#include "figure/formation_batalion.h"
#include "scenario/distant_battle.h"

void city_military_t::clear_infantry_batalions() {
    infantry_batalions = 0;
}

void city_military_t::add_infantry_batalion() {
    infantry_batalions++;
}

bool city_military_t::has_infantry_batalions() {
    return infantry_batalions > 0;
}

void city_military_t::clear_kingdome_service_batalions() {
    kingdome_service_batalions = 0;
}

void city_military_t::update_totals() {
    kingdome_service_batalions = 0;
    total_soldiers = 0;
    total_batalions = 0;
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        const formation* m = formation_get(i);
        if (m->in_use && m->own_batalion) {
            total_batalions++;
            total_soldiers += m->num_figures;
            if (m->empire_service && m->num_figures > 0) {
                kingdome_service_batalions++;
            }
        }
    }
}

bool city_military_t::is_native_attack_active() {
    return native_attack_duration > 0;
}

void city_military_t::start_native_attack() {
    native_attack_duration = 2;
}

void city_military_t::decrease_native_attack_duration() {
    if (native_attack_duration > 0)
        native_attack_duration--;
}

static auto &city_data = g_city;

int city_military_distant_battle_kingdome_months_traveled() {
    return g_distant_battle.battle.egyptian_months_traveled;
}
void city_military_t::request_tower_sentry() {
    tower_sentry_request = 2;
}

void city_military_t::decay_tower_sentry_request() {
    if (tower_sentry_request > 0) {
        tower_sentry_request--;
    }
}

bool city_military_t::has_tower_sentry_request() const {
    return tower_sentry_request > 0;
}

class military_system : public sim_system {
public:
    const char* name() const override { return "military"; }
    void register_steps(sim_schedule_t& schedule) override {
        schedule.add({sim_step_tower_sentry_decay, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 31) {
                              return;
                          }
                          g_city.military.decay_tower_sentry_request();
                      }});
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_military_system) {
    static military_system system;
    g_simulation.register_system(&system);
}

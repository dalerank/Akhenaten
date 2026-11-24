#include "city/city_monuments.h"
#include "game/simulation.h"
#include "core/app_module.h"
#include "city/city.h"
#include "game/sim_schedule.h"

#include "game/game_events.h"
#include "js/js_register.h"

void city_monuments_t::update_month() {

}

void city_monuments_t::advance_year() {
    emit(esid(__func__));
}

class monuments_system : public sim_system {
public:
    const char* name() const override { return "monuments"; }
    void register_steps() override {
        sim_schedule_add(
          {sim_step_monuments_year, SIM_PHASE_YEAR, -1, SIM_AREA_MONUMENTS, [] { g_city.monuments.advance_year(); }});
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_monuments_system) {
    static monuments_system system;
    g_simulation.register_system(&system);
}

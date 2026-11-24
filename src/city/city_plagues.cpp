#include "city/city_plagues.h"
#include "game/sim_schedule.h"

#include "core/app_module.h"
#include "core/xvalue.h"
#include "game/simulation.h"

city_plagues_t& city_plagues() {
    return xvalue<city_plagues_t>::ref();
}

class plagues_system : public sim_system {
public:
    const char* name() const override { return "plagues"; }
    void register_steps(sim_schedule_t& schedule) override {
        schedule.add({sim_step_plagues, SIM_PHASE_TICK_CITY_END, -1, [] { city_plagues().decrease_countdowns(); }});
    }
    void on_reset() override { city_plagues().reset(); }
};

void ANK_REGISTER_APPLICATION_MODULE(register_plagues_system) {
    static plagues_system system;
    g_simulation.register_system(&system);
}

void city_plagues_t::reset() {
    *this = {};
}

void city_plagues_t::decrease_countdowns() {
    if (locusts_countdown > 0) {
        locusts_countdown--;
    }
    if (frogs_countdown > 0) {
        frogs_countdown--;
    }
}

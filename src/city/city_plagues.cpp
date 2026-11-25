#include "city/city_plagues.h"
#include "building/building_house.h"
#include "city/city_buildings.h"
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
        schedule.add({sim_step_plagues, SIM_PHASE_TICK_CITY_END, [](int) { city_plagues().decrease_countdowns(); }});
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

void city_plagues_t::update_day() {
    buildings_house_do([](auto house) {
        if (!house->hsize()) {
            return;
        }

        if (house->base.has_plague && house->base.disease_days > 0) {
            house->base.disease_days--;
            house->base.has_plague = (house->base.disease_days > 0);
        }

        auto& housed = house->runtime_data();
        if (housed.frog_infest_days > 0) {
            housed.frog_infest_days--;
        }
    });
}

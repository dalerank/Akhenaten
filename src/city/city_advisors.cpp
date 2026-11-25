#include "city/city_advisors.h"

#include "core/app_module.h"
#include "core/xvalue.h"
#include "game/sim_system.h"
#include "game/simulation.h"

city_advisors_t& city_advisors() {
    return xvalue<city_advisors_t>::ref();
}

void city_advisors_t::reset() {
    *this = {};
}

class advisors_sim_system : public sim_system {
public:
    const char* name() const override { return "advisors"; }
    void on_reset() override { city_advisors().reset(); }
};

void ANK_REGISTER_APPLICATION_MODULE(register_advisors_system) {
    static advisors_sim_system system;
    g_simulation.register_system(&system);
}

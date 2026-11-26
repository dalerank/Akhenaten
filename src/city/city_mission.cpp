#include "city/city_mission.h"
#include "city/campaign_carry.h"

#include "city/city_mission_chunks.h"
#include "core/app_module.h"
#include "core/xvalue.h"
#include "game/sim_system.h"
#include "game/simulation.h"
#include "io/chunk_serializer.h"

city_mission_t& city_mission() {
    return xvalue<city_mission_t>::ref();
}

void city_mission_t::reset() {
    *this = {};
}

class mission_sim_system : public sim_system {
public:
    const char* name() const override { return "mission"; }
    void on_reset() override {
        city_mission().reset();
        g_campaign_carry.clear_troops();
        g_campaign_carry.clear_monuments();
    }
    void push_save_sections(int file_version) override {
        g_chunk_io.push_chunk<city_mission_chunk>(city_mission_chunk::size, false);
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_mission_system) {
    static mission_sim_system system;
    g_simulation.register_system(&system);
}

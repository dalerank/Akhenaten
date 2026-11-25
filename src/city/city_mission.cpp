#include "city/city_mission.h"

#include "city/city_mission_chunks.h"
#include "core/app_module.h"
#include "core/xvalue.h"
#include "game/sim_system.h"
#include "game/simulation.h"
#include "io/chunk_serializer.h"
#include "io/gamestate/save_versions.h"

city_mission_t& city_mission() {
    return xvalue<city_mission_t>::ref();
}

void city_mission_t::reset() {
    *this = {};
}

class mission_sim_system : public sim_system {
public:
    const char* name() const override { return "mission"; }
    void on_reset() override { city_mission().reset(); }
    void push_save_sections(int file_version) override {
        if (file_version >= save_version_city_sections) {
            g_chunk_io.push_chunk<city_mission_chunk>(city_mission_chunk::size, false);
        }
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_mission_system) {
    static mission_sim_system system;
    g_simulation.register_system(&system);
}

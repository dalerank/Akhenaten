#include "city_desirability.h"
#include "game/simulation.h"
#include "core/app_module.h"
#include "game/sim_schedule.h"

#include "core/profiler.h"
#include "building/building.h"
#include "grid/elevation.h"
#include "city/city_buildings.h"
#include "grid/desirability.h"

void building_update_desirability(void) {
    OZZY_PROFILER_SECTION(_, "Game/Run/Tick/Building Update Desirability");
    buildings_valid_do([] (building &b) {
        b.current_desirability = g_desirability.get_max(b.tile, b.size);
        if (b.is_adjacent_to_water) {
            b.current_desirability += 10;
        }

        const int elevation = map_elevation_at(b.tile.grid_offset());
        switch (elevation) {
        case 0:
            break;
        case 1:
            b.current_desirability += 10;
            break;
        case 2:
            b.current_desirability += 12;
            break;
        case 3:
            b.current_desirability += 14;
            break;
        case 4:
            b.current_desirability += 16;
            break;
        default:
            b.current_desirability += 18;
            break;
        }
    });
}

class desirability_system : public sim_system {
public:
    const char* name() const override { return "desirability"; }
    void register_steps() override {
        sim_schedule_add({SIM_PHASE_TICK_SLOT, 38, 410, "building_desirability", SIM_AREA_BUILDINGS,
          [] { building_update_desirability(); }});
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_desirability_system) {
    static desirability_system system;
    g_simulation.register_system(&system);
}

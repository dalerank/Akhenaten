#include "city_malaria_risk.h"

#include "core/profiler.h"
#include "core/calc.h"
#include "building/building.h"
#include "building/building_house.h"
#include "grid/malaria_risk.h"
#include "city/city_buildings.h"

void building_update_malaria_risk(void) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Building Update Malaria Risk");
    buildings_valid_do([] (building &b) {
        int risk = g_malaria_risk.get_max(b.tile, b.size);
        
        auto house = b.dcast_house();
        if (house) {
            auto &housed = house->runtime_data();
            if (housed.apothecary > 0) {
                risk = std::max(0, risk - 30);
            }

            if (housed.water_supply > 0) {
                risk = std::max(0, risk - 20);
            }
        }
        
        b.malaria_risk = (uint8_t)calc_bound(risk, 0, 100);
    });
}


#include "city_malaria_risk.h"

#include "core/profiler.h"
#include "core/calc.h"
#include "building/building.h"
#include "building/building_house.h"
#include "grid/malaria_risk.h"
#include "grid/terrain.h"
#include "city/city_buildings.h"

void building_update_malaria_risk(void) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Building Update Malaria Risk");
    buildings_valid_do([] (building &b) {
        int risk = g_malaria_risk.get_max(b.tile, b.size);
        
        // Вычисляем базовый риск от terrain (вода/болота) - это минимальное значение
        // которое не может быть снижено аптекой/водоснабжением
        int base_terrain_risk = 0;
        
        // Проверяем близость к болотам (высокий базовый риск)
        if (map_terrain_exists_tile_in_radius_with_type(b.tile, b.size, 3, TERRAIN_MARSHLAND)) {
            base_terrain_risk = std::max(base_terrain_risk, 50); // Минимум 50 для болот
        } else if (map_terrain_exists_tile_in_radius_with_type(b.tile, b.size, 2, TERRAIN_MARSHLAND)) {
            base_terrain_risk = std::max(base_terrain_risk, 40);
        }
        
        // Проверяем близость к воде (средний базовый риск)
        if (map_terrain_is_adjacent_to_water(b.tile, b.size)) {
            base_terrain_risk = std::max(base_terrain_risk, 40); // Минимум 40 для воды рядом
        } else if (map_terrain_exists_tile_in_radius_with_type(b.tile, b.size, 2, TERRAIN_WATER)) {
            base_terrain_risk = std::max(base_terrain_risk, 30); // Минимум 30 для воды в радиусе 2
        }
        
        // Применяем снижение от аптеки/водоснабжения, но не ниже базового риска от terrain
        auto house = b.dcast_house();
        if (house) {
            auto &housed = house->runtime_data();
            if (housed.apothecary > 0) {
                risk = std::max(base_terrain_risk, risk - 30);
            }

            if (housed.water_supply > 0) {
                risk = std::max(base_terrain_risk, risk - 20);
            }
        }
        
        // Финальный риск не может быть ниже базового риска от terrain
        risk = std::max(risk, base_terrain_risk);
        
        b.malaria_risk = (uint8_t)calc_bound(risk, 0, 100);
    });
}


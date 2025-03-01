#include "houses.h"

#include "city/city.h"
#include "core/random.h"
#include "core/profiler.h"
#include "figure/service.h"
#include "game/game.h"
#include "grid/routing/routing_terrain.h"
#include "building/building_house.h"

void city_t::houses_reset_demands() {
    houses.missing.fountain = 0;
    houses.missing.well = 0;
    houses.missing.entertainment = 0;
    houses.missing.more_entertainment = 0;
    houses.missing.education = 0;
    houses.missing.more_education = 0;
    houses.missing.religion = 0;
    houses.missing.second_religion = 0;
    houses.missing.third_religion = 0;
    houses.missing.apothecary = 0;
    houses.missing.dentist = 0;
    houses.missing.mortuary = 0;
    houses.missing.physician = 0;
    houses.missing.food = 0;
    // NB: second_wine purposely not cleared

    houses.requiring.school = 0;
    houses.requiring.library = 0;
    houses.requiring.dentist = 0;
    houses.requiring.physician = 0;
    houses.requiring.water_supply = 0;
    houses.requiring.religion = 0;
}

void city_t::house_service_update_health() {
    OZZY_PROFILER_SECTION("Game/Update/House Service Update Health");
    buildings_valid_do([] (building &b) {
        auto house = b.dcast_house();

        if (!house || !b.house_size || b.house_population <= 0) {
            return;
        }

        decay_service(b.common_health);

        auto &housed = house->runtime_data();
        int target_common_health = (!!housed.apothecary ? 33 : 0)
                                    + (!!housed.physician ? 33 : 0)
                                    + (!!housed.dentist ? 33 : 0);

        b.common_health += ((b.common_health < target_common_health) ? +1 : -1);
        b.common_health = std::clamp<int8_t>(b.common_health, 0, 100);

        if (b.has_plague) {
            random_generate_next();
            int chance_death = std::max(100 - b.common_health, 10);
            int randm = (random_short() % 99 + 1);
            bool has_death_today = (randm < chance_death);
            if (has_death_today && b.house_population > 0) {
                --b.house_population;
            }
        }
    });
}

void city_t::houses_calculate_culture_demands(void) {
    // health
    houses.health = 0;
    int max = 0;
    if (houses.missing.water_supply > max) {
        houses.health = 1;
        max = houses.missing.water_supply;
    }

    if (houses.missing.apothecary > max) {
        houses.health = 2;
        max = houses.missing.apothecary;
    }

    if (houses.missing.dentist > max) {
        houses.health = 3;
        max = houses.missing.dentist;
    }

    if (houses.missing.physician > max) {
        houses.health = 4;
    }

    // education
    houses.education = 0;
    if (houses.missing.more_education > houses.missing.education)
        houses.education = 1; // schools(academies?)
    else if (houses.missing.more_education < houses.missing.education)
        houses.education = 2; // libraries
    else if (houses.missing.more_education || houses.missing.education)
        houses.education = 3; // more education

    // entertainment
    houses.entertainment = 0;
    if (houses.missing.entertainment > houses.missing.more_entertainment)
        houses.entertainment = 1;
    else if (houses.missing.more_entertainment)
        houses.entertainment = 2;

    // religion
    houses.religion = 0;
    max = 0;
    if (houses.missing.religion > max) {
        houses.religion = 1;
        max = houses.missing.religion;
    }
    if (houses.missing.second_religion > max) {
        houses.religion = 2;
        max = houses.missing.second_religion;
    }
    if (houses.missing.third_religion > max)
        houses.religion = 3;
}

void city_t::house_service_decay_services() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/House Decay Culture");
    buildings_valid_do([] (building &b) {
        auto house = b.dcast_house();

        if (!house || !b.house_size) {
            return;
        }

        auto &housed = house->runtime_data();
        decay_service(housed.booth_juggler);
        decay_service(housed.bandstand_juggler);
        decay_service(housed.bandstand_musician);
        decay_service(housed.pavillion_musician);
        decay_service(housed.senet_player);
        decay_service(housed.magistrate);
        decay_service(housed.bullfighter);
        decay_service(housed.school);
        decay_service(housed.library);
        decay_service(housed.academy);
        decay_service(housed.apothecary);
        decay_service(housed.dentist);
        decay_service(housed.mortuary);
        decay_service(housed.physician);
        decay_service(housed.temple_osiris);
        decay_service(housed.temple_ra);
        decay_service(housed.temple_ptah);
        decay_service(housed.temple_seth);
        decay_service(housed.temple_bast);
        decay_service(housed.bazaar_access);

    });
}

void city_t::house_service_decay_tax_collector() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Tax Collector Update");
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->house_tax_coverage)
            b->house_tax_coverage--;
    }
}

void city_t::house_service_decay_houses_covered() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/House Service Decay Update");
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_UNUSED) { // b->type != BUILDING_TOWER
            if (b->houses_covered > 0)
                b->houses_covered--;
            //            if (building_is_farm(b->type) && b->data.industry.labor_days_left > 0)
            //                b->data.industry.labor_days_left--;
            ////            else if (b->houses_covered > 0)
            ////                b->houses_covered--;
            //
            ////            if (b->houses_covered == 255)
            ////                b->houses_covered = 0;
            //            if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            //                if (b->data.industry.labor_state == 2)
            //                    b->data.industry.labor_state = 1;
            //                if (b->data.industry.labor_days_left == 0)
            //                    b->data.industry.labor_state = 0;
            //            }
        }
    }
}

void city_t::house_process_evolve_and_consume_goods() {
    OZZY_PROFILER_SECTION("Game/Update/Process And Consume Goods");
    g_city.houses_reset_demands();
    house_demands &demands = g_city.houses;
    bool has_expanded = false;
    buildings_house_do([&] (building &h) {
        building_house *house = h.dcast_house();
        e_building_type save_type = h.type;
        has_expanded |= house->evolve(&demands);
        e_building_type new_type = h.type;
        if (new_type != save_type) {
            h.clear_impl();
        }
    });

    if (game.simtime.day == 0 || game.simtime.day == 7) {
        buildings_house_do([&] (building &h) {
            building_house *house = h.dcast_house();
            //building_house_check_for_corruption(&h);
            house->consume_resources();
        });
    }

    if (has_expanded) {
        map_routing_update_land();
    }
}


void city_t::house_service_calculate_culture_aggregates() {
    OZZY_PROFILER_SECTION("Game/Update/House Aggreate Culture");
    int base_entertainment = avg_coverage.calc_average_entertainment() / 5;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        auto house = building_get(i)->dcast_house();
        if (!house || house->state() != BUILDING_STATE_VALID || !house->base.house_size)
            continue;

        // entertainment
        auto &housed = house->runtime_data();
        housed.entertainment = base_entertainment;
        const int jugglers_value = std::max<int>(housed.booth_juggler, housed.bandstand_juggler);
        housed.entertainment += (jugglers_value / 5);
 
        const int musicians_value = std::max<int>(housed.bandstand_musician, housed.pavillion_musician);
        housed.entertainment += (musicians_value / 4);

        const int dancers_value = housed.pavillion_dancer;
        housed.entertainment += (dancers_value / 3);

        const int senet_value = housed.senet_player;
        housed.entertainment += (senet_value / 2.5f);

        housed.entertainment = std::min<int>(housed.entertainment, 100);

        // education
        housed.education = 0;
        if (housed.school || housed.library) {
            housed.education = 1;
            if (housed.school && housed.library) {
                housed.education = 2;
                if (housed.academy)
                    housed.education = 3;
            }
        }

        // religion
        housed.num_gods = 0;
        if (housed.temple_osiris)
            ++housed.num_gods;

        if (housed.temple_ra)
            ++housed.num_gods;

        if (housed.temple_ptah)
            ++housed.num_gods;

        if (housed.temple_seth)
            ++housed.num_gods;

        if (housed.temple_bast)
            ++housed.num_gods;

        if (housed.num_gods == 0 && housed.shrine_access) {
            housed.num_gods = 1;
        }

        // health
        housed.health = 0;
        if (housed.apothecary)
            ++housed.health;

        if (housed.physician)
            ++housed.health;
    }
}

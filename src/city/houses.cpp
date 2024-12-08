#include "houses.h"

#include "city/city.h"
#include "core/random.h"
#include "core/profiler.h"
#include "figure/service.h"
#include "game/time.h"
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
        if (!b.house_size || b.house_population <= 0) {
            return;
        }

        decay_service(b.common_health);

        int target_common_health = (!!b.data.house.apothecary ? 33 : 0)
                                    + (!!b.data.house.physician ? 33 : 0)
                                    + (!!b.data.house.dentist ? 33 : 0);

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
        if (!b.house_size) {
            return;
        }

        decay_service(b.data.house.booth_juggler);
        decay_service(b.data.house.bandstand_juggler);
        decay_service(b.data.house.bandstand_musician);
        decay_service(b.data.house.pavillion_musician);
        decay_service(b.data.house.senet_player);
        decay_service(b.data.house.magistrate);
        decay_service(b.data.house.bullfighter);
        decay_service(b.data.house.school);
        decay_service(b.data.house.library);
        decay_service(b.data.house.academy);
        decay_service(b.data.house.apothecary);
        decay_service(b.data.house.dentist);
        decay_service(b.data.house.mortuary);
        decay_service(b.data.house.physician);
        decay_service(b.data.house.temple_osiris);
        decay_service(b.data.house.temple_ra);
        decay_service(b.data.house.temple_ptah);
        decay_service(b.data.house.temple_seth);
        decay_service(b.data.house.temple_bast);
        decay_service(b.data.house.bazaar_access);

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

    if (gametime().day == 0 || gametime().day == 7) {
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
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || !b->house_size)
            continue;

        // entertainment
        b->data.house.entertainment = base_entertainment;
        const int jugglers_value = std::max<int>(b->data.house.booth_juggler, b->data.house.bandstand_juggler);
        b->data.house.entertainment += (jugglers_value / 10);
 
        const int musicians_value = std::max<int>(b->data.house.bandstand_musician, b->data.house.pavillion_musician);
        b->data.house.entertainment += (musicians_value / 5);

        const int dancers_value = b->data.house.pavillion_dancer;
        b->data.house.entertainment += (dancers_value / 3);

        const int senet_value = b->data.house.senet_player;
        b->data.house.entertainment += (senet_value / 2.5f);

        b->data.house.entertainment = std::min<int>(b->data.house.entertainment, 100);

        // education
        b->data.house.education = 0;
        if (b->data.house.school || b->data.house.library) {
            b->data.house.education = 1;
            if (b->data.house.school && b->data.house.library) {
                b->data.house.education = 2;
                if (b->data.house.academy)
                    b->data.house.education = 3;
            }
        }

        // religion
        b->data.house.num_gods = 0;
        if (b->data.house.temple_osiris)
            ++b->data.house.num_gods;

        if (b->data.house.temple_ra)
            ++b->data.house.num_gods;

        if (b->data.house.temple_ptah)
            ++b->data.house.num_gods;

        if (b->data.house.temple_seth)
            ++b->data.house.num_gods;

        if (b->data.house.temple_bast)
            ++b->data.house.num_gods;

        if (b->data.house.num_gods == 0 && b->data.house.shrine_access) {
            b->data.house.num_gods = 1;
        }

        // health
        b->data.house.health = 0;
        if (b->data.house.apothecary)
            ++b->data.house.health;

        if (b->data.house.physician)
            ++b->data.house.health;
    }
}

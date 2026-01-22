#include "city/city.h"

#include "core/random.h"
#include "core/profiler.h"
#include "figure/service.h"
#include "game/game.h"
#include "grid/routing/routing_terrain.h"
#include "building/building_house.h"

void city_t::house_service_update_health() {
    OZZY_PROFILER_FUNCTION();
    buildings_house_do([] (auto house) {
        if (house->house_population() <= 0) {
            return;
        }

        decay_service(house->base.common_health);

        auto &housed = house->runtime_data();
        int target_common_health = (!!housed.apothecary ? 33 : 0)
                                    + (!!housed.physician ? 33 : 0)
                                    + (!!housed.dentist ? 33 : 0);

        auto &b = house->base;
        b.common_health += ((b.common_health < target_common_health) ? +1 : -1);
        b.common_health = std::clamp<int8_t>(b.common_health, 0, 100);

        if (b.has_plague) {
            random_generate_next();
            int chance_death = std::max(100 - b.common_health, 10);
            int randm = (random_short() % 99 + 1);
            bool has_death_today = (randm < chance_death);
            if (has_death_today && house->house_population() > 0) {
                house->change_population(-1);
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

void city_t::house_service_decay_houses_covered() {
    OZZY_PROFILER_FUNCTION();
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

void city_t::house_process_evolve() {
    OZZY_PROFILER_FUNCTION();
    g_city.houses_reset_demands();
    house_demands &demands = g_city.houses;
    bool has_expanded = false;
    buildings_house_do([&] (building_house *house) {
        e_building_type save_type = house->type();
        has_expanded |= house->evolve(&demands);
        e_building_type new_type = house->type();
        if (new_type != save_type) {
            house->base.clear_impl();
        }
    });

    if (has_expanded) {
        map_routing_update_land();
    }
}

void city_t::house_service_calculate_culture_aggregates() {
    OZZY_PROFILER_FUNCTION();
    int base_entertainment = avg_coverage.calc_average_entertainment() / 5;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        auto house = building_get(i)->dcast_house();
        if (!house || house->state() != BUILDING_STATE_VALID || !house->hsize())
            continue;

        // entertainment
        auto &housed = house->runtime_data();
        const model_house& model = house->model();
        housed.entertainment = base_entertainment;
        const int jugglers_value = std::max<int>(housed.booth_juggler, housed.bandstand_juggler);
        housed.entertainment += (jugglers_value * 10) / model.entertainment_juggler_divider;
 
        const int musicians_value = std::max<int>(housed.bandstand_musician, housed.pavillion_musician);
        housed.entertainment += (musicians_value * 10) / model.entertainment_musician_divider;

        const int dancers_value = housed.pavillion_dancer;
        housed.entertainment += (dancers_value * 10) / model.entertainment_dancer_divider;

        const int senet_value = housed.senet_player;
        housed.entertainment += (senet_value * 10) / model.entertainment_senet_divider;

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

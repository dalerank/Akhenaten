#include "house_service.h"

#include "building/building.h"
#include "building/industry.h"
#include "city/coverage.h"
#include "core/game_environment.h"
#include "core/profiler.h"

static void decay(unsigned char* value) {
    if (*value > 0)
        *value = *value - 1;
    else {
        *value = 0;
    }
}

void house_service_decay_culture(void) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/House Decay Culture");
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || !b->house_size)
            continue;

        decay(&b->data.house.juggler);
        decay(&b->data.house.bandstand_juggler);
        decay(&b->data.house.bandstand_musician);
        decay(&b->data.house.colosseum_gladiator);
        decay(&b->data.house.magistrate);
        decay(&b->data.house.hippodrome);
        decay(&b->data.house.school);
        decay(&b->data.house.library);
        decay(&b->data.house.academy);
        decay(&b->data.house.apothecary);
        decay(&b->data.house.dentist);
        decay(&b->data.house.mortuary);
        decay(&b->data.house.physician);
        decay(&b->data.house.temple_osiris);
        decay(&b->data.house.temple_ra);
        decay(&b->data.house.temple_ptah);
        decay(&b->data.house.temple_seth);
        decay(&b->data.house.temple_bast);
        decay(&b->data.house.bazaar_access);
    }
}

void house_service_decay_tax_collector(void) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Tax Collector Update");
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->house_tax_coverage)
            b->house_tax_coverage--;
    }
}

void house_service_decay_houses_covered(void) {
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

void house_service_calculate_culture_aggregates(void) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/House Aggreate Culture");
    int base_entertainment = city_culture_coverage_average_entertainment() / 5;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || !b->house_size)
            continue;

        // entertainment
        b->data.house.entertainment = base_entertainment;
        if (b->data.house.juggler || b->data.house.bandstand_juggler) {
            b->data.house.entertainment += 10;
        }

        if (b->data.house.bandstand_musician) {
            b->data.house.entertainment += 15;
        }

        if (b->data.house.colosseum_gladiator) {
            //            if (b->data.house.magistrate)
            //                b->data.house.entertainment += 25;
            //            else {
            b->data.house.entertainment += 15;
            //            }
        }

        if (b->data.house.hippodrome) {
            b->data.house.entertainment += 30;
        }

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

#include "coverage.h"

#include "building/building.h"
#include "building/count.h"
#include "city/constants.h"
#include "city/city.h"
#include "city/entertainment.h"
#include "city/festival.h"
#include "city/constants.h"
#include "city/population.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "core/buffer.h"
#include "gods.h"

coverage_data_t g_coverage;
static auto &city_data = g_city;

int city_avg_coverage_religion(e_god god) {
    return g_coverage.religion[god];
}

void city_t::average_coverage_t::update() {
    OZZY_PROFILER_SECTION("Game/Update/Culture Calculate");
    city_data.avg_coverage.average_entertainment = 0;
    city_data.avg_coverage.average_religion = 0;
    city_data.avg_coverage.average_education = 0;
    city_data.avg_coverage.average_health = 0;

    int num_houses = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->house_size) {
            num_houses++;
            city_data.avg_coverage.average_entertainment += b->data.house.entertainment;
            city_data.avg_coverage.average_religion += b->data.house.num_gods;
            city_data.avg_coverage.average_education += b->data.house.education;
            city_data.avg_coverage.average_health += b->data.house.health;
        }
    }

    if (num_houses) {
        city_data.avg_coverage.average_entertainment /= num_houses;
        city_data.avg_coverage.average_religion /= num_houses;
        city_data.avg_coverage.average_education /= num_houses;
        city_data.avg_coverage.average_health /= num_houses;
    }

    g_city.entertainment.calculate_shows();
}

void city_coverage_save_state(buffer* buf) {
    auto& coverage = g_coverage;

    buf->write_i32(coverage.booth);
    buf->write_i32(coverage.bandstand);
    buf->write_i32(coverage.pavilion);
    buf->write_i32(coverage.physician);
    buf->write_i32(coverage.senet_house);

    for (int i = GOD_OSIRIS; i <= GOD_BAST; i++) {
        buf->write_i32(coverage.religion[i]);
    }

    buf->write_i32(coverage.oracle);
    buf->write_i32(coverage.school);
    buf->write_i32(coverage.library);
    buf->write_i32(coverage.academy);
    buf->write_i32(coverage.mortuary);
}

void city_coverage_load_state(buffer* buf) {
    auto& coverage = g_coverage;

    // Yes, hospital is saved twice
    coverage.booth = buf->read_i32();
    coverage.bandstand = buf->read_i32();
    coverage.pavilion = buf->read_i32();
    coverage.physician = buf->read_i32();
    coverage.senet_house = buf->read_i32();

    for (int i = GOD_OSIRIS; i <= GOD_BAST; i++) {
        coverage.religion[i] = buf->read_i32();
    }

    coverage.oracle = buf->read_i32();
    coverage.school = buf->read_i32();
    coverage.library = buf->read_i32();
    coverage.academy = buf->read_i32();
    coverage.mortuary = buf->read_i32();
}

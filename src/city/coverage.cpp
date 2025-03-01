#include "coverage.h"

#include "building/building_house.h"
#include "building/count.h"
#include "city/constants.h"
#include "city/city.h"
#include "city/entertainment.h"
#include "city/constants.h"
#include "city/population.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "core/buffer.h"

city_coverage_t g_coverage;

void city_average_coverage_t::update() {
    static auto &data = g_city;

    OZZY_PROFILER_SECTION("Game/Update/Culture Calculate");
    data.avg_coverage.average_entertainment = 0;
    data.avg_coverage.average_religion = 0;
    data.avg_coverage.average_education = 0;
    data.avg_coverage.average_health = 0;

    int num_houses = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        auto house = building_get(i)->dcast_house();

        if (house && house->state() == BUILDING_STATE_VALID && house->base.house_size) {
            num_houses++;
            auto &housed = house->runtime_data();
            data.avg_coverage.average_entertainment += housed.entertainment;
            data.avg_coverage.average_religion += housed.num_gods;
            data.avg_coverage.average_education += housed.education;
            data.avg_coverage.average_health += housed.health;
        }
    }

    if (num_houses) {
        data.avg_coverage.average_entertainment /= num_houses;
        data.avg_coverage.average_religion /= num_houses;
        data.avg_coverage.average_education /= num_houses;
        data.avg_coverage.average_health /= num_houses;
    }

    g_city.entertainment.calculate_shows();
}

void city_coverage_t::save(buffer *buf) {
    buf->write_i32(booth);
    buf->write_i32(bandstand);
    buf->write_i32(pavilion);
    buf->write_u8(physician);
    buf->write_u8(dentist);
    buf->write_u8(apothecary);
    buf->write_u8(0);
    buf->write_i32(senet_house);

    buf->write_i32(0);
    buf->write_i32(0);
    buf->write_i32(0);
    buf->write_i32(0);
    buf->write_i32(0);

    buf->write_i32(oracle);
    buf->write_i32(school);
    buf->write_i32(library);
    buf->write_i32(academy);
    buf->write_i32(mortuary);
}

void city_coverage_t::load(buffer *buf) {
    booth = buf->read_i32();
    bandstand = buf->read_i32();
    pavilion = buf->read_i32();
    physician = buf->read_u8();
    dentist = buf->read_u8();
    apothecary = buf->read_u8();
    int tmp = buf->read_u8();
    senet_house = buf->read_i32();

    buf->skip(5);

    oracle = buf->read_i32();
    school = buf->read_i32();
    library = buf->read_i32();
    academy = buf->read_i32();
    mortuary = buf->read_i32();
}

int city_average_coverage_t::calc_average_entertainment() {
    return (g_coverage.senet_house + g_coverage.pavilion + g_coverage.bandstand + g_coverage.booth) / 4;
}

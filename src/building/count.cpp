#include "count.h"

#include "building/building.h"
#include "city/buildings.h"
#include "city/city.h"
#include "core/profiler.h"
#include "core/game_environment.h"
#include "figure/figure.h"

#include <string.h>

struct record {
    int active;
    int total;
};

struct count_data_t {
    struct record buildings[BUILDING_MAX];
    struct record industry[RESOURCES_MAX];
};

count_data_t g_count_data;

void building_clear_counters() {
    memset(&g_count_data, 0, sizeof(count_data_t));
}

void building_increase_type_count(e_building_type type, bool active) {
    g_count_data.buildings[type].total++;
    g_count_data.buildings[type].active += (active ? 1 : 0);
}

void building_increase_industry_count(int resource, bool active) {
    g_count_data.industry[resource].total++;
    g_count_data.industry[resource].active += (active ? 1 : 0);
}

static void limit_senet_house() {
    if (g_count_data.buildings[BUILDING_SENET_HOUSE].total > 1) {
        g_count_data.buildings[BUILDING_SENET_HOUSE].total = 1;
    }

    if (g_count_data.buildings[BUILDING_SENET_HOUSE].active > 1) {
        g_count_data.buildings[BUILDING_SENET_HOUSE].active = 1;
    }
}

int building_count_active(e_building_type type) {
    return g_count_data.buildings[type].active;
}

int building_count_active(std::initializer_list<e_building_type> types) {
    int count = 0;
    for (const auto &type : types) {
        count += building_count_active(type);
    }

    return count;
}

int building_count_total(e_building_type type) {
    return g_count_data.buildings[type].total;
}

int building_count_industry_active(e_resource resource) {
    return g_count_data.industry[resource].active;
}

int building_count_industry_total(e_resource resource) {
    return g_count_data.industry[resource].total;
}

io_buffer* iob_building_count_industry = new io_buffer([](io_buffer* iob, size_t version) {
    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_INT32, &g_count_data.industry[i].total);

    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_INT32, &g_count_data.industry[i].active);

    //    // culture 1
    //    data.buildings[BUILDING_BOOTH].total = culture1->read_i32();
    //    data.buildings[BUILDING_BOOTH].active = culture1->read_i32();
    //    data.buildings[BUILDING_BANDSTAND].total = culture1->read_i32();
    //    data.buildings[BUILDING_BANDSTAND].active = culture1->read_i32();
    //    data.buildings[BUILDING_PAVILLION].total = culture1->read_i32();
    //    data.buildings[BUILDING_PAVILLION].active = culture1->read_i32();
    //    data.buildings[BUILDING_SENET_HOUSE].total = culture1->read_i32();
    //    data.buildings[BUILDING_SENET_HOUSE].active = culture1->read_i32();
    //    data.buildings[BUILDING_SCRIBAL_SCHOOL].total = culture1->read_i32();
    //    data.buildings[BUILDING_SCRIBAL_SCHOOL].active = culture1->read_i32();
    //    data.buildings[BUILDING_LIBRARY].total = culture1->read_i32();
    //    data.buildings[BUILDING_LIBRARY].active = culture1->read_i32();
    //    data.buildings[BUILDING_MENU_WATER_CROSSINGS].total = culture1->read_i32();
    //    data.buildings[BUILDING_MENU_WATER_CROSSINGS].active = culture1->read_i32();
    //    data.buildings[BUILDING_DENTIST].total = culture1->read_i32();
    //    data.buildings[BUILDING_DENTIST].active = culture1->read_i32();
    //    data.buildings[BUILDING_MENU_MONUMENTS].total = culture1->read_i32();
    //    data.buildings[BUILDING_MENU_MONUMENTS].active = culture1->read_i32();
    //    data.buildings[BUILDING_APOTHECARY].total = culture1->read_i32();
    //    data.buildings[BUILDING_APOTHECARY].active = culture1->read_i32();
    //    data.buildings[BUILDING_MORTUARY].total = culture1->read_i32();
    //    data.buildings[BUILDING_MORTUARY].active = culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_OSIRIS].total = culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_RA].total = culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_PTAH].total = culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_SETH].total = culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_BAST].total = culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_OSIRIS].total = culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_RA].total = culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_PTAH].total = culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_SETH].total = culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_BAST].total = culture1->read_i32();
    //    data.buildings[BUILDING_ORACLE].total = culture1->read_i32();
    //
    //    // culture 2
    //    data.buildings[BUILDING_JUGGLER_SCHOOL].total = culture2->read_i32();
    //    data.buildings[BUILDING_JUGGLER_SCHOOL].active = culture2->read_i32();
    //    data.buildings[BUILDING_CONSERVATORY].total = culture2->read_i32();
    //    data.buildings[BUILDING_CONSERVATORY].active = culture2->read_i32();
    //    data.buildings[BUILDING_DANCE_SCHOOL].total = culture2->read_i32();
    //    data.buildings[BUILDING_DANCE_SCHOOL].active = culture2->read_i32();
    //    data.buildings[BUILDING_CHARIOT_MAKER].total = culture2->read_i32();
    //    data.buildings[BUILDING_CHARIOT_MAKER].active = culture2->read_i32();
    //
    //    // culture 3
    //    data.buildings[BUILDING_TEMPLE_OSIRIS].active = culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_RA].active = culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_PTAH].active = culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_SETH].active = culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_BAST].active = culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_OSIRIS].active = culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_RA].active = culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_PTAH].active = culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_SETH].active = culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_BAST].active = culture3->read_i32();
    //
    //    // military
    //    data.buildings[BUILDING_MILITARY_ACADEMY].total = military->read_i32();
    //    data.buildings[BUILDING_MILITARY_ACADEMY].active = military->read_i32();
    //    data.buildings[BUILDING_RECRUITER].total = military->read_i32();
    //    data.buildings[BUILDING_RECRUITER].active = military->read_i32();
    //
    //    // support
    //    data.buildings[BUILDING_BAZAAR].total = support->read_i32();
    //    data.buildings[BUILDING_BAZAAR].active = support->read_i32();
    //    data.buildings[BUILDING_WATER_LIFT].total = support->read_i32();
    //    data.buildings[BUILDING_WATER_LIFT].active = support->read_i32();
    //    data.buildings[BUILDING_MENU_BEAUTIFICATION].total = support->read_i32();
    //    data.buildings[BUILDING_MENU_BEAUTIFICATION].active = support->read_i32();
});
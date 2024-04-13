#include "count.h"

#include "building/building.h"
#include "city/buildings.h"
#include "city/health.h"
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

static void clear_counters() {
    memset(&g_count_data, 0, sizeof(count_data_t));
}

void building_increase_type_count(int type, bool active) {
    ++g_count_data.buildings[type].total;
    g_count_data.buildings[type].active += (active ? 1 : 0);
}
void building_increase_industry_count(int resource, bool active) {
    ++g_count_data.industry[resource].total;
    g_count_data.industry[resource].active += (active ? 1 : 0);
}

static void limit_hippodrome() {
    if (g_count_data.buildings[BUILDING_SENET_HOUSE].total > 1) {
        g_count_data.buildings[BUILDING_SENET_HOUSE].total = 1;
    }

    if (g_count_data.buildings[BUILDING_SENET_HOUSE].active > 1) {
        g_count_data.buildings[BUILDING_SENET_HOUSE].active = 1;
    }
}

void building_entertainment_update() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Entertainment Update");
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->house_size) {
            continue;
        }

        int is_entertainment_venue = 0;
        int type = b->type;
        switch (type) {
        // SPECIAL TREATMENT
        // entertainment venues
        case BUILDING_BOOTH:
        case BUILDING_BANDSTAND:
        case BUILDING_PAVILLION:
        case BUILDING_SENET_HOUSE:
            is_entertainment_venue = 1;
            break;
        }

        if (is_entertainment_venue) {
            // update number of shows
            int shows = 0;
            if (b->data.entertainment.days1 > 0) {
                --b->data.entertainment.days1;
                ++shows;
            }

            if (b->data.entertainment.days2 > 0) {
                --b->data.entertainment.days2;
                ++shows;
            }

            if (type != BUILDING_BOOTH && b->data.entertainment.days3_or_play > 0) {
                --b->data.entertainment.days3_or_play;
                ++shows;
            }

            b->data.entertainment.num_shows = shows;
        }
    }
}

void building_count_update() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Buildin Count Update");
    clear_counters();
    city_buildings_reset_dock_wharf_counters();
    city_health_reset_mortuary_workers();

    buildings_valid_do ( [] (building &b) {
        if (b.house_size) {
            return;
        }

        e_building_type type = b.type;
        switch (type) {
        default:
            building_increase_type_count(type, b.num_workers > 0);
            break;

        case BUILDING_PAVILLION:
            building_increase_type_count(type, b.num_workers > 0);
            building_increase_type_count(BUILDING_BANDSTAND, b.num_workers > 0);
            building_increase_type_count(BUILDING_BOOTH, b.num_workers > 0);
            break;

        case BUILDING_SENET_HOUSE:
            building_increase_type_count(type, b.num_workers > 0);
            break;

        case BUILDING_RECRUITER:
            city_buildings_set_recruiter(b.id);
            building_increase_type_count(type, b.num_workers > 0);
            break;

        case BUILDING_MORTUARY:
            building_increase_type_count(type, b.num_workers > 0);
            city_health_add_mortuary_workers(b.num_workers);
            break;

            // water
        case BUILDING_WATER_LIFT:
        case BUILDING_MENU_BEAUTIFICATION:
            building_increase_type_count(type, b.has_water_access);
            break;

            // education
        case BUILDING_LIBRARY:
        case BUILDING_ACADEMY:
            // health
        case BUILDING_DENTIST:
        case BUILDING_MENU_MONUMENTS:
        case BUILDING_APOTHECARY:
            // government
        case BUILDING_VILLAGE_PALACE:
        case BUILDING_TOWN_PALACE:
            // entertainment schools
        case BUILDING_JUGGLER_SCHOOL:
        case BUILDING_CONSERVATORY:
        case BUILDING_DANCE_SCHOOL:
        case BUILDING_SENET_MASTER:
            // military
        case BUILDING_MILITARY_ACADEMY:
            // religion
        case BUILDING_TEMPLE_OSIRIS:
        case BUILDING_TEMPLE_RA:
        case BUILDING_TEMPLE_PTAH:
        case BUILDING_TEMPLE_SETH:
        case BUILDING_TEMPLE_BAST:
        case BUILDING_TEMPLE_COMPLEX_OSIRIS:
        case BUILDING_TEMPLE_COMPLEX_RA:
        case BUILDING_TEMPLE_COMPLEX_PTAH:
        case BUILDING_TEMPLE_COMPLEX_SETH:
        case BUILDING_TEMPLE_COMPLEX_BAST:
        case BUILDING_ORACLE:
            building_increase_type_count(type, b.num_workers > 0);
            break;

        case BUILDING_SHRINE_OSIRIS:
        case BUILDING_SHRINE_RA:
        case BUILDING_SHRINE_PTAH:
        case BUILDING_SHRINE_SETH:
        case BUILDING_SHRINE_BAST:
            building_increase_type_count(type, b.has_road_access);
            break;

            // water-side
        case BUILDING_FISHING_WHARF:
            if (b.num_workers > 0 && b.has_open_water_access) {
                city_buildings_add_working_wharf(!b.data.industry.fishing_boat_id);
            }
            break;

        case BUILDING_SHIPWRIGHT:
            if (b.num_workers > 0 && b.has_open_water_access) {
                city_buildings_add_working_shipyard(b.id);
            }
            break;
        }
        // industry
        switch (b.type) {
        case BUILDING_GRAIN_FARM:
            building_increase_industry_count(RESOURCE_GRAIN, b.num_workers > 0);
            break;
        case BUILDING_BARLEY_FARM:
            building_increase_industry_count(RESOURCE_BARLEY, b.num_workers > 0);
            break;
        case BUILDING_FLAX_FARM:
            building_increase_industry_count(RESOURCE_FLAX, b.num_workers > 0);
            break;
        case BUILDING_LETTUCE_FARM:
            building_increase_industry_count(RESOURCE_LETTUCE, b.num_workers > 0);
            break;
        case BUILDING_POMEGRANATES_FARM:
            building_increase_industry_count(RESOURCE_POMEGRANATES, b.num_workers > 0);
            break;
        case BUILDING_CHICKPEAS_FARM:
            building_increase_industry_count(RESOURCE_CHICKPEAS, b.num_workers > 0);
            break;
        case BUILDING_FIGS_FARM:
            building_increase_industry_count(RESOURCE_FIGS, b.num_workers > 0);
            break;
        case BUILDING_HENNA_FARM:
            building_increase_industry_count(RESOURCE_HENNA, b.num_workers > 0);
            break;
        case BUILDING_HUNTING_LODGE:
            building_increase_industry_count(RESOURCE_GAMEMEAT, b.num_workers > 0);
            break;
        case BUILDING_FISHING_WHARF:
            building_increase_industry_count(RESOURCE_FISH, b.num_workers > 0);
            break;
        case BUILDING_CLAY_PIT:
            building_increase_industry_count(RESOURCE_CLAY, b.num_workers > 0);
            break;
        case BUILDING_GEMSTONE_MINE:
            building_increase_industry_count(RESOURCE_GEMS, b.num_workers > 0);
            break;
        case BUILDING_GOLD_MINE:
            building_increase_industry_count(RESOURCE_GOLD, b.num_workers > 0);
            break;
        case BUILDING_COPPER_MINE:
            building_increase_industry_count(RESOURCE_COPPER, b.num_workers > 0);
            break;
        case BUILDING_STONE_QUARRY:
            building_increase_industry_count(RESOURCE_STONE, b.num_workers > 0);
            break;
        case BUILDING_LIMESTONE_QUARRY:
            building_increase_industry_count(RESOURCE_LIMESTONE, b.num_workers > 0);
            break;
        case BUILDING_GRANITE_QUARRY:
            building_increase_industry_count(RESOURCE_GRANITE, b.num_workers > 0);
            break;
        case BUILDING_SANDSTONE_QUARRY:
            building_increase_industry_count(RESOURCE_SANDSTONE, b.num_workers > 0);
            break;
        case BUILDING_POTTERY_WORKSHOP:
            building_increase_industry_count(RESOURCE_POTTERY, b.num_workers > 0);
            break;
        case BUILDING_BREWERY_WORKSHOP:
            building_increase_industry_count(RESOURCE_BEER, b.num_workers > 0);
            break;
        case BUILDING_WEAVER_WORKSHOP:
            building_increase_industry_count(RESOURCE_LINEN, b.num_workers > 0);
            break;
        case BUILDING_JEWELS_WORKSHOP:
            building_increase_industry_count(RESOURCE_LUXURY_GOODS, b.num_workers > 0);
            break;
        case BUILDING_BRICKS_WORKSHOP:
            building_increase_industry_count(RESOURCE_BRICKS, b.num_workers > 0);
            break;
        case BUILDING_LAMP_WORKSHOP:
            building_increase_industry_count(RESOURCE_LAMPS, b.num_workers > 0);
            break;
        case BUILDING_PAINT_WORKSHOP:
            building_increase_industry_count(RESOURCE_PAINT, b.num_workers > 0);
            break;
        case BUILDING_WEAPONSMITH:
            building_increase_industry_count(RESOURCE_WEAPONS, b.num_workers > 0);
            break;
        case BUILDING_CHARIOTS_WORKSHOP:
            building_increase_industry_count(RESOURCE_CHARIOTS, b.num_workers > 0);
            break;

        default:
            b.dcast()->update_count();
            return;
        }
    });
}

int building_count_active(e_building_type type) {
    return g_count_data.buildings[type].active;
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
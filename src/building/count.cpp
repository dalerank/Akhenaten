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

static void clear_counters(void) {
    memset(&g_count_data, 0, sizeof(count_data_t));
}
static void increase_count(int type, bool active) {
    ++g_count_data.buildings[type].total;
    if (active)
        ++g_count_data.buildings[type].active;
}
static void increase_industry_count(int resource, bool active) {
    ++g_count_data.industry[resource].total;
    if (active)
        ++g_count_data.industry[resource].active;
}

static void limit_hippodrome(void) {
    if (g_count_data.buildings[BUILDING_SENET_HOUSE].total > 1)
        g_count_data.buildings[BUILDING_SENET_HOUSE].total = 1;
    if (g_count_data.buildings[BUILDING_SENET_HOUSE].active > 1)
        g_count_data.buildings[BUILDING_SENET_HOUSE].active = 1;
}

void building_entertainment_update() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Entertainment Update");
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->house_size)
            continue;

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
void building_count_update(void) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Buildin Count Update");
    clear_counters();
    city_buildings_reset_dock_wharf_counters();
    city_health_reset_hospital_workers();

    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->house_size)
            continue;

        int type = b->type;
        switch (type) {
        default:
            increase_count(type, b->num_workers > 0);
            break;

        // SPECIAL TREATMENT
        // entertainment venues
        case BUILDING_BOOTH:
            increase_count(type, b->num_workers > 0);
            break;

        case BUILDING_BANDSTAND:
            increase_count(type, b->num_workers > 0);
            increase_count(BUILDING_BOOTH, b->num_workers > 0);
            break;

        case BUILDING_PAVILLION:
            increase_count(type, b->num_workers > 0);
            increase_count(BUILDING_BANDSTAND, b->num_workers > 0);
            increase_count(BUILDING_BOOTH, b->num_workers > 0);
            break;

        case BUILDING_SENET_HOUSE:
            increase_count(type, b->num_workers > 0);
            break;

        case BUILDING_RECRUITER:
            city_buildings_set_recruiter(i);
            increase_count(type, b->num_workers > 0);
            break;

        case BUILDING_MORTUARY:
            increase_count(type, b->num_workers > 0);
            city_health_add_hospital_workers(b->num_workers);
            break;

            // water
        case BUILDING_WATER_LIFT:
        case BUILDING_MENU_BEAUTIFICATION:
            increase_count(type, b->has_water_access);
            break;

            // DEFAULT TREATMENT
            // education
        case BUILDING_SCHOOL:
        case BUILDING_LIBRARY:
        case BUILDING_MENU_WATER_CROSSINGS:
            // health
        case BUILDING_DENTIST:
        case BUILDING_MENU_MONUMENTS:
        case BUILDING_APOTHECARY:
            // government
        case BUILDING_TAX_COLLECTOR:
        case BUILDING_TAX_COLLECTOR_UPGRADED:
        case BUILDING_GREATE_PALACE:
        case BUILDING_GREATE_PALACE_UPGRADED:
            // entertainment schools
        case BUILDING_JUGGLER_SCHOOL:
        case BUILDING_CONSERVATORY:
        case BUILDING_DANCE_SCHOOL:
        case BUILDING_CHARIOT_MAKER:
            // distribution
        case BUILDING_MARKET:
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
            increase_count(type, b->num_workers > 0);
            break;

        case BUILDING_SHRINE_OSIRIS:
        case BUILDING_SHRINE_RA:
        case BUILDING_SHRINE_PTAH:
        case BUILDING_SHRINE_SETH:
        case BUILDING_SHRINE_BAST:
            increase_count(type, b->has_road_access);
            break;

            // water-side
        case BUILDING_FISHING_WHARF:
            if (b->num_workers > 0)
                city_buildings_add_working_wharf(!b->data.industry.fishing_boat_id);
            break;

        case BUILDING_DOCK:
            if (b->num_workers > 0 && b->has_water_access)
                city_buildings_add_working_dock(i);
            break;
        }
        // industry
        switch (b->type) {
        case BUILDING_GRAIN_FARM:
            increase_industry_count(RESOURCE_GRAIN, b->num_workers > 0);
            break;
            //                    increase_industry_count(RESOURCE_STRAW, b->num_workers > 0); break; // TODO: how is
            //                    this handled in Pharaoh??
        case BUILDING_BARLEY_FARM:
            increase_industry_count(RESOURCE_BARLEY, b->num_workers > 0);
            break;
        case BUILDING_FLAX_FARM:
            increase_industry_count(RESOURCE_FLAX, b->num_workers > 0);
            break;
        case BUILDING_LETTUCE_FARM:
            increase_industry_count(RESOURCE_LETTUCE, b->num_workers > 0);
            break;
        case BUILDING_POMEGRANATES_FARM:
            increase_industry_count(RESOURCE_POMEGRANATES, b->num_workers > 0);
            break;
        case BUILDING_CHICKPEAS_FARM:
            increase_industry_count(RESOURCE_CHICKPEAS, b->num_workers > 0);
            break;
        case BUILDING_FIGS_FARM:
            increase_industry_count(RESOURCE_FIGS, b->num_workers > 0);
            break;
        case BUILDING_HENNA_FARM:
            increase_industry_count(RESOURCE_HENNA, b->num_workers > 0);
            break;
            ////
        case BUILDING_HUNTING_LODGE:
            increase_industry_count(RESOURCE_GAMEMEAT, b->num_workers > 0);
            break;
        case BUILDING_FISHING_WHARF:
            increase_industry_count(RESOURCE_FISH, b->num_workers > 0);
            break;
            ////
        case BUILDING_CLAY_PIT:
            increase_industry_count(RESOURCE_CLAY, b->num_workers > 0);
            break;
        case BUILDING_REED_GATHERER:
            increase_industry_count(RESOURCE_REEDS, b->num_workers > 0);
            break;
        case BUILDING_WOOD_CUTTERS:
            increase_industry_count(RESOURCE_TIMBER, b->num_workers > 0);
            break;
            ////
        case BUILDING_GEMSTONE_MINE:
            increase_industry_count(RESOURCE_GEMS, b->num_workers > 0);
            break;
        case BUILDING_GOLD_MINE:
            increase_industry_count(RESOURCE_GOLD, b->num_workers > 0);
            break;
        case BUILDING_COPPER_MINE:
            increase_industry_count(RESOURCE_COPPER, b->num_workers > 0);
            break;
            ////
        case BUILDING_STONE_QUARRY:
            increase_industry_count(RESOURCE_STONE, b->num_workers > 0);
            break;
        case BUILDING_LIMESTONE_QUARRY:
            increase_industry_count(RESOURCE_LIMESTONE, b->num_workers > 0);
            break;
        case BUILDING_GRANITE_QUARRY:
            increase_industry_count(RESOURCE_GRANITE, b->num_workers > 0);
            break;
        case BUILDING_SANDSTONE_QUARRY:
            increase_industry_count(RESOURCE_SANDSTONE, b->num_workers > 0);
            break;
            ////
        case BUILDING_POTTERY_WORKSHOP:
            increase_industry_count(RESOURCE_POTTERY, b->num_workers > 0);
            break;
        case BUILDING_BEER_WORKSHOP:
            increase_industry_count(RESOURCE_BEER, b->num_workers > 0);
            break;
        case BUILDING_LINEN_WORKSHOP:
            increase_industry_count(RESOURCE_LINEN, b->num_workers > 0);
            break;
        case BUILDING_JEWELS_WORKSHOP:
            increase_industry_count(RESOURCE_LUXURY_GOODS, b->num_workers > 0);
            break;
        case BUILDING_PAPYRUS_WORKSHOP:
            increase_industry_count(RESOURCE_PAPYRUS, b->num_workers > 0);
            break;
        case BUILDING_BRICKS_WORKSHOP:
            increase_industry_count(RESOURCE_BRICKS, b->num_workers > 0);
            break;
        case BUILDING_LAMP_WORKSHOP:
            increase_industry_count(RESOURCE_LAMPS, b->num_workers > 0);
            break;
        case BUILDING_PAINT_WORKSHOP:
            increase_industry_count(RESOURCE_PAINT, b->num_workers > 0);
            break;
            //                case BUILDING_OIL_WORKSHOP:
            //                    increase_industry_count(RESOURCE_OIL_PH, b->num_workers > 0); break;
            ////
        case BUILDING_WEAPONS_WORKSHOP:
            increase_industry_count(RESOURCE_WEAPONS, b->num_workers > 0);
            break;
        case BUILDING_CHARIOTS_WORKSHOP:
            increase_industry_count(RESOURCE_CHARIOTS, b->num_workers > 0);
            break;
            ////
        default:
            continue;
        }
        if (b->has_figure(2)) {
            figure* f = b->get_figure(2);
            if (f->state != FIGURE_STATE_ALIVE || f->destination()->id != i)
                b->remove_figure(2);
            //                b->immigrant_figure_id = 0;
        }
    }
    if (GAME_ENV == ENGINE_ENV_C3)
        limit_hippodrome();
}
int building_count_active(int type) {
    return g_count_data.buildings[type].active;
}
int building_count_total(int type) {
    return g_count_data.buildings[type].total;
}
int building_count_industry_active(int resource) {
    return g_count_data.industry[resource].active;
}
int building_count_industry_total(int resource) {
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
    //    data.buildings[BUILDING_SCHOOL].total = culture1->read_i32();
    //    data.buildings[BUILDING_SCHOOL].active = culture1->read_i32();
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
    //    data.buildings[BUILDING_MARKET].total = support->read_i32();
    //    data.buildings[BUILDING_MARKET].active = support->read_i32();
    //    data.buildings[BUILDING_WATER_LIFT].total = support->read_i32();
    //    data.buildings[BUILDING_WATER_LIFT].active = support->read_i32();
    //    data.buildings[BUILDING_MENU_BEAUTIFICATION].total = support->read_i32();
    //    data.buildings[BUILDING_MENU_BEAUTIFICATION].active = support->read_i32();
});
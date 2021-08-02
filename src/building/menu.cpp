#include "menu.h"

#include "city/buildings.h"
#include "core/config.h"
#include "empire/city.h"
#include "game/tutorial.h"
#include "scenario/building.h"

#define BUILD_MENU_ITEM_MAX 30

static const int MENU_int[][BUILD_MENU_MAX][BUILD_MENU_ITEM_MAX] = {
        {
                {BUILDING_HOUSE_VACANT_LOT, 0},
                {BUILDING_CLEAR_LAND, 0},
                {BUILDING_ROAD, 0},
                {BUILDING_DRAGGABLE_RESERVOIR, BUILDING_AQUEDUCT, BUILDING_FOUNTAIN, BUILDING_WELL, 0},
                {BUILDING_BARBER, BUILDING_BATHHOUSE, BUILDING_DOCTOR, BUILDING_HOSPITAL, 0},
                {BUILDING_MENU_SMALL_TEMPLES, BUILDING_MENU_LARGE_TEMPLES, BUILDING_ORACLE, 0},
                {BUILDING_SCHOOL, BUILDING_ACADEMY, BUILDING_LIBRARY, BUILDING_MISSION_POST, 0},
                {BUILDING_THEATER, BUILDING_AMPHITHEATER, BUILDING_COLOSSEUM, BUILDING_HIPPODROME,
                 BUILDING_ACTOR_COLONY, BUILDING_GLADIATOR_SCHOOL, BUILDING_LION_HOUSE, BUILDING_CHARIOT_MAKER, 0},
                {BUILDING_FORUM, BUILDING_SENATE_UPGRADED, BUILDING_GOVERNORS_HOUSE, BUILDING_GOVERNORS_VILLA, BUILDING_GOVERNORS_PALACE,
                 BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_ROADBLOCK, BUILDING_TRIUMPHAL_ARCH, 0},
                {BUILDING_GARDENS, BUILDING_PLAZA, BUILDING_ENGINEERS_POST, BUILDING_LOW_BRIDGE, BUILDING_SHIP_BRIDGE, BUILDING_SHIPYARD, BUILDING_DOCK, BUILDING_WHARF, 0},
                {BUILDING_WALL, BUILDING_TOWER,              BUILDING_GATEHOUSE,  BUILDING_PREFECTURE, BUILDING_MENU_FORTS,       BUILDING_MILITARY_ACADEMY,  BUILDING_BARRACKS,      0},
                {BUILDING_MENU_FARMS, BUILDING_MENU_RAW_MATERIALS, BUILDING_MENU_WORKSHOPS, BUILDING_MARKET, BUILDING_GRANARY, BUILDING_WAREHOUSE, 0},
                {BUILDING_WHEAT_FARM, BUILDING_VEGETABLE_FARM, BUILDING_FRUIT_FARM, BUILDING_OLIVE_FARM, BUILDING_VINES_FARM, BUILDING_PIG_FARM, 0},
                {BUILDING_CLAY_PIT, BUILDING_MARBLE_QUARRY, BUILDING_IRON_MINE, BUILDING_TIMBER_YARD, 0},
                {BUILDING_WINE_WORKSHOP, BUILDING_OIL_WORKSHOP, BUILDING_WEAPONS_WORKSHOP, BUILDING_FURNITURE_WORKSHOP, BUILDING_POTTERY_WORKSHOP, 0},
                {BUILDING_MENU_SMALL_TEMPLES, BUILDING_SMALL_TEMPLE_CERES, BUILDING_SMALL_TEMPLE_NEPTUNE, BUILDING_SMALL_TEMPLE_MERCURY, BUILDING_SMALL_TEMPLE_MARS, BUILDING_SMALL_TEMPLE_VENUS, 0},
                {BUILDING_MENU_LARGE_TEMPLES, BUILDING_LARGE_TEMPLE_CERES, BUILDING_LARGE_TEMPLE_NEPTUNE, BUILDING_LARGE_TEMPLE_MERCURY, BUILDING_LARGE_TEMPLE_MARS, BUILDING_LARGE_TEMPLE_VENUS, 0},
                {BUILDING_FORT_LEGIONARIES, BUILDING_FORT_JAVELIN, BUILDING_FORT_MOUNTED, 0},

                {0},
                {0},
                {0},
                {0},
                {0},
        },
        {
                {BUILDING_HOUSE_VACANT_LOT, 0},
                {BUILDING_CLEAR_LAND, 0},
                {BUILDING_ROAD, 0},

                // water crossings
                {BUILDING_LOW_BRIDGE, BUILDING_FERRY, 0},
                // health and sanitation structures
                {BUILDING_WELL, BUILDING_WATER_SUPPLY, BUILDING_DENTIST, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_MORTUARY, 0},
                // religious structures
                {BUILDING_MENU_SHRINES, BUILDING_MENU_TEMPLES, BUILDING_MENU_TEMPLE_COMPLEX, BUILDING_MENU_MONUMENTS, BUILDING_FESTIVAL_SQUARE, 0},
                // education structures
                {BUILDING_SCHOOL, BUILDING_LIBRARY, 0},
                // entertainment structures
                {BUILDING_BOOTH, BUILDING_BANDSTAND, BUILDING_PAVILLION, BUILDING_SENET_HOUSE,
                 BUILDING_JUGGLER_SCHOOL, BUILDING_CONSERVATORY, BUILDING_DANCE_SCHOOL, 0}, //BUILDING_CHARIOT_MAKER
                // municipal structures
                {BUILDING_FIREHOUSE, BUILDING_ENGINEERS_POST, BUILDING_POLICE_STATION, BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE,
                 BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_CITY_PALACE,
                 BUILDING_PERSONAL_MANSION, BUILDING_FAMILY_MANSION, BUILDING_DYNASTY_MANSION,
                 BUILDING_ROADBLOCK, BUILDING_MENU_WATER_CROSSINGS, BUILDING_MENU_BEAUTIFICATION, 0},

                // beautifications
                {BUILDING_GARDENS, BUILDING_PLAZA, BUILDING_SMALL_STATUE,   BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, 0},

                // military structures
                {BUILDING_MENU_DEFENSES, BUILDING_RECRUITER, BUILDING_MENU_FORTS, BUILDING_MILITARY_ACADEMY,
                 BUILDING_WEAPONS_WORKSHOP, BUILDING_CHARIOTS_WORKSHOP, BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF},
                // industry structures
                {BUILDING_MENU_RAW_MATERIALS, BUILDING_JEWELS_WORKSHOP, BUILDING_POTTERY_WORKSHOP, BUILDING_BEER_WORKSHOP, BUILDING_LINEN_WORKSHOP,
                 BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP, BUILDING_LAMP_WORKSHOP, BUILDING_PAINT_WORKSHOP, BUILDING_SHIPYARD, BUILDING_MENU_GUILDS, 0},

                // farms
                {BUILDING_GRAIN_FARM, BUILDING_LETTUCE_FARM, BUILDING_POMEGRANATES_FARM, BUILDING_CHICKPEAS_FARM, BUILDING_FIGS_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_HENNA_FARM, 0},
                // raw materials
                {BUILDING_CLAY_PIT, BUILDING_GEMSTONE_MINE, BUILDING_GOLD_MINE, BUILDING_COPPER_MINE, BUILDING_STONE_QUARRY,
                 BUILDING_LIMESTONE_QUARRY, BUILDING_GRANITE_QUARRY, BUILDING_SANDSTONE_QUARRY, BUILDING_REED_GATHERER, BUILDING_TIMBER_YARD, 0},
                // guilds
                {BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD, BUILDING_STONEMASONS_GUILD, BUILDING_ARTISANS_GUILD},
                // shrines
                {BUILDING_TEMPLE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_TEMPLE_PTAH, BUILDING_TEMPLE_SETH, BUILDING_TEMPLE_BAST, 0},
                {BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_PTAH, BUILDING_TEMPLE_COMPLEX_SETH, BUILDING_TEMPLE_COMPLEX_BAST, 0},
                {BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS, 0},

                // food structures
                {BUILDING_MENU_FARMS, BUILDING_WATER_LIFT, BUILDING_IRRIGATION_DITCH, BUILDING_FISHING_WHARF, BUILDING_HUNTING_LODGE, BUILDING_WORK_CAMP},
                // distribution structures
                {BUILDING_GRANARY, BUILDING_MARKET, BUILDING_WAREHOUSE, BUILDING_DOCK, 0},
                // shrines
                {BUILDING_SHRINE_OSIRIS, BUILDING_SHRINE_RA, BUILDING_SHRINE_PTAH, BUILDING_SHRINE_SETH, BUILDING_SHRINE_BAST, 0},
                // monuments
                {BUILDING_SMALL_ROYAL_TOMB, BUILDING_MEDIUM_ROYAL_TOMB, BUILDING_LARGE_ROYAL_TOMB, BUILDING_GRAND_ROYAL_TOMB,
                 BUILDING_PYRAMID, BUILDING_SPHYNX, BUILDING_MAUSOLEUM, BUILDING_ALEXANDRIA_LIBRARY, BUILDING_CAESAREUM,
                 BUILDING_PHAROS_LIGHTHOUSE, BUILDING_ABU_SIMBEL, 0},
                // defensive structures
                {BUILDING_WALL_PH, BUILDING_TOWER_PH, BUILDING_GATEHOUSE_PH, 0},
        }
};
static int menu_enabled[BUILD_MENU_MAX][BUILD_MENU_ITEM_MAX];

static int changed = 1;

#include "SDL.h"
#include "core/lang.h"
#include "core/game_environment.h"

void building_menu_disable_all() {
    for (int sub = 0; sub < BUILD_MENU_MAX; sub++) {
        for (int item = 0; item < BUILD_MENU_ITEM_MAX; item++) {
            menu_enabled[sub][item] = 0;
        }
    }
}
void building_menu_enable_all(void) {
    for (int sub = 0; sub < BUILD_MENU_MAX; sub++) {
        for (int item = 0; item < BUILD_MENU_ITEM_MAX; item++) {
            menu_enabled[sub][item] = 1;
        }
    }
}

#include "building/industry.h"

int is_building_enabled(int type) {
    for (int sub = 0; sub < BUILD_MENU_MAX; sub++) {
        for (int item = 0; item < BUILD_MENU_ITEM_MAX; item++) {
            if (MENU_int[GAME_ENV][sub][item] == type) // found matching menu item!!!
                return menu_enabled[sub][item];
        }
    }
    return 0;
}

static void enable_building(int type, bool enabled = true) {
    for (int sub = 0; sub < BUILD_MENU_MAX; sub++) {
        for (int item = 0; item < BUILD_MENU_ITEM_MAX; item++) {
            if (MENU_int[GAME_ENV][sub][item] == type) // found matching menu item!!!
                menu_enabled[sub][item] = enabled;
        }
    }
    if (GAME_ENV == ENGINE_ENV_PHARAOH && enabled) {
        if (building_is_farm(type)) {
            enable_building(BUILDING_MENU_FARMS);
//            enable_building(BUILDING_WORK_CAMP);
        }
        if (building_is_extractor(type))
            enable_building(BUILDING_MENU_RAW_MATERIALS);
//        if (building_is_fort(type))
//            enable_building(BUILD_MENU_FORTS);
        if (building_is_defense_ph(type))
            enable_building(BUILDING_MENU_DEFENSES);
        if (building_is_shrine(type))
            enable_building(BUILDING_MENU_SHRINES);
        if (building_is_temple(type))
            enable_building(BUILDING_MENU_SMALL_TEMPLES);
        if (building_is_large_temple(type))
            enable_building(BUILDING_MENU_LARGE_TEMPLES);
        if (building_is_guild(type))
            enable_building(BUILDING_MENU_LARGE_TEMPLES);
        if (building_is_beautification(type))
            enable_building(BUILDING_MENU_BEAUTIFICATION);
        if (building_is_water_crossing(type))
            enable_building(BUILDING_MENU_WATER_CROSSINGS);
//        if (building_is_monument(type))
//            enable_building(BUILDING_MENU_MONUMENTS);
//            enable_building(BUILDING_WORK_CAMP);
    }
}
static void enable_cycling_temples_if_allowed(int type) {
    int sub = (type == BUILDING_MENU_SMALL_TEMPLES) ? BUILD_MENU_SMALL_TEMPLES : BUILD_MENU_LARGE_TEMPLES;
    menu_enabled[sub][0] = 1;
}
static void enable_if_allowed(int type) {
    if (scenario_building_allowed(type)) {
        enable_building(type, true);
        if (type == BUILDING_MENU_SMALL_TEMPLES || type == BUILDING_MENU_LARGE_TEMPLES)
            enable_cycling_temples_if_allowed(type);
    } else
        enable_building(type, false);
}

static int disable_raw_if_unavailable(int type, int resource) {
    if (!empire_can_produce_resource(resource, false)) {
        enable_building(type, false);
        return 0;
    }
    return 1;
}
static int disable_crafted_if_unavailable(int type, int resource, int resource2 = RESOURCE_NONE) {
    if (!empire_can_produce_resource(resource, false)) {
        enable_building(type, false);
        return 0;
    }
    if (resource2 != RESOURCE_NONE && !empire_can_produce_resource(resource2, false)) {
        enable_building(type, false);
        return 0;
    }
    return 1;
}
static void disable_resources() {
    if (GAME_ENV == ENGINE_ENV_C3) {
        int farms = 0;
        farms += disable_raw_if_unavailable(BUILDING_WHEAT_FARM, RESOURCE_WHEAT);
        farms += disable_raw_if_unavailable(BUILDING_VEGETABLE_FARM, RESOURCE_VEGETABLES);
        farms += disable_raw_if_unavailable(BUILDING_FRUIT_FARM, RESOURCE_FRUIT);
        farms += disable_raw_if_unavailable(BUILDING_PIG_FARM, RESOURCE_MEAT_C3);
        farms += disable_raw_if_unavailable(BUILDING_OLIVE_FARM, RESOURCE_OLIVES);
        farms += disable_raw_if_unavailable(BUILDING_VINES_FARM, RESOURCE_VINES);
        farms += disable_raw_if_unavailable(BUILDING_CLAY_PIT, RESOURCE_CLAY);
        farms += disable_raw_if_unavailable(BUILDING_TIMBER_YARD, RESOURCE_TIMBER_C3);
        farms += disable_raw_if_unavailable(BUILDING_IRON_MINE, RESOURCE_IRON);
        farms += disable_raw_if_unavailable(BUILDING_MARBLE_QUARRY, RESOURCE_MARBLE_C3);
//        if (!farms) // todo: monuments
//            enable_building(BUILDING_WORK_CAMP, false);
        disable_crafted_if_unavailable(BUILDING_POTTERY_WORKSHOP, RESOURCE_POTTERY_C3);
        disable_crafted_if_unavailable(BUILDING_FURNITURE_WORKSHOP, RESOURCE_FURNITURE);
        disable_crafted_if_unavailable(BUILDING_OIL_WORKSHOP, RESOURCE_OIL_C3);
        disable_crafted_if_unavailable(BUILDING_WINE_WORKSHOP, RESOURCE_WINE);
        disable_crafted_if_unavailable(BUILDING_WEAPONS_WORKSHOP, RESOURCE_WEAPONS_C3);
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        disable_raw_if_unavailable(BUILDING_BARLEY_FARM, RESOURCE_BARLEY);
        disable_raw_if_unavailable(BUILDING_FLAX_FARM, RESOURCE_FLAX);
        disable_raw_if_unavailable(BUILDING_GRAIN_FARM, RESOURCE_GRAIN);
        disable_raw_if_unavailable(BUILDING_LETTUCE_FARM, RESOURCE_LETTUCE);
        disable_raw_if_unavailable(BUILDING_POMEGRANATES_FARM, RESOURCE_POMEGRANATES);
        disable_raw_if_unavailable(BUILDING_CHICKPEAS_FARM, RESOURCE_CHICKPEAS);
        disable_raw_if_unavailable(BUILDING_FIGS_FARM, RESOURCE_FIGS);
        disable_raw_if_unavailable(BUILDING_HENNA_FARM, RESOURCE_HENNA);
        //
        disable_raw_if_unavailable(BUILDING_HUNTING_LODGE, RESOURCE_GAMEMEAT);
        disable_raw_if_unavailable(BUILDING_FISHING_WHARF, RESOURCE_FISH);
        //
        disable_raw_if_unavailable(BUILDING_CLAY_PIT, RESOURCE_CLAY);
        disable_raw_if_unavailable(BUILDING_TIMBER_YARD, RESOURCE_TIMBER_PH);
        disable_raw_if_unavailable(BUILDING_REED_GATHERER, RESOURCE_REEDS);
        //
        disable_raw_if_unavailable(BUILDING_STONE_QUARRY, RESOURCE_STONE);
        disable_raw_if_unavailable(BUILDING_LIMESTONE_QUARRY, RESOURCE_LIMESTONE);
        disable_raw_if_unavailable(BUILDING_GRANITE_QUARRY, RESOURCE_GRANITE);
//        disable_raw_if_unavailable(BUILDING_UNUSED12, RESOURCE_UNUSED12);
        disable_raw_if_unavailable(BUILDING_SANDSTONE_QUARRY, RESOURCE_SANDSTONE);
//        disable_raw_if_unavailable(BUILDING_MARBLE_QUARRY_PH, RESOURCE_MARBLE_PH);
        disable_raw_if_unavailable(BUILDING_COPPER_MINE, RESOURCE_COPPER);
        disable_raw_if_unavailable(BUILDING_GEMSTONE_MINE, RESOURCE_GEMS);
//        disable_raw_if_unavailable(BUILDING_OIL_WORKSHOP_PH, RESOURCE_OIL_PH);

        disable_crafted_if_unavailable(BUILDING_POTTERY_WORKSHOP, RESOURCE_POTTERY_PH);
        disable_crafted_if_unavailable(BUILDING_BEER_WORKSHOP, RESOURCE_BEER);
        disable_crafted_if_unavailable(BUILDING_JEWELS_WORKSHOP, RESOURCE_LUXURY_GOODS);
        disable_crafted_if_unavailable(BUILDING_LINEN_WORKSHOP, RESOURCE_LINEN);
        disable_crafted_if_unavailable(BUILDING_PAPYRUS_WORKSHOP, RESOURCE_PAPYRUS);
        disable_crafted_if_unavailable(BUILDING_BRICKS_WORKSHOP, RESOURCE_BRICKS, RESOURCE_STRAW);
        disable_crafted_if_unavailable(BUILDING_CATTLE_RANCH, RESOURCE_MEAT_PH, RESOURCE_STRAW);
        disable_crafted_if_unavailable(BUILDING_WEAPONS_WORKSHOP, RESOURCE_WEAPONS_PH);
        disable_crafted_if_unavailable(BUILDING_CHARIOTS_WORKSHOP, RESOURCE_CHARIOTS);
//        disable_crafted_if_unavailable(enabled, type, BUILDING_OIL_WORKSHOP_PH, RESOURCE_OIL_PH);
        disable_crafted_if_unavailable(BUILDING_PAINT_WORKSHOP, RESOURCE_PAINT);
        disable_crafted_if_unavailable(BUILDING_LAMP_WORKSHOP, RESOURCE_LAMPS);
    }
}

#include "scenario/property.h"

enum {
    GOD_OSIRIS = 1,
    GOD_RA = 2,
    GOD_PTAH = 4,
    GOD_SETH = 8,
    GOD_BAST = 16,
};

static void enable_common_beautifications() {
    enable_building(BUILDING_SMALL_STATUE);
    enable_building(BUILDING_MEDIUM_STATUE);
    enable_building(BUILDING_LARGE_STATUE);
    enable_building(BUILDING_GARDENS);
    enable_building(BUILDING_PLAZA);
}
static void enable_common_municipal(int level) {
    enable_common_beautifications();
    enable_building(BUILDING_ROADBLOCK);
    enable_building(BUILDING_FIREHOUSE);
    enable_building(BUILDING_ENGINEERS_POST);
    enable_building(BUILDING_POLICE_STATION);
    if (level >= 3)
        enable_building(BUILDING_CITY_PALACE);
    else if (level >= 2)
        enable_building(BUILDING_TOWN_PALACE);
    else if (level >= 1)
        enable_building(BUILDING_VILLAGE_PALACE);
}
static void enable_common_health() {
    enable_building(BUILDING_WATER_SUPPLY);
    enable_building(BUILDING_APOTHECARY);
    enable_building(BUILDING_PHYSICIAN);
}
static void enable_entertainment(int level) {
    if (level >= 1) {
        enable_building(BUILDING_BOOTH);
        enable_building(BUILDING_JUGGLER_SCHOOL);
    }
    if (level >= 2) {
        enable_building(BUILDING_BANDSTAND);
        enable_building(BUILDING_CONSERVATORY);
    }
    if (level >= 3) {
        enable_building(BUILDING_PAVILLION);
        enable_building(BUILDING_DANCE_SCHOOL);
    }
    if (level >= 4) {
        enable_building(BUILDING_SENET_HOUSE);
    }
}
static void enable_gods(int flag) {
    enable_building(BUILDING_FESTIVAL_SQUARE);
    if (flag & 1) {
        enable_building(BUILDING_TEMPLE_OSIRIS);
        enable_building(BUILDING_SHRINE_OSIRIS);
    }
    if (flag & 2) {
        enable_building(BUILDING_TEMPLE_RA);
        enable_building(BUILDING_SHRINE_RA);
    }
    if (flag & 4) {
        enable_building(BUILDING_TEMPLE_PTAH);
        enable_building(BUILDING_SHRINE_PTAH);
    }
    if (flag & 8) {
        enable_building(BUILDING_TEMPLE_SETH);
        enable_building(BUILDING_SHRINE_SETH);
    }
    if (flag & 16) {
        enable_building(BUILDING_TEMPLE_BAST);
        enable_building(BUILDING_SHRINE_BAST);
    }
}

void building_menu_update(int build_set) {
    // do this if loading normally from a save - tutorial stage will
    // be determined accordingly by the set flags!
    if (build_set == BUILDSET_NORMAL) {
        for (int i = 1; i <= 10; i++)
            if (scenario_is_tutorial(i))
                return tutorial_menu_update(i);
    }

    switch (build_set) {
        case BUILDSET_TUT1_START:
            building_menu_disable_all();
            break;
        case BUILDSET_TUT1_FIRE_C3:
            enable_building(BUILDING_PREFECTURE);
            enable_building(BUILDING_MARKET);
            break;
        case BUILDSET_TUT1_FIRE_PH:
            enable_building(BUILDING_FIREHOUSE);
            break;
        case BUILDSET_TUT1_FOOD:
            enable_building(BUILDING_HUNTING_LODGE);
            enable_building(BUILDING_GRANARY);
            enable_building(BUILDING_MARKET);
            break;
        case BUILDSET_TUT1_WATER:
            enable_building(BUILDING_WATER_SUPPLY);
            break;
        case BUILDSET_TUT1_COLLAPSE_C3:
            enable_building(BUILDING_ENGINEERS_POST);
            enable_building(BUILDING_SENATE_UPGRADED);
            enable_building(BUILDING_ROADBLOCK);
            break;
        case BUILDSET_TUT1_COLLAPSE_PH:
            enable_building(BUILDING_ENGINEERS_POST);
            break;
        case BUILDSET_TUT2_START:
            building_menu_disable_all();
            if (GAME_ENV == ENGINE_ENV_C3) {
                enable_building(BUILDING_PREFECTURE);
                enable_building(BUILDING_ENGINEERS_POST);
                enable_building(BUILDING_SENATE_UPGRADED);
                enable_building(BUILDING_ROADBLOCK);
                enable_building(BUILDING_MARKET);
                enable_building(BUILDING_GRANARY);
                enable_building(BUILDING_MENU_FARMS);
                enable_building(BUILDING_MENU_SMALL_TEMPLES);
            } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
                enable_building(BUILDING_FIREHOUSE);
                enable_building(BUILDING_ENGINEERS_POST);
                enable_building(BUILDING_POLICE_STATION);
                enable_building(BUILDING_MARKET);
                enable_building(BUILDING_GRANARY);
                enable_building(BUILDING_HUNTING_LODGE);
                enable_building(BUILDING_WATER_SUPPLY);
                enable_building(BUILDING_GOLD_MINE);
                enable_building(BUILDING_VILLAGE_PALACE);
            }
            break;
        case BUILDSET_TUT2_GODS:
            enable_gods(GOD_BAST);
            break;
        case BUILDSET_TUT2_ENTERTAINMENT:
            enable_building(BUILDING_BOOTH);
            enable_building(BUILDING_JUGGLER_SCHOOL);
            break;
        case BUILDSET_TUT2_UP_TO_250:
            enable_building(BUILDING_DRAGGABLE_RESERVOIR);
            enable_building(BUILDING_AQUEDUCT);
            enable_building(BUILDING_FOUNTAIN);
            break;
        case BUILDSET_TUT2_UP_TO_450:
            enable_building(BUILDING_GARDENS);
            enable_building(BUILDING_ACTOR_COLONY);
            enable_building(BUILDING_THEATER);
            enable_building(BUILDING_BATHHOUSE);
            enable_building(BUILDING_SCHOOL);
            break;
        case BUILDSET_TUT2_AFTER_450:
            enable_building(BUILDING_MENU_RAW_MATERIALS);
            enable_building(BUILDING_MENU_WORKSHOPS);
            enable_building(BUILDING_WAREHOUSE);
            enable_building(BUILDING_FORUM);
            enable_building(BUILDING_BOOTH);
            enable_building(BUILDING_JUGGLER_SCHOOL);
            break;
        case BUILDSET_TUT3_START:
            building_menu_disable_all();
            enable_building(BUILDING_FIREHOUSE);
            enable_building(BUILDING_ENGINEERS_POST);
            enable_building(BUILDING_POLICE_STATION);
            enable_building(BUILDING_VILLAGE_PALACE);
            enable_building(BUILDING_WATER_SUPPLY);
            enable_building(BUILDING_FIGS_FARM);
            enable_building(BUILDING_WORK_CAMP);
            enable_building(BUILDING_BOOTH);
            enable_building(BUILDING_JUGGLER_SCHOOL);
            enable_building(BUILDING_MARKET);
            enable_building(BUILDING_GRANARY);
            enable_gods(GOD_OSIRIS);
            break;
        case BUILDSET_TUT3_INDUSTRY:
            enable_building(BUILDING_CLAY_PIT);
            enable_building(BUILDING_POTTERY_WORKSHOP);
            enable_building(BUILDING_WAREHOUSE);
            break;
        case BUILDSET_TUT3_GARDENS:
            enable_building(BUILDING_ROADBLOCK);
            enable_building(BUILDING_FERRY);
            enable_common_beautifications();
            break;
        case BUILDSET_TUT3_HEALTH:
            enable_common_health();
            break;
        case BUILDSET_TUT4_START:
            building_menu_disable_all();
            enable_common_municipal(1);
            enable_common_health();
            enable_building(BUILDING_GRAIN_FARM);
            enable_building(BUILDING_BARLEY_FARM);
            enable_building(BUILDING_WORK_CAMP);
            enable_entertainment(2);
            enable_building(BUILDING_MARKET);
            enable_building(BUILDING_GRANARY);
            building_menu_update(BUILDSET_TUT3_INDUSTRY);
            enable_building(BUILDING_LOW_BRIDGE);
            enable_gods(GOD_OSIRIS + GOD_RA + GOD_BAST);
            enable_building(BUILDING_BEER_WORKSHOP);
            break;
        case BUILDSET_TUT4_FINANCE:
            enable_building(BUILDING_TAX_COLLECTOR);
            enable_building(BUILDING_PERSONAL_MANSION);
            break;
        case BUILDSET_TUT5_START:
            building_menu_disable_all();
            enable_common_municipal(1);
            enable_building(BUILDING_TAX_COLLECTOR);
            enable_building(BUILDING_COURTHOUSE);
            enable_building(BUILDING_PERSONAL_MANSION);
            enable_common_health();
            enable_entertainment(2);
            enable_gods(GOD_OSIRIS + GOD_RA + GOD_BAST);

            enable_building(BUILDING_CLAY_PIT);
            enable_building(BUILDING_POTTERY_WORKSHOP);
            enable_building(BUILDING_BEER_WORKSHOP);

            enable_building(BUILDING_MARKET);
            enable_building(BUILDING_GRANARY);
            enable_building(BUILDING_WAREHOUSE);

            enable_building(BUILDING_CHICKPEAS_FARM);
            enable_building(BUILDING_BARLEY_FARM);
            enable_building(BUILDING_WORK_CAMP);
            break;
        case BUILDSET_TUT5_EDUCATION:
            enable_building(BUILDING_REED_GATHERER);
            enable_building(BUILDING_PAPYRUS_WORKSHOP);
            enable_building(BUILDING_SCHOOL);
            break;
        case BUILDSET_TUT5_TRADING:
            // TODO: enable trading
            enable_building(BUILDING_DOCK);
            break;
        case BUILDSET_TUT5_MONUMENTS:
            enable_building(BUILDING_BRICKLAYERS_GUILD);
//            enable_monument(MONUMENT_SMALL_MASTABA); // todo!!!!!!
            break;
        case BUILDSET_TUT6_START:
            building_menu_disable_all();
            // todo
            break;
        case BUILDSET_TUT7_START:
            building_menu_disable_all();
            for (int i = 0; i < int_MAX; i++)
                enable_if_allowed(i);
            // todo
            break;
        case BUILDSET_TUT8_START:
            building_menu_disable_all();
            for (int i = 0; i < int_MAX; i++)
                enable_if_allowed(i);
            // todo
            break;
        default:
            for (int i = 0; i < int_MAX; i++)
                enable_if_allowed(i);

            // enable monuments!!!
//            enable_available_monuments(); // todo!!!!!!

            // disable resources that aren't available on map
            disable_resources();
            break;
    }

    // disable government building tiers depending on mission rank
    int rank = scenario_property_player_rank();
    if (rank < 6) {
        //
        enable_building(BUILDING_TOWN_PALACE, false);
        enable_building(BUILDING_CITY_PALACE, false);
        //
        enable_building(BUILDING_FAMILY_MANSION, false);
        enable_building(BUILDING_DYNASTY_MANSION, false);
    } else if (rank < 8) {
        enable_building(BUILDING_VILLAGE_PALACE, false);
        //
        enable_building(BUILDING_CITY_PALACE, false);
        enable_building(BUILDING_FAMILY_MANSION, false);
        //
        enable_building(BUILDING_DYNASTY_MANSION, false);

    } else {
        enable_building(BUILDING_VILLAGE_PALACE, false);
        enable_building(BUILDING_TOWN_PALACE, false);
        //
        enable_building(BUILDING_PERSONAL_MANSION, false);
        enable_building(BUILDING_FAMILY_MANSION, false);
        //
    }

    // these are always enabled
    enable_building(BUILDING_HOUSE_VACANT_LOT);
    enable_building(BUILDING_CLEAR_LAND);
    enable_building(BUILDING_ROAD);
    enable_building(BUILDING_WELL);

    changed = 1;
}
int building_menu_count_items(int submenu) {
    int count = 0;
    for (int item = 0; item < BUILD_MENU_ITEM_MAX; item++) {
        if (menu_enabled[submenu][item] && MENU_int[GAME_ENV][submenu][item] > 0)
            count++;
    }
    return count;
}
int building_menu_next_index(int submenu, int current_index) {
    for (int i = current_index + 1; i < BUILD_MENU_ITEM_MAX; i++) {
        if (MENU_int[GAME_ENV][submenu][i] <= 0)
            return 0;

        if (menu_enabled[submenu][i])
            return i;

    }
    return 0;
}
int building_menu_type(int submenu, int item) {
    return MENU_int[GAME_ENV][submenu][item];
}

int building_menu_has_changed(void) {
    if (changed) {
        changed = 0;
        return 1;
    }
    return 0;
}

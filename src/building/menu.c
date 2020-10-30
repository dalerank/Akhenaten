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
                {BUILDING_BARBER, BUILDING_BATHHOUSE,    BUILDING_DOCTOR,  BUILDING_HOSPITAL,   0},
                {BUILDING_MENU_SMALL_TEMPLES, BUILDING_MENU_LARGE_TEMPLES, BUILDING_ORACLE,              0},
                {BUILDING_SCHOOL, BUILDING_ACADEMY, BUILDING_LIBRARY, BUILDING_MISSION_POST, 0},
                {BUILDING_THEATER, BUILDING_AMPHITHEATER, BUILDING_COLOSSEUM, BUILDING_HIPPODROME,
                        BUILDING_GLADIATOR_SCHOOL, BUILDING_LION_HOUSE, BUILDING_ACTOR_COLONY, BUILDING_CHARIOT_MAKER, 0},
                {BUILDING_FORUM,     BUILDING_SENATE_UPGRADED, BUILDING_GOVERNORS_HOUSE, BUILDING_GOVERNORS_VILLA, BUILDING_GOVERNORS_PALACE,
                                                                                                                                        BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE,    BUILDING_LARGE_STATUE,   BUILDING_ROADBLOCK,          BUILDING_TRIUMPHAL_ARCH, 0},
                {BUILDING_GARDENS, BUILDING_PLAZA, BUILDING_ENGINEERS_POST, BUILDING_LOW_BRIDGE,    BUILDING_SHIP_BRIDGE,
                                                                                                                           BUILDING_SHIPYARD, BUILDING_DOCK, BUILDING_WHARF, 0},
                {BUILDING_WALL,          BUILDING_TOWER,     BUILDING_GATEHOUSE, BUILDING_PREFECTURE,
                        BUILDING_FORT,             BUILDING_MILITARY_ACADEMY,  BUILDING_BARRACKS,      0},
                {BUILDING_MENU_FARMS, BUILDING_MENU_RAW_MATERIALS, BUILDING_MENU_WORKSHOPS,
                                                                                           BUILDING_MARKET,         BUILDING_GRANARY,         BUILDING_WAREHOUSE,        0},
                {BUILDING_WHEAT_FARM,  BUILDING_VEGETABLE_FARM, BUILDING_FRUIT_FARM, BUILDING_OLIVE_FARM,   BUILDING_VINES_FARM,        BUILDING_PIG_FARM,       0},
                {BUILDING_CLAY_PIT, BUILDING_MARBLE_QUARRY, BUILDING_IRON_MINE, BUILDING_TIMBER_YARD, 0},
                {BUILDING_WINE_WORKSHOP,    BUILDING_OIL_WORKSHOP,      BUILDING_WEAPONS_WORKSHOP,  BUILDING_FURNITURE_WORKSHOP, BUILDING_POTTERY_WORKSHOP, 0},
                {BUILDING_MENU_SMALL_TEMPLES, BUILDING_SMALL_TEMPLE_CERES, BUILDING_SMALL_TEMPLE_NEPTUNE, BUILDING_SMALL_TEMPLE_MERCURY, BUILDING_SMALL_TEMPLE_MARS, BUILDING_SMALL_TEMPLE_VENUS, 0},
                {BUILDING_MENU_LARGE_TEMPLES,    BUILDING_LARGE_TEMPLE_CERES, BUILDING_LARGE_TEMPLE_NEPTUNE, BUILDING_LARGE_TEMPLE_MERCURY, BUILDING_LARGE_TEMPLE_MARS,   BUILDING_LARGE_TEMPLE_VENUS, 0},
                {BUILDING_FORT_LEGIONARIES, BUILDING_FORT_JAVELIN,  BUILDING_FORT_MOUNTED,     0},

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
                {BUILDING_LOW_BRIDGE,          BUILDING_FERRY,    0},
                // health and sanitation structures
                {BUILDING_WELL,   BUILDING_WATER_SUPPLY, BUILDING_DENTIST, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_MORTUARY, 0},
                // religious structures
                {BUILDING_MENU_SHRINES,       BUILDING_MENU_TEMPLES,       BUILDING_MENU_TEMPLE_COMPLEX, BUILDING_MENU_MONUMENTS, BUILDING_FESTIVAL_SQUARE, 0},
                // education structures
                {BUILDING_SCHOOL, BUILDING_LIBRARY, 0},
                // entertainment structures
                {BUILDING_THEATER, BUILDING_AMPHITHEATER, BUILDING_COLOSSEUM, BUILDING_HIPPODROME,
                        BUILDING_GLADIATOR_SCHOOL, BUILDING_LION_HOUSE, BUILDING_ACTOR_COLONY, BUILDING_CHARIOT_MAKER, 0},
                // municipal structures
                {BUILDING_FIREHOUSE, BUILDING_ENGINEERS_POST,  BUILDING_POLICE_STATION,  BUILDING_TAX_COLLECTOR,   BUILDING_COURTHOUSE, BUILDING_VILLAGE_PALACE,
                                                                                                                                                               BUILDING_PERSONAL_MANSION, BUILDING_FAMILY_MANSION, BUILDING_FAMILY_BEEG_PALACE, BUILDING_ROADBLOCK,
                                                                                                                                                                                                                                                                         BUILDING_MENU_WATER_CROSSINGS, BUILDING_MENU_BEAUTIFICATION, 0},
                // beautifications
                {BUILDING_GARDENS, BUILDING_PLAZA, BUILDING_SMALL_STATUE,   BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, 0},

                // military structures
                {BUILDING_MENU_DEFENCES, BUILDING_RECRUITER, BUILDING_FORT,      BUILDING_MILITARY_ACADEMY,
                        BUILDING_WEAPONS_WORKSHOP, BUILDING_CHARIOTS_WORKSHOP, BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF},
                // industry structures
                {BUILDING_MENU_RAW_MATERIALS,
                                      BUILDING_POTTERY_WORKSHOP,   BUILDING_BEER_WORKSHOP, BUILDING_LINEN_WORKSHOP, BUILDING_JEWELS_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP, BUILDING_LAMP_WORKSHOP, BUILDING_PAINT_WORKSHOP,
                        BUILDING_SHIPYARD, BUILDING_MENU_GUILDS, 0},

                // farms
                {BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM,      BUILDING_GRAIN_FARM, BUILDING_LETTUCE_FARM, BUILDING_POMEGRANATES_FARM, BUILDING_CHICKPEAS_FARM, 0},
                // raw materials
                {BUILDING_CLAY_PIT,
                                    BUILDING_GEMSTONE_MINE, BUILDING_GOLD_MINE, BUILDING_COPPER_MINE,
                                                                                                      BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_GRANITE_QUARRY, BUILDING_SANDSTONE_QUARRY,
                        BUILDING_REED_GATHERER, BUILDING_TIMBER_YARD, 0},
                // guilds
                {BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD, BUILDING_STONEMASONS_GUILD, BUILDING_ARTISANS_GUILD},
                // shrines
                {BUILDING_TEMPLE_OSIRIS,      BUILDING_TEMPLE_RA,          BUILDING_TEMPLE_PTAH,          BUILDING_TEMPLE_SETH,          BUILDING_TEMPLE_BAST,       0},
                {BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_RA,  BUILDING_TEMPLE_COMPLEX_PTAH,  BUILDING_TEMPLE_COMPLEX_SETH,  BUILDING_TEMPLE_COMPLEX_BAST, 0},
                {BUILDING_FORT_ARCHERS,     BUILDING_FORT_INFANTRY, BUILDING_FORT_CHARIOTEERS, 0},

                // food structures
                {BUILDING_MENU_FARMS, BUILDING_WATER_LIFT, BUILDING_IRRIGATION_DITCH, BUILDING_FISHING_WHARF, BUILDING_HUNTING_LODGE, BUILDING_WORK_CAMP},
                // distribution structures
                {BUILDING_GRANARY, BUILDING_MARKET, BUILDING_WAREHOUSE, BUILDING_DOCK, 0},
                // shrines
                {BUILDING_SHRINE_OSIRIS, BUILDING_SHRINE_RA, BUILDING_SHRINE_PTAH, BUILDING_SHRINE_SETH, BUILDING_SHRINE_BAST, 0},
                // monuments
                {0},
                // defensive structures
                {BUILDING_WALL_PH, BUILDING_TOWER_PH, BUILDING_GATEHOUSE_PH, 0},
        }
};
static int menu_enabled[BUILD_MENU_MAX][BUILD_MENU_ITEM_MAX];

static int changed = 1;

#include "SDL.h"
#include "core/lang.h"
#include "core/game_environment.h"

void building_menu_enable_all(void) {
    for (int sub = 0; sub < BUILD_MENU_MAX; sub++) {
        for (int item = 0; item < BUILD_MENU_ITEM_MAX; item++) {
            menu_enabled[sub][item] = 1;
        }
    }
//    for (int i = 0; i < 400; i++) {
//        auto s = lang_get_string(28, i);
//        SDL_Log("%i : %s", i, s);
//    }
}

static void enable_cycling_temples_if_allowed(int type) {
    int sub = (type == BUILDING_MENU_SMALL_TEMPLES) ? BUILD_MENU_SMALL_TEMPLES : BUILD_MENU_LARGE_TEMPLES;
    menu_enabled[sub][0] = 1;
}
static void enable_if_allowed(int *enabled, int menu_int, int type) {
    if (menu_int == type && scenario_building_allowed(type)) {
        *enabled = 1;
        if (type == BUILDING_MENU_SMALL_TEMPLES || type == BUILDING_MENU_LARGE_TEMPLES)
            enable_cycling_temples_if_allowed(type);
    }
}

static void disable_raw(int *enabled, int menu_int, int type, int resource) {
    if (type == menu_int && !empire_can_produce_resource(resource))
        *enabled = 0;
}
static void disable_crafted(int *enabled, int menu_int, int type, int resource) {
    if (type == menu_int && !empire_can_produce_resource_potentially(resource))
        *enabled = 0;
}
static void enable_normal(int *enabled, int type) {
    if (GAME_ENV == ENGINE_ENV_PHARAOH) {
//        int max = env_sizes().MAX_ALLOWED_BUILDINGS;
        for (int i = 0; i < 236; i++)
            enable_if_allowed(enabled, type, i);
        return;
//        return building_menu_enable_all();
    }
    enable_if_allowed(enabled, type, BUILDING_ROAD);
    enable_if_allowed(enabled, type, BUILDING_DRAGGABLE_RESERVOIR);
    enable_if_allowed(enabled, type, BUILDING_AQUEDUCT);
    enable_if_allowed(enabled, type, BUILDING_FOUNTAIN);
    enable_if_allowed(enabled, type, BUILDING_WELL);
    enable_if_allowed(enabled, type, BUILDING_BARBER);
    enable_if_allowed(enabled, type, BUILDING_BATHHOUSE);
    enable_if_allowed(enabled, type, BUILDING_DOCTOR);
    enable_if_allowed(enabled, type, BUILDING_HOSPITAL);
    enable_if_allowed(enabled, type, BUILDING_MENU_SMALL_TEMPLES);
    enable_if_allowed(enabled, type, BUILDING_MENU_LARGE_TEMPLES);
    enable_if_allowed(enabled, type, BUILDING_ORACLE);
    enable_if_allowed(enabled, type, BUILDING_SCHOOL);
    enable_if_allowed(enabled, type, BUILDING_ACADEMY);
    enable_if_allowed(enabled, type, BUILDING_LIBRARY);
    enable_if_allowed(enabled, type, BUILDING_THEATER);
    enable_if_allowed(enabled, type, BUILDING_AMPHITHEATER);
    enable_if_allowed(enabled, type, BUILDING_COLOSSEUM);
    enable_if_allowed(enabled, type, BUILDING_HIPPODROME);
    enable_if_allowed(enabled, type, BUILDING_GLADIATOR_SCHOOL);
    enable_if_allowed(enabled, type, BUILDING_LION_HOUSE);
    enable_if_allowed(enabled, type, BUILDING_ACTOR_COLONY);
    enable_if_allowed(enabled, type, BUILDING_CHARIOT_MAKER);
    enable_if_allowed(enabled, type, BUILDING_FORUM);
    enable_if_allowed(enabled, type, BUILDING_SENATE_UPGRADED);
    enable_if_allowed(enabled, type, BUILDING_GOVERNORS_HOUSE);
    enable_if_allowed(enabled, type, BUILDING_GOVERNORS_VILLA);
    enable_if_allowed(enabled, type, BUILDING_GOVERNORS_PALACE);
    enable_if_allowed(enabled, type, BUILDING_SMALL_STATUE);
    enable_if_allowed(enabled, type, BUILDING_MEDIUM_STATUE);
    enable_if_allowed(enabled, type, BUILDING_LARGE_STATUE);
    enable_if_allowed(enabled, type, BUILDING_GARDENS);
    enable_if_allowed(enabled, type, BUILDING_PLAZA);
    enable_if_allowed(enabled, type, BUILDING_ENGINEERS_POST);
    enable_if_allowed(enabled, type, BUILDING_MISSION_POST);
    enable_if_allowed(enabled, type, BUILDING_SHIPYARD);
    enable_if_allowed(enabled, type, BUILDING_WHARF);
    enable_if_allowed(enabled, type, BUILDING_DOCK);
    enable_if_allowed(enabled, type, BUILDING_WALL);
    enable_if_allowed(enabled, type, BUILDING_TOWER);
    enable_if_allowed(enabled, type, BUILDING_GATEHOUSE);
    enable_if_allowed(enabled, type, BUILDING_PREFECTURE);
    enable_if_allowed(enabled, type, BUILDING_FORT);
    enable_if_allowed(enabled, type, BUILDING_MILITARY_ACADEMY);
    enable_if_allowed(enabled, type, BUILDING_BARRACKS);
    enable_if_allowed(enabled, type, BUILDING_DISTRIBUTION_CENTER_UNUSED);
    enable_if_allowed(enabled, type, BUILDING_MENU_FARMS);
    enable_if_allowed(enabled, type, BUILDING_MENU_RAW_MATERIALS);
    enable_if_allowed(enabled, type, BUILDING_MENU_WORKSHOPS);
    enable_if_allowed(enabled, type, BUILDING_MARKET);
    enable_if_allowed(enabled, type, BUILDING_GRANARY);
    enable_if_allowed(enabled, type, BUILDING_WAREHOUSE);
    enable_if_allowed(enabled, type, BUILDING_LOW_BRIDGE);
    enable_if_allowed(enabled, type, BUILDING_SHIP_BRIDGE);
    if (type == BUILDING_TRIUMPHAL_ARCH) {
        if (city_buildings_triumphal_arch_available())
            *enabled = 1;
    }
    enable_if_allowed(enabled, type, BUILDING_ROADBLOCK);
}

static void enable_tutorial1_start(int *enabled, int type) {
    enable_if_allowed(enabled, type, BUILDING_WELL);
    enable_if_allowed(enabled, type, BUILDING_ROAD);
}
static void enable_tutorial1_after_fire(int *enabled, int type) {
    enable_tutorial1_start(enabled, type);
    enable_if_allowed(enabled, type, BUILDING_PREFECTURE);
    enable_if_allowed(enabled, type, BUILDING_MARKET);
}
static void enable_tutorial1_after_collapse(int *enabled, int type) {
    enable_tutorial1_after_fire(enabled, type);
    enable_if_allowed(enabled, type, BUILDING_ENGINEERS_POST);
    enable_if_allowed(enabled, type, BUILDING_SENATE_UPGRADED);
    enable_if_allowed(enabled, type, BUILDING_ROADBLOCK);
}
static void enable_tutorial2_start(int *enabled, int type) {
    enable_if_allowed(enabled, type, BUILDING_WELL);
    enable_if_allowed(enabled, type, BUILDING_ROAD);
    enable_if_allowed(enabled, type, BUILDING_PREFECTURE);
    enable_if_allowed(enabled, type, BUILDING_ENGINEERS_POST);
    enable_if_allowed(enabled, type, BUILDING_SENATE_UPGRADED);
    enable_if_allowed(enabled, type, BUILDING_ROADBLOCK);
    enable_if_allowed(enabled, type, BUILDING_MARKET);
    enable_if_allowed(enabled, type, BUILDING_GRANARY);
    enable_if_allowed(enabled, type, BUILDING_MENU_FARMS);
    enable_if_allowed(enabled, type, BUILDING_MENU_SMALL_TEMPLES);
}
static void enable_tutorial2_up_to_250(int *enabled, int type) {
    enable_tutorial2_start(enabled, type);
    enable_if_allowed(enabled, type, BUILDING_DRAGGABLE_RESERVOIR);
    enable_if_allowed(enabled, type, BUILDING_AQUEDUCT);
    enable_if_allowed(enabled, type, BUILDING_FOUNTAIN);
}
static void enable_tutorial2_up_to_450(int *enabled, int type) {
    enable_tutorial2_up_to_250(enabled, type);
    enable_if_allowed(enabled, type, BUILDING_GARDENS);
    enable_if_allowed(enabled, type, BUILDING_ACTOR_COLONY);
    enable_if_allowed(enabled, type, BUILDING_THEATER);
    enable_if_allowed(enabled, type, BUILDING_BATHHOUSE);
    enable_if_allowed(enabled, type, BUILDING_SCHOOL);
}
static void enable_tutorial2_after_450(int *enabled, int type) {
    enable_tutorial2_up_to_450(enabled, type);
    enable_if_allowed(enabled, type, BUILDING_MENU_RAW_MATERIALS);
    enable_if_allowed(enabled, type, BUILDING_MENU_WORKSHOPS);
    enable_if_allowed(enabled, type, BUILDING_WAREHOUSE);
    enable_if_allowed(enabled, type, BUILDING_FORUM);
    enable_if_allowed(enabled, type, BUILDING_AMPHITHEATER);
    enable_if_allowed(enabled, type, BUILDING_GLADIATOR_SCHOOL);
}

static void disable_resources(int *enabled, int type) {
    if (GAME_ENV == ENGINE_ENV_C3) {
        disable_raw(enabled, type, BUILDING_WHEAT_FARM, RESOURCE_WHEAT);
        disable_raw(enabled, type, BUILDING_VEGETABLE_FARM, RESOURCE_VEGETABLES);
        disable_raw(enabled, type, BUILDING_FRUIT_FARM, RESOURCE_FRUIT);
        disable_raw(enabled, type, BUILDING_PIG_FARM, RESOURCE_MEAT_C3);
        disable_raw(enabled, type, BUILDING_OLIVE_FARM, RESOURCE_OLIVES);
        disable_raw(enabled, type, BUILDING_VINES_FARM, RESOURCE_VINES);
        disable_raw(enabled, type, BUILDING_CLAY_PIT, RESOURCE_CLAY_C3);
        disable_raw(enabled, type, BUILDING_TIMBER_YARD, RESOURCE_TIMBER_C3);
        disable_raw(enabled, type, BUILDING_IRON_MINE, RESOURCE_IRON);
        disable_raw(enabled, type, BUILDING_MARBLE_QUARRY, RESOURCE_MARBLE_C3);
        disable_crafted(enabled, type, BUILDING_POTTERY_WORKSHOP, RESOURCE_POTTERY_C3);
        disable_crafted(enabled, type, BUILDING_FURNITURE_WORKSHOP, RESOURCE_FURNITURE);
        disable_crafted(enabled, type, BUILDING_OIL_WORKSHOP, RESOURCE_OIL_C3);
        disable_crafted(enabled, type, BUILDING_WINE_WORKSHOP, RESOURCE_WINE);
        disable_crafted(enabled, type, BUILDING_WEAPONS_WORKSHOP, RESOURCE_WEAPONS_C3);
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        disable_raw(enabled, type, BUILDING_BARLEY_FARM, RESOURCE_BARLEY);
        disable_raw(enabled, type, BUILDING_FLAX_FARM, RESOURCE_FLAX);
        disable_raw(enabled, type, BUILDING_GRAIN_FARM, RESOURCE_GRAIN);
        disable_raw(enabled, type, BUILDING_LETTUCE_FARM, RESOURCE_LETTUCE);
        disable_raw(enabled, type, BUILDING_POMEGRANATES_FARM, RESOURCE_POMEGRANATES);
        disable_raw(enabled, type, BUILDING_CHICKPEAS_FARM, RESOURCE_CHICKPEAS);
        disable_raw(enabled, type, BUILDING_FIGS_FARM, RESOURCE_FIGS);
        disable_raw(enabled, type, BUILDING_HENNA_FARM, RESOURCE_HENNA);
        //
        disable_raw(enabled, type, BUILDING_HUNTING_LODGE, RESOURCE_GAMEMEAT);
        //
        disable_raw(enabled, type, BUILDING_CLAY_PIT, RESOURCE_CLAY_PH);
        disable_raw(enabled, type, BUILDING_TIMBER_YARD, RESOURCE_TIMBER_PH);
        disable_raw(enabled, type, BUILDING_REED_GATHERER, RESOURCE_REEDS);
        //
        disable_raw(enabled, type, BUILDING_STONE_QUARRY, RESOURCE_STONE);
        disable_raw(enabled, type, BUILDING_LIMESTONE_QUARRY, RESOURCE_LIMESTONE);
        disable_raw(enabled, type, BUILDING_GRANITE_QUARRY, RESOURCE_GRANITE);
//        disable_raw(enabled, type, BUILDING_UNUSED12, RESOURCE_UNUSED12);
        disable_raw(enabled, type, BUILDING_SANDSTONE_QUARRY, RESOURCE_SANDSTONE);
//        disable_raw(enabled, type, BUILDING_MARBLE_QUARRY_PH, RESOURCE_MARBLE_PH);
        disable_raw(enabled, type, BUILDING_COPPER_MINE, RESOURCE_COPPER);
        disable_raw(enabled, type, BUILDING_GEMSTONE_MINE, RESOURCE_GEMS);

        disable_crafted(enabled, type, BUILDING_POTTERY_WORKSHOP, RESOURCE_POTTERY_PH);
        disable_crafted(enabled, type, BUILDING_JEWELS_WORKSHOP, RESOURCE_LUXURY_GOODS);
        disable_crafted(enabled, type, BUILDING_LINEN_WORKSHOP, RESOURCE_LINEN);
        disable_crafted(enabled, type, BUILDING_BEER_WORKSHOP, RESOURCE_BEER);
        disable_crafted(enabled, type, BUILDING_PAPYRUS_WORKSHOP, RESOURCE_PAPYRUS);
        disable_crafted(enabled, type, BUILDING_BRICKS_WORKSHOP, RESOURCE_BRICKS);
        disable_crafted(enabled, type, BUILDING_CATTLE_RANCH, RESOURCE_MEAT_PH);
        disable_crafted(enabled, type, BUILDING_WEAPONS_WORKSHOP, RESOURCE_WEAPONS_PH);
        disable_crafted(enabled, type, BUILDING_CHARIOTS_WORKSHOP, RESOURCE_CHARIOTS);
//        disable_crafted(enabled, type, BUILDING_OIL_WORKSHOP_PH, RESOURCE_OIL_PH);
        disable_crafted(enabled, type, BUILDING_PAINT_WORKSHOP, RESOURCE_PAINT);
        disable_crafted(enabled, type, BUILDING_LAMP_WORKSHOP, RESOURCE_LAMPS);
    }
}

void building_menu_update(void) {
    tutorial_build_buttons tutorial_buttons = tutorial_get_build_buttons();
    for (int sub = 0; sub < BUILD_MENU_MAX; sub++) {
        for (int item = 0; item < BUILD_MENU_ITEM_MAX; item++) {
            int building_type = MENU_int[GAME_ENV][sub][item]; // cycle through each building, determine if it's allowed...
            int *menu_item = &menu_enabled[sub][item];
            // first 12 items always disabled
            if (sub < 12)
                *menu_item = 0;
            else
                *menu_item = 1;

            if (building_type >= BUILDING_HOUSE_VACANT_LOT && building_type <= BUILDING_HOUSE_LUXURY_PALACE)
                *menu_item = 1;
            if (building_type == BUILDING_CLEAR_LAND)
                *menu_item = 1;
            if (building_type == BUILDING_ROAD)
                *menu_item = 1;

            enable_normal(menu_item, building_type); // first, enabled as normal

            switch (tutorial_buttons) {
                case TUT1_BUILD_START:
                    enable_tutorial1_start(menu_item, building_type);
                    break;
                case TUT1_BUILD_AFTER_FIRE:
                    enable_tutorial1_after_fire(menu_item, building_type);
                    break;
                case TUT1_BUILD_AFTER_COLLAPSE:
                    enable_tutorial1_after_collapse(menu_item, building_type);
                    break;
                case TUT2_BUILD_START:
                    enable_tutorial2_start(menu_item, building_type);
                    break;
                case TUT2_BUILD_UP_TO_250:
                    enable_tutorial2_up_to_250(menu_item, building_type);
                    break;
                case TUT2_BUILD_UP_TO_450:
                    enable_tutorial2_up_to_450(menu_item, building_type);
                    break;
                case TUT2_BUILD_AFTER_450:
                    enable_tutorial2_after_450(menu_item, building_type);
                    break;
//                default:
//                    enable_normal(menu_item, building_type);
//                    break;
            }
            disable_resources(menu_item, building_type);
        }
    }

//    building_menu_enable_all(); // temp

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

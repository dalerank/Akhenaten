#include "menu.h"

#include "city/buildings.h"
#include "empire/city.h"
#include "game/tutorial.h"
#include "config/config.h"
#include "scenario/building.h"
#include "scenario/property.h"

#define BUILD_MENU_ITEM_MAX 30

static const int MENU_int[][BUILD_MENU_MAX][BUILD_MENU_ITEM_MAX] = {
  {
    {BUILDING_HOUSE_VACANT_LOT, 0},
    {BUILDING_CLEAR_LAND, 0},
    {BUILDING_ROAD, 0},
    {BUILDING_WATER_LIFT, BUILDING_IRRIGATION_DITCH, BUILDING_MENU_BEAUTIFICATION, BUILDING_WELL, 0},
    {BUILDING_DENTIST, BUILDING_MENU_MONUMENTS, BUILDING_APOTHECARY, BUILDING_MORTUARY, 0},
    {BUILDING_MENU_TEMPLES, BUILDING_MENU_TEMPLE_COMPLEX, BUILDING_ORACLE, 0},
    {BUILDING_SCHOOL, BUILDING_MENU_WATER_CROSSINGS, BUILDING_LIBRARY, BUILDING_MISSION_POST, 0},
    {BUILDING_BOOTH,
     BUILDING_BANDSTAND,
     BUILDING_PAVILLION,
     BUILDING_SENET_HOUSE,
     BUILDING_JUGGLER_SCHOOL,
     BUILDING_CONSERVATORY,
     BUILDING_DANCE_SCHOOL,
     BUILDING_CHARIOT_MAKER,
     0},
    {BUILDING_TAX_COLLECTOR,
     BUILDING_GREATE_PALACE,
     BUILDING_PERSONAL_MANSION,
     BUILDING_FAMILY_MANSION,
     BUILDING_DYNASTY_MANSION,
     BUILDING_SMALL_STATUE,
     BUILDING_MEDIUM_STATUE,
     BUILDING_LARGE_STATUE,
     BUILDING_ROADBLOCK,
     BUILDING_TRIUMPHAL_ARCH,
     0},
    {BUILDING_GARDENS,
     BUILDING_PLAZA,
     BUILDING_ENGINEERS_POST,
     BUILDING_LOW_BRIDGE,
     BUILDING_SHIP_BRIDGE,
     BUILDING_SHIPYARD,
     BUILDING_DOCK,
     BUILDING_FISHING_WHARF,
     0},
    {BUILDING_WALL,
     BUILDING_TOWER,
     BUILDING_GATEHOUSE,
     BUILDING_POLICE_STATION,
     BUILDING_MENU_FORTS,
     BUILDING_MILITARY_ACADEMY,
     BUILDING_RECRUITER,
     0},
    {BUILDING_MENU_FARMS,
     BUILDING_MENU_RAW_MATERIALS,
     BUILDING_MENU_GUILDS,
     BUILDING_MARKET,
     BUILDING_GRANARY,
     BUILDING_STORAGE_YARD,
     0},
    {BUILDING_BARLEY_FARM,
     BUILDING_FLAX_FARM,
     BUILDING_GRAIN_FARM,
     BUILDING_LETTUCE_FARM,
     BUILDING_POMEGRANATES_FARM,
     BUILDING_CHICKPEAS_FARM,
     0},
    {BUILDING_CLAY_PIT, BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_WOOD_CUTTERS, 0},
    {BUILDING_BEER_WORKSHOP,
     BUILDING_LINEN_WORKSHOP,
     BUILDING_WEAPONS_WORKSHOP,
     BUILDING_JEWELS_WORKSHOP,
     BUILDING_POTTERY_WORKSHOP,
     0},
    {BUILDING_MENU_TEMPLES,
     BUILDING_TEMPLE_OSIRIS,
     BUILDING_TEMPLE_RA,
     BUILDING_TEMPLE_PTAH,
     BUILDING_TEMPLE_SETH,
     BUILDING_TEMPLE_BAST,
     0},
    {BUILDING_MENU_TEMPLE_COMPLEX,
     BUILDING_TEMPLE_COMPLEX_OSIRIS,
     BUILDING_TEMPLE_COMPLEX_RA,
     BUILDING_TEMPLE_COMPLEX_PTAH,
     BUILDING_TEMPLE_COMPLEX_SETH,
     BUILDING_TEMPLE_COMPLEX_BAST,
     0},
    {BUILDING_FORT_CHARIOTEERS, BUILDING_FORT_ARCHERS, BUILDING_FORT_INFANTRY, 0},

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
    {BUILDING_WELL,
     BUILDING_WATER_SUPPLY,
     BUILDING_DENTIST,
     BUILDING_APOTHECARY,
     BUILDING_PHYSICIAN,
     BUILDING_MORTUARY,
     0},
    // religious structures
    {BUILDING_MENU_SHRINES,
     BUILDING_MENU_TEMPLES,
     BUILDING_MENU_TEMPLE_COMPLEX,
     BUILDING_MENU_MONUMENTS,
     BUILDING_FESTIVAL_SQUARE,
     0},
    // education structures
    {BUILDING_SCHOOL, BUILDING_LIBRARY, 0},
    // entertainment structures
    {BUILDING_BOOTH,
     BUILDING_BANDSTAND,
     BUILDING_PAVILLION,
     BUILDING_SENET_HOUSE,
     BUILDING_JUGGLER_SCHOOL,
     BUILDING_CONSERVATORY,
     BUILDING_DANCE_SCHOOL,
     0}, // BUILDING_CHARIOT_MAKER
    // municipal structures
    {BUILDING_FIREHOUSE,
     BUILDING_ENGINEERS_POST,
     BUILDING_POLICE_STATION,
     BUILDING_TAX_COLLECTOR,
     BUILDING_COURTHOUSE,
     BUILDING_VILLAGE_PALACE,
     BUILDING_TOWN_PALACE,
     BUILDING_CITY_PALACE,
     BUILDING_PERSONAL_MANSION,
     BUILDING_FAMILY_MANSION,
     BUILDING_DYNASTY_MANSION,
     BUILDING_ROADBLOCK,
     BUILDING_MENU_WATER_CROSSINGS,
     BUILDING_MENU_BEAUTIFICATION,
     0},

    // beautifications
    {BUILDING_GARDENS, BUILDING_PLAZA, BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, 0},

    // military structures
    {BUILDING_MENU_DEFENSES,
     BUILDING_RECRUITER,
     BUILDING_MENU_FORTS,
     BUILDING_MILITARY_ACADEMY,
     BUILDING_WEAPONS_WORKSHOP,
     BUILDING_CHARIOTS_WORKSHOP,
     BUILDING_WARSHIP_WHARF,
     BUILDING_TRANSPORT_WHARF},
    // industry structures
    {BUILDING_MENU_RAW_MATERIALS,
     BUILDING_JEWELS_WORKSHOP,
     BUILDING_POTTERY_WORKSHOP,
     BUILDING_BEER_WORKSHOP,
     BUILDING_LINEN_WORKSHOP,
     BUILDING_PAPYRUS_WORKSHOP,
     BUILDING_BRICKS_WORKSHOP,
     BUILDING_LAMP_WORKSHOP,
     BUILDING_PAINT_WORKSHOP,
     BUILDING_SHIPYARD,
     BUILDING_MENU_GUILDS,
     0},

    // farms
    {BUILDING_GRAIN_FARM,
     BUILDING_LETTUCE_FARM,
     BUILDING_POMEGRANATES_FARM,
     BUILDING_CHICKPEAS_FARM,
     BUILDING_FIGS_FARM,
     BUILDING_BARLEY_FARM,
     BUILDING_FLAX_FARM,
     BUILDING_HENNA_FARM,
     0},
    // raw materials
    {BUILDING_CLAY_PIT,
     BUILDING_GEMSTONE_MINE,
     BUILDING_GOLD_MINE,
     BUILDING_COPPER_MINE,
     BUILDING_STONE_QUARRY,
     BUILDING_LIMESTONE_QUARRY,
     BUILDING_GRANITE_QUARRY,
     BUILDING_SANDSTONE_QUARRY,
     BUILDING_REED_GATHERER,
     BUILDING_WOOD_CUTTERS,
     0},
    // guilds
    {BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD, BUILDING_STONEMASONS_GUILD, BUILDING_ARTISANS_GUILD},
    // shrines
    {BUILDING_TEMPLE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_TEMPLE_PTAH, BUILDING_TEMPLE_SETH, BUILDING_TEMPLE_BAST, 0},
    // temple complexes
    {BUILDING_TEMPLE_COMPLEX_OSIRIS,
     BUILDING_TEMPLE_COMPLEX_RA,
     BUILDING_TEMPLE_COMPLEX_PTAH,
     BUILDING_TEMPLE_COMPLEX_SETH,
     BUILDING_TEMPLE_COMPLEX_BAST,
     BUILDING_TEMPLE_COMPLEX_ALTAR,
     BUILDING_TEMPLE_COMPLEX_ORACLE,
     0},
    // forts
    {BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS, 0},

    // food structures
    {BUILDING_MENU_FARMS,
     BUILDING_WATER_LIFT,
     BUILDING_IRRIGATION_DITCH,
     BUILDING_FISHING_WHARF,
     BUILDING_HUNTING_LODGE,
     BUILDING_WORK_CAMP},
    // distribution structures
    {BUILDING_GRANARY, BUILDING_MARKET, BUILDING_STORAGE_YARD, BUILDING_DOCK, 0},
    // shrines
    {BUILDING_SHRINE_OSIRIS, BUILDING_SHRINE_RA, BUILDING_SHRINE_PTAH, BUILDING_SHRINE_SETH, BUILDING_SHRINE_BAST, 0},
    // monuments
    {BUILDING_SMALL_ROYAL_TOMB,
     BUILDING_MEDIUM_ROYAL_TOMB,
     BUILDING_LARGE_ROYAL_TOMB,
     BUILDING_GRAND_ROYAL_TOMB,
     BUILDING_PYRAMID,
     BUILDING_SPHYNX,
     BUILDING_MAUSOLEUM,
     BUILDING_ALEXANDRIA_LIBRARY,
     BUILDING_CAESAREUM,
     BUILDING_PHAROS_LIGHTHOUSE,
     BUILDING_ABU_SIMBEL,
     0},
    // defensive structures
    {BUILDING_WALL_PH, BUILDING_TOWER_PH, BUILDING_GATEHOUSE_PH, 0},
  }};
int g_menu_enabled[BUILD_MENU_MAX][BUILD_MENU_ITEM_MAX];

static int changed = 1;

#include "SDL.h"
#include "core/game_environment.h"
#include "io/gamefiles/lang.h"

void building_menu_disable_all() {
    for (int sub = 0; sub < BUILD_MENU_MAX; sub++) {
        for (int item = 0; item < BUILD_MENU_ITEM_MAX; item++) {
            g_menu_enabled[sub][item] = 0;
        }
    }
}
void building_menu_enable_all(void) {
    for (int sub = 0; sub < BUILD_MENU_MAX; sub++) {
        for (int item = 0; item < BUILD_MENU_ITEM_MAX; item++) {
            g_menu_enabled[sub][item] = 1;
        }
    }
}

#include "building/industry.h"

int is_building_enabled(int type) {
    for (int sub = 0; sub < BUILD_MENU_MAX; sub++) {
        for (int item = 0; item < BUILD_MENU_ITEM_MAX; item++) {
            if (MENU_int[GAME_ENV][sub][item] == type) // found matching menu item!!!
                return g_menu_enabled[sub][item];
        }
    }
    return 0;
}

static void toggle_building(int type, bool enabled = true) {
    // go through all the menu items, and toggle the matching one
    for (int sub = 0; sub < BUILD_MENU_MAX; sub++) {
        for (int item = 0; item < BUILD_MENU_ITEM_MAX; item++) {
            if (MENU_int[GAME_ENV][sub][item] == type) // found match!
                g_menu_enabled[sub][item] = enabled;
        }
    }

    // additional buildings / building menus
    if (GAME_ENV == ENGINE_ENV_PHARAOH && enabled) {
        if (building_is_farm(type))
            toggle_building(BUILDING_MENU_FARMS);
        if (building_is_extractor(type))
            toggle_building(BUILDING_MENU_RAW_MATERIALS);
        if (building_is_fort(type))
            toggle_building(BUILD_MENU_FORTS);
        if (building_is_defense_ph(type))
            toggle_building(BUILDING_MENU_DEFENSES);
        if (building_is_shrine(type))
            toggle_building(BUILDING_MENU_SHRINES);
        if (building_is_temple(type))
            toggle_building(BUILDING_MENU_TEMPLES);
        if (building_is_large_temple(type))
            toggle_building(BUILDING_MENU_TEMPLE_COMPLEX);
        if (building_is_guild(type))
            toggle_building(BUILDING_MENU_GUILDS);
        if (building_is_beautification(type))
            toggle_building(BUILDING_MENU_BEAUTIFICATION);
        if (building_is_water_crossing(type))
            toggle_building(BUILDING_MENU_WATER_CROSSINGS);
        if (building_is_monument(type))
            toggle_building(BUILDING_MENU_MONUMENTS);
    }
}
static void enable_if_allowed(int type) {
    if (scenario_building_allowed(type))
        toggle_building(type, true);
    else
        toggle_building(type, false);
}

static int disable_raw_if_unavailable(int type, int resource) {
    if (!empire_can_produce_resource(resource, false)) {
        toggle_building(type, false);
        return 0;
    }
    return 1;
}
static int disable_crafted_if_unavailable(int type, int resource, int resource2 = RESOURCE_NONE) {
    if (!empire_can_produce_resource(resource, false)) {
        toggle_building(type, false);
        return 0;
    }
    if (resource2 != RESOURCE_NONE && !empire_can_produce_resource(resource2, false)) {
        toggle_building(type, false);
        return 0;
    }
    return 1;
}
static void disable_resources() {
    if (GAME_ENV == ENGINE_ENV_C3) {
        int farms = 0;
        farms += disable_raw_if_unavailable(BUILDING_BARLEY_FARM, RESOURCE_GRAIN);
        farms += disable_raw_if_unavailable(BUILDING_FLAX_FARM, RESOURCE_MEAT);
        farms += disable_raw_if_unavailable(BUILDING_GRAIN_FARM, RESOURCE_LETTUCE);
        farms += disable_raw_if_unavailable(BUILDING_CHICKPEAS_FARM, RESOURCE_FIGS);
        farms += disable_raw_if_unavailable(BUILDING_LETTUCE_FARM, RESOURCE_STRAW);
        farms += disable_raw_if_unavailable(BUILDING_POMEGRANATES_FARM, RESOURCE_BARLEY);
        farms += disable_raw_if_unavailable(BUILDING_CLAY_PIT, RESOURCE_CLAY);
        farms += disable_raw_if_unavailable(BUILDING_WOOD_CUTTERS, RESOURCE_GEMS);
        farms += disable_raw_if_unavailable(BUILDING_LIMESTONE_QUARRY, RESOURCE_COPPER);
        farms += disable_raw_if_unavailable(BUILDING_STONE_QUARRY, RESOURCE_STONE);
        //        if (!farms) // todo: monuments
        //            toggle_building(BUILDING_WORK_CAMP, false);
        disable_crafted_if_unavailable(BUILDING_POTTERY_WORKSHOP, RESOURCE_POTTERY);
        disable_crafted_if_unavailable(BUILDING_JEWELS_WORKSHOP, RESOURCE_LUXURY_GOODS);
        disable_crafted_if_unavailable(BUILDING_LINEN_WORKSHOP, RESOURCE_MEAT);
        disable_crafted_if_unavailable(BUILDING_BEER_WORKSHOP, RESOURCE_BEER);
        disable_crafted_if_unavailable(BUILDING_WEAPONS_WORKSHOP, RESOURCE_WEAPONS);
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
        disable_raw_if_unavailable(BUILDING_WOOD_CUTTERS, RESOURCE_TIMBER);
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

        disable_crafted_if_unavailable(BUILDING_POTTERY_WORKSHOP, RESOURCE_POTTERY);
        disable_crafted_if_unavailable(BUILDING_BEER_WORKSHOP, RESOURCE_BEER);
        disable_crafted_if_unavailable(BUILDING_JEWELS_WORKSHOP, RESOURCE_LUXURY_GOODS);
        disable_crafted_if_unavailable(BUILDING_LINEN_WORKSHOP, RESOURCE_LINEN);
        disable_crafted_if_unavailable(BUILDING_PAPYRUS_WORKSHOP, RESOURCE_PAPYRUS);
        disable_crafted_if_unavailable(BUILDING_BRICKS_WORKSHOP, RESOURCE_BRICKS, RESOURCE_STRAW);
        disable_crafted_if_unavailable(BUILDING_CATTLE_RANCH, RESOURCE_MEAT, RESOURCE_STRAW);
        disable_crafted_if_unavailable(BUILDING_WEAPONS_WORKSHOP, RESOURCE_WEAPONS);
        disable_crafted_if_unavailable(BUILDING_CHARIOTS_WORKSHOP, RESOURCE_CHARIOTS);
        //        disable_crafted_if_unavailable(enabled, type, BUILDING_OIL_WORKSHOP_PH, RESOURCE_OIL_PH);
        disable_crafted_if_unavailable(BUILDING_PAINT_WORKSHOP, RESOURCE_PAINT);
        disable_crafted_if_unavailable(BUILDING_LAMP_WORKSHOP, RESOURCE_LAMPS);
    }
}

static void enable_correct_palace_tier() {
    int rank = scenario_property_player_rank();
    if (rank < 6) {
        //
        toggle_building(BUILDING_TOWN_PALACE, false);
        toggle_building(BUILDING_CITY_PALACE, false);
        //
        toggle_building(BUILDING_FAMILY_MANSION, false);
        toggle_building(BUILDING_DYNASTY_MANSION, false);
    } else if (rank < 8) {
        toggle_building(BUILDING_VILLAGE_PALACE, false);
        //
        toggle_building(BUILDING_CITY_PALACE, false);
        toggle_building(BUILDING_FAMILY_MANSION, false);
        //
        toggle_building(BUILDING_DYNASTY_MANSION, false);

    } else {
        toggle_building(BUILDING_VILLAGE_PALACE, false);
        toggle_building(BUILDING_TOWN_PALACE, false);
        //
        toggle_building(BUILDING_PERSONAL_MANSION, false);
        toggle_building(BUILDING_FAMILY_MANSION, false);
        //
    }
}

static void enable_common_beautifications() {
    toggle_building(BUILDING_SMALL_STATUE);
    toggle_building(BUILDING_MEDIUM_STATUE);
    toggle_building(BUILDING_LARGE_STATUE);
    toggle_building(BUILDING_GARDENS);
    toggle_building(BUILDING_PLAZA);
}
static void enable_common_municipal(int level) {
    enable_common_beautifications();
    toggle_building(BUILDING_ROADBLOCK);
    toggle_building(BUILDING_FIREHOUSE);
    toggle_building(BUILDING_ENGINEERS_POST);
    toggle_building(BUILDING_POLICE_STATION);
    if (level >= 3) toggle_building(BUILDING_CITY_PALACE);
    else if (level >= 2) toggle_building(BUILDING_TOWN_PALACE);
    else if (level >= 1) toggle_building(BUILDING_VILLAGE_PALACE);
}

static void enable_common_health() {
    toggle_building(BUILDING_WATER_SUPPLY);
    toggle_building(BUILDING_APOTHECARY);
    toggle_building(BUILDING_PHYSICIAN);
}

static void enable_entertainment(int level) {
    if (level >= 1) {
        toggle_building(BUILDING_BOOTH);
        toggle_building(BUILDING_JUGGLER_SCHOOL);
    }

    if (level >= 2) {
        toggle_building(BUILDING_BANDSTAND);
        toggle_building(BUILDING_CONSERVATORY);
    }

    if (level >= 3) {
        toggle_building(BUILDING_PAVILLION);
        toggle_building(BUILDING_DANCE_SCHOOL);
    }

    if (level >= 4) {
        toggle_building(BUILDING_SENET_HOUSE);
    }
}

struct god_buildings_alias {
    e_god god;
    e_building_type types[2];
};

god_buildings_alias god_buildings_aliases[] = {
    {GOD_OSIRIS,    {BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS}},
    {GOD_RA,        {BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA}},
    {GOD_PTAH,      {BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH}},
    {GOD_SETH,      {BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH}},
    {GOD_BAST,      {BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST}}
};

template<typename ... Args>
static void enable_gods(Args... args) {
    int mask = make_gods_mask(args...);
    int gods[] = {args...};

    toggle_building(BUILDING_FESTIVAL_SQUARE);
    for (auto &g : gods) {
        auto &buildings = god_buildings_aliases[g].types;
        for (auto &b : buildings) {
            toggle_building(b);
        }
    }
}

void building_menu_update_gods_available(e_god god, bool available) {
    auto &buildings = god_buildings_aliases[god].types;
    for (auto &b : buildings) {
        toggle_building(b, available);
    }
}

void building_menu_update_temple_complexes() {
    if (!config_get(CONFIG_GP_CH_MULTIPLE_TEMPLE_COMPLEXES)) {
        if (city_buildings_has_temple_complex()) {
            // can't build more than one
            toggle_building(BUILDING_TEMPLE_COMPLEX_OSIRIS, false);
            toggle_building(BUILDING_TEMPLE_COMPLEX_RA, false);
            toggle_building(BUILDING_TEMPLE_COMPLEX_PTAH, false);
            toggle_building(BUILDING_TEMPLE_COMPLEX_SETH, false);
            toggle_building(BUILDING_TEMPLE_COMPLEX_BAST, false);

            // check if upgrades have been placed
            building* b = building_get(city_buildings_get_temple_complex());
            if (b->data.monuments.temple_complex_attachments & 2) // altar
                toggle_building(BUILDING_TEMPLE_COMPLEX_ALTAR, false);
            else
                toggle_building(BUILDING_TEMPLE_COMPLEX_ALTAR, true);
            if (b->data.monuments.temple_complex_attachments & 1) // oracle
                toggle_building(BUILDING_TEMPLE_COMPLEX_ORACLE, false);
            else
                toggle_building(BUILDING_TEMPLE_COMPLEX_ORACLE, true);

            // all upgrades have been placed!
            if (b->data.monuments.temple_complex_attachments == 1 + 2)
                toggle_building(BUILDING_MENU_TEMPLE_COMPLEX, false);

        } else {
            enable_if_allowed(BUILDING_TEMPLE_COMPLEX_OSIRIS);
            enable_if_allowed(BUILDING_TEMPLE_COMPLEX_RA);
            enable_if_allowed(BUILDING_TEMPLE_COMPLEX_PTAH);
            enable_if_allowed(BUILDING_TEMPLE_COMPLEX_SETH);
            enable_if_allowed(BUILDING_TEMPLE_COMPLEX_BAST);

            toggle_building(BUILDING_TEMPLE_COMPLEX_ALTAR, false);
            toggle_building(BUILDING_TEMPLE_COMPLEX_ORACLE, false);
        }
    } else {
        // TODO...?
    }
}
void building_menu_update_monuments() {
}

void building_menu_update(int build_set) {
    // do this if loading normally from a save - tutorial stage will
    // be determined accordingly by the set flags!
    if (build_set == BUILDSET_NORMAL) {
        for (int i = 1; i <= 10; i++)
            if (scenario_is_mission_rank(i)) {
                return tutorial_menu_update(i);
            }
    }

    switch (build_set) {
    case BUILDSET_TUT1_START:
        building_menu_disable_all();
        break;

    case BUILDSET_TUT1_FIRE_C3:
        toggle_building(BUILDING_POLICE_STATION);
        toggle_building(BUILDING_MARKET);
        break;

    case BUILDSET_TUT1_FIRE_PH:
        toggle_building(BUILDING_FIREHOUSE);
        break;

    case BUILDSET_TUT1_FOOD:
        toggle_building(BUILDING_HUNTING_LODGE);
        toggle_building(BUILDING_GRANARY);
        toggle_building(BUILDING_MARKET);
        break;

    case BUILDSET_TUT1_WATER:
        toggle_building(BUILDING_WATER_SUPPLY);
        break;

    case BUILDSET_TUT1_COLLAPSE_C3:
        toggle_building(BUILDING_ENGINEERS_POST);
        toggle_building(BUILDING_GREATE_PALACE);
        toggle_building(BUILDING_ROADBLOCK);
        break;

    case BUILDSET_TUT1_COLLAPSE_PH:
        toggle_building(BUILDING_ENGINEERS_POST);
        break;

    case BUILDSET_TUT2_START:
        building_menu_disable_all();

        toggle_building(BUILDING_FIREHOUSE);
        toggle_building(BUILDING_ENGINEERS_POST);
        toggle_building(BUILDING_POLICE_STATION);
        toggle_building(BUILDING_MARKET);
        toggle_building(BUILDING_GRANARY);
        toggle_building(BUILDING_HUNTING_LODGE);
        toggle_building(BUILDING_WATER_SUPPLY);
        toggle_building(BUILDING_GOLD_MINE);
        toggle_building(BUILDING_VILLAGE_PALACE);
        break;

    case BUILDSET_TUT2_GODS:
        enable_gods(GOD_BAST);
        break;

    case BUILDSET_TUT2_ENTERTAINMENT:
        toggle_building(BUILDING_BOOTH);
        toggle_building(BUILDING_JUGGLER_SCHOOL);
        break;

    case BUILDSET_TUT2_UP_TO_250:
        toggle_building(BUILDING_WATER_LIFT);
        toggle_building(BUILDING_IRRIGATION_DITCH);
        toggle_building(BUILDING_MENU_BEAUTIFICATION);
        break;

    case BUILDSET_TUT2_UP_TO_450:
        toggle_building(BUILDING_GARDENS);
        toggle_building(BUILDING_JUGGLER_SCHOOL);
        toggle_building(BUILDING_BOOTH);
        toggle_building(BUILDING_MENU_MONUMENTS);
        toggle_building(BUILDING_SCHOOL);
        break;

    case BUILDSET_TUT2_AFTER_450:
        toggle_building(BUILDING_MENU_RAW_MATERIALS);
        toggle_building(BUILDING_MENU_GUILDS);
        toggle_building(BUILDING_STORAGE_YARD);
        toggle_building(BUILDING_TAX_COLLECTOR);
        toggle_building(BUILDING_BOOTH);
        toggle_building(BUILDING_JUGGLER_SCHOOL);
        break;

    case BUILDSET_TUT3_START:
        building_menu_disable_all();

        toggle_building(BUILDING_FIREHOUSE);
        toggle_building(BUILDING_ENGINEERS_POST);
        toggle_building(BUILDING_POLICE_STATION);
        toggle_building(BUILDING_VILLAGE_PALACE);
        toggle_building(BUILDING_WATER_SUPPLY);
        toggle_building(BUILDING_FIGS_FARM);
        toggle_building(BUILDING_WORK_CAMP);
        toggle_building(BUILDING_BOOTH);
        toggle_building(BUILDING_JUGGLER_SCHOOL);
        toggle_building(BUILDING_MARKET);
        toggle_building(BUILDING_GRANARY);
        enable_gods(GOD_OSIRIS);
        break;

    case BUILDSET_TUT3_INDUSTRY:
        toggle_building(BUILDING_CLAY_PIT);
        toggle_building(BUILDING_POTTERY_WORKSHOP);
        toggle_building(BUILDING_STORAGE_YARD);
        break;

    case BUILDSET_TUT3_GARDENS:
        toggle_building(BUILDING_ROADBLOCK);
        toggle_building(BUILDING_FERRY);
        enable_common_beautifications();
        break;

    case BUILDSET_TUT3_HEALTH:
        enable_common_health();
        break;

    case BUILDSET_TUT4_START:
        building_menu_disable_all();
        enable_common_municipal(1);
        enable_common_health();
        toggle_building(BUILDING_GRAIN_FARM);
        toggle_building(BUILDING_BARLEY_FARM);
        toggle_building(BUILDING_WORK_CAMP);
        enable_entertainment(2);
        toggle_building(BUILDING_MARKET);
        toggle_building(BUILDING_GRANARY);
        toggle_building(BUILDING_FERRY);
        building_menu_update(BUILDSET_TUT3_INDUSTRY);
        //toggle_building(BUILDING_LOW_BRIDGE);
        enable_gods(GOD_OSIRIS, GOD_RA, GOD_BAST);
        toggle_building(BUILDING_BEER_WORKSHOP);
        break;

    case BUILDSET_TUT4_FINANCE:
        toggle_building(BUILDING_TAX_COLLECTOR);
        toggle_building(BUILDING_PERSONAL_MANSION);
        break;

    case BUILDSET_TUT5_START:
        building_menu_disable_all();
        enable_common_municipal(1);
        toggle_building(BUILDING_TAX_COLLECTOR);
        toggle_building(BUILDING_COURTHOUSE);
        toggle_building(BUILDING_PERSONAL_MANSION);
        enable_common_health();
        enable_entertainment(2);
        enable_gods(GOD_OSIRIS, GOD_RA, GOD_BAST);

        toggle_building(BUILDING_CLAY_PIT);
        toggle_building(BUILDING_POTTERY_WORKSHOP);
        toggle_building(BUILDING_BEER_WORKSHOP);

        toggle_building(BUILDING_MARKET);
        toggle_building(BUILDING_GRANARY);
        toggle_building(BUILDING_STORAGE_YARD);

        toggle_building(BUILDING_CHICKPEAS_FARM);
        toggle_building(BUILDING_BARLEY_FARM);
        toggle_building(BUILDING_WORK_CAMP);
        break;

    case BUILDSET_TUT5_EDUCATION:
        toggle_building(BUILDING_REED_GATHERER);
        toggle_building(BUILDING_PAPYRUS_WORKSHOP);
        toggle_building(BUILDING_SCHOOL);
        break;
    case BUILDSET_TUT5_TRADING:
        // TODO: enable trading
        toggle_building(BUILDING_DOCK);
        break;
    case BUILDSET_TUT5_MONUMENTS:
        toggle_building(BUILDING_BRICKLAYERS_GUILD);
        //            enable_monument(MONUMENT_SMALL_MASTABA); // todo!!!!!!
        break;
    case BUILDSET_TUT6_START:
        building_menu_disable_all();
        // todo
        break;
    case BUILDSET_TUT7_START:
        building_menu_disable_all();
        for (int i = 0; i < BUILDING_MAX; i++)
            enable_if_allowed(i);
        // todo
        break;
    case BUILDSET_TUT8_START:
        building_menu_disable_all();
        for (int i = 0; i < BUILDING_MAX; i++)
            enable_if_allowed(i);
        // todo
        break;
    default:
        for (int i = 0; i < BUILDING_MAX; i++)
            enable_if_allowed(i);

        // enable monuments!
        building_menu_update_monuments(); // todo!!!!!!

        // update temple complexes
        building_menu_update_temple_complexes();

        // disable resources that aren't available on map
        disable_resources();
        break;
    }

    // disable government building tiers depending on mission rank
    enable_correct_palace_tier();

    // these are always enabled
    toggle_building(BUILDING_HOUSE_VACANT_LOT);
    toggle_building(BUILDING_CLEAR_LAND);
    toggle_building(BUILDING_ROAD);
    toggle_building(BUILDING_WELL);

    changed = 1;
}
int building_menu_count_items(int submenu) {
    int count = 0;
    for (int item = 0; item < BUILD_MENU_ITEM_MAX; item++) {
        if (g_menu_enabled[submenu][item] && MENU_int[GAME_ENV][submenu][item] > 0)
            count++;
    }
    return count;
}
int building_menu_next_index(int submenu, int current_index) {
    for (int i = current_index + 1; i < BUILD_MENU_ITEM_MAX; i++) {
        if (MENU_int[GAME_ENV][submenu][i] <= 0)
            return 0;

        if (g_menu_enabled[submenu][i])
            return i;
    }
    return 0;
}

e_building_type building_menu_type(int submenu, int item) {
    return (e_building_type)MENU_int[GAME_ENV][submenu][item];
}

int building_menu_has_changed(void) {
    if (changed) {
        changed = 0;
        return 1;
    }
    return 0;
}

#include "properties.h"
#include "core/game_environment.h"
#include "core/image_group.h"

static int BUILD_MAX[2] = {
        140,
        300 // ????? temp...
};

static building_properties properties[2][400] = {
        { // SZ FIRE GRP OFF
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {1, 0, 112, 0},
                {1, 0, 24, 26},
                {1, 0, 0,  0},
                {1, 0, 19, 2},
                {0, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {2, 0, 0, 0},
                {2, 0, 0, 0},
                {2, 0, 0, 0},
                {2, 0, 0, 0},
                {3, 0, 0, 0},
                {3, 0, 0, 0},
                {3, 0, 0, 0},
                {3, 0, 0, 0},
                {4, 0, 0, 0},
                {4, 0, 0, 0},
                {3, 0, 45, 0},
                {2, 0, 46, 0},
                {5, 0, 213, 0},
                {5, 0, 48, 0},
                {3, 0, 49, 0},
                {3, 0, 50, 0},
                {3, 0, 51, 0},
                {3, 0, 52, 0},
                {1, 1, 58, 0},
                {1, 1, 59, 0},
                {3, 1, 66, 0},
                {1, 1, 61, 0},
                {2, 1, 61,             1},
                {3, 1, 61,             2},
                {3, 1, 66, 0},
                {3, 1, 66, 0},
                {1, 0, 68, 0},
                {3, 0, 70, 0},
                {2, 0, 185, 0},
                {1, 0, 67, 0},
                {3, 0, 66, 0},
                {2, 0, 41, 0},
                {3, 0, 43, 0},
                {2, 0, 42, 0},
                {4, 1, 66, 1},
                {1, 0, 64, 0},
                {3, 1, 205, 0},
                {3, 1, 66, 0},
                {2, 1, 17, 1},
                {2, 1, 17, 0},
                {2, 0, 71, 0},
                {2, 0, 72, 0},
                {2, 0, 73, 0},
                {2, 0, 74, 0},
                {2, 0, 75, 0},
                {3,  0, 71, 1},
                {3,  0, 72, 1},
                {3,  0, 73, 1},
                {3,  0, 74, 1},
                {3,  0, 75, 1},
                {2, 0, 22, 0},
                {3, 0, 99, 0},
                {1, 1, 82, 0},
                {1, 1, 82, 0},
                {2, 0, 77, 0},
                {3, 0, 78, 0},
                {2, 0, 79, 0},
                {3, 0, 85, 0},
                {4, 0, 86, 0},
                {5, 0, 87, 0},
                {2, 1, 184, 0},
                {1, 1, 81, 0},
                {1, 1, 0, 0},
                {1, 1, 0, 0},
                {0, 0, 0, 0},
                {5, 0, 62, 0},
                {2, 0, 63, 0},
                {0, 0, 0,  0},
                {1, 1, 183, 0},
                {2, 1, 183, 2},
                {3, 1, 25, 0},
                {1, 1, 54, 0},
                {1, 1, 23, 0},
                {1, 1, 100, 0},
                {3, 0, 201, 0},
                {3, 0, 166, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {2, 0, 76, 0},
                {1, 1, 0, 0},
                {3, 0, 37, 0},
                {3, 0, 37, 0},
                {3, 0, 37, 0},
                {3, 0, 37, 0},
                {3, 0, 37, 0},
                {3, 0, 37, 0},
                {2, 0, 38, 0},
                {2, 0, 39, 0},
                {2, 0, 65, 0},
                {2, 0, 40, 0},
                {2, 0, 44, 0},
                {2, 0, 122, 0},
                {2, 0, 123, 0},
                {2, 0, 124, 0},
                {2, 0, 125, 0},
                {0, 0, 0,                0},
                {1, 1, 0, 0},
                {1, 1, 0, 0},
                {1, 1, 0, 0},
                {1, 1, 0, 0},
                {1, 1, 0, 0},
                {1, 1, 0, 0},
                {1, 1, 0, 0},
                {1, 1, 0, 0},
                {1, 1, 0, 0},
                {1, 1, 0, 0},
                {1, 1, 0, 0},
                {1, 1, 0, 0},
                {1, 1, 0, 0},
                {2, 1, 216, 0},
                {1, 1, 0, 0},
                {1, 1, 0, 0},
                {1, 1, 0, 0},
                {1, 1, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0,  0},
                {0, 0, 0, 0},
                {0, 0, 0,               0},
                {0, 0, 0, 0}
        },
        { // PHARAOH
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {1, 0, 0, 0}, // road
                {1, 0, 0, 0}, // wall (unused)
                {0, 0, 0, 0},
                {1, 0, 0, 0}, // irrigation ditch
                {0, 0, 0, 0}, // clear land
                {1, 0, GROUP_BUILDING_HOUSE_VACANT_LOT}, // houses vvvv
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {2, 0, 0, 0},
                {2, 0, 0, 0},
                {2, 0, 0, 0},
                {2, 0, 0, 0},
                {3, 0, 0, 0},
                {3, 0, 0, 0},
                {3, 0, 0, 0},
                {3, 0, 0, 0},
                {4, 0, 0, 0},
                {4, 0, 0, 0}, // houses ^^^^
                {1, 0, 0, 0}, // bandstand
                {1, 0, 0, 0}, // booth
                {4, 0, GROUP_BUILDING_SENET_HOUSE}, // senet
                {2, 0, 0, 0}, // pavillion
                {3, 0, GROUP_BUILDING_CONSERVATORY}, // conservatory
                {4, 0, GROUP_BUILDING_DANCE_SCHOOL}, // dance school
                {2, 0, GROUP_BUILDING_JUGGLER_SCHOOL}, // juggler school
                {3, 0, 0, 0}, // unused (senet master)
                {1, 1, GROUP_TERRAIN_PLAZA}, // plaza
                {1, 1, GROUP_TERRAIN_GARDEN}, // gardens
                {3, 1, 0, 0}, // charioteers
                {1, 1, 0, 0},
                {2, 1, 0, 0},
                {3, 1, 0, 0}, // statues ^^^
                {3, 1, GROUP_BUILDING_FORT}, // archers
                {3, 1, GROUP_BUILDING_FORT}, // infantry
                {1, 0, GROUP_BUILDING_APOTHECARY}, // apothecary
                {2, 0, GROUP_BUILDING_MORTUARY}, // mortuary
                {2, 0, 0, 0},
                {1, 0, GROUP_BUILDING_DENTIST}, // dentist
                {3, 0, 0, 0}, // unused (distribution center)
                {2, 0, GROUP_BUILDING_SCHOOL}, // school
                {3, 0, 0, 0}, // water crossings
                {3, 0, GROUP_BUILDING_LIBRARY}, // library
                {4, 1, GROUP_BUILDING_FORT, 1}, // fort yard
                {1, 0, GROUP_BUILDING_POLICE_STATION}, // police
                {3, 1, 0, 0},
                {3, 1, GROUP_BUILDING_FORT}, // fort (main)
                {2, 1, 0, 0},
                {2, 1, 0, 0},
                {3, 0, GROUP_BUILDING_TEMPLE_OSIRIS},
                {3, 0, GROUP_BUILDING_TEMPLE_RA},
                {3, 0, GROUP_BUILDING_TEMPLE_PTAH},
                {3, 0, GROUP_BUILDING_TEMPLE_SETH},
                {3, 0, GROUP_BUILDING_TEMPLE_BAST}, // temples ^^^^
                {3, 0, 0, 0}, // oz
                {3, 0, 0, 0}, // ra
                {3, 0, 0, 0}, // ptah
                {3, 0, 0, 0}, // seth
                {3, 0, 0, 0}, // temple complex ^^^^
                {2, 0, GROUP_BUILDING_MARKET}, // bazaar
                {4, 0, GROUP_BUILDING_GRANARY}, // granary
                {1, 1, GROUP_BUILDING_WAREHOUSE}, // storageyard (hut)
                {1, 1, 0, 0}, // storageyard (space tile)
                {3, 0, GROUP_BUILDING_SHIPYARD}, // shipwright
                {3, 0, GROUP_BUILDING_DOCK}, // dock
                {2, 0, GROUP_BUILDING_FISHING_WHARF}, // wharf (fish)
                {3, 0, GROUP_BUILDING_GOVERNORS_HOUSE},
                {4, 0, GROUP_BUILDING_GOVERNORS_VILLA},
                {5, 0, GROUP_BUILDING_GOVERNORS_PALACE}, // mansions ^^^
                {2, 1, 0, 0},
                {1, 1, GROUP_BUILDING_ENGINEERS_POST}, // architects
                {1, 1, 0, 0}, // bridge
                {1, 1, 0, 0},
                {0, 0, 0, 0}, // senate (unused?)
                {5, 0, 0, 0}, // senate2 (unused?)
                {2, 0, GROUP_BUILDING_TAX_COLLECTOR},
                {2, 0, GROUP_BUILDING_TAX_COLLECTOR}, // tax collectors ^^
                {1, 1, 0, 0},
                {2, 1, 0, 0},
                {2, 1, GROUP_BUILDING_WATER_LIFT}, // ??????? water lift ???????
                {1, 1, 0, 0},
                {1, 1, GROUP_BUILDING_WELL}, // well
                {1, 1, 0, 0},
                {4, 0, GROUP_BUILDING_MILITARY_ACADEMY}, // academy
                {3, 0, GROUP_BUILDING_BARRACKS}, // recruiter
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {2, 0, 0, 0},
                {1, 1, 0, 0}, // burning ruin
                {3, 0, 0, 0},
                {3, 0, 0, 0},
                {3, 0, 0, 0},
                {3, 0, 0, 0},
                {3, 0, 0, 0},
                {3, 0, 0, 0}, // farms ^^^
                {2, 0, GROUP_BUILDING_STONE_QUARRY}, // stone
                {2, 0, GROUP_BUILDING_LIMESTONE_QUARRY}, // limestone
                {2, 0, GROUP_BUILDING_TIMBER_YARD}, // wood
                {2, 0, GROUP_BUILDING_CLAY_PIT}, // clay
                {2, 0, GROUP_BUILDING_BEER_WORKSHOP}, // beer
                {2, 0, GROUP_BUILDING_LINEN_WORKSHOP}, // linen
                {2, 0, GROUP_BUILDING_WEAPONS_WORKSHOP}, // weapons
                {2, 0, GROUP_BUILDING_JEWELS_WORKSHOP}, // jewels
                {2, 0, GROUP_BUILDING_POTTERY_WORKSHOP}, // pottery

                {2, 0, GROUP_BUILDING_HUNTING_LODGE}, // hunters
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {4, 0, 0, 0},
                {2, 1, GROUP_BUILDING_FERRY}, // ferry
                {2, 0, 0, 0},
                {1, 1, GROUP_BUILDING_ROADBLOCK}, // roadblock
                {0, 0, 0, 0},
                {1, 0, GROUP_BUILDING_SHRINE_OSIRIS},
                {1, 0, GROUP_BUILDING_SHRINE_RA},
                {1, 0, GROUP_BUILDING_SHRINE_PTAH},
                {1, 0, GROUP_BUILDING_SHRINE_SETH},
                {1, 0, GROUP_BUILDING_SHRINE_BAST}, // shrines ^^^^
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {1, 1, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {2, 0, GROUP_BUILDING_GOLD_MINE}, // gold
                {2, 0, GROUP_BUILDING_GEMSTONE_MINE}, // gemstone
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {1, 0, GROUP_BUILDING_FIREHOUSE}, // firehouse
                {0, 0, 0, 0},
                {1, 1, 0, 0}, // wall
                {0, 0, 0, 0},
                {1, 1, 0, 0}, // gatehouse
                {0, 0, 0, 0},
                {2, 1, GROUP_BUILDING_TOWER}, // tower
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {1, 1, 0, 0},
                {2, 0, GROUP_BUILDING_GUILD_CARPENTERS},
                {2, 0, GROUP_BUILDING_GUILD_BRICKLAYERS},
                {2, 0, GROUP_BUILDING_GUILD_STONEMASONS}, // guilds ^^^
                {2, 1, GROUP_BUILDING_WATER_SUPPLY}, // water supply
                {2, 1, GROUP_BUILDING_TRANSPORT_WHARF}, // wharf (transport)
                {3, 1, GROUP_BUILDING_WARSHIP_WHARF}, // wharf (warship)
                {-1, 1, 0, 0}, // pyramid
                {3, 0, GROUP_BUILDING_COURTHOUSE}, // courthouse
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {4, 0, GROUP_BUILDING_VILLAGE_PALACE},
                {5, 0, GROUP_BUILDING_TOWN_PALACE},
                {6, 0, GROUP_BUILDING_CITY_PALACE}, // town palace ^^^
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {4, 0, GROUP_BUILDING_CATTLE_RANCH}, // ranch
                {2, 0, GROUP_BUILDING_REEDS_COLLECTOR}, // reeds
                {3, 1, 0, 0}, // figs farm
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {2, 0, GROUP_BUILDING_WORKCAMP}, // work camp
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {1, 1, 0, 0}, // gatehouse (2)
                {2, 0, GROUP_BUILDING_PAPYRUS_WORKSHOP}, // papyrus
                {2, 0, GROUP_BUILDING_BRICKS_WORKSHOP, 0}, // bricks
                {4, 0, 0, 0}, // chariots
                {2, 0, GROUP_BUILDING_PHYSICIAN, 0}, // physician
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {5, 1, 0, 0}, // festival square
                {-1, 1, 0, 0}, // sphynx
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {2, 0, GROUP_BUILDING_GRANITE_QUARY, 0}, // granite
                {2, 0, GROUP_BUILDING_COPPER_MINE, 0}, // copper
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {2, 0, GROUP_BUILDING_SANDSTONE_MINE, 0}, // sandstone
                {-1, 1, 0, 0}, // mausoleum
                {0, 0, 0, 0},
                {3, 0, 0, 0}, // henna
                {-1, 1, 0, 0}, // alexandria library
        }
};


building_properties ROADBLOCK_PROPERTIES = {1, 1, 10000, 0};

const building_properties dummy_property = {0, 0, 0, 0};

const building_properties *building_properties_for_type(int type) {
    // Roadblock properties, as plaza
    if (type == 115 && GAME_ENV == ENGINE_ENV_C3)
        return &properties[GAME_ENV][38];
    if (type >= BUILD_MAX[GAME_ENV])
        return &dummy_property;
    auto p = &properties[GAME_ENV][type];
    return p;
}


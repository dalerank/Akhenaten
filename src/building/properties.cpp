#include "building/building.h"
#include "core/game_environment.h"
#include "graphics/image_groups.h"

constexpr int BUILD_MAX = 300;

struct building_properties {
    int size;
    bool fire_proof;
};
static building_properties properties[400] = {
    // PHARAOH
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {1, 0}, // road
    {1, 0}, // wall (unused)
    {0, 0},
    {1, 0},                            // irrigation ditch
    {0, 0},                            // clear land
    {1, 0}, // houses vacant lot
    {1, 0},
    {1, 0},
    {1, 0},
    {1, 0},
    {1, 0},
    {1, 0},
    {1, 0},
    {1, 0},
    {1, 0},
    {2, 0},
    {2, 0},
    {2, 0},
    {2, 0},
    {3, 0},
    {3, 0},
    {3, 0},
    {3, 0},
    {4, 0},
    {4, 0},                          // houses ^^^^
    {1, 0},                          // bandstand
    {1, 0},                          // booth
    {4, 0},    // senet
    {2, 0, 0, 0},                          // pavillion
    {3, 0, 0, 0},   // conservatory
    {4, 0, 0, 0},   // dance school
    {2, 0, 0, 0}, // juggler school
    {3, 0, 0, 0},                          // unused (senet master)
    {1, 1, GROUP_TERRAIN_PLAZA},           // plaza
    {1, 1, GROUP_TERRAIN_GARDEN},          // gardens
    {3, 1, 0, 0},                          // charioteers
    {1, 1, 0, 0},
    {2, 1, 0, 0},
    {3, 1, 0, 0},                      // statues ^^^
    {3, 1, 0, 0},       // archers
    {3, 1, 0, 0},       // infantry
    {1, 0, 0, 0}, // apothecary
    {2, 0, GROUP_BUILDING_MORTUARY},   // mortuary
    {2, 0, 0, 0},
    {1, 0, 0, 0},        // dentist
    {3, 0, 0, 0},                          // unused (distribution center)
    {2, 0, 0, 0},         // school
    {3, 0, 0, 0},                          // water crossings
    {3, 0, GROUP_BUILDING_LIBRARY},        // library
    {4, 1, 0, 0},        // fort yard
    {1, 0, GROUP_BUILDING_POLICE_STATION}, // police
    {3, 1, 0, 0},
    {3, 1, 0, 0}, // fort (main)
    {2, 1, 0, 0},
    {2, 1, 0, 0},
    {3, 0, 0, 0},
    {3, 0, 0, 0},
    {3, 0, 0, 0},
    {3, 0, 0, 0},
    {3, 0, 0, 0},   // temples ^^^^
    {3, 0, 0, 0},                         // oz
    {3, 0, 0, 0},                         // ra
    {3, 0, 0, 0},                         // ptah
    {3, 0, 0, 0},                         // seth
    {3, 0, 0, 0},                         // temple complex ^^^^
    {2, 0, 0, 0},        // bazaar
    {4, 0, 0, 0},       // granary
    {1, 1, 0, 0},  // storageyard (hut)
    {1, 1, 0, 0},                         // storageyard (space tile)
    {3, 0, 0, 0},      // shipwright
    {3, 0, 0, 0},          // dock
    {2, 0, 0, 0}, // wharf (fish)
    {3, 0, 0, 0},
    {4, 0, GROUP_BUILDING_GOVERNORS_VILLA},
    {5, 0, GROUP_BUILDING_GOVERNORS_PALACE}, // mansions ^^^
    {2, 1, 0, 0},
    {1, 1, 0, 0}, // architects
    {1, 1, 0, 0},                          // bridge
    {1, 1, 0, 0},
    {0, 0, 0, 0}, // senate (unused?)
    {5, 0, 0, 0}, // senate2 (unused?)
    {2, 0, 0, 0},
    {2, 0, 0, 0}, // tax collectors ^^
    {1, 1, 0, 0},
    {2, 1, 0, 0},
    {2, 1, GROUP_BUILDING_WATER_LIFT}, // ??????? water lift ???????
    {1, 1, 0, 0},
    {1, 1, 0, 0}, // well
    {1, 1, 0, 0},
    {4, 0, GROUP_BUILDING_MILITARY_ACADEMY}, // academy
    {3, 0, 0, 0},         // recruiter
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {2, 0, 0, 0},
    {1, 1, 0, 0}, // burning ruin
    {3, 0, 0, 0},
    {3, 0, 0, 0},
    {3, 0, 0, 0},
    {3, 0, 0, 0},
    {3, 0, 0, 0},
    {3, 0, 0, 0},                            // farms ^^^
    {2, 0, 0, 0},     // stone
    {2, 0, GROUP_BUILDING_LIMESTONE_QUARRY}, // limestone
    {2, 0, GROUP_BUILDING_TIMBER_YARD},      // wood
    {2, 0, 0, 0},         // clay
    {2, 0, 0, 0},    // beer
    {2, 0, GROUP_BUILDING_LINEN_WORKSHOP},   // linen
    {2, 0, 0, 0}, // weapons
    {2, 0, GROUP_BUILDING_JEWELS_WORKSHOP},  // jewels
    {2, 0, 0, 0}, // pottery

    {2, 0, 0, 0}, // hunters
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
    {2, 1, 0, 0}, // ferry
    {2, 0, 0, 0},
    {1, 1, GROUP_BUILDING_ROADBLOCK}, // roadblock
    {0, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0}, // shrines ^^^^
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
    {2, 0, 0, 0},     // gold
    {2, 0, 0, 0}, // gemstone
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {1, 0, 0, 0}, // firehouse
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
    {2, 0, 0, 0},
    {2, 0, 0, 0}, // guilds ^^^
    {2, 1, 0, 0},      // water supply
    {2, 1, GROUP_BUILDING_TRANSPORT_WHARF},   // wharf (transport)
    {3, 1, GROUP_BUILDING_WARSHIP_WHARF},     // wharf (warship)
    {-1, 1, 0, 0},                            // pyramid
    {3, 0, 0, 0},        // courthouse
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {4, 0, 0, 0},
    {5, 0, GROUP_BUILDING_TOWN_PALACE},
    {6, 0, GROUP_BUILDING_CITY_PALACE}, // town palace ^^^
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {3, 0, 0, 0},
    {2, 0, 0, 0}, // reeds
    {3, 1, 0, 0},                           // figs farm
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {2, 0, 0, 0}, // work camp
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {1, 1, 0, 0},                              // gatehouse (2)
    {2, 0, 0, 0},   // papyrus
    {2, 0, 0, 0, 0}, // bricks
    {4, 0, 0, 0},                              // chariots
    {2, 0, 0, 0},       // physician
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {5, 1, 0, 0},  // festival square
    {-1, 1, 0, 0}, // sphynx
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {2, 0, GROUP_BUILDING_GRANITE_QUARY, 0}, // granite
    {2, 0, 0, 0},   // copper
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {2, 0, 0, 0}, // sandstone
    {-1, 1, 0, 0},                            // mausoleum
    {0, 0, 0, 0},
    {3, 0, 0, 0},  // henna
    {-1, 1, 0, 0}, // alexandria library
};

//building_properties ROADBLOCK_PROPERTIES = {1, 1, 10000, 0};

void building_properties_init() {
    properties[BUILDING_TEMPLE_BAST] = {3, 0, 0, 0, 0, IMG_TEMPLE_BAST};
    properties[BUILDING_COURTHOUSE] = {3, 0, 0, 0, 0, IMG_NONE};
    properties[BUILDING_WEAPONSMITH] = {2, 0, 0, 0, 0, IMG_NONE};
    properties[BUILDING_ARCHITECT_POST] = {1, 0, 0, 0, 0, IMG_NONE};
    properties[BUILDING_STORAGE_YARD] = {1, 0, 0, 0, 0, IMG_STORAGE_YARD};
    properties[BUILDING_WORK_CAMP] = {2, 0, 0, 0, 0, IMG_WORKCAMP};
    properties[BUILDING_REED_GATHERER] = {2, 0, 0, 0, 0, IMG_NONE};
    properties[BUILDING_PAPYRUS_WORKSHOP] = {2, 0, 0, 0, 0, IMG_NONE};
    properties[BUILDING_WATER_SUPPLY] = {2, 1, 0, 0, 0, IMG_NONE};
    properties[BUILDING_STONEMASONS_GUILD] = {2, 0, 0, 0, 0, IMG_GUILD_STONEMASONS};
    properties[BUILDING_DOCK] = {3, 1, 0, 0, 0, IMG_BUILDING_DOCK};
    properties[BUILDING_DANCE_SCHOOL] = {4, 0, 0, 0, 0, IMG_NONE};
    properties[BUILDING_FERRY] = {2, 1, 0, 0, 0, IMG_NONE};
    properties[BUILDING_DENTIST] = {1, 0, 0, 0, 0, IMG_NONE};
}
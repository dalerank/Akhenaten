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
    {2, 0},                          // pavillion
    {3, 0},   // conservatory
    {4, 0},   // dance school
    {2, 0}, // juggler school
    {3, 0},                          // unused (senet master)
    {1, 1},           // plaza
    {1, 1},          // gardens
    {3, 1},                          // charioteers
    {1, 1},
    {2, 1},
    {3, 1},                      // statues ^^^
    {3, 1},       // archers
    {3, 1},       // infantry
    {1, 0}, // apothecary
    {2, 0},   // mortuary
    {2, 0},
    {1, 0},        // dentist
    {3, 0},                          // unused (distribution center)
    {2, 0},         // school
    {3, 0},                          // water crossings
    {3, 0},        // library
    {4, 1},        // fort yard
    {1, 0}, // police
    {3, 1},
    {3, 1}, // fort (main)
    {2, 1},
    {2, 1},
    {3, 0},
    {3, 0},
    {3, 0},
    {3, 0},
    {3, 0},   // temples ^^^^
    {3, 0},                         // oz
    {3, 0},                         // ra
    {3, 0},                         // ptah
    {3, 0},                         // seth
    {3, 0},                         // temple complex ^^^^
    {2, 0},        // bazaar
    {4, 0},       // granary
    {1, 1},  // storageyard (hut)
    {1, 1},                         // storageyard (space tile)
    {3, 0},      // shipwright
    {3, 0},          // dock
    {2, 0}, // wharf (fish)
    {3, 0},
    {4, 0},
    {5, 0}, // mansions ^^^
    {2, 1},
    {1, 1}, // architects
    {1, 1},                          // bridge
    {1, 1},
    {0, 0}, // senate (unused?)
    {5, 0}, // senate2 (unused?)
    {2, 0},
    {2, 0}, // tax collectors ^^
    {1, 1},
    {2, 1},
    {2, 1}, // ??????? water lift ???????
    {1, 1},
    {1, 1}, // well
    {1, 1},
    {4, 0}, // academy
    {3, 0},         // recruiter
    {0, 0},
    {0, 0},
    {2, 0},
    {1, 1}, // burning ruin
    {3, 0},
    {3, 0},
    {3, 0},
    {3, 0},
    {3, 0},
    {3, 0},                            // farms ^^^
    {2, 0},     // stone
    {2, 0}, // limestone
    {2, 0},      // wood
    {2, 0},         // clay
    {2, 0},    // beer
    {2, 0},   // linen
    {2, 0}, // weapons
    {2, 0},  // jewels
    {2, 0}, // pottery

    {2, 0}, // hunters
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {4, 0},
    {2, 1}, // ferry
    {2, 0},
    {1, 1}, // roadblock
    {0, 0},
    {1, 0},
    {1, 0},
    {1, 0},
    {1, 0},
    {1, 0}, // shrines ^^^^
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {1, 1},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {2, 0},     // gold
    {2, 0}, // gemstone
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {1, 0}, // firehouse
    {0, 0},
    {1, 1}, // wall
    {0, 0},
    {1, 1}, // gatehouse
    {0, 0},
    {2, 1}, // tower
    {0, 0},
    {0, 0},
    {1, 1},
    {2, 0},
    {2, 0},
    {2, 0}, // guilds ^^^
    {2, 1},      // water supply
    {2, 1},   // wharf (transport)
    {3, 1},     // wharf (warship)
    {-1, 1},                            // pyramid
    {3, 0},        // courthouse
    {0, 0},
    {0, 0},
    {4, 0},
    {5, 0},
    {6, 0}, // town palace ^^^
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {3, 0},
    {2, 0}, // reeds
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
    {2, 0}, // granite
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


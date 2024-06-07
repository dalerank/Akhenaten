#pragma once

#include "building/building_type.h"
#include "city/constants.h"
#include "city/gods.h"
#include "core/bstring.h"

enum e_build_menu {
    BUILD_MENU_VACANT_HOUSE = 0,
    BUILD_MENU_CLEAR_LAND = 1,
    BUILD_MENU_ROAD = 2,
    BUILD_MENU_WATER_CROSSINGS = 3,
    BUILD_MENU_HEALTH = 4,
    BUILD_MENU_RELIGION = 5,
    BUILD_MENU_EDUCATION = 6,
    BUILD_MENU_ENTERTAINMENT = 7,
    BUILD_MENU_ADMINISTRATION = 8,
    BUILD_MENU_BEAUTIFICATION = 9,
    BUILD_MENU_SECURITY = 10,
    BUILD_MENU_INDUSTRY = 11,

    BUILD_MENU_FARMS = 12,
    BUILD_MENU_RAW_MATERIALS = 13,
    BUILD_MENU_GUILDS = 14,
    BUILD_MENU_TEMPLES = 15,
    BUILD_MENU_LARGE_TEMPLES = 16,
    BUILD_MENU_TEMPLE_COMPLEX = 16,
    BUILD_MENU_FORTS = 17,
    //
    BUILD_MENU_FOOD = 18,
    BUILD_MENU_DISTRIBUTION = 19,
    BUILD_MENU_SHRINES = 20,
    BUILD_MENU_MONUMENTS = 21,
    BUILD_MENU_DEFENCES = 22,
    //
    BUILD_MENU_MAX
};

int building_menu_is_building_enabled(int type);
void building_menu_toggle_building(int type, bool enabled = true);

void building_menu_set_all(bool enabled);

void building_menu_update(const bstring64 &stage);

int building_menu_count_items(int submenu);

int building_menu_next_index(int submenu, int current_index);

e_building_type building_menu_type(int submenu, int item);

void building_menu_update_monuments();
void building_menu_update_temple_complexes();
void building_menu_update_gods_available(e_god god, bool available);

bool building_menu_has_changed();
void building_menu_invalidate();
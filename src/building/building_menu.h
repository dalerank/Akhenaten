#pragma once

#include "building/building_type.h"
#include "city/constants.h"
#include "city/city_religion.h"
#include "core/bstring.h"
#include "graphics/animation.h"

int building_menu_is_building_enabled(int type);
void building_menu_toggle_building(int type, bool enabled = true);

void building_menu_set_all(bool enabled);
bool building_menu_is_submenu(int submenu);

void building_menu_setup_mission();
void building_menu_update(const xstring stage);

int building_menu_count_items(int submenu);

int building_menu_next_index(int submenu, int current_index);

e_building_type building_menu_type(int submenu, int item);
const animation_t &building_menu_anim(int submenu);

void building_menu_update_monuments();
void building_menu_update_temple_complexes();
void building_menu_update_gods_available(e_god god, bool available);

bool building_menu_has_changed();
void building_menu_invalidate();
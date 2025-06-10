#pragma once

struct animation_t;

struct event_building_change_mode { const animation_t &anim; };

void window_build_menu_show(int submenu);
int window_build_menu_selected();
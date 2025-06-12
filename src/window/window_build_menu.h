#pragma once

#include "graphics/image_desc.h"

struct event_building_change_mode { image_desc img; };

void window_build_menu_show(int submenu);
int window_build_menu_selected();
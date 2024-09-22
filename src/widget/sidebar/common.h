#pragma once

#include "graphics/elements/menu.h"
#include "graphics/image_desc.h"

#define SIDEBAR_MAIN_SECTION_HEIGHT 450

int sidebar_common_get_height(void);
void sidebar_common_draw_relief(int x_offset, int y_offset, image_desc desc, bool is_collapsed);


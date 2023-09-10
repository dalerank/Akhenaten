#pragma once

#include "core/vec2i.h"

struct mouse;

void widget_minimap_invalidate();

void widget_minimap_draw(vec2i offset, int width_tiles, int height_tiles, int force);

bool widget_minimap_handle_mouse(const mouse* m);

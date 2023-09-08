#pragma once

#include "core/vec2i.h"

void screen_set_resolution(int width, int height);

int screen_width();
int screen_height();
vec2i screen_size();

int screen_dialog_offset_x(void);
int screen_dialog_offset_y(void);
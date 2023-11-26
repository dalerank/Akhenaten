#pragma once

#include "graphics/color.h"
#include "core/vec2i.h"

class building;
struct object_info;
struct painter;

void building_juggler_school_draw_info(object_info& c);
void building_conservatory_draw_info(object_info& c);
void building_dancer_school_draw_info(object_info& c);
void building_bullfight_school_draw_info(object_info& c);

void building_entertainment_draw_shows_dancers(painter &ctx, building *b, vec2i pixel, color color_mask);
void building_entertainment_draw_show_jugglers(painter &ctx, building *b, vec2i pixel, color color_mask);
void building_entertainment_draw_shows_musicians(painter &ctx, building *b, vec2i pixel, int direction, color color_mask);
#pragma once

#include "core/vec2i.h"
#include "game/resource.h"
#include "city/constants.h"

#define DEFAULT_BLOCK_SIZE 16

struct painter;

void outer_panel_draw(vec2i pos, int width_blocks, int height_blocks);

void inner_panel_draw(vec2i pos, vec2i size);
void outer_panel_draw_exact(vec2i pos, vec2i size);
void unbordered_panel_draw(int x, int y, int width_blocks, int height_blocks);

void small_panel_draw(vec2i pos, int width_blocks, int type);
void small_panel_draw_colored(vec2i pos, int width_blocks, int type, uint32_t mask);

void large_label_draw(int x, int y, int width_blocks, int type);
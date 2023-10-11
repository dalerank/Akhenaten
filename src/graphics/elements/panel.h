#pragma once

#include <cstdint>

#define DEFAULT_BLOCK_SIZE 16

void outer_panel_draw(int x, int y, int width_blocks, int height_blocks);

void inner_panel_draw(int x, int y, int width_blocks, int height_blocks);

void unbordered_panel_draw(int x, int y, int width_blocks, int height_blocks);

void label_draw(int x, int y, int width_blocks, int type);
void label_draw_colored(int x, int y, int width_blocks, int type, uint32_t mask);

void large_label_draw(int x, int y, int width_blocks, int type);

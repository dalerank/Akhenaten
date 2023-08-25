#pragma once

#include "grid/grid.h"

#define MAX_QUEUE GRID_SIZE_TOTAL

void clear_distances(void);
int valid_offset(int grid_offset);

void enqueue(int offset, int distance);
void route_queue(int source, int dest, void (*callback)(int next_offset, int dist));
void route_queue_until(int source, bool (*callback)(int next_offset, int dist));
bool route_queue_until_found(int source, int* dst_x, int* dst_y, bool (*callback)(int, int));
bool route_queue_until_terrain(int source, int terrain_type, int* dst_x, int* dst_y, bool (*callback)(int, int, int));
void route_queue_max(int source, int dest, int max_tiles, void (*callback)(int, int));
void route_queue_boat(int source, void (*callback)(int, int));
void route_queue_dir8(int source, void (*callback)(int, int));

bool queue_has(int offset);
int queue_get(int i);

#ifndef MAP_ORIENTATION_H
#define MAP_ORIENTATION_H

void map_orientation_change(int counter_clockwise);

int map_orientation_for_gatehouse(int x, int y);

int map_orientation_for_triumphal_arch(int x, int y);

void map_orientation_update_buildings(void);

int map_orientation_for_venue(int x, int y, int mode, int *building_orientation);
int map_orientation_for_venue_with_map_orientation(int x, int y, int mode, int *building_orientation);

#endif // MAP_ORIENTATION_H

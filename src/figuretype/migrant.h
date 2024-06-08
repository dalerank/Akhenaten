#pragma once

#include "grid/point.h"

class building;

void figure_add_house_population(building *house, int num_people);
int figure_closest_house_with_room(tile2i tile);
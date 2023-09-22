#pragma once

#include "grid/point.h"

class building;

void figure_create_immigrant(building* house, int num_people);
void figure_create_emigrant(building* house, int num_people);
void figure_create_homeless(tile2i tile, int num_people);
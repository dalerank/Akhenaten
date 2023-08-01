#ifndef FIGURETYPE_MIGRANT_H
#define FIGURETYPE_MIGRANT_H

#include "building/building.h"
#include "figure/figure.h"

void figure_create_immigrant(building* house, int num_people);
void figure_create_emigrant(building* house, int num_people);
void figure_create_homeless(int x, int y, int num_people);

#endif // FIGURETYPE_MIGRANT_H

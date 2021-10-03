#ifndef BUILDING_CONSTRUCTION_ROUTED_H
#define BUILDING_CONSTRUCTION_ROUTED_H

#include "map/routing.h"

int building_construction_place_road(bool measure_only, int x_start, int y_start, int x_end, int y_end);

int building_construction_place_wall(bool measure_only, int x_start, int y_start, int x_end, int y_end);

int building_construction_place_aqueduct(bool measure_only, int x_start, int y_start, int x_end, int y_end);

int building_construction_place_aqueduct_for_reservoir(bool measure_only, int x_start, int y_start, int x_end, int y_end,
                                                       int *items);

#endif // BUILDING_CONSTRUCTION_ROUTED_H

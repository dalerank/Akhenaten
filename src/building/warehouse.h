#pragma once

#include "building/building.h"
#include "grid/point.h"

enum e_warehouse_state { WAREHOUSE_ROOM = 0, WAREHOUSE_FULL = 1, WAREHOUSE_SOME_ROOM = 2 };

enum e_warehouse_task {
    WAREHOUSE_TASK_NONE = -1,
    WAREHOUSE_TASK_GETTING = 0,
    WAREHOUSE_TASK_DELIVERING = 1,
    WAREHOUSE_TASK_EMPTYING = 2,
    //
    WAREHOUSE_TASK_GETTING_MOAR = 9,
};

int building_warehouse_get_space_info(building* warehouse);

int building_warehouse_get_amount(building* warehouse, int resource);

int building_warehouse_add_resource(building* b, int resource, int amount);

bool building_warehouse_is_accepting(int resource, building* b);
bool building_warehouse_is_getting(int resource, building* b);
bool building_warehouse_is_emptying(int resource, building* b);
bool building_warehouse_is_not_accepting(int resource, building* b);
int building_warehouse_get_accepting_amount(int resource, building* b);

int building_warehouse_remove_resource(building* warehouse, int resource, int amount);

void building_warehouse_remove_resource_curse(building* warehouse, int amount);

void building_warehouse_space_set_image(building* space, int resource);

void building_warehouse_space_add_import(building* space, int resource);

void building_warehouse_space_remove_export(building* space, int resource);

void building_warehouses_add_resource(int resource, int amount);

int building_warehouses_remove_resource(int resource, int amount);

int building_warehouse_for_storing(building* src,
                                   int x,
                                   int y,
                                   int resource,
                                   int distance_from_entry,
                                   int road_network_id,
                                   int* understaffed,
                                   map_point* dst);

int building_warehouse_for_getting(building* src, int resource, map_point* dst);

int building_warehouse_determine_worker_task(building* warehouse, int* resource, int* amount);

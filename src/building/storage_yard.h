#pragma once

#include "game/resource.h"
#include "grid/point.h"

#include "building/building.h"

class building_storage_yard : public building_impl {
public:
    building_storage_yard(building &b) : building_impl(b) {}
    virtual void on_create() override;
    virtual void spawn_figure() override;
    virtual void window_info_background(object_info &ctx) override;
    virtual void window_info_foreground(object_info &ctx) override;

private:
    void draw_warehouse_orders(object_info *c);
    void draw_warehouse(object_info *c);
    void draw_warehouse_orders_foreground(object_info *c);
    void draw_warehouse_foreground(object_info *c);
};


enum e_storageyard_state { STORAGEYARD_ROOM = 0, STORAGEYARD_FULL = 1, STORAGEYARD_SOME_ROOM = 2 };

enum e_storageyard_task {
    STORAGEYARD_TASK_NONE = -1,
    STORAGEYARD_TASK_GETTING = 0,
    STORAGEYARD_TASK_DELIVERING = 1,
    STORAGEYARD_TASK_EMPTYING = 2,
    STORAGEYARD_TASK_MONUMENT = 3,
    //
    STORAGEYARD_TASK_GETTING_MOAR = 9,
};

struct storage_worker_task {
    e_storageyard_task result = STORAGEYARD_TASK_NONE;
    building *space = nullptr;
    int amount = 0;
    e_resource resource = RESOURCE_NONE;
    building *dest = nullptr;
};

int building_storageyard_get_space_info(building* warehouse);

int building_storageyard_get_amount(const building* warehouse, e_resource resource);
int building_storageyard_get_freespace(building* warehouse, e_resource resource);

int building_storageyard_add_resource(building* b, e_resource resource, int amount);

bool building_storageyard_is_accepting(e_resource resource, building* b);
bool building_storageyard_is_getting(e_resource resource, building* b);
bool building_storageyard_is_emptying(e_resource resource, building* b);
bool building_storageyard_is_not_accepting(e_resource resource, building* b);
int building_storageyard_get_accepting_amount(e_resource resource, building* b);

int building_storageyard_remove_resource(building* warehouse, e_resource resource, int amount);

void building_storageyard_remove_resource_curse(building* warehouse, int amount);

void building_storageyard_space_set_image(building* space, e_resource resource);

void building_storageyard_space_add_import(building* space, e_resource resource);

void building_storageyard_space_remove_export(building* space, e_resource resource);

void building_storageyards_add_resource(e_resource resource, int amount);

int building_storageyard_remove_resource(e_resource resource, int amount);

int building_storageyard_for_storing(building* src, tile2i tile, e_resource resource, int distance_from_entry, int road_network_id, int* understaffed, tile2i* dst);

int building_storageyard_for_getting(building* src, e_resource resource, tile2i* dst);

storage_worker_task building_storageyard_determine_worker_task(building* warehouse);

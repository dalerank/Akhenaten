#pragma once

#include "game/resource.h"
#include "grid/point.h"

#include "building/building.h"

struct building_storage;
class building_storage_room;

class building_storage_yard : public building_impl {
public:
    building_storage_yard(building &b) : building_impl(b), stored_full_amount(b.stored_full_amount) {}
    virtual void on_create() override;
    virtual void spawn_figure() override;
    virtual void window_info_background(object_info &ctx) override;
    virtual void window_info_foreground(object_info &ctx) override;

    virtual building_storage_yard *dcast_storage_yard() override { return this; }
    
    building_storage_room *room() { return next()->dcast_storage_room(); }
    const building_storage *storage();

    int get_amount(e_resource resource);
    bool is_not_accepting(e_resource resource);

    int remove_resource(e_resource resource, int amount);
    int add_resource(e_resource resource, int amount);
    bool is_gettable(e_resource resource);
    bool is_getting(e_resource resource);
    bool is_emptying(e_resource resource);
    bool get_permission(int p) const;

    int accepting_amount(e_resource resource);

    int for_getting(e_resource resource, tile2i *dst);

    short &stored_full_amount;

private:
    void draw_warehouse_orders(object_info *c);
    void draw_warehouse(object_info *c);
    void draw_warehouse_orders_foreground(object_info *c);
    void draw_warehouse_foreground(object_info *c);
    int get_space_info() const;
    bool is_accepting(e_resource resource);
};

class building_storage_room : public building_impl {
public:
    building_storage_room(building &b) : building_impl(b), stored_full_amount(b.stored_full_amount) {}

    virtual building_storage_room *dcast_storage_room() { return this; }
    building_storage_room *next_room() { return next()->dcast_storage_room(); }
    building_storage_yard *yard() { return main()->dcast_storage_yard(); }
    const building_storage *storage();

    void set_image(e_resource resource);
    void add_import(e_resource resource);
    bool is_this_space_the_best(tile2i tile, e_resource resource, int distance_from_entry);
    void remove_export(e_resource resource);
    int accepting_amount(e_resource resource);

    short &stored_full_amount;
};

int get_storage_accepting_amount(building *b, e_resource resource);
int building_storage_yard_for_storing(tile2i tile, e_resource resource, int distance_from_entry, int road_network_id, int *understaffed, tile2i *dst);

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

int building_storageyard_get_freespace(building* warehouse, e_resource resource);

void building_storageyard_remove_resource_curse(building* warehouse, int amount);

void building_storageyard_space_remove_export(building* space, e_resource resource);

void building_storageyards_add_resource(e_resource resource, int amount);

int building_storageyards_remove_resource(e_resource resource, int amount);

storage_worker_task building_storageyard_determine_worker_task(building* warehouse);

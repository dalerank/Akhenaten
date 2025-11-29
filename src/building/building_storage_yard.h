#pragma once

#include "building/building_storage.h"
#include "building/building_type.h"
#include "grid/point.h"
#include "core/svector.h"

enum e_storageyard_state {
    STORAGEYARD_ROOM = 0,
    STORAGEYARD_FULL = 1,
    STORAGEYARD_SOME_ROOM = 2
};

enum e_storageyard_task {
    STORAGEYARD_TASK_NONE = -1,
    STORAGEYARD_TASK_GETTING = 0,
    STORAGEYARD_TASK_DELIVERING = 1,
    STORAGEYARD_TASK_EMPTYING = 2,
    STORAGEYARD_TASK_MONUMENT = 3,
    STORAGEYARD_TASK_POLICE_STATION = 4,
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

struct event_warehouse_filled { building_id bid; };

class building_storage_yard : public building_storage {
public:
    BUILDING_METAINFO(BUILDING_STORAGE_YARD, building_storage_yard, building_storage)
    virtual building_storage_yard *dcast_storage_yard() override { return this; }

    struct runtime_data_t {
        std::array<building_id, 4> police_station_weapon_requests;
    } BUILDING_RUNTIME_DATA_T;

    struct preview : building_planer_renderer {
        virtual void setup_preview_graphics(build_planner &planer) const override;
        virtual int construction_update(build_planner &p, tile2i start, tile2i end) const override;
        virtual void ghost_preview(build_planner &p, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const override;
    };

    virtual void on_create(int orientation) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_place_checks() override;
    virtual void spawn_figure() override;
    virtual void update_graphic() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_STORAGE_YARD; }

    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    
    building_storage_room *room() { return next()->dcast_storage_room(); }
    const building_storage_room *room() const { return ((building_impl*)this)->next()->dcast_storage_room(); }

    virtual int amount(e_resource resource) const override;
    virtual int total_stored() const override;
    virtual int freespace() const override;
    bool is_not_accepting(e_resource resource);
    void remove_resource_curse(int amount);

    virtual int remove_resource(e_resource resource, int amount) override;
    virtual int add_resource(e_resource resource, int amount, bool force) override;

    virtual bool is_getting(e_resource resource) override;

    int freespace(e_resource resource);
    int stored_full_amount() const { return base.stored_amount_first;  }

    int for_getting(e_resource resource, tile2i *dst);

    static storage_worker_task deliver_food_to_gettingup_granary(building *warehouse);

    storage_worker_task determine_worker_task();

private:
    int get_space_info() const;
    bool is_accepting(e_resource resource);
    building *add_storageyard_space(int x, int y, building *prev);
};

building_storage_yard *storage_yard_cast(building *b);

building_id building_storage_yard_for_storing(tile2i tile, e_resource resource, int distance_from_entry, int road_network_id, int *understaffed, tile2i &dst);
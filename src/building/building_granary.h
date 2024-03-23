#pragma once

#include "building/building.h"
#include "game/resource.h"
#include "core/vec2i.h"
#include "grid/point.h"
#include "graphics/color.h"

struct building_storage;

enum e_granary_task {
    GRANARY_TASK_NONE = -1,
    GRANARY_TASK_GETTING = 0,
};

struct granary_task_status {
    e_granary_task status;
    e_resource resource;
};

class building_granary : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_GRANARY, building_granary)

    building_granary(building &b) : building_impl(b) {}
    virtual building_granary *dcast_granary() override { return this; }

    virtual void on_create(int orientation) override;
    virtual void spawn_figure() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_GRANARY; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual std::pair<int, int> get_tooltip() const;
    virtual void window_info_background(object_info &ctx) override;
    virtual void window_info_foreground(object_info &ctx) override;
    virtual int window_info_handle_mouse(const mouse *m, object_info &c) override;

    const building_storage *storage();
    int amount(e_resource resource);
    bool is_accepting(e_resource resource);
    int is_not_accepting(e_resource resource);
    bool is_getting(e_resource resource);
    int for_getting(tile2i *dst);
    int add_resource(e_resource resource, int is_produced, int amount);

    void bless();
    bool is_gettable(e_resource resource);
    granary_task_status determine_worker_task();
    int remove_resource(e_resource resource, int amount);
    static int remove_for_getting_deliveryman(building* src, building* dst, e_resource& resource);
};

void building_granaries_calculate_stocks();
int building_granary_for_storing(tile2i tile, e_resource resource, int distance_from_entry, int road_network_id, int force_on_stockpile, int* understaffed, tile2i* dst);
int building_getting_granary_for_storing(tile2i tile, e_resource resource, int distance_from_entry, int road_network_id, tile2i* dst);
#pragma once

#include "building/building.h"
#include "game/resource.h"
#include "core/vec2i.h"
#include "grid/point.h"
#include "graphics/color.h"

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
    virtual void on_create() override;
    virtual void spawn_figure() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_GRANARY; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual std::pair<int, int> get_tooltip() const;
    virtual void window_info_background(object_info &ctx) override;
    virtual void window_info_foreground(object_info &ctx) override;
    virtual int window_info_handle_mouse(const mouse *m, object_info &c) override;
};

int building_granary_get_amount(building* granary, e_resource resource);

int building_granary_add_resource(building* granary, e_resource resource, int is_produced, int amount);

int building_granary_remove_resource(building* granary, e_resource resource, int amount);

int building_granary_remove_for_getting_deliveryman(building* src, building* dst, e_resource& resource);

int building_granary_is_not_accepting(e_resource resource, building* b);

granary_task_status building_granary_determine_worker_task(building* granary);

void building_granaries_calculate_stocks();

int building_granary_for_storing(tile2i tile, e_resource resource, int distance_from_entry, int road_network_id, int force_on_stockpile, int* understaffed, tile2i* dst);

int building_getting_granary_for_storing(tile2i tile, e_resource resource, int distance_from_entry, int road_network_id, tile2i* dst);

int building_granary_for_getting(building* src, tile2i* dst);

void building_granary_bless();
void building_granary_warehouse_curse(int big);

bool building_granary_is_getting(e_resource resource, building* b);
void building_granary_set_res_offset(int i, vec2i v);
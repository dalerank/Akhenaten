#pragma once

#include "building/building_storage.h"
#include "core/vec2i.h"
#include "grid/point.h"
#include "graphics/color.h"

enum e_granary_task {
    GRANARY_TASK_NONE = 0,
    GRANARY_TASK_GETTING = 1,
    GRANARY_TASK_EMPTYING = 2,
};

struct granary_task_status {
    e_granary_task status;
    e_resource resource;
};

struct granary_getting_result {
    int building_id;
    tile2i tile;
};

struct event_granary_resource_added { building_id bid; e_resource r; int amount; };
struct event_granary_resource_removed { building_id bid; e_resource r;  int amount; };

class building_granary : public building_storage {
public:
    BUILDING_METAINFO(BUILDING_GRANARY, building_granary, building_storage)

    virtual building_granary *dcast_granary() override { return this; }

    struct static_params : building_static_params {
        vec2i begin_spot_pos;
    } BUILDING_STATIC_DATA_T;

    struct runtime_data_t {
        short resource_stored[16];
    } BUILDING_RUNTIME_DATA_T;

    virtual void on_create(int orientation) override;
    virtual void spawn_figure() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_GRANARY; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual textid get_tooltip() const override;
    virtual void on_place_checks() override;
    virtual void update_day() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_FOOD_STOCKS; }
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;

    virtual int amount(e_resource resource) const override;
    virtual bool is_getting(e_resource resource) override;
    virtual int remove_resource(e_resource resource, int amount) override;
    virtual int add_resource(e_resource resource, int amount, bool force) override;
    virtual int freespace() const override;
    bool is_accepting(e_resource resource);
    bool is_not_accepting(e_resource resource);
    granary_getting_result find_storage_for_getting();
    int total_stored() const override;
    int capacity_stored() const { return 3200; }
    int allow_food_types() const { return 4; }

    void bless();
    granary_task_status determine_worker_task();
    void draw_stores(vec2i point, color color_mask, painter &ctx);

    template<e_building_type T>
    int better_getting_storage();
};
ANK_CONFIG_STRUCT(building_granary::static_params, begin_spot_pos);

int building_granary_for_storing(tile2i tile, e_resource resource, int distance_from_entry, int road_network_id, int force_on_stockpile, int* understaffed, tile2i* dst);
int building_getting_granary_for_storing(tile2i tile, e_resource resource, int distance_from_entry, int road_network_id, tile2i* dst);
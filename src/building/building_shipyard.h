#pragma once

#include "building/building_industry.h"

enum {
    SHIPYARD_REPAIR_QUEUES = 10,
};

class building_shipyard : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_SHIPWRIGHT, building_shipyard, building_impl)

    virtual building_shipyard *dcast_shipyard() override { return this; }

    struct static_params : public building_static_params {
        int warship_progress_cost;
        int transport_progress_cost;
        int fishingboat_progress_cost;
    } BUILDING_STATIC_DATA_T;

    struct runtime_data_t {
        e_figure_type process_type;
        bool reparing;
        figure_id repair_fid;
        uint8_t queue_slot; // 1-based index into g_shipyard_repair_queues; 0 = none
    } BUILDING_RUNTIME_DATA_T;

    virtual void on_create(int orientation) override;
    virtual void on_place(int orientation, int variant) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_destroy() override;
    virtual void on_post_load() override;
    virtual void update_day() override;
    virtual void update_month() override;
    virtual void update_graphic() override;
    virtual void update_count() const override;
    virtual void spawn_figure() override;
    virtual void update_map_orientation(int orientation) override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_STORAGE_YARD; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual bool add_resource(e_resource resource, int amount, figure_id fid = 0) override;

    int repair_queue_size() const;
    bool pop_repair_order(figure_id &out_fid);
};

void building_shipyard_repair_queues_clear();
void building_shipyard_repair_queue_add(building_id bid);
void building_shipyard_repair_queue_remove(building_id bid);
int building_shipyard_repair_queue_size(building_id bid);
int building_shipyard_find_best_dock(figure_id fid);
bool building_shipyard_queue_ship(figure_id fid, building_id bid);
void building_shipyard_leave_queue(figure_id fid);

ANK_CONFIG_STRUCT(building_shipyard::static_params,
    warship_progress_cost, transport_progress_cost, fishingboat_progress_cost)

ANK_CONFIG_PROPERTY(building_shipyard::runtime_data_t, process_type, reparing, repair_fid)

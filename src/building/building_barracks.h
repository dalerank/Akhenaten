#pragma once

#include "building/building.h"
#include "window/window_building_info.h"

class buffer;

enum e_barracks_priority {
    PRIORITY_TOWER = 0,
    PRIORITY_FORT = 1,
};

class building_recruiter : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_RECRUITER, building_recruiter, building_impl)
    virtual building_recruiter *dcast_recruiter() override { return this; }

    struct static_params : public building_static_params {
        virtual bool is_unique_building() const override;
    } BUILDING_STATIC_DATA_T;

    struct runtime_data_t {
        uint8_t priority;
    } BUILDING_RUNTIME_DATA_T;

    virtual void on_create(int orientation) override;
    virtual void on_post_load() override;
    virtual void on_place_checks() override;
    virtual void spawn_figure() override;
    virtual void update_count() const override;
    virtual bool add_resource(e_resource resource, int amount) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;

    int get_priority();
    void set_priority(int v);
    bool create_tower_sentry();
    bool create_soldier();
    e_formation_id get_closest_batalion_needing_soldiers();
};
ANK_CONFIG_STRUCT(building_recruiter::static_params, meta)

void building_barracks_request_tower_sentry();
void building_barracks_decay_tower_sentry_request();
int building_barracks_has_tower_sentry_request();

void building_barracks_save_state(buffer* buf);
void building_barracks_load_state(buffer* buf);


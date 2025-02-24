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
    BUILDING_METAINFO(BUILDING_RECRUITER, building_recruiter)
    building_recruiter(building &b) : building_impl(b) {}
    virtual building_recruiter *dcast_recruiter() override { return this; }

    struct static_params : public buildings::model_t<building_recruiter> {
        virtual bool is_unique_building() const override;
    };

    virtual void on_create(int orientation) override;
    virtual void on_post_load() override;
    virtual void on_place_checks() override;
    virtual void spawn_figure() override;
    virtual void update_count() const override;
    virtual bool add_resource(e_resource resource, int amount) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;

    int get_priority();
    bool create_tower_sentry();
    bool create_soldier();
};

void building_barracks_request_tower_sentry();
void building_barracks_decay_tower_sentry_request();
int building_barracks_has_tower_sentry_request();

void building_barracks_save_state(buffer* buf);
void building_barracks_load_state(buffer* buf);


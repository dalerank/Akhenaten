#pragma once

#include "building/building.h"

class buffer;

class building_recruiter : public building_impl {
public:
    building_recruiter(building &b) : building_impl(b) {}
    virtual void on_create() override;
    virtual void spawn_figure() override;
    virtual void window_info_background(object_info &ctx) override;
    virtual void window_info_foreground(object_info &ctx) override;
    virtual int window_info_handle_mouse(const mouse *m, object_info &c) override;
};

void building_barracks_request_tower_sentry();
void building_barracks_decay_tower_sentry_request();
int building_barracks_has_tower_sentry_request();

void building_barracks_save_state(buffer* buf);
void building_barracks_load_state(buffer* buf);

enum e_barracks_priority {
    PRIORITY_TOWER = 0,
    PRIORITY_FORT = 1,
};

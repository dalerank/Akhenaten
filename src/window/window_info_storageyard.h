#pragma once

#include "city/object_info.h"
#include "window_building_info.h"
#include "building/building.h"

struct info_window_storageyard : public building_info_window_t<info_window_storageyard> {
    virtual void init(object_info &c) override;
    virtual void window_info_background(object_info &c) override;
    virtual void window_info_foreground(object_info &c) override;
    virtual bool check(object_info &c) override;

    virtual int window_info_handle_mouse(const mouse *m, object_info &c) override;
};

struct info_window_storageyard_orders : building_info_window_t<info_window_storageyard_orders> {
    vec2i parent_window_offset;

    void draw_background(object_info *c);
    void draw_foreground(object_info *c);
    vec2i get_adjusted_offset(object_info *c);

    virtual int window_info_handle_mouse(const mouse *m, object_info &c) override;

    virtual void archive_load(archive arch) override {
        building_info_window::archive_load(arch);

        parent_window_offset = arch.r_vec2i("parent_window_offset");
    }
};
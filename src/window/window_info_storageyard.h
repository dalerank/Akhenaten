#pragma once

#include "city/object_info.h"
#include "window_building_info.h"
#include "building/building.h"

struct info_window_storageyard : public building_info_window_t<info_window_storageyard> {
    virtual void window_info_background(object_info &c) override;
    virtual void window_info_foreground(object_info &c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        return building_type_any_of(*b, BUILDING_STORAGE_YARD, BUILDING_STORAGE_YARD_UP, BUILDING_STORAGE_ROOM);
    }

    virtual int window_info_handle_mouse(const mouse *m, object_info &c) override;

    void draw_background(object_info *c);
    void draw_foreground(object_info *c);
};

struct info_window_storageyard_orders : building_info_window_t<info_window_storageyard_orders> {
    vec2i parent_window_offset;

    void draw_background(object_info *c);
    void draw_foreground(object_info *c);

    virtual int window_info_handle_mouse(const mouse *m, object_info &c) override;

    virtual void load(archive arch, pcstr section) override {
        building_info_window::load(arch, section);

        parent_window_offset = arch.r_vec2i("parent_window_offset");
    }
};
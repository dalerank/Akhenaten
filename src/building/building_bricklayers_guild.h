#pragma once

#include "building/building.h"

struct object_info;

class building_bricklayers_guild : public building_impl {
public:
    building_bricklayers_guild(building &b) : building_impl(b) {}
    virtual void on_create() override;
    virtual void spawn_figure() override;
    virtual void window_info_background(object_info &c) override;
};

void building_bricklayers_guild_draw_info(object_info &c);

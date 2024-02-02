#pragma once

#include "building/building.h"

void building_marble_quarry_draw_info(object_info& c);
void building_limestone_quarry_draw_info(object_info& c);
void building_timber_yard_draw_info(object_info& c);
void building_clay_pit_draw_info(object_info& c);
void building_copper_mine_draw_info(object_info &c);
void building_reed_gatherer_draw_info(object_info& c);
void building_sandstone_quarry_draw_info(object_info &c);
void building_granite_quarry_draw_info(object_info &c);

class building_mine_gold : public building_impl {
public:
    building_mine_gold(building &b) : building_impl(b) {}
    virtual void on_create() override;
    virtual void window_info_background(object_info &c) override;
    virtual int get_produce_uptick_per_day() const override;
};

class building_quarry_stone : public building_impl {
public:
    building_quarry_stone(building &b) : building_impl(b) {}
    virtual void on_create() override;
    virtual void window_info_background(object_info &c) override;
    virtual int get_produce_uptick_per_day() const override { return base.num_workers / 2.f; }
};

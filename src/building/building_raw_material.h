#pragma once

#include "building/building.h"

void building_marble_quarry_draw_info(object_info& c);
void building_limestone_quarry_draw_info(object_info& c);
void building_timber_yard_draw_info(object_info& c);
void building_copper_mine_draw_info(object_info &c);
void building_reed_gatherer_draw_info(object_info& c);
void building_sandstone_quarry_draw_info(object_info &c);
void building_granite_quarry_draw_info(object_info &c);

class building_clay_pit : public building_impl {
public:
    building_clay_pit(building &b) : building_impl(b) {}
    virtual void on_create() override;
    virtual void window_info_background(object_info &c) override;
    virtual int get_fire_risk(int value) const override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_CLAY_PIT; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};

class building_mine_gold : public building_impl {
public:
    building_mine_gold(building &b) : building_impl(b) {}
    virtual void on_create() override;
    virtual void window_info_background(object_info &c) override;
    virtual int get_produce_uptick_per_day() const override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};

class building_mine_gems : public building_impl {
public:
    building_mine_gems(building &b) : building_impl(b) {}
    virtual void on_create() override;
    virtual void window_info_background(object_info &c) override;
    virtual int get_produce_uptick_per_day() const override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};

class building_quarry_stone : public building_impl {
public:
    building_quarry_stone(building &b) : building_impl(b) {}
    virtual void on_create() override;
    virtual void window_info_background(object_info &c) override;
    virtual int get_produce_uptick_per_day() const override { return base.num_workers / 2.f; }
};

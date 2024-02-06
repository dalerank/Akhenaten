#pragma once

#include "building/building.h"

void building_marble_quarry_draw_info(object_info& c);
void building_limestone_quarry_draw_info(object_info& c);
void building_timber_yard_draw_info(object_info& c);
void building_reed_gatherer_draw_info(object_info& c);
void building_sandstone_quarry_draw_info(object_info &c);
void building_granite_quarry_draw_info(object_info &c);

namespace model {
    struct raw_building_t;
}

class building_clay_pit : public building_impl {
public:
    building_clay_pit(building &b) : building_impl(b) {}
    virtual void on_create() override;
    virtual void window_info_background(object_info &c) override;
    virtual int get_fire_risk(int value) const override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_CLAY_PIT; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};

class building_mine : public building_impl {
public:
    building_mine(building &b) : building_impl(b) {}
    virtual void on_create() override;
    virtual const model::raw_building_t &params() const = 0;
    virtual void window_info_background(object_info &c) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};

class building_mine_gold : public building_mine {
public:
    building_mine_gold(building &b) : building_mine(b) {}
    virtual const model::raw_building_t &params() const override;
    virtual int get_produce_uptick_per_day() const override;
};

class building_mine_gems : public building_mine {
public:
    building_mine_gems(building &b) : building_mine(b) {}
    virtual const model::raw_building_t &params() const override;
    virtual int get_produce_uptick_per_day() const override { return base.num_workers > 0 ? std::max<int>(1, base.num_workers / 3) : 0; }
};

class building_quarry_stone : public building_impl {
public:
    building_quarry_stone(building &b) : building_impl(b) {}
    virtual void on_create() override;
    virtual void window_info_background(object_info &c) override;
    virtual int get_produce_uptick_per_day() const override { return base.num_workers > 0 ? std::max<int>(1, base.num_workers / 2) : 0; }
};

class building_mine_copper : public building_mine {
public:
    building_mine_copper(building &b) : building_mine(b) {}
    virtual const model::raw_building_t &params() const override;
    virtual int get_produce_uptick_per_day() const override { return base.num_workers > 0 ? std::max<int>(1, base.num_workers / 2) : 0; }
};

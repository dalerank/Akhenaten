#pragma once

#include "building/building_industry.h"

class building_clay_pit : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_CLAY_PIT, building_clay_pit, building_industry)
    virtual building_clay_pit *dcast_clay_pit() override { return this; }

    virtual int get_fire_risk(int value) const override;
    virtual void on_before_flooded() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_CLAY_PIT; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};


class building_mine : public building_industry {
public:
    building_mine(building &b) : building_industry(b) {}
    virtual building_mine *dcast_mine() override { return this; }

    virtual void on_create(int orientation) override;
    virtual void update_graphic() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};

class building_mine_gold : public building_mine {
public:
    BUILDING_METAINFO(BUILDING_GOLD_MINE, building_mine_gold, building_mine)

    virtual int produce_uptick_per_day() const override;
};

class building_mine_gems : public building_mine {
public:
    BUILDING_METAINFO(BUILDING_GEMSTONE_MINE, building_mine_gems, building_mine)

    virtual int produce_uptick_per_day() const override { return base.num_workers > 0 ? std::max<int>(1, base.num_workers / 3) : 0; }
};

class building_mine_copper : public building_mine {
public:
    BUILDING_METAINFO(BUILDING_COPPER_MINE, building_mine_copper, building_mine)

    struct preview : building_planer_renderer {
        virtual bool is_need_flag(build_planner& p, e_building_flags flag) const override;
    };

    virtual int produce_uptick_per_day() const override { return base.num_workers > 0 ? std::max<int>(1, base.num_workers / 2) : 0; }
    virtual void on_before_collapse() override;
};

#pragma once

#include "building/building.h"

class building_palace : public building_impl {
public:
    building_palace(building &b) : building_impl(b) {}
    virtual building_palace *dcast_palace() override { return this; }

    virtual void on_create(int orientation) override;
    virtual void on_post_load() override;
    virtual void on_destroy() override;
    virtual bool can_play_animation() const override;
    virtual void update_graphic() override;
    virtual void draw_tooltip(tooltip_context *c) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
};

class building_village_palace : public building_palace {
public:
    BUILDING_METAINFO(BUILDING_VILLAGE_PALACE, building_village_palace)
    building_village_palace(building &b) : building_palace(b) {}
};

class building_town_palace : public building_palace {
public:
    BUILDING_METAINFO(BUILDING_TOWN_PALACE, building_town_palace)
    building_town_palace(building &b) : building_palace(b) {}
};

class building_city_palace : public building_palace {
public:
    BUILDING_METAINFO(BUILDING_CITY_PALACE, building_city_palace)
    building_city_palace(building &b) : building_palace(b) {}
};
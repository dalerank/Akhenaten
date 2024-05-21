#pragma once

#include "building/building.h"

class building_carpenters_guild : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_CARPENTERS_GUILD, building_carpenters_guild)
    building_carpenters_guild(building &b) : building_impl(b) {}

    //virtual void on_create(int orientation) override;
    //virtual void on_place(int orientation, int variant) override;
    //virtual void window_info_background(object_info &c) override;
    //virtual void spawn_figure() override;
};

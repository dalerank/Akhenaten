#pragma once

#include "building/building_guild.h"

class building_carpenters_guild : public building_guild {
public:
    BUILDING_METAINFO(BUILDING_CARPENTERS_GUILD, building_carpenters_guild, building_guild)

    virtual void on_create(int orientation) override;
    virtual void spawn_figure() override;
    virtual void update_graphic() override;
    bool can_spawn_carpenter(int max_gatherers_per_building);
};
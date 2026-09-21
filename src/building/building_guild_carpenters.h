#pragma once

#include "building/building_guild.h"

class building_carpenters_guild : public building_guild {
public:
    BUILDING_METAINFO(BUILDING_CARPENTERS_GUILD, building_carpenters_guild, building_guild)

    virtual void spawn_figure() override;
    bool can_spawn_carpenter();
};

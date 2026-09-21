#pragma once

#include "building/building_guild.h"

class building_bricklayers_guild : public building_guild {
public:
    BUILDING_METAINFO(BUILDING_BRICKLAYERS_GUILD, building_bricklayers_guild, building_guild)

    virtual void spawn_figure() override;
    bool can_spawn_bricklayer_man();
};

#pragma once

#include "building/building_guild.h"

class building_artisans_guild : public building_guild {
public:
    BUILDING_METAINFO(BUILDING_ARTISANS_GUILD, building_artisans_guild, building_guild)

    virtual void spawn_figure() override;
    bool can_spawn_tomb_artisan();
    bool has_paint_and_clay() const;
};

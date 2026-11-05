#pragma once

#include "building/building_guild.h"

class building_carpenters_guild : public building_guild {
public:
    BUILDING_METAINFO(BUILDING_CARPENTERS_GUILD, building_carpenters_guild, building_guild)

    virtual void spawn_figure() override;
    virtual void update_day() override;

    int max_active_carpenters() const;
    bool can_spawn_carpenter() const;

    static building *find_monument_task(tile2i from);
    static building *find_statue_task();
};

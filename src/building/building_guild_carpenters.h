#pragma once

#include "building/building_guild.h"

class building_carpenters_guild : public building_guild {
public:
    BUILDING_METAINFO(BUILDING_CARPENTERS_GUILD, building_carpenters_guild, building_guild)

    struct static_params : public building_static_params {
        // OG: guild_worker_rules CARPENTER_PROGRESS / industry 2*PROGRESS_DONE / LOAD.
        uint16_t progress_ready = 400;
        uint16_t progress_cap = 400;
        uint16_t timber_load = 100;
    } BUILDING_STATIC_DATA_T;

    virtual void spawn_figure() override;
    virtual void update_day() override;

    int max_active_carpenters() const;
    bool can_spawn_carpenter() const;

    static building *find_monument_task(tile2i from);
    static building *find_statue_task();
};
ANK_CONFIG_STRUCT(building_carpenters_guild::static_params, progress_ready, progress_cap, timber_load)

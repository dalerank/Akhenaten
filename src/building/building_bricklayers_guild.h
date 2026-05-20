#pragma once

#include "building/building_guild.h"

class building_bricklayers_guild : public building_guild {
public:
    BUILDING_METAINFO(BUILDING_BRICKLAYERS_GUILD, building_bricklayers_guild, building_guild)

    struct static_params : public building_static_params {
        uint8_t max_workers;
    } BUILDING_STATIC_DATA_T;

    virtual void on_create(int orientation) override;
    virtual void spawn_figure() override;
    virtual void update_graphic() override;
    bool can_spawn_bricklayer_man();
};
ANK_CONFIG_STRUCT(building_bricklayers_guild::static_params, max_workers)
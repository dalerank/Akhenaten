#pragma once

#include "building/building_guild.h"

class building_artisans_guild : public building_guild {
public:
    BUILDING_METAINFO(BUILDING_ARTISANS_GUILD, building_artisans_guild, building_guild)

    struct static_params : public building_static_params {
        uint8_t max_workers;
    } BUILDING_STATIC_DATA_T;

    virtual void on_create(int orientation) override;
    virtual void spawn_figure() override;
    bool can_spawn_tomb_artisan();
    bool has_paint_and_clay() const;
};
ANK_CONFIG_STRUCT(building_artisans_guild::static_params, max_workers)

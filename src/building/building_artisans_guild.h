#pragma once

#include "building/building_guild.h"

class building_artisans_guild : public building_guild {
public:
    BUILDING_METAINFO(BUILDING_ARTISANS_GUILD, building_artisans_guild, building_guild)

    struct static_params : public building_static_params {
        uint16_t material_load = 100;
    } BUILDING_STATIC_DATA_T;

    virtual void spawn_figure() override;
    virtual void update_animation() override;

    int max_active_artisans() const;
    bool can_spawn_tomb_artisan() const;

    static building* find_monument_task(e_resource material);
};
ANK_CONFIG_STRUCT(building_artisans_guild::static_params, material_load)

#pragma once

#include "building/building_guild.h"

class building_stonemason_guild : public building_guild {
public:
    BUILDING_METAINFO(BUILDING_STONEMASONS_GUILD, building_stonemason_guild, building_guild)

    virtual void on_create(int orientation) override;
    virtual void spawn_figure() override;
    virtual void update_graphic() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;

    bool can_spawn_stonemason_man(int max_gatherers_per_building);
};
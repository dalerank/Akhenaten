#pragma once

#include "building/building.h"

enum {
    PERMISSION_NONE = 0,
    PERMISSION_MAINTENANCE = 1,
    PERMISSION_PRIEST = 2,
    PERMISSION_MARKET = 3,
    PERMISSION_ENTERTAINER = 4,
    PERMISSION_EDUCATION = 5,
    PERMISSION_MEDICINE = 6,
    PERMISSION_TAX_COLLECTOR = 7
};

void building_roadblock_set_permission(int p, building* b);
int building_roadblock_get_permission(int p, building* b);

class building_roadblock : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_ROADBLOCK, building_roadblock)
    building_roadblock(building &b) : building_impl(b) {}

    virtual void on_place_checks() override;
    //virtual void window_info_background(object_info &c) override;
    //virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) override;
};
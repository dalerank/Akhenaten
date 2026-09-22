#pragma once

#include "building/building.h"

class building_industry_office : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_INDUSTRY_OFFICE, building_industry_office, building_impl)
    virtual building_industry_office *dcast_industry_office() override { return this; }

    struct static_params : public building_static_params {
        uint8_t management_radius;
    } BUILDING_STATIC_DATA_T;

    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void update_graphic() override;
    virtual bool force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual bool add_resource(e_resource resource, int amount, figure_id fid = 0) override;

    bool is_management_active() const;
    int management_radius() const;

private:
    void draw_placeholder(painter &ctx, color color_mask) const;
};

ANK_CONFIG_STRUCT(building_industry_office::static_params, management_radius)

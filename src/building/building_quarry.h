#pragma once

#include "building/building_industry.h"
#include "grid/grid.h"

class building_quarry : public building_industry {
public:
    building_quarry(building &b) : building_industry(b) {}
    virtual building_quarry *dcast_quarry() override { return this; }

protected:
    template<typename GetResourceFunc, typename DepleteResourceFunc>
    void update_production_with_resource_depletion(GetResourceFunc get_resource, DepleteResourceFunc deplete_resource) {
        auto &d = runtime_data();
        int current_progress = d.progress;

        tile2i best_tile = tile2i::invalid;
        int best_resource = 0;

        grid_area search_area = map_grid_get_area(base.tile, base.size, 0);
        map_grid_area_foreach(search_area.tmin, search_area.tmax, [&] (tile2i t) {
            int resource = get_resource(t);
            if (resource > 0 && resource > best_resource) {
                best_tile = t;
                best_resource = resource;
            }
        });

        if (best_resource <= 0) {
            return;
        }
        
        building_industry::update_production();
        int delta_progress = d.progress - current_progress;
       
        deplete_resource(best_tile, delta_progress);
    }
};

class building_sandstone_quarry : public building_quarry {
public:
    BUILDING_METAINFO(BUILDING_SANDSTONE_QUARRY, building_sandstone_quarry, building_quarry)

    virtual int animation_speed(int speed) const override { return 3; }
    virtual int produce_uptick_per_day() const override { return base.num_workers > 0 ? std::max<int>(1, base.num_workers / 2) : 0; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void update_production() override;
};

class building_stone_quarry : public building_quarry {
public:
    BUILDING_METAINFO(BUILDING_STONE_QUARRY, building_stone_quarry, building_quarry)

    virtual int animation_speed(int speed) const override { return 3; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual int produce_uptick_per_day() const override { return base.num_workers > 0 ? std::max<int>(1, base.num_workers / 2) : 0; }
    virtual void update_production() override;
};

class building_limestone_quarry : public building_quarry {
public:
    BUILDING_METAINFO(BUILDING_LIMESTONE_QUARRY, building_limestone_quarry, building_quarry)

    virtual int animation_speed(int speed) const override { return 3; }
    virtual int produce_uptick_per_day() const override { return base.num_workers > 0 ? std::max<int>(1, base.num_workers / 2) : 0; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void update_production() override;
};

class building_granite_quarry : public building_quarry {
public:
    BUILDING_METAINFO(BUILDING_GRANITE_QUARRY, building_granite_quarry, building_quarry)

    virtual int animation_speed(int speed) const override { return 3; }
    virtual int produce_uptick_per_day() const override { return base.num_workers > 0 ? std::max<int>(1, base.num_workers / 2) : 0; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void update_production() override;
};
#pragma once

#include "building/building.h"

struct building_gatehouse_ghost {
    svector<vec2i, 8> main_view_offset;
    svector<vec2i, 8> part_view_offset;
};
ANK_CONFIG_STRUCT(building_gatehouse_ghost, main_view_offset, part_view_offset)

class building_gatehouse : public building_impl {
public:
    building_gatehouse(building &b) : building_impl(b) {}
    virtual building_gatehouse *dcast_gatehouse() override { return this; }

    struct preview : building_planer_renderer {
        virtual void ghost_preview(build_planner &planer, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const override;
        virtual void ghost_blocked(build_planner &planer, painter &ctx, tile2i tile, tile2i end, vec2i pixel, bool fully_blocked) const override;
    };

    struct gatehouse_params_t {
        building_gatehouse_ghost ghost;
    };

    virtual void on_create(int orientation) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_place(int orientation, int variant) override;
    virtual void on_place_checks() override;
    virtual void update_map_orientation(int orientation) override;
        
    struct back_tile_orientation {
        tile2i tile;
        int orientation;
    };
    static back_tile_orientation second_part_tile(build_planner &planer, tile2i end, int city_orientation);
    static void update_image_set(building &maingate);

    virtual void spawn_figure() override;
};

class building_brick_gatehouse : public building_gatehouse {
public:
    BUILDING_METAINFO(BUILDING_BRICK_GATEHOUSE, building_brick_gatehouse, building_gatehouse)

    struct static_params : public gatehouse_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;
};
ANK_CONFIG_STRUCT(building_brick_gatehouse::static_params, ghost)

class building_mud_gatehouse : public building_gatehouse {
public:
    BUILDING_METAINFO(BUILDING_MUD_GATEHOUSE, building_mud_gatehouse, building_gatehouse)

    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;

    struct static_params : public gatehouse_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;
};
ANK_CONFIG_STRUCT(building_mud_gatehouse::static_params, ghost)

class building_tower_gatehouse : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_TOWER_GATEHOUSE, building_tower_gatehouse, building_impl)

    struct preview : building_planer_renderer {
        virtual void ghost_preview(build_planner &planer, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const override;
        virtual void ghost_blocked(build_planner &planer, painter &ctx, tile2i tile, tile2i end, vec2i pixel, bool fully_blocked) const override;
        virtual int can_place(build_planner &p, tile2i tile, tile2i end, int state) const override;
    };

    virtual void update_map_orientation(int orientation) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_create(int orientation) override;
};

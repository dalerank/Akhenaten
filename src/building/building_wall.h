#pragma once

#include "building/building.h"
#include "grid/image_context.h"

struct event_building_update_walls { tile2i tile; int size; };

class building_mud_wall : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_MUD_WALL, building_mud_wall, building_impl)

    struct preview : building_planer_renderer {
        virtual bool can_construction_start(build_planner &p, tile2i start) const override;
        virtual int construction_update(build_planner &p, tile2i start, tile2i end) const override;
        virtual int construction_place(build_planner &planer, tile2i start, tile2i end, int orientation, int variant) const override;
    };

    virtual void on_place_checks() override;

    static bool place_wall(bool measure_only, tile2i start, tile2i end);
    static bool set_wall(tile2i tile);
    static void set_image(tile2i tile);
    static void set_wall_gatehouse_image_manually(int grid_offset);
    static int get_gatehouse_position(int grid_offset, int direction, int building_id);
    static int get_gatehouse_building_id(int grid_offset);
    static void update_all_walls();
    static void update_area_walls(tile2i tile, int size);

    static terrain_image get_terrain_image(tile2i tile);
};
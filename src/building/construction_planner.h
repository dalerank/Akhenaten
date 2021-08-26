#ifndef OZYMANDIAS_CONSTRUCTION_PLANNER_H
#define OZYMANDIAS_CONSTRUCTION_PLANNER_H

#include "graphics/color.h"
#include "map/point.h"

enum PlannerReqs {
    Groundwater =           1,
    Water =                 1 << 1,
    NearbyWater =           1 << 2,
    ShoreLine =             1 << 3,
    Meadow =                1 << 4,
    Trees =                 1 << 5,
    //
    Rock =                  1 << 8,
    Ore =                   1 << 9,
    Road =                  1 << 10,
    Intersection =          1 << 11,
    Walls =                 1 << 12,
    //
    RiverAccess =           1 << 16,
};

extern class BuildPlanner {
private:
    map_point size;
    map_point pivot;
    int tile_graphics_array[30][30] = {};
    int tile_sizes_array[30][30] = {};
    int tile_restricted_terrains[30][30] = {};
    bool tile_blocked_array[30][30] = {};
    int tiles_blocked_total = 0;

    long long requirement_flags = 0;
    int additional_req_param = 0;
    bool meets_special_requirements = false;
    int immediate_warning_id = -1;

    int start_offset_x_view;
    int start_offset_y_view;

    void reset();
    void init_tiles(int size_x, int size_y);
    void set_pivot(int x, int y);
    void update_coord_caches(const map_tile *cursor_tile, int x, int y);

    void set_graphics_row(int row, int *image_ids, int total);
    void set_graphics_array(int *image_set, int size_x, int size_y);

    void load_build_graphics(); // fills in data automatically

    void set_tile_size(int row, int column, int size);
    void set_allowed_terrain(int row, int column, int terrain);

    void set_requirements(long long flags, int extra_param);
    void update_requirements_check();
    void dispatch_warnings();

    void update_obstructions_check();

    void draw_flat_tile(int x, int y, color_t color_mask);
    void draw_blueprints(bool fully_blocked);
    void draw_graphics();

    /////

public:
    int building_type;
    bool in_progress;
    bool draw_as_constructing;
    map_tile start;
    map_tile end;
    int cost;

    void setup_build_type(int type);
    void clear_building_type(void);
    int get_building_type(void);

    int get_total_drag_size(int *x, int *y);

    void construction_start(int x, int y, int grid_offset);

    bool construction_is_draggable(void);

    void construction_cancel(void);
    void construction_update(int x, int y, int grid_offset);
    void construction_finalize(void);

    void construction_record_view_position(int view_x, int view_y, int grid_offset);

    int orientation;
    int variant;

    void update_orientations();

    void update(const map_tile *cursor_tile, int x, int y);
    void draw();
    bool place_check_attempt();
} Planner;

#endif //OZYMANDIAS_CONSTRUCTION_PLANNER_H

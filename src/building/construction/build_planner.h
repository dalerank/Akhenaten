#pragma once

#include "building/type.h"

#include "graphics/color.h"
#include "graphics/view/view.h"
#include "grid/point.h"

enum PlannerFlags {
    Groundwater = 1,
    Water = 1 << 1,
    NearbyWater = 1 << 2,
    ShoreLine = 1 << 3,
    RiverAccess = 1 << 4,
    FloodplainShore = 1 << 5,
    //
    Meadow = 1 << 6,
    Trees = 1 << 7,
    Rock = 1 << 8,
    Ore = 1 << 9,
    Road = 1 << 10,
    Intersection = 1 << 11,
    FancyRoad = 1 << 12,
    Walls = 1 << 13,
    Canals = 1 << 14,
    //
    TempleUpgrade = 1 << 16,
    Resources = 1 << 17,
    IgnoreNearbyEnemy = 1 << 18,
    //
    Draggable = 1 << 21,
    Ferry = 1 << 22,
    Bridge = 1 << 23,
};

enum e_place_action {
    CAN_PLACE = 0,
    CAN_NOT_PLACE = 1,
    CAN_NOT_BUT_GREEN = 2,
};

class BuildPlanner {
private:
    int tile_graphics_array[30][30] = {};
    int tile_sizes_array[30][30] = {};
    bool tile_blocked_array[30][30] = {};
    int tiles_blocked_total = 0;

    map_point tile_coord_cache[30][30];
    vec2i pixel_coords_cache[30][30];

    long long special_flags = 0;
    int additional_req_param1 = -1;
    int additional_req_param2 = -1;
    int additional_req_param3 = -1;
    int can_place = CAN_PLACE;

    int immediate_warning_id = -1;
    int extra_warning_id = -1;

    int start_offset_screen_x;
    int start_offset_screen_y;

    void init_tiles(int size_x, int size_y);
    void set_graphics_row(int row, int* image_ids, int total);
    void set_tiles_building(int image_id, int size_xx);
    void set_graphics_array(int* image_set, int size_x, int size_y);

    void setup_build_flags();
    void setup_build_graphics(); // fills in data automatically

    void set_tile_size(int row, int column, int size);

    void set_flag(long long flags, int param1 = -1, int param2 = -1, int param3 = -1);
    void update_obstructions_check();
    void update_requirements_check();
    void update_special_case_orientations_check();
    void update_unique_only_one_check();
    void dispatch_warnings();

    void update_coord_caches();
    void draw_flat_tile(int x, int y, color color_mask);
    void draw_blueprints(bool fully_blocked);
    void draw_graphics();

    /////

public:
    e_building_type build_type;
    bool in_progress;
    bool draw_as_constructing;
    map_point start;
    map_point end;
    int total_cost;
    int relative_orientation;
    int absolute_orientation;
    int variant;
    struct {
        int x;
        int y;
    } size;
    struct {
        int x;
        int y;
    } pivot;

    map_point north_tile;
    map_point east_tile;
    map_point south_tile;
    map_point west_tile;

    int can_be_placed();

    void reset();
    void setup_build(e_building_type type);

    void construction_start(map_point tile);
    void construction_update(map_point tile);
    void construction_cancel();
    void construction_finalize();

    void add_building_tiles_from_list(int building_id, bool graphics_only);

    void update_orientations(bool check_if_changed = true);
    void construction_record_view_position(vec2i pixel, map_point point);

    int get_total_drag_size(int* x, int* y);
    bool has_flag_set(int flag, int param1 = -1, int param2 = -1, int param3 = -1);

    void update(map_point cursor_tile);
    void draw();
    bool place();
};

extern BuildPlanner Planner;

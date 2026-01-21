#pragma once

#include "building/building.h"
#include "graphics/color.h"
#include "graphics/view/view.h"
#include "grid/point.h"
#include "grid/terrain.h"

enum e_planner_rule : uint8_t {
    Groundwater = 0,
    Water = 1,
    NearbyWater = 2,
    ShoreLine = 3,
    RiverAccess = 4,
    FloodplainShore = 5,
    //
    Meadow = 6,
    Trees = 7,
    Rock = 8,
    Ore = 9,
    Road = 10,
    Intersection = 11,
    FancyRoad = 12,
    Walls = 13,
    Canals = 14,
    //
    Reserved = 16,
    Resources = 17,
    IgnoreNearbyEnemy = 18,
    //
    Draggable = 21,
    Ferry = 22,
    Bridge = 23,
    //
    TempleUpgradeAltar = 24,
    TempleUpgradeOracle = 25,
};

enum e_place_action {
    CAN_PLACE = 0,
    CAN_NOT_PLACE = 1,
    CAN_NOT_BUT_GREEN = 2,
};

class build_planner {
    int tile_graphics_array[30][30] = {};
    int tile_sizes_array[30][30] = {};
    bool tile_blocked_array[30][30] = {};
    int tiles_blocked_total = 0;

    tile2i tile_coord_cache[30][30];
    vec2i pixel_coords_cache[30][30];

    int additional_req_param2 = -1;
    int additional_req_param3 = -1;
    int can_place = CAN_PLACE;

    xstring immediate_warning;
    xstring extra_warning;

    int start_offset_screen_x;
    int start_offset_screen_y;

    void set_graphics_row(int row, custom_span<int> image_ids, int def);

    void setup_build_flags();
    void setup_build_graphics(); // fills in data automatically

    void set_tile_size(int row, int column, int size);

    void set_flag(e_planner_rule flags, int param1 = -1, int param2 = -1, int param3 = -1);
    void update_obstructions_check();
    void update_requirements_check();
    void update_special_case_orientations_check();
    void update_unique_only_one_check();
    void dispatch_warnings();
    void checks_generic_rules(building *b, tile2i tile, int size, int orientation);
    void check_road_access(building *b, tile2i tile, int size, int orientation);

    void update_coord_caches();
    void draw_graphics(painter &ctx);
    int place_houses(bool measure_only, int x_start, int y_start, int x_end, int y_end);

public:
    void set_warning(xstring warning) { immediate_warning = warning; }
    void set_extra_warning(xstring warning) { extra_warning = warning; }

    inline bool needGroundwater() const { return is_flag(e_planner_rule::Groundwater); }
    inline bool needWater() const { return is_flag(e_planner_rule::Water); }
    inline bool needShoreLine() const { return is_flag(e_planner_rule::ShoreLine); }
    inline bool needNearbyWater() const { return is_flag(e_planner_rule::NearbyWater); }
    inline bool needMeadow() const { return is_flag(e_planner_rule::Meadow); }
    inline bool needRiverAccess() const { return is_flag(e_planner_rule::RiverAccess); }
    inline bool needFloodplainShore() const { return is_flag(e_planner_rule::FloodplainShore); }
    inline bool needTrees() const { return is_flag(e_planner_rule::Trees); }
    inline bool needRock() const { return is_flag(e_planner_rule::Rock); }
    inline bool needOre() const { return is_flag(e_planner_rule::Ore); }
    inline bool needRoad() const { return is_flag(e_planner_rule::Road); }
    inline bool needIntersection() const { return is_flag(e_planner_rule::Intersection); }
    inline bool needFancyRoad() const { return is_flag(e_planner_rule::FancyRoad); }
    inline bool needWalls() const { return is_flag(e_planner_rule::Walls); }
    inline bool needCanals() const { return is_flag(e_planner_rule::Canals); }
    inline bool needResources() const { return is_flag(e_planner_rule::Resources); }
    inline bool ignoreNearbyEnemy() const { return is_flag(e_planner_rule::IgnoreNearbyEnemy); }
    inline bool draggable() const { return is_flag(e_planner_rule::Draggable); }
    inline bool needFerry() const { return is_flag(e_planner_rule::Ferry); }
    inline bool needBridge() const { return is_flag(e_planner_rule::Bridge); }
    inline bool needTempleUpgradeAltar() const { return is_flag(e_planner_rule::TempleUpgradeAltar); }
    inline bool needTempleUpgradeOracle() const { return is_flag(e_planner_rule::TempleUpgradeOracle); }

    int additional_req_param1 = -1;

    e_building_type build_type;
    building* last_created_building = nullptr;
    bool should_update_land_routing = false;
    bool in_progress;
    sbitarray64 rules;
    bool draw_as_constructing;
    tile2i start;
    tile2i end;
    int total_cost;
    int relative_orientation;
    int absolute_orientation;
    int custom_building_variant;
    int building_variant;
    vec2i size;
    vec2i pivot;

    tile2i north_tile;
    tile2i east_tile;
    tile2i south_tile;
    tile2i west_tile;

    int can_be_placed();

    void init();
    void reset();

private:
    void setup_build(e_building_type type);

public:
    void set_graphics_array(custom_span<int> image_set, vec2i size);

    void construction_start(tile2i tile);
    void construction_update(tile2i tile);
    bool construction_active() const { return build_type != BUILDING_NONE; }
    void construction_cancel();
    void construction_finalize();

    void add_building_tiles_from_list(int building_id, bool graphics_only);

    void update_orientations(bool check_if_changed = true);
    void construction_record_view_position(vec2i pixel, tile2i point);

    int get_total_drag_size(int* x, int* y);
    bool is_flag(e_planner_rule flag, int param1 = -1, int param2 = -1, int param3 = -1) const;

    void update(tile2i cursor_tile);
    void draw(painter &ctx);
    bool place();

    void set_tiles_building(int image_id, int size_xx);
    void update_tiles_building(int image_id);
    void init_tiles(int size_x, int size_y);

    static void draw_building_ghost(painter &ctx, int image_id, vec2i pixel, color color_mask = COLOR_MASK_GREEN);
    static void draw_flat_tile(painter &ctx, vec2i pixel, color color_mask);
    static void draw_flat_tile(vec2i pos, color color_mask, painter &ctx);
    static int is_blocked_for_building(tile2i tile, int size, blocked_tile_vec &blocked_tiles, uint32_t restricted_terrain = TERRAIN_ALL);
    static void draw_bridge(tile2i tile, vec2i pixel, int type, painter &ctx);
    static void draw_partially_blocked(painter &ctx, int fully_blocked, const blocked_tile_vec &blocked_tiles);
    static int tile_grid_offset(int x, int y);

    vec2i pixel_coord_offset(int row, int column) { return pixel_coords_cache[row][column]; }
    bool is_blocked_tile(int row, int column) { return tile_blocked_array[row][column]; }

    bool ghost_mark_deleting(tile2i tile);
    void next_building_variant();
    void setup_building_variant(tile2i tile, e_building_type type);
    void mark_construction(tile2i tile, vec2i size, int terrain, bool absolute_xy);
    void draw_tile_graphics_array(painter &ctx, tile2i start, tile2i end, vec2i pixel);

    bool attach_temple_upgrade(int upgrade_param, int grid_offset);
};

extern build_planner g_city_planner;
extern const vec2i VIEW_OFFSETS[];

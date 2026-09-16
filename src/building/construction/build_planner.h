#pragma once

#include "building/building.h"
#include "core/tokenum.h"
#include "graphics/color.h"
#include "graphics/view/view.h"
#include "grid/point.h"
#include "grid/terrain.h"

enum e_planner_rule : uint8_t {
    PLANNER_RULE_GROUNDWATER = 0,
    PLANNER_RULE_WATER = 1,
    PLANNER_RULE_NEARBY_WATER = 2,
    PLANNER_RULE_SHORELINE = 3,
    PLANNER_RULE_RIVER_ACCESS = 4,
    PLANNER_RULE_FLOODPLAIN_SHORE = 5,
    PLANNER_RULE_MEADOW = 6,
    PLANNER_RULE_TREES = 7,
    PLANNER_RULE_ROCK = 8,
    PLANNER_RULE_ORE = 9,
    PLANNER_RULE_ROAD = 10,
    PLANNER_RULE_INTERSECTION = 11,
    PLANNER_RULE_FANCY_ROAD = 12,
    PLANNER_RULE_WALLS = 13,
    PLANNER_RULE_CANALS = 14,
    PLANNER_RULE_UNUSED_15 = 15,
    PLANNER_RULE_RESERVED = 16,
    PLANNER_RULE_RESOURCES = 17,
    PLANNER_RULE_IGNORE_NEARBY_ENEMY = 18,
    PLANNER_RULE_UNUSED_19 = 19,
    PLANNER_RULE_UNUSED_20 = 20,
    PLANNER_RULE_DRAGGABLE = 21,
    PLANNER_RULE_FERRY = 22,
    PLANNER_RULE_BRIDGE = 23,
    PLANNER_RULE_TEMPLE_UPGRADE_ALTAR = 24,
    PLANNER_RULE_TEMPLE_UPGRADE_ORACLE = 25,

    PLANNER_RULE_MAX
};
using e_planner_rules_t = token_holder<e_planner_rule, PLANNER_RULE_GROUNDWATER, PLANNER_RULE_MAX>;
extern e_planner_rules_t e_planner_rules;

enum e_place_action {
    CAN_PLACE = 0,
    CAN_NOT_PLACE = 1,
    CAN_NOT_BUT_GREEN = 2,
};

struct event_building_change_mode {
    int16_t pack = 0;
    int16_t id = 0;
    int16_t offset = 0;
};

struct event_build_menu_submenu_changed {
    int submenu = 0;
};

struct event_building_menu_update { xstring stage; };
struct event_building_menu_changed { bool temp; };
struct event_use_building { int type = 0; bool en = false; };

class build_planner {
    // Large royal tomb footprint is 17×34 (bulk+entrance); keep headroom for rotation.
    static constexpr int TILE_DIM = 40;

    int tile_graphics_array[TILE_DIM][TILE_DIM] = {};
    int tile_sizes_array[TILE_DIM][TILE_DIM] = {};
    bool tile_blocked_array[TILE_DIM][TILE_DIM] = {};
    int tiles_blocked_total = 0;

    tile2i tile_coord_cache[TILE_DIM][TILE_DIM];
    vec2i pixel_coords_cache[TILE_DIM][TILE_DIM];

    int additional_req_param2 = -1;
    int additional_req_param3 = -1;
    int can_place = CAN_PLACE;

    xstring immediate_warning;
    xstring extra_warning;

    void set_graphics_row(int row, xspan<int> image_ids, int def);

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
    void draw_road_access_marker(painter &ctx);
    int place_houses(bool measure_only, int x_start, int y_start, int x_end, int y_end);

public:
    void set_warning(xstring warning) { immediate_warning = warning; }
    void set_extra_warning(xstring warning) { extra_warning = warning; }

    inline bool needGroundwater() const { return is_flag(PLANNER_RULE_GROUNDWATER); }
    inline bool needWater() const { return is_flag(PLANNER_RULE_WATER); }
    inline bool needShoreLine() const { return is_flag(PLANNER_RULE_SHORELINE); }
    inline bool needNearbyWater() const { return is_flag(PLANNER_RULE_NEARBY_WATER); }
    inline bool needMeadow() const { return is_flag(PLANNER_RULE_MEADOW); }
    inline bool needRiverAccess() const { return is_flag(PLANNER_RULE_RIVER_ACCESS); }
    inline bool needFloodplainShore() const { return is_flag(PLANNER_RULE_FLOODPLAIN_SHORE); }
    inline bool needTrees() const { return is_flag(PLANNER_RULE_TREES); }
    inline bool needRock() const { return is_flag(PLANNER_RULE_ROCK); }
    inline bool needOre() const { return is_flag(PLANNER_RULE_ORE); }
    inline bool needRoad() const { return is_flag(PLANNER_RULE_ROAD); }
    inline bool needIntersection() const { return is_flag(PLANNER_RULE_INTERSECTION); }
    inline bool needFancyRoad() const { return is_flag(PLANNER_RULE_FANCY_ROAD); }
    inline bool needWalls() const { return is_flag(PLANNER_RULE_WALLS); }
    inline bool needCanals() const { return is_flag(PLANNER_RULE_CANALS); }
    inline bool needResources() const { return is_flag(PLANNER_RULE_RESOURCES); }
    inline bool ignoreNearbyEnemy() const { return is_flag(PLANNER_RULE_IGNORE_NEARBY_ENEMY); }
    inline bool draggable() const { return is_flag(PLANNER_RULE_DRAGGABLE); }
    inline bool needFerry() const { return is_flag(PLANNER_RULE_FERRY); }
    inline bool needBridge() const { return is_flag(PLANNER_RULE_BRIDGE); }
    inline bool needTempleUpgradeAltar() const { return is_flag(PLANNER_RULE_TEMPLE_UPGRADE_ALTAR); }
    inline bool needTempleUpgradeOracle() const { return is_flag(PLANNER_RULE_TEMPLE_UPGRADE_ORACLE); }

    int additional_req_param1 = -1;

    e_building_type build_type;
    building* last_created_building = nullptr;
    bool should_update_land_routing = false;
    bool in_progress;
    sbitarray64 rules;
    bool draw_as_constructing;
    int construction_update_items = 0;
    int finalize_check_result = 0;
    int need_flag_result = 0;
    tile2i start;
    tile2i end;
    int total_cost;
    int global_rotation = 0;
    int road_orientation = 1;
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
    void set_graphics_array(xspan<int> image_set, vec2i size);

    void construction_start(tile2i tile);
    void construction_update(tile2i tile);
    bool construction_active() const { return build_type != BUILDING_NONE; }
    void construction_cancel(bool release_sidebar = true);
    void construction_finalize();

    void add_building_tiles_from_list(int building_id, bool graphics_only);

    void update_orientations(bool check_if_changed = true);

    int get_total_drag_size(int* x, int* y);
    bool is_flag(e_planner_rule flag, int param1 = -1, int param2 = -1, int param3 = -1) const;

    void update_preview(tile2i cursor_tile);
    void update_hover(tile2i cursor_tile);
    void update(tile2i cursor_tile);
    void draw(painter &ctx);
    bool place();

    void set_tiles_building(int image_id, int size_xx);
    void update_tiles_building(int image_id);
    void init_tiles(int size_x, int size_y);

    static void draw_building_ghost(painter &ctx, int image_id, vec2i pixel, color color_mask = COLOR_MASK_GREEN);
    static void draw_ghost_overlay(painter &ctx, int image_id, vec2i pixel);
    static void draw_from_below(painter &ctx, int image_id, vec2i pixel, color color_mask = COLOR_MASK_GREEN);
    static void draw_overlay_tile(painter &ctx, int image_id, vec2i pixel, color color_mask, float scale = 1.f);
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

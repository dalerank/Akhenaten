#include "build_planner.h"
#include "core/draw_phase.h"

#include <algorithm>
#include <cmath>

#include "grid/floodplain.h"
#include "core/log.h"

#include "building/building_dock.h"
#include "building/building_road.h"
#include "building/building_wall.h"
#include "building/monuments.h"
#include "building/monument_mastaba.h"
#include "building/building_plaza.h"
#include "building/building_garden.h"
#include "building/rotation.h"
#include "building/building_statue.h"
#include "building/building_booth.h"
#include "building/building_bandstand.h"
#include "building/building_pavilion.h"
#include "building/building_farm.h"
#include "building/building_fishing_wharf.h"
#include "building/building_festival_square.h"
#include "building/building_bridge.h"
#include "building/building_mansion.h"
#include "city/city_industry.h"
#include "building/building_ferry.h"
#include "building/building_fort.h"
#include "building/building.h"
#include "city/campaign_carry.h"
#include "building/building_temple_complex.h"
#include "city/buildings.h"
#include "city/city_buildings.h"
#include "city/city_finance.h"
#include "game/game_events.h"
#include "city/city_resource.h"
#include "city/city_warnings.h"
#include "building/construction/construction_warnings.h"
#include "clear.h"
#include "figure/formation_batalion.h"
#include "game/undo.h"
#include "grid/bridge.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/image.h"
#include "grid/orientation.h"
#include "grid/property.h"
#include "grid/routing/routing_terrain.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "grid/water.h"
#include "grid/figure.h"
#include "grid/road_access.h"
#include "grid/routing/routing.h"
#include "game/game_config.h"
#include "routed.h"
#include "city/city.h"
#include "js/js_register.h"
#include "core/profiler.h"
#include "scenario/scenario.h"

class build_planner_clear_land : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_CLEAR_LAND, build_planner_clear_land, building_impl)
};
REPLICATE_STATIC_PARAMS_FROM_CONFIG(build_planner_clear_land);

enum e_place_reservoir {
    PLACE_RESERVOIR_BLOCKED = -1,
    PLACE_RESERVOIR_NO = 0,
    PLACE_RESERVOIR_YES = 1,
    PLACE_RESERVOIR_EXISTS = 2
};

build_planner g_city_planner;

static void city_planner_subscribe_events() {
    g_city_planner.subscribe_events();
}
static events::session_subscriber g_city_planner_session(&city_planner_subscribe_events);

static int last_items_cleared;

static const vec2i FORT_OFFSET[4][4] = {{{3, -1}, {4, -1}, {4, 0}, {3, 0}},
                                        {{-1, -4}, {0, -4}, {0, -3}, {-1, -3}},
                                        {{-4, 0}, {-3, 0}, {-3, 1}, {-4, 1}},
                                        {{0, 3}, {1, 3}, {1, 4}, {0, 4}}};

const vec2i VIEW_OFFSETS[] = {                    {0, 0},
                                       {-30,15}, {30, 15}, {0,30},
                             {-60,30}, {60, 30}, {-30,45}, {30, 45}, {0,  60},
                  {-90, 45}, {90, 45}, {-60,60}, {60, 60}, {-30,75}, {30, 75},  {0, 90},
       {-120,60}, {120, 60}, {-90,75}, {90, 75}, {-60,90}, {60, 90}, {-30,105}, {30,105}, {0,120} };

#define MAX_TILES 25
const int TILE_GRID_OFFSETS_PH[4][MAX_TILES] = {
  {GRID_OFFSET(0, 0), GRID_OFFSET(0, 1), GRID_OFFSET(1, 0), GRID_OFFSET(1, 1), GRID_OFFSET(0, 2),
   GRID_OFFSET(2, 0), GRID_OFFSET(1, 2), GRID_OFFSET(2, 1), GRID_OFFSET(2, 2), GRID_OFFSET(0, 3),
   GRID_OFFSET(3, 0), GRID_OFFSET(1, 3), GRID_OFFSET(3, 1), GRID_OFFSET(2, 3), GRID_OFFSET(3, 2),
   GRID_OFFSET(3, 3), GRID_OFFSET(0, 4), GRID_OFFSET(4, 0), GRID_OFFSET(1, 4), GRID_OFFSET(4, 1),
   GRID_OFFSET(2, 4), GRID_OFFSET(4, 2), GRID_OFFSET(3, 4), GRID_OFFSET(4, 3), GRID_OFFSET(4, 4)},
  {GRID_OFFSET(0, 0),  GRID_OFFSET(-1, 0), GRID_OFFSET(0, 1),  GRID_OFFSET(-1, 1), GRID_OFFSET(-2, 0),
   GRID_OFFSET(0, 2),  GRID_OFFSET(-2, 1), GRID_OFFSET(-1, 2), GRID_OFFSET(-2, 2), GRID_OFFSET(-3, 0),
   GRID_OFFSET(0, 3),  GRID_OFFSET(-3, 1), GRID_OFFSET(-1, 3), GRID_OFFSET(-3, 2), GRID_OFFSET(-2, 3),
   GRID_OFFSET(-3, 3), GRID_OFFSET(-4, 0), GRID_OFFSET(0, 4),  GRID_OFFSET(-4, 1), GRID_OFFSET(-1, 4),
   GRID_OFFSET(-4, 2), GRID_OFFSET(-2, 4), GRID_OFFSET(-4, 3), GRID_OFFSET(-3, 4), GRID_OFFSET(-4, 4)},
  {GRID_OFFSET(0, 0),   GRID_OFFSET(0, -1),  GRID_OFFSET(-1, 0),  GRID_OFFSET(-1, -1), GRID_OFFSET(0, -2),
   GRID_OFFSET(-2, 0),  GRID_OFFSET(-1, -2), GRID_OFFSET(-2, -1), GRID_OFFSET(-2, -2), GRID_OFFSET(0, -3),
   GRID_OFFSET(-3, 0),  GRID_OFFSET(-1, -3), GRID_OFFSET(-3, -1), GRID_OFFSET(-2, -3), GRID_OFFSET(-3, -2),
   GRID_OFFSET(-3, -3), GRID_OFFSET(0, -4),  GRID_OFFSET(-4, 0),  GRID_OFFSET(-1, -4), GRID_OFFSET(-4, -1),
   GRID_OFFSET(-2, -4), GRID_OFFSET(-4, -2), GRID_OFFSET(-3, -4), GRID_OFFSET(-4, -3), GRID_OFFSET(-4, -4)},
  {GRID_OFFSET(0, 0),  GRID_OFFSET(1, 0),  GRID_OFFSET(0, -1), GRID_OFFSET(1, -1), GRID_OFFSET(2, 0),
   GRID_OFFSET(0, -2), GRID_OFFSET(2, -1), GRID_OFFSET(1, -2), GRID_OFFSET(2, -2), GRID_OFFSET(3, 0),
   GRID_OFFSET(0, -3), GRID_OFFSET(3, -1), GRID_OFFSET(1, -3), GRID_OFFSET(3, -2), GRID_OFFSET(2, -3),
   GRID_OFFSET(3, -3), GRID_OFFSET(4, 0),  GRID_OFFSET(0, -4), GRID_OFFSET(4, -1), GRID_OFFSET(1, -4),
   GRID_OFFSET(4, -2), GRID_OFFSET(2, -4), GRID_OFFSET(4, -3), GRID_OFFSET(3, -4), GRID_OFFSET(4, -4)},
};

bool build_planner::ghost_mark_deleting(tile2i tile) {
    draw_phase::check_write("build_planner");
    if (!game_features::gameui_visual_feedback_on_delete) {
        return false;
    }

    int construction_type = build_type;
    if (!tile.grid_offset() || draw_as_constructing || construction_type != BUILDING_CLEAR_LAND) {
        return (construction_type == BUILDING_CLEAR_LAND);
    }

    if (!in_progress) {
        map_property_clear_constructing_and_deleted();
    }

    map_building_tiles_mark_deleting(tile.grid_offset());
    return true;
}

void build_planner::mark_construction(tile2i tile, vec2i size, int terrain, bool absolute_xy) {
    if (g_city_planner.can_be_placed() == CAN_PLACE
        && map_building_tiles_mark_construction(tile, size.x, size.y, terrain, absolute_xy)) {
        g_city_planner.draw_as_constructing = true;
    }
}

int build_planner::place_houses(bool measure_only, int x_start, int y_start, int x_end, int y_end) {
    grid_area area = map_grid_get_area(tile2i(x_start, y_start), tile2i(x_end, y_end));

    int needs_road_warning = 0;
    int items_placed = 0;
    game_undo_restore_building_state();
    const auto &bparams = building_static_params::get(BUILDING_HOUSE_VACANT_LOT);
    int vacant_lot_id = bparams.first_img(animkeys().preview);
    for (int y = area.tmin_y, endy = area.tmax_y; y <= endy; y++) {
        for (int x = area.tmin_x, endx = area.tmax_x; x <= endx; x++) {
            int grid_offset = MAP_OFFSET(x, y);
            if (map_terrain_is(grid_offset, TERRAIN_NOT_CLEAR)
                || map_terrain_exists_tile_in_radius_with_type(tile2i(x, y), 1, 1, TERRAIN_FLOODPLAIN)) {
                continue;
            }

            if (measure_only) {
                map_property_mark_constructing(grid_offset);
                items_placed++;

            } else {
                if (g_city.animals.breeding_ground_at(tile2i(x, y), 1)) {
                    map_property_clear_constructing_and_deleted();
                    events::emit(event_city_warning{ "#cannot_build_over_animal_breeding_grounds" });
                } else {
                    building* b = building_create(BUILDING_HOUSE_VACANT_LOT, tile2i(x, y), 0);
                    game_undo_add_building(b);
                    if (b->id > 0) {
                        items_placed++;
                        tile2i otile(x, y);
                        map_building_tiles_add(b->id, otile, 1, vacant_lot_id, TERRAIN_BUILDING);
                        if (!map_terrain_exists_tile_in_radius_with_type(otile, 1, 2, TERRAIN_ROAD)) {
                            needs_road_warning = 1;
                        }
                    }
                }
            }
        }
    }

    if (!measure_only) {
        construction_warnings_check_house_plots();
        if (needs_road_warning) {
            events::emit(event_city_warning{ "#plots_too_far_from_road" });
        }

        map_routing_update_land();
    }
    return items_placed;
}

int build_planner::can_be_placed() {
    return can_place;
}

void build_planner::subscribe_events() {
    events::subscribe([this] (event_city_building_mode ev) {
        e_building_type btype = (e_building_type)ev.value;
        if (ev.value == BUILDING_NONE) {
            construction_cancel(false);
        }

        const bool enabled = scenario_building_allowed(btype);
        if (enabled) {
            construction_cancel(false);
            setup_build((e_building_type)ev.value);
        }
    });
}

void build_planner::reset() {
    // reset build info
    total_cost = 0;
    site_parts.clear();
    site_blocked = false;
    site_orientation = 0;
    ferry_placement = FERRY_PLACEMENT_NONE;
    ferry_first = 0;
    build_type = BUILDING_NONE;
    in_progress = false;
    draw_as_constructing = false;

    // set boundary size and reset pivot
    size = {0, 0};
    pivot = {0, 0};
    tiles_blocked_total = 0;

    // position and orientation
    start.set(-1, -1);
    end.set(-1, -1);
    global_rotation = 0;
    relative_orientation = 0;
    custom_building_variant = 0;
    building_variant = 0;

    // reset special requirements flags/params
    rules.zero();
    additional_req_param1 = -1;
    additional_req_param2 = -1;
    additional_req_param3 = -1;
    can_place = CAN_PLACE;
    immediate_warning = "";
    extra_warning = "";
}

void build_planner::init_tiles(int size_x, int size_y) {
    size.x = size_x;
    size.y = size_y;
    if (size.x > TILE_DIM || size.y > TILE_DIM) {
        logs::error("build_planner::init_tiles footprint %dx%d exceeds TILE_DIM=%d", size.x, size.y, TILE_DIM);
        size.x = std::min(size.x, TILE_DIM);
        size.y = std::min(size.y, TILE_DIM);
    }
    for (int row = 0; row < size.y; ++row) {
        for (int column = 0; column < size.x; ++column) {
            tile_graphics_array[row][column] = 0;
            tile_sizes_array[row][column] = 1; // reset tile size to 1 by default
            tile_blocked_array[row][column] = false;

            // reset caches
            tile_coord_cache[row][column] = {0, 0};
        }
    }
}

void build_planner::set_tile_size(int row, int column, int size) {
    if (row < 0 || column < 0 || row >= TILE_DIM || column >= TILE_DIM)
        return;
    tile_sizes_array[row][column] = size;
}

void build_planner::set_flag(e_planner_rule flags, int param1, int param2, int param3) {
    rules.set(flags, true);
    if (param1 != -1)
        additional_req_param1 = param1;

    if (param2 != -1)
        additional_req_param2 = param2;

    if (param3 != -1)
        additional_req_param3 = param3;
}

bool build_planner::is_flag(e_planner_rule flag, int param1, int param2, int param3) const {
    if (param1 != -1 && additional_req_param1 != param1)
        return false;

    if (param2 != -1 && additional_req_param2 != param2)
        return false;

    if (param3 != -1 && additional_req_param3 != param3)
        return false;

    return rules.is_set(flag);
}

void build_planner::set_graphics_row(int row, xspan<int> image_ids, int def) {
    if (row < 0) {
        return;
    }

    for (int i = 0; i < image_ids.size(); ++i) {
        if (row >= TILE_DIM || i >= TILE_DIM) {
            return;
        }

        const int image_id = image_ids[i];
        tile_graphics_array[row][i] = (image_id > 0 ? image_id : def);

        // set sizes automatically as default
        if (image_ids[i] > 0) {
            auto img = image_get(image_ids[i]);
            set_tile_size(row, i, img ? img->isometric_size() : 1);
        } else {
            set_tile_size(row, i, 1); // default size is 1
        }
    }
}

void build_planner::update_tiles_building(int image_id) {
    std::array<int, 10> empty_row = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    std::array<int, 10> draw_row = { image_id ? image_id : -1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    const int def = image_id ? 0 : -1;
    for (int row = 0; row < size.y; ++row) {
        if (row == size.y - 1)
            set_graphics_row(row, make_span(draw_row.data(), size.x), def);
        else
            set_graphics_row(row, make_span(empty_row.data(), size.x), def);
    }
}

void build_planner::set_tiles_building(int image_id, int size_xx) {
    init_tiles(size_xx, size_xx);
    update_tiles_building(image_id);
}

void build_planner::set_graphics_array(xspan<int> image_set, vec2i size) {
    init_tiles(size.x, size.y);
    // int (*image_array)[size_y][size_x] = (int(*)[size_y][size_x])image_set;

    // do it row by row...
    // for (int row = 0; row < size_y; ++row)
    //    set_graphics_row(row, (*image_array)[row], size_x);

    for (int row = 0; row < size.y; ++row) {
        set_graphics_row(row, make_span(& image_set[row * size.x], size.x), 0);
    }
}

void build_planner::setup_building_variant(tile2i tile, e_building_type type) {
    const auto& preview = placement_rules_of(type);
    int random_value = tile.grid_offset();
    custom_building_variant = preview.setup_building_variant(type, tile, random_value);
}

void build_planner::next_building_variant() {
    const auto& preview = placement_rules_of(build_type);
    custom_building_variant = preview.next_building_variant(build_type, end, custom_building_variant);
    update_orientations();
}

void build_planner::setup_build(e_building_type type) { // select building for construction, set up main terrain restrictions/requirements
    draw_phase::check_write("build_planner");
    building_ferry::placement_cancel(*this);
    reset();

    // ignore empty building types
    switch (type) {
    case BUILDING_NONE:
    case BUILDING_MENU_FARMS:
    case BUILDING_MENU_RAW_MATERIALS:
    case BUILDING_MENU_CONSTURCTION_GUILDS:
    case BUILDING_MENU_SHRINES:
    case BUILDING_MENU_TEMPLES:
    case BUILDING_MENU_TEMPLE_COMPLEX:
    case BUILDING_MENU_MONUMENTS:
    case BUILDING_MENU_DEFENSES:
    case BUILDING_MENU_FORTS:
    case BUILDING_MENU_WATER_CROSSINGS:
    case BUILDING_MENU_BEAUTIFICATION:
    case BUILDING_MENU_EDUCATION:
    case BUILDING_MENU_MUD_STRUCTURES:
    case BUILDING_MENU_BRICK_STRUCTURES:
    case BUILDING_MENU_VACANT_HOUSE:
    case BUILDING_MENU_CLEAR_LAND:
    case BUILDING_MENU_ROAD:
    case BUILDING_MENU_HEALTH:
    case BUILDING_MENU_RELIGION:
    case BUILDING_MENU_ENTERTAINMENT:
    case BUILDING_MENU_ADMINISTRATION:
    case BUILDING_MENU_SECURITY:
    case BUILDING_MENU_INDUSTRY:
    case BUILDING_MENU_GUILDS:
    case BUILDING_MENU_LARGE_TEMPLES:
    case BUILDING_MENU_FOOD:
    case BUILDING_MENU_DISTRIBUTION:
    case BUILDING_MENU_BRICK_DEFENSES:
    case BUILDING_MENU_DEFAULT:
        return;
    default:
        break;
    }

    build_type = type;

    events::emit(event_build_tool_selected{type});

    const auto &params = building_static_params::get(type);
    const auto& preview = placement_rules_of(type);
    preview.setup_build(*this);

    setup_building_variant(end, build_type);
    relative_orientation = preview.setup_orientation(relative_orientation); // force these buildings to start in a specific orientation
    update_orientations(false);

    // load building data
    setup_build_flags();
    setup_build_graphics();
}

void build_planner::setup_build_flags() {
    const auto &params = building_static_params::get(build_type);
    const auto& preview = placement_rules_of(build_type);

    for (const auto flag: e_planner_rules.values) {
        const bool is_need = preview.is_need_flag(*this, flag.id);
        if (is_need) {
            set_flag((e_planner_rule)flag.id);
        }
    }

    switch (build_type) {
    default:
        ; // nothing
        break;

    case BUILDING_MUD_TOWER:
    case BUILDING_BRICK_TOWER:
    case BUILDING_TOWER:
        set_flag(PLANNER_RULE_WALLS);
        break;

        //        case BUILDING_LIBRARY: // TODO
        //            set_requirements(PlannerReqs::Resources, RESOURCE_PAPYRUS, 300);
        //            break;
        // Obelisk granite pre-stock is handled in building_obelisk::preview
        // (placement_resources from JS config) — not via the removed set_requirements API.

    case BUILDING_LOW_BRIDGE:
    case BUILDING_UNUSED_SHIP_BRIDGE_83:
        set_flag(PLANNER_RULE_BRIDGE);
        break;

    case BUILDING_ROAD:
        set_flag(PLANNER_RULE_ROAD, false);
        break;

    case BUILDING_MUD_GATEHOUSE:
    case BUILDING_MUD_GATEHOUSE_UP:
    case BUILDING_BRICK_GATEHOUSE:
    case BUILDING_BRICK_GATEHOUSE_UP:
    case BUILDING_GATEHOUSE:
    case BUILDING_DECORATIVE_GATEHOUSE:
        set_flag(PLANNER_RULE_ROAD, false);
        break;

    case BUILDING_ROADBLOCK:
        set_warning("#only_build_roadblocks_on_roads");
        set_flag(PLANNER_RULE_ROAD, true);
        break;

    case BUILDING_PLAZA:
        set_flag(PLANNER_RULE_ROAD, true);
        set_flag(PLANNER_RULE_FANCY_ROAD);
        break;

    case BUILDING_BOOTH:
        set_warning("#entertainment_venue_at_intersection");
        set_flag(PLANNER_RULE_INTERSECTION, 0);
        break;

    case BUILDING_BANDSTAND:
        set_warning("#entertainment_venue_at_intersection");
        set_flag(PLANNER_RULE_INTERSECTION, 1);
        break;

    case BUILDING_PAVILLION:
        set_warning("#entertainment_venue_at_intersection");
        set_flag(PLANNER_RULE_INTERSECTION, 2);
        break;

    case BUILDING_FESTIVAL_SQUARE:
        set_warning("#entertainment_venue_at_intersection");
        set_flag(PLANNER_RULE_INTERSECTION, 3);
        break;

    case BUILDING_CLEAR_LAND:
        set_flag(PLANNER_RULE_IGNORE_NEARBY_ENEMY);
        break;
    }

    if (params.planner_update_rule.is_draggable) {
        set_flag(PLANNER_RULE_DRAGGABLE);
    }
}

void build_planner::setup_build_graphics() {
    const auto& preview = placement_rules_of(build_type);
    preview.setup_preview_graphics(*this);
}

void build_planner::update_tile_caches() {
    if (size.x < 1 || size.y < 1) {
        return;
    }
    int orientation = map_view_orientation() / 2;
    for (int row = 0; row < size.y; row++) {
        for (int column = 0; column < size.x; column++) {
            // get tile offset
            int x_offset = (column - pivot.x);
            int y_offset = (row - pivot.y);

            // get abs. tile
            tile2i tile;
            switch (orientation) {
            case 0:
                tile = end.shifted(x_offset, y_offset);
                break;
            case 1:
                tile = end.shifted(-y_offset, x_offset);
                break;
            case 2:
                tile = end.shifted(-x_offset, -y_offset);
                break;
            case 3:
                tile = end.shifted(y_offset, -x_offset);
                break;
            }

            tile_coord_cache[row][column] = tile;
        }
    }
    switch (orientation) {
    case 0: // north
        north_tile = tile_coord_cache[0][0];
        east_tile = tile_coord_cache[0][size.x - 1];
        south_tile = tile_coord_cache[size.y - 1][size.x - 1];
        west_tile = tile_coord_cache[size.y - 1][0];
        break;
    case 1: // east
        north_tile = tile_coord_cache[size.y - 1][0];
        east_tile = tile_coord_cache[0][0];
        south_tile = tile_coord_cache[0][size.x - 1];
        west_tile = tile_coord_cache[size.y - 1][size.x - 1];
        break;
    case 2: // south
        north_tile = tile_coord_cache[size.y - 1][size.x - 1];
        east_tile = tile_coord_cache[size.y - 1][0];
        south_tile = tile_coord_cache[0][0];
        west_tile = tile_coord_cache[0][size.x - 1];
        break;
    case 3: // west
        north_tile = tile_coord_cache[0][size.x - 1];
        east_tile = tile_coord_cache[size.y - 1][size.x - 1];
        south_tile = tile_coord_cache[size.y - 1][0];
        west_tile = tile_coord_cache[0][0];
        break;
    }
}

void build_planner::update_orientations(bool check_if_changed) {
    int prev_orientation = relative_orientation;
    int prev_variant = building_variant;
   //int global_rotation = building_rotation_global_rotation();

    const auto& preview = placement_rules_of(build_type);

    relative_orientation = preview.update_relative_orientation(*this, end, relative_orientation);
    relative_orientation = relative_orientation % 4;
    // Absolute must be fresh before variant: temple (and others) derive variant from it.
    absolute_orientation = map_view_absolute_orientation(relative_orientation);
    building_variant = preview.update_building_variant(*this);

    // do not refresh graphics if nothing changed
    if (check_if_changed && relative_orientation == prev_orientation && building_variant == prev_variant) {
        return;
    }

    setup_build_graphics(); // reload graphics, tiles, etc.
    update_tile_caches();   // refresh caches
}

void build_planner::dispatch_warnings() {
    if (!!immediate_warning) {
        events::emit(event_city_warning{ immediate_warning });
    }

    if (!!extra_warning) {
        events::emit(event_city_warning{ extra_warning });
    }
}

int build_planner::get_total_drag_size(int* x, int* y) {
    if (!game_features::gameui_show_construction_size || !draggable()
        || (build_type != BUILDING_CLEAR_LAND && !total_cost)) {
        return 0;
    }
    int size_x = end.x() - start.x();
    int size_y = end.y() - start.y();
    if (size_x < 0)
        size_x = -size_x;

    if (size_y < 0)
        size_y = -size_y;

    size_x++;
    size_y++;
    *x = size_x;
    *y = size_y;
    return 1;
}

void build_planner::construction_start(tile2i tile) {
    draw_phase::check_write("build_planner");
    if (!tile.valid()) {
        return;
    }

    if (in_progress) {
        return;
    }

    start = tile;
    end = tile;

    const auto& preview = placement_rules_of(build_type);
    if (game_undo_start_build(build_type)) {
        in_progress = true;
        const bool can_start = preview.can_construction_start(*this, start);

        if (!can_start) {
            construction_cancel(false);
        }
    }
}

void build_planner::construction_cancel(bool release_sidebar) {
    draw_phase::check_write("build_planner");
    map_property_clear_constructing_and_deleted();
    if (in_progress && draggable()) {
        game_undo_restore_map(1);
        in_progress = false;
    } else {
        setup_build(BUILDING_NONE);
        if (release_sidebar) {
            events::emit(event_build_menu_submenu_changed{ 0 });
        }
    }

    custom_building_variant = 0;
    global_rotation = 0;
    update_orientations();
}

void build_planner::construction_update(tile2i tile) {
    draw_phase::check_write("build_planner");
    end = tile;
    if (!end.valid()) {
        return;
    }

    if (!build_type || finance_system::is_out_of_money(g_city.finance)) {
        total_cost = 0;
        return;
    }

    map_property_clear_constructing_and_deleted();
    uint16_t current_cost = building_static_params::get(build_type).get_cost();
    int items_placed = 1;

    const auto &params = building_static_params::get(build_type);
    const auto& preview = placement_rules_of(build_type);
    switch (build_type) {
    case BUILDING_CLEAR_LAND:
        last_items_cleared = building_construction_clear_land(true, start, end);
        items_placed = last_items_cleared;
        break;

    case BUILDING_LOW_BRIDGE:
    case BUILDING_UNUSED_SHIP_BRIDGE_83: {
        const bool is_ship = (build_type == BUILDING_UNUSED_SHIP_BRIDGE_83);
        int length = 0;
        int direction = 0;
        map_bridge_calculate_length_direction(end.x(), end.y(), &length, &direction, is_ship);
        items_placed = map_bridge_building_length();
        break;
    }

    case BUILDING_HOUSE_VACANT_LOT:
        items_placed = place_houses(true, start.x(), start.y(), end.x(), end.y());
        break;

    case BUILDING_RESERVED_TRIUMPHAL_ARCH_56:
        mark_construction(tile, { 3, 3 }, ~TERRAIN_ROAD, false);
        break;

    case BUILDING_FORT_ARCHERS:
    case BUILDING_FORT_CHARIOTEERS:
    case BUILDING_FORT_INFANTRY:
        if (g_formations.num_batalions < formation_get_max_forts()) {
            vec2i offset = FORT_OFFSET[building_fort::placement_rotation()][map_view_orientation() / 2];
            tile2i ground = tile.shifted(offset.x, offset.y);
            if (map_building_tiles_are_clear(tile, 3, TERRAIN_ALL)
                && map_building_tiles_are_clear(ground, 4, TERRAIN_ALL)) {
                mark_construction(tile, { 3, 3 }, TERRAIN_ALL, false);
            }
        }
        break;

    default:
        items_placed = preview.construction_update(*this, start, end);
    }

    if (items_placed >= 0) {
        current_cost *= items_placed;
    }

    total_cost = current_cost;
}

void build_planner::checks_generic_rules(building* b) {
    if (!b || !b->is_valid()) {
        return;
    }

    construction_warnings_check_site(*b);
    b->dcast()->on_place_checks();
    construction_warnings_check_road_access(*b);
}

void build_planner::construction_finalize() { // confirm final placement
    draw_phase::check_write("build_planner");
    logs::info("[build-btn] finalize enter type=%d start=%d(%d,%d) end=%d(%d,%d) can_place=%d cost=%d",
               (int)build_type, start.grid_offset(), start.x(), start.y(), end.grid_offset(), end.x(), end.y(),
               (int)can_place, total_cost);

    in_progress = false;

    const auto& preview = placement_rules_of(build_type);
    const auto &params = building_static_params::get(build_type);
    can_place = preview.finalize_check(*this, start, end, can_place);

    if (can_place != CAN_PLACE && !params.planner_update_rule.is_draggable) { // this is the FINAL check!
        logs::info("[build-btn] finalize abort: can_place=%d (not draggable)", (int)can_place);
        dispatch_warnings();
        return;
    }

    // attempt placing, restore terrain data on failure
    if (!place()) {
        logs::info("[build-btn] finalize place() FAILED type=%d cost=%d", (int)build_type, total_cost);
        map_property_clear_constructing_and_deleted();
        if (building_type_any_of(build_type,
                {BUILDING_MUD_WALL, BUILDING_BRICK_WALL, BUILDING_WALL, BUILDING_ROAD, BUILDING_IRRIGATION_DITCH,
                    BUILDING_DIKE})) {
            game_undo_restore_map(0);
        } else if (build_type == BUILDING_PLAZA || build_type == BUILDING_GARDENS) {
            game_undo_restore_map(1);
        } else if (build_type == BUILDING_LOW_BRIDGE || build_type == BUILDING_UNUSED_SHIP_BRIDGE_83) {
            map_bridge_reset_building_length();
        }

        dispatch_warnings();
        return;
    }

    logs::info("[build-btn] finalize place() OK type=%d cost=%d end=%d(%d,%d)", (int)build_type, total_cost,
               end.grid_offset(), end.x(), end.y());

    checks_generic_rules(last_created_building);
    bool should_recalc_ferry_routes = params.needs.shoreline;
    total_cost = preview.finalize_cost(*this, total_cost);

    setup_building_variant(end, build_type);
    update_orientations(false);

    // update terrain data for certain special cases
    if (needMeadow()) {
        for (int y = end.y(); y < end.y() + size.y; y++) {
            for (int x = end.x(); x < end.x() + size.x; x++) {
                map_set_floodplain_growth(MAP_OFFSET(x, y), 0);
            }
        }
    }

    if (needRoad()) {
        map_terrain_add_in_area(end, end.shifted(size.x - 1, size.y - 1), TERRAIN_ROAD);
        map_tiles_update_area_roads(end.x(), end.y(), 5);
        map_tiles_update_all_plazas();
    }

    if (needWalls()) {
        events::emit(event_building_update_walls{ end, 5 });
    }

    // consume resources for specific buildings (e.g. marble, granite)
    if (needResources()) {
        events::emit(event_storageyards_remove_resource{ (e_resource)additional_req_param1, additional_req_param2 });
    }

    // finally, go over the rest of the stuff for all building types
    formation_move_herds_away(end);
    events::emit(event_finance_request{efinance_request_construction, total_cost });
    game_undo_finish_build(total_cost);
    map_tiles_update_region_empty_land(false, start.shifted(-3, -3), end.shifted(size.x + 3, size.y + 3));
    map_routing_update_land();
    map_routing_update_walls();

    if (should_recalc_ferry_routes) {
        building_ferry::update_routes();
    }
}

//////////////////////

void build_planner::update_preview(tile2i cursor_tile) {
    OZZY_PROFILER_FUNCTION();
    if (!build_type) {
        return;
    }

    if (!cursor_tile.valid()) {
        return;
    }

    end = cursor_tile;
    update_tile_caches();
    site_parts.clear();
    site_blocked = false;
    site_orientation = 0;
    placement_rules_of(build_type).collect_site(*this, end);

    immediate_warning = "";
    extra_warning = "";
    can_place = CAN_PLACE;
    if (!needBridge()) {
        update_obstructions_check();
    }
    update_requirements_check();
    update_special_case_orientations_check();
    update_unique_only_one_check();

    if (needBridge()) {
        const bool is_ship = (build_type == BUILDING_UNUSED_SHIP_BRIDGE_83);
        int length = 0;
        int direction = 0;
        int end_offset = map_bridge_calculate_length_direction(end.x(), end.y(), &length, &direction, is_ship);
        const auto &params = building_static_params::get(build_type);
        const int min_length = bridge_span_min_length(is_ship);
        const int max_length = bridge_span_max_length(is_ship);
        const bool blocked = !end_offset || length < min_length || length > max_length
                             || finance_system::is_out_of_money(g_city.finance);
        can_place = blocked ? CAN_NOT_PLACE : CAN_PLACE;
        total_cost = blocked ? 0 : (int)params.get_cost() * length;
    }
}

void build_planner::update_hover(tile2i cursor_tile) {
    if (in_progress) {
        return;
    }

    update_preview(cursor_tile);
}

void build_planner::update(tile2i cursor_tile) {
    draw_phase::check_write("build_planner");
    update_preview(cursor_tile);

    if (in_progress && draggable()) {
        construction_update(end);
    }
}

int build_planner::is_blocked_for_building(tile2i tile, int size, blocked_tile_vec &blocked_tiles, uint32_t restricted_terrain) {
    // TILE_GRID_OFFSETS_PH is only 5×5. Indexing it with size*size for a 6×6 (sphinx
    // part) reads off the end and paints tiles that are not in the footprint.
    // blocked_tile_vec holds 36, so 6×6 is the largest square that fits.
    if (size < 1) {
        return 0;
    }
    if (size > 6) {
        size = 6;
    }

    const int orientation_index = map_view_orientation() / 2;
    int blocked = 0;
    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            int sx = dx;
            int sy = dy;
            switch (orientation_index) {
            case 1:
                sx = -dx;
                break;
            case 2:
                sx = -dx;
                sy = -dy;
                break;
            case 3:
                sy = -dy;
                break;
            default:
                break;
            }

            tile2i check_tile = tile.shifted(sx, sy);
            bool tile_blocked = map_terrain_is(check_tile, restricted_terrain & TERRAIN_NOT_CLEAR)
                || (map_terrain_count_directly_adjacent_with_type(check_tile, TERRAIN_FLOODPLAIN) > 0)
                || (map_terrain_count_diagonally_adjacent_with_type(check_tile, TERRAIN_FLOODPLAIN) > 0)
                || map_has_figure_at(check_tile);

            blocked_tiles.push_back({ check_tile, tile_blocked });
            blocked += (tile_blocked ? 1 : 0);
        }
    }

    return blocked;
}

int build_planner::tile_grid_offset(int orientation, int y) {
    return TILE_GRID_OFFSETS_PH[orientation][y];
}

bool build_planner::place() {
    if (end == tile2i(-1, -1)) {
        return false;
    }

    // for debugging...
    logs::info("Attempting to place at: %03i %03i %06i", end.x(), end.y(), end.grid_offset());

    // Check warnings for placement and create building/update tiles accordingly.
    // Some of the buildings below have specific warning messages (e.g. roadblocks)
    // that can't be easily put in `building_construction_can_place_on_terrain()`!
    const auto &params = building_static_params::get(build_type);
    const auto& preview = placement_rules_of(build_type);
    int placement_cost = params.get_cost();
    last_created_building = nullptr;

    switch (build_type) {
    case BUILDING_CLEAR_LAND: {
            // BUG in original (keep this behaviour): if confirmation has to be asked (bridge/fort),
            // the previous cost is deducted from treasury and if user chooses 'no', they still pay for removal.
            // If we don't do it this way, the user doesn't pay for the removal at all since we don't come back
            // here when the user says yes.
            int items_placed = building_construction_clear_land(false, start, end);
            if (items_placed < 0)
                items_placed = last_items_cleared;
            placement_cost *= items_placed;
            map_property_clear_constructing_and_deleted();
            total_cost = placement_cost;
            // Unit cost may be 0 in config; still finish undo when something was cleared.
            return items_placed > 0;
        }

    case BUILDING_LOW_BRIDGE:
    case BUILDING_UNUSED_SHIP_BRIDGE_83: {
        const bool is_ship = (build_type == BUILDING_UNUSED_SHIP_BRIDGE_83);
        int length = 0;
        int direction = 0;
        map_bridge_calculate_length_direction(end.x(), end.y(), &length, &direction, is_ship);
        const int placed = map_bridge_add(end.x(), end.y(), is_ship);
        placement_cost *= placed;
        if (placed < 2) {
            events::emit(event_city_warning{"#scout_along_river_for_site"});
            return false;
        }
        break;
    }

    case BUILDING_HOUSE_VACANT_LOT:
        placement_cost *= place_houses(false, start.x(), start.y(), end.x(), end.y());
        if (placement_cost == 0) {
            events::emit(event_city_warning{ "#must_build_on_cleared_land" });
            return false;
        }
        break;

    case BUILDING_NONE:
        return false;

    default:
        {
            if (params.building_size <= 0) {
                construction_cancel(false);
                return false;
            }

            int construction_placed = preview.construction_place(*this, start, end, absolute_orientation, building_variant);
            if (construction_placed == 0) {
                return false;
            }

            placement_cost *= construction_placed;
        }
        break;
    }

    if (should_update_land_routing) {
        map_routing_update_land();
        should_update_land_routing = false;
    }

    total_cost = placement_cost;
    // Free buildings (OG cost 0: sphinx, royal tombs) still placed something on the default path.
    if (total_cost == 0 && params.get_cost() != 0) {
        return false;
    }

    // CO2b: OG-style — building anything except a land fort drops pending troop carry.
    if (!campaign_carry_is_fort_building(build_type)) {
        g_campaign_carry.expire_pending_troops();
    }

    return true;
}

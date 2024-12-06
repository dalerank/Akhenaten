#include "build_planner.h"

#include "figure/formation_herd.h"
#include "graphics/view/lookup.h"
#include "grid/floodplain.h"
#include "core/log.h"
#include "widget/widget_sidebar.h"

#include "building/building_dock.h"
#include "building/building_menu.h"
#include "building/count.h"
#include "building/model.h"
#include "building/monuments.h"
#include "building/monument_mastaba.h"
#include "building/building_plaza.h"
#include "building/building_garden.h"
#include "building/rotation.h"
#include "building/building_statue.h"
#include "building/building_storage_yard.h"
#include "building/building_road.h"
#include "city/buildings.h"
#include "city/city_buildings.h"
#include "city/finance.h"
#include "city/city_resource.h"
#include "city/warnings.h"
#include "clear.h"
#include "figure/formation_legion.h"
#include "game/undo.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/window.h"
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
#include "config/config.h"
#include "routed.h"
#include "city/city.h"

enum e_place_reservoir {
    PLACE_RESERVOIR_BLOCKED = -1,
    PLACE_RESERVOIR_NO = 0,
    PLACE_RESERVOIR_YES = 1,
    PLACE_RESERVOIR_EXISTS = 2
};

BuildPlanner Planner;

static int last_items_cleared;

static const vec2i FORT_OFFSET[4][4] = {{{3, -1}, {4, -1}, {4, 0}, {3, 0}}, 
                                        {{-1, -4}, {0, -4}, {0, -3}, {-1, -3}}, 
                                        {{-4, 0}, {-3, 0}, {-3, 1}, {4, 1}}, 
                                        {{0, 3}, {1, 3}, {1, 4}, {0, 4}}};

void BuildPlanner::add_building_tiles_from_list(int building_id, bool graphics_only) {
    for (int row = 0; row < size.y; ++row) {
        for (int column = 0; column < size.x; ++column) {
            int image_id = tile_graphics_array[row][column];
            int size = tile_sizes_array[row][column];
            tile2i tile = tile_coord_cache[row][column];

            // correct for city orientation
            switch (city_view_orientation() / 2) {
            case 0: tile.shift(0, -size + 1); break;
            case 1: break;
            case 2: tile.shift(-size + 1, 0); break;
            case 3: tile.shift(-size + 1, -size + 1); break;
            }

            if (image_id > 0 && size > 0) {
                if (!graphics_only) {
                    map_building_tiles_add(building_id, tile, size, image_id, TERRAIN_BUILDING);
                } else {
                    map_image_set(tile.grid_offset(), image_id);
                }
            }
        }
    }
}

static building* add_temple_complex_element(int x, int y, int orientation, building* prev) {
    building* b = building_create(prev->type, tile2i(x, y), orientation);
    game_undo_add_building(b);

    b->size = 3;
    b->prev_part_building_id = prev->id;
    prev->next_part_building_id = b->id;
    int image_id = map_image_at(MAP_OFFSET(x, y));
    map_building_tiles_add(b->id, b->tile, 3, image_id, TERRAIN_BUILDING);

    return b;
}

static void add_temple_complex(building* b, int orientation) {
    Planner.add_building_tiles_from_list(b->id, false);
    tile2i offset = {0, 0};
    switch (orientation) {
    case 0:
        offset = {0, -3};
        break;
    case 1:
        offset = {3, 0};
        break;
    case 2:
        offset = {0, 3};
        break;
    case 3:
        offset = {-3, 0};
        break;
    }
    building* altar = add_temple_complex_element(b->tile.x() + offset.x(), b->tile.y() + offset.y(), orientation, b);
    building* oracle = add_temple_complex_element(b->tile.x() + 2 * offset.x(), b->tile.y() + 2 * offset.y(), orientation, altar);
}

void build_planner_latch_on_venue(e_building_type type, building *b, int dx, int dy, int orientation, bool main_venue) {
    tile2i point = b->tile.shifted(dx, dy);
    // set map graphics accordingly

    const auto &params = b->dcast()->params();
    switch (type) {
    case BUILDING_GARDENS:
        map_terrain_add(point, TERRAIN_GARDEN);
        map_tiles_update_all_gardens();
        break;

    case BUILDING_BOOTH: {
           int booth = params.anim["booth"].first_img();
           map_image_set(point, booth);
        }
        break;

    case BUILDING_BANDSTAND:
        if (main_venue) {
            int stand_sn_s = params.anim["stand_sn_s"].first_img();
            b->data.entertainment.latched_venue_main_grid_offset = point.grid_offset();
            int offset = map_bandstand_main_img_offset(orientation);
            map_image_set(point, stand_sn_s + offset);
        } else {
            int stand_sn_s = params.anim["stand_sn_s"].first_img();
            b->data.entertainment.latched_venue_add_grid_offset = point.grid_offset();
            int offset = map_bandstand_add_img_offset(orientation);
            map_image_set(point, stand_sn_s + offset);
        }
        break;

    case BUILDING_PAVILLION: {
            int base_id = params.anim["base"].first_img();
            map_building_tiles_add(b->id, point, 2, base_id, TERRAIN_BUILDING);
        }
        break;
    }
}

static void add_building_tiles_image(building* b, int image_id) {
    map_building_tiles_add(b->id, b->tile, b->size, image_id, TERRAIN_BUILDING);
}

static void add_building(building* b, int orientation, int variant) {
    int orientation_rel = city_view_relative_orientation(orientation);
    const auto &params = b->dcast()->params();
    switch (b->type) {
    // houses
    case BUILDING_HOUSE_STURDY_HUT:
    case BUILDING_HOUSE_MEAGER_SHANTY:
    case BUILDING_HOUSE_COMMON_SHANTY:
    case BUILDING_HOUSE_ROUGH_COTTAGE:
    case BUILDING_HOUSE_ORDINARY_COTTAGE:
    case BUILDING_HOUSE_MODEST_HOMESTEAD:
    case BUILDING_HOUSE_SPACIOUS_HOMESTEAD:
    case BUILDING_HOUSE_MODEST_APARTMENT:
    case BUILDING_HOUSE_SPACIOUS_APARTMENT:
    case BUILDING_HOUSE_COMMON_RESIDENCE:
    case BUILDING_HOUSE_SPACIOUS_RESIDENCE:
    case BUILDING_HOUSE_ELEGANT_RESIDENCE:
    case BUILDING_HOUSE_FANCY_RESIDENCE:
    case BUILDING_HOUSE_COMMON_MANOR:
    case BUILDING_HOUSE_SPACIOUS_MANOR:
    case BUILDING_HOUSE_ELEGANT_MANOR:
    case BUILDING_HOUSE_STATELY_MANOR:
    case BUILDING_HOUSE_MODEST_ESTATE:
    case BUILDING_HOUSE_PALATIAL_ESTATE:
        add_building_tiles_image(b, params.anim["house"].first_img());
        break;

        // government
    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
    case BUILDING_TEMPLE_COMPLEX_RA:
    case BUILDING_TEMPLE_COMPLEX_PTAH:
    case BUILDING_TEMPLE_COMPLEX_SETH:
    case BUILDING_TEMPLE_COMPLEX_BAST:
        add_temple_complex(b, orientation);
        break;

    case BUILDING_RESERVED_TRIUMPHAL_ARCH_56:
        add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_TRIUMPHAL_ARCH) + orientation - 1);
        map_terrain_add_triumphal_arch_roads(b->tile.x(), b->tile.y(), orientation);
        city_buildings_build_triumphal_arch();
        Planner.reset();
        break;

    default:
        b->dcast()->on_place(orientation, variant);
        break;
    }
}

static void mark_construction(tile2i tile, int size_x, int size_y, int terrain, bool absolute_xy) {
    if (Planner.can_be_placed() == CAN_PLACE
        && map_building_tiles_mark_construction(tile, size_x, size_y, terrain, absolute_xy)) {
        Planner.draw_as_constructing = true;
    }
}

static int has_nearby_enemy(int x_start, int y_start, int x_end, int y_end) {
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure* f = figure_get(i);
        if (config_get(CONFIG_GP_CH_WOLVES_BLOCK)) {
            if (f->state != FIGURE_STATE_ALIVE || !f->is_enemy()) {
                continue;
            }

        } else if (f->state != FIGURE_STATE_ALIVE || !f->is_enemy()) {
            continue;
        }

        int tile_x = f->tile.x();
        int tile_y = f->tile.y();
        int dx = (tile_x > x_start) ? (tile_x - x_start) : (x_start - tile_x);
        int dy = (tile_y > y_start) ? (tile_y - y_start) : (y_start - tile_y);
        if (dx <= 12 && dy <= 12) {
            return 1;
        }

        dx = (tile_x > x_end) ? (tile_x - x_end) : (x_end - tile_x);
        dy = (tile_y > y_end) ? (tile_y - y_end) : (y_end - tile_y);
        if (dx <= 12 && dy <= 12) {
            return 1;
        }
    }
    return 0;
}

static int place_houses(bool measure_only, int x_start, int y_start, int x_end, int y_end) {
    grid_area area = map_grid_get_area(tile2i(x_start, y_start), tile2i(x_end, y_end));

    int needs_road_warning = 0;
    int items_placed = 0;
    game_undo_restore_building_state();
    int vacant_lot_id = building_impl::params(BUILDING_HOUSE_VACANT_LOT).anim["preview"].first_img();
    for (int y = area.tmin.y(), endy = area.tmax.y(); y <= endy; y++) {
        for (int x = area.tmin.x(), endx = area.tmax.x(); x <= endx; x++) {
            int grid_offset = MAP_OFFSET(x, y);
            if (map_terrain_is(grid_offset, TERRAIN_NOT_CLEAR)
                || map_terrain_exists_tile_in_radius_with_type(tile2i(x, y), 1, 1, TERRAIN_FLOODPLAIN)) {
                continue;
            }

            if (measure_only) {
                map_property_mark_constructing(grid_offset);
                items_placed++;

            } else {
                if (formation_herd_breeding_ground_at(x, y, 1)) {
                    map_property_clear_constructing_and_deleted();
                    city_warning_show(WARNING_HERD_BREEDING_GROUNDS);
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
        //building_construction_warning_check_food_stocks(BUILDING_HOUSE_VACANT_LOT);
        if (needs_road_warning) {
            city_warning_show(WARNING_HOUSE_TOO_FAR_FROM_ROAD);
        }

        map_routing_update_land();
    }
    return items_placed;
}


bool BuildPlanner::place_building(e_building_type type, tile2i tile, int orientation, int variant) {
    // by default, get size from building's properties
    int size = building_impl::params(type).building_size;
    assert(size > 0);

    // correct building placement for city orientations
    switch (city_view_orientation()) {
    case DIR_2_BOTTOM_RIGHT:
        tile = tile.shifted(-size + 1, 0);
        break;

    case DIR_4_BOTTOM_LEFT:
        tile = tile.shifted(-size + 1, -size + 1);
        break;

    case DIR_6_TOP_LEFT:
        tile = tile.shifted(0, -size + 1);
        break;
    }

    // create building
    last_created_building = nullptr;
    building* b = building_create(type, tile, orientation);
    game_undo_add_building(b);
    if (b->id <= 0) { // building creation failed????
        return false;
    }
    
    add_building(b, orientation, variant);
    last_created_building = b;
    return true;
}

static bool attach_temple_upgrade(int upgrade_param, int grid_offset) {
    building* target = building_at(grid_offset)->main();
    if (!building_at(grid_offset) || !building_is_large_temple(target->type)) {
        return false;
    }

    if (target->data.monuments.temple_complex_attachments & upgrade_param) {
        return false;
    }

    target->data.monuments.temple_complex_attachments |= upgrade_param;
    map_building_tiles_add_temple_complex_parts(target);
    building_menu_update_temple_complexes();
    return true;
}

static tile2i temple_complex_part_target(building* main, int part) {
    building* b = main;
    if (part == 1) {
        b = b->next();
    } else if (part == 2) {
       // b = get_temple_complex_front_facing_part(main);
    }

    int x = b->tile.x();
    int y = b->tile.y();
    switch (city_view_orientation() / 2) {
    case 1:  x += 2; break; // east
    case 2:  x += 2; y += 2; break; // south
    case 3:  y += 2; break; // west
    }
    return tile2i(x, y);
}

//////////////////////

int BuildPlanner::can_be_placed() {
    return can_place;
}

void BuildPlanner::reset() {
    // reset build info
    total_cost = 0;
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
    relative_orientation = 0;
    variant = 0;

    // reset special requirements flags/params
    special_flags = 0;
    additional_req_param1 = -1;
    additional_req_param2 = -1;
    additional_req_param3 = -1;
    can_place = CAN_PLACE;
    immediate_warning_id = -1;
    extra_warning_id = -1;
}

void BuildPlanner::init_tiles(int size_x, int size_y) {
    size.x = size_x;
    size.y = size_y;
    for (int row = 0; row < size.y; ++row) {
        for (int column = 0; column < size.x; ++column) {
            if (column > 29 || row > 29)
                return;

            tile_graphics_array[row][column] = 0;
            tile_sizes_array[row][column] = 1; // reset tile size to 1 by default
            tile_blocked_array[row][column] = false;

            // reset caches
            tile_coord_cache[row][column] = {0, 0};
            pixel_coords_cache[row][column] = {0, 0};
        }
    }
}

void BuildPlanner::set_tile_size(int row, int column, int size) {
    if (row > 29 || column > 29)
        return;
    tile_sizes_array[row][column] = size;
}

void BuildPlanner::set_flag(long long flags, int param1, int param2, int param3) {
    special_flags |= flags;
    if (param1 != -1)
        additional_req_param1 = param1;

    if (param2 != -1)
        additional_req_param2 = param2;

    if (param3 != -1)
        additional_req_param3 = param3;
}

bool BuildPlanner::has_flag_set(int flag, int param1, int param2, int param3) {
    if (param1 != -1 && additional_req_param1 != param1)
        return false;

    if (param2 != -1 && additional_req_param2 != param2)
        return false;

    if (param3 != -1 && additional_req_param3 != param3)
        return false;

    if (special_flags & flag)
        return true;

    return false;
}

void BuildPlanner::set_graphics_row(int row, int* image_ids, int total) {
    for (int i = 0; i < total; ++i) {
        if (row > 29 || i > 29)
            return;
        tile_graphics_array[row][i] = image_ids[i];

        // set sizes automatically as default
        int tile_size = 0;
        if (image_ids[i] != 0) {
            auto img = image_get(image_ids[i]);
            set_tile_size(row, i, img->isometric_size());
        }
    }
}

void BuildPlanner::set_tiles_building(int image_id, int size_xx) {
    init_tiles(size_xx, size_xx);
    int empty_row[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int draw_row[] = {image_id, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int row = 0; row < size.y; ++row) {
        if (row == size.y - 1)
            set_graphics_row(row, draw_row, size.x);
        else
            set_graphics_row(row, empty_row, size.x);
    }
}
void BuildPlanner::set_graphics_array(int* image_set, int size_x, int size_y) {
    init_tiles(size_x, size_y);
    // int (*image_array)[size_y][size_x] = (int(*)[size_y][size_x])image_set;

    // do it row by row...
    // for (int row = 0; row < size_y; ++row)
    //    set_graphics_row(row, (*image_array)[row], size_x);

    for (int row = 0; row < size_y; ++row) {
        set_graphics_row(row, image_set + (row * size_x), size_x);
    }
}

void BuildPlanner::setup_build(e_building_type type) { // select building for construction, set up main terrain restrictions/requirements
    // initial data
    reset();
    build_type = type;

    // ignore empty building types
    switch (type) {
    case BUILDING_NONE:
    case BUILDING_MENU_FARMS:
    case BUILDING_MENU_RAW_MATERIALS:
    case BUILDING_MENU_SHRINES:
    case BUILDING_MENU_TEMPLES:
    case BUILDING_MENU_TEMPLE_COMPLEX:
    case BUILDING_MENU_CONSTURCTION_GUILDS:
    case BUILDING_MENU_DEFENSES:
    case BUILDING_MENU_FORTS:
    case BUILDING_MENU_WATER_CROSSINGS:
    case BUILDING_MENU_BEAUTIFICATION:
    case BUILDING_MENU_MONUMENTS:
        return;
    }

    // leftover special cases....
    switch (build_type) {
    case BUILDING_SMALL_STATUE:
    case BUILDING_MEDIUM_STATUE:
    case BUILDING_LARGE_STATUE:
        building_rotation_randomize_variant(end, type);
        relative_orientation = 1; // force these buildings to start in a specific orientation
        update_orientations(false);
        break;
        //
    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
    case BUILDING_TEMPLE_COMPLEX_RA:
    case BUILDING_TEMPLE_COMPLEX_PTAH:
    case BUILDING_TEMPLE_COMPLEX_SETH:
    case BUILDING_TEMPLE_COMPLEX_BAST:
        relative_orientation = 1; // force these buildings to start in a specific orientation
        update_orientations(false);
        break;
    }

    // load building data
    setup_build_flags();
    setup_build_graphics();
}

void BuildPlanner::setup_build_flags() {
    switch (build_type) {
    default:
        ; // nothing
        break;

    case BUILDING_BARLEY_FARM:
    case BUILDING_FLAX_FARM:
    case BUILDING_GRAIN_FARM:
    case BUILDING_LETTUCE_FARM:
    case BUILDING_POMEGRANATES_FARM:
    case BUILDING_CHICKPEAS_FARM:
    case BUILDING_FIGS_FARM:
    case BUILDING_HENNA_FARM:
        set_flag(PlannerFlags::Meadow);
        break;

    case BUILDING_STONE_QUARRY:
    case BUILDING_LIMESTONE_QUARRY:
    case BUILDING_GRANITE_QUARRY:
    case BUILDING_SANDSTONE_QUARRY:
        set_flag(PlannerFlags::Rock);
        break;

    case BUILDING_GOLD_MINE:
    case BUILDING_GEMSTONE_MINE:
        set_flag(PlannerFlags::Rock);
        set_flag(PlannerFlags::Ore);
        break;

    case BUILDING_COPPER_MINE:
        set_flag(PlannerFlags::Rock);
        if (!config_get(CONFIG_GP_CH_COPPER_NEAR_MOUNTAINS)) {
            set_flag(PlannerFlags::Ore);
        }
        break;

    case BUILDING_CLAY_PIT:
        set_flag(PlannerFlags::NearbyWater);
        break;

    case BUILDING_MUD_TOWER:
        set_flag(PlannerFlags::Walls);
        break;

    case BUILDING_WELL:
    case BUILDING_WATER_SUPPLY:
    case BUILDING_VILLAGE_PALACE:
    case BUILDING_TOWN_PALACE:
    case BUILDING_CITY_PALACE:
        set_flag(PlannerFlags::Groundwater);
        break;
        //        case BUILDING_LIBRARY: // TODO
        //            set_requirements(PlannerReqs::Resources, RESOURCE_PAPYRUS, 300);
        //            break;
        //        case BUILDING_OBELYSK: // TODO
        //            set_requirements(PlannerReqs::Resources, RESOURCE_GRANITE, 200);
        //            break;
    case BUILDING_WATER_LIFT:
        set_flag(PlannerFlags::ShoreLine, 2);
        set_flag(PlannerFlags::FloodplainShore, 2);
        break;

    case BUILDING_FISHING_WHARF:
    case BUILDING_TRANSPORT_WHARF:
        set_flag(PlannerFlags::ShoreLine, 2);
        break;

    case BUILDING_SHIPWRIGHT:
    case BUILDING_DOCK:
    case BUILDING_WARSHIP_WHARF:
        set_flag(PlannerFlags::ShoreLine, 3);
        break;

    case BUILDING_FERRY:
        set_flag(PlannerFlags::ShoreLine, 2);
        set_flag(PlannerFlags::Ferry);
        break;

    case BUILDING_LOW_BRIDGE:
    case BUILDING_UNUSED_SHIP_BRIDGE_83:
        set_flag(PlannerFlags::ShoreLine, 1);
        set_flag(PlannerFlags::Bridge);
        break;

    case BUILDING_IRRIGATION_DITCH:
        set_flag(PlannerFlags::Canals, false);
        break;

    case BUILDING_ROAD:
        set_flag(PlannerFlags::Road, false);
        break;

    case BUILDING_ROADBLOCK:
        set_flag(PlannerFlags::Road, true, WARNING_ROADBLOCKS_ROAD_NEEDED);
        break;

    case BUILDING_PLAZA:
        set_flag(PlannerFlags::Road, true, -1);
        set_flag(PlannerFlags::FancyRoad);
        break;

    case BUILDING_BOOTH:
        set_flag(PlannerFlags::Intersection, 0, WARNING_BOOTH_ROAD_INTERSECTION_NEEDED);
        break;

    case BUILDING_BANDSTAND:
        set_flag(PlannerFlags::Intersection, 1, WARNING_BOOTH_ROAD_INTERSECTION_NEEDED);
        break;

    case BUILDING_PAVILLION:
        set_flag(PlannerFlags::Intersection, 2, WARNING_BOOTH_ROAD_INTERSECTION_NEEDED);
        break;

    case BUILDING_FESTIVAL_SQUARE:
        set_flag(PlannerFlags::Intersection, 3, WARNING_FESTIVAL_ROAD_INTERSECTION_NEEDED);
        break;

    case BUILDING_CLEAR_LAND:
        set_flag(PlannerFlags::IgnoreNearbyEnemy);
        break;

    case BUILDING_TEMPLE_COMPLEX_ALTAR:
        set_flag(PlannerFlags::TempleUpgrade, 2);
        break;

    case BUILDING_TEMPLE_COMPLEX_ORACLE:
        set_flag(PlannerFlags::TempleUpgrade, 1);
        break;
    }

    if (building_is_draggable(build_type)) {
        set_flag(PlannerFlags::Draggable);
    }
}

void BuildPlanner::setup_build_graphics() {
    const auto &props = building_impl::params(build_type);
    switch (build_type) {
    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
    case BUILDING_TEMPLE_COMPLEX_RA:
    case BUILDING_TEMPLE_COMPLEX_PTAH:
    case BUILDING_TEMPLE_COMPLEX_SETH:
    case BUILDING_TEMPLE_COMPLEX_BAST: { // CHANGE: in the original game, the cursor does not always follow the main
                                         // building's top tile
        // size of every big item 3x3, in general 7x13
        // 25 max tiles at the moment to check blocked tiles
        int main_image_id = image_id_from_group(GROUP_BUILDING_TEMPLE_COMPLEX_MAIN, build_type);
        int oracle_image_id = image_id_from_group(GROUP_BUILDING_TEMPLE_COMPLEX_ORACLE, build_type);
        int altar_image_id = image_id_from_group(GROUP_BUILDING_TEMPLE_COMPLEX_ALTAR, build_type);
        int flooring_image_id = image_id_from_group(GROUP_BUILDING_TEMPLE_COMPLEX_FLOORING, build_type);
        int statue1_image_id = image_id_from_group(GROUP_BUILDING_TEMPLE_COMPLEX_STATUE_1, build_type);
        int statue2_image_id = image_id_from_group(GROUP_BUILDING_TEMPLE_COMPLEX_STATUE_2, build_type);

        int EMPTY = 0;
        int mn_1A = main_image_id;
        int mn_1B = main_image_id + 3;
        int mn_2A = oracle_image_id;
        int mn_2B = oracle_image_id + 3;
        int mn_3A = altar_image_id;
        int mn_3B = altar_image_id + 3;

        int til_0 = flooring_image_id + 0;
        int til_1 = flooring_image_id + 1;
        int til_2 = flooring_image_id + 2;
        int til_3 = flooring_image_id + 3;

        int smst0 = statue1_image_id + 0; // north
        int smst1 = statue1_image_id + 1; // east
        int smst2 = statue1_image_id + 2; // south
        int smst3 = statue1_image_id + 3; // west

        int lst0A = statue2_image_id + 0; // north
        int lst0B = statue2_image_id + 1;
        int lst1A = statue2_image_id + 2; // east
        int lst1B = statue2_image_id + 3;
        int lst2A = statue2_image_id + 4; // south
        int lst2B = statue2_image_id + 5;
        int lst3A = statue2_image_id + 6; // west
        int lst3B = statue2_image_id + 7;

        //            int orientation_rel = city_view_relative_orientation(orientation_rel);
        switch (relative_orientation) {
        case 0: { // NE
            int TEMPLE_COMPLEX_SCHEME[13][7] = {
              {til_3, lst1A, lst1B, til_1, lst3A, lst3B, til_3},
              {til_2, lst1A, lst1B, til_1, lst3A, lst3B, til_2},
              {til_3, lst1A, lst1B, til_1, lst3A, lst3B, til_3},
              {til_2, til_0, til_0, til_1, til_0, til_0, til_2},
              {til_0, til_0, EMPTY, EMPTY, EMPTY, til_0, til_0},
              {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
              {smst3, til_0, mn_1B, EMPTY, EMPTY, til_0, smst1},
              {til_1, til_1, EMPTY, EMPTY, EMPTY, til_1, til_1},
              {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
              {smst3, til_0, mn_2B, EMPTY, EMPTY, til_0, smst1},
              {til_1, til_1, EMPTY, EMPTY, EMPTY, til_1, til_1},
              {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
              {smst3, til_0, mn_3B, EMPTY, EMPTY, til_0, smst1},
            };
            set_graphics_array((int*)TEMPLE_COMPLEX_SCHEME, 7, 13);
            pivot = {2, 10};
            break;
        }
        case 1: { // SE
            int TEMPLE_COMPLEX_SCHEME[7][13] = {
              {smst0, smst0, til_1, smst0, smst0, til_1, smst0, smst0, til_0, til_2, til_3, til_2, til_3},
              {til_0, til_0, til_1, til_0, til_0, til_1, til_0, til_0, til_0, til_0, lst2B, lst2B, lst2B},
              {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, til_0, lst2A, lst2A, lst2A},
              {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, til_1, til_1, til_1, til_1},
              {mn_1A, EMPTY, EMPTY, mn_2A, EMPTY, EMPTY, mn_3A, EMPTY, EMPTY, til_0, lst0B, lst0B, lst0B},
              {til_0, til_0, til_1, til_0, til_0, til_1, til_0, til_0, til_0, til_0, lst0A, lst0A, lst0A},
              {smst2, smst2, til_1, smst2, smst2, til_1, smst2, smst2, til_0, til_2, til_3, til_2, til_3},
            };
            set_graphics_array((int*)TEMPLE_COMPLEX_SCHEME, 13, 7);
            pivot = {0, 2};
            break;
        }
        case 2: { // SW
            int TEMPLE_COMPLEX_SCHEME[13][7] = {
              {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
              {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
              {til_1, til_1, mn_1B, EMPTY, EMPTY, til_1, til_1},
              {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
              {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
              {til_1, til_1, mn_2B, EMPTY, EMPTY, til_1, til_1},
              {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
              {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
              {til_0, til_0, mn_3B, EMPTY, EMPTY, til_0, til_0},
              {til_2, til_0, til_0, til_1, til_0, til_0, til_2},
              {til_3, lst1A, lst1B, til_1, lst3A, lst3B, til_3},
              {til_2, lst1A, lst1B, til_1, lst3A, lst3B, til_2},
              {til_3, lst1A, lst1B, til_1, lst3A, lst3B, til_3},
            };
            set_graphics_array((int*)TEMPLE_COMPLEX_SCHEME, 7, 13);
            pivot = {2, 0};
            break;
        }
        case 3: { // NW
            int TEMPLE_COMPLEX_SCHEME[7][13] = {
              {til_3, til_2, til_3, til_2, til_0, smst0, smst0, til_1, smst0, smst0, til_1, smst0, smst0},
              {lst2B, lst2B, lst2B, til_0, til_0, til_0, til_0, til_1, til_0, til_0, til_1, til_0, til_0},
              {lst2A, lst2A, lst2A, til_0, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
              {til_1, til_1, til_1, til_1, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
              {lst0B, lst0B, lst0B, til_0, mn_1A, EMPTY, EMPTY, mn_2A, EMPTY, EMPTY, mn_3A, EMPTY, EMPTY},
              {lst0A, lst0A, lst0A, til_0, til_0, til_0, til_0, til_1, til_0, til_0, til_1, til_0, til_0},
              {til_3, til_2, til_3, til_2, til_0, smst2, smst2, til_1, smst2, smst2, til_1, smst2, smst2},
            };
            set_graphics_array((int*)TEMPLE_COMPLEX_SCHEME, 13, 7);
            pivot = {10, 2};
            break;
        }
        }
        break;
    }
    case BUILDING_TEMPLE_COMPLEX_ALTAR:
    case BUILDING_TEMPLE_COMPLEX_ORACLE:
        init_tiles(3, 3);
        set_tiles_building(get_temple_complex_part_image(building_at(end.grid_offset())->main()->type, additional_req_param1, relative_orientation, 1), 3);
        break;

    case BUILDING_WATER_LIFT:
        set_tiles_building(props.anim["base"].first_img() + relative_orientation + variant * 4, props.building_size);
        break;

    case BUILDING_DOCK:
    case BUILDING_WARSHIP_WHARF:
    case BUILDING_TRANSPORT_WHARF:
        set_tiles_building(props.anim["base"].first_img() + relative_orientation, props.building_size);
        break;

    case BUILDING_LOW_BRIDGE:
    case BUILDING_UNUSED_SHIP_BRIDGE_83:
        // TODO
        break;

    case BUILDING_SMALL_STATUE:
    case BUILDING_MEDIUM_STATUE:
    case BUILDING_LARGE_STATUE: {
            int statue_img = building_statue::get_image(build_type, relative_orientation, variant);
            set_tiles_building(statue_img, props.building_size);
        }
        break;

    case BUILDING_STORAGE_YARD:
        set_tiles_building(props.anim[animkeys().base].first_img(), 3);
        break;

    case BUILDING_SMALL_MASTABA:
        switch (city_view_orientation() / 2) {
        case 0: init_tiles(4, 10); break;
        case 1: init_tiles(10, 4); break;
        case 2: init_tiles(4, 10); break;
        case 3: init_tiles(10, 4); break;
        }
        break;    

    case BUILDING_BOOTH:
        init_tiles(2, 2);
        break;

    case BUILDING_BANDSTAND:
        init_tiles(3, 3);
        break;

    case BUILDING_PAVILLION:
        init_tiles(4, 4); // TODO
        break;

    case BUILDING_FESTIVAL_SQUARE:
        init_tiles(5, 5); // TODO
        break;

    default: // regular buildings 
        {
            const auto &params = building_impl::params(build_type);
            int img_id = props.anim[animkeys().base].first_img();
            if (!img_id) {
                img_id = params.anim[animkeys().preview].first_img();
            }
            img_id += params.planer_relative_orientation * relative_orientation;
            set_tiles_building(img_id, props.building_size);
        }
        break;
    }
}

void BuildPlanner::update_obstructions_check() {
    tiles_blocked_total = 0;
    for (int row = 0; row < size.y; row++) {
        for (int column = 0; column < size.x; column++) {
            // check terrain at coords
            tile2i current_tile = tile_coord_cache[row][column];
            unsigned int restricted_terrain = TERRAIN_ALL;

            // special cases
            if (special_flags & PlannerFlags::Meadow
                || special_flags & PlannerFlags::FloodplainShore
                || special_flags & PlannerFlags::Road || special_flags & PlannerFlags::Canals) {
                restricted_terrain -= TERRAIN_FLOODPLAIN;
            }

            bool can_blocked_by_floodplain_edge = !building_is_farm(build_type);
            if (special_flags & PlannerFlags::Road
                || special_flags & PlannerFlags::Intersection
                || special_flags & PlannerFlags::Canals) {
                restricted_terrain -= TERRAIN_ROAD;
                can_blocked_by_floodplain_edge = false;
            }

            if (special_flags & PlannerFlags::Road || special_flags & PlannerFlags::Canals) {
                restricted_terrain -= TERRAIN_CANAL;

            }

            if (special_flags & PlannerFlags::Water || special_flags & PlannerFlags::ShoreLine) {
                restricted_terrain -= TERRAIN_WATER;
            }

            if (special_flags & PlannerFlags::TempleUpgrade) { // special case
                return;
            }

            tile_blocked_array[row][column] = false;
            bool blocked_by_floodplain_edge = (can_blocked_by_floodplain_edge && map_get_floodplain_edge(current_tile));
            if (!map_grid_is_inside(current_tile, 1)
                || map_terrain_is(current_tile, restricted_terrain & TERRAIN_NOT_CLEAR)
                || map_has_figure_at(current_tile)
                || blocked_by_floodplain_edge) {
                tile_blocked_array[row][column] = true;
                tiles_blocked_total++;
            }
        }
    }

    if (tiles_blocked_total > 0) {
        immediate_warning_id = WARNING_CLEAR_LAND_NEEDED;
        can_place = CAN_NOT_BUT_GREEN;
    }
}

void BuildPlanner::update_requirements_check() {
    // invalid build
    if (build_type == BUILDING_NONE) {
        can_place = CAN_NOT_PLACE;
        return;
    }

    // out of money!
    if (city_finance_out_of_money()) {
        // TODO: no money needed if building has zero cost?
        immediate_warning_id = WARNING_OUT_OF_MONEY;
        can_place = CAN_NOT_PLACE;
        return;
    }

    /////// special requirements
    //
    if (special_flags & PlannerFlags::Resources) {
        if (city_resource_warehouse_stored((e_resource)additional_req_param1) < additional_req_param2) {
            immediate_warning_id = additional_req_param3;
            can_place = CAN_NOT_BUT_GREEN;
        }
    }

    if (special_flags & PlannerFlags::Groundwater) {
        if (!map_terrain_exists_tile_in_radius_with_type(end, size.x, 0, TERRAIN_GROUNDWATER)) {
            immediate_warning_id = WARNING_GROUNDWATER_NEEDED;
            can_place = CAN_NOT_PLACE;
        }
    }
    if (special_flags & PlannerFlags::NearbyWater) {
        if (!map_terrain_exists_tile_in_radius_with_type(end, size.x, 3, TERRAIN_WATER)
            && !map_terrain_exists_tile_in_radius_with_type(end, size.x, 3, TERRAIN_FLOODPLAIN)) {
            immediate_warning_id = WARNING_WATER_NEEDED;
            can_place = CAN_NOT_PLACE;
        }
    }

    if (special_flags & PlannerFlags::Meadow) {
        if (!map_terrain_exists_tile_in_radius_with_type(end, size.x, 1, TERRAIN_MEADOW)
            && !map_terrain_all_tiles_in_radius_are(end.x(), end.y(), size.x, 0, TERRAIN_FLOODPLAIN)) {
            immediate_warning_id = WARNING_MEADOW_NEEDED;
            can_place = CAN_NOT_PLACE;
        }
    }

    if (special_flags & PlannerFlags::Rock) {
        if (!map_terrain_exists_tile_in_radius_with_type(end, size.x, 1, TERRAIN_ROCK)) {
            immediate_warning_id = WARNING_ROCK_NEEDED;
            can_place = CAN_NOT_PLACE;
        }
    }

    if (special_flags & PlannerFlags::Ore) {
        if (!map_terrain_exists_tile_in_radius_with_type(end, size.x, 1, TERRAIN_ORE)) {
            immediate_warning_id = WARNING_ROCK_NEEDED;
            can_place = CAN_NOT_PLACE;
        }
    }

    if (special_flags & PlannerFlags::Trees) {
        if (!map_terrain_exists_tile_in_radius_with_type(end, size.x, 1, TERRAIN_SHRUB | TERRAIN_TREE)) {
            immediate_warning_id = WARNING_TREE_NEEDED;
            can_place = CAN_NOT_PLACE;
        }
    }

    if (special_flags & PlannerFlags::Walls) {
        if (!map_terrain_all_tiles_in_radius_are(end.x(), end.y(), size.x, 0, TERRAIN_WALL)) {
            immediate_warning_id = WARNING_WALL_NEEDED;
            can_place = CAN_NOT_PLACE;
        }
    }

    if (!!(special_flags & PlannerFlags::IgnoreNearbyEnemy) == false) {
        if (has_nearby_enemy(start.x(), start.y(), end.x(), end.y())) {
            immediate_warning_id = WARNING_ENEMY_NEARBY;
            can_place = CAN_NOT_PLACE;
        }
    }
    if ((!!(special_flags & PlannerFlags::Road) && !!additional_req_param1) == true) {
        if (!map_terrain_is(end.grid_offset(), TERRAIN_ROAD)) {
            immediate_warning_id = additional_req_param2;
            can_place = CAN_NOT_PLACE;
        }
    }

    if ((!!(special_flags & PlannerFlags::Canals) && !!additional_req_param1) == true) {
        if (!map_terrain_is(end.grid_offset(), TERRAIN_CANAL)) {
            immediate_warning_id = additional_req_param2;
            can_place = CAN_NOT_PLACE;
        }
    }

    if (special_flags & PlannerFlags::FancyRoad) {
        if (!map_tiles_is_paved_road(end.grid_offset())) {
            can_place = CAN_NOT_PLACE;
        }
    }

    if (special_flags & PlannerFlags::RiverAccess) {
        if (!map_tile_is_connected_to_open_water(end)) {
            immediate_warning_id = WARNING_DOCK_OPEN_WATER_NEEDED;
        }
    }
}
void BuildPlanner::update_special_case_orientations_check() {
    int dir_relative;

    // for special buildings that require oriented terrain
    if (special_flags & PlannerFlags::ShoreLine) {
        shore_orientation result = map_shore_determine_orientation(end, additional_req_param1, true);
        if (special_flags & PlannerFlags::FloodplainShore) {
            // in original Pharaoh, this actually is allowed to be built over the EDGE CORNERS.
            // it looks off, but it's legit!
            variant = 0;
            if (!result.match) {
                result = map_shore_determine_orientation(end, additional_req_param1, true, true, TERRAIN_FLOODPLAIN);
                if (result.match && !map_terrain_exists_tile_in_area_with_type(end, size.x, TERRAIN_WATER)) { // correct for water
                    variant = 1;
                } else {
                    result.match = false;
                }
            } else if (map_terrain_exists_tile_in_area_with_type(end, size.x, TERRAIN_FLOODPLAIN)) { // correct the ShoreLine check for floodplains!
                result.match = false;
            }
        }
        dir_relative = city_view_relative_orientation(result.orientation_absolute);
        if (!result.match) {
            immediate_warning_id = WARNING_SHORE_NEEDED;
            can_place = CAN_NOT_PLACE;
        } else if (relative_orientation != dir_relative) {
            relative_orientation = dir_relative;
            update_orientations(false);
        }
    }
    if (special_flags & PlannerFlags::Intersection) {
        bool match = map_orientation_for_venue_with_map_orientation(end, (e_venue_mode_orientation)additional_req_param1, &dir_relative);
        int city_direction = dir_relative / 2;
        if (!match) {
            immediate_warning_id = additional_req_param2;
            can_place = CAN_NOT_PLACE;
        } else if (relative_orientation != city_direction) {
            relative_orientation = city_direction;
            update_orientations(false);
        }
    }

    if (special_flags & PlannerFlags::TempleUpgrade) {
        building* target = building_at(end.grid_offset())->main();
        if (!building_at(end.grid_offset()) || !building_is_large_temple(target->type)) {
            immediate_warning_id = WARNING_TEMPLE_UPGRADE_PLACEMENT_NEED_TEMPLE;
            can_place = CAN_NOT_PLACE;
        } else if (target->data.monuments.temple_complex_attachments & additional_req_param1) {
            immediate_warning_id = WARNING_TEMPLE_UPGRADE_ONLY_ONE;
            can_place = CAN_NOT_PLACE;
        } else {
            int dir_absolute = (5 - (target->data.monuments.variant / 2)) % 4;
            dir_relative = city_view_relative_orientation(dir_absolute);
            relative_orientation = (1 + dir_relative) % 2;
            end = temple_complex_part_target(target, additional_req_param1);
            update_orientations(false);
        }
    }
}

void BuildPlanner::update_unique_only_one_check() {
    bool unique_already_placed = false;

    bool is_unique_building = building_impl::params(build_type).unique_building;
    if (is_unique_building) {
        unique_already_placed = building_count_total(build_type);
    }

    // for unique buildings - only one can be placed inside the mission
    switch (build_type) {
    case BUILDING_RECRUITER:
        if (city_buildings_has_recruiter() && !config_get(CONFIG_GP_CH_MULTIPLE_BARRACKS)) {
            unique_already_placed = true;
        }
        break;
    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
    case BUILDING_TEMPLE_COMPLEX_RA:
    case BUILDING_TEMPLE_COMPLEX_PTAH:
    case BUILDING_TEMPLE_COMPLEX_SETH:
    case BUILDING_TEMPLE_COMPLEX_BAST:
        //        case BUILDING_TEMPLE_COMPLEX_ALTAR:
        //        case BUILDING_TEMPLE_COMPLEX_ORACLE:
        if (city_buildings_has_temple_complex() && !config_get(CONFIG_GP_CH_MULTIPLE_TEMPLE_COMPLEXES))
            unique_already_placed = true;
        break;

    default:
        ; // nothing
    }

    if (unique_already_placed) {
        immediate_warning_id = WARNING_ONE_BUILDING_OF_TYPE;
        can_place = CAN_NOT_PLACE;
    }
}

void BuildPlanner::update_coord_caches() {
    vec2i view_tile = tile_to_pixel(end);
    if (view_tile.x == 0 && view_tile.y == 0)
        // this prevents graphics from being drawn on the top left corner
        // of the screen when the current "end" tile isn't valid.
        view_tile = camera_get_selected_screen_tile();
    int orientation = city_view_orientation() / 2;
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

            // get tile pixel coords
            int current_x = view_tile.x + x_offset * 30 - y_offset * 30;
            int current_y = view_tile.y + x_offset * 15 + y_offset * 15;

            // save values in cache
            tile_coord_cache[row][column] = tile;
            pixel_coords_cache[row][column] = {current_x, current_y};
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

void BuildPlanner::update_orientations(bool check_if_changed) {
    int prev_orientation = relative_orientation;
    int prev_variant = variant;
    int global_rotation = building_rotation_global_rotation();

    switch (build_type) {
    case BUILDING_SMALL_STATUE:
    case BUILDING_MEDIUM_STATUE:
    case BUILDING_LARGE_STATUE:
        relative_orientation = global_rotation + 1;
        variant = building_rotation_get_building_variant();
        break;

    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
    case BUILDING_TEMPLE_COMPLEX_RA:
    case BUILDING_TEMPLE_COMPLEX_PTAH:
    case BUILDING_TEMPLE_COMPLEX_SETH:
    case BUILDING_TEMPLE_COMPLEX_BAST: // CHANGE: in the original game, only two orientations are allowed
        relative_orientation = global_rotation + 1;
        variant = 0;
        break;

    default:
        break;
    }
    relative_orientation = relative_orientation % 4;
    absolute_orientation = city_view_absolute_orientation(relative_orientation);

    // do not refresh graphics if nothing changed
    if (check_if_changed && relative_orientation == prev_orientation && variant == prev_variant) {
        return;
    }

    setup_build_graphics(); // reload graphics, tiles, etc.
    update_coord_caches();  // refresh caches
}
void BuildPlanner::construction_record_view_position(vec2i pixel, tile2i point) {
    if (point == start) {
        start_offset_screen_x = pixel.x;
        start_offset_screen_y = pixel.y;
    }
}
void BuildPlanner::dispatch_warnings() {
    if (immediate_warning_id > -1)
        city_warning_show(immediate_warning_id);
    if (extra_warning_id > -1)
        city_warning_show(extra_warning_id);
}

int BuildPlanner::get_total_drag_size(int* x, int* y) {
    if (!config_get(CONFIG_UI_SHOW_CONSTRUCTION_SIZE) || !(special_flags & PlannerFlags::Draggable)
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

void BuildPlanner::construction_start(tile2i tile) {
    start = end = tile;

    if (game_undo_start_build(build_type)) {
        in_progress = true;
        int can_start = true;
        switch (build_type) {
        case BUILDING_ROAD:
            can_start = map_routing_calculate_distances_for_building(ROUTED_BUILDING_ROAD, start);
            break;
        case BUILDING_IRRIGATION_DITCH:
            //            case BUILDING_WATER_LIFT:
            can_start = map_routing_calculate_distances_for_building(ROUTED_BUILDING_AQUEDUCT, start);
            break;
        case BUILDING_MUD_WALL:
            can_start = map_routing_calculate_distances_for_building(ROUTED_BUILDING_WALL, start);
            break;

        default:
            break;
        }

        if (!can_start) {
            construction_cancel();
        }
    }
}

void BuildPlanner::construction_cancel() {
    map_property_clear_constructing_and_deleted();
    if (in_progress && special_flags & PlannerFlags::Draggable) {
        game_undo_restore_map(1);
        in_progress = false;
    } else {
        setup_build(BUILDING_NONE);
        //widget_sidebar_city_release_build_buttons();
    }
    building_rotation_reset_rotation();
}

void BuildPlanner::construction_update(tile2i tile) {
    end = tile;
    if (end == tile2i(-1, -1)) {
        return;
    }

    if (!build_type || city_finance_out_of_money()) {
        total_cost = 0;
        return;
    }

    map_property_clear_constructing_and_deleted();
    int current_cost = model_get_building(build_type)->cost;
    int global_rotation = building_rotation_global_rotation();
    int items_placed = 1;
    switch (build_type) {
    case BUILDING_CLEAR_LAND:
        items_placed = last_items_cleared = building_construction_clear_land(true, start, end);
        break;

    case BUILDING_MUD_WALL:
        items_placed = building_construction_place_wall(true, start, end);
        break;

    case BUILDING_ROAD:
        items_placed = building_road::place(true, start, end);
        break;

    case BUILDING_PLAZA:
        items_placed = building_plaza::place(start, end);
        break;

    case BUILDING_GARDENS:
        items_placed = building_garden::place(start, end);
        break;

    case BUILDING_IRRIGATION_DITCH:
        items_placed = building_construction_place_canal(true, start, end);
        map_tiles_update_all_canals(0);
        break;

    case BUILDING_LOW_BRIDGE:
    case BUILDING_UNUSED_SHIP_BRIDGE_83:
        items_placed = map_bridge_building_length();
        break;

    case BUILDING_HOUSE_VACANT_LOT:
        items_placed = place_houses(true, start.x(), start.y(), end.x(), end.y());
        break;

    case BUILDING_BRICK_GATEHOUSE:
    case BUILDING_MUD_GATEHOUSE:
        mark_construction(tile, 1, 3, ~TERRAIN_ROAD, false); // TODO
        break;

    case BUILDING_RESERVED_TRIUMPHAL_ARCH_56:
        mark_construction(tile, 3, 3, ~TERRAIN_ROAD, false);
        break;

    case BUILDING_STORAGE_YARD:
        mark_construction(tile, 3, 3, TERRAIN_ALL, false);
        break;

    case BUILDING_WATER_LIFT:
    case BUILDING_FISHING_WHARF:
    case BUILDING_TRANSPORT_WHARF:
    case BUILDING_SHIPWRIGHT:
    case BUILDING_DOCK:
    case BUILDING_WARSHIP_WHARF:
    case BUILDING_FERRY:
        draw_as_constructing = map_shore_determine_orientation(end, additional_req_param1, true).match;
        break;

    case BUILDING_FORT_ARCHERS:
    case BUILDING_FORT_CHARIOTEERS:
    case BUILDING_FORT_INFANTRY:
        if (formation_get_num_forts_cached() < 6) {
            vec2i offset = FORT_OFFSET[global_rotation][city_view_orientation() / 2];
            tile2i ground = tile.shifted(offset.x, offset.y);
            if (map_building_tiles_are_clear(tile, 3, TERRAIN_ALL)
                && map_building_tiles_are_clear(ground, 4, TERRAIN_ALL)) {
                mark_construction(tile, 3, 3, TERRAIN_ALL, false);
            }
        }
        break;

    default:
        if (special_flags & PlannerFlags::Meadow || special_flags & PlannerFlags::Rock
            || special_flags & PlannerFlags::Trees || special_flags & PlannerFlags::NearbyWater
            || special_flags & PlannerFlags::Walls || special_flags & PlannerFlags::Groundwater
            || special_flags & PlannerFlags::Water || special_flags & PlannerFlags::ShoreLine
            || special_flags & PlannerFlags::Road || special_flags & PlannerFlags::Intersection) {
            // never draw as constructing
        } else {
            if ((city_view_orientation() / 2) % 2 == 0) {
                mark_construction(north_tile, size.x, size.y, TERRAIN_ALL, true);
            } else {
                mark_construction(north_tile, size.y, size.x, TERRAIN_ALL, true);
            }
        }
    }

    if (items_placed >= 0) {
        current_cost *= items_placed;
    }
    
    total_cost = current_cost;
}

void BuildPlanner::construction_finalize() { // confirm final placement
    in_progress = false;

    dispatch_warnings();
    if (can_place != CAN_PLACE && !building_is_draggable(build_type)) { // this is the FINAL check!
        return;
    }

    // attempt placing, restore terrain data on failure
    if (!place()) {
        map_property_clear_constructing_and_deleted();
        if (build_type == BUILDING_MUD_WALL || build_type == BUILDING_ROAD || build_type == BUILDING_IRRIGATION_DITCH)
            game_undo_restore_map(0);
        else if (build_type == BUILDING_PLAZA || build_type == BUILDING_GARDENS)
            game_undo_restore_map(1);
        else if (build_type == BUILDING_LOW_BRIDGE || build_type == BUILDING_UNUSED_SHIP_BRIDGE_83)
            map_bridge_reset_building_length();

        return;
    }

    // final generic building warnings - these are in another file
    // TODO: bring these warnings over.
    building_construction_warning_generic_checks(last_created_building, end, size.x, relative_orientation);
    bool should_recalc_ferry_routes = false;

    // update city building info with newly created
    // building for special/unique constructions
    switch (build_type) {
    case BUILDING_SMALL_STATUE:
    case BUILDING_MEDIUM_STATUE:
    case BUILDING_LARGE_STATUE:
        building_rotation_randomize_variant(end, build_type);
        update_orientations(false);
        break;

    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
    case BUILDING_TEMPLE_COMPLEX_RA:
    case BUILDING_TEMPLE_COMPLEX_PTAH:
    case BUILDING_TEMPLE_COMPLEX_SETH:
    case BUILDING_TEMPLE_COMPLEX_BAST:
        city_buildings_add_temple_complex(last_created_building);
        break;

    case BUILDING_FERRY:
        should_recalc_ferry_routes = true;
        break;

    default:
        ; // nothing
    }

    // update terrain data for certain special cases
    if (special_flags & PlannerFlags::Meadow) {
        for (int y = end.y(); y < end.y() + size.y; y++) {
            for (int x = end.x(); x < end.x() + size.x; x++) {
                map_set_floodplain_growth(MAP_OFFSET(x, y), 0);
            }
        }
    }

    if (special_flags & PlannerFlags::Road) {
        map_terrain_add_in_area(end.x(), end.y(), end.x() + size.x - 1, end.y() + size.y - 1, TERRAIN_ROAD);
        map_tiles_update_area_roads(end.x(), end.y(), 5);
        map_tiles_update_all_plazas();
    }

    if (special_flags & PlannerFlags::Walls) {
        map_tiles_update_area_walls(end, 5);
    }

    // consume resources for specific buildings (e.g. marble, granite)
    if (special_flags & PlannerFlags::Resources) {
        city_storageyards_remove_resource((e_resource)additional_req_param1, additional_req_param2);
    }

    // finally, go over the rest of the stuff for all building types
    formation_move_herds_away(end);
    city_finance_process_construction(total_cost);
    game_undo_finish_build(total_cost);
    map_tiles_update_region_empty_land(false, start.shifted(-2, -2), end.shifted(size.x + 2, size.y + 2));
    map_routing_update_land();
    map_routing_update_walls();

    if (should_recalc_ferry_routes) {
        map_routing_update_ferry_routes();
    }
}

//////////////////////

void BuildPlanner::update(tile2i cursor_tile) {
    end = cursor_tile;
    update_coord_caches();

    immediate_warning_id = -1;
    can_place = CAN_PLACE;
    update_obstructions_check();
    update_requirements_check();
    update_special_case_orientations_check();
    update_unique_only_one_check();
}

bool BuildPlanner::place() {
    if (end == tile2i(-1, -1)) {
        return false;
    }

    int x = end.x();
    int y = end.y();

    // for debugging...
    logs::info("Attempting to place at: %03i %03i %06i", x, y, MAP_OFFSET(x, y));

    // Check warnings for placement and create building/update tiles accordingly.
    // Some of the buildings below have specific warning messages (e.g. roadblocks)
    // that can't be easily put in `building_construction_can_place_on_terrain()`!
    int placement_cost = model_get_building(build_type)->cost;
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
        }
        break;

    case BUILDING_MUD_WALL:
        placement_cost *= building_construction_place_wall(false, start, end);
        break;

    case BUILDING_ROAD:
        placement_cost *= building_road::place(false, start, end);
        break;

    case BUILDING_PLAZA:
        placement_cost *= building_plaza::place(start, end);
        break;

    case BUILDING_GARDENS:
        placement_cost *= building_garden::place(start, end);
        map_routing_update_land();
        break;

    case BUILDING_LOW_BRIDGE:
    case BUILDING_UNUSED_SHIP_BRIDGE_83: {
        placement_cost *= map_bridge_add(x, y, build_type == BUILDING_UNUSED_SHIP_BRIDGE_83);
        break;
    }
    case BUILDING_IRRIGATION_DITCH: {
        placement_cost *= building_construction_place_canal(false, start, end);
        if (!placement_cost) {
            map_tiles_update_all_canals(0);
            map_routing_update_land();
        }
        break;
    }
    case BUILDING_HOUSE_VACANT_LOT:
        placement_cost *= place_houses(false, start.x(), start.y(), end.x(), end.y());
        if (placement_cost == 0) {
            city_warning_show(WARNING_CLEAR_LAND_NEEDED);
            return false;
        }
        break;
    case BUILDING_TEMPLE_COMPLEX_ALTAR:
    case BUILDING_TEMPLE_COMPLEX_ORACLE:
        if (!attach_temple_upgrade(additional_req_param1, end.grid_offset())) {
            return false;
        }
        break;

    default:
        if (!place_building(build_type, end, absolute_orientation, variant)) {
            return false;
        }
        break;
    }

    // TODO
    //    if (building_is_fort(building_type)) {
    //        const int offsets_x[] = {3, -1, -4, 0};
    //        const int offsets_y[] = {-1, -4, 0, 3};
    //        int orient_index = building_rotation_get_rotation();
    //        int x_offset = offsets_x[orient_index];
    //        int y_offset = offsets_y[orient_index];
    //        if (!map_tiles_are_clear(x + x_offset, y + y_offset, 4, terrain_mask)) {
    //            city_warning_show(WARNING_CLEAR_LAND_NEEDED);
    //            return 0;
    //        }
    //        if (formation_get_num_legions_cached() >= formation_get_max_legions()) {
    //            city_warning_show(WARNING_MAX_LEGIONS_REACHED);
    //            return 0;
    //        }
    //    }

    total_cost = placement_cost;
    if (total_cost == 0) {
        return false;
    }
    return true;
}
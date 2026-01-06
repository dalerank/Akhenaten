#include "build_planner.h"

#include "graphics/view/lookup.h"
#include "grid/floodplain.h"
#include "core/log.h"
#include "widget/widget_sidebar.h"

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
#include "building/building_well.h"
#include "building/building_bridge.h"
#include "city/city_industry.h"
#include "building/building_fort.h"
#include "building/building.h"
#include "building/building_temple_complex.h"
#include "city/buildings.h"
#include "city/city_buildings.h"
#include "city/city_finance.h"
#include "game/game_events.h"
#include "city/city_resource.h"
#include "city/city_warnings.h"
#include "clear.h"
#include "figure/formation_batalion.h"
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
#include "game/game_config.h"
#include "routed.h"
#include "city/city.h"

enum e_place_reservoir {
    PLACE_RESERVOIR_BLOCKED = -1,
    PLACE_RESERVOIR_NO = 0,
    PLACE_RESERVOIR_YES = 1,
    PLACE_RESERVOIR_EXISTS = 2
};

build_planner g_city_planner;

static int last_items_cleared;

static const vec2i FORT_OFFSET[4][4] = {{{3, -1}, {4, -1}, {4, 0}, {3, 0}}, 
                                        {{-1, -4}, {0, -4}, {0, -3}, {-1, -3}}, 
                                        {{-4, 0}, {-3, 0}, {-3, 1}, {4, 1}}, 
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

void build_planner::add_building_tiles_from_list(int building_id, bool graphics_only) {
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

bool build_planner::ghost_mark_deleting(tile2i tile) {
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

void build_planner::draw_tile_graphics_array(painter &ctx, tile2i start, tile2i end, vec2i pixel) {
    // go through the tiles DIAGONALLY to render footprint and top correctly
    for (int dg_y = 0; dg_y < size.y + size.x - 1; dg_y++) {
        for (int dg_x = fmax(0, dg_y - size.y + 1); dg_x < size.x && dg_x < dg_y + 1; dg_x++) {
            // extract proper row and column index from the mess above
            int row = dg_y - dg_x;
            int column = dg_x;

            int image_id = tile_graphics_array[row][column];
            if (image_id > 0) {
                auto& command = ImageDraw::create_command(render_command_t::ert_drawtile_full);
                command.image_id = image_id;
                command.pixel = pixel_coords_cache[row][column];
                command.mask = COLOR_MASK_GREEN;
            } else if(image_id < 0) {
                auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
                command.image_id = image_id_from_group(GROUP_TERRAIN_BLACK);
                command.pixel = pixel_coords_cache[row][column];
                command.mask = COLOR_MASK_GREEN;
            }
        }
    }
}

static int has_nearby_enemy(int x_start, int y_start, int x_end, int y_end) {
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure* f = figure_get(i);
        if (!!game_features::gameplay_hyenas_block) {
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

int build_planner::place_houses(bool measure_only, int x_start, int y_start, int x_end, int y_end) {
    grid_area area = map_grid_get_area(tile2i(x_start, y_start), tile2i(x_end, y_end));

    int needs_road_warning = 0;
    int items_placed = 0;
    game_undo_restore_building_state();
    const auto &bparams = building_static_params::get(BUILDING_HOUSE_VACANT_LOT);
    int vacant_lot_id = bparams.first_img(animkeys().preview);
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
                if (g_city_animals.breeding_ground_at(tile2i(x, y), 1)) {
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
        //building_construction_warning_check_food_stocks(BUILDING_HOUSE_VACANT_LOT);
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

void build_planner::init() {
    events::subscribe([this] (event_rotate_building ev) {
        building_rotation_rotate_by_hotkey();
        update_orientations();
    });

    events::subscribe([this] (event_city_building_mode ev) {
        e_building_type btype = (e_building_type)ev.value;
        if (ev.value == BUILDING_NONE) {
            construction_cancel();
        }

        const bool enabled = scenario_building_allowed(btype);
        if (enabled) {
            construction_cancel();
            setup_build((e_building_type)ev.value);
        }
    });

    events::subscribe([this] (event_change_building_variant) {
        next_building_variant();
    });
}

void build_planner::reset() {
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
    custom_building_variant = 0;
    building_variant = 0;

    // reset special requirements flags/params
    special_flags = 0;
    additional_req_param1 = -1;
    additional_req_param2 = -1;
    additional_req_param3 = -1;
    can_place = CAN_PLACE;
    immediate_warning_id = "";
    extra_warning_id = "";
}

void build_planner::init_tiles(int size_x, int size_y) {
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

void build_planner::set_tile_size(int row, int column, int size) {
    if (row > 29 || column > 29)
        return;
    tile_sizes_array[row][column] = size;
}

void build_planner::set_flag(uint64_t flags, int param1, int param2, int param3) {
    special_flags |= flags;
    if (param1 != -1)
        additional_req_param1 = param1;

    if (param2 != -1)
        additional_req_param2 = param2;

    if (param3 != -1)
        additional_req_param3 = param3;
}

bool build_planner::has_flag_set(int flag, int param1, int param2, int param3) {
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

void build_planner::set_graphics_row(int row, custom_span<int> image_ids, int def) {
    if (row < 0) {
        return;
    }

    for (int i = 0; i < image_ids.size(); ++i) {
        if (row > 29 || i > 29) {
            return;
        }

        const int image_id = image_ids[i];
        tile_graphics_array[row][i] = (image_id > 0 ? image_id : def);

        // set sizes automatically as default
        int tile_size = 0;
        if (image_ids[i] > 0) {
            auto img = image_get(image_ids[i]);
            set_tile_size(row, i, img->isometric_size());
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

void build_planner::set_graphics_array(custom_span<int> image_set, vec2i size) {
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
    const auto &preview = building_planer_renderer::get(type);
    int random_value = tile.grid_offset();
    custom_building_variant = preview.setup_building_variant(type, tile, random_value);
}

void build_planner::next_building_variant() {
    const auto &preview = building_planer_renderer::get(build_type);
    custom_building_variant = preview.next_building_variant(build_type, end, custom_building_variant);
    update_orientations();
}

void build_planner::setup_build(e_building_type type) { // select building for construction, set up main terrain restrictions/requirements
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
    default:
        break;
    }

    const auto &params = building_static_params::get(type);
    const auto &preview = building_planer_renderer::get(type);
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
    const auto &preview = building_planer_renderer::get(build_type);

    const e_building_flag flags[] = { e_building_flag::Meadow, e_building_flag::Rock, e_building_flag::Ore, e_building_flag::TempleUpgradeAltar,
                                      e_building_flag::TempleUpgradeOracle, e_building_flag::NearbyWater, e_building_flag::Groundwater, e_building_flag::ShoreLine,
                                      e_building_flag::Canals, e_building_flag::FloodplainShore };

    for (const auto flag: flags) {
        const bool is_need = preview.is_need_flag(*this, flag);
        if (is_need) {
            set_flag(flag);
        }
    }

    switch (build_type) {
    default:
        ; // nothing
        break;

    case BUILDING_MUD_TOWER:
        set_flag(e_building_flag::Walls);
        break;

        //        case BUILDING_LIBRARY: // TODO
        //            set_requirements(PlannerReqs::Resources, RESOURCE_PAPYRUS, 300);
        //            break;
        //        case BUILDING_OBELYSK: // TODO
        //            set_requirements(PlannerReqs::Resources, RESOURCE_GRANITE, 200);
        //            break;

    case BUILDING_LOW_BRIDGE:
    case BUILDING_UNUSED_SHIP_BRIDGE_83:
        set_flag(e_building_flag::ShoreLine, 1);
        set_flag(e_building_flag::Bridge);
        break;

    case BUILDING_ROAD:
        set_flag(e_building_flag::Road, false);
        break;

    case BUILDING_MUD_GATEHOUSE:
    case BUILDING_MUD_GATEHOUSE_UP:
    case BUILDING_BRICK_GATEHOUSE:
    case BUILDING_BRICK_GATEHOUSE_UP:
        set_flag(e_building_flag::Road, false);
        break;

    case BUILDING_ROADBLOCK:
        set_warning("#only_build_roadblocks_on_roads");
        set_flag(e_building_flag::Road, true);
        break;

    case BUILDING_PLAZA:
        set_flag(e_building_flag::Road, true);
        set_flag(e_building_flag::FancyRoad);
        break;

    case BUILDING_BOOTH:
        set_warning("#entertainment_venue_at_intersection");
        set_flag(e_building_flag::Intersection, 0);
        break;

    case BUILDING_BANDSTAND:
        set_warning("#entertainment_venue_at_intersection");
        set_flag(e_building_flag::Intersection, 1);
        break;

    case BUILDING_PAVILLION:
        set_warning("#entertainment_venue_at_intersection");
        set_flag(e_building_flag::Intersection, 2);
        break;

    case BUILDING_FESTIVAL_SQUARE:
        set_warning("#entertainment_venue_at_intersection");
        set_flag(e_building_flag::Intersection, 3);
        break;

    case BUILDING_CLEAR_LAND:
        set_flag(e_building_flag::IgnoreNearbyEnemy);
        break;
    }

    if (building_is_draggable(build_type)) {
        set_flag(e_building_flag::Draggable);
    }
}

void build_planner::setup_build_graphics() {
    const auto &preview = building_planer_renderer::get(build_type);   
    preview.setup_preview_graphics(*this);
}

void build_planner::update_obstructions_check() {
    tiles_blocked_total = 0;
    const auto &params = building_static_params::get(build_type);
    const auto &preview = building_planer_renderer::get(build_type);

    for (int row = 0; row < size.y; row++) {
        for (int column = 0; column < size.x; column++) {
            // check terrain at coords
            tile2i current_tile = tile_coord_cache[row][column];
            unsigned int restricted_terrain = TERRAIN_ALL;

            // special cases
            if (special_flags & e_building_flag::Meadow
                || special_flags & e_building_flag::FloodplainShore
                || special_flags & e_building_flag::Road 
                || special_flags & e_building_flag::Canals) {
                restricted_terrain -= TERRAIN_FLOODPLAIN;
            }

            bool can_blocked_by_floodplain_edge = !building_is_farm(build_type);
            if (special_flags & e_building_flag::Road
                || special_flags & e_building_flag::Intersection
                || special_flags & e_building_flag::Canals) {
                restricted_terrain -= TERRAIN_ROAD;
                can_blocked_by_floodplain_edge = false;
            }

            if (special_flags & e_building_flag::Road || special_flags & e_building_flag::Canals) {
                restricted_terrain -= TERRAIN_CANAL;
            }

            if (special_flags & e_building_flag::Walls) {
                restricted_terrain -= TERRAIN_WALL;
            }

            if (special_flags & e_building_flag::Water || special_flags & e_building_flag::ShoreLine) {
                restricted_terrain -= TERRAIN_WATER;
            }

            if ((special_flags & e_building_flag::TempleUpgradeAltar) || (special_flags & e_building_flag::TempleUpgradeOracle)) { // special case
                return;
            }


            tile_blocked_array[row][column] = false;
            const bool blocked_by_floodplain_edge = (can_blocked_by_floodplain_edge && map_get_floodplain_edge(current_tile));
            const bool inside_map = map_grid_is_inside(current_tile, 1);
            const bool not_clear = inside_map && map_terrain_is(current_tile, restricted_terrain & TERRAIN_NOT_CLEAR);
            const bool allow_tile = inside_map && preview.ghost_allow_tile(*this, current_tile);
            if (!inside_map || not_clear || !allow_tile || blocked_by_floodplain_edge) {
                tile_blocked_array[row][column] = true;
                tiles_blocked_total++;
            }
        }
    }

    if (tiles_blocked_total > 0) {
        immediate_warning_id = "#must_build_on_cleared_land";
        can_place = CAN_NOT_BUT_GREEN;
    }
}

void build_planner::update_requirements_check() {
    // invalid build
    if (build_type == BUILDING_NONE) {
        can_place = CAN_NOT_PLACE;
        return;
    }

    // out of money!
    if (g_city.finance.is_out_of_money()) {
        // TODO: no money needed if building has zero cost?
        immediate_warning_id = "#out_of_credit";
        can_place = CAN_NOT_PLACE;
        return;
    }

    /////// special requirements
    //
    if (special_flags & e_building_flag::Resources) {
        if (g_city.resource.yards_stored((e_resource)additional_req_param1) < additional_req_param2) {
            //immediate_warning_id = additional_req_param3;
            can_place = CAN_NOT_BUT_GREEN;
        }
    }

    if (special_flags & e_building_flag::Groundwater) {
        if (!map_terrain_exists_tile_in_radius_with_type(end, size.x, 0, TERRAIN_GROUNDWATER)) {
            immediate_warning_id = "#needs_groundwater";
            can_place = CAN_NOT_PLACE;
        }
    }
    if (special_flags & e_building_flag::NearbyWater) {
        if (!map_terrain_exists_tile_in_radius_with_type(end, size.x, 3, TERRAIN_WATER)
            && !map_terrain_exists_tile_in_radius_with_type(end, size.x, 3, TERRAIN_FLOODPLAIN)) {
            immediate_warning_id = "#building_not_next_to_water";
            can_place = CAN_NOT_PLACE;
        }
    }

    if (special_flags & e_building_flag::Meadow) {
        if (!map_terrain_exists_tile_in_radius_with_type(end, size.x, 1, TERRAIN_MEADOW)
            && !map_terrain_all_tiles_in_radius_are(end, size.x, 0, TERRAIN_FLOODPLAIN)) {
            immediate_warning_id = "#build_farms_on_meadow";
            can_place = CAN_NOT_PLACE;
        }
    }

    if (special_flags & e_building_flag::Rock) {
        if (!map_terrain_exists_tile_in_radius_with_type(end, size.x, 1, TERRAIN_ROCK)) {
            immediate_warning_id = "#build_next_to_rocky_areas";
            can_place = CAN_NOT_PLACE;
        }
    }

    if (special_flags & e_building_flag::Ore) {
        if (!map_terrain_exists_tile_in_radius_with_type(end, size.x, 1, TERRAIN_ORE)) {
            immediate_warning_id = "#build_next_to_rocky_areas";
            can_place = CAN_NOT_PLACE;
        }
    }

    if (special_flags & e_building_flag::Trees) {
        if (!map_terrain_exists_tile_in_radius_with_type(end, size.x, 1, TERRAIN_SHRUB | TERRAIN_TREE)) {
            immediate_warning_id = "#build_wood_cutters_next_to_trees";
            can_place = CAN_NOT_PLACE;
        }
    }

    if (special_flags & e_building_flag::Walls) {
        if (!map_terrain_all_tiles_in_radius_are(end, size.x, 0, TERRAIN_WALL)) {
            immediate_warning_id = "#build_towers_on_thick_walls";
            can_place = CAN_NOT_PLACE;
        }
    }

    if (!!(special_flags & e_building_flag::IgnoreNearbyEnemy) == false) {
        if (has_nearby_enemy(start.x(), start.y(), end.x(), end.y())) {
            immediate_warning_id = "#too_close_to_enemy_troops";
            can_place = CAN_NOT_PLACE;
        }
    }
    if ((!!(special_flags & e_building_flag::Road) && !!additional_req_param1) == true) {
        if (!map_terrain_is(end.grid_offset(), TERRAIN_ROAD)) {
            can_place = CAN_NOT_PLACE;
        }
    }

    if ((!!(special_flags & e_building_flag::Canals) && !!additional_req_param1) == true) {
        if (!map_terrain_is(end.grid_offset(), TERRAIN_CANAL)) {
            can_place = CAN_NOT_PLACE;
        }
    }

    if (special_flags & e_building_flag::FancyRoad) {
        if (!building_road::is_paved(end)) {
            can_place = CAN_NOT_PLACE;
        }
    }

    const auto &preview = building_planer_renderer::get(build_type);
    can_place = preview.can_place(*this, start, end, can_place);

    if (special_flags & e_building_flag::RiverAccess) {
        if (!map_tile_is_connected_to_open_water(end)) {
            immediate_warning_id = "#inland_lake_has_no_sea_access";
        }
    }
}

void build_planner::update_special_case_orientations_check() {
    int dir_relative;

    // for special buildings that require oriented terrain
    if (special_flags & e_building_flag::ShoreLine) {
        const auto &params = building_static_params::get(build_type);
        int shoreline_size = (additional_req_param1 > 0) ? additional_req_param1 : params.building_size;
        shore_orientation result = map_shore_determine_orientation(end, shoreline_size, true);
        if (special_flags & e_building_flag::FloodplainShore) {
            // in original Pharaoh, this actually is allowed to be built over the EDGE CORNERS.
            // it looks off, but it's legit!
            building_variant = 0;
            if (!result.match) {
                result = map_shore_determine_orientation(end, shoreline_size, true, true, TERRAIN_FLOODPLAIN);
                if (result.match && !map_terrain_exists_tile_in_area_with_type(end, size.x, TERRAIN_WATER)) { // correct for water
                    building_variant = 1;
                } else {
                    result.match = false;
                }
            } else if (map_terrain_exists_tile_in_area_with_type(end, size.x, TERRAIN_FLOODPLAIN)) { // correct the ShoreLine check for floodplains!
                result.match = false;
            }
        }

        dir_relative = city_view_relative_orientation(result.orientation_absolute);
        if (!result.match) {
            immediate_warning_id = "#building_not_next_to_water";
            can_place = CAN_NOT_PLACE;
        } else if (relative_orientation != dir_relative) {
            relative_orientation = dir_relative;
            update_orientations(false);
        }
    }

    if (special_flags & e_building_flag::Intersection) {
        bool match = map_orientation_for_venue_with_map_orientation(end, (e_venue_mode_orientation)additional_req_param1, &dir_relative);
        int city_direction = dir_relative / 2;
        if (!match) {
            //immediate_warning_id = additional_req_param2;
            can_place = CAN_NOT_PLACE;
        } else if (relative_orientation != city_direction) {
            relative_orientation = city_direction;
            update_orientations(false);
        }
    }

    const bool temple_altar = (special_flags & e_building_flag::TempleUpgradeAltar);
    const bool temple_oracle = (special_flags & e_building_flag::TempleUpgradeOracle);
    const int temple_options = (temple_altar ? etc_upgrade_altar : 0) | (temple_oracle ? etc_upgrade_oracle : 0);
    if (temple_altar || temple_oracle) {
        auto complex = building_at(end)->main()->dcast_temple_complex();
        if (!complex) {
            immediate_warning_id = "#must_have_completed_temple_first";
            can_place = CAN_NOT_PLACE;
        } else if (complex->has_upgrade((e_temple_compex_upgrade)temple_options) ) {
            immediate_warning_id = "#must_build_temple_complex_first";
            can_place = CAN_NOT_PLACE;
        } else {
            int dir_absolute = (5 - (complex->runtime_data().variant / 2)) % 4;
            dir_relative = city_view_relative_orientation(dir_absolute);
            relative_orientation = (1 + dir_relative) % 2;
            end = complex->tile();
            update_orientations(false);
        }
    }
}

void build_planner::update_unique_only_one_check() {
    if (!build_type) {
        return;
    }

    bool unique_already_placed = false;

    const auto &params = building_static_params::get(build_type);
    bool is_unique_building = params.is_unique_building();
    if (is_unique_building) {
        unique_already_placed = g_city.buildings.count_total(build_type);
    }

    // for unique buildings - only one can be placed inside the mission
    switch (build_type) {
    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
    case BUILDING_TEMPLE_COMPLEX_RA:
    case BUILDING_TEMPLE_COMPLEX_PTAH:
    case BUILDING_TEMPLE_COMPLEX_SETH:
    case BUILDING_TEMPLE_COMPLEX_BAST:
        //        case BUILDING_TEMPLE_COMPLEX_ALTAR:
        //        case BUILDING_TEMPLE_COMPLEX_ORACLE:
        if (g_city.buildings.has_temple_complex() && !game_features::gameplay_change_multiple_temple_complexes) {
            unique_already_placed = true;
        }
        break;
    default:
        break;
    }

    if (unique_already_placed) {
        immediate_warning_id = "#only_one_building_of_this_type";
        can_place = CAN_NOT_PLACE;
    }
}

void build_planner::update_coord_caches() {
    vec2i view_tile = lookup_tile_to_pixel(end);
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

void build_planner::update_orientations(bool check_if_changed) {
    int prev_orientation = relative_orientation;
    int prev_variant = building_variant;
   //int global_rotation = building_rotation_global_rotation();

    const auto &preview = building_planer_renderer::get(build_type);

    relative_orientation = preview.update_relative_orientation(*this, end, relative_orientation);
    building_variant = preview.update_building_variant(*this);

    relative_orientation = relative_orientation % 4;
    absolute_orientation = city_view_absolute_orientation(relative_orientation);

    // do not refresh graphics if nothing changed
    if (check_if_changed && relative_orientation == prev_orientation && building_variant == prev_variant) {
        return;
    }

    setup_build_graphics(); // reload graphics, tiles, etc.
    update_coord_caches();  // refresh caches
}

void build_planner::construction_record_view_position(vec2i pixel, tile2i point) {
    if (point == start) {
        start_offset_screen_x = pixel.x;
        start_offset_screen_y = pixel.y;
    }
}

void build_planner::dispatch_warnings() {
    if (!!immediate_warning_id) {
        events::emit(event_city_warning{ immediate_warning_id.c_str() });
    }

    if (!!extra_warning_id) {
        events::emit(event_city_warning{ extra_warning_id.c_str() });
    }
}

int build_planner::get_total_drag_size(int* x, int* y) {
    if (!game_features::gameui_show_construction_size || !(special_flags & e_building_flag::Draggable)
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
    if (!tile.valid()) {
        return;
    }

    if (in_progress) {
        return;
    }

    start = tile;
    end = tile;

    const auto &preview = building_planer_renderer::get(build_type);
    if (game_undo_start_build(build_type)) {
        in_progress = true;
        const bool can_start = preview.can_construction_start(*this, start);

        if (!can_start) {
            construction_cancel();
        }
    }
}

void build_planner::construction_cancel() {
    map_property_clear_constructing_and_deleted();
    if (in_progress && special_flags & e_building_flag::Draggable) {
        game_undo_restore_map(1);
        in_progress = false;
    } else {
        setup_build(BUILDING_NONE);
        //widget_sidebar_city_release_build_buttons();
    }

    custom_building_variant = 0;
    building_rotation_reset_rotation();
    update_orientations();
}

void build_planner::construction_update(tile2i tile) {
    end = tile;
    if (!end.valid()) {
        return;
    }

    if (!build_type || g_city.finance.is_out_of_money()) {
        total_cost = 0;
        return;
    }

    map_property_clear_constructing_and_deleted();
    uint16_t current_cost = building_static_params::get(build_type).get_cost();
    int global_rotation = building_rotation_global_rotation();
    int items_placed = 1;

    const auto &params = building_static_params::get(build_type);
    const auto &preview = building_planer_renderer::get(build_type);
    switch (build_type) {
    case BUILDING_CLEAR_LAND:
        last_items_cleared = building_construction_clear_land(true, start, end);
        items_placed = last_items_cleared;
        break;

    case BUILDING_LOW_BRIDGE:
    case BUILDING_UNUSED_SHIP_BRIDGE_83:
        items_placed = map_bridge_building_length();
        break;

    case BUILDING_HOUSE_VACANT_LOT:
        items_placed = place_houses(true, start.x(), start.y(), end.x(), end.y());
        break;

    case BUILDING_RESERVED_TRIUMPHAL_ARCH_56:
        mark_construction(tile, { 3, 3 }, ~TERRAIN_ROAD, false);
        break;

    case BUILDING_FORT_ARCHERS:
    case BUILDING_FORT_CHARIOTEERS:
    case BUILDING_FORT_INFANTRY:
        if (g_formations.num_batalions < 6) {
            vec2i offset = FORT_OFFSET[global_rotation][city_view_orientation() / 2];
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

void build_planner::check_road_access(building *b, tile2i tile, int size, int orientation) {
    if (!building_is_temple_complex(b->type)) {
        return;
    }

    const bool has_road = map_has_road_access_temple_complex(tile, orientation, true, nullptr);
    if (!has_road) {
        events::emit(event_construction_warning{ "#needs_road_access" });
    }
}

void build_planner::checks_generic_rules(building *b, tile2i tile, int size, int orientation) {
    if (!b) {
        return;
    }

    e_building_type type = b->type;
    check_road_access(b, tile, size, orientation);
    b->dcast()->on_place_checks();
}

void build_planner::construction_finalize() { // confirm final placement
    in_progress = false;

    dispatch_warnings();
    if (can_place != CAN_PLACE && !building_is_draggable(build_type)) { // this is the FINAL check!
        return;
    }

    // attempt placing, restore terrain data on failure
    const auto &params = building_static_params::get(build_type);
    if (!place()) {
        map_property_clear_constructing_and_deleted();
        if (building_type_any_of(build_type, { BUILDING_MUD_WALL, BUILDING_ROAD, BUILDING_IRRIGATION_DITCH })) {
            game_undo_restore_map(0);
        } else if (build_type == BUILDING_PLAZA || build_type == BUILDING_GARDENS) {
            game_undo_restore_map(1);
        } else if (build_type == BUILDING_LOW_BRIDGE || build_type == BUILDING_UNUSED_SHIP_BRIDGE_83) {
            map_bridge_reset_building_length();
        }

        return;
    }

    // final generic building warnings - these are in another file
    // TODO: bring these warnings over.
    checks_generic_rules(last_created_building, end, size.x, relative_orientation);
    bool should_recalc_ferry_routes = params.needs.shoreline;

    setup_building_variant(end, build_type);
    update_orientations(false);

    // update terrain data for certain special cases
    if (special_flags & e_building_flag::Meadow) {
        for (int y = end.y(); y < end.y() + size.y; y++) {
            for (int x = end.x(); x < end.x() + size.x; x++) {
                map_set_floodplain_growth(MAP_OFFSET(x, y), 0);
            }
        }
    }

    if (special_flags & e_building_flag::Road) {
        map_terrain_add_in_area(end, end.shifted(size.x - 1, size.y - 1), TERRAIN_ROAD);
        map_tiles_update_area_roads(end.x(), end.y(), 5);
        map_tiles_update_all_plazas();
    }

    if (special_flags & e_building_flag::Walls) {
        events::emit(event_building_update_walls{ end, 5 });
    }

    // consume resources for specific buildings (e.g. marble, granite)
    if (special_flags & e_building_flag::Resources) {
        events::emit(event_storageyards_remove_resource{ (e_resource)additional_req_param1, additional_req_param2 });
    }

    // finally, go over the rest of the stuff for all building types
    formation_move_herds_away(end);
    g_city.finance.process_construction(total_cost);
    game_undo_finish_build(total_cost);
    map_tiles_update_region_empty_land(false, start.shifted(-2, -2), end.shifted(size.x + 2, size.y + 2));
    map_routing_update_land();
    map_routing_update_walls();

    if (should_recalc_ferry_routes) {
        map_routing_update_ferry_routes();
    }
}

//////////////////////

void build_planner::update(tile2i cursor_tile) {
    if (!build_type) {
        return;
    }

    end = cursor_tile;
    update_coord_caches();

    immediate_warning_id = "";
    can_place = CAN_PLACE;
    update_obstructions_check();
    update_requirements_check();
    update_special_case_orientations_check();
    update_unique_only_one_check();
}

void build_planner::draw_flat_tile(vec2i pos, color color_mask, painter &ctx) {
    ctx.img_generic(image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED), pos, color_mask);
}

void build_planner::draw_bridge(tile2i tile, vec2i pixel, int type, painter &ctx) {
    int length, direction;
    int end_grid_offset = map_bridge_calculate_length_direction(tile.x(), tile.y(), &length, &direction);

    int dir = direction - city_view_orientation();
    if (dir < 0)
        dir += 8;

    bool blocked = false;
    if (type == BUILDING_UNUSED_SHIP_BRIDGE_83 && length < 5)
        blocked = true;
    else if (!end_grid_offset)
        blocked = true;

    if (g_city.finance.is_out_of_money())
        blocked = true;

    int x_delta, y_delta;
    switch (dir) {
    case DIR_0_TOP_RIGHT:
        x_delta = 29;
        y_delta = -15;
        break;
    case DIR_2_BOTTOM_RIGHT:
        x_delta = 29;
        y_delta = 15;
        break;
    case DIR_4_BOTTOM_LEFT:
        x_delta = -29;
        y_delta = 15;
        break;
    case DIR_6_TOP_LEFT:
        x_delta = -29;
        y_delta = -15;
        break;
    default:
        return;
    }
    if (blocked) {
        draw_flat_tile(ctx, pixel, length > 0 ? COLOR_MASK_GREEN : COLOR_MASK_RED);
        if (length > 1)
            draw_flat_tile(ctx, pixel + vec2i(x_delta * (length - 1), y_delta * (length - 1)), COLOR_MASK_RED);

    } else {
        if (dir == DIR_0_TOP_RIGHT || dir == DIR_6_TOP_LEFT) {
            for (int i = length - 1; i >= 0; i--) {
                int sprite_id = map_bridge_get_sprite_id(i, length, dir, type == BUILDING_UNUSED_SHIP_BRIDGE_83);
                city_draw_bridge_tile(ctx, pixel.x + x_delta * i, pixel.y + y_delta * i, sprite_id, COLOR_MASK_GREEN);
            }
        } else {
            for (int i = 0; i < length; i++) {
                int sprite_id = map_bridge_get_sprite_id(i, length, dir, type == BUILDING_UNUSED_SHIP_BRIDGE_83);
                city_draw_bridge_tile(ctx, pixel.x + x_delta * i, pixel.y + y_delta * i, sprite_id, COLOR_MASK_GREEN);
            }
        }
    }
}

int build_planner::is_blocked_for_building(tile2i tile, int size, blocked_tile_vec &blocked_tiles, uint32_t restricted_terrain) {
    int orientation_index = city_view_orientation() / 2;
    int blocked = 0;
    int num_tiles = (size * size);
    for (int i = 0; i < num_tiles; i++) {
        int offset = TILE_GRID_OFFSETS_PH[orientation_index][i];
        tile2i check_tile = tile.shifted(offset);
        bool tile_blocked = map_terrain_is(check_tile, restricted_terrain & TERRAIN_NOT_CLEAR)
            || (map_terrain_count_directly_adjacent_with_type(check_tile, TERRAIN_FLOODPLAIN) > 0)
            || (map_terrain_count_diagonally_adjacent_with_type(check_tile, TERRAIN_FLOODPLAIN) > 0)
            || map_has_figure_at(check_tile);

        blocked_tiles.push_back({ check_tile, tile_blocked });
        blocked += (tile_blocked ? 1 : 0);
    }

    return blocked;
}

void build_planner::draw_partially_blocked(painter &ctx, int fully_blocked, const blocked_tile_vec &blocked_tiles) {
    for (auto &tile : blocked_tiles) {
        vec2i pixel = lookup_tile_to_pixel(tile.tile);
        draw_flat_tile(ctx, pixel, (fully_blocked || tile.blocked) ? COLOR_MASK_RED_30 : COLOR_MASK_GREEN_30);
    }
}

int build_planner::tile_grid_offset(int orientation, int y) {
    return TILE_GRID_OFFSETS_PH[orientation][y];
}

void build_planner::draw_flat_tile(painter &ctx, vec2i pixel, color color_mask) {
    ctx.img_generic(image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED), pixel, color_mask);
}

void build_planner::draw(painter &ctx) {
    // empty building
    if (size.x < 1 || size.y < 1) {
        return;
    }

    vec2i pixel = pixel_coords_cache[0][0];
    const auto &preview = building_planer_renderer::get(build_type);
    if (can_place == CAN_NOT_PLACE) {
        // draw fully red (placement not allowed)
        preview.ghost_blocked(*this, ctx, start, end, pixel, /*fully_blocked*/true);
    } else if (tiles_blocked_total > 0) {
        // draw green blueprint with red (blocked) tiles
        preview.ghost_blocked(*this, ctx, start, end, pixel, /*fully_blocked*/false);
    } else if (!draw_as_constructing) {
        // draw normal building ghost (green)
        draw_graphics(ctx);
    }
}

void build_planner::draw_building_ghost(painter &ctx, int image_id, vec2i pixel, color color_mask) {
    auto& command = ImageDraw::create_command(render_command_t::ert_drawtile_full);
    command.image_id = image_id;
    command.pixel = pixel;
    command.mask = color_mask;
}

void build_planner::draw_graphics(painter &ctx) {
    // TODO: bring these all over the unified system
    // special graphics buildings
    vec2i pixel = pixel_coords_cache[0][0];
    const auto &preview = building_planer_renderer::get(build_type);
    preview.ghost_preview(*this, ctx, start, end, pixel);
}

bool build_planner::place() {
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
    const auto &params = building_static_params::get(build_type);
    const auto &preview = building_planer_renderer::get(build_type);
    int placement_cost = params.get_cost();

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

    case BUILDING_LOW_BRIDGE:
    case BUILDING_UNUSED_SHIP_BRIDGE_83: {
            placement_cost *= map_bridge_add(x, y, build_type == BUILDING_UNUSED_SHIP_BRIDGE_83);
        }
        break;

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
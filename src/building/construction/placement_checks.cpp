#include "build_planner.h"
#include "city/buildings.h"
#include "city/city_resource.h"
#include "city/city_finance.h"

#include "building/building.h"
#include "building/building_dock.h"
#include "building/building_road.h"
#include "building/building_temple_complex.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "city/city_fog_of_war.h"
#include "city/city_temple_complexes.h"
#include "game/game_config.h"
#include "grid/building.h"
#include "grid/figure.h"
#include "grid/floodplain.h"
#include "grid/grid.h"
#include "grid/water.h"

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

static bool is_tile_occupied_by_active_building(tile2i tile) {
    int bid = map_building_at(tile);
    if (!bid) {
        return false;
    }
    building* b = building_get(bid);
    if (!b || b->id <= 0 || b->is_deleted || b->state == BUILDING_STATE_DELETED_BY_PLAYER
        || b->state == BUILDING_STATE_UNUSED) {
        return false;
    }
    return true;
}

void build_planner::update_obstructions_check() {
    tiles_blocked_total = 0;
    int tiles_blocked_by_fog_only = 0;
    const auto& params = building_static_params::get(build_type);
    const auto& preview = placement_rules_of(build_type);
    const bool edge_margin = !draggable() && !params.flags.no_map_edge_margin;

    for (int row = 0; row < size.y; row++) {
        for (int column = 0; column < size.x; column++) {
            // check terrain at coords
            tile2i current_tile = tile_coord_cache[row][column];
            unsigned int restricted_terrain = TERRAIN_ALL;

            // special cases
            if (needMeadow() || needFloodplainShore() || needRoad() || needCanals()) {
                restricted_terrain -= TERRAIN_FLOODPLAIN;
            }

            bool can_blocked_by_floodplain_edge = !params.flags.is_farm;
            if (needRoad() || needIntersection() || needCanals()) {
                restricted_terrain -= TERRAIN_ROAD;
                can_blocked_by_floodplain_edge = false;
            }

            if (needRoad() || needCanals()) {
                restricted_terrain -= TERRAIN_CANAL;
            }

            if (needWalls()) {
                restricted_terrain -= TERRAIN_WALL;
            }

            if (needWater() || needShoreLine()) {
                restricted_terrain -= TERRAIN_WATER;
            }

            if (needTempleUpgradeAltar() || needTempleUpgradeOracle()) { // special case
                return;
            }


            tile_blocked_array[row][column] = false;
            const bool blocked_by_floodplain_edge
              = (can_blocked_by_floodplain_edge && map_get_floodplain_edge(current_tile));
            const bool inside_map
              = edge_margin ? map_grid_is_inside_building_area(current_tile) : map_grid_is_inside(current_tile, 1);
            const uint32_t ignore_terrain = preview.ghost_ignore_terrain(*this, current_tile);
            const uint32_t not_clear_mask = (restricted_terrain & TERRAIN_NOT_CLEAR) & ~ignore_terrain;
            const bool has_existing_building = is_tile_occupied_by_active_building(current_tile);
            const bool not_clear
              = inside_map && (map_terrain_is(current_tile, not_clear_mask) || has_existing_building);
            const bool allow_tile = inside_map && preview.ghost_allow_tile(*this, current_tile);
            const bool unexplored = !city_fog_of_war().is_explored(current_tile);
            const bool blocked = !inside_map || not_clear || !allow_tile || blocked_by_floodplain_edge;
            if (blocked || unexplored) {
                tile_blocked_array[row][column] = true;
                tiles_blocked_total++;
                tiles_blocked_by_fog_only += blocked ? 0 : 1;
            }
        }
    }

    if (tiles_blocked_total > 0) {
        immediate_warning = tiles_blocked_by_fog_only == tiles_blocked_total ? "#must_build_on_explored_land"
                                                                             : "#must_build_on_cleared_land";
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
    if (city_finance().is_out_of_money()) {
        // TODO: no money needed if building has zero cost?
        immediate_warning = "#out_of_credit";
        can_place = CAN_NOT_PLACE;
        return;
    }

    /////// special requirements
    //
    if (needResources()) {
        if (city_resource().yards_stored((e_resource)additional_req_param1) < additional_req_param2) {
            // immediate_warning_id = additional_req_param3;
            can_place = CAN_NOT_BUT_GREEN;
        }
    }

    if (needGroundwater()) {
        if (!map_terrain_exists_tile_in_radius_with_type(end, size.x, 0, TERRAIN_GROUNDWATER)) {
            immediate_warning = "#needs_groundwater";
            can_place = CAN_NOT_PLACE;
        }
    }
    if (needNearbyWater()) {
        if (!map_terrain_exists_tile_in_radius_with_type(end, size.x, 3, TERRAIN_WATER)
            && !map_terrain_exists_tile_in_radius_with_type(end, size.x, 3, TERRAIN_FLOODPLAIN)) {
            immediate_warning = "#building_not_next_to_water";
            can_place = CAN_NOT_PLACE;
        }
    }

    if (needMeadow()) {
        if (!map_terrain_exists_tile_in_radius_with_type(end, size.x, 1, TERRAIN_MEADOW)
            && !map_terrain_all_tiles_in_radius_are(end, size.x, 0, TERRAIN_FLOODPLAIN)) {
            immediate_warning = "#build_farms_on_meadow";
            can_place = CAN_NOT_PLACE;
        }
    }

    if (needRock()) {
        // OG: plain stone quarry accepts any ROCK bit; limestone/granite/sandstone/gem
        // require build_flags_is_kind_b (ROCK without ORE / monument-rock bits).
        const bool kind_b = (build_type == BUILDING_LIMESTONE_QUARRY || build_type == BUILDING_GRANITE_QUARRY
                             || build_type == BUILDING_SANDSTONE_QUARRY || build_type == BUILDING_GEMSTONE_MINE);
        const bool has_rock = kind_b ? map_terrain_exists_rock_kind_b_in_radius(end, size.x, 1)
                                     : map_terrain_exists_tile_in_radius_with_type(end, size.x, 1, TERRAIN_ROCK);
        if (!has_rock) {
            immediate_warning = "#build_next_to_rocky_areas";
            can_place = CAN_NOT_PLACE;
        }
    }

    if (needOre()) {
        if (!map_terrain_exists_tile_in_radius_with_type(end, size.x, 1, TERRAIN_ORE)) {
            immediate_warning = "#build_next_to_rocky_areas";
            can_place = CAN_NOT_PLACE;
        }
    }

    if (needTrees()) {
        if (!map_terrain_exists_tile_in_radius_with_type(end, size.x, 1, TERRAIN_SHRUB | TERRAIN_TREE)) {
            immediate_warning = "#build_wood_cutters_next_to_trees";
            can_place = CAN_NOT_PLACE;
        }
    }

    if (needWalls()) {
        if (!map_terrain_all_tiles_in_radius_are(end, size.x, 0, TERRAIN_WALL)) {
            immediate_warning = "#build_towers_on_thick_walls";
            can_place = CAN_NOT_PLACE;
        }
    }

    if (!ignoreNearbyEnemy()) {
        if (has_nearby_enemy(start.x(), start.y(), end.x(), end.y())) {
            immediate_warning = "#too_close_to_enemy_troops";
            can_place = CAN_NOT_PLACE;
        }
    }
    if (needRoad() && !!additional_req_param1) {
        if (!map_terrain_is(end.grid_offset(), TERRAIN_ROAD)) {
            can_place = CAN_NOT_PLACE;
        }
    }

    if (needCanals() && !!additional_req_param1) {
        if (!map_terrain_is(end.grid_offset(), TERRAIN_CANAL)) {
            can_place = CAN_NOT_PLACE;
        }
    }

    if (needFancyRoad()) {
        if (!building_road::is_paved(end)) {
            can_place = CAN_NOT_PLACE;
        }
    }

    const auto& preview = placement_rules_of(build_type);
    can_place = preview.can_place(*this, start, end, can_place);

    if (needRiverAccess()) {
        if (!map_tile_is_connected_to_open_water(end)) {
            immediate_warning = "#inland_lake_has_no_sea_access";
        }
    }
}

void build_planner::update_special_case_orientations_check() {
    int dir_relative;

    // for special buildings that require oriented terrain
    if (needShoreLine()) {
        const auto& params = building_static_params::get(build_type);
        int shoreline_size = (additional_req_param1 > 0) ? additional_req_param1 : params.building_size;
        shore_orientation result = map_shore_determine_orientation(end, shoreline_size, true);
        if (needFloodplainShore()) {
            // in original Pharaoh, this actually is allowed to be built over the EDGE CORNERS.
            // it looks off, but it's legit!
            building_variant = 0;
            if (!result.match) {
                result = map_shore_determine_orientation(end, shoreline_size, true, true, TERRAIN_FLOODPLAIN);
                if (result.match && !map_terrain_exists_tile_in_area_with_type(end, size.x, TERRAIN_WATER)) { // correct
                                                                                                              // for
                                                                                                              // water
                    building_variant = 1;
                } else {
                    result.match = false;
                }
            } else if (map_terrain_exists_tile_in_area_with_type(end, size.x, TERRAIN_FLOODPLAIN)) { // correct the
                                                                                                     // ShoreLine check
                                                                                                     // for floodplains!
                result.match = false;
            }
        }

        dir_relative = map_view_relative_orientation(result.orientation_absolute);
        if (!result.match) {
            immediate_warning = "#building_not_next_to_water";
            can_place = CAN_NOT_PLACE;
        } else if (relative_orientation != dir_relative) {
            relative_orientation = dir_relative;
            update_orientations(false);
        }
    }

    if (needIntersection()) {
        bool match = map_orientation_for_venue_with_map_orientation(end,
          (e_venue_mode_orientation)additional_req_param1, &dir_relative);
        int city_direction = dir_relative / 2;
        if (!match) {
            // immediate_warning_id = additional_req_param2;
            can_place = CAN_NOT_PLACE;
        } else if (relative_orientation != city_direction) {
            relative_orientation = city_direction;
            update_orientations(false);
        }
    }

    const bool temple_altar = needTempleUpgradeAltar();
    const bool temple_oracle = is_flag(PLANNER_RULE_TEMPLE_UPGRADE_ORACLE);
    const int temple_options = (temple_altar ? etc_upgrade_altar : 0) | (temple_oracle ? etc_upgrade_oracle : 0);
    if (temple_altar || temple_oracle) {
        auto complex = city_buildings().at(end)->main()->dcast_temple_complex();
        if (!complex) {
            immediate_warning = "#must_have_completed_temple_first";
            can_place = CAN_NOT_PLACE;
        } else if (complex->has_upgrade((e_temple_compex_upgrade)temple_options)) {
            immediate_warning = "#must_build_temple_complex_first";
            can_place = CAN_NOT_PLACE;
        } else {
            int dir_absolute = (5 - (complex->runtime_data().variant / 2)) % 4;
            dir_relative = map_view_relative_orientation(dir_absolute);
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

    const auto& params = building_static_params::get(build_type);
    bool is_unique_building = params.is_unique_building();
    if (is_unique_building) {
        unique_already_placed = city_building_stats().count_total(build_type);
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
        if (city_temple_complexes().has_any() && !game_features::gameplay_change_multiple_temple_complexes) {
            unique_already_placed = true;
        }
        break;
    case BUILDING_PERSONAL_MANSION:
    case BUILDING_FAMILY_MANSION:
    case BUILDING_DYNASTY_MANSION:
        // OG mansion_placed: one mansion of any tier.
        unique_already_placed = city_building_stats().has_mansion();
        break;
    case BUILDING_VILLAGE_PALACE:
    case BUILDING_TOWN_PALACE:
    case BUILDING_CITY_PALACE:
    case BUILDING_VILLAGE_PALACE_UP:
    case BUILDING_TOWN_PALACE_UP:
        // OG palace_placed: one palace of any tier.
        unique_already_placed = city_building_stats().has_palace();
        break;
    case BUILDING_TAX_COLLECTOR:
    case BUILDING_TAX_COLLECTOR_UPGRADED:
        // OG: cannot place tax office without a palace.
        if (!city_building_stats().has_palace()) {
            immediate_warning = "#no_taxes_without_palace";
            can_place = CAN_NOT_PLACE;
            return;
        }
        break;
    default:
        break;
    }

    if (unique_already_placed) {
        immediate_warning = "#only_one_building_of_this_type";
        can_place = CAN_NOT_PLACE;
    }
}

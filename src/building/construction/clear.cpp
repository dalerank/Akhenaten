#include "clear.h"

#include "building/building.h"
#include "building/industry.h"
#include "building/building_farm.h"
#include "city/warning.h"
#include "figuretype/migrant.h"
#include "game/undo.h"
#include "graphics/window.h"
#include "grid/aqueduct.h"
#include "grid/bridge.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/grid.h"
#include "grid/property.h"
#include "grid/routing/routing_terrain.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "config/config.h"
#include "window/popup_dialog.h"

struct clear_confirm_t {
    tile2i cstart;
    tile2i cend;
    int bridge_confirmed;
    int fort_confirmed;
};

clear_confirm_t g_clear_confirm;

static building* get_deletable_building(int grid_offset) {
    int building_id = map_building_at(grid_offset);
    if (!building_id)
        return 0;

    building* b = building_get(building_id)->main();
    if (b->type == BUILDING_BURNING_RUIN || b->type == BUILDING_UNUSED_NATIVE_CROPS_93 || b->type == BUILDING_UNUSED_NATIVE_HUT_88
        || b->type == BUILDING_UNUSED_NATIVE_MEETING_89) {
        return 0;
    }

    if (b->state == BUILDING_STATE_DELETED_BY_PLAYER || b->is_deleted) {
        return 0;
    }

    return b;
}

static int clear_land_confirmed(bool measure_only, tile2i start, tile2i end) {
    auto& confirm = g_clear_confirm;
    int items_placed = 0;
    game_undo_restore_building_state();
    game_undo_restore_map(0);

    grid_area area = map_grid_get_area(start, end);

    int visual_feedback_on_delete = config_get(CONFIG_UI_VISUAL_FEEDBACK_ON_DELETE);
    for (int y = area.tmin.y(), endy = area.tmax.y(); y <= endy; y++) {
        for (int x = area.tmin.x(), endx = area.tmax.x(); x <= endx; x++) {
            int grid_offset = MAP_OFFSET(x, y);
            if (map_terrain_is(grid_offset, TERRAIN_ROCK | TERRAIN_ELEVATION | TERRAIN_DUNE)) {
                continue;
            }

            if (measure_only && visual_feedback_on_delete) {
                building* b = get_deletable_building(grid_offset);
                if (map_property_is_deleted(grid_offset) || (b && map_property_is_deleted(b->tile.grid_offset()))) {
                    continue;
                }

                map_building_tiles_mark_deleting(grid_offset);
                
                if (map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
                    if (b)
                        items_placed++;
                } else if (map_terrain_is(grid_offset, TERRAIN_WATER)) { // keep the "bridge is free" bug from C3
                    continue;
                } else if (map_terrain_is(grid_offset, TERRAIN_CANAL)
                           || (map_terrain_is(grid_offset, TERRAIN_NOT_CLEAR)
                           && map_terrain_is(grid_offset, TERRAIN_CLEARABLE)
                           && !map_terrain_exists_tile_in_radius_with_type(tile2i(x, y), 1, 1, TERRAIN_FLOODPLAIN))) {
                    items_placed++;
                }
                continue;
            }
            if (map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
                building* b = get_deletable_building(grid_offset);
                if (!b) {
                    continue;
                }

                if (b->type == BUILDING_FORT_GROUND || building_is_fort(b->type)) {
                    if (!measure_only && confirm.fort_confirmed != 1) {
                        continue;
                    }

                    if (!measure_only && confirm.fort_confirmed == 1) {
                        game_undo_disable();
                    }
                }

                if (b->house_size && b->house_population && !measure_only) {
                    figure_create_homeless(b->tile, b->house_population);
                    b->house_population = 0;
                }

                if (building_is_floodplain_farm(*b) && config_get(CONFIG_GP_CH_SOIL_DEPLETION)) {
                    b->dcast_farm()->deplete_soil();
                }

                if (b->state != BUILDING_STATE_DELETED_BY_PLAYER) {
                    items_placed++;
                    game_undo_add_building(b);
                }
                b->state = BUILDING_STATE_DELETED_BY_PLAYER;
                b->is_deleted = 1;
                building* space = b;
                for (int i = 0; i < 99; i++) {
                    if (space->prev_part_building_id <= 0)
                        break;

                    space = building_get(space->prev_part_building_id);
                    game_undo_add_building(space);
                    space->state = BUILDING_STATE_DELETED_BY_PLAYER;
                }
                space = b;
                for (int i = 0; i < 9; i++) {
                    space = space->next();
                    if (space->id <= 0)
                        break;
                    game_undo_add_building(space);
                    space->state = BUILDING_STATE_DELETED_BY_PLAYER;
                }
            } else if (map_terrain_is(grid_offset, TERRAIN_CANAL)) {
                map_terrain_remove(grid_offset, TERRAIN_CLEARABLE);
                items_placed++;
                map_aqueduct_remove(grid_offset);
            } else if (map_terrain_is(grid_offset, TERRAIN_WATER)) {
                if (!measure_only && map_bridge_count_figures(grid_offset) > 0)
                    city_warning_show(WARNING_PEOPLE_ON_BRIDGE);
                else if (confirm.bridge_confirmed == 1) {
                    map_bridge_remove(grid_offset, measure_only);
                    items_placed++;
                }
            } else if (map_terrain_is(grid_offset, TERRAIN_NOT_CLEAR)) {
                if (map_terrain_is(grid_offset, TERRAIN_ROAD))
                    map_property_clear_plaza_or_earthquake(grid_offset);

                map_terrain_remove(grid_offset, TERRAIN_CLEARABLE);
                if (map_terrain_is(grid_offset, TERRAIN_CLEARABLE))
                    items_placed++;
            }
        }
    }
    if (!measure_only || !visual_feedback_on_delete) {
        int radius;
        if (area.tmax.x() - area.tmin.x() <= area.tmax.y() - area.tmin.y()) {
            radius = area.tmax.y() - area.tmin.y() + 3;
        } else {
            radius = area.tmax.x() - area.tmin.x() + 3;
        }

        const int x_min = area.tmin.x();
        const int y_min = area.tmin.y();
        const int x_max = area.tmax.x();
        const int y_max = area.tmax.y();
        map_tiles_update_region_empty_land(true, area.tmin, area.tmax);
        map_tiles_update_region_meadow(x_min, y_min, x_max, y_max);
        map_tiles_update_region_rubble(x_min, y_min, x_max, y_max);
        map_tiles_update_all_gardens();
        map_tiles_update_area_roads(x_min, y_min, radius);
        map_tiles_update_all_plazas();
        map_tiles_update_area_walls(x_min, y_min, radius);
        map_tiles_update_region_aqueducts(x_min - 3, y_min - 3, x_max + 3, y_max + 3);
    }

    if (!measure_only) {
        map_routing_update_land();
        map_routing_update_walls();
        map_routing_update_water();
        if (config_get(CONFIG_GP_CH_IMMEDIATELY_DELETE_BUILDINGS))
            building_update_state();

        window_invalidate();
    }
    return items_placed;
}

static void confirm_delete_fort(bool accepted) {
    auto& confirm = g_clear_confirm;
    confirm.fort_confirmed = accepted ? 1 : -1;

    clear_land_confirmed(0, confirm.cstart, confirm.cend);
}

static void confirm_delete_bridge(bool accepted) {
    auto& confirm = g_clear_confirm;
    if (accepted)
        confirm.bridge_confirmed = 1;
    else
        confirm.bridge_confirmed = -1;
    clear_land_confirmed(0, confirm.cstart, confirm.cend);
}

int building_construction_clear_land(bool measure_only, tile2i start, tile2i end) {
    auto& confirm = g_clear_confirm;
    confirm.fort_confirmed = 0;
    confirm.bridge_confirmed = 0;
    if (measure_only) {
        return clear_land_confirmed(measure_only, start, end);
    }

    grid_area area = map_grid_get_area(start, end);

    int ask_confirm_bridge = 0;
    int ask_confirm_fort = 0;
    map_grid_area_foreach(area.tmin, area.tmax, [&] (tile2i tile) {
        int grid_offset = tile.grid_offset();
        int building_id = map_building_at(grid_offset);
        if (building_id) {
            building *b = building_get(building_id);
            if (building_is_fort(b->type) || b->type == BUILDING_FORT_GROUND) {
                ask_confirm_fort = 1;
            }
        }

        if (map_is_bridge(grid_offset)) {
            ask_confirm_bridge = 1;
        }
    });

    confirm.cstart = start;
    confirm.cend = end;

    if (ask_confirm_fort) {
        window_popup_dialog_show(POPUP_DIALOG_DELETE_FORT, confirm_delete_fort, e_popup_btns_yesno);
        return -1;
    } else if (ask_confirm_bridge) {
        window_popup_dialog_show(POPUP_DIALOG_DELETE_BRIDGE, confirm_delete_bridge, e_popup_btns_yesno);
        return -1;
    } else {
        return clear_land_confirmed(measure_only, start, end);
    }
}

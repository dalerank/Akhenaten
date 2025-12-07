#include "clear.h"

#include "building/building_house.h"
#include "building/building_farm.h"
#include "building/building_wall.h"
#include "city/city.h"
#include "game/game_events.h"
#include "city/city_warnings.h"
#include "figuretype/figure_homeless.h"
#include "game/undo.h"
#include "graphics/window.h"
#include "grid/canals.h"
#include "grid/bridge.h"
#include "grid/gardens.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/grid.h"
#include "grid/property.h"
#include "grid/routing/routing_terrain.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "game/game_config.h"
#include "window/popup_dialog.h"

struct clear_confirm_t {
    tile2i cstart = tile2i();
    tile2i cend = tile2i();
    bool bridge_confirmed = false;
    bool fort_confirmed = false;
};

static building* get_deletable_building(int grid_offset) {
    int building_id = map_building_at(grid_offset);
    if (!building_id) {
        return nullptr;
    }

    building* b = building_get(building_id)->main();
    if (b->type == BUILDING_BURNING_RUIN || b->type == BUILDING_UNUSED_NATIVE_CROPS_93 || b->type == BUILDING_UNUSED_NATIVE_HUT_88
        || b->type == BUILDING_UNUSED_NATIVE_MEETING_89) {
        return 0;
    }

    if (b->state == BUILDING_STATE_DELETED_BY_PLAYER || b->is_deleted) {
        return nullptr;
    }

    if (!b->dcast()->is_deletable()) {
        return nullptr;
    }

    return b;
}

static int clear_land_confirmed(bool measure_only, clear_confirm_t confirm) {
    int items_placed = 0;
    game_undo_restore_building_state();
    game_undo_restore_map(0);

    grid_area area = map_grid_get_area(confirm.cstart, confirm.cend);

    const int visual_feedback_on_delete = !!game_features::gameui_visual_feedback_on_delete;
    for (int y = area.tmin.y(), endy = area.tmax.y(); y <= endy; y++) {
        for (int x = area.tmin.x(), endx = area.tmax.x(); x <= endx; x++) {
            int grid_offset = MAP_OFFSET(x, y);
            if (map_terrain_is(grid_offset, TERRAIN_ROCK | TERRAIN_ELEVATION | TERRAIN_DUNE)) {
                continue;
            }

            if (measure_only && visual_feedback_on_delete) {
                building* b = get_deletable_building(grid_offset);
                if (map_property_is_deleted(grid_offset) || (b && map_property_is_deleted(b->tile))) {
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

                if (b->dcast_fort_ground() || b->dcast_fort()) {
                    if (!measure_only && confirm.fort_confirmed != 1) {
                        continue;
                    }

                    if (!measure_only && confirm.fort_confirmed == 1) {
                        game_undo_disable();
                    }
                }

                auto house = b->dcast_house();
                if (house && house->house_population() > 0 && !measure_only) {
                    events::emit(event_create_homeless{ b->tile, house->house_population(), SOURCE_LOCATION });
                    house->runtime_data().population = 0;
                }

                if (building_is_floodplain_farm(*b) && !!game_features::gameplay_change_soil_depletion) {
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
                map_canal_remove(grid_offset);
            } else if (map_terrain_is(grid_offset, TERRAIN_WATER)) {
                if (!measure_only && map_bridge_count_figures(grid_offset) > 0)
                    events::emit(event_city_warning{ "#cannot_demolish_bridge_with_people" });
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
        map_tiles_gardens_update_all();
        map_tiles_update_area_roads(x_min, y_min, radius);
        map_tiles_update_all_plazas();
        building_mud_wall::update_area_walls(area.tmin, radius);
        map_tiles_update_region_canals(tile2i(x_min - 3, y_min - 3), tile2i(x_max + 3, y_max + 3));
    }

    if (!measure_only) {
        map_routing_update_land();
        map_routing_update_walls();
        map_routing_update_water();
        if (!!game_features::gameplay_change_immediate_delete) {
            building_update_state();
        }

    }
    return items_placed;
}

int building_construction_clear_land(bool measure_only, tile2i start, tile2i end) {
    clear_confirm_t confirm{};
    confirm.cstart = start;
    confirm.cend = end;
    confirm.fort_confirmed = false;
    confirm.bridge_confirmed = false;
    if (measure_only) {
        return clear_land_confirmed(measure_only, confirm);
    }

    grid_area area = map_grid_get_area(start, end);

    int ask_confirm_bridge = 0;
    int ask_confirm_fort = 0;
    map_grid_area_foreach(area.tmin, area.tmax, [&] (tile2i tile) {
        int building_id = map_building_at(tile);
        building *b = building_get(building_id);
        ask_confirm_fort |= (building_id && (b->dcast_fort() || b->dcast_fort_ground()));
        ask_confirm_bridge |= map_is_bridge(tile);
    });

    confirm.cstart = start;
    confirm.cend = end;

    if (ask_confirm_fort) {
        popup_dialog::show_yesno("#popup_dialog_delete_fort", [confirm] () mutable {
            confirm.fort_confirmed = true;
            clear_land_confirmed(0, confirm);
        });
        return -1;
    } 
    
    if (ask_confirm_bridge) {
        popup_dialog::show_yesno("#popup_dialog_delete_bridge", [confirm] () mutable {
            confirm.bridge_confirmed = true;
            clear_land_confirmed(0, confirm);
        });
        return -1;
    }

    return clear_land_confirmed(measure_only, confirm);
}

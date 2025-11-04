#include "undo.h"

#include "building/building_storage_yard.h"
#include "building/building_house.h"
#include "city/city_finance.h"
#include "game/game_events.h"
#include "city/city_resource.h"
#include "city/city_buildings.h"
#include "game/resource.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/window.h"
#include "grid/canals.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/grid.h"
#include "grid/image.h"
#include "grid/property.h"
#include "grid/routing/routing_terrain.h"
#include "grid/sprite.h"
#include "grid/terrain.h"
#include "city/city.h"
#include "scenario/earthquake.h"

#include <string.h>

#define MAX_UNDO_BUILDINGS 500

struct undo_data_t {
    int available;
    int ready;
    int timeout_ticks;
    int building_cost;
    int num_buildings;
    int type;
    building buildings[MAX_UNDO_BUILDINGS];
    int newhouses_offsets[MAX_UNDO_BUILDINGS];
    int newhouses_num;
};

undo_data_t g_undo_data;

int game_can_undo(void) {
    auto &data = g_undo_data;
    return data.ready && data.available;
}
void game_undo_disable(void) {
    auto &data = g_undo_data;
    data.available = 0;
}
void game_undo_add_building(building* b) {
    auto &data = g_undo_data;
    if (b->id <= 0)
        return;
    data.num_buildings = 0;
    int is_on_list = 0;
    for (int i = 0; i < MAX_UNDO_BUILDINGS; i++) {
        if (data.buildings[i].id)
            data.num_buildings++;
        if (data.buildings[i].id == b->id)
            is_on_list = 1;
    }
    if (!is_on_list) {
        for (int i = 0; i < MAX_UNDO_BUILDINGS; i++) {
            if (!data.buildings[i].id) {
                data.num_buildings++;
                memcpy(&data.buildings[i], b, sizeof(building));
                return;
            }
        }
        data.available = 0;
    }
}
void game_undo_adjust_building(building* b) {
    auto &data = g_undo_data;
    for (int i = 0; i < MAX_UNDO_BUILDINGS; i++) {
        if (data.buildings[i].id == b->id) {
            // found! update the building now
            memcpy(&data.buildings[i], b, sizeof(building));
        }
    }
}
int game_undo_contains_building(int building_id) {
    auto &data = g_undo_data;
    if (building_id <= 0 || !game_can_undo())
        return 0;
    if (data.num_buildings <= 0)
        return 0;
    for (int i = 0; i < MAX_UNDO_BUILDINGS; i++) {
        if (data.buildings[i].id == building_id)
            return 1;
    }
    return 0;
}

static void clear_buildings(void) {
    auto &data = g_undo_data;
    data.num_buildings = 0;
    memset(data.buildings, 0, MAX_UNDO_BUILDINGS * sizeof(building));
}

int game_undo_start_build(int type) {
    auto &data = g_undo_data;
    data.ready = 0;
    data.available = 1;
    data.timeout_ticks = 0;
    data.building_cost = 0;
    data.type = type;
    clear_buildings();
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_UNDO) {
            data.available = 0;
            return 0;
        }
        if (b->state == BUILDING_STATE_DELETED_BY_PLAYER)
            data.available = 0;
    }

    map_image_backup();
    map_terrain_backup();
    map_canal_backup();
    map_property_backup();
    map_sprite_backup();

    return 1;
}
void game_undo_restore_building_state(void) {
    auto &data = g_undo_data;
    for (int i = 0; i < data.num_buildings; i++) {
        if (data.buildings[i].id) {
            building* b = building_get(data.buildings[i].id);
            if (b->state == BUILDING_STATE_DELETED_BY_PLAYER)
                b->state = BUILDING_STATE_VALID;
            b->is_deleted = 0;
        }
    }
    clear_buildings();
}

static void restore_map_images(void) {
    int map_width = scenario_map_data()->width;
    int map_height = scenario_map_data()->height;
    //    int map_width, map_height;
    //    map_grid_size(&map_width, &map_height);
    for (int y = 0; y < map_height; y++) {
        for (int x = 0; x < map_width; x++) {
            int grid_offset = MAP_OFFSET(x, y);
            if (!map_building_at(grid_offset))
                map_image_restore_at(grid_offset);
        }
    }
}

void game_undo_restore_map(int include_properties) {
    map_terrain_restore();
    map_canal_restore();
    if (include_properties)
        map_property_restore();
    restore_map_images();
}
void game_undo_finish_build(int cost) {
    auto &data = g_undo_data;
    data.ready = 1;
    data.timeout_ticks = 500;
    data.building_cost = cost;
}

static void add_building_to_terrain(building* b) {
    if (b->id <= 0) {
        return;
    }

    int size = building_static_params::get(b->type).building_size;
    map_building_tiles_add(b->id, b->tile, size, 0, 0);
    b->state = BUILDING_STATE_VALID;

    auto main = b->main();
    main->dcast()->on_undo();
}

static void restore_housing(building* b) {
    auto house = b->dcast_house();
    auto &housed = house->runtime_data();
    auto &data = g_undo_data;
    int size = housed.hsize;
    for (int x = b->tile.x(); x < b->tile.x() + size; x++)
        for (int y = b->tile.y(); y < b->tile.y() + size; y++) {
            int grid_offset = MAP_OFFSET(x, y);
            data.newhouses_offsets[data.newhouses_num] = grid_offset + 1;
            data.newhouses_num++;
            //            if (x == b->tile.x() && y == b->tile.y()) {
            //                b->house_size = 1;
            //                b->house_is_merged = 0;
            //                map_building_tiles_add(b->id, x, y, 1,
            //                                       image_id_from_group(GROUP_BUILDING_HOUSE_TENT), TERRAIN_BUILDING);
            //            } else {
            //                building *new_b = building_create(BUILDING_HOUSE_VACANT_LOT, x, y);
            //                if (new_b->id > 0)
            //                    map_building_tiles_add(new_b->id, x, y, 1,
            //                                           image_id_from_group(GROUP_BUILDING_HOUSE_TENT),
            //                                           TERRAIN_BUILDING);
            //            }
        }
}

void game_undo_perform() {
    auto &data = g_undo_data;
    if (!game_can_undo())
        return;
    data.available = 0;
    g_city.finance.process_construction(-data.building_cost);
    if (data.type == BUILDING_CLEAR_LAND) {
        for (int i = 0; i < data.num_buildings; i++) {
            if (data.buildings[i].id) {
                building* b = building_get(data.buildings[i].id);
                if (building_is_house(data.buildings[i].type) && true) {
                    restore_housing(&data.buildings[i]);
                } else {
                    memcpy(b, &data.buildings[i], sizeof(building));
                    b->reset_impl();
                    if (b->type == BUILDING_STORAGE_YARD || b->type == BUILDING_GRANARY) {
                        if (!building_storage_restore(b->storage_id))
                            building_storage_reset_building_ids();
                    }
                    add_building_to_terrain(b);
                }
            }
        }
        map_terrain_restore();
        map_canal_restore();
        map_sprite_restore();
        map_image_restore();
        map_property_restore();
        map_property_clear_constructing_and_deleted();
    } else if (building_type_any_of((e_building_type)data.type, make_array(BUILDING_IRRIGATION_DITCH, BUILDING_ROAD, BUILDING_MUD_WALL))) {
        map_terrain_restore();
        map_canal_restore();
        restore_map_images();
    } else if (data.type == BUILDING_LOW_BRIDGE || data.type == BUILDING_UNUSED_SHIP_BRIDGE_83) {
        map_terrain_restore();
        map_sprite_restore();
        restore_map_images();
    } else if (data.type == BUILDING_PLAZA || data.type == BUILDING_GARDENS) {
        map_terrain_restore();
        map_canal_restore();
        map_property_restore();
        restore_map_images();
    } else if (data.num_buildings) {
        if (data.type == BUILDING_WATER_LIFT) {
            map_terrain_restore();
            map_canal_restore();
            restore_map_images();
        }
        for (int i = 0; i < data.num_buildings; i++) {
            if (data.buildings[i].id) {
                building* b = building_get(data.buildings[i].id);
                if (b->type == BUILDING_ORACLE || (b->type >= BUILDING_TEMPLE_COMPLEX_OSIRIS && b->type <= BUILDING_TEMPLE_COMPLEX_BAST)) {
                    events::emit(event_storageyards_add_resource{ RESOURCE_MARBLE, 2 });
                }

                b->state = BUILDING_STATE_UNDO;
            }
        }
    }
    map_routing_update_land();
    map_routing_update_walls();
    data.num_buildings = 0;
    int vacant_lot_image = building_static_params::get(BUILDING_HOUSE_VACANT_LOT).base_img();
    for (int i = 0; data.newhouses_offsets[i] != 0; i++) {
        int grid_offset = data.newhouses_offsets[i] - 1;

        tile2i tile(grid_offset);

        building* new_house = building_create(BUILDING_HOUSE_VACANT_LOT, tile, 0);
        if (new_house->id > 0) {
            map_building_tiles_add(new_house->id, tile, 1, vacant_lot_image, TERRAIN_BUILDING);
        }

        map_image_set(grid_offset, vacant_lot_image);

        data.newhouses_offsets[i] = 0;
        data.newhouses_num--;
    }
}

void game_undo_reduce_time_available(void) {
    auto &data = g_undo_data;
    if (!game_can_undo())
        return;
    if (data.timeout_ticks <= 0 || scenario_earthquake_is_in_progress()) {
        data.available = 0;
        clear_buildings();
        return;
    }
    data.timeout_ticks--;
    switch (data.type) {
    case BUILDING_CLEAR_LAND:
    case BUILDING_IRRIGATION_DITCH:
    case BUILDING_ROAD:
    case BUILDING_MUD_WALL:
    case BUILDING_LOW_BRIDGE:
    case BUILDING_UNUSED_SHIP_BRIDGE_83:
    case BUILDING_PLAZA:
    case BUILDING_GARDENS:
        return;

    default:
        break;
    }
    if (data.num_buildings <= 0) {
        data.available = 0;
        return;
    }

    if (data.type == BUILDING_HOUSE_VACANT_LOT) {
        for (int i = 0; i < data.num_buildings; i++) {
            auto house = building_get(data.buildings[i].id)->dcast_house();

            if (house && house->house_population() > 0) {
                // no undo on a new house where people moved in
                data.available = 0;
                return;
            }
        }
    }
    for (int i = 0; i < data.num_buildings; i++) {
        if (data.buildings[i].id) {
            building* b = building_get(data.buildings[i].id);
            if (b->state == BUILDING_STATE_UNDO || b->state == BUILDING_STATE_RUBBLE
                || b->state == BUILDING_STATE_DELETED_BY_GAME) {
                data.available = 0;
                return;
            }
            if (b->type != data.buildings[i].type || b->tile.grid_offset() != data.buildings[i].tile.grid_offset()) {
                data.available = 0;
                return;
            }
        }
    }
}

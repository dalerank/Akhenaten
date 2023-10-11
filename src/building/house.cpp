#include "house.h"

#include "building/building.h"
#include "core/game_environment.h"
#include "game/resource.h"
#include "game/tutorial.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/grid.h"
#include "grid/image.h"
#include "grid/random.h"
#include "grid/terrain.h"
#include "config/config.h"

#define MAX_DIR 4

// #define OFFSET_C3(x,y) (x + GRID_SIZE_C3 * y)
// #define OFFSET_PH(x,y) (x + GRID_SIZE_PH * y)

// static const int HOUSE_TILE_OFFSETS_C3[] = {
//         OFFSET_C3(0, 0), OFFSET_C3(1, 0), OFFSET_C3(0, 1), OFFSET_C3(1, 1), // 2x2
//         OFFSET_C3(2, 0), OFFSET_C3(2, 1), OFFSET_C3(2, 2), OFFSET_C3(1, 2), OFFSET_C3(0, 2), // 3x3
//         OFFSET_C3(3, 0), OFFSET_C3(3, 1), OFFSET_C3(3, 2), OFFSET_C3(3, 3), OFFSET_C3(2, 3), OFFSET_C3(1, 3),
//         OFFSET_C3(0, 3) // 4x4
// };
static const int HOUSE_TILE_OFFSETS_PH[] = {
  GRID_OFFSET(0, 0),
  GRID_OFFSET(1, 0),
  GRID_OFFSET(0, 1),
  GRID_OFFSET(1, 1), // 2x2
  GRID_OFFSET(2, 0),
  GRID_OFFSET(2, 1),
  GRID_OFFSET(2, 2),
  GRID_OFFSET(1, 2),
  GRID_OFFSET(0, 2), // 3x3
  GRID_OFFSET(3, 0),
  GRID_OFFSET(3, 1),
  GRID_OFFSET(3, 2),
  GRID_OFFSET(3, 3),
  GRID_OFFSET(2, 3),
  GRID_OFFSET(1, 3),
  GRID_OFFSET(0, 3) // 4x4
};

struct house_image_t {
    int collection;
    int group;
    int offset;
    int num_types;
};

const house_image_t HOUSE_IMAGE[20] = {
  {GROUP_BUILDING_HOUSE_TENT, 0, 2},     {GROUP_BUILDING_HOUSE_TENT, 2, 2},     {GROUP_BUILDING_HOUSE_SHACK, 0, 2},
  {GROUP_BUILDING_HOUSE_SHACK, 2, 2},    {GROUP_BUILDING_HOUSE_HOVEL, 0, 2},    {GROUP_BUILDING_HOUSE_HOVEL, 2, 2},
  {GROUP_BUILDING_HOUSE_CASA, 0, 2},     {GROUP_BUILDING_HOUSE_CASA, 2, 2},     {GROUP_BUILDING_HOUSE_INSULA_1, 0, 2},
  {GROUP_BUILDING_HOUSE_INSULA_1, 2, 2}, {GROUP_BUILDING_HOUSE_INSULA_2, 0, 2}, {GROUP_BUILDING_HOUSE_INSULA_2, 2, 2},
  {GROUP_BUILDING_HOUSE_VILLA_1, 0, 2},  {GROUP_BUILDING_HOUSE_VILLA_1, 2, 2},  {GROUP_BUILDING_HOUSE_VILLA_2, 0, 1},
  {GROUP_BUILDING_HOUSE_VILLA_2, 1, 1},  {GROUP_BUILDING_HOUSE_PALACE_1, 0, 1}, {GROUP_BUILDING_HOUSE_PALACE_1, 1, 1},
  {GROUP_BUILDING_HOUSE_PALACE_2, 0, 1}, {GROUP_BUILDING_HOUSE_PALACE_2, 1, 1},
};

struct expand_direction_t {
    int x;
    int y;
    int offset;
};

expand_direction_t expand_direction;

const expand_direction_t EXPAND_DIRECTION_DELTA_PH[MAX_DIR]
  = {{0, 0, 0}, {-1, -1, -GRID_LENGTH - 1}, {-1, 0, -1}, {0, -1, -GRID_LENGTH}};
;

struct merge_data_t {
    int x;
    int y;
    int inventory[INVENTORY_MAX];
    int population;
};

merge_data_t g_merge_data;

int house_tile_offsets(int i) {
    return HOUSE_TILE_OFFSETS_PH[i];
}
expand_direction_t expand_delta(int i) {
    return EXPAND_DIRECTION_DELTA_PH[i];
}

static void create_vacant_lot(int x, int y, int image_id) {
    building* b = building_create(BUILDING_HOUSE_VACANT_LOT, x, y, 0);
    b->house_population = 0;
    b->distance_from_entry = 0;
    map_building_tiles_add(b->id, b->tile, 1, image_id, TERRAIN_BUILDING);
}

void building_house_change_to(building* house, e_building_type type) {
    tutorial_on_house_evolve((e_house_level)(type - BUILDING_HOUSE_VACANT_LOT));
    house->type = type;
    house->subtype.house_level = house->type - BUILDING_HOUSE_VACANT_LOT;
    int image_id = image_id_from_group(HOUSE_IMAGE[house->subtype.house_level].collection, HOUSE_IMAGE[house->subtype.house_level].group);
    if (house->house_is_merged) {
        image_id += 4;
        if (HOUSE_IMAGE[house->subtype.house_level].offset)
            image_id += 1;

    } else {
        image_id += HOUSE_IMAGE[house->subtype.house_level].offset;
        image_id += map_random_get(house->tile.grid_offset()) & (HOUSE_IMAGE[house->subtype.house_level].num_types - 1);
    }
    map_building_tiles_add(house->id, house->tile, house->size, image_id, TERRAIN_BUILDING);
}
void building_house_change_to_vacant_lot(building* house) {
    house->type = BUILDING_HOUSE_VACANT_LOT;
    house->subtype.house_level = house->type - BUILDING_HOUSE_VACANT_LOT;
    int image_id = image_id_from_group(GROUP_BUILDING_HOUSE_VACANT_LOT);
    if (house->house_is_merged) {
        map_building_tiles_remove(house->id, house->tile.x(), house->tile.y());
        house->house_is_merged = 0;
        house->size = house->house_size = 1;
        map_building_tiles_add(house->id, house->tile, 1, image_id, TERRAIN_BUILDING);

        create_vacant_lot(house->tile.x() + 1, house->tile.y(), image_id);
        create_vacant_lot(house->tile.x(), house->tile.y() + 1, image_id);
        create_vacant_lot(house->tile.x() + 1, house->tile.y() + 1, image_id);
    } else {
        map_image_set(house->tile.grid_offset(), image_id);
    }
}

static void prepare_for_merge(int building_id, int num_tiles) {
    for (int i = 0; i < INVENTORY_MAX; i++) {
        g_merge_data.inventory[i] = 0;
    }

    g_merge_data.population = 0;
    int grid_offset = MAP_OFFSET(g_merge_data.x, g_merge_data.y);
    for (int i = 0; i < num_tiles; i++) {
        int house_offset = grid_offset + house_tile_offsets(i);
        if (map_terrain_is(house_offset, TERRAIN_BUILDING)) {
            building* house = building_at(house_offset);
            if (house->id != building_id && house->house_size) {
                g_merge_data.population += house->house_population;
                for (int inv = 0; inv < INVENTORY_MAX; inv++) {
                    g_merge_data.inventory[inv] += house->data.house.inventory[inv];
                    house->house_population = 0;
                    house->state = BUILDING_STATE_DELETED_BY_GAME;
                }
            }
        }
    }
}
static void merge(building* b) {
    prepare_for_merge(b->id, 4);

    b->size = b->house_size = 2;
    b->house_population += g_merge_data.population;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        b->data.house.inventory[i] += g_merge_data.inventory[i];
    }
    int image_id
      = image_id_from_group(HOUSE_IMAGE[b->subtype.house_level].collection, HOUSE_IMAGE[b->subtype.house_level].group)
        + 4;
    if (HOUSE_IMAGE[b->subtype.house_level].offset)
        image_id += 1;

    map_building_tiles_remove(b->id, b->tile.x(), b->tile.y());
    b->tile.set(g_merge_data.x, g_merge_data.y);
    //    b->tile.x() = merge_data.x;
    //    b->tile.y() = merge_data.y;
    //    b->tile.grid_offset() = MAP_OFFSET(b->tile.x(), b->tile.y());
    b->house_is_merged = 1;
    map_building_tiles_add(b->id, b->tile, 2, image_id, TERRAIN_BUILDING);
}

void building_house_merge(building* house) {
    if (house->house_is_merged)
        return;
    if (!config_get(CONFIG_GP_CH_ALL_HOUSES_MERGE)) {
        if ((map_random_get(house->tile.grid_offset()) & 7) >= 5)
            return;
    }
    int num_house_tiles = 0;
    for (int i = 0; i < 4; i++) {
        int tile_offset = house->tile.grid_offset() + house_tile_offsets(i);
        if (map_terrain_is(tile_offset, TERRAIN_BUILDING)) {
            building* other_house = building_at(tile_offset);
            if (other_house->id == house->id)
                num_house_tiles++;
            else if (other_house->state == BUILDING_STATE_VALID && other_house->house_size
                     && other_house->subtype.house_level == house->subtype.house_level
                     && !other_house->house_is_merged) {
                num_house_tiles++;
            }
        }
    }
    if (num_house_tiles == 4) {
        g_merge_data.x = house->tile.x() + expand_delta(0).x;
        g_merge_data.y = house->tile.y() + expand_delta(0).y;
        merge(house);
    }
}
int building_house_can_expand(building* house, int num_tiles) {
    // merge with other houses
    for (int dir = 0; dir < MAX_DIR; dir++) {
        int base_offset = expand_delta(dir).offset + house->tile.grid_offset();
        int ok_tiles = 0;
        for (int i = 0; i < num_tiles; i++) {
            int tile_offset = base_offset + house_tile_offsets(i);
            if (map_terrain_is(tile_offset, TERRAIN_BUILDING)) {
                building* other_house = building_at(tile_offset);
                if (other_house->id == house->id)
                    ok_tiles++;
                else if (other_house->state == BUILDING_STATE_VALID && other_house->house_size) {
                    if (other_house->subtype.house_level <= house->subtype.house_level)
                        ok_tiles++;
                }
            }
        }
        if (ok_tiles == num_tiles) {
            g_merge_data.x = house->tile.x() + expand_delta(dir).x;
            g_merge_data.y = house->tile.y() + expand_delta(dir).y;
            return 1;
        }
    }
    // merge with houses and empty terrain
    for (int dir = 0; dir < MAX_DIR; dir++) {
        int base_offset = expand_delta(dir).offset + house->tile.grid_offset();
        int ok_tiles = 0;
        for (int i = 0; i < num_tiles; i++) {
            int tile_offset = base_offset + house_tile_offsets(i);
            if (!map_terrain_is(tile_offset, TERRAIN_NOT_CLEAR))
                ok_tiles++;
            else if (map_terrain_is(tile_offset, TERRAIN_BUILDING)) {
                building* other_house = building_at(tile_offset);
                if (other_house->id == house->id)
                    ok_tiles++;
                else if (other_house->state == BUILDING_STATE_VALID && other_house->house_size) {
                    if (other_house->subtype.house_level <= house->subtype.house_level)
                        ok_tiles++;
                }
            }
        }
        if (ok_tiles == num_tiles) {
            g_merge_data.x = house->tile.x() + expand_delta(dir).x;
            g_merge_data.y = house->tile.y() + expand_delta(dir).y;
            return 1;
        }
    }
    // merge with houses, empty terrain and gardens
    for (int dir = 0; dir < MAX_DIR; dir++) {
        int base_offset = expand_delta(dir).offset + house->tile.grid_offset();
        int ok_tiles = 0;
        for (int i = 0; i < num_tiles; i++) {
            int tile_offset = base_offset + house_tile_offsets(i);
            if (!map_terrain_is(tile_offset, TERRAIN_NOT_CLEAR))
                ok_tiles++;
            else if (map_terrain_is(tile_offset, TERRAIN_BUILDING)) {
                building* other_house = building_at(tile_offset);
                if (other_house->id == house->id)
                    ok_tiles++;
                else if (other_house->state == BUILDING_STATE_VALID && other_house->house_size) {
                    if (other_house->subtype.house_level <= house->subtype.house_level)
                        ok_tiles++;
                }
            } else if (map_terrain_is(tile_offset, TERRAIN_GARDEN)
                       && !config_get(CONFIG_GP_CH_HOUSES_DONT_EXPAND_INTO_GARDENS))
                ok_tiles++;
        }
        if (ok_tiles == num_tiles) {
            g_merge_data.x = house->tile.x() + expand_delta(dir).x;
            g_merge_data.y = house->tile.y() + expand_delta(dir).y;
            return 1;
        }
    }
    house->data.house.no_space_to_expand = 1;
    return 0;
}

static int house_image_group(int level) {
    return image_id_from_group(HOUSE_IMAGE[level].collection, HOUSE_IMAGE[level].group) + HOUSE_IMAGE[level].offset;
}

static void create_house_tile(e_building_type type, int x, int y, int image_id, int population, const int* inventory) {
    building* house = building_create(type, x, y, 0);
    house->house_population = population;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        house->data.house.inventory[i] = inventory[i];
    }
    house->distance_from_entry = 0;
    map_building_tiles_add(house->id, house->tile, 1, image_id + (map_random_get(house->tile.grid_offset()) & 1), TERRAIN_BUILDING);
}

static void split_size2(building* house, e_building_type new_type) {
    int inventory_per_tile[INVENTORY_MAX];
    int inventory_remainder[INVENTORY_MAX];
    for (int i = 0; i < INVENTORY_MAX; i++) {
        inventory_per_tile[i] = house->data.house.inventory[i] / 4;
        inventory_remainder[i] = house->data.house.inventory[i] % 4;
    }
    int population_per_tile = house->house_population / 4;
    int population_remainder = house->house_population % 4;

    map_building_tiles_remove(house->id, house->tile.x(), house->tile.y());

    // main tile
    house->type = new_type;
    house->subtype.house_level = house->type - BUILDING_HOUSE_VACANT_LOT;
    house->size = house->house_size = 1;
    house->house_is_merged = 0;
    house->house_population = population_per_tile + population_remainder;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        house->data.house.inventory[i] = inventory_per_tile[i] + inventory_remainder[i];
    }
    house->distance_from_entry = 0;

    int image_id = house_image_group(house->subtype.house_level);
    map_building_tiles_add(house->id, house->tile, house->size, image_id + (map_random_get(house->tile.grid_offset()) & 1), TERRAIN_BUILDING);

    // the other tiles (new buildings)
    create_house_tile(
      house->type, house->tile.x() + 1, house->tile.y(), image_id, population_per_tile, inventory_per_tile);
    create_house_tile(
      house->type, house->tile.x(), house->tile.y() + 1, image_id, population_per_tile, inventory_per_tile);
    create_house_tile(
      house->type, house->tile.x() + 1, house->tile.y() + 1, image_id, population_per_tile, inventory_per_tile);
}
static void split_size3(building* house) {
    int inventory_per_tile[INVENTORY_MAX];
    int inventory_remainder[INVENTORY_MAX];
    for (int i = 0; i < INVENTORY_MAX; i++) {
        inventory_per_tile[i] = house->data.house.inventory[i] / 9;
        inventory_remainder[i] = house->data.house.inventory[i] % 9;
    }
    int population_per_tile = house->house_population / 9;
    int population_remainder = house->house_population % 9;

    map_building_tiles_remove(house->id, house->tile.x(), house->tile.y());

    // main tile
    house->type = BUILDING_HOUSE_MEDIUM_INSULA;
    house->subtype.house_level = house->type - BUILDING_HOUSE_VACANT_LOT;
    house->size = house->house_size = 1;
    house->house_is_merged = 0;
    house->house_population = population_per_tile + population_remainder;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        house->data.house.inventory[i] = inventory_per_tile[i] + inventory_remainder[i];
    }
    house->distance_from_entry = 0;

    int image_id = house_image_group(house->subtype.house_level);
    map_building_tiles_add(house->id, house->tile, house->size, image_id + (map_random_get(house->tile.grid_offset()) & 1), TERRAIN_BUILDING);

    // the other tiles (new buildings)
    create_house_tile(house->type, house->tile.x(), house->tile.y() + 1, image_id, population_per_tile, inventory_per_tile);
    create_house_tile(house->type, house->tile.x() + 1, house->tile.y() + 1, image_id, population_per_tile, inventory_per_tile);
    create_house_tile(house->type, house->tile.x() + 2, house->tile.y() + 1, image_id, population_per_tile, inventory_per_tile);
    create_house_tile(house->type, house->tile.x(), house->tile.y() + 2, image_id, population_per_tile, inventory_per_tile);
    create_house_tile(house->type, house->tile.x() + 1, house->tile.y() + 2, image_id, population_per_tile, inventory_per_tile);
    create_house_tile(house->type, house->tile.x() + 2, house->tile.y() + 2, image_id, population_per_tile, inventory_per_tile);
}
static void split(building* house, int num_tiles) {
    int grid_offset = MAP_OFFSET(g_merge_data.x, g_merge_data.y);
    for (int i = 0; i < num_tiles; i++) {
        int tile_offset = grid_offset + house_tile_offsets(i);
        if (map_terrain_is(tile_offset, TERRAIN_BUILDING)) {
            building* other_house = building_at(tile_offset);
            if (other_house->id != house->id && other_house->house_size) {
                if (other_house->house_is_merged == 1)
                    split_size2(other_house, other_house->type);
                else if (other_house->house_size == 2)
                    split_size2(other_house, BUILDING_HOUSE_MEDIUM_INSULA);
                else if (other_house->house_size == 3)
                    split_size3(other_house);
            }
        }
    }
}

/// OLD STUFF

void building_house_expand_to_large_insula(building* house) {
    split(house, 4);
    prepare_for_merge(house->id, 4);

    house->type = BUILDING_HOUSE_LARGE_INSULA;
    house->subtype.house_level = HOUSE_LARGE_INSULA;
    house->size = house->house_size = 2;
    house->house_population += g_merge_data.population;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        house->data.house.inventory[i] += g_merge_data.inventory[i];
    }
    int image_id = house_image_group(house->subtype.house_level) + (map_random_get(house->tile.grid_offset()) & 1);
    map_building_tiles_remove(house->id, house->tile.x(), house->tile.y());
    house->tile.set(g_merge_data.x, g_merge_data.y);
    //    house->tile.x() = merge_data.x;
    //    house->tile.y() = merge_data.y;
    //    house->tile.grid_offset() = MAP_OFFSET(house->tile.x(), house->tile.y());
    map_building_tiles_add(house->id, house->tile, house->size, image_id, TERRAIN_BUILDING);
}
void building_house_expand_to_large_villa(building* house) {
    split(house, 9);
    prepare_for_merge(house->id, 9);

    house->type = BUILDING_HOUSE_LARGE_VILLA;
    house->subtype.house_level = HOUSE_LARGE_VILLA;
    house->size = house->house_size = 3;
    house->house_population += g_merge_data.population;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        house->data.house.inventory[i] += g_merge_data.inventory[i];
    }
    int image_id = house_image_group(house->subtype.house_level);
    map_building_tiles_remove(house->id, house->tile.x(), house->tile.y());
    house->tile.set(g_merge_data.x, g_merge_data.y);
    //    house->tile.x() = merge_data.x;
    //    house->tile.y() = merge_data.y;
    //    house->tile.grid_offset() = MAP_OFFSET(house->tile.x(), house->tile.y());
    map_building_tiles_add(house->id, house->tile, house->size, image_id, TERRAIN_BUILDING);
}
void building_house_expand_to_large_palace(building* house) {
    split(house, 16);
    prepare_for_merge(house->id, 16);

    house->type = BUILDING_HOUSE_LARGE_PALACE;
    house->subtype.house_level = HOUSE_LARGE_PALACE;
    house->size = house->house_size = 4;
    house->house_population += g_merge_data.population;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        house->data.house.inventory[i] += g_merge_data.inventory[i];
    }
    int image_id = house_image_group(house->subtype.house_level);
    map_building_tiles_remove(house->id, house->tile.x(), house->tile.y());
    house->tile.set(g_merge_data.x, g_merge_data.y);
    //    house->tile.x() = merge_data.x;
    //    house->tile.y() = merge_data.y;
    //    house->tile.grid_offset() = MAP_OFFSET(house->tile.x(), house->tile.y());
    map_building_tiles_add(house->id, house->tile, house->size, image_id, TERRAIN_BUILDING);
}

void building_house_devolve_from_large_insula(building* house) {
    split_size2(house, BUILDING_HOUSE_MEDIUM_INSULA);
}

void building_house_devolve_from_large_villa(building* house) {
    int inventory_per_tile[INVENTORY_MAX];
    int inventory_remainder[INVENTORY_MAX];

    for (int i = 0; i < INVENTORY_MAX; i++) {
        inventory_per_tile[i] = house->data.house.inventory[i] / 6;
        inventory_remainder[i] = house->data.house.inventory[i] % 6;
    }

    int population_per_tile = house->house_population / 6;
    int population_remainder = house->house_population % 6;

    map_building_tiles_remove(house->id, house->tile.x(), house->tile.y());

    // main tile
    house->type = BUILDING_HOUSE_MEDIUM_VILLA;
    house->subtype.house_level = house->type - BUILDING_HOUSE_VACANT_LOT;
    house->size = house->house_size = 2;
    house->house_is_merged = 0;
    house->house_population = population_per_tile + population_remainder;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        house->data.house.inventory[i] = inventory_per_tile[i] + inventory_remainder[i];
    }
    house->distance_from_entry = 0;

    int image_id = house_image_group(house->subtype.house_level);
    map_building_tiles_add(house->id, house->tile, house->size, image_id + (map_random_get(house->tile.grid_offset()) & 1), TERRAIN_BUILDING);

    // the other tiles (new buildings)
    image_id = house_image_group(HOUSE_MEDIUM_INSULA);
    create_house_tile(BUILDING_HOUSE_MEDIUM_INSULA, house->tile.x() + 2, house->tile.y(), image_id, population_per_tile,inventory_per_tile);
    create_house_tile(BUILDING_HOUSE_MEDIUM_INSULA, house->tile.x() + 2, house->tile.y() + 1, image_id, population_per_tile, inventory_per_tile);
    create_house_tile(BUILDING_HOUSE_MEDIUM_INSULA, house->tile.x(), house->tile.y() + 2, image_id, population_per_tile, inventory_per_tile);
    create_house_tile(BUILDING_HOUSE_MEDIUM_INSULA, house->tile.x() + 1, house->tile.y() + 2, image_id, population_per_tile, inventory_per_tile);
    create_house_tile(BUILDING_HOUSE_MEDIUM_INSULA, house->tile.x() + 2, house->tile.y() + 2, image_id, population_per_tile, inventory_per_tile);
}

void building_house_devolve_from_large_palace(building* house) {
    int inventory_per_tile[INVENTORY_MAX];
    int inventory_remainder[INVENTORY_MAX];
    for (int i = 0; i < INVENTORY_MAX; i++) {
        inventory_per_tile[i] = house->data.house.inventory[i] / 8;
        inventory_remainder[i] = house->data.house.inventory[i] % 8;
    }
    int population_per_tile = house->house_population / 8;
    int population_remainder = house->house_population % 8;

    map_building_tiles_remove(house->id, house->tile.x(), house->tile.y());

    // main tile
    house->type = BUILDING_HOUSE_MEDIUM_PALACE;
    house->subtype.house_level = house->type - BUILDING_HOUSE_VACANT_LOT;
    house->size = house->house_size = 3;
    house->house_is_merged = 0;
    house->house_population = population_per_tile + population_remainder;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        house->data.house.inventory[i] = inventory_per_tile[i] + inventory_remainder[i];
    }
    house->distance_from_entry = 0;

    int image_id = house_image_group(house->subtype.house_level);
    map_building_tiles_add(house->id, house->tile, house->size, image_id, TERRAIN_BUILDING);

    // the other tiles (new buildings)
    image_id = house_image_group(HOUSE_MEDIUM_INSULA);
    create_house_tile(BUILDING_HOUSE_MEDIUM_INSULA, house->tile.x() + 3, house->tile.y(), image_id, population_per_tile, inventory_per_tile);
    create_house_tile(BUILDING_HOUSE_MEDIUM_INSULA, house->tile.x() + 3, house->tile.y() + 1, image_id, population_per_tile, inventory_per_tile);
    create_house_tile(BUILDING_HOUSE_MEDIUM_INSULA, house->tile.x() + 3, house->tile.y() + 2, image_id, population_per_tile, inventory_per_tile);
    create_house_tile(BUILDING_HOUSE_MEDIUM_INSULA, house->tile.x(), house->tile.y() + 3, image_id, population_per_tile, inventory_per_tile);
    create_house_tile(BUILDING_HOUSE_MEDIUM_INSULA, house->tile.x() + 1, house->tile.y() + 3, image_id, population_per_tile, inventory_per_tile);
    create_house_tile(BUILDING_HOUSE_MEDIUM_INSULA, house->tile.x() + 2, house->tile.y() + 3, image_id, population_per_tile, inventory_per_tile);
    create_house_tile(BUILDING_HOUSE_MEDIUM_INSULA, house->tile.x() + 3, house->tile.y() + 3, image_id, population_per_tile, inventory_per_tile);
}

void building_house_check_for_corruption(building* house) {
    house->data.house.no_space_to_expand = 0;

    // house offset is corrupted??
    if (house->tile.grid_offset() != MAP_OFFSET(house->tile.x(), house->tile.y())
        || map_building_at(house->tile.grid_offset()) != house->id) {
        int map_width = scenario_map_data()->width;
        int map_height = scenario_map_data()->height;
        //        int map_width, map_height;
        //        map_grid_size(&map_width, &map_height); // get map size and store in temp vars

        // go through tiles and find tile belonging to the house
        for (int y = 0; y < map_height; y++) {
            for (int x = 0; x < map_width; x++) {
                int grid_offset = MAP_OFFSET(x, y); // get offset of current tile (global map tile offset)
                if (map_building_at(grid_offset) == house->id) { // does this tile belong to the house I'm searching for??
                    house->tile.set(grid_offset);
                    //                    house->tile.grid_offset() = grid_offset; // set house offset to this tile's
                    //                    offset (i.e. lowest x & y; north-west corner) house->tile.x() =
                    //                    MAP_X(grid_offset); // set house coords (x) to tile's coords (x)
                    //                    house->tile.y() = MAP_Y(grid_offset); // set house coords (y) to tile's coords
                    //                    (y) building_totals_add_corrupted_house(0);
                    return;
                }
            }
        }
        //        building_totals_add_corrupted_house(1);
        house->state = BUILDING_STATE_RUBBLE;
    }
}

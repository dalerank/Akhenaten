#include "building_house.h"

#include "building/building.h"
#include "city/warnings.h"
#include "city/population.h"
#include "city/resource.h"
#include "core/game_environment.h"
#include "city/labor.h"
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
#include "js/js_game.h"

#define MAX_DIR 4

buildings::model_t<building_house_vacant> house_vacant_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_house_models);
void config_load_house_models() {
    house_vacant_m.load();
}

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

struct house_image_t : public image_desc {
    int num_types;
    e_image_id img_desc_id = IMG_NONE;
};

const house_image_t HOUSE_IMAGE[20] = {
    {0, 0, 0, 2, IMG_HOUSE_HUT},
    {0, 0, 2, 2, IMG_HOUSE_HUT},
    {0, 0, 0, 2, IMG_HOUSE_SHANTY},
    {0, 0, 2, 2, IMG_HOUSE_SHANTY},
    {0, 0, 0, 2, IMG_HOUSE_COTTAGE},
    {0, 0, 2, 2, IMG_HOUSE_COTTAGE},
    {0, 0, 0, 2, IMG_HOUSE_HOMESTEAD},
    {0, 0, 2, 2, IMG_HOUSE_HOMESTEAD},
    {0, 0, 0, 2, IMG_HOUSE_APARTMENT},
    {0, 0, 2, 2, IMG_HOUSE_APARTMENT},
    {GROUP_BUILDING_HOUSE_RESIDENCE, 0, 2},
    {GROUP_BUILDING_HOUSE_RESIDENCE, 2, 2},
    {GROUP_BUILDING_HOUSE_MANOR, 0, 2},
    {GROUP_BUILDING_HOUSE_MANOR, 2, 2},
    {GROUP_BUILDING_HOUSE_ELEGANT_MANOR, 0, 1},
    {GROUP_BUILDING_HOUSE_ELEGANT_MANOR, 1, 1},
    {GROUP_BUILDING_HOUSE_ESTATE, 0, 1},
    {GROUP_BUILDING_HOUSE_ESTATE, 1, 1},
    {GROUP_BUILDING_HOUSE_PALATIAL, 0, 1},
    {GROUP_BUILDING_HOUSE_PALATIAL, 1, 1},
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

void building_house::on_undo() {
    /*nothing*/
}

void building_house::create_vacant_lot(tile2i tile, int image_id) {
    building* b = building_create(BUILDING_HOUSE_VACANT_LOT, tile, 0);
    b->house_population = 0;
    b->distance_from_entry = 0;
    map_building_tiles_add(b->id, b->tile, 1, image_id, TERRAIN_BUILDING);
}

template<bool use_offset>
static int house_image_group(int level) {
    int image_id = 0;
    const auto &house_img_desc = HOUSE_IMAGE[level];
    if (house_img_desc.img_desc_id) {
        image_id = image_group(house_img_desc.img_desc_id);
    } else {
        image_id = image_id_from_group(house_img_desc.pack, house_img_desc.id);
    }

    return image_id + (use_offset ? house_img_desc.offset : 0);
}

void building_house_change_to(building* house, e_building_type type) {
    tutorial_on_house_evolve((e_house_level)(type - BUILDING_HOUSE_VACANT_LOT));
    house->type = type;
    house->subtype.house_level = (e_house_level)(house->type - BUILDING_HOUSE_VACANT_LOT);
    
    int image_id = house_image_group<false>(house->subtype.house_level);
    if (house->house_is_merged) {
        image_id += 4;
        if (HOUSE_IMAGE[house->subtype.house_level].offset) {
            image_id += 1;
        }
    } else {
        image_id += HOUSE_IMAGE[house->subtype.house_level].offset;
        image_id += map_random_get(house->tile.grid_offset()) & (HOUSE_IMAGE[house->subtype.house_level].num_types - 1);
    }
    map_building_tiles_add(house->id, house->tile, house->size, image_id, TERRAIN_BUILDING);
}

void building_house::change_to_vacant_lot() {
    base.house_population = 0;
    base.type = BUILDING_HOUSE_VACANT_LOT;
    base.subtype.house_level = (e_house_level)(base.type - BUILDING_HOUSE_VACANT_LOT);
    int vacant_lot_id = house_vacant_m.anim["base"].first_img();
    if (base.house_is_merged) {
        map_building_tiles_remove(base.id, base.tile);
        base.house_is_merged = 0;
        base.size = base.house_size = 1;
        map_building_tiles_add(base.id, base.tile, 1, vacant_lot_id, TERRAIN_BUILDING);

        building_house::create_vacant_lot(base.tile.shifted(1, 0), vacant_lot_id);
        building_house::create_vacant_lot(base.tile.shifted(0, 1), vacant_lot_id);
        building_house::create_vacant_lot(base.tile.shifted(1, 1), vacant_lot_id);
    } else {
        map_image_set(base.tile.grid_offset(), vacant_lot_id);
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
    int image_id = house_image_group<false>(b->subtype.house_level) + 4;

    if (HOUSE_IMAGE[b->subtype.house_level].offset) {
        image_id += 1;
    }

    map_building_tiles_remove(b->id, b->tile);
    b->tile.set(g_merge_data.x, g_merge_data.y);

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
            if (other_house->id == house->id) {
                num_house_tiles++;
            } else if (other_house->state == BUILDING_STATE_VALID && other_house->house_size
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
                if (other_house->id == house->id) {
                    ok_tiles++;
                } else if (other_house->state == BUILDING_STATE_VALID && other_house->house_size) {
                    if (other_house->subtype.house_level <= house->subtype.house_level) {
                        ok_tiles++;
                    }
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
            if (!map_terrain_is(tile_offset, TERRAIN_NOT_CLEAR)) {
                ok_tiles++;
            } else if (map_terrain_is(tile_offset, TERRAIN_BUILDING)) {
                building* other_house = building_at(tile_offset);
                if (other_house->id == house->id) {
                    ok_tiles++;
                } else if (other_house->state == BUILDING_STATE_VALID && other_house->house_size) {
                    if (other_house->subtype.house_level <= house->subtype.house_level)
                        ok_tiles++;
                }
            } else if (map_terrain_is(tile_offset, TERRAIN_GARDEN) && !config_get(CONFIG_GP_CH_HOUSES_DONT_EXPAND_INTO_GARDENS)) {
                ok_tiles++;
            }
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

static void create_house_tile(e_building_type type, tile2i tile, int image_id, int population, const int* inventory) {
    building* house = building_create(type, tile, 0);
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

    map_building_tiles_remove(house->id, house->tile);

    // main tile
    house->type = new_type;
    house->subtype.house_level = (e_house_level)(house->type - BUILDING_HOUSE_VACANT_LOT);
    house->size = house->house_size = 1;
    house->house_is_merged = 0;
    house->house_population = population_per_tile + population_remainder;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        house->data.house.inventory[i] = inventory_per_tile[i] + inventory_remainder[i];
    }
    house->distance_from_entry = 0;

    int image_id = house_image_group<true>(house->subtype.house_level);
    map_building_tiles_add(house->id, house->tile, house->size, image_id + (map_random_get(house->tile.grid_offset()) & 1), TERRAIN_BUILDING);

    // the other tiles (new buildings)
    create_house_tile(house->type, house->tile.shifted(1, 0), image_id, population_per_tile, inventory_per_tile);
    create_house_tile(house->type, house->tile.shifted(0, 1), image_id, population_per_tile, inventory_per_tile);
    create_house_tile(house->type, house->tile.shifted(1, 1), image_id, population_per_tile, inventory_per_tile);
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

    map_building_tiles_remove(house->id, house->tile);

    // main tile
    house->type = BUILDING_HOUSE_SPACIOUS_APARTMENT;
    house->subtype.house_level = (e_house_level)(house->type - BUILDING_HOUSE_VACANT_LOT);
    house->size = house->house_size = 1;
    house->house_is_merged = 0;
    house->house_population = population_per_tile + population_remainder;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        house->data.house.inventory[i] = inventory_per_tile[i] + inventory_remainder[i];
    }
    house->distance_from_entry = 0;

    int image_id = house_image_group<true>(house->subtype.house_level);
    map_building_tiles_add(house->id, house->tile, house->size, image_id + (map_random_get(house->tile.grid_offset()) & 1), TERRAIN_BUILDING);

    // the other tiles (new buildings)
    create_house_tile(house->type, house->tile.shifted(0, 1), image_id, population_per_tile, inventory_per_tile);
    create_house_tile(house->type, house->tile.shifted(1, 1), image_id, population_per_tile, inventory_per_tile);
    create_house_tile(house->type, house->tile.shifted(2, 1), image_id, population_per_tile, inventory_per_tile);
    create_house_tile(house->type, house->tile.shifted(0, 2), image_id, population_per_tile, inventory_per_tile);
    create_house_tile(house->type, house->tile.shifted(1, 2), image_id, population_per_tile, inventory_per_tile);
    create_house_tile(house->type, house->tile.shifted(2, 2), image_id, population_per_tile, inventory_per_tile);
}
static void split(building* house, int num_tiles) {
    int grid_offset = MAP_OFFSET(g_merge_data.x, g_merge_data.y);
    for (int i = 0; i < num_tiles; i++) {
        int tile_offset = grid_offset + house_tile_offsets(i);
        if (map_terrain_is(tile_offset, TERRAIN_BUILDING)) {
            building* other_house = building_at(tile_offset);
            if (other_house->id != house->id && other_house->house_size) {
                if (other_house->house_is_merged == 1) {
                    split_size2(other_house, other_house->type);
                } else if (other_house->house_size == 2) {
                    split_size2(other_house, BUILDING_HOUSE_SPACIOUS_APARTMENT);
                } else if (other_house->house_size == 3) {
                    split_size3(other_house);
                }
            }
        }
    }
}

void building_house_expand_to_large_insula(building* house) {
    split(house, 4);
    prepare_for_merge(house->id, 4);

    house->type = BUILDING_HOUSE_COMMON_RESIDENCE;
    house->subtype.house_level = HOUSE_COMMON_RESIDENCE;
    house->size = house->house_size = 2;
    house->house_population += g_merge_data.population;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        house->data.house.inventory[i] += g_merge_data.inventory[i];
    }
    int image_id = house_image_group<true>(house->subtype.house_level) + (map_random_get(house->tile.grid_offset()) & 1);
    map_building_tiles_remove(house->id, house->tile);
    house->tile.set(g_merge_data.x, g_merge_data.y);
    //    house->tile.x() = merge_data.x;
    //    house->tile.y() = merge_data.y;
    //    house->tile.grid_offset() = MAP_OFFSET(house->tile.x(), house->tile.y());
    map_building_tiles_add(house->id, house->tile, house->size, image_id, TERRAIN_BUILDING);
}
void building_house_expand_to_large_villa(building* house) {
    split(house, 9);
    prepare_for_merge(house->id, 9);

    house->type = BUILDING_HOUSE_COMMON_MANOR;
    house->subtype.house_level = HOUSE_COMMON_MANOR;
    house->size = house->house_size = 3;
    house->house_population += g_merge_data.population;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        house->data.house.inventory[i] += g_merge_data.inventory[i];
    }
    int image_id = house_image_group<true>(house->subtype.house_level);
    map_building_tiles_remove(house->id, house->tile);
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
    house->subtype.house_level = HOUSE_MODEST_ESTATE;
    house->size = house->house_size = 4;
    house->house_population += g_merge_data.population;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        house->data.house.inventory[i] += g_merge_data.inventory[i];
    }
    int image_id = house_image_group<true>(house->subtype.house_level);
    map_building_tiles_remove(house->id, house->tile);
    house->tile.set(g_merge_data.x, g_merge_data.y);
    //    house->tile.x() = merge_data.x;
    //    house->tile.y() = merge_data.y;
    //    house->tile.grid_offset() = MAP_OFFSET(house->tile.x(), house->tile.y());
    map_building_tiles_add(house->id, house->tile, house->size, image_id, TERRAIN_BUILDING);
}

void building_house_devolve_from_large_insula(building* house) {
    split_size2(house, BUILDING_HOUSE_SPACIOUS_APARTMENT);
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

    map_building_tiles_remove(house->id, house->tile);

    // main tile
    house->type = BUILDING_HOUSE_FANCY_RESIDENCE;
    house->subtype.house_level = (e_house_level)(house->type - BUILDING_HOUSE_VACANT_LOT);
    house->size = house->house_size = 2;
    house->house_is_merged = 0;
    house->house_population = population_per_tile + population_remainder;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        house->data.house.inventory[i] = inventory_per_tile[i] + inventory_remainder[i];
    }
    house->distance_from_entry = 0;

    int image_id = house_image_group<true>(house->subtype.house_level);
    map_building_tiles_add(house->id, house->tile, house->size, image_id + (map_random_get(house->tile.grid_offset()) & 1), TERRAIN_BUILDING);

    // the other tiles (new buildings)
    image_id = house_image_group<true>(HOUSE_SPACIOUS_APARTMENT);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, house->tile.shifted(2, 0), image_id, population_per_tile,inventory_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, house->tile.shifted(2, 1), image_id, population_per_tile, inventory_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, house->tile.shifted(0, 2), image_id, population_per_tile, inventory_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, house->tile.shifted(1, 2), image_id, population_per_tile, inventory_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, house->tile.shifted(2, 2), image_id, population_per_tile, inventory_per_tile);
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

    map_building_tiles_remove(house->id, house->tile);

    // main tile
    house->type = BUILDING_HOUSE_MEDIUM_PALACE;
    house->subtype.house_level = (e_house_level)(house->type - BUILDING_HOUSE_VACANT_LOT);
    house->size = house->house_size = 3;
    house->house_is_merged = 0;
    house->house_population = population_per_tile + population_remainder;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        house->data.house.inventory[i] = inventory_per_tile[i] + inventory_remainder[i];
    }
    house->distance_from_entry = 0;

    int image_id = house_image_group<true>(house->subtype.house_level);
    map_building_tiles_add(house->id, house->tile, house->size, image_id, TERRAIN_BUILDING);

    // the other tiles (new buildings)
    image_id = house_image_group<true>(HOUSE_SPACIOUS_APARTMENT);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, house->tile.shifted(3, 0), image_id, population_per_tile, inventory_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, house->tile.shifted(3, 1), image_id, population_per_tile, inventory_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, house->tile.shifted(3, 2), image_id, population_per_tile, inventory_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, house->tile.shifted(0, 3), image_id, population_per_tile, inventory_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, house->tile.shifted(1, 3), image_id, population_per_tile, inventory_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, house->tile.shifted(2, 3), image_id, population_per_tile, inventory_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, house->tile.shifted(3, 3), image_id, population_per_tile, inventory_per_tile);
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

void building_house::on_place_checks() {
    if (building_construction_has_warning()) {
        return;
    }
        
    if (type() != BUILDING_HOUSE_VACANT_LOT) {
        return;
    }

    if (city_population() >= 200 && !scenario_property_kingdom_supplies_grain()) {
        if (city_resource_food_percentage_produced() <= 95) {
            building_construction_warning_show(WARNING_MORE_FOOD_NEEDED);
        }
    }
}

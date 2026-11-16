#include "image_context.h"

#include "city/city_buildings.h"
#include "core/core.h"
#include "graphics/view/view.h"
#include "grid/building.h"
#include "grid/elevation.h"
#include "grid/grid.h"
#include "grid/property.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "grid/canals.h"
#include "building/building_wall.h"
#include "js/js_game.h"
#include "moisture.h"
#include "scenario/earthquake.h"

#include <array>
#include <vector>

extern bool city_has_loaded;

struct terrain_image_context {
    unsigned char tiles[MAP_IMAGE_MAX_TILES]{};
    unsigned char offset_for_orientation[4]{};
    unsigned char canal_offset = 0;
    unsigned char max_item_offset = 0;
    unsigned char current_item_offset = 0;
};

struct image_context_row {
    std::array<uint8_t, MAP_IMAGE_MAX_TILES> tiles{};
    std::array<uint8_t, 4> offsets{};
    uint8_t canal = 0;
    uint8_t variants = 1;
};
ANK_CONFIG_STRUCT(image_context_row, tiles, offsets, canal, variants)

// 0 = no match, 1 = match, 2 = don't care (in tiles[])
// All image_context rows live in src/scripts/image_context.js
//
// Neighbor order:
// [5][6][7]
// [4]   [0]
// [3][2][1]

using image_context_rows = std::vector<terrain_image_context>;

struct image_contexts_t {
    image_context_rows water;
    image_context_rows wall;
    image_context_rows wall_gatehouse;
    image_context_rows elevation;
    image_context_rows earthquake;
    image_context_rows dirt_road;
    image_context_rows paved_road;
    image_context_rows canal;
    image_context_rows deepwater;
    image_context_rows floodsystem;
    image_context_rows grass_corners;

    image_context_rows& get(e_terrain_image_context group) {
        switch (group) {
        case CONTEXT_WATER: return water;
        case CONTEXT_WALL: return wall;
        case CONTEXT_WALL_GATEHOUSE: return wall_gatehouse;
        case CONTEXT_ELEVATION: return elevation;
        case CONTEXT_EARTHQUAKE: return earthquake;
        case CONTEXT_DIRT_ROAD: return dirt_road;
        case CONTEXT_PAVED_ROAD: return paved_road;
        case CONTEXT_CANAL: return canal;
        case CONTEXT_DEEPWATER: return deepwater;
        case CONTEXT_FLOODSYSTEM: return floodsystem;
        case CONTEXT_GRASSCORNERS: return grass_corners;
        case CONTEXT_MAX_ITEMS: break;
        }
        return water;
    }
};

static image_contexts_t g_contexts;

static void clear_current_offset(image_context_rows& rows) {
    for (auto& row : rows) {
        row.current_item_offset = 0;
    }
}

static void apply_image_context_rows(image_context_rows& rows, pcstr js_name) {
    rows.clear();
    g_config_arch.r_array(js_name, [&](archive arch) {
        image_context_row entry;
        arch.r(entry);

        terrain_image_context item;
        for (int t = 0; t < MAP_IMAGE_MAX_TILES; t++) {
            item.tiles[t] = entry.tiles[t];
        }
        for (int o = 0; o < 4; o++) {
            item.offset_for_orientation[o] = entry.offsets[o];
        }
        item.canal_offset = entry.canal;
        item.max_item_offset = entry.variants;
        rows.push_back(item);
    });
    verify_no_crash(!rows.empty() && "image_context table missing — check modules.js import image_context");
}

void ANK_REGISTER_CONFIG_ITERATOR(config_load_image_context) {
    apply_image_context_rows(g_contexts.water, "image_context_water");
    apply_image_context_rows(g_contexts.wall, "image_context_wall");
    apply_image_context_rows(g_contexts.wall_gatehouse, "image_context_wall_gatehouse");
    apply_image_context_rows(g_contexts.elevation, "image_context_elevation");
    apply_image_context_rows(g_contexts.earthquake, "image_context_earthquake");
    apply_image_context_rows(g_contexts.dirt_road, "image_context_dirt_road");
    apply_image_context_rows(g_contexts.paved_road, "image_context_paved_road");
    apply_image_context_rows(g_contexts.canal, "image_context_canal");
    apply_image_context_rows(g_contexts.deepwater, "image_context_deepwater");
    apply_image_context_rows(g_contexts.floodsystem, "image_context_floodsystem");
    apply_image_context_rows(g_contexts.grass_corners, "image_context_grass_corners");

    if (city_has_loaded) {
        map_tiles_update_all_roads();
        map_tiles_river_refresh_entire();
        map_tiles_update_all_elevation();
        map_tiles_update_all_earthquake();
        map_canal_update_all_tiles(0);
        building_mud_wall::update_all_walls();
    }
}

void map_image_context_init(void) {
    clear_current_offset(g_contexts.water);
    clear_current_offset(g_contexts.wall);
    clear_current_offset(g_contexts.wall_gatehouse);
    clear_current_offset(g_contexts.elevation);
    clear_current_offset(g_contexts.earthquake);
    clear_current_offset(g_contexts.dirt_road);
    clear_current_offset(g_contexts.paved_road);
    clear_current_offset(g_contexts.canal);
    clear_current_offset(g_contexts.deepwater);
    clear_current_offset(g_contexts.floodsystem);
    clear_current_offset(g_contexts.grass_corners);
}

void map_image_context_reset_water(void) {
    clear_current_offset(g_contexts.water);
}

void map_image_context_reset_elevation(void) {
    clear_current_offset(g_contexts.elevation);
}

bool map_image_context_context_matches_tiles(const terrain_image_context* context, const image_tiles_vec& tiles) {
    for (int i = 0; i < MAP_IMAGE_MAX_TILES; i++) {
        if (context->tiles[i] != 2 && tiles[i] != context->tiles[i]) // if pattern isn't "2", it must match!
            return false;
    }
    return true;
}

void map_image_context_fill_matches_grass(tile2i tile, int match_value, int no_match_value, image_tiles_vec& tiles) {
    const int grid_offset = tile.grid_offset();
    for (int i = 0; i < MAP_IMAGE_MAX_TILES; i++) {
        int moisture = map_moisture_get(grid_offset + map_grid_direction_delta(i));
        if (moisture & MOISTURE_TRANSITION)
            tiles[i] = no_match_value;
        else if (moisture >= 46 && moisture <= 50)
            tiles[i] = match_value;
        else
            tiles[i] = no_match_value;
    }
}

terrain_image map_image_context_get_terrain_image(e_terrain_image_context group, const image_tiles_vec& tiles) {
    terrain_image result;

    result.is_valid = 0;
    auto& rows = g_contexts.get(group);
    for (auto& context : rows) {
        if (map_image_context_context_matches_tiles(&context, tiles)) {
            context.current_item_offset++;
            if (context.current_item_offset >= context.max_item_offset)
                context.current_item_offset = 0;

            result.is_valid = 1;
            result.group_offset = context.offset_for_orientation[g_camera.orientation / 2];
            result.item_offset = context.current_item_offset;
            result.canal_offset = context.canal_offset;
            break;
        }
    }

    return result;
}

terrain_image map_image_context_get_elevation(int grid_offset, int elevation) {
    image_tiles_vec tiles;
    for (int i = 0; i < MAP_IMAGE_MAX_TILES; i++) {
        tiles[i] = map_elevation_at(grid_offset + map_grid_direction_delta(i)) >= elevation ? 1 : 0;
    }
    return map_image_context_get_terrain_image(CONTEXT_ELEVATION, tiles);
}

terrain_image map_image_context_get_earthquake(int grid_offset) {
    image_tiles_vec tiles;
    for (int i = 0; i < MAP_IMAGE_MAX_TILES; i++) {
        int offset = grid_offset + map_grid_direction_delta(i);
        tiles[i] = (map_terrain_is(offset, TERRAIN_ROCK) && map_property_is_plaza_or_earthquake(tile2i(grid_offset))) ? 1 : 0;
    }
    return map_image_context_get_terrain_image(CONTEXT_EARTHQUAKE, tiles);
}

terrain_image map_image_context_get_shore(tile2i tile) {
    image_tiles_vec tiles;
    map_image_context_fill_matches(tile, TERRAIN_WATER, { 0, 1 }, tiles);
    return map_image_context_get_terrain_image(CONTEXT_WATER, tiles);
}

terrain_image map_image_context_get_river(tile2i tile) {
    image_tiles_vec tiles;
    map_image_context_fill_matches(tile, TERRAIN_DEEPWATER, { 1, 0 }, tiles);
    return map_image_context_get_terrain_image(CONTEXT_DEEPWATER, tiles);
}

terrain_image map_image_context_get_floodplain_shore(tile2i tile) {
    image_tiles_vec tiles;
    map_image_context_fill_matches(tile, TERRAIN_FLOODPLAIN, { 0, 1 }, tiles);
    return map_image_context_get_terrain_image(CONTEXT_DEEPWATER, tiles);
}

terrain_image map_image_context_get_floodplain_waterline(tile2i tile) {
    image_tiles_vec tiles;
    map_image_context_fill_matches(tile, TERRAIN_WATER, { 1, 0 } , tiles);
    return map_image_context_get_terrain_image(CONTEXT_FLOODSYSTEM, tiles);
}

terrain_image map_image_context_get_reeds_transition(tile2i tile) {
    image_tiles_vec tiles;
    map_image_context_fill_matches(tile, TERRAIN_MARSHLAND, { 1, 0 }, tiles);
    return map_image_context_get_terrain_image(CONTEXT_FLOODSYSTEM, tiles);
}

terrain_image map_image_context_get_grass_corners(tile2i tile) {
    image_tiles_vec tiles;
    map_image_context_fill_matches_grass(tile, 1, 0, tiles);
    return map_image_context_get_terrain_image(CONTEXT_GRASSCORNERS, tiles);
}

terrain_image map_image_context_get_wall_gatehouse(tile2i tile) {
    image_tiles_vec tiles = {0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < MAP_IMAGE_MAX_TILES; i += 2) {
        const int grid_offset = tile.grid_offset() + map_grid_direction_delta(i);
        tiles[i] = map_terrain_is(grid_offset, TERRAIN_WALL_OR_GATEHOUSE) ? 1 : 0;
    }
    return map_image_context_get_terrain_image(CONTEXT_WALL_GATEHOUSE, tiles);
}

void map_image_context_set_tiles_road(tile2i tile, image_tiles_vec& tiles) {
    map_image_context_fill_matches(tile, TERRAIN_ROAD, { 1, 0 }, tiles);
    const int grid_offset = tile.grid_offset();
    for (int i = 0; i < MAP_IMAGE_MAX_TILES; i += 2) {
        int offset = grid_offset + map_grid_direction_delta(i);
        if (map_terrain_is(offset, TERRAIN_GATEHOUSE)) {
            building* b = building_at(offset);
            if ((b->type == BUILDING_MUD_GATEHOUSE || b->type == BUILDING_DECORATIVE_GATEHOUSE) && b->orientation == 1 + ((i / 2) & 1)) { // 1,2,1,2
                tiles[i] = 1;
            }
        } else if (map_terrain_is(offset, TERRAIN_ACCESS_RAMP)) {
            tiles[i] = 1;
        } else if (map_terrain_is(offset, TERRAIN_BUILDING)) {
            building* b = building_at(offset);
            //if (b->type == BUILDING_GRANARY) {
            //    tiles[i] = (offset == b->tile.grid_offset() + GRID_OFFSET(1, 0)) ? 1 : 0;
            //    tiles[i] |= (offset == b->tile.grid_offset() + GRID_OFFSET(0, 1)) ? 1 : 0;
            //    tiles[i] |= (offset == b->tile.grid_offset() + GRID_OFFSET(2, 1)) ? 1 : 0;
            //    tiles[i] |= (offset == b->tile.grid_offset() + GRID_OFFSET(1, 2)) ? 1 : 0;
            //}
        }
    }
}

terrain_image map_image_context_get_dirt_road(tile2i tile) {
    image_tiles_vec tiles;
    map_image_context_set_tiles_road(tile, tiles);
    return map_image_context_get_terrain_image(CONTEXT_DIRT_ROAD, tiles);
}

terrain_image map_image_context_get_paved_road(tile2i tile) {
    image_tiles_vec tiles;
    map_image_context_set_tiles_road(tile, tiles);
    return map_image_context_get_terrain_image(CONTEXT_PAVED_ROAD, tiles);
}

void map_image_context_fill_matches(tile2i tile, int terrain, match_option match, image_tiles_vec &tiles) {
    const int grid_offset = tile.grid_offset();

    for (int i = 0; i < MAP_IMAGE_MAX_TILES; i++) {
        const int t_offset = grid_offset + map_grid_direction_delta(i);
        tiles[i] = map_terrain_is(t_offset, terrain) ? match.match : match.nomatch;
    }
}

void map_image_context_fill_matches(tile2i tile, int terrain, e_building_type btype, match_option match, image_tiles_vec &tiles) {
    const int grid_offset = tile.grid_offset();

    for (int i = 0; i < MAP_IMAGE_MAX_TILES; i++) {
        const int tile_ter = map_terrain_get(grid_offset + map_grid_direction_delta(i));

        const bool is_building = !!(tile_ter & TERRAIN_BUILDING);
        if (is_building) {
            const int tile_bid = map_building_at(tile);
            const int tile_btype = building_get(tile_bid)->type;
            tiles[i] = (tile_bid == btype) ? match.match : match.nomatch;
        } else {
            tiles[i] = !!(tile_ter & terrain) ? match.match : match.nomatch;
        }
    }
}


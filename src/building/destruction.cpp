#include "destruction.h"

#include "building/building_house.h"
#include "building/building_wall.h"
#include "city/city_message.h"
#include "city/city_population.h"
#include "city/city.h"
#include "figuretype/wall.h"
#include "game/undo.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/grid.h"
#include "grid/random.h"
#include "grid/routing/routing_terrain.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "sound/sound.h"

#include <core/random.h>
#include <string.h>

void building_destroy_by_poof(building* b, bool clouds) {
    b = b->main();
    if (clouds) {
        figure_create_explosion_cloud(b->tile, b->size);
        g_sound.play_effect(SOUND_EFFECT_EXPLOSION);
    }

    do {
        b->state = BUILDING_STATE_UNUSED;
        map_tiles_update_region_empty_land(true, b->tile, b->tile.shifted(b->size - 1, b->size - 1));
        if (b->next_part_building_id < 1) {
            return;
        }

        b = b->next();
    } while (true);
}

int building_destroy_first_of_type(e_building_type type) {
    int i = building_id_first(type);
    if (i < MAX_BUILDINGS) {
        building* b = building_get(i);
        int grid_offset = b->tile.grid_offset();
        game_undo_disable();
        b->state = BUILDING_STATE_RUBBLE;
        map_building_tiles_set_rubble(i, b->tile, b->size);
        g_sound.play_effect(SOUND_EFFECT_EXPLOSION);
        map_routing_update_land();
        return grid_offset;
    }
    return 0;
}

void building_destroy_increase_enemy_damage(int grid_offset, int max_damage) {
    if (map_building_damage_increase(grid_offset) > max_damage) {
        building_destroy_by_enemy(tile2i(grid_offset));
    }
}

void building_destroy_by_enemy(tile2i tile) {
    int building_id = map_building_at(tile);
    if (building_id > 0) {
        building* b = building_get(building_id);
        if (b->state == BUILDING_STATE_VALID) {
            g_city.ratings.monument_building_destroyed(b->type);
            b->destroy_by_collapse();
        }
    } else {
        if (map_terrain_is(tile, TERRAIN_WALL)) {
            figure_kill_tower_sentries_at(tile);
        }

        map_building_tiles_set_rubble(0, tile, 1);
    }
    figure_tower_sentry_reroute();
    building_mud_wall::update_area_walls(tile, 3);
    map_tiles_update_region_canals(tile.shifted(-3, -3), tile.shifted(3, 3));
    map_routing_update_land();
    map_routing_update_walls();
}
